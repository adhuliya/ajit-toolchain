#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <string.h>
#include "swizzler.h"
#include "memory.h"
#include "measures.h"

#define START_ADDRESS 16
#define END_ADDRESS 512*16
SwizzlerRecord *Sr = NULL;
int global_verbose_flag = 0;


#define BUFFER_SIZE 256

// Function to process the input file and output the desired result
void process_file(const char* inputFileName, const char* outputFileName) {
    FILE *inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        perror("Error opening input file");
        return;
    }

    // Open the output file
    FILE *outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        perror("Error creating output file");
        fclose(inputFile);
        return;
    }

    char line[BUFFER_SIZE];

    // Read the input file line by line
    while (fgets(line, sizeof(line), inputFile)) {
        // Skip lines that do not match the format we expect
        if (strncmp(line, ">>>>M", 5) != 0) {
            continue;
        }

        // Find the second column (skip the first part which is ">>>>M <number> ")
        char* token = strtok(line, " ");
        token = strtok(NULL, " "); // Skip the first column
        token = strtok(NULL, " "); // Second column

        if (token) {
            // Remove the "0x" prefix and write the remaining value to the output file
            if (strncmp(token, "0x", 2) == 0) {
                token += 2;  // Skip the "0x" part
            }

            fprintf(outputFile, "%s\n", token);
        }
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);
}

int main(int argc, char *argv[]) {
printf("Hi \n");
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    allocateMemory(24);
    
    double cv_values[1000]; // Store CV for 100 iterations
    double dp_values[1000];
    double avg_cv, avg_dp = 0.0;
    srand(clock());
    
    printf("Cth is %d, no_sets is %d \n", Cth, no_sets);
    for (int iteration = 0; iteration < 1000; iteration++) {

        SwizzlerRecord swizz;
        Sr = &swizz;
        initSwizzler(Sr);
	if(iteration % 200 == 0){printf("%d \n", iteration);}
        uint32_t address;
        uint64_t data_h_write, data_l_write;

        FILE* traceFile = fopen("trace.txt", "w");
        FILE* mappedFile = fopen("mapped.txt", "w");
        if (traceFile == NULL || mappedFile == NULL) {
            perror("Failed to open trace file");
            return EXIT_FAILURE;
        }
        setMemoryTraceFile(traceFile);

        for (uint32_t i = 0; i <= 7; i++) {
            for (address = START_ADDRESS; address <= END_ADDRESS; address = address + 16) {
                data_h_write = address + i;  // High 64-bits set to 0
                data_l_write = address + i + 1;  // Low 64-bits set to address
                setQuadWordInMemory(address, data_h_write, data_l_write);
            }
        }

        // Call measure1 to calculate the CV value
        fclose(mappedFile);
        fclose(traceFile);
        //printf("Milestone 1\n");
        process_file("trace.txt", "addr_trace.txt");
        cv_values[iteration] = measure1("addr_trace.txt");
		dp_values[iteration] = measure2("addr_trace.txt","base.txt");
    }

    // Calculate the average CV and DP
    for (int i = 0; i < 1000; i++) {
        avg_cv += cv_values[i];
        avg_dp += dp_values[i];
    }
    avg_cv /= 1000; 
	avg_dp /= 1000;
	
    // Append avg_cv to the file specified in argv[1]
    FILE* outputFile = fopen(argv[1], "a");  // Open the file in append mode
    if (outputFile == NULL) {
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }
    fprintf(outputFile, "Average CV: %f\n", avg_cv);  // Append avg_cv to the file
    fprintf(outputFile, "Average DP: %f\n", avg_dp);  // Append avg_cv to the file
    printf("average CV: %f\n", avg_cv);
    printf("average DP: %f\n", avg_dp);
    fclose(outputFile);

    return 0;
}

