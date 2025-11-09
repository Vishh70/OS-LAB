#include <stdio.h>

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; ++i)
        if (time[i] < min) { min = time[i]; pos = i; }
    return pos;
}

int main() {
    int n, f;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[30];
    printf("Enter reference string:\n");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    printf("Enter number of frames (>=3): ");
    scanf("%d", &f);
    if (f < 3) { printf("Frame size must be ≥3\n"); return 0; }

    int frames[10], counter[10], time[10];
    int flag1, flag2, flag3, faults, i, j, pos, k;

    /* ---------- FCFS ---------- */
    for (i = 0; i < f; i++) frames[i] = -1;
    pos = faults = 0;
    printf("\n---- FCFS Page Replacement ----\n");
    for (i = 0; i < n; i++) {
        flag1 = flag2 = 0;
        for (j = 0; j < f; j++)
            if (frames[j] == pages[i]) { flag1 = flag2 = 1; break; }

        if (flag1 == 0) {
            frames[pos] = pages[i];
            pos = (pos + 1) % f;
            faults++;
        }

        printf("Frames: ");
        for (j = 0; j < f; j++)
            if (frames[j] != -1) printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total Page Faults (FCFS) = %d\n", faults);

    /* ---------- LRU ---------- */
    for (i = 0; i < f; i++) frames[i] = -1;
    faults = 0; k = 0;
    printf("\n---- LRU Page Replacement ----\n");
    for (i = 0; i < n; i++) {
        flag1 = flag2 = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                k++;
                counter[j] = k;
                flag1 = flag2 = 1;
                break;
            }
        }
        if (flag1 == 0) {
            if (i < f) frames[i] = pages[i];
            else {
                pos = findLRU(counter, f);
                frames[pos] = pages[i];
            }
            k++;
            counter[i % f] = k;
            faults++;
        }

        printf("Frames: ");
        for (j = 0; j < f; j++)
            if (frames[j] != -1) printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total Page Faults (LRU) = %d\n", faults);

    /* ---------- Optimal ---------- */
    for (i = 0; i < f; i++) frames[i] = -1;
    faults = 0;
    printf("\n---- Optimal Page Replacement ----\n");
    for (i = 0; i < n; i++) {
        flag1 = flag2 = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) { flag1 = flag2 = 1; break; }
        }
        if (flag1 == 0) {
            if (i < f) frames[i] = pages[i];
            else {
                flag3 = 0;
                int farthest = i + 1, idx = -1;
                for (j = 0; j < f; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k]) {
                            if (k > farthest) { farthest = k; idx = j; }
                            break;
                        }
                    }
                    if (k == n) { idx = j; break; } // page not used again
                }
                if (idx == -1) idx = 0;
                frames[idx] = pages[i];
            }
            faults++;
        }

        printf("Frames: ");
        for (j = 0; j < f; j++)
            if (frames[j] != -1) printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total Page Faults (Optimal) = %d\n", faults);

    return 0;
}
