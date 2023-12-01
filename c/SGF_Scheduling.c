#include<stdio.h>
#include<stdlib.h>

typedef struct {
    char *name;
    int st,bt,ft,tat;
}Process;

void main(){
    int n;
    Process p[10];

    printf("Enter number of processes\n");
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        char *name = (char*)malloc(sizeof(char)*20);
        printf("Enter process name : ");
        scanf("%s",name);
        p[i].name = name;
        printf("Burst Time of process %s : ",p[i].name);
        scanf("%d",&p[i].bt);
    }

    for (int i = 0; i < n; i++){
        int min = i;
        for(int j = i+1;j<n;j++ )
            if(p[i].bt>p[j].bt)  min = j;
        if(min!=i){
            int temp;
            temp = p[min].bt;
            p[min].bt = p[i].bt;
            p[i].bt = temp;
            char *name = p[min].name;
            p[min].name = p[i].name;
            p[i].name = name;
        }
    }
    for(int i = 0;i<n;i++){
        p[i].st = i==0?0:p[i-1].ft;
        p[i].ft = p[i].st + p[i].bt;
        p[i].tat = p[i].ft - p[i].st;
    }
    printf("\nPROCESS NAME\tBURST\tSTART\tFINISH\tTURN AROUND\n");
    for(int i = 0;i<n;i++)
        printf("%s\t\t%d\t%d\t%d\t%d\n",p[i].name,p[i].bt,p[i].st,p[i].ft,p[i].tat);
    printf("\n");
    for(int i = 0; i<n;i++){
        free(p[i].name);
    }
}