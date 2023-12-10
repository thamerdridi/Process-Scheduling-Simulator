#ifndef FIFO_H
#define FIFO_H

#include <stdio.h>
#include <stdlib.h>
#include "process.h"

// Function to compare arrival times (used in qsort)
static inline int compareArrivalTime(const void *a, const void *b) {
    Process *processA = (Process *)a;
    Process *processB = (Process *)b;
    return processA->arrival_time - processB->arrival_time;
}

// FIFO scheduling function
static inline void fifo(Process *processes, int num_processes) {
    qsort(processes, num_processes, sizeof(Process), compareArrivalTime);

    int currentTime = 0;
    int totalWaitTime = 0;
    int totalRotationTime = 0;

    // Enhanced Gantt Chart display
    printf("\n┌─────────────────────────────┐\n");
    printf("│       Gantt Chart          │\n");
    printf("└─────────────────────────────┘\n");
    for (int i = 0; i < num_processes; i++) {
        if (processes[i].arrival_time > currentTime) {
            currentTime = processes[i].arrival_time;
        }

        int wait_time = currentTime - processes[i].arrival_time;
        int rotation_time = wait_time + processes[i].exec_time;
        currentTime += processes[i].exec_time;

        totalWaitTime += wait_time;
        totalRotationTime += rotation_time;

        printf("| %-4s (%d-%d) ", processes[i].pid, currentTime - processes[i].exec_time, currentTime);
    }
    printf("|\n");

    // Enhanced average time display
    printf("\n┌─────────────────────────────┐\n");
    printf("| Average Wait Time: %.2f     |\n", (float)totalWaitTime / num_processes);
    printf("| Average Rotation Time: %.2f |\n", (float)totalRotationTime / num_processes);
    printf("└─────────────────────────────┘\n");
}

#endif // FIFO_H

