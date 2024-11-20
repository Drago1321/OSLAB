// Write a program to calculate the number of page faults for a reference string (input any suitable reference string)
//  using the Least Recently Used (LRU) page replacement algorithms.

#include <stdio.h>

#define MAX_FRAMES 10  // Maximum number of frames

// Function to simulate LRU page replacement algorithm
int lruPageReplacement(int pages[], int pageCount, int frameCount) {
    int frames[frameCount];
    int lastUsed[frameCount];  // Track the last used time of each frame
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;  // Initialize frames as empty
        lastUsed[i] = -1;  // Initialize last used time as -1
    }

    int pageFaults = 0;
    int time = 0;  // To simulate the passage of time (incremented with each page reference)

    // Iterate through the reference string
    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in frames
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1;
                lastUsed[j] = time;  // Update last used time
                break;
            }
        }

        // If page is not found, replace the least recently used page
        if (!found) {
            int lruIndex = 0;
            for (int j = 1; j < frameCount; j++) {
                if (lastUsed[j] < lastUsed[lruIndex]) {
                    lruIndex = j;
                }
            }
            frames[lruIndex] = page;  // Replace the LRU page
            lastUsed[lruIndex] = time;  // Update last used time of replaced page
            pageFaults++;
        }

        // Display the current frame status
        printf("Frames: ");
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");

        time++;  // Increment the time after each reference
    }

    return pageFaults;
}

int main() {
    int pageCount, frameCount;

    // Input for the reference string
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &pageCount);
    int pages[pageCount];

    printf("Enter the reference string (space-separated): ");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]);
    }

    // Input for the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);

    // Call LRU page replacement function
    int pageFaults = lruPageReplacement(pages, pageCount, frameCount);
    printf("Total number of page faults: %d\n", pageFaults);

    return 0;
}
