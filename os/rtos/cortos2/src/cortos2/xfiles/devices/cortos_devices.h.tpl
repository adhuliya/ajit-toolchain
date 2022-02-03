
#ifndef CORTOS_DEVICES_H
#define CORTOS_DEVICES_H

// Enable serial device to use printf etc.
// This function is automatically called by cortos in `init_00.s`.
void __cortos_enable_serial();

// Enable serail device and its interrupts.
void __cortos_enable_serial_interrupt();

#endif // CORTOS_DEVICES_H
