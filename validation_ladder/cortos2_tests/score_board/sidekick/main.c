#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include "score_board.h"

volatile ThreadChannel tc;

void startup_routine()
{
	initChannel(&tc);
}

void foo(uint32_t argc, uint32_t* argv, uint32_t* ret_argc, uint32_t* ret_vals)
{
	CORTOS_INFO("Sidekick: foo %d ", argc);
	int I;
	for(I = 0; I < argc; I++)
	{
		CORTOS_INFO(" 0x%x ", argv[I]);
		ret_vals[I] = argv[I];
	}
	*ret_argc = argc;
	CORTOS_INFO("\n");

}


void main_00 ()
{
	uint32_t int_array[8];
	int I;
	for(I = 0; I < 8; I++)
	{
		int_array[I] = I;
	}


	uint32_t last_request_id = 0;
	for(I = 0; I < 8; I++)
	{
		int_array[I] = (~I);

		scheduleChannelJob(CALL_FUNCTION, &foo, 8, int_array, &tc);
		CORTOS_INFO("scheduled job %d on channel.\n", tc.request_id);

		// wait until job completes.
		while(!responseReadyInChannel(&last_request_id, &tc)) 
		{
		}

		CORTOS_INFO("sidekick returned... response_id=%d.\n", tc.response_id);
		int J;
		for(J = 0; J < tc.response_size; J++)
		{
			CORTOS_INFO(" 0x%x ", tc.response_words[J]);
		}
	}
}




void main_01 () 
{
	CORTOS_INFO("started scheduler on (0,1).\n");
	sidekickServer(8, 0,1,&tc);
}

