#include<stdio.h>
typedef struct {
    char name[10];
    int age;
} Student;

void main(){
    Student *s[10];
    for(int i=0;i<10;i++)
        s[i] = NULL;
    for(int i=0;i<10;i++)
        printf("%d\n",s[i]);
}