
#ifndef CORTOS_DEVICES_H
#define CORTOS_DEVICES_H

// Enable serial device to use printf etc.
// This function is automatically called by cortos in `init_00.s`.
void __cortos_enable_serial();

#endif // CORTOS_DEVICES_H
