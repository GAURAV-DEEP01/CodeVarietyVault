// no ai challenge
package main

import (
	"bufio"
	"errors"
	"fmt"
	"io"
	"net"
	"os"
	"strings"
	"sync"
	"time"

	"golang.org/x/term"
)

const (
	WINNING_POINTS = 300
	WIN_OFFSET     = 6
)

type Player struct {
	score         int
	previousClick time.Time
}
type Terminal struct {
	width  int
	height int
}

var (
	click       chan struct{}
	stopSending chan struct{}
	started     chan struct{}

	you      Player
	opponent Player

	exited = false
	isHost = false

	terminal  Terminal
	clickLock *sync.Mutex
	w         *bufio.Writer
)

func main() {
	you = Player{score: 0}
	opponent = Player{score: 0}

	click = make(chan struct{})
	stopSending = make(chan struct{})
	started = make(chan struct{})

	defer close(click)
	defer close(stopSending)
	defer close(started)

	var choice string
	var conn net.Conn
	var err error

	terminal = Terminal{}
	terminal.width, terminal.height, err = term.GetSize(int(os.Stdin.Fd()))
	if err != nil {
		fmt.Println("Couldnt get terminal Dimentions", err)
		return
	}
	clickLock = &sync.Mutex{}
	w = bufio.NewWriter(os.Stdout)

	centerCard(pad(4)+"Game Keys: Press 'space' to Go forward"+pad(4), 0)

	fmt.Println()
	fmt.Print("Do you want to Host? (y/n): ")
	fmt.Scan(&choice)

	conn, isWrongInput := decideHostOrJoin(choice, conn, err)
	if isWrongInput {
		return
	}
	if conn == nil {
		return
	}

	oldState, err := term.MakeRaw(int(os.Stdin.Fd()))
	if err != nil {
		panic(err)
	}
	defer func() {
		term.Restore(int(os.Stdin.Fd()), oldState)
		err := recover()
		if err != nil {
			fmt.Println("Something Went wrong")
		}
	}()

	defer func() {
		fmt.Print("\033[?25h")
	}()

	defer conn.Close()
	handleConnections(conn)
}

func decideHostOrJoin(choice string, conn net.Conn, err error) (net.Conn, bool) {
	if strings.Compare(choice, "y") == 0 {
		isHost = true
		ips, err := GetLocalIP()
		if err != nil {
			fmt.Println("Failed to get Host IP", err)
			return nil, true
		}
		fmt.Println("Hosts IP For others to Join: ", ips)
		joined := make(chan struct{})
		waitForOpponent := func() {
			fmt.Print("\033[?25l")
			fmt.Print("Waiting for opponent to join")
		Loop:
			for {
				select {
				case <-joined:
					break Loop
				default:
				}
				for range 3 {
					fmt.Print(".")
					time.Sleep(time.Millisecond * 300)
				}
				fmt.Print("\b\b\b   \b\b\b")
				time.Sleep(time.Millisecond * 300)
			}
			fmt.Println()
		}
		go waitForOpponent()

		conn = hostGame(conn, joined)
	} else if strings.Compare(choice, "n") == 0 {
		fmt.Print("Joining..", endl())
		conn = joinGame(conn, err)
	} else {
		fmt.Print("Dont Press Random buttons, Choose something!!...", endl())
		return nil, true
	}
	return conn, false
}

func joinGame(conn net.Conn, err error) net.Conn {
	fmt.Print("Enter the Host IP to connect to: ")

	var hostIp string
	fmt.Scan(&hostIp)

	if strings.Trim(hostIp, " ") != "localhost" {
		isValid := net.ParseIP(hostIp)
		if isValid == nil {
			fmt.Println("Invalid IP")
			return nil
		}
	}
	conn, err = net.Dial("tcp", hostIp+":8000")

	if err != nil {
		fmt.Print("Failed to accept connections: ", err, endl())
		return nil
	}
	fmt.Print("Connected to Host...", endl())
	return conn
}

func hostGame(conn net.Conn, joined chan struct{}) net.Conn {
	listener, err := net.Listen("tcp", ":8000")
	if err != nil {
		fmt.Print("Failed to host: ", err, endl())
		return nil
	}

	conn, err = listener.Accept()
	if err != nil {
		fmt.Print("Failed to accept connections: ", err, endl())
		return nil
	}

	joined <- struct{}{}
	fmt.Print("A Player has Joined...", endl())
	return conn
}

