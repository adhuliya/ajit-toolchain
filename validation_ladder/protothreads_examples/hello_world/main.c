#include <unistd.h>
#include <core_portme.h>
#include <ajit_access_routines.h>
#define PRINTF ee_printf

#include "pt.h"

static PT_THREAD(p0_thread(struct pt *pt))
{
  static int COUNTER = 0;
  /*
   * Declare the beginning of the protothread.
   */
  PT_BEGIN(pt);

  /*
   * We'll let the protothread loop until the protothread is
   * expliticly exited with PT_EXIT().
   */
  while(1) {
	PRINTF("p0: COUNTER = %d.\n", COUNTER);
	COUNTER++;
	if(COUNTER == 8)
		break;

	PT_YIELD(pt);

  }
  PT_END(pt);
}

static PT_THREAD(p1_thread(struct pt *pt))
{
  static int COUNTER = 0;
  /*
   * Declare the beginning of the protothread.
   */
  PT_BEGIN(pt);

  /*
   * We'll let the protothread loop until the protothread is
   * expliticly exited with PT_EXIT().
   */
  while(1) {
	PRINTF("p1: COUNTER = %d.\n", COUNTER);
	COUNTER++;
	if(COUNTER == 8)
		break;

	PT_YIELD(pt);
  }

  PT_END(pt);
}

struct pt p0_pt, p1_pt;

int main(void)
{

  __ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
  PRINTF("Start run on AJIT.\n");

  /* initialize */
  PT_INIT(&p0_pt);
  PT_INIT(&p1_pt);

  while(1) {
    int p0 = PT_SCHEDULE(p0_thread(&p0_pt));
    int p1 = PT_SCHEDULE(p1_thread(&p1_pt));

   if ((p0 == 0) && (p1 == 0))
	break;
  }
  PRINTF("Finished run on AJIT.\n");
  return 0;
}

