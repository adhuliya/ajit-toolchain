#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "aes_block.h"
#include "aes_utils.h"


//
// When was this written
// Who wrote it.
//


// will be set to generate lots of prints.
extern int global_verbose_flag;

// global, used in memory.

EncryptDecryptBlock* aes_ed_block = NULL;

// return 0 if all 3 values read from file.
int readKeyAndAddressMaskFromFile(FILE* fp, uint64_t* k_h, uint64_t* k_l, uint32_t* seed) {
    int n = fscanf(fp, "%" PRIx64 " %" PRIx64 " %" PRIx32, k_h, k_l, seed);
    if (n == 3) {
        fprintf(stderr, "AES keys: %" PRIx64 " %" PRIx64 "\n", *k_h, *k_l);
        fprintf(stderr, "Mask: %" PRIx32 "\n", *seed);
        return 0; // Success
    } else {
        return 1; // Error reading values
    }
}

// Setup encrypt decrypt block.... return 0 on success.
int makeEncryptDecryptBlock (FILE* fp)
{
	aes_ed_block = (EncryptDecryptBlock*) malloc (sizeof (EncryptDecryptBlock));

	uint64_t k_h, k_l;
	uint32_t seed;
	int status = readKeyAndAddressMaskFromFile (fp, &k_h, &k_l, &seed);
	if(status)
	{
		free(aes_ed_block);
		aes_ed_block = NULL;
		return(1);
	}
	
	setupEncryptDecryptBlock (aes_ed_block, k_h, k_l, seed);
	return(0);
}

void setupEncryptDecryptBlock (EncryptDecryptBlock *ed, 
					uint64_t aes_key_h, 
					uint64_t aes_key_l, 
					uint32_t seed)
{
	ed->aes_key_h = aes_key_h;
	ed->aes_key_l = aes_key_l;
	ed->hash_seed = seed;
	//ed->address_mask = address_mask;

	//
	// TODO: calculate and save the round keys!
	//
	uint64_t root_key[2] = {aes_key_h, aes_key_l};
  uint32_t w[44];  //Values obtained for keys
  uint32_t T[11]; //Extra entry used in array for convenience purpose
  
  // Most significant 64 bits
  w[0] = (uint32_t)(root_key[0] >> 32);  // Upper 32 bits of key_value[0]
  w[1] = (uint32_t)(root_key[0]);        // Lower 32 bits of key_value[0]
    
  // Least significant 64 bits
  w[2] = (uint32_t)(root_key[1] >> 32);  // Upper 32 bits of key_value[1]
  w[3] = (uint32_t)(root_key[1]);        // Lower 32 bits of key_value[1]

  

 //generating all the round keys word during key expansion
 uint32_t temp;

  for (int i = 4; i < 44; i++) {
      if (i % 4 == 0) {  
        temp = RotWord(w[i - 1]);
        temp = SubRows(temp);
        temp ^= RCon[(i / 4) - 1]; 
      } else {
        temp = w[i - 1];  
      }
    
    w[i] = w[i - 4] ^ temp;  

    // Print words in blocks of 4
    if (i % 4 == 3) {
        if (global_verbose_flag)
        {
          printf("WORD %d TO %d\n", i - 3, i);
          printf("%08X\n%08X\n%08X\n%08X\n", w[i - 3], w[i - 2], w[i - 1], w[i]);
        }
    }
}

  //Strong back to the ed structure
  int round_index = 0;
  for (int i = 4; i < 44; i += 2) {  
    ed->expanded_round_keys[round_index] = ((uint64_t)w[i] << 32) | w[i + 1];
    round_index++;
  }

  
}

					

