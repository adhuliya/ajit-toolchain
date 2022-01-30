
#include <stdarg.h>
#include <cortos_locks.h>
#include <cortos_utils.h>

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
  unsigned int *time;

  __asm__ (
  "  rd %%asr29, %%l1\n"
  "  mov %%l1, %0\n"
  :"=r" (asrValue)
  :
  :"%l1"
  );

  __cortos_lock_acquire_buzy(__RES_LOCK_INDEX_PRINTF);


  clock_time = cortos_get_clock_time();
  time = &clock_time;

  n += ee_printf(
   "CoRTOS:LOG: %s: (%d,%d): %s:%d, %s() [%lu,%lu]. ",
   levelName, asrValue & 0xFF00, asrValue & 0xFF,
   fileName, lineNum, funcName, *time, *(time+1));

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


