#include <stdio.h>
#include <stdint.h>
#include "ThreadLogging.h"


//routines to enable/disable logging by the cpu.
//The log signature, if generated, is sent out
//on AJIT_to_ENV_logger pipe.
static int LOGGING_ENABLED =0;
void enable_logging_by_thread()
{
	LOGGING_ENABLED=1;
}
void disable_logging_by_thread()
{
	LOGGING_ENABLED=0;
}
int  is_logging_enabled()
{
	return LOGGING_ENABLED;
}



