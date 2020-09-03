#ifndef _bridge_h___
#define _bridge_h___

void bridge_cpu_0 ();
void bridge_cpu_1 ();
void bridge_cpu_2 ();
void bridge_cpu_3 ();

void bridge_cpu_core (int cpu_id,
				char* req_pipe_name, char* addr_pipe_name, 
				char* wdata_pipe_name,  char* byte_mask_pipe_name,
					char* rdata_pipe_name );
void register_bridge_pipes (int number_of_cpus);
void start_bridge_daemons (int number_of_cpus);


#endif
