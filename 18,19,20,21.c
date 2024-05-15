#include <stdio.h>
#include <stdbool.h>

void lru(int total_frames, int total_pages, int pages[]) {
    int frames[total_frames];
    int recent[total_frames];
    int page_fault = 0;
    int i, j;

    for (i = 0; i < total_frames; i++) {
        frames[i] = -1;
        recent[i] = 0;
    }

    for (i = 0; i < total_pages; i++) {
        bool found = false;
        for (j = 0; j < total_frames; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                recent[j] = i + 1;
                break;
            }
        }
        if (!found) {
            int least_recent = recent[0], least_recent_pos = 0;
            for (j = 1; j < total_frames; j++) {
                if (recent[j] < least_recent) {
                    least_recent = recent[j];
                    least_recent_pos = j;
                }
            }
            frames[least_recent_pos] = pages[i];
            recent[least_recent_pos] = i + 1;
            page_fault++;
        }

        printf("%d: ", pages[i]);
        for (j = 0; j < total_frames; j++) {
            printf("%d\t", frames[j]);
        }
        printf("\n");
    }
    printf("\nTotal Number of Page Faults (LRU):\t%d\n\n", page_fault);
}

void fifo(int total_frames, int total_pages, int pages[]) {
    int frames[total_frames];
    int page_fault = 0;
    int i, j, k = 0;

    for (i = 0; i < total_frames; i++) {
        frames[i] = -1;
    }

    for (i = 0; i < total_pages; i++) {
        bool found = false;
        for (j = 0; j < total_frames; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            frames[k] = pages[i];
            k = (k + 1) % total_frames;
            page_fault++;
        }

        printf("%d: ", pages[i]);
        for (j = 0; j < total_frames; j++) {
            printf("%d\t", frames[j]);
        }
        printf("\n");
    }
    printf("\nTotal Number of Page Faults (FIFO):\t%d\n\n", page_fault);
}

void secondChance(int total_frames, int total_pages, int pages[]) {
    int frames[total_frames];
    bool second_chance[total_frames];
    int page_fault = 0;
    int i, j, k = 0;

    for (i = 0; i < total_frames; i++) {
        frames[i] = -1;
        second_chance[i] = false;
    }

    for (i = 0; i < total_pages; i++) {
        bool found = false;
        for (j = 0; j < total_frames; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                second_chance[j] = true;
                break;
            }
        }
        if (!found) {
            while (true) {
                if (!second_chance[k]) {
                    frames[k] = pages[i];
                    second_chance[k] = true;
                    page_fault++;
                    k = (k + 1) % total_frames;
                    break;
                } else {
                    second_chance[k] = false;
                    k = (k + 1) % total_frames;
                }
            }
        }

        printf("%d: ", pages[i]);
        for (j = 0; j < total_frames; j++) {
            printf("%d\t", frames[j]);
        }
        printf("\n");
    }
    printf("\nTotal Number of Page Faults (Second Chance):\t%d\n\n", page_fault);
}

void optimal(int total_frames, int total_pages, int pages[]) {
    int frames[total_frames];
    int page_fault = 0;
    int i, j, k;

    for (i = 0; i < total_frames; i++) {
        frames[i] = -1;
    }

    for (i = 0; i < total_pages; i++) {
        bool found = false;
        for (j = 0; j < total_frames; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            int farthest = i;
            for (j = 0; j < total_frames; j++) {
                bool future = false;
                for (k = i + 1; k < total_pages; k++) {
                    if (frames[j] == pages[k]) {
                        future = true;
                        if (k > farthest) {
                            farthest = k;
                        }
                        break;
                    }
                }
                if (!future) {
                    farthest = k;
                    break;
                }
            }
            frames[j] = pages[i];
            page_fault++;
        }

        printf("%d: ", pages[i]);
        for (j = 0; j < total_frames; j++) {
            printf("%d\t", frames[j]);
        }
        printf("\n");
    }
    printf("\nTotal Number of Page Faults (Optimal):\t%d\n\n", page_fault);
}

int main() {
    int total_frames, total_pages;

    printf("Enter the number of frames: ");
    scanf("%d", &total_frames);

    printf("Enter the number of pages: ");
    scanf("%d", &total_pages);

    int pages[total_pages];

    printf("Enter the page reference sequence:\n");
    for (int i = 0; i < total_pages; i++) {
        printf("Page reference for page %d: ", i + 1);
        scanf("%d", &pages[i]);
    }

    printf("\nLRU Page Replacement Algorithm:\n");
    lru(total_frames, total_pages, pages);

    printf("\nFIFO Page Replacement Algorithm:\n");
    fifo(total_frames, total_pages, pages);

    printf("\nSecond Chance Page Replacement Algorithm:\n");
    secondChance(total_frames, total_pages, pages);

    printf("\nOptimal Page Replacement Algorithm:\n");
    optimal(total_frames, total_pages, pages);

    return 0;
}
