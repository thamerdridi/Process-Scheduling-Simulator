#ifndef PRIORITY_H
#define PRIORITY_H

#include <stdio.h>
#include <stdlib.h>
#include "process.h"

// Priority scheduling function
static inline void priorityScheduling(Process *processes, int n) {
    int currentTime = 0, completed = 0;
    int lastProcess = -1;
    int totalWaitTime = 0, totalTurnaroundTime = 0;
    int running = -1; // Index of the currently running process

    // Enhanced Gantt Chart display
    printf("\n┌─────────────────────────────┐\n");
    printf("│       Gantt Chart          │\n");
    printf("└─────────────────────────────┘\n");
    while (completed < n) {
        int highestPriority = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= currentTime && processes[i].exec_time > 0) {
                if (highestPriority == -1 || processes[i].priority > processes[highestPriority].priority) {
                    highestPriority = i;
                    running = i;
                }
            }
        }

        if (highestPriority == -1) {
            currentTime++;
            continue;
        }

        if (lastProcess != running) {
            if (lastProcess != -1) {
                printf("%d)] ", currentTime);
            }
            printf("[%s (%d-", processes[running].pid, currentTime);
            lastProcess = running;
        }

        processes[running].exec_time--;
        currentTime++;

        if (processes[running].exec_time == 0) {
            printf("%d)] ", currentTime);
            completed++;
            totalWaitTime += currentTime - processes[running].arrival_time - processes[running].exec_time;
            totalTurnaroundTime += currentTime - processes[running].arrival_time;
            lastProcess = -1;
        }
    }
    printf("|\n");

    // Enhanced average time display
    printf("\n┌─────────────────────────────┐\n");
    printf("| Average Wait Time: %.2f     |\n", totalWaitTime / (float)n);
    printf("| Average Turnaround Time: %.2f|\n", totalTurnaroundTime / (float)n);
    printf("└─────────────────────────────┘\n");
}

#endif // PRIORITY_H

