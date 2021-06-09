#ifndef CPU_ENV_MODEL_H__
#define CPU_ENV_MODEL_H__
int cpu_env_model(char*, int log_mem_size, int sw_flag, int use_display_driver, int use_kbd_driver,
				int verbose_flag, FILE* logger_trace_file);

#ifdef proto_board
int initialize_Memory (char* memoryMapFile);
#endif

// For dumping aa register-write-trace
FILE* reg_write_file;
FILE* long_reg_write_file;
char* logger_server_ip_address;
int   logger_server_port_number;
#endif
