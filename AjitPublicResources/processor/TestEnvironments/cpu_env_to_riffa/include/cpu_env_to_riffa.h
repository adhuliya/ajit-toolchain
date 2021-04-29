#ifndef cpu_env_to_riffa_h__
#define cpu_env_to_riffa_h__

#include <stdint.h>

#define CPU_ICACHE_TO_RIFFA  	1
#define CPU_DCACHE_TO_RIFFA  	2
#define CPU_MODE_TO_RIFFA  	3
#define CPU_DEBUG_TO_RIFFA  	4
#define RIFFA_RESET_TO_CPU  	5
#define RIFFA_INTR_TO_CPU  	6
#define RIFFA_ICACHE_TO_CPU  	7
#define RIFFA_DCACHE_TO_CPU  	8
#define RIFFA_DEBUG_TO_CPU  	9

void cetr_send_u64_to_cpu(uint64_t* uword, int n_64bit_words);
void cetr_get_u64_from_cpu(uint64_t* uword, int n_64bit_words);
void cetr_icache_to_cpu_daemon();
void cetr_dcache_to_cpu_daemon();
void cetr_interface_daemon();
void cetr_start_daemons();
void cetr_stop_daemons();

#endif
