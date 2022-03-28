// Program for RPN calculator  using serial sw_traps
#include <stdint.h>
#include <stdio.h>
#include <setjmp.h>
#include <ajit_access_routines.h>
#include <core_portme.h>
#include <ajit_mt_sw_traps.h>
#include <cortos.h>


// This is the handler that sits in the sw trap handler array..
void user_handler05(uint32_t arg1, uint32_t arg2, uint32_t arg3) {
  CORTOS_INFO("Inside user_handler05. %lu, %lu, %lu", arg1, arg2, arg3);
}


int main () {

  __AJIT_SW_TRAP(5);
  __AJIT_SW_TRAP(5);
  __AJIT_SW_TRAP(5);
  __AJIT_SW_TRAP(5);

	return 0;
}
