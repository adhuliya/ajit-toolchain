#include "stdint.h"
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "math.h" 

#define TESTLENGTH 16

// mapped to 0x10000
unsigned int *noncacheable_mem = (unsigned int *) 0x10000; 
unsigned int *bypass_mem       = (unsigned int *) 0x11000; 
unsigned int *cacheable_mem    = (unsigned int *) 0x12000; 

int march_test_byte (int bypass_flag, uint8_t* a, int length)
{
	int err = 0;
	int i;
	for(i=0; i < length; i++)
	{
		if(bypass_flag)
		{
			__AJIT_STORE_UBYTE_MMU_BYPASS__(((uint32_t) (a + i)), ((uint8_t) i));
		}
		else
		{
			*(a+i) = i;
		}
	}
	for(i=0; i < length; i++)
	{
		if(bypass_flag)
		{
			uint32_t v;
			__AJIT_LOAD_UBYTE_MMU_BYPASS__(((uint32_t) (a+i)), v);
			if(v != i)
				err = 1;
		}
		else
		{
			if(*(a+i) != i)
				err = 1;
		}
	}
	return(err);
}

int march_test (int bypass_flag, unsigned int* a, int length)
{
	int err = 0;
	int i;
	for(i=0; i < length; i++)
	{
		if(bypass_flag)
		{
			__ajit_store_word_mmu_bypass__((uint32_t) i,(uint32_t) (a + i));
		}
		else
		{
			*(a+i) = i;
		}
	}
	for(i=0; i < length; i++)
	{
		if(bypass_flag)
		{
			uint32_t v = __ajit_load_word_mmu_bypass__((uint32_t) (a + i));
			if(v != i)
				err = 1;
		}
		else
		{
			if(*(a+i) != i)
				err = 1;
		}
	}
	return(err);
}

int main()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);

	int err = 0;
	err = march_test(0,noncacheable_mem,TESTLENGTH);
	if(err)
	{
		ee_printf("Error non-cacheable\n");
	}
	err = march_test(1,bypass_mem,TESTLENGTH);
	if(err)
	{
		ee_printf("Error bypass\n");
	}
	err = march_test(0,cacheable_mem,TESTLENGTH);
	if(err)
	{
		ee_printf("Error cacheable\n");
	}

	err = march_test_byte(0,(uint8_t*) noncacheable_mem,TESTLENGTH);
	if(err)
	{
		ee_printf("Error non-cacheable byte\n");
	}
	err = march_test_byte(1,(uint8_t*) bypass_mem,TESTLENGTH);
	if(err)
	{
		ee_printf("Error bypass byte\n");
	}
	err = march_test_byte(0,(uint8_t*) cacheable_mem,TESTLENGTH);
	if(err)
	{
		ee_printf("Error cacheable byte\n");
	}


	ee_printf("done\n");

	return (0);
}



