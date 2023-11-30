#include<stdio.h>
void main(){
    int arr[7] = {7,6,5,4,3,2,1};
    int n = 7,min,temp;
    for(int i = 0;i<n;i++){
        min = i;
        for (int j = i+1; j <n ; j++)
            if(arr[min]>arr[j])  min = j;
        if (min!=i){
            temp= arr[i];
            arr[i]=arr[min];
            arr[min]= temp;
        }
    }
    for (int i = 0; i < n; i++)
        printf("%d\t",arr[i]);    
}