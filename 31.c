#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>

// Function to implement FCFS Disk Scheduling Algorithm
void fcfsDiskScheduling(int *requests, int num_requests, int current_position) {
    int total_head_movements = 0;
    printf("Order of Requests: ");
    for(int i = 0; i < num_requests; i++) {
        printf("%d ", requests[i]);
        total_head_movements += abs(requests[i] - current_position);
        current_position = requests[i];
    }
    printf("\nTotal Head Movements: %d\n", total_head_movements);
}

// Function to implement Best Fit Memory Placement Algorithm
void bestFitMemoryPlacement(int *block_sizes, int num_blocks, int *process_sizes, int num_processes) {
    int allocation[num_processes];
    for(int i = 0; i < num_processes; i++) {
        allocation[i] = -1;
    }

    for(int i = 0; i < num_processes; i++) {
        int best_fit_index = -1;
        for(int j = 0; j < num_blocks; j++) {
            if(block_sizes[j] >= process_sizes[i]) {
                if(best_fit_index == -1 || block_sizes[j] < block_sizes[best_fit_index]) {
                    best_fit_index = j;
                }
            }
        }
        if(best_fit_index != -1) {
            allocation[i] = best_fit_index;
            block_sizes[best_fit_index] -= process_sizes[i];
        }
    }

    printf("Process\tBlock\n");
    for(int i = 0; i < num_processes; i++) {
        printf("P%d\t", i);
        if(allocation[i] != -1) {
            printf("%d\n", allocation[i]);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    // FCFS Disk Scheduling
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int num_requests = sizeof(requests) / sizeof(requests[0]);
    int current_position = 53;

    fcfsDiskScheduling(requests, num_requests, current_position);

    for (int i = 1; i < num_requests; ++i) {
        printf(" + (%d-%d)", requests[i], requests[i - 1]);
    }

    printf("\n")

    // Best Fit Memory Placement
    int block_sizes[] = {100, 500, 200, 300, 600};
    int num_blocks = sizeof(block_sizes) / sizeof(block_sizes[0]);
    int process_sizes[] = {212, 417, 112, 426};
    int num_processes = sizeof(process_sizes) / sizeof(process_sizes[0]);

    bestFitMemoryPlacement(block_sizes, num_blocks, process_sizes, num_processes);

    return 0;
}




