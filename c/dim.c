#include<stdio.h>
void main(){
    int n;
    printf("Enter the number n\n");
    scanf("%d",&n);
    for(int i=1;i<n*2;i++){
        for(int j=n-i;j>0;j--)
            printf(" ");
        if(i<=n){ 
            printf("*");
            for (int j=1;j < i*2-2; j++)
                printf(" ");
            if(i!=1) printf("*");
        }            
        if (i>n){
            for(int j=1;j<=i-n;j++)
                printf(" ");
            printf("*");
            for(int j=(n-(i-n))*2-3;j>0;j--){
                printf(" ");
            }
            if(i!=n*2-1)printf("*");
        }
        printf("\n");
    }
}