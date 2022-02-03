
#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "cortos_devices.h"


// enables the serial device (UART)
void __cortos_enable_serial() {
  __ajit_write_serial_control_register__(TX_ENABLE | RX_ENABLE);
}

void __cortos_enable_serial_interrupt() {
  __ajit_write_serial_control_register__(TX_ENABLE | RX_ENABLE | RX_INTR_ENABLE);
}


