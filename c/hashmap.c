#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define TABLE_SIZE 20

typedef struct {
    char name[20];
    int age;
    bool married;
}Person;

Person *per[TABLE_SIZE];

void init(){
    for(int i=0;i<TABLE_SIZE;i++)   
        per[i] = NULL;
}

void printH(){
    printf("\n\n");
    for (int i = 0; i <TABLE_SIZE; i++){
        char istrue[] = "false";
        if (per[i]==NULL)
            printf("-----null-----\n");
        else {
            per[i]->married==true?strcpy(istrue,"true"):strcpy(istrue,"false");
            printf("Name: %s\tAge: %d\tMarried: \t%s\n",per[i]->name,per[i]->age,istrue);
        }  
    }
    printf("\n\n");
    
}

unsigned int hash(char *str){
    int hashValue = 1;
    for(int i=0;i<strlen(str);i++){
        hashValue += str[i];
        hashValue *= str[i];
    }
    return hashValue%TABLE_SIZE;
}

void insert(Person *p){
    unsigned int hashval = hash(p->name);
    if(per[hashval] == NULL) per[hashval] = p;
    else printf("DUPLICATE INDEX ->  %d\n",hashval);  
}

void main(){
    init();
    Person p1 = {.name = "bob", .age = 24, .married = false };
    Person p2 = {.name = "Mickel", .age = 29, .married = true };
    Person p3 = {.name = "ricky", .age = 43, .married = true };
    Person p4 = {.name = "jord", .age = 43, .married = false };
    Person p5 = {.name = "eren", .age = 43, .married = true };
    insert(&p1);
    insert(&p2);
    insert(&p3);
    insert(&p4);
    insert(&p5);
    printH();
}

