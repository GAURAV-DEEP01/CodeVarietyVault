#include<stdio.h>
#include<stdlib.h>

#define MAX 5
int s[MAX];
int top = -1;

void palindrome();
void push(int);
int pop();
void display();

void main(){
    int choice,item;
    while(1){
        printf("\n\n~~~~~~~MENU~~~~~~:\n");
        printf("=>1. Push an element to stack and overflow demo\n");
        printf("=>2. pop an element from the stack and underflow demo\n");
        printf("=>3. Palindrome demo\n");
        printf("=>4. Display\n");
        printf("=>5. Exit\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);
        switch (choice){
            case 1: printf("Enter the element to be pushed:");
                    scanf("%d",&item);
                    push(item);
                    break;
            case 2: item = pop();
                    if(item != -1)
                        printf("\nElement poped is : %d",item);
                    break;
            case 3: palindrome();
                    break;
            case 4: display();
                    break;
            case 5: exit(1);
            default:printf("\nPlease enter valid choice");
                    break;
        }
    }
}
void push(int item){
    if(top+1 == MAX){
        printf("\n~~~~~~~~Stack Overflow~~~~~~~~");
        return;
    }
    s[++top] = item;
}
int pop(){
    if (top == -1){
        printf("\n~~~~~~~Stack Underflow~~~~~~~~");
        return top;
    }
    return s[top--];
}
void display(){
    if(top == -1){
        printf("\n~~~~~~~~~Stack Is Empty~~~~~~~~~");
        return;
    }
    printf("\nStack elements are :\n");
    for(int i= top;i>=0;i--)
        printf("| %d |\n",s[i]);
}
void palindrome(){
    int flag = 1;
    printf("\nStack content are :\n");
    for(int i = top;i>=0;i--)
        printf("| %d |\n",s[i]);
    printf("\nReverse of stack content are :\n");
    for(int i = 0;i<=top;i++)
        printf("| %d |\n",s[i]);
    for(int i=0;i<top/2;i++){
        if(s[i] != s[top-i]){
            flag = 0;
            break; 
        }
    }
    if(flag == 1)
        printf("It is a palindrome\n");
    else 
        printf("It is not a palindrome\n");
}