#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char pid[10];
    int arrival_time;
    int exec_time;
    int priority;
} Process;

int readProcesses(const char *filename, Process **processes) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    int capacity = 10;
    *processes = malloc(sizeof(Process) * capacity);
    int count = 0;

    while (fscanf(file, "%s %d %d %d", (*processes)[count].pid, &(*processes)[count].arrival_time, 
                  &(*processes)[count].exec_time, &(*processes)[count].priority) != EOF) {
        count++;
        if (count >= capacity) {
            capacity *= 2;
            *processes = realloc(*processes, sizeof(Process) * capacity);
        }
    }

    fclose(file);
    return count;
}

void priorityScheduling(Process *processes, int n) {
    int currentTime = 0, completed = 0;
    int lastProcess = -1;
    int totalWaitTime = 0, totalTurnaroundTime = 0;
    int running = -1; // Index of the currently running process

    // Print Gantt Chart Header
    printf("Gantt Chart:\n");

    while (completed < n) {
        int highestPriority = -1; // Now the highest value has the highest priority

        // Find the process with the highest priority that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= currentTime && processes[i].exec_time > 0) {
                if (processes[i].priority > highestPriority) {
                    highestPriority = processes[i].priority;
                    running = i;
                }
            }
        }

        // No process is currently running, increment currentTime
        if (highestPriority == -1) {
            currentTime++;
            continue;
        }

        // If a process with a higher priority preempts the current process
        if (lastProcess != running) {
            if (lastProcess != -1) {
                printf("%d)] ", currentTime);
            }
            printf("[%s (%d-", processes[running].pid, currentTime);
            lastProcess = running;
        }

        // Running the process
        processes[running].exec_time--;
        currentTime++;

        // If the process finishes
        if (processes[running].exec_time == 0) {
            printf("%d)] ", currentTime);
            completed++;
            totalWaitTime += currentTime - processes[running].arrival_time - processes[running].exec_time;
            totalTurnaroundTime += currentTime - processes[running].arrival_time;
            lastProcess = -1;
        }
    }

    printf("\nAverage Wait Time: %.2f\n", totalWaitTime / (float)n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / (float)n);
}

int main() {
    Process *processes;
    int n = readProcesses("file1.txt", &processes);

    if (n > 0) {
        priorityScheduling(processes, n);
        free(processes);
    } else {
        printf("Error: No processes were read from the file.\n");
    }

    return 0;
}

