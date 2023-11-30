#include<stdio.h>
void main(){
    int n,j,key, arr[20];
    printf("Enter the size of the array\n");
    scanf("%d",&n);
    printf("Enter the array elements\n");
    for (int i = 0; i < n; i++)
        scanf("%d",&arr[i]);
    for(int i = 1;i<n ; i++){
        j = i-1;
        key = arr[i];
        while (j>=0&&arr[j]>key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
    for (int i = 0; i < n; i++)
        printf("%d\t",arr[i]);
}