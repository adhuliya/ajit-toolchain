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

void monitorLogger(void* vmls)
{
	monitorLogger_core ((MonitorLoggerState*)vmls);
}


DEFINE_THREAD_WITH_ARG(monitorLogger, vmls);

MonitorLoggerState*  start_monitor_logger_thread (uint32_t core_id, uint32_t thread_id,
					char* reg_write_file,
					char* long_reg_write_file,
					char* server_ip_address,
					int server_port_number,
					int verbose_flag)
{

	MonitorLoggerState* mls = makeMonitorLoggerState (core_id, thread_id, reg_write_file, long_reg_write_file,
								server_ip_address, server_port_number,
								verbose_flag);
	PTHREAD_DECL(monitorLogger);
	PTHREAD_CREATE_WITH_ARG(monitorLogger, ((void*) mls));
	

	return(mls);
}

