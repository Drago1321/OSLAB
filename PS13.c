// Write a program to calculate the number of page faults for a reference string 
// (input any suitable reference string) using the Optimal page replacement algorithms.

#include <stdio.h>

#define MAX_FRAMES 10  // Maximum number of frames

// Function to find the optimal page to replace
int findOptimal(int pages[], int frameCount, int frames[], int pageCount, int currentIndex) {
    int farthest = currentIndex, pos = -1;

    // Try to find the page that will not be used for the longest period of time
    for (int i = 0; i < frameCount; i++) {
        int j;
        for (j = currentIndex + 1; j < pageCount; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        // If the page is never referenced again, replace it
        if (j == pageCount) {
            return i;
        }
        // If no position has been assigned yet, set it to the current frame
        if (pos == -1) {
            pos = i;
        }
    }

    return pos;
}

// Function to simulate the Optimal page replacement algorithm
int optimalPageReplacement(int pages[], int pageCount, int frameCount) {
    int frames[frameCount];
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;  // Initialize frames as empty
    }

    int pageFaults = 0;

    // Iterate through the reference string
    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in frames
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If page is not found, replace it with the optimal page
        if (!found) {
            int pos = -1;

            // Check if there is an empty frame available
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame, find the optimal page to replace
            if (pos == -1) {
                pos = findOptimal(pages, frameCount, frames, pageCount, i);
            }

            frames[pos] = page;  // Replace the page
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

    // Call Optimal page replacement function
    int pageFaults = optimalPageReplacement(pages, pageCount, frameCount);
    printf("Total number of page faults: %d\n", pageFaults);

    return 0;
}