func handleConnections(conn net.Conn) {
	var wg sync.WaitGroup

	wg.Add(2)
	go recieveData(conn, &wg)
	go sendData(conn, &wg)
	go gameLoop()
	wg.Wait()
}

func recieveData(conn net.Conn, wg *sync.WaitGroup) {
	defer wg.Done()
	defer conn.Close()

	buff := make([]byte, 100)

	defer func() {
		stopSending <- struct{}{}
	}()

	<-started
	for {
		_, err := conn.Read(buff)

		if errors.Is(err, io.EOF) {
			if exited {
				return
			}
			exited = true
			fmt.Print("Connection Closed by opponent", endl())
			return
		}

		if err != nil {
			if strings.Contains(err.Error(), "use of closed network connection") {
				return
			}
			fmt.Print("Something went wrong while reciving data: ", err, endl())
			return
		}

		isClosingKey := checkIfClosingKey(buff[0])
		if isClosingKey || exited {
			fmt.Print("Connection Closed", endl())
			return
		}

		if buff[0] == ' ' {
			opponent.score++
			clickLock.Lock()
			click <- struct{}{}
			clickLock.Unlock()
		}
	}
}

func sendData(conn net.Conn, wg *sync.WaitGroup) {
	defer conn.Close()
	buff := make([]byte, 1)

	go func() {
		<-stopSending
		wg.Done()
	}()

	<-started
	for {
		_, err := os.Stdin.Read(buff)
		if err != nil {
			fmt.Print("Failed to read Key Press", err, endl())
			return
		}

		isClosingKey := checkIfClosingKey(buff[0])
		if isClosingKey || exited {
			fmt.Print("Quitting application", endl())
			return
		}

		if buff[0] == ' ' {
			timeSinceClick := time.Since(you.previousClick)
			you.previousClick = time.Now()

			if timeSinceClick.Milliseconds() < 60 {
				continue
			}

			you.score++
			clickLock.Lock()
			click <- struct{}{}
			clickLock.Unlock()
		}

		_, err = conn.Write(buff)
		if err != nil {
			if strings.Contains(err.Error(), "use of closed network connection") {
				return
			}
			fmt.Print("Something went wrong while sending data: ", err, endl())
			return
		}
	}
}

func checkIfClosingKey(b byte) bool {
	if b == 'q' || b == 3 /* ctrl + c */ || b == 27 /* esc */ {
		exited = true
		return true
	}

	return false
}

func gameLoop() {
	var winStr string

	startGame()
	for {
		render()
		winStr = isWinner()

		if exited {
			fmt.Fprint(w, endl())
			centerCard(winStr, len(red("")))
			return
		}
		<-click
	}
}
func startGame() {
	time.Sleep(time.Second * 2)

	render()

	if !isHost {
		time.Sleep(time.Millisecond * 500)
	}

	var light func(string) string
	for i := range 3 {
		switch i {
		case 0:
			light = redBg
		case 1:
			light = yelloBg
		case 2:
			light = greenBg
		}
		fmt.Fprint(w, "\033[H")
		fmt.Fprint(w, endl(), endl(), endl())
		centerCard(pad(4)+fmt.Sprintf("Game starts in %v ", 3-i)+light("  ")+pad(4), len(redBg("")))
		time.Sleep(time.Second * 1)
		w.Flush()
	}

	started <- struct{}{}
	started <- struct{}{}
}

func isWinner() string {
	padding := 4
	if opponent.score == WINNING_POINTS && you.score == WINNING_POINTS {
		exited = true
		return pad(padding) + "Its a tie" + pad(padding)
	}

	if opponent.score == WINNING_POINTS {
		exited = true
		return pad(padding) + red("Opponent Wins") + pad(padding)
	}

	if you.score == WINNING_POINTS {
		exited = true
		return pad(padding) + green("You win!") + pad(padding)
	}

	return ""
}

func centerCard(s string, invisibleChars int) {
	padTillCenter := func() {
		totalPadding := (terminal.width / 2) - (len(s) / 2)
		for range totalPadding {
			fmt.Fprint(w, "\033[C")
		}
	}

	fmt.Fprint(w, endl())

	padTillCenter()
	fmt.Fprint(w, "╭")
	for range len(s) - invisibleChars {
		fmt.Fprint(w, "─")
	}
	fmt.Fprint(w, "╮", endl())

	padTillCenter()
	fmt.Fprint(w, "│")
	for range len(s) - invisibleChars {
		fmt.Fprint(w, " ")
	}
	fmt.Fprint(w, "│", endl())

	padTillCenter()
	fmt.Fprint(w, "│")
	fmt.Fprint(w, s)
	fmt.Fprint(w, "│", endl())

	padTillCenter()
	fmt.Fprint(w, "│")
	for range len(s) - invisibleChars {
		fmt.Fprint(w, " ")
	}
	fmt.Fprint(w, "│", endl())

	padTillCenter()
	fmt.Fprint(w, "╰")
	for range len(s) - invisibleChars {
		fmt.Fprint(w, "─")
	}
	fmt.Fprint(w, "╯", endl())

	w.Flush()
}

