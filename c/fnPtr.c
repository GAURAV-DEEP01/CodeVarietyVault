#include<stdio.h>
void somefn(int num,void (*add)(int)){
    add(num);
}
void thisPara(int num){
        printf("%d",num+num);
}
void main(){
    somefn(5,thisPara);
}