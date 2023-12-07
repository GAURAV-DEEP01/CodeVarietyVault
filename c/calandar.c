#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
    char *name;
    int date;
    char *discription;
}Day;

Day* create(){
    Day* calendar = (Day*)malloc(sizeof(Day)*7);
    if(calendar == NULL){
        printf("Error allocating memory for calendar\n");
        exit(0);
    }
    return calendar;
}
void read(Day *calendar){
    for (int i = 0; i < 7; i++){
        printf("Enter the name of day %d :",i+1);
        char *name = (char*)malloc(sizeof(char)*100);
        if(name == NULL){
            printf("Error allocating memory for day name\n");
            exit(1);
        }
        scanf("%s",name);
        calendar[i].name = name;
        printf("Enter the date of day %d :",i+1);
        scanf("%d",&calendar[i].date);
        printf("Enter the discription of the activity for day %d :",i+1);
        char *discription = (char*)malloc(sizeof(char)*100);
        if(discription == NULL){
            printf("Error allocating memory for activity description\n");
            exit(1);
        }
        scanf("%s",discription);
        calendar[i].discription= discription;
    }
}
void display(Day *calendar){
    printf("\nWeek Activity Details Report\n");
    printf("------------------------------\n");
    for (int i = 0; i <7 ; i++)
        printf("%s%d:%s\n",calendar[i].name,calendar[i].date,calendar[i].discription);
}
void main(){
    Day *calendar = create();
    read(calendar);
    display(calendar);
    for (int i = 0; i < 7; i++){
        free(calendar[i].name);
        free(calendar[i].discription);
    }
    free(calendar);    
}