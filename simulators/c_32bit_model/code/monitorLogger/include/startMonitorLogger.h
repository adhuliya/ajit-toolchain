#ifndef startMonitorLogger_h__
#define startMonitorLogger_h__

#include "monitorLogger.h"
DEFINE_THREAD(monitorLogger);

void start_monitor_logger()
{
	PTHREAD_DECL(monitorLogger);
	PTHREAD_CREATE(monitorLogger);
}

#endif
