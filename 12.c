#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct {
    int at; // Arrival Time
    int bt; // Burst Time
    int bt_remaining; // Remaining Burst Time
    int ct; // Completion Time
    int tat; // Turn Around Time
    int wt; // Waiting Time
    int is_completed;
} Process;

void srtf(Process processes[], int n) {
    int time = 0, completed = 0, shortest = -1;
    int min_bt_remaining = __INT_MAX__;

    for (int i = 0; i < n; i++) {
        processes[i].bt_remaining = processes[i].bt;
    }

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && processes[i].is_completed == 0 && processes[i].bt_remaining < min_bt_remaining) {
                min_bt_remaining = processes[i].bt_remaining;
                shortest = i;
            }
        }
        if (shortest == -1) {
            time++;
        } else {
            processes[shortest].bt_remaining--;
            time++;
            if (processes[shortest].bt_remaining == 0) {
                processes[shortest].ct = time;
                processes[shortest].tat = processes[shortest].ct - processes[shortest].at;
                processes[shortest].wt = processes[shortest].tat - processes[shortest].bt;
                processes[shortest].is_completed = 1;
                completed++;
                min_bt_remaining = __INT_MAX__;
            }
        }
    }
}

void fcfs(Process processes[], int n) {
    int time = 0, completed = 0;
    while (completed != n) {
        int earliest = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && processes[i].is_completed == 0) {
                if (earliest == -1 || processes[i].at < processes[earliest].at) {
                    earliest = i;
                }
            }
        }
        if (earliest == -1) {
            time++;
        } else {
            time += processes[earliest].bt;
            processes[earliest].ct = time;
            processes[earliest].tat = processes[earliest].ct - processes[earliest].at;
            processes[earliest].wt = processes[earliest].tat - processes[earliest].bt;
            processes[earliest].is_completed = 1;
            completed++;
        }
    }
}

void print_table(Process processes[], int n) {
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, processes[i].at, processes[i].bt,
               processes[i].ct, processes[i].tat, processes[i].wt);
    }
}

void reset_processes(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].bt_remaining = processes[i].bt;
        processes[i].ct = 0;
        processes[i].tat = 0;
        processes[i].wt = 0;
        processes[i].is_completed = 0;
    }
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
        processes[i].is_completed = 0;
    }

    printf("\nShortest Remaining Time First (SRTF) Scheduling\n");
    srtf(processes, n);
    print_table(processes, n);

    reset_processes(processes, n);

    printf("\nFirst-Come-First-Serve (FCFS) Scheduling\n");
    fcfs(processes, n);
    print_table(processes, n);

    return 0;
}


/*
Input Example

Number of processes: 4

Process 1: AT=0, BT=6
Process 2: AT=2, BT=8
Process 3: AT=4, BT=7
Process 4: AT=6, BT=3
*/