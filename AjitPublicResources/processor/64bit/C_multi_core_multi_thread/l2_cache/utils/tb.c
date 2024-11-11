#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <assert.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "Ajit_Hardware_Configuration.h"
#include "RequestTypeValues.h"
#include "L2CacheInterface.h"
#include "Ancillary.h"
#include "ASI_values.h"
#include "aes_block.h"
#include "memory.h"

int global_verbose_flag = 1;

#ifdef ENCRYPT
int use_encrypted_memory = 1;
extern EncryptDecryptBlock* aes_ed_block;
#else
int use_encrypted_memory = 0;
#endif

// random addresses for march.
uint64_t r_history [1024];


int random_write_march(WriteBackCache* c, int n_samples)
{
	int I;
	for(I = 0; I < n_samples; I++)
	{
		uint64_t addr = (lrand48() % (1 << 24)) & (~ 0x7);
		doWriteBackCacheAccess (c, 0, 0xff, addr, addr);
		r_history[I] = addr;
	}	
}

int random_read_march(WriteBackCache* c, int n_samples)
{
	int _err_ = 0;
	int I;
	for(I = 0; I < n_samples; I++)
	{
		uint64_t addr = r_history[I];
		uint64_t rdata = doWriteBackCacheAccess (c, 1, 0xff, addr, 0x0);
		if(rdata != addr)
		{
			fprintf(stderr,"Error: addr=0x%llx rdata=0x%llx\n", addr, rdata);
			_err_ = 1;
		}
		else
		{
			fprintf(stderr,"Info: addr=0x%llx rdata=0x%llx\n", addr, rdata);
		}
	}	
	return(_err_);
}


int read_march (WriteBackCache* c, int n_dwords)
{

	int _err_ = 0;
	int N;
	uint64_t addr;

	for(N = 0, addr=0x0; N < n_dwords; N++, addr=addr+8)
	{
		uint64_t rdata = doWriteBackCacheAccess (c, 1, 0xff, addr, 0x0);
		if(rdata != addr)
		{
			fprintf(stderr,"Error: addr=0x%llx rdata=0x%llx\n", addr, rdata);
			_err_ = 1;
		}
		else
		{
			fprintf(stderr,"Info: addr=0x%llx rdata=0x%llx\n", addr, rdata);
		}
			
	}
	return(_err_);
}

int write_march (WriteBackCache* c, int n_dwords)
{

	int _err_ = 0;
	int N;
	uint64_t addr;

	for(N = 0, addr=0x0; N < n_dwords; N++, addr=addr+8)
	{
		doWriteBackCacheAccess (c, 0, 0xff, addr, addr);
	}
	return(0);
}

int main(int argc, char* argv [])
{
	int _err_ = 0;
	srand48(191);


	if (argc < 2)
	{	
		fprintf(stderr,"Usage: %s <n-dwords> \n", argv[0]);
		return(1);
	}

	int n_dwords = atoi(argv[1]);

	allocateMemory (24);
	WriteBackCache* c = makeWriteBackCache (0, 256, 8);

#ifdef ENCRYPT
	FILE* e_fp;
	e_fp = fopen ("aes_keys.txt", "r");
	if(e_fp == NULL)
	{
		fprintf(stderr,"Error: could not open aes_keys.txt\n");
		return(1);
	}
	int status = makeEncryptDecryptBlock(e_fp);
	fclose (e_fp);
	if(status)
	{
		fprintf(stderr,"Error: could not make encrypt block.\n");
		use_encrypted_memory = 0;
		return(1);
	}
#endif

	uint64_t addr, rdata;
	write_march(c, n_dwords);
	_err_ = read_march (c, n_dwords);

	printWriteBackCacheStatistics (c);

	if(_err_)
		fprintf(stderr,"normal march: FAILURE.\n");
	else
		fprintf(stderr,"normal march: SUCCESS.\n");


	clearWriteBackCache(c);

	random_write_march(c, n_dwords % 1024);
	_err_ = random_read_march(c, n_dwords % 1024);
	
	printWriteBackCacheStatistics (c);

	if(_err_)
		fprintf(stderr,"random march: FAILURE.\n");
	else
		fprintf(stderr,"random march: SUCCESS.\n");
	return(0);
}

