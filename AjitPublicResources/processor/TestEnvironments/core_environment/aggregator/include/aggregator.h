#ifndef _aggregator_h___
#define _aggregator_h___
#include "spi.h"

// listen on ENV_to_AJIT_debug_command pipe
//    when bytes are received,  send them to the debug-spi-master
//    using the pipe noblock_debug_to_cpu pipe (master commands to cpu)
//
//    Then read from the cpu_to_debug  pipe (master response from cpu).
//    as soon as enough bytes have been received, send the
//    response on AJIT_to_ENV_debug_response pipe.
//
//  Note cpu_to_debug_pipe should be deep!
void debugSpiMasterDaemon();


// listen on CONSOLE_to_SERIAL_Rx pipe. As soon
// as you get a byte, write SPI master commands
// to transfer it as a pair of hex bytes
// using noblock_serial_to_cpu pipe.
void listenOnSerialRxDaemon();

//
// listen on cpu_to_serial pipe.
//   as soon as a byte is assembled, send it
//   to SERIAL_TX_to_CONSOLE
//
void listenOnSerialTxDaemon();

// collect non-block information and
// ship it to the CPU.
void sendToCpuDaemon();

// listen on incoming from CPU
//    debug bytes (feed to debugResponseDaemon)
//    serial bytes (feed directly to SERIAL_TX_to_CONSOLE pipe)
void listenOnCpuDaemon();


// register pipes and start daemons!
void startAggregatorDaemons();

#endif
