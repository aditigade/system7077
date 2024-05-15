#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// Function to implement SCAN Disk Scheduling Algorithm
void scanDiskScheduling(int *requests, int num_requests, int current_position, char direction) {
    int total_head_movements = 0;
    int min_cylinder = 0;
    int max_cylinder = 199;
    int visited[num_requests];
    for(int i = 0; i < num_requests; i++) {
        visited[i] = 0;
    }

    printf("Order of Traversal: %d ", current_position);

    // Sort requests based on distance from current position
    for(int i = 0; i < num_requests - 1; i++) {
        for(int j = 0; j < num_requests - i - 1; j++) {
            if(requests[j] > requests[j+1]) {
                int temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1] = temp;
            }
        }
    }

    // Determine the index of the request closest to the current position
    int closest_index = -1;
    for(int i = 0; i < num_requests; i++) {
        if(requests[i] >= current_position) {
            closest_index = i;
            break;
        }
    }

    // If no request is ahead of current position, move towards the maximum cylinder
    if(closest_index == -1) {
        closest_index = num_requests - 1;
    }

    // Traverse in the specified direction (left or right)
    int i;
    if(direction == 'l') {
        for(i = closest_index; i >= 0; i--) {
            printf("-> %d ", requests[i]);
            total_head_movements += abs(requests[i] - current_position);
            current_position = requests[i];
        }
        total_head_movements += abs(min_cylinder - current_position);
        printf("-> %d ", min_cylinder);

        for(i = closest_index + 1; i < num_requests; i++) {
            printf("-> %d ", requests[i]);
            total_head_movements += abs(requests[i] - min_cylinder);
            current_position = requests[i];
        }
    } else if(direction == 'r') {
        for(i = closest_index; i < num_requests; i++) {
            printf("-> %d ", requests[i]);
            total_head_movements += abs(requests[i] - current_position);
            current_position = requests[i];
        }
        total_head_movements += abs(max_cylinder - current_position);
        printf("-> %d ", max_cylinder);

        for(i = closest_index - 1; i >= 0; i--) {
            printf("-> %d ", requests[i]);
            total_head_movements += abs(requests[i] - max_cylinder);
            current_position = requests[i];
        }
    }

    printf("\nTotal Head Movements: %d\n", total_head_movements);
}

// Function to implement Worst Fit Memory Placement Algorithm
void worstFitMemoryPlacement(int *block_sizes, int num_blocks, int *process_sizes, int num_processes) {
    int allocation[num_processes];
    for(int i = 0; i < num_processes; i++) {
        allocation[i] = -1;
    }

    for(int i = 0; i < num_processes; i++) {
        int worst_fit_index = -1;
        for(int j = 0; j < num_blocks; j++) {
            if(block_sizes[j] >= process_sizes[i]) {
                if(worst_fit_index == -1 || block_sizes[j] > block_sizes[worst_fit_index]) {
                    worst_fit_index = j;
                }
            }
        }
        if(worst_fit_index != -1) {
            allocation[i] = worst_fit_index;
            block_sizes[worst_fit_index] -= process_sizes[i];
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
    // SCAN Disk Scheduling
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int num_requests = sizeof(requests) / sizeof(requests[0]);
    int current_position = 53;
    char direction = 'r'; // 'l' for left, 'r' for right

    scanDiskScheduling(requests, num_requests, current_position, direction);

    // Worst Fit Memory Placement
    int block_sizes[] = {100, 500, 200, 300, 600};
    int num_blocks = sizeof(block_sizes) / sizeof(block_sizes[0]);
    int process_sizes[] = {212, 417, 112, 426};
    int num_processes = sizeof(process_sizes) / sizeof(process_sizes[0]);

    worstFitMemoryPlacement(block_sizes, num_blocks, process_sizes, num_processes);

    return 0;
}
