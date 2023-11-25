#include<stdio.h>
void main(){
    int n,k,i,j;
    printf("enter a number\n");
    scanf("%d",&n);
    for (int i = 1; i <= n; i++){
        for(int j=n-i+1;j>0;j--)
            printf("_");
        for (int k = 1; k <i*2 ; k++)
            printf("*");
    printf("\n");        
    }
}