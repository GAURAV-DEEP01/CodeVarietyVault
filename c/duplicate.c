#include<stdio.h>
void main(){
    int arr[20],n,count=0;
    printf("Input the number of elements to be stored in the array\t");
    scanf("%d",&n);
    printf("Input %d elements in the array :\n",n);
    for (int i = 0; i <n; i++){
        printf("element - %d : ",i);    
        scanf("%d",&arr[i]);
    }
    for (int i = 0; i < n; i++){
        int duplicate = 0;
        for (int j = i; j < n; j++)
            if(arr[i]==arr[j]&&i!=j){ 
                duplicate=1;
                break;            
            }
        if (duplicate) count++;
    }
    printf("Total count of duplicate elements is %d",count);
}