#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

// Function to implement SSTF Disk Scheduling Algorithm
void sstfDiskScheduling(int *requests, int num_requests, int current_position) {
    int total_head_movements = 0;
    int visited[num_requests];
    for(int i = 0; i < num_requests; i++) {
        visited[i] = 0;
    }

    printf("Order of Traversal: %d ", current_position);

    for(int i = 0; i < num_requests; i++) {
        int shortest_distance = INT_MAX;
        int next_request;
        for(int j = 0; j < num_requests; j++) {
            if(!visited[j]) {
                int distance = abs(requests[j] - current_position);
                if(distance < shortest_distance) {
                    shortest_distance = distance;
                    next_request = requests[j];
                }
            }
        }
        visited[next_request] = 1;
        total_head_movements += shortest_distance;
        current_position = next_request;
        printf("-> %d ", current_position);
    }

    printf("\nTotal Head Movements: %d\n", total_head_movements);
}

// Function to implement First Fit Memory Placement Algorithm
void firstFitMemoryPlacement(int *block_sizes, int num_blocks, int *process_sizes, int num_processes) {
    int allocation[num_processes];
    for(int i = 0; i < num_processes; i++) {
        allocation[i] = -1;
    }

    for(int i = 0; i < num_processes; i++) {
        for(int j = 0; j < num_blocks; j++) {
            if(block_sizes[j] >= process_sizes[i]) {
                allocation[i] = j;
                block_sizes[j] -= process_sizes[i];
                break;
            }
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
    // SSTF Disk Scheduling
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int num_requests = sizeof(requests) / sizeof(requests[0]);
    int current_position = 53;

    sstfDiskScheduling(requests, num_requests, current_position);

    // First Fit Memory Placement
    int block_sizes[] = {100, 500, 200, 300, 600};
    int num_blocks = sizeof(block_sizes) / sizeof(block_sizes[0]);
    int process_sizes[] = {212, 417, 112, 426};
    int num_processes = sizeof(process_sizes) / sizeof(process_sizes[0]);

    firstFitMemoryPlacement(block_sizes, num_blocks, process_sizes, num_processes);

    return 0;
}
