// Write a program to implement following CPU scheduling algorithms:
// 1)	SJF
// 2)	SRTF

#include <stdio.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int pid;  // Process ID
    int at;   // Arrival Time
    int bt;   // Burst Time
    int ct;   // Completion Time
    int tat;  // Turnaround Time
    int wt;   // Waiting Time
    int rt;   // Remaining Time (for SRTF)
} Process;

void sjf(Process p[], int n) {
    int completed = 0, currentTime = 0;
    bool visited[MAX] = { false };

    while (completed < n) {
        int idx = -1;
        int min_bt = 1e9;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i] && p[i].at <= currentTime && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }

        if (idx != -1) {
            currentTime += p[idx].bt;
            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            visited[idx] = true;
            completed++;
        } else {
            currentTime++;
        }
    }
}

void srtf(Process p[], int n) {
    int completed = 0, currentTime = 0, prev = -1;
    int min_rt = 1e9;
    bool visited[MAX] = { false };

    while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && !visited[i] && p[i].rt < min_rt) {
                min_rt = p[i].rt;
                idx = i;
            }
        }

        if (idx != -1) {
            if (prev != idx) {
                min_rt = p[idx].rt;
                prev = idx;
            }
            currentTime++;
            p[idx].rt--;

            if (p[idx].rt == 0) {
                p[idx].ct = currentTime;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                visited[idx] = true;
                completed++;
                min_rt = 1e9;
            }
        } else {
            currentTime++;
        }
    }
}

void printResults(Process p[], int n) {
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

int main() {
    int n;
    Process p[MAX];

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input arrival times and burst times
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;  // Initialize remaining time for SRTF
    }

    printf("\nSJF Scheduling:\n");
    sjf(p, n);
    printResults(p, n);

    // Reinitialize remaining times for SRTF
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
    }

    printf("\nSRTF Scheduling:\n");
    srtf(p, n);
    printResults(p, n);

    return 0;
}


/*
Input Example

Enter the number of processes: 5
Enter arrival time and burst time for each process:
Process 1: 0 8
Process 2: 1 4
Process 3: 2 9
Process 4: 3 5
Process 5: 4 2
*/