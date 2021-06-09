#include "dhry.h"
#include <stdint.h>

#define haszero(v) (((v) - 0x01010101) & ~(v) & 0x80808080)

void *__memcpy(void *dest, const void *src, size_t n)
{
	int I=0;
	int J=0;

#ifndef DHRYOPT
	uint32_t aligned_8 = ((((uint32_t) dest) & 0x7) | (((uint32_t) src) & 0x7)) == 0;
	if(aligned_8 && (n > 7))
	{
#endif
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
#ifndef DHRYOPT
	}
	else
	{
		uint32_t aligned_4 = ((((uint32_t) dest) & 0x3) | (((uint32_t) src) & 0x3)) == 0;
		if(aligned_4 && (n > 3))
		{
			uint32_t* cdest_32 = (uint32_t*) dest;
			uint32_t* csrc_32  = (uint32_t*) src;

			uint32_t S = csrc_32[0];
			do
			{
				cdest_32[I] = S;
				I++;
				J += 4;
				S = csrc_32[I];
			} while ( J < n);

		}
	}
#endif

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

#ifndef DHRYOPT
	uint32_t aligned_4 = ((((uint32_t) dest) & 0x3) | (((uint32_t) src) & 0x3)) == 0;
	if(aligned_4)
	{
#endif
		uint32_t* cdest_32 = (uint32_t*) dest;
		uint32_t* csrc_32 = (uint32_t*) src;

		uint32_t S = csrc_32[0];
		uint32_t brk_flag = 0;
		do 
		{
			brk_flag = haszero(S);
	
#ifdef DHRYOPT
			cdest_32[I] = S;
#else

			uint32_t b3 = (S & 0x000000ff); // first character
			uint32_t b2 = (S & 0x0000ff00);
			uint32_t b1 = (S & 0x00ff0000);
			uint32_t b0 = (S & 0xff000000); // last character.

			uint8_t cp_word = (b3 && b2 && b1);
			if(cp_word)	
			{
				cdest_32[I] = S;
			}
			else 
			{
			    int J = I << 2;
			    dest[J] = b3;
			    if(b3)
			    {
				dest[J+1] = (b2 >> 8);
				if (b2)
				{
					dest[J+2] = (b1 >> 16);
					if(b1) 
					{
						dest[J+3] = (b0 >> 24);
					}
				}
			    }
			    break;
			}
#endif // DHRYOPT

			I++;
			S = csrc_32[I];
		} while (!brk_flag);
#ifndef DHRYOPT
	}
	else
	{
		uint8_t S;
		do {
			S = *src++;	
			*dest++ = S;
		} while (S != 0);
			
	}
#endif
	return(dest);
}

int __strcmp(const char *s1, const char *s2)
{
	register int ret_val = 0;
	int I;
	I = 0;

#ifndef DHRYOPT
	uint32_t aligned_4 = ((((uint32_t) s1) & 0x3) | (((uint32_t) s2) & 0x3)) == 0;
	if(aligned_4)
	{
#endif
		uint32_t* S1_32 = (uint32_t*) s1;
		uint32_t* S2_32 = (uint32_t*) s2;

		uint32_t brk_flag = 0;
		do 
		{
			uint32_t S = S1_32[I];
			uint32_t D = S2_32[I];

			ret_val = (S-D);

			if(ret_val | haszero(S))
				brk_flag = 1;

			I++;
		} while (!brk_flag);
#ifndef DHRYOPT
	}
	else
		// byte-by-byte..
	{
		unsigned char c1, c2;
		do
		{
			c1 = (unsigned char) *s1++;
			c2 = (unsigned char) *s2++;
			if (c1 == '\0')
			{
				ret_val = c1 - c2;
				break;
			}
		}
		while (c1 == c2);
	}
#endif

	return(ret_val);
}
