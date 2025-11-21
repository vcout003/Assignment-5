#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 1000

// Function Prototypes
int FIFO(int pages[], int pageCount, int frames, int finalFrames[]);
int simulate_LRU(int pages[], int pageCount, int frames, int finalFrames[]);
void print_frames(int frameArray[], int frames);

// Main
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s pagereffile numberofframes\n", argv[0]);
        return 1;
    }

    int frames = atoi(argv[2]);
    if (frames < 1 || frames > MAX_FRAMES) {
        fprintf(stderr, "Error: number of frames must be between 1 and %d\n", MAX_FRAMES);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    int pages[MAX_PAGES];
    int pageCount = 0;

    // Read all integers in the file
    while (fscanf(fp, "%d", &pages[pageCount]) == 1) {
        pageCount++;
        if (pageCount >= MAX_PAGES) {
            fprintf(stderr, "Error: too many page references\n");
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    printf("Loaded %d page references.\n", pageCount);
    int fifoFinal[MAX_FRAMES];
    int lruFinal[MAX_FRAMES];
 // Call FIFO & LRU (not implemented yet)
    int fifo_faults = FIFO(pages, pageCount, frames, fifoFinal);
    printf("FIFO page faults: %d\n", fifo_faults);

    int lru_faults = simulate_LRU(pages, pageCount, frames, lruFinal);
    printf("LRU page faults: %d\n", lru_faults);

    return 0;
}


// FIFO
int FIFO(int pages[], int pageCount, int frames, int finalFrames[]) {

    int frameArray[MAX_FRAMES];
    int i, j;

    //Set all frames as empty
    for (i = 0; i < frames; i++) {
    finalFrames[i] = frameArray[i];
    }

    int pageFaults = 0;//variable to store page faults
    int fifoIndex = 0;  //variable to store which frame needs to be replaced

    for (i = 0; i < pageCount; i++) {//for loop to store currentPage
        int currentPage = pages[i];
        int found = 0;

        //frame check
        for (j = 0; j < frames; j++) {
            if (frameArray[j] == currentPage) {
                found = 1;
                break;
            }
        }

        //trigger page fault if page is not found
        if (!found) {
            pageFaults++;

            //replace the oldest page
            frameArray[fifoIndex] = currentPage;

            //Move pointer
            fifoIndex = (fifoIndex + 1) % frames;
        }
 }

    return pageFaults;
}



// LRU

int simulate_LRU(int pages[], int pageCount,int frames, int finalFrames[]) { //Andy

    int frameArray[MAX_FRAMES];
    int lastUsed[MAX_FRAMES];
    int time = 0;

    // Initialize
    for (int i = 0; i < frames; i++) {
        frameArray[i] = -1;
        lastUsed[i] = -1;
    }

    int pageFaults = 0;

    for (int i = 0; i < pageCount; i++) {

        int currentPage = pages[i];
        int found = -1;

        // Check if page exists in frames
        for (int j = 0; j < frames; j++) {
            if (frameArray[j] == currentPage) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            // Page hit → update last used
            lastUsed[found] = time;
        } else {
            // Page fault
            pageFaults++;

            // Find empty frame first
            int emptyIndex = -1;
            for (int j = 0; j < frames; j++) {
                if (frameArray[j] == -1) {
                    emptyIndex = j;
                    break;
                }
            }

            if (emptyIndex != -1) {
                // Use empty frame
                frameArray[emptyIndex] = currentPage;
                lastUsed[emptyIndex] = time;
            } else {
                // Replace LRU page
                int lruIndex = 0;
                for (int j = 1; j < frames; j++) {
                    if (lastUsed[j] < lastUsed[lruIndex])
                        lruIndex = j;
                }

                frameArray[lruIndex] = currentPage;
                lastUsed[lruIndex] = time;
            }
        }

        time++;
    }

    // Copy final frame state
    for (int i = 0; i < frames; i++)
      finalFrames[i] = frameArray[i];

    return pageFaults;


}


// Helper to print frame contents //Arantza + Testing/Bug Fix
void print_frames(int frameArray[], int frames) {

   for (int i = 0; i < frames; i++) {
        if (frameArray[i] == -1)
            printf("[ ] ");
        else
            printf("[%d] ", frameArray[i]);
    }
    printf("\n");
}
                if (frameArray[j] == -1) {
                    emptyIndex = j;
                    break;
                }
            }

            if (emptyIndex != -1) {
                // Use empty frame
                frameArray[emptyIndex] = currentPage;
                lastUsed[emptyIndex] = time;
            } else {
                // Replace LRU page
                int lruIndex = 0;
                for (int j = 1; j < frames; j++) {
                    if (lastUsed[j] < lastUsed[lruIndex])
                        lruIndex = j;
                }

                frameArray[lruIndex] = currentPage;
                lastUsed[lruIndex] = time;
            }
        }

        time++;
    }

    // Copy final frame state
    for (int i = 0; i < frames; i++)
      finalFrames[i] = frameArray[i];

    return pageFaults;


}


// Helper to print frame contents //Arantza + Testing/Bug Fix
void print_frames(int frameArray[], int frames) {

   for (int i = 0; i < frames; i++) {
        if (frameArray[i] == -1)
            printf("[ ] ");
        else
            printf("[%d] ", frameArray[i]);
    }
    printf("\n");
}

                                                                            
