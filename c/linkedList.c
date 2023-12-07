#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct myData{
    int data;
    struct myData *next;
}myData;

void insert(myData *this,int data){
    while(this->next!=NULL)
        this = this->next;  
    this->next = (myData*)malloc(sizeof(myData));
    this->next->data = data;
    this->next->next = NULL; 
}
void display(myData *this){
    while(true){
        printf("the data is %d\n",this->data);
        if(this->next == NULL) break;
        this = this->next;
    }
}
void freeList(myData *this){
    while(true){
        myData *next = this->next;
        free(this);
        this = next;
        if(this == NULL) break;
    }
}
int forEach(myData *this){
    int total=0;
    while (true){
        total += this->data;
        if(this->next== NULL) break;
        this = this->next;
    }
    return total; 
}
int getNum(){
    int num;
    scanf("%d",&num);
    return num;
}
void main(){
    myData *head = (myData*)malloc(sizeof(myData));
    head->next = NULL;
    printf("Enter the size of the list");
    int size = getNum();
    printf("Enter the %d number of element to incert :\n",size);
    head->data = getNum();
    for(int i=0; i<size-1;i++)
        insert(head,getNum());
    display(head);
    int total = forEach(head);
    printf("The total is %d " ,total);
    freeList(head);
}