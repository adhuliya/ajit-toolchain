#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "pipeHandler.h"
#include "Pipes.h"
#include "SockPipes.h"
#include "riffa.h"
#include "processor_link.h"
#include <inttypes.h>
#include <pthread.h>
#include <pthreadUtils.h>

static fpga_t* fpga = NULL;
MUTEX_DECL(fpga_mutex);

int processor_link_type = PROCESSOR_SOCKET_LINK;
// set the type of link: sockets or riffa?
int set_processor_link(int plink_type)
{
	assert((plink_type == PROCESSOR_SOCKET_LINK) ||
		(plink_type == PROCESSOR_RIFFA_LINK));

	processor_link_type = plink_type;

	int ret_val = 0;
	if(plink_type == PROCESSOR_RIFFA_LINK)
	{
		// open the FPGA.
		// ret_val = 1 if there is a problem
		MUTEX_LOCK(fpga_mutex);
		fpga = fpga_open(0);
		if(fpga == NULL)	
		{
			fprintf(stderr,"Error: could not open FPGA.\n");
			ret_val = 1;
		}
		fpga_reset(fpga);
		MUTEX_UNLOCK(fpga_mutex);
	}

	return(ret_val);
}

int close_fpga ()
{
	MUTEX_LOCK(fpga_mutex);
	if(fpga != NULL)
	{
		fpga_close(fpga);
		fpga = NULL;
	}
	MUTEX_UNLOCK(fpga_mutex);

	return 0;
}

// return 0 on success, non-zero on failure.
int send_u64_to_processor(uint64_t* s_word)
{
	int ret_val = 0;
	if(processor_link_type == PROCESSOR_SOCKET_LINK)
	{
		sock_write_uint64("RIFFA_to_CPU", *s_word);
	}
	else
	{
		MUTEX_LOCK(fpga_mutex);
		if(fpga == NULL)
		{
			fprintf(stderr,"\ncetr_send_u64_to_cpu: FPGA = NULL, skipped.\n");
		}
		else
		{
			// fpga-struct, buf-ptr, length in uint32's, dest-offset, last-flag, timeout
			int sent = fpga_send(fpga, 0, s_word, 2, 0, 1, 0);	
			if (sent == 2)			
				ret_val = 0;
			else
				ret_val = sent;
		}
		MUTEX_UNLOCK(fpga_mutex);
	}
	return(ret_val);
}

int recv_u64_from_processor(uint64_t* r_word)
{
	int ret_val = 0;
	if(processor_link_type == PROCESSOR_SOCKET_LINK)
	{
		*r_word = sock_read_uint64("CPU_to_RIFFA");
	}
	else
	{
		MUTEX_LOCK(fpga_mutex);
		if(fpga == NULL)
		{
			fprintf(stderr,"\ncetr_get_u64_from_cpu: FPGA = NULL, skipped.\n");
		}
		else
		{
			int expected_word_count = 2;
			int recv = fpga_recv(fpga, 0, (void*) r_word, expected_word_count, 5000);
			if(recv < 0)
			{
				fprintf(stderr,"Error:cetr_get_u64_to_cpu: read error.. resetting the FPGA and returning 0's.\n");
				fpga_reset(fpga);
				memset((void*) r_word, 0, expected_word_count*4);
			}
			else if (recv < expected_word_count)
			{
				fprintf(stderr,"Warning:cetr_get_u64_to_cpu: possible incomplete read..  data may have been lost.. \n");
			}
			if (recv != 2)			
				ret_val = recv;
			else
				ret_val = 0;
		}
		MUTEX_UNLOCK(fpga_mutex);
	}
	return(ret_val);
}

