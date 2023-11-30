#include<stdio.h>
void main(){
    int **ptp;
    int num = 6;
    int *p;
    p=&num;
    ptp= &p;
    printf("num is \t%d\n",num);
    printf("p\t%x\n",p);
    printf("*p \t%ld\n",*p);
    printf("&p \t%x\n",&p);
    printf("ptp \t%x\n",ptp);
    printf("**ptp \t%d\n",**ptp);
    printf("*ptp \t%x\n",*ptp);
    printf("&ptp \t%x\n",&ptp);
}