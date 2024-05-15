#include <stdio.h>
#include <stdbool.h>

// Process struct definition
struct Process {
    int pid; // Process ID
    int arrival_time; // Arrival time
    int burst_time; // Burst time
    int remaining_time; // Remaining time
    int waiting_time; // Waiting time
    int turnaround_time; // Turnaround time
    int priority; // Priority of the process
    bool is_completed; // Indicates whether process has completed or not
};

// Function to find the process with the highest priority in the queue
int find_highest_priority(struct Process processes[], int n, int current_time) {
    int highest_priority_index = -1;
    int highest_priority = -1;
    
    for (int i = 0; i < n; i++) {
        if (processes[i].priority > highest_priority && processes[i].is_completed == false && processes[i].arrival_time <= current_time) {
            highest_priority_index = i;
            highest_priority = processes[i].priority;
        }
    }
    
    return highest_priority_index;
}

// Function to calculate waiting time and turnaround time for each process
void calculate_times(struct Process processes[], int n) {
    int current_time = 0;
    int completed_processes = 0;
    
    while (completed_processes != n) {
        int highest_priority_index = find_highest_priority(processes, n, current_time);
        
        if (highest_priority_index == -1) {
            current_time++;
            continue;
        }
        
        processes[highest_priority_index].remaining_time--;
        
        if (processes[highest_priority_index].remaining_time == 0) {
            processes[highest_priority_index].waiting_time = current_time - processes[highest_priority_index].arrival_time - processes[highest_priority_index].burst_time;
            processes[highest_priority_index].turnaround_time = current_time - processes[highest_priority_index].arrival_time;
            processes[highest_priority_index].is_completed = true;
            completed_processes++;
        }
        
        current_time++;
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
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].is_completed = false;
    }
    
    // Calcul
// Calculation of waiting time and turnaround time
calculate_times(processes, n);

// Printing the details of each process
print_processes(processes, n);

return 0;
}
