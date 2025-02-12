#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include "aes_block.h"
#include "aes_utils.h"

// Global verbose flag (1 = print debug info, 0 = silent mode)
int verbose = 1;  
int global_verbose_flag = 0;
extern EncryptDecryptBlock* aes_ed_block;

// Function to get memory bounds from file, this function gets the first and the last memory address and makes sure they'r divisible by 0xF
void getMemoryRange(const char *filename, uint64_t *start, uint64_t *end) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        exit(1);
    }

    uint64_t firstAddr = 0, lastAddr = 0;
    uint8_t value;

    // Read the first valid address
    if (fscanf(fp, "%" SCNx64 " %hhx", &firstAddr, &value) != 2) {
        fprintf(stderr, "Error: Failed to read first address from %s\n", filename);
        fclose(fp);
        exit(1);
    }

    lastAddr = firstAddr;

    uint64_t tempAddr;
    while (fscanf(fp, "%" SCNx64 " %hhx", &tempAddr, &value) == 2) {
        lastAddr = tempAddr;
    }

    fclose(fp);

    // **Ensure first address aligns DOWN to 16-byte boundary**
    *start = firstAddr & ~0xFULL;

    uint64_t size = lastAddr - *start + 1;

    if (size % 16 != 0) {
        lastAddr += (16 - (size % 16));  // Only add the necessary padding
    }

   
    // **Align last address UP to nearest 16-byte boundary**
    *end = (lastAddr);

    // Debugging Prints
    if (verbose) {
        printf("[DEBUG] First Address (Original): 0x%lx\n", firstAddr);
        printf("[DEBUG] Last Address (Original): 0x%lx\n", lastAddr);
        printf("[DEBUG] First Address (Aligned): 0x%lx\n", *start);
        printf("[DEBUG] Last Address (Aligned): 0x%lx\n", *end);
        printf("Aligned Memory Range: 0x%lx - 0x%lx\n", *start, *end);
    }
}



// Function to allocate memory create an array based on the first and last addresses, used calloc becuase auto assign to zero
uint8_t *allocateMemory(uint64_t firstAddr, uint64_t lastAddr) {
    size_t size = lastAddr - firstAddr + 1;
    uint8_t *memory = (uint8_t *)calloc(size, sizeof(uint8_t));

    if (!memory) {
        fprintf(stderr, "Error: Memory allocation failed!\n");
        exit(1);
    }

    if (verbose) {
        printf("Allocated memory: %zu bytes (0x%lx - 0x%lx)\n", size, firstAddr, lastAddr);
    }

    return memory;
}

// Function to load memory from file, file to array
void loadMemoryFile(const char *filename, uint8_t *memory, uint64_t firstAddr) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        exit(1);
    }

    uint64_t addr;
    uint8_t value;

    while (fscanf(fp, "%" SCNx64 " %hhx", &addr, &value) == 2) {
        memory[addr - firstAddr] = value;
    }

    fclose(fp);
}

// Convert 8-bit array to 64-bit words in big endian, direct conversion didnt seem to give appropriate results, used bit manipiulation to get this
uint64_t *convertTo64BitWords(uint8_t *memory, uint64_t firstAddr, uint64_t lastAddr) {
    size_t size = lastAddr - firstAddr + 1;
    size_t numWords = (size + 7) / 8;
    uint64_t *wordArray = (uint64_t *)calloc(numWords, sizeof(uint64_t));

    if (!wordArray) {
        fprintf(stderr, "Error: Memory allocation for uint64_t array failed!\n");
        exit(1);
    }

    for (size_t i = 0; i < numWords; i++) {
        uint64_t word = 0;
        for (size_t j = 0; j < 8; j++) {
            size_t byteIndex = i * 8 + j;
            if (byteIndex < size) {
                word |= ((uint64_t)memory[byteIndex]) << ((7 - j) * 8);
            }
        }
        wordArray[i] = word;

        if (verbose) {
            printf("Word %zu: 0x%016" PRIx64 "\n", i, word);
        }
    }

    return wordArray;
}

// Convert 64-bit words back to 8-bit array, for final conversion and printing
uint8_t *convertTo8BitArray(uint64_t *wordArray, size_t numWords, uint64_t firstAddr, uint64_t lastAddr) {
    size_t size = lastAddr - firstAddr + 1;
    uint8_t *byteArray = (uint8_t *)calloc(size, sizeof(uint8_t));

    if (!byteArray) {
        fprintf(stderr, "Error: Memory allocation for uint8_t array failed!\n");
        exit(1);
    }

    for (size_t i = 0; i < numWords; i++) {
        for (size_t j = 0; j < 8; j++) {
            size_t byteIndex = i * 8 + j;
            if (byteIndex < size) {
                byteArray[byteIndex] = (wordArray[i] >> ((7 - j) * 8)) & 0xFF;
            }
        }
    }

    return byteArray;
}



