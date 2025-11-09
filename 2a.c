#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n, arr[10], i, j, temp;
    pid_t pid;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for(i=0; i<n; i++)
        scanf("%d", &arr[i]);

    pid = fork();

    if(pid < 0) {
        printf("Fork failed!\n");
        exit(1);
    }
    else if(pid == 0) {
        // Child Process
        printf("\n[Child] Sorting numbers...\n");
        for(i=0; i<n-1; i++) {
            for(j=0; j<n-i-1; j++) {
                if(arr[j] > arr[j+1]) {
                    temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }

        printf("[Child] Sorted array: ");
        for(i=0; i<n; i++)
            printf("%d ", arr[i]);
        printf("\n[Child] PID: %d, PPID: %d\n", getpid(), getppid());
        printf("[Child] Sleeping 5 seconds...\n");
        sleep(5);
        printf("[Child] Exiting...\n");
        exit(0);
    }
    else {
        // Parent Process
        printf("\n[Parent] PID: %d created Child PID: %d\n", getpid(), pid);
        printf("[Parent] Waiting for Child to finish...\n");
        wait(NULL);
        printf("[Parent] Child completed. Parent exiting...\n");
    }

    return 0;
}
