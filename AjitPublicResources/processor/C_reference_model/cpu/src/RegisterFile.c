#include <stdint.h>
#include "RegisterFile.h"
#include "ImplementationDependent.h"
#include "Ancillary.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "CpuInterface.h"
#include <inttypes.h>
#include "SocketLib.h"

uint32_t g[8]; // Global Registers
uint32_t r[16 * NWINDOWS]; // Windowed Registers
uint32_t f[32]; // General Purpose floating point registers;


void initRegisterFile()
{
	//Initialize registers to random values
	int i;
	for(i = 0; i < 8; i++)
	{
		g[i] = rand();
	}
	//g[0] is always read as 0
	g[0]=0;

	for(i = 0; i < 16 * NWINDOWS; i++)
	{
		r[i] = rand(); 
	}

	for(i = 0; i < 32; i++)
	{
		f[i] = rand();
	}
}

void writeRegister( uint8_t addr, uint8_t cwp, uint32_t value)
{
	uint8_t skip_write =  (addr == 0);
	uint8_t is_global = (addr < 8);
	uint8_t local_reg_addr = rem8(((addr - 8) + (cwp * 16)) , (16 * NWINDOWS));

	if (!skip_write && is_global) g[addr] = value ;
	if (!skip_write && !is_global) r[local_reg_addr] = value ;
}

uint32_t readRegister(uint8_t addr, uint8_t cwp)
{
	int8_t is_global = (addr < 8);
	uint8_t local_reg_addr = rem8 (((addr - 8) + (cwp * 16)) , (16 * NWINDOWS));

	uint32_t res = is_global ? g[addr] : r[local_reg_addr];

	return res;
}

void writeFRegister( uint8_t addr, uint32_t value)
{
	f[addr] =  value;
}

uint32_t readFRegister(uint8_t addr)
{
	return f[addr];
}
