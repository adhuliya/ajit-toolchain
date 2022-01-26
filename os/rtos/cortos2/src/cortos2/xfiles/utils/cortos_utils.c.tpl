#include "stdint.h"
#include "stdarg.h"

#include <cortos_utils.h>
#include <cortos_locks.h>
#include "ajit_access_routines.h"
#include "core_portme.h"


inline uint64_t cortos_get_clock_time() {
  return __ajit_get_clock_time();
}

inline void cortos_sleep(uint32_t clock_cycles) {
  __ajit_sleep__(clock_cycles);
}

// Returns the thread id of the system.
// 0 for Thread 00
// 1 for Thread 01
// 2 for Thread 10
// 3 for Thread 11
// ...
char cortos_get_thread_id() {
  unsigned int asrValue;

  __asm__ (
  "  rd %%asr29, %%l1\n"
  "  mov %%l1, %0\n"
  :"=r" (asrValue)
  :
  :"%l1"
  );

  return (((asrValue & 0xFF00) >> 8) * 2) + (asrValue & 0xFF);
}


// defined in cortos_ee_printf.c
int ee_vsprintf(char *buf, const char *fmt, va_list args);

// Thread Safe.
// Prints and returns the number of characters printed.
// Logic taken from ee_printf() in `minimal_printf_timer/src/ee_printf.c`
int cortos_printf(const char *fmt, ...) {
  char buf[1024], *p;
  va_list args;
  int n=0;

  __cortos_lock_acquire_buzy(__RES_LOCK_INDEX_PRINTF);

  va_start(args, fmt);
  ee_vsprintf(buf, fmt, args);
  va_end(args);
  p=buf;
  while (*p) {
    uart_send_char(*p);
    n++;
    p++;
  }

  __cortos_lock_release(__RES_LOCK_INDEX_PRINTF);

  return n;
}


