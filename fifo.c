Code-
#include <stdio.h>
#include <stdbool.h>

int main() {
    int frames, pages;

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    printf("Enter the number of pages: ");
    scanf("%d", &pages);

    int incomingStream[pages];
    int pageFaults = 0;

    printf("Enter the page reference sequence:\n");
    for (int i = 0; i < pages; i++) {
        printf("Page reference for page %d: ", i + 1);
        scanf("%d", &incomingStream[i]);
    }

    printf("Incoming\t");
    for (int i = 0; i < frames; i++) {
        printf("Frame %d\t", i + 1);
    }

    int temp[frames];
    for (int m = 0; m < frames; m++) {
        temp[m] = -1;
    }

    for (int m = 0; m < pages; m++) {
        int s = 0;

        for (int n = 0; n < frames; n++) {
            if (incomingStream[m] == temp[n]) {
                s++;
                pageFaults--;
            }
        }

        pageFaults++;

        if ((pageFaults <= frames) && (s == 0)) {
            temp[m] = incomingStream[m];
        } else if (s == 0) {
            temp[(pageFaults - 1) % frames] = incomingStream[m];
        }

        printf("\n%d\t\t", incomingStream[m]);
        for (int n = 0; n < frames; n++) {
            if (temp[n] != -1) {
                printf(" %d\t\t", temp[n]);
            } else {
                printf(" - \t\t");
            }
        }
    }

    printf("\nTotal Page Faults:\t%d\n", pageFaults);

    return 0;
}
