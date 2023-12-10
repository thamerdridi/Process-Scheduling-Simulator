#ifndef SRT_H
#define SRT_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "process.h"

// SRT scheduling function
static inline void srt(Process *processes, int n) {
    int currentTime = 0, completed = 0;
    int remainingTime[n];
    int lastProcess = -1;
    int totalWaitTime = 0, totalTurnaroundTime = 0;

    // Initialize remaining times
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].exec_time;
    }

    // Enhanced Gantt Chart display
    printf("\n┌─────────────────────────────┐\n");
    printf("│       Gantt Chart          │\n");
    printf("└─────────────────────────────┘\n");
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

        if (lastProcess != shortest) {
            if (lastProcess != -1) {
                printf("%d)] ", currentTime);
            }
            printf("[%s (%d-", processes[shortest].pid, currentTime);
            lastProcess = shortest;
        }

        remainingTime[shortest]--;
        currentTime++;

        if (remainingTime[shortest] == 0) {
            completed++;
            printf("%d)] ", currentTime);
            lastProcess = -1;

            int turnaroundTime = currentTime - processes[shortest].arrival_time;
            int waitingTime = turnaroundTime - processes[shortest].exec_time;
            totalWaitTime += waitingTime;
            totalTurnaroundTime += turnaroundTime;
        }
    }
    printf("\n");

    // Enhanced average time display
    printf("\n┌─────────────────────────────┐\n");
    printf("| Average Wait Time: %.2f     |\n", (float)totalWaitTime / n);
    printf("| Average Turnaround Time: %.2f|\n", (float)totalTurnaroundTime / n);
    printf("└─────────────────────────────┘\n");
}

#endif // SRT_H

