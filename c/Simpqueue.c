#include<stdio.h>
#define MAX_SIZE 10
int queue[MAX_SIZE];
int front = -1,rear =-1;

void enQueue(int);
int deQueue();
int isEmpty();
int isFull();

void main(){
    int end = 0,choice,ele;

    while(1){
        printf("\nEnter the operation \n1. Enqueue \n2. Dequeue\n3. Exit\n");
        scanf("%d",&choice);
        switch (choice){
            case 1:
                printf("Enter the element to be inserted\n");
                scanf("%d",&ele);
                enQueue(ele);
                break;
            case 2:
                ele= deQueue();
                if(ele!= -1)
                    printf("Dequeued element is %d\n",ele);
                break;
            case 3:
                return;
            default: printf("\nWrong input");
                break;
        }
    }   
}
void enQueue(int ele){
     if(isFull())
        return;
    queue[++rear] = ele;
    if (front ==-1) front++;
}
int deQueue(){
   if(isEmpty())  return -1;
    return queue[front++];
}
int isEmpty(){
    if(rear-front == -1||front==-1){
        printf("\n~~~~~~~~~Queue is empty~~~~~~~~");
        return 1;
    }
    return 0;
}
int isFull(){
    if(rear == MAX_SIZE - 1){
        printf("\n~~~~~~~~~Queue is full~~~~~~~~~");
        return 1;
    }
    return 0;
}