void initializeAES(const char *keyfile) {
    FILE *key_fp = fopen(keyfile, "r");
    if (!key_fp) {
        fprintf(stderr, "Error: Could not open key file %s\n", keyfile);
        exit(1);
    }

    int status = makeEncryptDecryptBlock(key_fp);
    fclose(key_fp);

    if (status != 0) {
        fprintf(stderr, "Failed to initialize EncryptDecryptBlock.\n");
        exit(1);
    }

    if (verbose) printf("[DEBUG] AES Key Initialized Successfully!\n");
}

//A function to convert the 8 bit alighned array back to a similar file format with padding entries for encryption
void writeByteArrayToFile(const char *filename, uint8_t *byteArray, uint64_t firstAddr, uint64_t lastAddr) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file %s for writing\n", filename);
        exit(1);
    }

    for (uint64_t addr = firstAddr; addr <= lastAddr; addr++) {
        fprintf(fp, "%" PRIx64 " %02x\n", addr, byteArray[addr - firstAddr]);
    }

    fclose(fp);
    printf("File written successfully: %s\n", filename);
}


void encryptMemory(uint8_t *memory, uint64_t firstAddr, uint64_t lastAddr, const char *filename) {
    size_t size = lastAddr - firstAddr + 1;
    uint64_t *wordArray = convertTo64BitWords(memory, firstAddr, lastAddr);
    size_t numWords = size / 8;  // Number of 64-bit words

    for (size_t i = 0; i < numWords; i += 2) {  // Process two words per AES block
        encryptBlock(aes_ed_block, wordArray[i], wordArray[i+1], firstAddr + (i * 8), &wordArray[i], &wordArray[i+1]);
    }

    uint8_t *encryptedMemory = convertTo8BitArray(wordArray, numWords, firstAddr, lastAddr);
    writeByteArrayToFile(filename, encryptedMemory, firstAddr, lastAddr);

    free(wordArray);
    free(encryptedMemory);

    if (verbose) printf("[DEBUG] Memory Encrypted Successfully!\n");
}

void decryptMemory(uint8_t *memory, uint64_t firstAddr, uint64_t lastAddr, const char *filename) {
    size_t size = lastAddr - firstAddr + 1;
    uint64_t *wordArray = convertTo64BitWords(memory, firstAddr, lastAddr);
    size_t numWords = size / 8;  // Number of 64-bit words

    for (size_t i = 0; i < numWords; i += 2) {  // Process two words per AES block
        decryptBlock(aes_ed_block, wordArray[i], wordArray[i+1], firstAddr + (i * 8), &wordArray[i], &wordArray[i+1]);
    }

    uint8_t *decryptedMemory = convertTo8BitArray(wordArray, numWords, firstAddr, lastAddr);
    writeByteArrayToFile(filename, decryptedMemory, firstAddr, lastAddr);

    free(wordArray);
    free(decryptedMemory);

    if (verbose) printf("[DEBUG] Memory Decrypted Successfully!\n");
}





void printUsage(const char *program_name) {
    printf("Usage: %s <-e/-d> <encrypted_file> <decrypted_file> <key_file>\n", program_name);
    printf("  <-e/-d> : encrypt or decrypt?\n");
    printf("  <encrypted_file> : Path to the encrypted input file.\n");
    printf("  <decrypted_file> : Path to the decrypted output file.\n");
    printf("  <key_file>       : Path to the AES key file.\n");
}



int main(int argc, char *argv[]) {
    // Check for proper number of arguments
    if (argc != 5) {
        fprintf(stderr, "Error: Invalid number of arguments.\n");
        printUsage(argv[0]);
        return 1;
    }

    // Read mode flag
    const char *mode = argv[1];
    const char *input_file = argv[2];
    const char *output_file = argv[3];
    const char *keyfile = argv[4];

    // Initialize AES
    initializeAES(keyfile);

    // Get memory range and allocate memory
    uint64_t firstAddr, lastAddr;
    getMemoryRange(input_file, &firstAddr, &lastAddr);
    uint8_t *memory = allocateMemory(firstAddr, lastAddr);
    loadMemoryFile(input_file, memory, firstAddr);

    // Perform encryption or decryption based on the mode
    if (strcmp(mode, "-e") == 0) {
        printf("[INFO] Performing encryption...\n");
        encryptMemory(memory, firstAddr, lastAddr, output_file);
        printf("[SUCCESS] Encryption completed.\n");
    } else if (strcmp(mode, "-d") == 0) {
        printf("[INFO] Performing decryption...\n");
        decryptMemory(memory, firstAddr, lastAddr, output_file);
        printf("[SUCCESS] Decryption completed.\n");
    } else {
        fprintf(stderr, "Error: Invalid mode flag '%s'. Use -e for encryption or -d for decryption.\n", mode);
        printUsage(argv[0]);
        free(memory);
        return 1;
    }
}


