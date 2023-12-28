#include<stdio.h>
#include<stdlib.h>
void main(){
    printf("Enter the number elements to store\n");
    int n;
    scanf("%d",&n);
    int *arr = (int*)malloc(n*sizeof(int));
    if(arr == NULL){
        printf("Unable to allocate memory\n");
        exit(0);
    }
    printf("Enter the individual elements\n");
    for (int i = 0; i < n; i++)
        scanf("%d",&arr[i]);
    printf("The array elements are \n");
    for (int i = 0; i < n; i++)
        printf("%d\n",arr[i]);
    printf("Enter the resize value \n");
    int cont = n; 
    scanf("%d",&n);
    printf("Memory location before realloc : %p\n",arr);
    arr = (int*)realloc(arr,n*sizeof(int));
    printf("Memory location after realloc : %p\n",arr);
    if(arr == NULL){
        printf("Unable to resize the array\n");
        exit(0);
    }
    printf("Add The extra elements \n"); 
    for (int i = cont; i <n; i++)
        scanf("%d",&arr[i]);
    printf("the final array\n");
    for (int i = 0; i < n; i++)
        printf("%d\n",arr[i]);
    free(arr);
}