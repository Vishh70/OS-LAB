#include <stdio.h>

int main() {
    int n, bt[20], rem[20], wt=0, tat=0, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for(int i=0; i<n; i++) {
        printf("Enter burst time for P%d: ", i+1);
        scanf("%d", &bt[i]);
        rem[i] = bt[i];
    }
    printf("Enter time quantum: ");
    scanf("%d", &tq);

    int t = 0;
    while(1) {
        int done = 1;
        for(int i=0; i<n; i++) {
            if(rem[i] > 0) {
                done = 0;
                if(rem[i] > tq) {
                    t += tq;
                    rem[i] -= tq;
                } else {
                    t += rem[i];
                    wt += t - bt[i];
                    rem[i] = 0;
                }
            }
        }
        if(done) break;
    }
    for(int i=0; i<n; i++)
        tat += bt[i] + (wt/n);
    printf("\nAverage Waiting Time = %.2f", (float)wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)tat/n);
    return 0;
}
