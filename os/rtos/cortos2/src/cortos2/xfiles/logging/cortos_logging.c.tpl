
#include <stdarg.h>
#include <cortos_locks.h>
#include <cortos_utils.h>

#define LOGGING_LOCK_INDEX 4
uint8_t* loggingLockAddr = 0;

void cortos_init_logging() {
  // allocate lock
  uint8_t* lockStartAddrNc = (uint8_t*){{ confObj.software.locks.locksStartAddr }}; // non-cacheable
  allocatedLocksNc[LOGGING_LOCK_INDEX] = 1;
  loggingLockAddr = lockStartAddrNc + LOGGING_LOCK_INDEX;
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
  unsigned int *time;

  __asm__ (
  "  rd %%asr29, %%l1\n"
  "  mov %%l1, %0\n"
  :"=r" (asrValue)
  :
  :"%l1"
  );

  cortos_lock_acquire_buzy(loggingLockAddr);


  clock_time = cortos_get_clock_time();
  time = &clock_time;

  n += ee_printf(
   "CoRTOS:LOG: %s: (%d,%d): %s:%d, %s() [%lu,%lu]. ",
   levelName, (asrValue & 0xFF00) >> 8, asrValue & 0xFF,
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

  cortos_lock_release(loggingLockAddr);

  return n;
}


