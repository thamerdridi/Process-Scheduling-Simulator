#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline void generate_process_file(int num_processes) {
    static int file_counter = 1;
    char filename[20];

    
    sprintf(filename, "file%d.txt", file_counter++);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    srand((unsigned int)time(NULL));

   
    printf("\nGenerated Processes:\n");
    printf("PID\tArrival Time\tExecution Time\tPriority\n");
    printf("-----------------------------------------------\n");

    
    int p0_exec_time = rand() % 10 + 1;
    int p0_priority = rand() % 10 + 1;
    fprintf(file, "P0 0 %d %d\n", p0_exec_time, p0_priority);
    printf("P0\t0\t\t%d\t\t%d\n", p0_exec_time, p0_priority);

    
    for (int i = 1; i < num_processes; i++) {
        int arrival_time = rand() % 11; 
        int exec_time = rand() % 10 + 1; 
        int priority = rand() % 10 + 1; 
        fprintf(file, "P%d %d %d %d\n", i, arrival_time, exec_time, priority);
        printf("P%d\t%d\t\t%d\t\t%d\n", i, arrival_time, exec_time, priority);
    }

    fclose(file);
    printf("\nProcess data generated in: %s\n", filename);
}

#endif 
