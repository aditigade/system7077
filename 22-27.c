#include <stdio.h>
#include <stdlib.h>

// First Come First Serve (FCFS)
int FCFS(const int* requests, int n, int initialPosition) {
    int totalMovement = 0;
    int currentPosition = initialPosition;

    for (int i = 0; i < n; ++i) {
        totalMovement += abs(requests[i] - currentPosition);
        currentPosition = requests[i];
    }

    return totalMovement;
}

// Shortest Seek Time First (SSTF)
int SSTF(const int* requests, int n, int initialPosition) {
    int sortedRequests[n];
    for (int i = 0; i < n; ++i) {
        sortedRequests[i] = requests[i];
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (abs(sortedRequests[j] - initialPosition) > abs(sortedRequests[j + 1] - initialPosition)) {
                int temp = sortedRequests[j];
                sortedRequests[j] = sortedRequests[j + 1];
                sortedRequests[j + 1] = temp;
            }
        }
    }

    int totalMovement = 0;
    int currentPosition = initialPosition;

    for (int i = 0; i < n; ++i) {
        totalMovement += abs(sortedRequests[i] - currentPosition);
        currentPosition = sortedRequests[i];
    }

    return totalMovement;
}

// SCAN
int SCAN(const int* requests, int n, int initialPosition, int maxCylinder) {
    int sortedRequests[n];
    for (int i = 0; i < n; ++i) {
        sortedRequests[i] = requests[i];
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (sortedRequests[j] > sortedRequests[j + 1]) {
                int temp = sortedRequests[j];
                sortedRequests[j] = sortedRequests[j + 1];
                sortedRequests[j + 1] = temp;
            }
        }
    }

    int totalMovement = 0;
    int currentPosition = initialPosition;

    // Head movement towards lower cylinder numbers
    for (int i = 0; i < n; ++i) {
        if (sortedRequests[i] >= initialPosition) {
            break;
        }
        totalMovement += abs(sortedRequests[i] - currentPosition);
        currentPosition = sortedRequests[i];
    }

    // Head movement towards higher cylinder numbers
    for (int i = n - 1; i >= 0; --i) {
        if (sortedRequests[i] <= initialPosition) {
            break;
        }
        totalMovement += abs(sortedRequests[i] - currentPosition);
        currentPosition = sortedRequests[i];
    }

    return totalMovement;
}

// Circular SCAN (C-SCAN)
int CSCAN(const int* requests, int n, int initialPosition, int maxCylinder) {
    int sortedRequests[n];
    for (int i = 0; i < n; ++i) {
        sortedRequests[i] = requests[i];
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (sortedRequests[j] > sortedRequests[j + 1]) {
                int temp = sortedRequests[j];
                sortedRequests[j] = sortedRequests[j + 1];
                sortedRequests[j + 1] = temp;
            }
        }
    }

    int totalMovement = 0;
    int currentPosition = initialPosition;

    // Head movement towards lower cylinder numbers
    for (int i = 0; i < n; ++i) {
        if (sortedRequests[i] >= initialPosition) {
            break;
        }
        totalMovement += abs(sortedRequests[i] - currentPosition);
        currentPosition = sortedRequests[i];
    }

    // Head movement towards higher cylinder numbers
    totalMovement += abs(maxCylinder - currentPosition);
    currentPosition = 0;

    for (int i = 0; i < n; ++i) {
        if (sortedRequests[i] <= initialPosition) {
            break;
        }
        totalMovement += abs(sortedRequests[i] - currentPosition);
        currentPosition = sortedRequests[i];
    }

    return totalMovement;
}

int main() {
    int n; // Number of requests
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &requests[i]);
    }

    int initialPosition; // Initial head position
    printf("Enter the initial head position: ");
    scanf("%d", &initialPosition);

    int maxCylinder; // Maximum cylinder size
    printf("Enter the maximum cylinder size: ");
    scanf("%d", &maxCylinder);

    printf("FCFS Total Head Movement: (%d-%d)", requests[0], initialPosition);
    int fcfsTotal = FCFS(requests, n, initialPosition);
    for (int i = 1; i < n; ++i) {
        printf(" + (%d-%d)", requests[i], requests[i - 1]);
    }
    printf(" = %d\n", fcfsTotal);

    printf("SSTF Total Head Movement: (%d-%d)", requests[0], initialPosition);
    int sstfTotal = SSTF(requests, n, initialPosition);
    for (int i = 1; i < n; ++i) {
        printf(" + (%d-%d)", requests[i], requests[i - 1]);
    }
    printf(" = %d\n", sstfTotal);

    printf("SCAN Total Head Movement: (%d", initialPosition);
    int scanTotal = SCAN(requests, n, initialPosition, maxCylinder);
    int scannedRequests[n + 2];
    for (int i = 0; i < n; ++i) {
        scannedRequests[i] = requests[i];
    }
    scannedRequests[n] = 0;
    scannedRequests[n + 1] = maxCylinder;
    for (int i = 0; i < n + 2; ++i) {
        printf("-%d", scannedRequests[i]);
    }
    printf(") = %d\n", scanTotal);

    printf("C-SCAN Total Head Movement: (%d", initialPosition);
    int cscanTotal = CSCAN(requests, n, initialPosition, maxCylinder);
    int cscannedRequests[n + 2];
    for (int i = 0; i < n; ++i) {
        cscannedRequests[i] = requests[i];
    }
    cscannedRequests[n] = 0;
    cscannedRequests[n + 1] = maxCylinder;
    for (int i = 0; i < n + 2; ++i) {
        printf("-%d", cscannedRequests[i]);
    }
    printf(") = %d\n", cscanTotal);

    return 0;
}
