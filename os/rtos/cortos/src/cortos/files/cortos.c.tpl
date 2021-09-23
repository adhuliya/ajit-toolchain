#include "stdint.h"
#include "stdarg.h"

#include "cortos.h"
#include "__cortos.h"
#include "ajit_access_routines.h"
#include "core_portme.h"

char syncLockVars[__MAX_LOCK_VARS];

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


inline uint64_t cortos_get_clock_time() {
  return __ajit_get_clock_time();
}

inline void cortos_sleep(uint32_t clock_cycles) {
  __ajit_sleep__(clock_cycles);
}


int cortos_reserveLockVar() {
  int i, lid = -1;
  __cortos_lock_acquire_buzy(__RES_LOCK_GET_LOCK_ID);
  for (i=0; i < __MAX_LOCK_VARS; ++i) {
    if(syncLockVars[i] == 0) {
      syncLockVars[i] = 1;
      lid = i;
      break;
    }
  }
  __cortos_lock_release(__RES_LOCK_GET_LOCK_ID);
  return lid;
}


void cortos_freeLockVar(int lockId) {
  if (lockId >= 0 && lockId < __MAX_LOCK_VARS) {
    __cortos_lock_acquire_buzy(__RES_LOCK_GET_LOCK_ID);
    syncLockVars[lockId] = 0;
    __cortos_lock_release(__RES_LOCK_GET_LOCK_ID);
  }
}

