#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>
#include <ajit_context.h>
#include <data_struct.h>

void coroutine (void* ptr)
{
	CoroutineControl* ctrl = (CoroutineControl*) ptr;	
	uint32_t sp;
	 __AJIT_GET_IU_REGISTER(14,sp);

	cortos_printf("C%d (sp=0x%x): %d.\n", ctrl->id, sp, ctrl->counter);
	ctrl->counter += 1;
}
