#include<stdio.h>
void fib(int num1,int num2,int n){
    if(n==0)
        return;
    n--;
    printf("%d\t",num1);
    fib(num2,(num1+num2),n);

}
void main(){
    int num;
    printf("Enter a number\n");
    scanf("%d",&num);
    fib(0,1,num);
}