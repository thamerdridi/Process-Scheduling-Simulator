#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    char pid[10];
    int arrival_time;
    int exec_time;
    int priority;
} Process;

int readProcesses(const char *filename, Process **processes) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        return -1;
    }

    Process *tempProcesses = (Process *)malloc(sizeof(Process) * 100); // Assuming max 100 processes
    int count = 0;

    while (fscanf(file, "%s %d %d %d", tempProcesses[count].pid, &tempProcesses[count].arrival_time, 
                  &tempProcesses[count].exec_time, &tempProcesses[count].priority) != EOF) {
        count++;
    }

    *processes = tempProcesses;
    fclose(file);
    return count;
}

void srt(Process *processes, int n) {
    int currentTime = 0, completed = 0;
    int remainingTime[n];
    int lastProcess = -1;
    int totalWaitTime = 0, totalTurnaroundTime = 0;

    // Initialize remaining times
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].exec_time;
    }

    printf("Gantt Chart:\n");
    while (completed != n) {
        int shortest = -1, minm = INT_MAX;

        // Find the process with the shortest remaining time
        for (int j = 0; j < n; j++) {
            if (processes[j].arrival_time <= currentTime && remainingTime[j] < minm && remainingTime[j] > 0) {
                minm = remainingTime[j];
                shortest = j;
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        // If a new process is selected and it's not a continuation of the last process
        if (lastProcess != shortest) {
            if (lastProcess != -1) {
                // Print the end time for the last process before switching
                printf("%d)] ", currentTime);
            }
            printf("[%s (%d-", processes[shortest].pid, currentTime);
            lastProcess = shortest;
        }

        // Execute the process
        remainingTime[shortest]--;
        currentTime++;

        // If a process is completed
        if (remainingTime[shortest] == 0) {
            completed++;
            printf("%d)] ", currentTime);
            lastProcess = -1; // Reset last process

            // Calculate waiting time and turnaround time
            int turnaroundTime = currentTime - processes[shortest].arrival_time;
            int waitingTime = turnaroundTime - processes[shortest].exec_time;
            totalWaitTime += waitingTime;
            totalTurnaroundTime += turnaroundTime;
        }
    }
    printf("\n");

    printf("Average Wait Time: %.2f\n", (float)totalWaitTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

int main() {
    Process *processes;
    int n = readProcesses("file1.txt", &processes);

    if (n > 0) {
        srt(processes, n);
    } else {
        printf("Error: No processes were read from the file.\n");
    }

    free(processes);
    return 0;
}

