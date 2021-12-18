#ifdef AJIT
#include <stdlib.h>
#include <stdint.h>
#include <core_portme.h>
#include <ajit_access_routines.h>
#define EE_TICKS_PER_SECOND  (AJIT_CLOCK_FREQUENCY/256)

int clock_time(void)
{
  uint32_t tval  = ajit_barebones_clock();					
  int seconds    = (tval/ EE_TICKS_PER_SECOND );
#ifdef DEBUG
  ee_printf ("AJIT clock_time = %d (tval=%d).\n", seconds, tval);
#endif
  return seconds;
}

#endif

