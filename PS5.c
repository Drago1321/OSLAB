// Write a program to compute the Turnaround Time (TAT) and Waiting Time (WT) using the Shortest Job First 
// (Preemptive and Non-Preemptive) Scheduling. (enter suitable number of processes, CPU burst, and Arrival Time)

#include <stdio.h>
#include <limits.h>

// Structure to represent each process
struct Process {
    int pid;           // Process ID
    int arrivalTime;   // Arrival time
    int burstTime;     // Burst time
    int finishTime;    // Finish time
    int turnaroundTime; // Turnaround time
    int waitingTime;   // Waiting time
    int remainingTime; // Remaining burst time (used for Preemptive SJF)
    int isCompleted;   // Flag to check if process is completed
};

// Function for Non-Preemptive SJF
void nonPreemptiveSJF(struct Process proc[], int n) {
    int currentTime = 0, completed = 0;

    while (completed != n) {
        int minBurst = INT_MAX;
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (!proc[i].isCompleted && proc[i].arrivalTime <= currentTime && proc[i].burstTime < minBurst) {
                minBurst = proc[i].burstTime;
                idx = i;
            }
        }

        if (idx != -1) {
            proc[idx].finishTime = currentTime + proc[idx].burstTime;
            proc[idx].turnaroundTime = proc[idx].finishTime - proc[idx].arrivalTime;
            proc[idx].waitingTime = proc[idx].turnaroundTime - proc[idx].burstTime;
            proc[idx].isCompleted = 1;
            currentTime = proc[idx].finishTime;
            completed++;
        } else {
            currentTime++;
        }
    }
}

// Function for Preemptive SJF (Shortest Remaining Time First)
void preemptiveSJF(struct Process proc[], int n) {
    int currentTime = 0, completed = 0;

    while (completed != n) {
        int minRemaining = INT_MAX;
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && !proc[i].isCompleted && proc[i].remainingTime < minRemaining) {
                minRemaining = proc[i].remainingTime;
                idx = i;
            }
        }

        if (idx != -1) {
            proc[idx].remainingTime--;
            currentTime++;

            if (proc[idx].remainingTime == 0) {
                proc[idx].finishTime = currentTime;
                proc[idx].turnaroundTime = proc[idx].finishTime - proc[idx].arrivalTime;
                proc[idx].waitingTime = proc[idx].turnaroundTime - proc[idx].burstTime;
                proc[idx].isCompleted = 1;
                completed++;
            }
        } else {
            currentTime++;
        }
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

void resetProcesses(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].finishTime = 0;
        proc[i].turnaroundTime = 0;
        proc[i].waitingTime = 0;
        proc[i].isCompleted = 0;
        proc[i].remainingTime = proc[i].burstTime;
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &proc[i].arrivalTime);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].isCompleted = 0;
    }

    printf("\n--- Non-Preemptive SJF Scheduling ---\n");
    resetProcesses(proc, n);
    nonPreemptiveSJF(proc, n);
    printTable(proc, n);

    printf("\n--- Preemptive SJF (Shortest Remaining Time First) Scheduling ---\n");
    resetProcesses(proc, n);
    preemptiveSJF(proc, n);
    printTable(proc, n);

    return 0;
}