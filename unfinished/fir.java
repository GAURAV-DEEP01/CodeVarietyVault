
import java.util.Scanner;
class Sum {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.println("Enter two numbers");
        int num1 = input.nextInt();
        int num2 = input.nextInt();
        System.out.println("The sum is "+(num1+num2));
        input.close();
    }
}