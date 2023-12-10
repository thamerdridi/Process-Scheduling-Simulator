#ifndef RR_H
#define RR_H

#include <stdio.h>
#include <stdlib.h>
#include "process.h"


static inline void roundRobin(Process *processes, int n, int quantum) {
    int *remainingTime = malloc(n * sizeof(int));
    int currentTime = 0, totalWaitTime = 0, totalTurnaroundTime = 0, completed = 0;
    int *waitTime = malloc(n * sizeof(int));
    int *turnaroundTime = malloc(n * sizeof(int));
    int *isCompleted = calloc(n, sizeof(int));

   
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].exec_time;
        waitTime[i] = -1;
    }

    printf("\n┌─────────────────────────────┐\n");
    printf("│       Gantt Chart          │\n");
    printf("└─────────────────────────────┘\n");
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && processes[i].arrival_time <= currentTime) {
                if (waitTime[i] == -1) {
                    waitTime[i] = (currentTime > processes[i].arrival_time) ? (currentTime - processes[i].arrival_time) : 0;
                }

                if (remainingTime[i] > 0) {
                    printf("| %-4s ", processes[i].pid);
                    int execTime = (remainingTime[i] < quantum) ? remainingTime[i] : quantum;
                    remainingTime[i] -= execTime;
                    currentTime += execTime;
                    printf("(%d-%d) ", currentTime - execTime, currentTime);

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

    
    printf("\n┌─────────────────────────────┐\n");
    printf("| Average Wait Time: %.2f     |\n", (float)totalWaitTime / n);
    printf("| Average Turnaround Time: %.2f|\n", (float)totalTurnaroundTime / n);
    printf("└─────────────────────────────┘\n");

    free(remainingTime);
    free(waitTime);
    free(turnaroundTime);
    free(isCompleted);
}

#endif 
