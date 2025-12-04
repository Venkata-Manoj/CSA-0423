#include <stdio.h>
#include <limits.h>

int main() {
    int n, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int at[n], bt[n], ct[n], tat[n], wt[n], completed[n];
    for(i=0;i<n;i++){
        printf("Enter arrival time for P%d: ", i+1);
        scanf("%d",&at[i]);
        printf("Enter burst time for P%d: ", i+1);
        scanf("%d",&bt[i]);
        completed[i]=0;
        ct[i]=0;
    }
    int completed_count=0, time=0;
    while(completed_count < n){
        int idx = -1;
        int min_bt = INT_MAX;
        for(i=0;i<n;i++){
            if(at[i] <= time && !completed[i]){
                if(bt[i] < min_bt){
                    min_bt = bt[i];
                    idx = i;
                } else if(bt[i] == min_bt){
                    if(at[i] < at[idx]) idx = i;
                    else if(at[i] == at[idx] && i < idx) idx = i;
                }
            }
        }
        if(idx == -1){
            time++;
        } else {
            time += bt[idx];
            ct[idx] = time;
            completed[idx] = 1;
            completed_count++;
        }
    }
    float avg_tat=0, avg_wt=0;
    for(i=0;i<n;i++){
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_tat += tat[i];
        avg_wt += wt[i];
    }
    avg_tat /= n;
    avg_wt /= n;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
    printf("Average Waiting Time = %.2f\n", avg_wt);
    return 0;
}

