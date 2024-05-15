#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct {
    int at; // Arrival Time
    int bt; // Burst Time
    int priority;
    int ct; // Completion Time
    int tat; // Turn Around Time
    int wt; // Waiting Time
    int is_completed;
} Process;

void priority_nonpreemptive(Process processes[], int n) {
    int time = 0, completed = 0;
    while (completed != n) {
        int min_priority = __INT_MAX__;
        int next_process = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && processes[i].is_completed == 0 && processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                next_process = i;
            }
        }
        if (next_process == -1) {
            time++;
        } else {
            time += processes[next_process].bt;
            processes[next_process].ct = time;
            processes[next_process].tat = processes[next_process].ct - processes[next_process].at;
            processes[next_process].wt = processes[next_process].tat - processes[next_process].bt;
            processes[next_process].is_completed = 1;
            completed++;
        }
    }
}

void sjf(Process processes[], int n) {
    int time = 0, completed = 0;
    while (completed != n) {
        int shortest_bt = __INT_MAX__;
        int next_process = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && processes[i].is_completed == 0 && processes[i].bt < shortest_bt) {
                shortest_bt = processes[i].bt;
                next_process = i;
            }
        }
        if (next_process == -1) {
            time++;
        } else {
            time += processes[next_process].bt;
            processes[next_process].ct = time;
            processes[next_process].tat = processes[next_process].ct - processes[next_process].at;
            processes[next_process].wt = processes[next_process].tat - processes[next_process].bt;
            processes[next_process].is_completed = 1;
            completed++;
        }
    }
}

void print_table(Process processes[], int n) {
    printf("P\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, processes[i].at, processes[i].bt, processes[i].priority,
               processes[i].ct, processes[i].tat, processes[i].wt);
    }
}

void reset_processes(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
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
        printf("Enter arrival time, burst time and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].at, &processes[i].bt, &processes[i].priority);
        processes[i].is_completed = 0;
    }

    printf("\nPriority Non-Preemptive Scheduling\n");
    priority_nonpreemptive(processes, n);
    print_table(processes, n);

    reset_processes(processes, n);

    printf("\nShortest Job First (SJF) Scheduling\n");
    sjf(processes, n);
    print_table(processes, n);

    return 0;
}


/*
Input Example

Number of processes: 4

Process 1: AT=0, BT=5, Priority=2
Process 2: AT=1, BT=3, Priority=1
Process 3: AT=2, BT=8, Priority=4
Process 4: AT=3, BT=6, Priority=3
*/