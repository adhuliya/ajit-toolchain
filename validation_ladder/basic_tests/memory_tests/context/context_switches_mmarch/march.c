#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

#define BUFSIZE 1024
int marchTest(uint32_t context)
{
	int err = 0;
	uint32_t* base_ptr = 0x40040000;
	uint32_t  index;
	for(index = 0; index < BUFSIZE; index++)
	{
		*(base_ptr + index) = (index + context);
	}

	for(index = 0; index < BUFSIZE; index++)
	{
		uint32_t d = *(base_ptr + index);
		if (d != (index + context))
		{
			ee_printf("Error: context=%d, index=%d, read 0x%x.\n", 
					context, index, d);
			err = 1;
		}
	}
	

	return(err);

}

