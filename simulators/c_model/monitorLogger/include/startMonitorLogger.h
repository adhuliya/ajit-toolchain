#ifndef startMonitorLogger_h__
#define startMonitorLogger_h__

#include "monitorLogger.h"

void register_monitor_logger_pipes (MonitorLoggerState* mls);
MonitorLoggerState*
	 start_monitor_logger_thread (int cpu_id, 
					char* reg_write_file,
					char* long_reg_write_file,
					char* server_ip_address,
					int server_port_number,
					int verbose_flag);
#endif
