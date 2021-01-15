#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "SocketLib.h"
#include "monitorLogger.h"


void register_monitor_logger_pipes (MonitorLoggerState* mls)
{

}

void monitorLogger_0 (void* vmls)
{
	monitorLogger_core ((MonitorLoggerState*)vmls);
}
void monitorLogger_1 (void* vmls)
{
	monitorLogger_core ((MonitorLoggerState*)vmls);
}
void monitorLogger_2 (void* vmls)
{
	monitorLogger_core ((MonitorLoggerState*)vmls);
}
void monitorLogger_3 (void* vmls)
{
	monitorLogger_core ((MonitorLoggerState*)vmls);
}


DEFINE_THREAD_WITH_ARG(monitorLogger_0, vmls);
DEFINE_THREAD_WITH_ARG(monitorLogger_1, vmls);
DEFINE_THREAD_WITH_ARG(monitorLogger_2, vmls);
DEFINE_THREAD_WITH_ARG(monitorLogger_3, vmls);

MonitorLoggerState*  start_monitor_logger_thread (int cpu_id, 
					char* reg_write_file,
					char* long_reg_write_file,
					char* server_ip_address,
					int server_port_number,
					int verbose_flag)
{

	assert ((cpu_id >= 0) && (cpu_id < 4));
	MonitorLoggerState* mls = makeMonitorLoggerState (cpu_id, reg_write_file, long_reg_write_file,
								server_ip_address, server_port_number,
								verbose_flag);
	if(cpu_id == 0)
	{
		PTHREAD_DECL(monitorLogger_0);
		PTHREAD_CREATE_WITH_ARG (monitorLogger_0, ((void*) mls));
	}
	else if (cpu_id == 1)
	{
		PTHREAD_DECL(monitorLogger_1);
		PTHREAD_CREATE_WITH_ARG (monitorLogger_1, ((void*) mls));
	}
	else if (cpu_id == 2)
	{
		PTHREAD_DECL(monitorLogger_2);
		PTHREAD_CREATE_WITH_ARG (monitorLogger_2, ((void*) mls));
	}
	else if (cpu_id == 3)
	{
		PTHREAD_DECL(monitorLogger_3);
		PTHREAD_CREATE_WITH_ARG (monitorLogger_3, ((void*) mls));
	}
	
	return(mls);
}

