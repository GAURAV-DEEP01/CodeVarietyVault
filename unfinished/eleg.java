import java.util.Scanner;
class eligible{
    public static void main(String args[]){
        Scanner input = new Scanner(System.in);
        System.out.println("Enter the age");
        int age = input.nextInt();
        if(age<18)
            System.out.println("not eligible");
        else    
            System.out.println("eligble");
        input.close();
    }
}