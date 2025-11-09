#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sort(int arr[], int n) {
    int temp;
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d integers:\n", n);
    for(int i=0; i<n; i++)
        scanf("%d", &arr[i]);

    sort(arr, n);
    printf("\n[Parent] Sorted array: ");
    for(int i=0; i<n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    pid_t pid = fork();

    if(pid < 0) {
        printf("Fork failed!\n");
        exit(1);
    }
    else if(pid == 0) {
        // Prepare arguments for exec
        char *args[n+2];
        args[0] = "./reverse";
        for(int i=0; i<n; i++) {
            char *num = malloc(10);
            sprintf(num, "%d", arr[i]);
            args[i+1] = num;
        }
        args[n+1] = NULL;
        execv(args[0], args);
        perror("execv failed");
    }
    else {
        wait(NULL);
        printf("[Parent] Child process completed.\n");
    }
    return 0;
}
