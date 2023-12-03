#include<stdio.h>
#include<stdlib.h>
#define TABLE_SIZE 20

typedef struct {
    int rollno;
    char *name;
}Stud;

int studCount = 0;
void insertStud(Stud *studPtr[],Stud *s){
    studPtr[studCount] = s;
    studCount++; 
}
void printStud(Stud *s[]){
    for(int i = 0;i<studCount;i++)
        printf("\nRollno : %d\nName : %s\n",s[i]->rollno,s[i]->name);
}
void getStud(Stud *studPtr[]){
    char again;
    do {
        Stud *s = malloc(sizeof(Stud));
        s->name = malloc(sizeof(char)*20); 
        printf("Enter name of a student\n");
        scanf("%s",s->name);
        printf("Enter rollno of the student\n");
        scanf("%d",&(s->rollno));
        insertStud(studPtr,s);
        printf("Enter 'y' if you want to continue or 'n' if you want to exit (y/n) :");
        scanf(" %c",&again);
    }while(again=='y');
}
void main(){
    Stud *studs[TABLE_SIZE];
    char name[] = "varun"; 
    Stud s = {
        15,
        name
    };
    insertStud(studs,&s);
    printf("Default test element\n");
    printStud(studs);
    printf("\nUser input data\n");
    getStud(studs);
    printStud(studs);
    for (int i = 0; i < studCount; i++){
        free(studs[i]->name);
        free(studs[i]);
    }
}