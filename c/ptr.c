#include<stdio.h>
void main(){
    int arr[]={4,4,4,44,4};
    int *arrPtr=arr;
    for(int i = 0;i<5;i++){
        printf("%d\t",*arrPtr);
        arrPtr++;
    }
}