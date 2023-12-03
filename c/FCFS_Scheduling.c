#include<stdio.h>
#include<stdlib.h>   
void main(){
    int n,at[20],bt[20],wt[20],tt[20],ft[20],st[20],totWt = 0,totTat = 0;
    int idleTime = 0;
    float avgWt,avgTat;
    printf("Enter the number of processes\n");
    scanf("%d",&n);
    printf("Enter await time and burst time of %d processes\n",n);
    for (int i = 0; i < n; i++){
        printf("Await time of P%d : ",i+1);
        scanf("%d",&at[i]);
        printf("Burst Time of P%d : ",i+1);
        scanf("%d",&bt[i]);   
    } 
    for (int i = 0; i < n; i++){
        int min = i;
        for(int j= i+1;j<n;j++){
            if(at[min]>at[j]) min = j;
        }
        if(min!=i){
            int temp = at[min];
            at[min] = at[i];
            at[i] = temp;
            temp = bt[min];
            bt[min] = bt[i];
            bt[i] = temp;  
        }
    }
       
    for (int i = 0; i <n; i++){
        if(i==0){
            st[i] = at[i];
            wt[i] = st[i];
        }
        else
            if(ft[i-1]-at[i]<0){
                st[i] = at[i];
                wt[i] = 0;
                idleTime +=abs(ft[i-1]-at[i]);
            } else{
                st[i] = ft[i-1];
                wt[i] =st[i] - at[i];
            }
        ft[i] = st[i] + bt[i];
        tt[i] = ft[i] - at[i];      
    }
    printf("\nProcess\tAwait\tBurst\tStart\tFinish\tTurn around\tWait\n");
    for (int i = 0; i < n; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t\t%d\n",i+1,at[i],bt[i],st[i],ft[i],tt[i],wt[i]);
        totTat+=tt[i];
        totWt +=wt[i];
    }
    avgTat = (float)totTat/n;
    avgWt = (float)totWt/n;
    printf("Average wait time is : %.3f\n",avgWt);
    printf("Average turn around time is : %.3f\n",avgTat);   
    printf("Total Idle time is : %d\n\n",idleTime);  
}