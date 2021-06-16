#include <stdint.h>
#include <stdio.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

int main()
{
  double time;
  uint32_t v_l = __ajit_read_cycle_count_register_low__();
	uint32_t v_h = __ajit_read_cycle_count_register_high__();
  uint64_t ret_val = v_h;
	ret_val = ret_val << 32;
	ret_val = ret_val | v_l;
	__ajit_write_serial_control_register__ (TX_ENABLE | RX_ENABLE);
  ee_printf("Starting at 0x%x\n",ret_val);
  uint32_t v_l_t = __ajit_read_cycle_count_register_low__();
	uint32_t v_h_t = __ajit_read_cycle_count_register_high__();
  ee_printf("Time before printing is: low - 0x%x, high - 0x%x\n",v_l,v_h);
  ee_printf("Time after printing is: low - 0x%x, high - 0x%x\n", v_l_t, v_h_t);
  int a = 8;
  int i;
  for ( i = 0; i < a; i++)
  {
  uint32_t vlt = __ajit_read_cycle_count_register_low__();
	uint32_t vht = __ajit_read_cycle_count_register_high__();
  ee_printf("\t New Time after printing is: low - 0x%x, high - 0x%x\n", vlt, vht);
  }
  

}
