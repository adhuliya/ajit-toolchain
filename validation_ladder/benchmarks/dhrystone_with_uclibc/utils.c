#include "dhry.h"
#include <stdint.h>

#define haszero(v) (((v) - 0x01010101) & ~(v) & 0x80808080)

void *__memcpy(void *dest, const void *src, size_t n)
{
	int I=0;
	int J=0;

	uint64_t* cdest_64 = (uint64_t*) dest;
	uint64_t* csrc_64 = (uint64_t*) src;

	// transfer 64-bits at a time as much as possible
	uint64_t S = csrc_64[0];
	do 
	{
		cdest_64[I] = S;
		I++;
		J += 8;
		S = csrc_64[I];
	} while (J < n);

	// copy the rest..
	if(J < n)
	{
		uint8_t* cdest_8 = (uint8_t*) dest;
		uint8_t* csrc_8 = (uint8_t*) src;
		do 
		{
			cdest_8[J] = csrc_8[J];
			J++;
		} while(J < n);
	}

	return(dest);
}

char *__strcpy(char *dest, const char *src)
{
	int I;
	I = 0;
	
	int n1 = 0;

	uint32_t* cdest_32 = (uint32_t*) dest;
	uint32_t* csrc_32 = (uint32_t*) src;

	uint32_t S = csrc_32[0];
	uint32_t brk_flag = 0;
	do 
	{
		brk_flag = haszero(S);
		cdest_32[I] = S;
		I++;
		S = csrc_32[I];
	} while (!brk_flag);

	return(dest);
}

int __strcmp(const char *s1, const char *s2)
{
	register int ret_val = 0;
	int I;
	I = 0;

	uint32_t* S1_32 = (uint32_t*) s1;
	uint32_t* S2_32 = (uint32_t*) s2;

	uint32_t brk_flag = 0;
	do 
	{
		uint32_t S = S1_32[I];
		uint32_t D = S2_32[I];

		ret_val = (S-D);

		brk_flag = (ret_val | haszero(S));
		I++;

	} while (!brk_flag);

	return(ret_val);
}
