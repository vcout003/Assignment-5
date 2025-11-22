#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 1000

// Function Prototypes
int FIFO(int pages[], int pageCount, int frames, int finalFrames[]);   // Andy
int LRU(int pages[], int pageCount, int frames, int finalFrames[]);    // Andy
void print_frames(int frameArray[], int frames);                       // Arantza + Testing/Bug Fix

int main(int argc, char *argv[]) {

    // Validate argument count
    if (argc != 3) {
        fprintf(stderr, "Usage: %s pagereffile numberofframes\n", argv[0]);
        return 1;
    }

    // Validate number of frames
    int frames = atoi(argv[2]);
    if (frames < 1 || frames > MAX_FRAMES) {
        fprintf(stderr, "Error: number of frames must be between 1 and %d\n", MAX_FRAMES);
        return 1;
    }

    // Try to open file
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    // Read all page references
    int pages[MAX_PAGES];
    int pageCount = 0;

    while (fscanf(fp, "%d", &pages[pageCount]) == 1) {
        if (pages[pageCount] < 0) {
            fprintf(stderr, "Error: page numbers must be non-negative\n");
            fclose(fp);
            return 1;
        }

        pageCount++;
        if (pageCount >= MAX_PAGES) {
            fprintf(stderr, "Error: too many page references\n");
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    //printf("Loaded %d page references.\n\n", pageCount);

    // Arrays to hold final frame states
    int finalFIFO[MAX_FRAMES];
    int finalLRU[MAX_FRAMES];

    // FIFO section (Andy)
    int fifo_faults = FIFO(pages, pageCount, frames, finalFIFO);
    printf("FIFO: %d page faults\n", fifo_faults);
    printf("Final state of memory: ");
    for (int i = 0; i < frames; i++)
        printf("%d ", finalFIFO[i]);
    printf("\n\n");

    // LRU section (Andy)
    int lru_faults = LRU(pages, pageCount, frames, finalLRU);
    printf("LRU: %d page faults\n", lru_faults);
    printf("Final state of memory: ");
    for (int i = 0; i < frames; i++)
        printf("%d ", finalLRU[i]);
    printf("\n");

    return 0;
}

// FIFO (Andy)

int FIFO(int pages[], int pageCount, int frames, int finalFrames[]) {

    int frameArray[MAX_FRAMES];
    int i, j;

    // Initialize frames to empty
    for (i = 0; i < frames; i++) {
        frameArray[i] = -1;
    }

    int pageFaults = 0;
    int fifoIndex = 0; // pointer to next replacement position

    for (i = 0; i < pageCount; i++) {
        int currentPage = pages[i];
        int found = 0;

        // Check if page is already in a frame
        for (j = 0; j < frames; j++) {
            if (frameArray[j] == currentPage) {
                found = 1;
                break;
            }
        }

        // Page fault occurs
        if (!found) {
            pageFaults++;

            frameArray[fifoIndex] = currentPage;
            fifoIndex = (fifoIndex + 1) % frames;
        }
    }

    // Save final frame state
    for (i = 0; i < frames; i++) {
        finalFrames[i] = frameArray[i];
    }

    return pageFaults;
}

// LRU (Andy)

int LRU(int pages[], int pageCount, int frames, int finalFrames[]) {

    int frameArray[MAX_FRAMES];
    int lastUsed[MAX_FRAMES];
    int time = 0;

    // Initialize frames
    for (int i = 0; i < frames; i++) {
        frameArray[i] = -1;
        lastUsed[i] = -1;
    }

    int pageFaults = 0;

    for (int i = 0; i < pageCount; i++) {
        int currentPage = pages[i];
        int found = -1;

        // Check if already in a frame
        for (int j = 0; j < frames; j++) {
            if (frameArray[j] == currentPage) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            // Page hit → update timestamp
            lastUsed[found] = time;
        } else {
            // Page fault
            pageFaults++;

            int emptyIndex = -1;

            // First look for empty frame
            for (int j = 0; j < frames; j++) {
                if (frameArray[j] == -1) {
                    emptyIndex = j;
                    break;
                }
            }

            if (emptyIndex != -1) {
                frameArray[emptyIndex] = currentPage;
                lastUsed[emptyIndex] = time;
            } else {
                // No empty frame → replace LRU
                int lruIndex = 0;
                for (int j = 1; j < frames; j++) {
                    if (lastUsed[j] < lastUsed[lruIndex]) {
                        lruIndex = j;
                    }
                }

                frameArray[lruIndex] = currentPage;
                lastUsed[lruIndex] = time;
            }
        }

        time++;
    }

    // Save final frame states
    for (int i = 0; i < frames; i++) {
        finalFrames[i] = frameArray[i];
    }

    return pageFaults;
}

// Helper to print frame contents (Arantza + Testing/Bug Fix)

void print_frames(int frameArray[], int frames) {
    for (int i = 0; i < frames; i++) {
        if (frameArray[i] == -1)
            printf("[ ] ");
        else
            printf("[%d] ", frameArray[i]);
    }
    printf("\n\n");
}
