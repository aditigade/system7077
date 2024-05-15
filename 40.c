#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnAroundTime;
};

// Function prototypes
void sjf(struct Process *processes, int n);
void srtf(struct Process *processes, int n);
void calculateWaitingTimeSJF(struct Process *processes, int n);
void calculateTurnAroundTimeSJF(struct Process *processes, int n);
void calculateSRTF(struct Process *processes, int n);
void printProcessDetails(struct Process *processes, int n);
void sort(struct Process *processes, int n);
int compareBurstTime(const void *a, const void *b);

int main() {
    struct Process processes[] = {{1, 0, 6, 6, 0, 0}, {2, 1, 8, 8, 0, 0}, {3, 2, 7, 7, 0, 0}, {4, 3, 3, 3, 0, 0}};
    int n = sizeof(processes) / sizeof(processes[0]);

    // Uncomment the following line to run SJF
    // sjf(processes, n);

    // Uncomment the following line to run SRTF
     srtf(processes, n);

    return 0;
}

void sjf(struct Process *processes, int n) {
    sort(processes, n);
    calculateWaitingTimeSJF(processes, n);
    calculateTurnAroundTimeSJF(processes, n);
    printProcessDetails(processes, n);
}

void srtf(struct Process *processes, int n) {
    calculateSRTF(processes, n);
    printProcessDetails(processes, n);
}

int compareBurstTime(const void *a, const void *b) {
    return ((struct Process *)a)->burstTime - ((struct Process *)b)->burstTime;
}

void sort(struct Process *processes, int n) {
    qsort(processes, n, sizeof(struct Process), compareBurstTime);
}

void calculateWaitingTimeSJF(struct Process *processes, int n) {
    processes[0].waitingTime = 0;
    for (int i = 1; i < n; ++i) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

void calculateTurnAroundTimeSJF(struct Process *processes, int n) {
    for (int i = 0; i < n; ++i) {
        processes[i].turnAroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void calculateSRTF(struct Process *processes, int n) {
    int currentTime = 0;
    int completed = 0;
    int minRemainingTime = INT_MAX;
    int shortest = 0;
    int found = 0;

    while (completed != n) {
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < minRemainingTime && processes[i].remainingTime > 0) {
                minRemainingTime = processes[i].remainingTime;
                shortest = i;
                found = 1;
            }
        }

        if (!found) {
            ++currentTime;
            continue;
        }

        --processes[shortest].remainingTime;
        minRemainingTime = processes[shortest].remainingTime;
        if (minRemainingTime == 0) {
            minRemainingTime = INT_MAX;
        }

        if (processes[shortest].remainingTime == 0) {
            ++completed;
            found = 0;
            processes[shortest].waitingTime = currentTime + 1 - processes[shortest].burstTime - processes[shortest].arrivalTime;
            if (processes[shortest].waitingTime < 0) {
                processes[shortest].waitingTime = 0;
            }
        }
        ++currentTime;
    }

    for (int i = 0; i < n; ++i) {
        processes[i].turnAroundTime = processes[i].burstTime + processes[i].waitingTime;
    }
}

void printProcessDetails(struct Process *processes, int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].waitingTime, processes[i].turnAroundTime);
    }
}