void encryptBlock (EncryptDecryptBlock* ed,
			uint64_t data_h, 
			uint64_t data_l,
			uint64_t address,
			uint64_t *cipher_text_h,
			uint64_t *cipher_text_l)
{


	// TODO: implement AES transformation
	//      1. hash the address 
	//      2. xor plain text with hash
	//      2. encrypt the xor result
	// Initialize State Matrix
	
	uint64_t hash[2] = {0, 0};
	MurmurHash3_x64_128(&address, 8, ed->hash_seed, hash);
  uint64_t iv_msb = data_h ^ hash[0];
  uint64_t iv_lsb = data_l ^ hash[1];
  
  
  uint64_t iv_msb_out = 0;
  uint64_t iv_lsb_out = 0;
  
    
  uint8_t state_matrix[STATE_ROWS][STATE_COLS];
  uint8_t transform_matrix[STATE_ROWS][STATE_COLS];
    
  // Load IV into state matrix in column-wise fashion
  for (int i = 0; i < 8; i++) {
    state_matrix[i % STATE_ROWS][i / STATE_ROWS] = (iv_msb >> (56 - 8 * i)) & 0xFF;
    state_matrix[(i + 8) % STATE_ROWS][(i + 8) / STATE_ROWS] = (iv_lsb >> (56 - 8 * i)) & 0xFF;
  }

  
  //Pre Round Transformation
  AddRoundKey(ed->aes_key_h, ed->aes_key_l, state_matrix, transform_matrix);
  
  
  //Round 1 to 10
  for (int round = 0; round < 10; round++) {
    SubBytes(transform_matrix, transform_matrix);
    ShiftRows(transform_matrix);
    if (round < 9) {  // MixColumns is skipped in the final round (Round 10)
        MixColumns(transform_matrix);
    }
    AddRoundKey(ed->expanded_round_keys[2 * round], 
                ed->expanded_round_keys[2 * round + 1], 
                transform_matrix, transform_matrix);
  }

  
  for (int i = 0; i < 8; i++) {
    iv_msb_out |= ((uint64_t)transform_matrix[i % STATE_ROWS][i / STATE_ROWS] << (56 - 8 * i));
    iv_lsb_out |= ((uint64_t)transform_matrix[(i + 8) % STATE_ROWS][(i + 8) / STATE_ROWS] << (56 - 8 * i));
  }
  
	*cipher_text_h = iv_msb_out;
	*cipher_text_l = iv_lsb_out;
	
}

void decryptBlock (EncryptDecryptBlock* ed,
			uint64_t cipher_text_h, 
			uint64_t cipher_text_l,
			uint64_t address,
			uint64_t *data_h,
			uint64_t *data_l)
{
	// TODO: implement AES transformation
	//       1. decrypt using round keys, calculate address-hash
	//       2. xor with address hash
	//       this should give us the decrypted plain text.

	
  uint64_t iv_msb = cipher_text_h;
  uint64_t iv_lsb = cipher_text_l;
  uint64_t iv_msb_out = 0;
  uint64_t iv_lsb_out = 0;
  
    
  uint8_t state_matrix[STATE_ROWS][STATE_COLS];
  uint8_t transform_matrix[STATE_ROWS][STATE_COLS];
    
  // Load IV into state matrix in column-wise fashion
  for (int i = 0; i < 8; i++) {
    state_matrix[i % STATE_ROWS][i / STATE_ROWS] = (iv_msb >> (56 - 8 * i)) & 0xFF;
    state_matrix[(i + 8) % STATE_ROWS][(i + 8) / STATE_ROWS] = (iv_lsb >> (56 - 8 * i)) & 0xFF;
  }

  
  // Round 10 (special case: no InverseMixColumns)
  AddRoundKey(ed->expanded_round_keys[18], ed->expanded_round_keys[19], state_matrix, transform_matrix);
  InverseShiftRows(transform_matrix);
  InverseSubBytes(transform_matrix, transform_matrix);

  // Rounds 9 to 1
  for (int round = 8; round >= 0; round--) {
    AddRoundKey(ed->expanded_round_keys[2 * round], ed->expanded_round_keys[2 * round + 1], transform_matrix, transform_matrix);
    InverseMixColumns(transform_matrix);
    InverseShiftRows(transform_matrix);
    InverseSubBytes(transform_matrix, transform_matrix);
  }

  //Post Round Transformation
  AddRoundKey(ed->aes_key_h, ed->aes_key_l, transform_matrix, transform_matrix);
  
  uint64_t hash[2] = {0, 0};
	MurmurHash3_x64_128(&address, 8, ed->hash_seed, hash);
	
	
	for (int i = 0; i < 8; i++) {
    iv_msb_out |= ((uint64_t)transform_matrix[i % STATE_ROWS][i / STATE_ROWS] << (56 - 8 * i));
    iv_lsb_out |= ((uint64_t)transform_matrix[(i + 8) % STATE_ROWS][(i + 8) / STATE_ROWS] << (56 - 8 * i));
  }
  
  *data_h = iv_msb_out ^ hash[0];
  *data_l = iv_lsb_out ^ hash[1];
	

}
