/*
Arantza Mendoza, Andy Lopez, Victoria Coutee
*/


#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 1000

//Function Prototypes
int FIFO(int pages[], int pageCount, int frames, int finalFrames[]);  //FIFO algorithm
int LRU(int pages[], int pageCount, int frames, int finalFrames[]);   //LRU algorithm
void print_frames(int frameArray[], int frames);                      //Helper to print frames

int main(int argc, char *argv[]) {

    //Check for 2 arguments (file + number of frames)
    if (argc != 3) {
        fprintf(stderr, "Usage: %s pagereffile numberofframes\n", argv[0]);
        return 1;
    }

    //Convert number of frames and validate
    int frames = atoi(argv[2]);
    if (frames < 1 || frames > MAX_FRAMES) {
        fprintf(stderr, "Error: number of frames must be between 1 and %d\n", MAX_FRAMES);
        return 1;
    }

    //Open text file with page references
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    //Array contain page numbers from text file
    int pages[MAX_PAGES];
    int pageCount = 0;

    //Read integers from text file
    while (fscanf(fp, "%d", &pages[pageCount]) == 1) {
        // Make sure pages are not negative
        if (pages[pageCount] < 0) {
            fprintf(stderr, "Error: page numbers must be non-negative\n");
            fclose(fp);
            return 1;
        }

        pageCount++;

        //Stop if max pages is exceeded
        if (pageCount >= MAX_PAGES) {
            fprintf(stderr, "Error: too many page references\n");
            fclose(fp);
            return 1;
        }
    }

    //close the file
    fclose(fp);

    //Arrays to store final frames
    int finalFIFO[MAX_FRAMES];
    int finalLRU[MAX_FRAMES];

    //Run FIFO and print results
    int fifo_faults = FIFO(pages, pageCount, frames, finalFIFO);
    printf("FIFO: %d page faults\n", fifo_faults);
    printf("Final state of memory: ");
    for (int i = 0; i < frames; i++)
        printf("%d ", finalFIFO[i]);
    printf("\n\n");

    //Run LRU and print results
    int lru_faults = LRU(pages, pageCount, frames, finalLRU);
    printf("LRU: %d page faults\n", lru_faults);
    printf("Final state of memory: ");
    for (int i = 0; i < frames; i++)
        printf("%d ", finalLRU[i]);
    printf("\n");

    return 0;
}

//FIFO replacement algorithm (replace oldest page first)
int FIFO(int pages[], int pageCount, int frames, int finalFrames[]) {

    int frameArray[MAX_FRAMES]; //stores all frames
    int i, j;

    //mark all frames with -1 to indicate they are empty
    for (i = 0; i < frames; i++) {
        frameArray[i] = -1;
    }

    int pageFaults = 0;
    int fifoIndex = 0; //track which frame to replace next

    //iterate through every page in the list
    for (i = 0; i < pageCount; i++) {
        int currentPage = pages[i];
        int found = 0;

        //check if page is already stored
        for (j = 0; j < frames; j++) {
            if (frameArray[j] == currentPage) {
                found = 1; // page hit
                break;
            }
        }

        // page fault if not found
        if (!found) {
            pageFaults++;

            //replace the oldest page
            frameArray[fifoIndex] = currentPage;

            //move pointer
            fifoIndex = (fifoIndex + 1) % frames;
        }
    }

    //copy final frame
    for (i = 0; i < frames; i++) {
        finalFrames[i] = frameArray[i];
    }

    return pageFaults;
}

//LRU replacement algorithm (replace page that was used the longest time ago)
int LRU(int pages[], int pageCount, int frames, int finalFrames[]) {

    int frameArray[MAX_FRAMES]; //stores pages in memory
    int lastUsed[MAX_FRAMES];   //tracks when frame was last used
    int time = 0;               //time variable to increment for each access

    //initialize all frames and times
    for (int i = 0; i < frames; i++) {
        frameArray[i] = -1;
        lastUsed[i] = -1;
    }

    int pageFaults = 0;

    //iteerate through all page references
    for (int i = 0; i < pageCount; i++) {
        int currentPage = pages[i];
        int found = -1;

        //check if page is present (i.e., hit)
        for (int j = 0; j < frames; j++) {
            if (frameArray[j] == currentPage) {
                found = j; //found the page index
                break;
            }
        }

        if (found != -1) {
            //Page hit (update when it was last used)
            lastUsed[found] = time;
        } else {
            //Page fault (page not in any frame)
            pageFaults++;

            int emptyIndex = -1;

            //try to find an empty frame
            for (int j = 0; j < frames; j++) {
                if (frameArray[j] == -1) {
                    emptyIndex = j;
                    break;
                }
            }

            if (emptyIndex != -1) {
                //store page in empty frame
                frameArray[emptyIndex] = currentPage;
                lastUsed[emptyIndex] = time;
            } else {
                // find the LRU frame if all are full
                int lruIndex = 0;
                for (int j = 1; j < frames; j++) {
                    if (lastUsed[j] < lastUsed[lruIndex]) {
                        lruIndex = j; // this frame was used the longest time ago
                    }
                }

                //replace the LRU page
                frameArray[lruIndex] = currentPage;
                lastUsed[lruIndex] = time;
            }
        }

        time++; //increment time variable
    }

    //save final frame
    for (int i = 0; i < frames; i++) {
        finalFrames[i] = frameArray[i];
    }

    return pageFaults;
}

//prints the frames
void print_frames(int frameArray[], int frames) {
    for (int i = 0; i < frames; i++) {
        if (frameArray[i] == -1)
            printf("[ ] ");      // empty frame
        else
            printf("[%d] ", frameArray[i]); // filled frame
    }
    printf("\n\n");
}
