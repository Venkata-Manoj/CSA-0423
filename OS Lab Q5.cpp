#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], pr[n], p[n], wt[n], tat[n];
    int i, j, temp;

    for(i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("Enter Burst Time for P%d: ", i+1);
        scanf("%d", &bt[i]);
        printf("Enter Priority for P%d: ", i+1);
        scanf("%d", &pr[i]);
    }

    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(pr[j] < pr[i]) {
                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = p[i];  p[i] = p[j];   p[j] = temp;
            }
        }
    }

    wt[0] = 0;
    for(i = 1; i < n; i++)
        wt[i] = wt[i-1] + bt[i-1];

    for(i = 0; i < n; i++)
        tat[i] = wt[i] + bt[i];

    printf("\nProcess\tBT\tPR\tWT\tTAT\n");
    for(i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i], bt[i], pr[i], wt[i], tat[i]);

    return 0;
}

