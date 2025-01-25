//&>/dev/null;x="${0%.*}";[ ! "$x" -ot "$0" ]||(rm -f "$x";g++ -o "$x" "$0")&&exec "$x" "$@"
#include <cctype>
#include <cstdio>
#include <cwchar>
#include <time.h>
#include <cstdlib>
#include <string>
#include <utility>
#include <iostream>
#include <vector>

using namespace std;

enum {
    WUMPUS = 1,
    DEADWUMPUS,
    PIT,
    STENCH,
    BREEZE,
    BREEZEANDSTENCH, 
    GOLD,
    AGENT,
};

string pad(){ return "\t\t"; }

class Surface{
public:
    vector<vector<int>> cave;
    pair<int, int> goldLocation;
    int wumpusCount = 1,  pitCount;

    Surface(int n){
        cave = vector(n, vector<int>(n, 0));
        hidden = vector(n, vector<int>(n, true));
        srand(time(nullptr));
        while(isInSpawn(goldLocation.first = rand() % n, goldLocation.second = rand() % n));
        cave[ goldLocation.first ][ goldLocation.second ] = GOLD;
        pitCount = rand() % n + 2;
        generateRandomSurface();
    }

    void showEntireCave(pair<int, int> &agentLocation){
        cout<<pad()<<"+";
        for(int i = 0; i<cave.size(); i++){
            cout<<"-----";
            if(i != cave.size() - 1) cout<<" ";
        }
        cout<<"+\n";
        for(int i = 0; i<cave.size(); i++){
            cout<<pad()<<"|";
            for(int j = 0; j<cave[0].size(); j++){
                if(i == agentLocation.first && j == agentLocation.second){
                    cout<<toAsciiSprite(AGENT)<<"|";
                    continue;
                }
                cout<<toAsciiSprite(cave[i][j])<<"|";
            }
            cout<<"\n";
        }
        cout<<pad()<<"+";
        for(int i = 0; i<cave.size(); i++){
            cout<<"-----";
            if(i != cave.size() - 1) cout<<" ";
        }
        cout<<"+"<<endl;
    }

    void showCaveVisibleToAgent(pair<int, int> &agentLocation){
        cout<<pad()<<"+";
        for(int i = 0; i<cave.size(); i++){
            cout<<"-----";
            if(i != cave.size() - 1) cout<<" ";
        }
        cout<<"+\n";
        for(int i = 0; i<cave.size(); i++){
            cout<<pad()<<'|';
            for(int j = 0; j<cave[0].size(); j++){
                if(i == agentLocation.first && j == agentLocation.second){
                    cout<<toAsciiSprite(AGENT)<<"|";
                    continue;
                }
                hidden[i][j] == true? 
                cout<<"[||||]":
                cout<<toAsciiSprite(cave[i][j])<<"|";
            }
            cout<<"\n";
        }
        cout<<pad()<<"+";
        for(int i = 0; i<cave.size(); i++){
            cout<<"-----";
            if(i != cave.size() - 1) cout<<" ";
        }
        cout<<"+"<<endl;
    }

    void seeSurround(int i, int j){
        hidden[i][j] = false;
    }

    static string toAsciiSprite(int type){
        switch (type) {
            case WUMPUS: return "*0x0*";
            case PIT: return "[ x ]";
            case STENCH: return "[ # ]";
            case BREEZE: return "[ ~ ]";
            case BREEZEANDSTENCH: return "[~ #]";
            case GOLD: return "[ $ ]";
            case AGENT: return "(0.0)";
            case DEADWUMPUS: return "*xox*";
        }
        return "     ";
    }

    static void worldInstructions(){
        cout<<pad()<<toAsciiSprite(WUMPUS)<<"\tWumpus\t\t";
        cout<<pad()<<toAsciiSprite(PIT)<<"\tPit\n";
        cout<<pad()<<toAsciiSprite(GOLD)<<"\tGold\t\t";
        cout<<pad()<<toAsciiSprite(BREEZE)<<"\tBreeze\n";
        cout<<pad()<<toAsciiSprite(STENCH)<<"\tStench\t\t";
        cout<<pad()<<toAsciiSprite(AGENT)<<"\tAgent\n";
        cout<<pad()<<toAsciiSprite(DEADWUMPUS)<<"\tDeadwumpus\n\n";
    }

private:
    vector<vector<int>> hidden;

    void generateRandomSurface(){
        int i, j;
        while(wumpusCount){
            i = rand() % cave.size();
            j = rand() % cave.size() ;
            if(cave[i][j] != GOLD && !isInSpawn(i, j)){
                cave[i][j] = WUMPUS;
                addSurround(i, j, WUMPUS);
                wumpusCount--;
            }
        }

        while(pitCount){
            i = rand() % cave.size();
            j = rand() % cave.size();
            if(!isSomethingHere(cave[i][j]) && !isInSpawn(i, j)){
                cave[i][j] = PIT;
                addSurround(i, j, PIT);
                pitCount--; 
            }
        }
    }

    void addSurround(int i, int j, int type){
        int surround = type == WUMPUS ? STENCH:BREEZE;
        int up = i - 1, down = i + 1, left = j - 1, right = j + 1;

        if(up >= 0 && !isSomethingHere(cave[up][j]))
            placeSurround(up, j, surround);

        if(down< cave.size() && !isSomethingHere(cave[down][j]))
            placeSurround(down, j, surround);

        if(left >= 0 && !isSomethingHere(cave[i][left]))
            placeSurround(i, left, surround);

        if(right< cave.size() && !isSomethingHere(cave[i][right]))
            placeSurround(i, right, surround);
    }

