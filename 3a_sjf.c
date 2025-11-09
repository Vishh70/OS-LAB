#include <stdio.h>

int main() {
    int n, bt[20], at[20], rt[20], remain = 0, time = 0, smallest;
    float avgwt = 0, avgtt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i=0;i<n;i++) {
        printf("Enter arrival and burst time for P%d: ", i+1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    rt[99] = 9999;
    printf("\nProcess\tTurnaround\tWaiting\n");
    for(time=0; remain!=n; time++) {
        smallest = 99;
        for(int i=0; i<n; i++) {
            if(at[i]<=time && rt[i]>0 && rt[i]<rt[smallest])
                smallest = i;
        }
        rt[smallest]--;
        if(rt[smallest]==0) {
            remain++;
            int finish = time+1;
            printf("P%d\t%d\t\t%d\n", smallest+1, finish-at[smallest], finish-bt[smallest]-at[smallest]);
            avgwt += finish - bt[smallest] - at[smallest];
            avgtt += finish - at[smallest];
        }
    }
    printf("\nAverage Waiting Time = %.2f", avgwt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avgtt/n);
    return 0;
}
