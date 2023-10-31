
#ifndef CORTOS_UTILS_H
#define CORTOS_UTILS_H

// Cortos utility functions.

#include <stdint.h>
#include <stdarg.h>

////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_debug_routines
////////////////////////////////////////////////////////////////////////////////

// Exit after putting error_code into asr16.
// Exit codes:
//   0        - denotes success
//   0 to 255 - Reserved for Cortos
//   >=256    - Can be used by the application.
void cortos_exit(uint32_t error_code);

// printf routine offered by Cortos
// This needs the serial device to be enabled.
// __cortos_enable_serial() enables the serial device and is
// automatically called in init.s file.
int cortos_printf(const char *fmt, ...);

// This is the base printf routine offered
// by cortos.  
int cortos_vprintf(const char* fmt, va_list args);

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_debug_routines
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_utility_routines
////////////////////////////////////////////////////////////////////////////////

// reads high and low clock counters to return
// the value...   Returns the number of elapsed ticks
// where one tick is 256 clock cycles.
//   (Thus, if the clock is 100MHz, 1 tick is 2.56 micro-seconds).
inline uint64_t cortos_get_clock_time();

// sleep for specified number of clock cycles
inline void cortos_sleep(uint32_t clock_cycles);

// Returns the thread id of the system.
// 0 for Thread 00
// 1 for Thread 01
// 2 for Thread 10
// 3 for Thread 11
// ...
char cortos_get_thread_id();

// Returns 1 only if the address lies in the Non-Cacheable Ram (NCRAM) region.
uint8_t cortos_IsNcRamAddr(void* addr);

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_utility_routines
////////////////////////////////////////////////////////////////////////////////

#endif // CORTOS_UTILS_H

