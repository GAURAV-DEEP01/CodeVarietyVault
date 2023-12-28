#include <stdio.h>
#include <string.h>
int F(char symbol){
    switch (symbol){
        case '+':
        case '-': return 2;
        case '*':
        case '/': return 4;
        case '^': return 5;
        case '(': return 0;
        case '#': return -1;
        default : return 8;
    }
}
int G(char symbol){
    switch (symbol){
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 3;
        case '^': return 6;
        case '(': return 9;
        case ')': return 0;
        default : return 7;
    }
}

void infix_postfix(char infix[], char postfix[]){
    int top = 0, j = 0, i;
    char stk[30], symbol;
    stk[top] = '#';
    for(i = 0; i < strlen(infix); i++){
        symbol = infix[i];
        while (F(stk[top]) > G(symbol))  
            postfix[j++] = stk[top--];
        if (F(stk[top]) != G(symbol)) 
            stk[++top] = symbol;
        else  top--;
    }     

    while (stk[top] != '#') postfix[j++] = stk[top--];
    postfix[j] = '\0';
}


void main(){
    char infix[20], postfix[20];

    printf("\nEnter a valid infix expression\n");
    gets(infix);

    infix_postfix(infix, postfix);

    printf("\nThe infix expression is:\n");
    printf("%s", infix);
    printf("\nThe postfix expression is:\n");
    printf("%s", postfix);
}

