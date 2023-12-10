#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char pid[10];
    int arrival_time;
    int exec_time;
    int priority;
} Process;

// Function to trim leading and trailing white spaces
char* trimWhiteSpace(char* str) {
    char* end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

// Inline implementation of readProcesses
Process* readProcesses(const char *filename, int *num_processes) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    int capacity = 10;
    Process *processes = malloc(sizeof(Process) * capacity);
    *num_processes = 0;

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // Trim white space and ignore empty lines and comments
        char* trimmedLine = trimWhiteSpace(line);
        if (trimmedLine[0] == '\0' || trimmedLine[0] == '#') {
            continue;
        }

        if (sscanf(trimmedLine, "%s %d %d %d", processes[*num_processes].pid, 
                  &processes[*num_processes].arrival_time, 
                  &processes[*num_processes].exec_time, 
                  &processes[*num_processes].priority) == 4) {
            (*num_processes)++;
            if (*num_processes >= capacity) {
                capacity *= 2;
                processes = realloc(processes, sizeof(Process) * capacity);
            }
        }
    }

    fclose(file);
    return processes;
}

#endif // PROCESS_H

