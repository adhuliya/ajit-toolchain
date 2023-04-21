#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ajit_access_routines.h>
#include <cortos.h>

int
main(void)
{
  int N;
  
  for(N = 0; N < 16; N++)
  {
	  // 1024 words.
	  uint32_t*  warray = cortos_bget(1024*4);
	  cortos_printf("Info: allocated 1024 words at 0x%x\n", (uint32_t) warray);

	  int I;
	  for(I = 0; I < 1024; I++)
		  warray[I] = I;

	  for(I = 0; I < 1024; I++)
	  {
		  uint32_t v = warray[I];
		  if (v != I)
		  {
			  cortos_printf("Error: mismatch at I=0x%x\n", I);
			  break;
		  }
	  }
	  cortos_brel(warray);
  }

  cortos_printf("Done.\n");
  return(0);
}
