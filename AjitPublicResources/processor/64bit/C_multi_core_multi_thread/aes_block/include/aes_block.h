#ifndef __aes_block_h___
#define __aes_block_h___

#define TABLE_SIZE         1024
#define TABLE_SIZE_MASK   0x3ff

typedef struct __EncryptDecryptBlock {
	// AES key
	uint64_t aes_key_h;
	uint64_t aes_key_l;

	// The bits of address to be masked
	// off during insertion.
	//
	// This is a dword address, which 
	// is PA[35:3], ie 33 bits wide
	// The mask will be the bottom K
	// bits of this 33 bit number..
	uint64_t address_mask;
	
	//
	// existing translations, a direct
	// mapped cache, which uses the bottom
	// 10-bits of the address as an index
	// into the table.
	//
	uint64_t translations[TABLE_SIZE][2];

} EncryptDecryptBlock;


// Setup encrypt decrypt block.... return 0 on success.
int  makeEncryptDecryptBlock (FILE* fp);
int readKeyAndAddressMaskFromFile (FILE* fp, uint64_t* k_h, uint64_t* k_l, uint64_t* a_mask);

void setupEncryptDecryptBlock (EncryptDecryptBlock *ed, uint64_t aes_key_h, 
					uint64_t aes_key_l,
					uint64_t address_mask);
					
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
