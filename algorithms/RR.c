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
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int count = 0;
    int size = 10;
    *processes = malloc(size * sizeof(Process));

    while (fscanf(file, "%s %d %d %d", (*processes)[count].pid, &(*processes)[count].arrival_time,
                  &(*processes)[count].exec_time, &(*processes)[count].priority) != EOF) {
        count++;
        if (count >= size) {
            size *= 2;
            *processes = realloc(*processes, size * sizeof(Process));
        }
    }

    fclose(file);
    return count;
}

void roundRobin(Process *processes, int n, int quantum) {
    int *remainingTime = malloc(n * sizeof(int));
    int currentTime = 0, totalWaitTime = 0, totalTurnaroundTime = 0, completed = 0;
    int *waitTime = malloc(n * sizeof(int));
    int *turnaroundTime = malloc(n * sizeof(int));
    int *isCompleted = calloc(n, sizeof(int));

    
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].exec_time;
        waitTime[i] = -1;
    }

    printf("Gantt Chart:\n");
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && processes[i].arrival_time <= currentTime) {
                if (waitTime[i] == -1) {
                    waitTime[i] = (currentTime > processes[i].arrival_time) ? (currentTime - processes[i].arrival_time) : 0;
                }

                if (remainingTime[i] > 0) {
                    printf("| %s ", processes[i].pid);
                    int execTime = (remainingTime[i] < quantum) ? remainingTime[i] : quantum;
                    remainingTime[i] -= execTime;
                    currentTime += execTime;
                    printf("(%d - %d) ", currentTime - execTime, currentTime);

                    if (remainingTime[i] == 0) {
                        isCompleted[i] = 1;
                        completed++;
                        turnaroundTime[i] = currentTime - processes[i].arrival_time;
                        totalTurnaroundTime += turnaroundTime[i];
                        totalWaitTime += waitTime[i];
                    }
                }
            }
        }
        
        if (completed == n) {
            break;
        }
        currentTime++;
    }
    printf("|\n");

    for (int i = 0; i < n; ++i) {
        if (waitTime[i] == -1) {
            waitTime[i] = 0;
        }
    }

    printf("\nAverage Wait Time: %.2f\n", (float)totalWaitTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);

    free(remainingTime);
    free(waitTime);
    free(turnaroundTime);
    free(isCompleted);
}

int main() {
    Process *processes;
    int n = readProcesses("file1.txt", &processes); 

    if (n > 0) {
        int quantum;
        printf("Enter Time Slice OR Quantum Number: ");
        scanf("%d", &quantum);

        roundRobin(processes, n, quantum);
        free(processes);
    } else {
        printf("Error: No processes were read from the file.\n");
    }

    return 0;
}

