#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int pageFaultsFIFO(int pages[], int n, int capacity);
int pageFaultsOptimal(int pages[], int n, int capacity);

int main() {
    int pages[] = {7, 1, 0, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    printf("Total Page Faults (FIFO): %d\n", pageFaultsFIFO(pages, n, capacity));
    printf("Total Page Faults (Optimal): %d\n", pageFaultsOptimal(pages, n, capacity));

    return 0;
}

int pageFaultsFIFO(int pages[], int n, int capacity) {
    int s[MAX_SIZE];
    int indexes[MAX_SIZE];
    int page_faults = 0;
    int front = 0, rear = 0;

    for (int i = 0; i < n; i++) {
        if (rear < capacity) {
            int found = 0;
            for (int j = 0; j < rear; j++) {
                if (s[j] == pages[i]) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                s[rear] = pages[i];
                page_faults++;
                indexes[rear++] = i;
            }
        } else {
            int found = 0;
            for (int j = 0; j < capacity; j++) {
                if (s[j] == pages[i]) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                int val = s[front];
                front = (front + 1) % capacity;
                s[rear] = pages[i];
                rear = (rear + 1) % capacity;
                page_faults++;
                indexes[rear - 1] = i;
            }
        }
    }

    return page_faults;
}

int pageFaultsOptimal(int pages[], int n, int capacity) {
    int s[MAX_SIZE];
    int index[MAX_SIZE];
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        if (i < capacity) {
            int found = 0;
            for (int j = 0; j < i; j++) {
                if (s[j] == pages[i]) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                s[i] = pages[i];
                page_faults++;
            }
            index[pages[i]] = i;
        } else {
            int found = 0;
            for (int j = 0; j < capacity; j++) {
                if (s[j] == pages[i]) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                int farthest = i + 1, val = -1;
                for (int j = 0; j < capacity; j++) {
                    if (index[s[j]] > farthest) {
                        farthest = index[s[j]];
                        val = s[j];
                    }
                }
                if (val == -1) {
                    for (int j = 0; j < capacity; j++) {
                        if (index[s[j]] < farthest) {
                            farthest = index[s[j]];
                            val = s[j];
                        }
                    }
                }
                for (int j = 0; j < capacity; j++) {
                    if (s[j] == val) {
                        s[j] = pages[i];
                        page_faults++;
                        break;
                    }
                }
            }
            index[pages[i]] = i;
        }
    }

    return page_faults;
}
