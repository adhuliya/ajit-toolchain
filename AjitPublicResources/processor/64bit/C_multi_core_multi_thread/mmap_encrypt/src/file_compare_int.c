#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PROGRESS_BAR_WIDTH 50  // Width of the progress bar

typedef struct {
    uint64_t address;  // Address as an integer
    uint8_t value;     // Value as an integer (0-255)
} MemoryEntry;

// Function to load key-value pairs from the original file
MemoryEntry* loadOriginalFile(const char *filename, int *entry_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "[ERROR] Cannot open file: %s\n", filename);
        exit(1);
    }

    int capacity = 10;
    *entry_count = 0;
    MemoryEntry *entries = (MemoryEntry *)malloc(capacity * sizeof(MemoryEntry));
    if (!entries) {
        fprintf(stderr, "[ERROR] Memory allocation failed!\n");
        exit(1);
    }

    char address_str[20], value_str[5];
    while (fscanf(file, "%s %s", address_str, value_str) == 2) {
        if (*entry_count >= capacity) {
            capacity *= 2;
            entries = (MemoryEntry *)realloc(entries, capacity * sizeof(MemoryEntry));
            if (!entries) {
                fprintf(stderr, "[ERROR] Memory reallocation failed!\n");
                exit(1);
            }
        }

        entries[*entry_count].address = strtoull(address_str, NULL, 16);
        entries[*entry_count].value = (uint8_t)strtoul(value_str, NULL, 16);
        (*entry_count)++;
    }

    fclose(file);
    return entries;
}

// Function to free allocated memory
void freeMemoryEntries(MemoryEntry *entries) {
    free(entries);
}

// Function to count total lines in the decrypted file for progress tracking
int countLines(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "[ERROR] Cannot open file: %s\n", filename);
        exit(1);
    }

    int lines = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        lines++;
    }

    fclose(file);
    return lines;
}

// Function to display progress as a percentage with a progress bar
void displayProgress(int current, int total) {
    int percent = (current * 100) / total;
    int filled = (current * PROGRESS_BAR_WIDTH) / total;

    printf("\r[PROGRESS] [");
    for (int i = 0; i < PROGRESS_BAR_WIDTH; i++) {
        if (i < filled) {
            printf("#");
        } else {
            printf("-");
        }
    }
    printf("] %d%%", percent);
    fflush(stdout);
}

// Function to compare the decrypted file with the original data
int compareFiles(const char *decrypted_file, MemoryEntry *original_data, int original_count) {
    FILE *file = fopen(decrypted_file, "r");
    if (!file) {
        fprintf(stderr, "[ERROR] Cannot open decrypted file: %s\n", decrypted_file);
        exit(1);
    }

    int total_lines = countLines(decrypted_file);  // Get total lines for progress tracking
    uint64_t dec_address;
    uint8_t dec_value;
    int mismatches = 0, processed_lines = 0;

    char dec_address_str[20], dec_value_str[5];

    while (fscanf(file, "%s %s", dec_address_str, dec_value_str) == 2) {
        processed_lines++;

        dec_address = strtoull(dec_address_str, NULL, 16);
        dec_value = (uint8_t)strtoul(dec_value_str, NULL, 16);

        int found = 0;

        // Compare with original data
        for (int i = 0; i < original_count; i++) {
            if (dec_address == original_data[i].address) {
                found = 1;
                if (dec_value != original_data[i].value) {
                    printf("\n[MISMATCH] Address: 0x%lx | Original: 0x%02x | Decrypted: 0x%02x\n",
                           dec_address, original_data[i].value, dec_value);
                    mismatches++;
                }
                break;
            }
        }

        // If address not found, value should be zero
        if (!found && dec_value != 0) {
            printf("\n[MISMATCH] Extra Address: 0x%lx | Expected: 0x00 | Found: 0x%02x\n",
                   dec_address, dec_value);
            mismatches++;
        }

        // Display progress every 1% or after the first line
        if (processed_lines % (total_lines / 100 == 0 ? 1 : total_lines / 100) == 0 || processed_lines == 1) {
            displayProgress(processed_lines, total_lines);
        }
    }

    fclose(file);

    // Final mismatch report
    printf("\n------------------------------------------------------------\n");
    printf("[RESULT] Total lines compared: %d\n", total_lines);
    printf("[RESULT] Total mismatches found: %d\n", mismatches);
    if (mismatches == 0) {
        printf("[SUCCESS] Decrypted file matches the original file!\n");
    } else {
        printf("[WARNING] Decrypted file has mismatches with the original!\n");
    }
    printf("------------------------------------------------------------\n");

    return mismatches;
}

// Main function to load and compare files
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <original_file> <decrypted_file>\n", argv[0]);
        return 1;
    }

    const char *original_file = argv[1];
    const char *decrypted_file = argv[2];

    int original_count = 0;
    MemoryEntry *original_data = loadOriginalFile(original_file, &original_count);

    compareFiles(decrypted_file, original_data, original_count);

    freeMemoryEntries(original_data);

    return 0;
}
