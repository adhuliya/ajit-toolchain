#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include "aes_block.h"
#include "aes_utils.h"

/*
	This is a test program to confirm the functionality 
	of the AES block.   Checks round key generation,
	encryption and decryption.

	The reference data used for these checks was obtained
	from NIST and the book .... by William Stalling.....

	// TODO: more (relevant) details.
  
*/

int global_verbose_flag = 0;
extern EncryptDecryptBlock* aes_ed_block;

int main(int argc, char* argv[]) {


    if(argc < 2)
    {
	fprintf(stderr,"Usage: %s <test-data-file>\n", argv[0]);
	return(1);
    }


    // Step 2: Open the file for reading
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "Error: could not open test data file %s\n", argv[0]);
        return 1;
    }

    // Step 3: Test makeEncryptDecryptBlock
    int status = makeEncryptDecryptBlock(fp);
    fclose(fp);

    // Step 4: Verify the output
    if (status == 0) {
        printf("EncryptDecryptBlock initialized successfully!\n");
        printf("High Key:  0x%" PRIx64 "\n", aes_ed_block->aes_key_h);
        printf("Low Key:   0x%" PRIx64 "\n", aes_ed_block->aes_key_l);

        // Testing key exp
        printf("First Round Key:  0x%" PRIx64 "\n", aes_ed_block->expanded_round_keys[0]);
        printf("Second Round Key: 0x%" PRIx64 "\n", aes_ed_block->expanded_round_keys[1]);
        printf("D Round Key:  0x%" PRIx64 "\n", aes_ed_block->expanded_round_keys[16]);
        printf("D Round Key: 0x%" PRIx64 "\n", aes_ed_block->expanded_round_keys[17]);
        printf("C Round Key:  0x%" PRIx64 "\n", aes_ed_block->expanded_round_keys[18]);
        printf("C Round Key: 0x%" PRIx64 "\n", aes_ed_block->expanded_round_keys[19]);

	//
	// TODO: What about the other keys??
	//

    } else {
        printf("Failed to initialize EncryptDecryptBlock.\n");
    }
    
    // Step 3: Define test plaintext
    
    uint64_t plaintext_high = 0x0123456789abcdef; // Example plaintext high 64 bits
    uint64_t plaintext_low = 0xfedcba9876543210;  // Example plaintext low 64 bits
    uint64_t ciphertext_high = 0;                // Output high
    uint64_t ciphertext_low = 0;                 // Output low
    uint64_t pt_high2 = 0;
    uint64_t pt_low2 = 0;

    // Step 4: Encrypt the block
    encryptBlock(aes_ed_block, plaintext_high, plaintext_low, 10, &ciphertext_high, &ciphertext_low);

    // Step 5: Print results
    printf("Plaintext:  High: 0x%" PRIx64 " Low: 0x%" PRIx64 "\n", plaintext_high, plaintext_low);
    printf("Ciphertext: High: 0x%" PRIx64 " Low: 0x%" PRIx64 "\n", ciphertext_high, ciphertext_low);

    decryptBlock(aes_ed_block, ciphertext_high, ciphertext_low, 10, &pt_high2, &pt_low2);
    
    printf("Plaintext 2:  High: 0x%" PRIx64 " Low: 0x%" PRIx64 "\n", pt_high2, pt_low2);
    
    // Step 7: Clean up
    free(aes_ed_block);
    aes_ed_block = NULL;

    return 0;
}
