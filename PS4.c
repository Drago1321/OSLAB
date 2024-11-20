// Write a program to compute the Turnaround Time (TAT) and Waiting Time (WT) using the First Come and First Serve 
// (FCFS) Scheduling. (enter suitable number of processes, CPU burst, and Arrival Time)

#include <stdio.h>

struct Process {
    int pid;           // Process ID
    int arrivalTime;   // Arrival time
    int burstTime;     // Burst time
    int finishTime;    // Finish time
    int turnaroundTime; // Turnaround time
    int waitingTime;   // Waiting time
};

void calculateTimes(struct Process proc[], int n) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        // Start time for current process is the maximum of its arrival time or the current time
        if (currentTime < proc[i].arrivalTime) {
            currentTime = proc[i].arrivalTime;
        }

        proc[i].finishTime = currentTime + proc[i].burstTime;
        proc[i].turnaroundTime = proc[i].finishTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;

        // Update current time to the finish time of the current process
        currentTime = proc[i].finishTime;
    }
}

void printTable(struct Process proc[], int n) {
    printf("\nPID\tArrival\tBurst\tFinish\tTurnaround\tWaiting\n");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime,
               proc[i].burstTime, proc[i].finishTime, proc[i].turnaroundTime,
               proc[i].waitingTime);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1; // Assign process ID
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &proc[i].arrivalTime);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &proc[i].burstTime);
    }

    // Calculate times
    calculateTimes(proc, n);

    // Print table
    printTable(proc, n);

    return 0;
}