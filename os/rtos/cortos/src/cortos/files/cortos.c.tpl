#include "stdint.h"
#include "stdarg.h"

#include "cortos.h"
#include "__cortos.h"
#include "ajit_access_routines.h"
#include "core_portme.h"

// defined in cortos_printf.c
int ee_vsprintf(char *buf, const char *fmt, va_list args);


// enables the serial device (UART)
void __cortos_enable_serial() {
  __ajit_write_serial_control_register__(TX_ENABLE);
}


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


// Thread Safe.
// Prints and returns the number of characters printed.
// Logic taken from ee_printf() in `minimal_printf_timer/src/ee_printf.c`
int __cortos_log_printf(
    const char* levelName,
    const char *fileName,
    const char *funcName,
    int lineNum,
    const char *fmt,
    ...
) {
  char buf[1024], *p;
  va_list args;
  int n=0;
  unsigned int asrValue;
  uint64_t clock_time;

  __asm__ (
  "  rd %%asr29, %%l1\n"
  "  mov %%l1, %0\n"
  :"=r" (asrValue)
  :
  :"%l1"
  );

  __cortos_lock_acquire_buzy(__RES_LOCK_INDEX_PRINTF);


  clock_time = cortos_get_clock_time();

  n += ee_printf(
   "CoRTOS:LOG: %s: (%d,%d): %s:%d, %s() [%ld]. ",
   levelName, asrValue & 0xFF00, asrValue & 0xFF,
   fileName, lineNum, funcName, clock_time);

  va_start(args, fmt);
  ee_vsprintf(buf, fmt, args);
  va_end(args);
  p=buf;
  while (*p) {
    uart_send_char(*p);
    n++;
    p++;
  }

  n += ee_printf("\n");

  __cortos_lock_release(__RES_LOCK_INDEX_PRINTF);

  return n;
}


inline uint64_t cortos_get_clock_time() {
  return __ajit_get_clock_time();
}

inline void cortos_sleep(uint32_t clock_cycles) {
  __ajit_sleep__(clock_cycles);
}


