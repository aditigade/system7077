#include <stdio.h>

// Process struct definition
struct Process {
    int pid; // Process ID
    int arrival_time; // Arrival time
    int burst_time; // Burst time
    int waiting_time; // Waiting time
    int turnaround_time; // Turnaround time
    int priority; // Priority of the process
};

// Function to calculate waiting time and turnaround time for each process
void calculate_times(struct Process processes[], int n) {
    // Sort processes based on priority
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Calculate waiting time and turnaround time for each process
    processes[0].waiting_time = 0; // First process has 0 waiting time

    for (int i = 1; i < n; i++) {
        int waiting_time = 0;

        for (int j = 0; j < i; j++) {
            waiting_time += processes[j].burst_time;
        }

        processes[i].waiting_time = waiting_time - processes[i].arrival_time;

        if (processes[i].waiting_time < 0) {
            processes[i].waiting_time = 0;
        }

        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

// Function to print process details
void print_processes(struct Process processes[], int n) {
    printf("PID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("\n");
}

// Main function
int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Process array initialization
    struct Process processes[n];

    // Inputting process details
    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time of process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter the priority of process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].pid = i + 1;
    }

    // Calculation of waiting time and turnaround time
    calculate_times(processes, n);

    // Printing process details
    print_processes(processes, n);

    return 0;
}
