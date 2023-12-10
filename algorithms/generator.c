#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_process_file(int num_processes) {
    static int file_counter = 1;
    char filename[20];

    // Create a filename
    sprintf(filename, "file%d.txt", file_counter++);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    srand((unsigned int)time(NULL));

    // P0 with a fixed arrival time of 0
    fprintf(file, "P0 0 %d %d\n", rand() % 10 + 1, rand() % 10 + 1);

    // Generate the rest of the processes
    for (int i = 1; i < num_processes; i++) {
        int arrival_time = rand() % 11; // Random arrival time [0,10]
        int exec_time = rand() % 10 + 1; // Execution time [1,10]
        int priority = rand() % 10 + 1; // Priority [1,10]
        fprintf(file, "P%d %d %d %d\n", i, arrival_time, exec_time, priority);
    }

    fclose(file);
    printf("Generated %s with %d processes.\n", filename, num_processes);
}

int main() {
    int num_processes;
    printf("Enter the number of processes to generate: ");
    scanf("%d", &num_processes);

    // Validate input
    if(num_processes > 0) {
        generate_process_file(num_processes);
    } else {
        printf("Number of processes must be greater than 0.\n");
    }
    return 0;
}
