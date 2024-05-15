#include <stdio.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

// Function to check for deadlock
void detectDeadlock(int processes[], int available[], int allocation[][R], int request[][R]) {
    int finish[P] = {0};
    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    int done;
    do {
        done = 1;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int canProceed = 1;
                for (int j = 0; j < R; j++) {
                    if (request[p][j] > work[j]) {
                        canProceed = 0;
                        break;
                    }
                }
                if (canProceed) {
                    for (int k = 0; k < R; k++) {
                        work[k] += allocation[p][k];
                    }
                    finish[p] = 1;
                    done = 0;
                }
            }
        }
    } while (!done);

    int deadlock = 0;
    printf("Processes in deadlock: ");
    for (int i = 0; i < P; i++) {
        if (!finish[i]) {
            printf("P%d ", i);
            deadlock = 1;
        }
    }
    if (!deadlock) {
        printf("None");
    }
    printf("\n");
}

int main() {
    int processes[P] = {0, 1, 2, 3, 4};

    // Available instances of resources
    int available[R] = {0, 0, 0};

    // Allocation Matrix
    int allocation[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 3},
        {2, 1, 1},
        {0, 0, 2}
    };

    // Request Matrix
    int request[P][R] = {
        {0, 0, 0},
        {2, 0, 2},
        {0, 0, 0},
        {1, 0, 0},
        {0, 0, 2}
    };

    // Check for deadlock
    detectDeadlock(processes, available, allocation, request);

    return 0;
}
