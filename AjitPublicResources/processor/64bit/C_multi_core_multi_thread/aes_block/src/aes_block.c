#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "aes_block.h"

// global, used in memory.
EncryptDecryptBlock* aes_ed_block = NULL;

// return 0 if all 3 values read from file.
int readKeyAndAddressMaskFromFile (FILE* fp, uint64_t* k_h, uint64_t* k_l, uint64_t* a_mask)
{
	int n = fscanf (fp, "%" PRIx64 " %" PRIx64 " %" PRIx64, k_h, k_l, a_mask);
	if (n == 3)
	{
		fprintf(stderr,"AES keys %" PRIx64 " %" PRIx64 " %" PRIx64 "\n", 
					*k_h, *k_l, *a_mask);
		return(0);
	}
	else
		return(1);
	
}

// Setup encrypt decrypt block.... return 0 on success.
int makeEncryptDecryptBlock (FILE* fp)
{
	aes_ed_block = (EncryptDecryptBlock*) malloc (sizeof (EncryptDecryptBlock));

	uint64_t k_h, k_l, a_mask;
	int status = readKeyAndAddressMaskFromFile (fp, &k_h, &k_l, &a_mask);
	if(status)
	{
		free(aes_ed_block);
		aes_ed_block = NULL;
		return(1);
	}
	
	setupEncryptDecryptBlock (aes_ed_block, k_h, k_l, a_mask);
	return(0);
}

void setupEncryptDecryptBlock (EncryptDecryptBlock *ed, 
					uint64_t aes_key_h, 
					uint64_t aes_key_l,
					uint64_t address_mask)
{
	ed->aes_key_h = aes_key_h;
	ed->aes_key_l = aes_key_l;
	ed->address_mask - address_mask;

	// TODO: generate the 10 round keys.
}

					

void encryptBlock (EncryptDecryptBlock* ed,
			uint64_t data_h, 
			uint64_t data_l,
			uint64_t address,
			uint64_t *cipher_text_h,
			uint64_t *cipher_text_l)
{
	// for now pass through.
	*cipher_text_h = data_h;
	*cipher_text_l = data_l;
}

void decryptBlock (EncryptDecryptBlock* ed,
			uint64_t cipher_text_h, 
			uint64_t cipher_text_l,
			uint64_t address,
			uint64_t *data_h,
			uint64_t *data_l)
{
	// for now pass through.
	*data_h = cipher_text_h;
	*data_l = cipher_text_l;

}

