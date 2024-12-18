#ifndef __aes_block_h___
#define __aes_block_h___

typedef struct __EncryptDecryptBlock {
	// AES key
	uint64_t aes_key_h;
	uint64_t aes_key_l;
  uint32_t hash_seed;
	uint64_t expanded_round_keys[20];

} EncryptDecryptBlock;


// Setup encrypt decrypt block.... return 0 on success.
int  makeEncryptDecryptBlock (FILE* fp);
int  readKeyAndAddressMaskFromFile (FILE* fp, uint64_t* k_h, uint64_t* k_l, uint32_t* seed);

// Calculate the round keys here..
void setupEncryptDecryptBlock (EncryptDecryptBlock *ed, 
					uint64_t aes_key_h, 
					uint64_t aes_key_l,
					uint32_t seed);
					
void encryptBlock (EncryptDecryptBlock* ed,
			uint64_t data_h, 
			uint64_t data_l,
			uint64_t address,
			uint64_t *cipher_text_h,
			uint64_t *cipher_text_l);
			
void decryptBlock (EncryptDecryptBlock* ed,
			uint64_t cipher_text_h, 
			uint64_t cipher_text_l,
			uint64_t address,
			uint64_t *data_h,
			uint64_t *data_l);
#endif
