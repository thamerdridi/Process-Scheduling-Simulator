#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char pid[10];
    int arrival_time;
    int exec_time;
    int priority;
} Process;

int num_processes = 0;

Process* readProcesses(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        return NULL;
    }

    Process *processes = malloc(sizeof(Process) * 100);
    while (fscanf(file, "%s %d %d %d", processes[num_processes].pid, 
                  &processes[num_processes].arrival_time, 
                  &processes[num_processes].exec_time, 
                  &processes[num_processes].priority) != EOF) {
        num_processes++;
    }

    fclose(file);
    return processes;
}

int compareArrivalTime(const void *a, const void *b) {
    Process *processA = (Process *)a;
    Process *processB = (Process *)b;
    return processA->arrival_time - processB->arrival_time;
}

void fifo(Process *processes) {
    // Sort processes based on arrival time
    qsort(processes, num_processes, sizeof(Process), compareArrivalTime);

    int currentTime = 0;
    int totalWaitTime = 0;
    int totalRotationTime = 0;

    printf("Gantt Chart:\n");
    for (int i = 0; i < num_processes; i++) {
        if (processes[i].arrival_time > currentTime) {
            currentTime = processes[i].arrival_time;
        }
        
        int wait_time = currentTime - processes[i].arrival_time;
        int rotation_time = wait_time + processes[i].exec_time;
        currentTime += processes[i].exec_time;

        totalWaitTime += wait_time;
        totalRotationTime += rotation_time;

        // Display Gantt chart
        printf("[ %s (%d - %d) ] ", processes[i].pid, currentTime - processes[i].exec_time, currentTime);
    }
    printf("\n");

    printf("Average Wait Time: %.2f\n", (float)totalWaitTime / num_processes);
    printf("Average Rotation Time: %.2f\n", (float)totalRotationTime / num_processes);
}

int main() {
    Process *processes = readProcesses("file1.txt");

    if (processes != NULL && num_processes > 0) {
        fifo(processes);
        free(processes);
    } else {
        printf("Failed to read processes from the file or no processes were found.\n");
    }

    return 0;
}

