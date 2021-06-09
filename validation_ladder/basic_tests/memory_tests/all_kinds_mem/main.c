#include<stdio.h>
#include <stdint.h>
#include "core_portme.h"
#include "ajit_access_routines.h"
#include <math.h>

#define TESTLENGTH 256
#define NSWEEPS    16

// mapped to VA_DATA_SECTION_START  + 0x10000
unsigned int *noncacheable_mem = (unsigned int *) (VA_DATA_SECTION_START + 0x2000); 
unsigned int *bypass_mem       = (unsigned int *) (VA_DATA_SECTION_START + 0x3000); 
unsigned int *cacheable_mem    = (unsigned int *) (VA_DATA_SECTION_START + 0x4000); 

float convertToSeconds(uint32_t ut)
{
	float result = (256.0/CLK_FREQUENCY)*((float) ut);
	return(result);
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
#ifdef EXPAND		
    for (i = 0; i < length; i++)
    {
    		if(bypass_flag)
			{
				uint32_t v = __ajit_load_word_mmu_bypass__((uint32_t) (a + i));
				ee_printf("\t Value stored at bypassed location 0x%x is : %d\r\n",(a + i),v);
			}
				else
			{
				ee_printf("\t Value stored at location 0x%x is : %d\r\n",(a + i),i);
			}
    }
#endif 
	return(err);
}

int march_test_byte (int bypass_flag, uint8_t* a, int length)
{
	int err = 0;
	int i;
	for(i=0; i < length; i++)
	{
		if(bypass_flag)
		{
			__AJIT_STORE_UBYTE_MMU_BYPASS__(((uint32_t) (a + i)), ((uint8_t) (i & 0xff)));
		}
		else
		{
			*(a+i) = i & 0xff;
		}
	}
	for(i=0; i < length; i++)
	{
		if(bypass_flag)
		{
			uint32_t v;
			__AJIT_LOAD_UBYTE_MMU_BYPASS__(((uint32_t) (a+i)), v);
			if(v != (i & 0xff))
				err = 1;
		}
		else
		{
			if(*(a+i) != (i & 0xff))
				err = 1;
		}
	}
	return(err);
}

int main()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);

#ifndef VA_DATA_SECTION_START
	ee_printf("Error: virtual address of data section not specified\n");		
	return(1);
#endif

#ifndef CLK_FREQUENCY
	ee_printf("Error: virtual clock frequency not specified\n");		
	return(1);
#endif

	int err = 0;
	uint32_t t0 = ajit_barebones_clock();

	int I;
	for(I = 0; I < NSWEEPS; I++)
	{
		err = march_test(0,noncacheable_mem,TESTLENGTH/4);
		if(err)
		{
			ee_printf("Error non-cacheable\n");
		}
	}
	uint32_t t1 = ajit_barebones_clock();
	ee_printf("Non-cacheable: Time = %f.\n",  convertToSeconds(t1 - t0));

	

	t0 = ajit_barebones_clock();
	for(I = 0; I < NSWEEPS; I++)
	{
		err = march_test(1,bypass_mem,TESTLENGTH/4);
		if(err)
		{
			ee_printf("Error bypass\n");
		}
	}
	t1 = ajit_barebones_clock();
	ee_printf("Bypass: Time = %f.\n",  convertToSeconds(t1 - t0));


	t0 = ajit_barebones_clock();
	for(I = 0; I < NSWEEPS; I++)
	{
		err = march_test(0,cacheable_mem,TESTLENGTH/4);
		if(err)
		{
			ee_printf("Error cacheable\n");
		}
	}
	t1 = ajit_barebones_clock();
	ee_printf("Cacheable: Time = %f.\n",  convertToSeconds(t1 - t0));

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

        ee_printf("Started march-test run for bypass memory\n");
        err = march_test(1,bypass_mem,TESTLENGTH/4);
        if(err)
        {
         	ee_printf("Error bypass\n");
        }
        else if(err==0)
        { 
					ee_printf("\tFinished march-test for by-passed locations\n"); 
				}

        ee_printf("Started march-test run for non-cacheable memory\n");
	err = march_test(0,noncacheable_mem,TESTLENGTH/4);
	if(err)
	{ 
		ee_printf("Error in non-cacheable locations\n"); 
	}
	else if(err==0)
	{ 
		ee_printf("\tFinished march-test for non-cacheable locations\n"); 
	}       

	ee_printf("\t\t\t Done with word-sized march tests \r\n");
	ee_printf("\t\t\t Starting with byte-sized march test \r\n"); 
	err = march_test_byte(0,(uint8_t*) noncacheable_mem,TESTLENGTH);
	if(err)
	{
		ee_printf("Error non-cacheable byte\n");
	}
	else
	{
		ee_printf("\tFinished byte-sized march-test for non-cacheable locations\n");
	}

	err = march_test_byte(1,(uint8_t*) bypass_mem,TESTLENGTH);
	if(err)
	{
		ee_printf("Error bypass byte\n");
	}
	else
	{
		ee_printf("\tFinished byte-sized march-test for bypassed locations\n");
	}
	err = march_test_byte(0,(uint8_t*) cacheable_mem,TESTLENGTH);
	if(err)
	{
		ee_printf("Error cacheable byte\n");
	}
	else
	{
		ee_printf("\tFinished byte-sized march-test for cacheable locations\n");
	}				
	ee_printf("done\n");
}

