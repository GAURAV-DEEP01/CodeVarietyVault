#include<stdio.h>
void printArr(int arr[2][4]){
    for(int i=0;i<2;i++){
        for(int j=0;j<4;j++){
            printf("%d\t",arr[i][j]);
        }
    }
}
void main(){
    int arr[2][4] = {{1,2,3,4},
                     {2,3,3,4}};
    printArr(arr);
}