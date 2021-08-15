#include "stdint.h"
#include "stdarg.h"

#include "cortos.h"
#include "ajit_access_routines.h"
#include "core_portme.h"

// defined in cortos_printf.c
int ee_vsprintf(char *buf, const char *fmt, va_list args);


// enables the serial device (UART)
void cortos_enable_serial() {
  __ajit_write_serial_control_register__(TX_ENABLE);
}


// Thread Safe.
// Prints and returns the number of characters printed.
// Logic taken from ee_printf() in `minimal_printf_timer/src/ee_printf.c`
int cortos_printf(const char *fmt, ...) {
  char buf[1024], *p;
  va_list args;
  int n=0;

  cortos_res_lock_acquire_buzy(RES_LOCK_INDEX_PRINTF);

  va_start(args, fmt);
  ee_vsprintf(buf, fmt, args);
  va_end(args);
  p=buf;
  while (*p) {
    uart_send_char(*p);
    n++;
    p++;
  }

  cortos_res_lock_release(RES_LOCK_INDEX_PRINTF);

  return n;
}


// Thread Safe.
// Prints and returns the number of characters printed.
// Logic taken from ee_printf() in `minimal_printf_timer/src/ee_printf.c`
int cortos_log_printf(
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

  __asm__ (
  "  rd %%asr29, %%l1\n"
  "  mov %%l1, %0\n"
  :"=r" (asrValue)
  :
  :"%l1"
  );

  cortos_res_lock_acquire_buzy(RES_LOCK_INDEX_PRINTF);

  n += ee_printf(
   "CoRTOS: LOG: %s: Thread (%d,%d), File: %s, Func: %s, Line: %d. ",
   levelName, asrValue & 0xFF00, asrValue & 0xFF, fileName, funcName, lineNum);

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

  cortos_res_lock_release(RES_LOCK_INDEX_PRINTF);

  return n;
}
