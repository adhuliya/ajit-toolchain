#include <stdint.h>
#include <assert.h>
#include "RegisterFile.h"
#include "ImplementationDependent.h"
#include "Ancillary.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "AjitThread.h"
#include "ThreadInterface.h"
#include <inttypes.h>
#include "SocketLib.h"

extern int global_verbose_flag;


RegisterFile* makeRegisterFile()
{
	RegisterFile* rf = (RegisterFile*) malloc (sizeof(RegisterFile));
	resetRegisterFile(rf);
	return(rf);
}

void resetRegisterFile(RegisterFile* rf)
{
	//Initialize registers to random values
	int i;
	for(i = 0; i < 8; i++)
	{
		rf->g[i] = rand();
	}
	//g[0] is always read as 0
	rf->g[0]=0;

	for(i = 0; i < 16 * NWINDOWS; i++)
	{
		rf->r[i] = rand(); 
	}

	for(i = 0; i < 32; i++)
	{
		rf->f[i] = rand();
	}
}

void writeRegister(uint32_t pc, RegisterFile* rf, uint8_t addr, uint8_t cwp, uint32_t value)
{
	assert(rf != NULL);

	uint8_t skip_write =  (addr == 0);
	uint8_t is_global = (addr < 8);
	uint8_t local_reg_addr = rem8(((addr - 8) + (cwp * 16)) , (16 * NWINDOWS));

	if (!skip_write && is_global)  rf->g[addr] = value ;
	if (!skip_write && !is_global) rf->r[local_reg_addr] = value ;

	if(global_verbose_flag && !skip_write)
	{
		fprintf(stderr,"RWRITE at PC= 0x%x:  CWP=0x%x, REGID= 0x%x, VALUE= 0x%x\n",
				pc, cwp, addr, value);
	}
}

uint32_t readRegister(RegisterFile* rf, uint8_t addr, uint8_t cwp)
{
	assert(rf != NULL);

	int8_t is_global = (addr < 8);
	uint8_t local_reg_addr = rem8 (((addr - 8) + (cwp * 16)) , (16 * NWINDOWS));

	uint32_t res = is_global ? rf->g[addr] : rf->r[local_reg_addr];

	return res;
}

void writeFRegister(RegisterFile* rf, uint8_t addr, uint32_t value)
{
	assert (rf != NULL);
	rf->f[addr] =  value;
}

uint32_t readFRegister(RegisterFile* rf, uint8_t addr)
{
	assert (rf != NULL);
	return rf->f[addr];
}
