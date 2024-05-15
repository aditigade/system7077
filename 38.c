#include <stdio.h>

void nextFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for(int i = 0; i < n; i++) allocation[i] = -1;  // Initialize allocation array with -1

    int j = 0;  // Initialize block index
    for (int i = 0; i < n; i++) {
        // Do while loop to traverse the blocks circularly
        int count = 0;  // To avoid infinite loop
        while (count < m) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
            j = (j + 1) % m;  // Move to next block
            count++;
        }
    }

    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t%d\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d", allocation[i] + 1);
        else
            printf("Not Allocated");
        printf("\n");
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;  // Initialize allocation array with -1

    for (int i = 0; i < n; i++) {
        int wstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (wstIdx == -1 || blockSize[j] > blockSize[wstIdx])
                    wstIdx = j;
            }
        }
        if (wstIdx != -1) {
            allocation[i] = wstIdx;
            blockSize[wstIdx] -= processSize[i];
        }
    }

    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t%d\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d", allocation[i] + 1);
        else
            printf("Not Allocated");
        printf("\n");
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;  // Initialize allocation array with -1

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t%d\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d", allocation[i] + 1);
        else
            printf("Not Allocated");
        printf("\n");
    }
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    printf("Next Fit Allocation:\n");
    nextFit(blockSize, m, processSize, n);
    
    // Reset block sizes for new allocation
    int blockSizeNextFit[] = {100, 500, 200, 300, 600};
    for(int i = 0; i < m; i++) blockSize[i] = blockSizeNextFit[i];

    printf("\nWorst Fit Allocation:\n");
    worstFit(blockSize, m, processSize, n);
    
    // Reset block sizes for new allocation
    int blockSizeWorstFit[] = {100, 500, 200, 300, 600};
    for(int i = 0; i < m; i++) blockSize[i] = blockSizeWorstFit[i];

    printf("\nBest Fit Allocation:\n");
    bestFit(blockSize, m, processSize, n);
    
    // Reset block sizes for new allocation
    int blockSizeBestFit[] = {100, 500, 200, 300, 600};
    for(int i = 0; i < m; i++) blockSize[i] = blockSizeBestFit[i];

    return 0;
}