func render() {
	// i keep forgetting this, This is clear screen and go to top!!!!!
	fmt.Fprint(w, "\033[H\033[2J")

	fmt.Fprint(w, endl(), endl())

	fmt.Fprint(w, "You:", endl())
	drawCar(you.score, true)
	drawTrack()

	fmt.Fprint(w, endl(), endl(), endl())

	fmt.Fprint(w, "Opponent:", endl())
	drawCar(opponent.score, false)
	drawTrack()

	w.Flush()
}

func drawTrack() {
	for range terminal.width {
		fmt.Fprint(w, "=")
	}
}

func drawCar(score int, isYou bool) {
	carWidth := 12
	spaceInFront := 0

	var err error
	var perc int

	terminal.width, terminal.height, err = term.GetSize(int(os.Stdin.Fd()))
	var carColor func(string) string

	if isYou {
		carColor = blue
	} else {
		carColor = yello
	}

	if err != nil {
		fmt.Print("Couldn't get terminal dimentions", err)
	}

	if score != 0 {
		perc = terminal.width * score / WINNING_POINTS
		if perc < carWidth {
			spaceInFront = terminal.width - carWidth - 2
		} else {
			spaceInFront = terminal.width - perc - 2
		}

		for range perc - carWidth {
			fmt.Fprint(w, " ")
		}

		fmt.Fprint(w, carColor("_    ___"), endl())

		for range perc - carWidth {
			fmt.Fprint(w, " ")
		}

		fmt.Fprint(w, carColor(" \\__│___\\___"), endl())

		for range perc - carWidth {
			fmt.Fprint(w, " ")
		}

		switch score % 10 {
		case 0:

			fmt.Fprint(w, ".=D", carColor("────────"), "D")
		case 1:
			fmt.Fprint(w, red("*"), "=D", carColor("────────"), "D")
		case 2:
			fmt.Fprint(w, redBg("#"), "=D", carColor("────────"), "D")
		default:
			fmt.Fprint(w, " =0", carColor("────────"), "0")
		}
	} else {
		spaceInFront = terminal.width - carWidth - 2
		fmt.Fprint(w, carColor("_    ___"), endl())
		fmt.Fprint(w, carColor(" \\__│___\\___"), endl())
		fmt.Fprint(w, " =0", carColor("────────"), "0")
	}

	if perc == terminal.width {
		fmt.Fprint(w, endl())
		return
	}

	for range spaceInFront {
		fmt.Fprint(w, " ")
	}

	if perc <= terminal.width-2 {
		fmt.Fprint(w, "│")
	}

	if perc <= terminal.width-1 {
		fmt.Fprint(w, "⠿")
	}

	fmt.Fprint(w, endl())
}

func endl() string {
	return ("\r\n")
}

func GetLocalIP() (string, error) {
	addrs, err := net.InterfaceAddrs()
	if err != nil {
		return "", err
	}
	for _, addr := range addrs {
		if ipnet, ok := addr.(*net.IPNet); ok && !ipnet.IP.IsLoopback() {
			if ip4 := ipnet.IP.To4(); ip4 != nil {
				return ip4.String(), nil
			}
		}
	}
	return "", fmt.Errorf("no IP found")
}

func pad(n int) string {
	return strings.Repeat(" ", n)
}
func red(s string) string {
	return "\033[31m" + s + "\033[0m"
}

func blue(s string) string {
	return "\033[34m" + s + "\033[0m"
}

func yello(s string) string {
	return "\033[33m" + s + "\033[0m"
}

func green(s string) string {
	return "\033[32m" + s + "\033[0m"
}

func redBg(s string) string {
	return "\033[41m" + s + "\033[0m"
}

func yelloBg(s string) string {
	return "\033[43m" + s + "\033[0m"
}

func greenBg(s string) string {
	return "\033[42m" + s + "\033[0m"
}
