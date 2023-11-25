#include<stdio.h>
#include<string.h>

#define TABLE_SIZE 20
typedef struct {
  char name[20];
  unsigned int age;
}Person;

Person *hash_table[TABLE_SIZE];

void init(){
    for (int i = 0; i <TABLE_SIZE; i++)
        hash_table[i] = NULL;
}
void printH(){
    for (int i = 0; i <TABLE_SIZE; i++)
        if(hash_table[i]==NULL)
            printf("null\n");
        else 
            printf("name :",hash_table[i]->name);
    
}

int hash_function(char *name){
    int hashValue=0;
    for (int i = 0; i < strlen(name); i++)
        hashValue +=name[i];
    return hashValue%10; 
}
void incert(Person *p){
    int idx= hash_function(p->name);
    hash_table[idx] =p;
}

void main(){
    init();
    Person per = {.name = "bob" ,.age= 20};
    incert(&per);
    printH();
    return;
}