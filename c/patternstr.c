#include<stdio.h>
char str[20],pat[20],rep[20],ans[20];
int c,m,i,j,k,flag = 0;
void stringMatch(){
    while (str[c]!='\0'){
        if(str[m]==pat[i]){
            i++;m++;
            if(pat[i]=='\0'){
                flag = 1;
                for(k=0;rep[k]!='\0';k++,j++)
                    ans[j] = rep[k];
                i=0; c=m;
            }
        }
        else{
            ans[j] = str[c];
            j++; c++;
            m=c;
            i=0;
        }
    }
    ans[j] = '\0';
}
void main(){
    printf("enter the string\n");
    gets(str);
    printf("enter the pat str\n");
    gets(pat);
    printf("enter the rep str\n");
    gets(rep);
    stringMatch();
    if(flag==0)
        printf("no pat found\n");
    else
        printf("%s",ans);
}