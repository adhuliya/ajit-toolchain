#ifndef _aggregator_h___
#define _aggregator_h___



// listen on CONSOLE_to_SERIAL_Rx pipe. As soon
// as you get a byte, write SPI master commands
// to transfer it as a pair of hex bytes
// using noblock_serial_to_cpu pipe.
void listenOnSerialRxDaemon();

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
