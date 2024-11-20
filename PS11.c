// Write a program to calculate the number of page faults for a reference string
//  (input any suitable reference string) using First In First Out (FIFO) page replacement algorithms.

#include <stdio.h>

// Function to simulate FIFO page replacement algorithm
int fifoPageReplacement(int pages[], int pageCount, int frameCount) {
    int frames[frameCount];
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;  // Initialize frames as empty
    }

    int pageFaults = 0;
    int nextIndex = 0;  // Pointer to track the next frame to replace

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

        // If page is not found, replace it
        if (!found) {
            frames[nextIndex] = page;  // Replace the page
            pageFaults++;
            nextIndex = (nextIndex + 1) % frameCount;  // Move to the next frame (circular)
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

    // Call FIFO page replacement function
    int pageFaults = fifoPageReplacement(pages, pageCount, frameCount);
    printf("Total number of page faults: %d\n", pageFaults);

    return 0;
}
