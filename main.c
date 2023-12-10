#include "generator.h"
#include "fifo.h"
#include "srt.h"
#include "RR.h"
#include "priority.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void printSeparator() {
    printf("------------------------------------------------\n");
}

void printGanttChartHeader() {
    printf("Gantt Chart:\n");
    printSeparator();
}

void printAlgorithmOutput(const char* algorithmName) {
    printSeparator();
    printf("%s Algorithm Output:\n", algorithmName);
    printSeparator();
}

int main() {
    printf("Hello and welcome to the C Process Scheduling Simulator!\n");
    printSeparator();

    int num_processes;
    printf("How many processes do you want to generate? ");
    scanf("%d", &num_processes);
    generate_process_file(num_processes); // This will create 'file1.txt'

    char choice[10];
    int quantum;
    Process *processes;
    int n;

    do {
        printf("\nDo you want to simulate these processes [FIFO per Default] (yes/no/another)? ");
        scanf("%s", choice);
        for (int i = 0; choice[i]; i++) choice[i] = tolower(choice[i]);

        if (strcmp(choice, "yes") == 0 || strcmp(choice, "another") == 0) {
            if (strcmp(choice, "yes") == 0) {
                strcpy(choice, "fifo");
            } else {
                printf("Choose an algorithm (FIFO, SRT, RR, Priority): ");
                scanf("%s", choice);
                for (int i = 0; choice[i]; i++) choice[i] = tolower(choice[i]);
            }

            processes = readProcesses("file1.txt", &n);
            printAlgorithmOutput(choice);

            if (strcmp(choice, "fifo") == 0) {
                fifo(processes, n);
            } else if (strcmp(choice, "srt") == 0) {
                srt(processes, n);
            } else if (strcmp(choice, "rr") == 0) {
                printf("Enter Quantum Number: ");
                scanf("%d", &quantum);
                roundRobin(processes, n, quantum);
            } else if (strcmp(choice, "priority") == 0) {
                priorityScheduling(processes, n);
            } else {
                printf("Algorithm not recognized. Please try again.\n");
                free(processes);
                continue;
            }

            free(processes);
        } else if (strcmp(choice, "no") != 0) {
            printf("Invalid choice. Please try again.\n");
        }
    } while (strcmp(choice, "no") != 0);

    printf("Thank you for using the C Process Scheduling Simulator!\n");

    return 0;
}

