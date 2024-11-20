// Write a program to compute the Turnaround Time (TAT) and Waiting Time (WT) 
// using the Round Robin Scheduling. (enter suitable number of processes, CPU burst, and Arrival Time)

#include <stdio.h>

// Function to calculate times using Round Robin Scheduling
void calculateTimes(int processes[], int n, int burstTime[], int arrivalTime[], int quantum) {
    int waitingTime[n], turnaroundTime[n], remainingTime[n];
    int t = 0; // Current time
    int done;

    // Copy burst times into remaining times
    for (int i = 0; i < n; i++)
        remainingTime[i] = burstTime[i];

    // Initialize waiting times to 0
    for (int i = 0; i < n; i++)
        waitingTime[i] = 0;

    // Loop until all processes are done
    do {
        done = 1; // Assume all processes are done

        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0 && arrivalTime[i] <= t) {
                done = 0; // Process still pending

                if (remainingTime[i] > quantum) {
                    t += quantum;
                    remainingTime[i] -= quantum;
                } else {
                    t += remainingTime[i];
                    waitingTime[i] = t - burstTime[i] - arrivalTime[i];
                    remainingTime[i] = 0;
                }
            }
        }

        // Increment time if no process is ready to execute
        if (done)
            t++;
    } while (!done);

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++)
        turnaroundTime[i] = burstTime[i] + waitingTime[i];

    // Display times for each process
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrivalTime[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }

    // Calculate average waiting and turnaround times
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += waitingTime[i];
        totalTAT += turnaroundTime[i];
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burstTime[n], arrivalTime[n];

    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    calculateTimes(processes, n, burstTime, arrivalTime, quantum);

    return 0;
}