    void placeSurrounding(int i, int j, int surround){
        if(cave[i][j] == BREEZE || cave[i][j] == STENCH){
            if(cave[i][j] != surround)
                cave[i][j] = BREEZEANDSTENCH;
        }else{
            cave[i][j] = surround;
        }
    }

    bool isSomethingHere(int type){
        switch (type) {
            case PIT: return true;
            case WUMPUS: return true;
            case GOLD: return true;
        }
        return false;
    }

    bool isInSpawn(int i, int j){
        if((i == 0 && j == 0) || (i == 1 && j == 0) || (i == 0 && j == 1))
            return true;
        return false;
    }

   void placeSurround(int i, int j, int surround){
        if(cave[i][j] == BREEZE || cave[i][j] == STENCH){
            if(cave[i][j] != surround)
                    cave[i][j] = BREEZEANDSTENCH;
        }else{
                cave[i][j] = surround;
        }
    }
};

class Agent{
public:
    Surface s;
    int arrows;
    int points;
    bool isWampusAlive = true;
    pair<int, int> location;

    Agent(int n, int arrows):s(n){
        this->arrows = arrows; 
        points = n * n;
        location.first = location.second = 0;
        s.seeSurround(0, 0);
        system("clear");
        gameLoop();
    }

    void getPrimaryChoice(){
        char ch;
        while(true){
            cin>>ch;
            ch = tolower(ch);
            switch (ch) {
                case 'm': moveChoice(); return;
                case 'f': fireChoice(); return;
                case 'q': quit(); return; 
                default: cout<<pad()<<"|xxx|-----Wrong Controls!-----|xxx|"<<"\n";
            }
        }
    }

    void moveChoice(){
        int i, j;
        char ch;
        ch = secondaryChoice();
        switch (ch) {
            case 'w': location.first--;
            break;
            case 's': location.first++;
            break;
            case 'a': location.second--;
            break;
            case 'd': location.second++;
            break;
        }
        points--;
        s.seeSurround(location.first, location.second);
    }

    char secondaryChoice(){
       char ch;
        cout<<pad()<<"(W) Up  \t(S) Down\t(A) Left\t(D) Right\n";
        while(true){
            cin>> ch;
            switch (ch) {
                case 'w': 
                    if(location.first - 1 >= 0) return ch;
                    break;
                case 's':
                    if(location.first + 1 < s.cave.size()) return ch;
                    break;
                case 'a':
                    if(location.second - 1 >= 0) return ch;
                    break;
                case 'd':
                    if(location.second + 1 <s.cave.size()) return ch;
                    break;
            }
            points -= 5;
            cout<<pad()<<"Agent hit the cave Wall --(x.x)-- (Penalty-5 Points)"<<"\n";
        }
    }

    void fireChoice(){
        int i = location.first, j = location.second;
        char ch;
        ch = secondaryChoice();
        switch (ch) {
            case 'w': i--;
            break;
            case 's': i++;
            break;
            case 'a': j--;
            break;
            case 'd': j++;
            break;
        }
        if(s.cave[i][j] == WUMPUS){
            isWampusAlive = false;
            s.cave[i][j] = DEADWUMPUS;
            points += 30;
        }
    }

    void quit(){
        s.showEntireCave(location);
        cout<<pad()<<"Game Over"<<endl;
        gameOver();
    }

    void gameLoop(){
        while(true){
            Surface::worldInstructions();
            frame();
            getPrimaryChoice();
            system("clear");
        }
    }

    void frame(){
        s.showCaveVisibleToAgent(location);
        currentLocationData();
        movementInstruction();
    }

    void gameOver(){
        cout<<"\n"<<pad()<<"Agent Points: "<<points<<"\n";
        exit(0);
    }
    void currentLocationData(){
        if(s.cave[location.first][location.second] == PIT){
            cout<<"[x-x]: Agent fell into a Pit"<<endl;
            s.showEntireCave(location);
            points -= 50;
            gameOver();
        }

        if(s.cave[location.first][location.second] == WUMPUS){
            cout<<"[x-x]: Wumpus destroied the Agent"<<endl;
            s.showEntireCave(location);
            points -= 50;
            gameOver();
        }

        if(s.cave[location.first][location.second] == GOLD){
            cout<<"[x-x]: Agent Found the Gold!"<<endl;
            s.showEntireCave(location);
            points += 70;
            gameOver();
        }

        if(!isWampusAlive){
            cout<<pad()<<"Wampus has been shot dead\n";
            isWampusAlive = true; // i had no option
        }
        cout<<"\n"<<pad()<<Surface::toAsciiSprite(AGENT)<<" Found: "
            <<(s.cave[location.first][location.second]?
                Surface::toAsciiSprite(s.cave[location.first][location.second]):
                "Nothing")<<pad()<<"Points: "<<points<<"\n\n";
    }

    void movementInstruction(){
        cout<<pad()<<"(M) Move\t\t";
        cout<<"(F) Fire Arrow\t\t";
        cout<<"(Q) Quit and see world\n\n";
    }
};

int main(int argc, char* argv[]){
    if(argc != 2){
        cout<<"Cave size is Undefined"<<endl;
        return 0;
    }
    int num = stoi(argv[1]);

    Agent a(num, 1);
    return 0;
}

