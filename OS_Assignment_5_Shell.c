#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 1000

// Function Prototypes
int simulate_FIFO(int pages[], int pageCount, int frames);
int simulate_LRU(int pages[], int pageCount, int frames);
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

    // Call FIFO & LRU (not implemented yet)
    int fifo_faults = simulate_FIFO(pages, pageCount, frames);
    printf("FIFO page faults: %d\n", fifo_faults);

    int lru_faults = simulate_LRU(pages, pageCount, frames);
    printf("LRU page faults: %d\n", lru_faults);

    return 0;
}


// FIFO 
int simulate_FIFO(int pages[], int pageCount, int frames) { //Victoria

    // TODO: Implement FIFO page replacement algorithm
    // TODO: Track page faults
    // TODO: Track final frame state
    // TODO: Return # of page faults

    return 0;
}


// LRU 

int simulate_LRU(int pages[], int pageCount, int frames) { //Andy

    // TODO: Implement LRU page replacement algorithm
    // TODO: Track page faults
    // TODO: Track final frame state
    // TODO: Return # of page faults

    return 0;
}


// Helper to print frame contents //Arantza + Testing/Bug Fix
void print_frames(int frameArray[], int frames) {

    // TODO: Print final frame state

}
