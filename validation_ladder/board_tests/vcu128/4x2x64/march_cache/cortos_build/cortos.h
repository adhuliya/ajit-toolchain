
// NOTE:
// All symbols for cortos' internal use are prefixed with `__`.

#ifndef CORTOS_H
#define CORTOS_H

#include <stdint.h>    // to use uint32_t, etc.

// TODO: can ee_printf support this?
// #include <inttypes.h>  // to pirint uint32_t, etc. printf("%" PRIu32 "\n", i);

// A flag for the programmer to know if the environment
// is provided by CORTOS or not.
#define CORTOS_ENV

// Total hardware and software threads available in the system.
#define CORTOS_TOTAL_HW_THREADS 8
#define CORTOS_TOTAL_SW_THREADS 8

// For more information on the APIs please read the respective headers.
#include <cortos_locks.h>       // API for locks
#include <cortos_logging.h>     // API for logging (CORTOS_DEBUG(),...)
#include <cortos_bget.h>        // API for heap memory
#include <cortos_utils.h>       // API for cortos misc utility functions
#include <cortos_traps.h>       // API for traps
#include <cortos_queues.h>      // API for message passing queues

////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_memory_layout
////////////////////////////////////////////////////////////////////////////////

// Initial part is occupied by the program text.

#define CORTOS_HEAP_START_ADDR 98304
#define CORTOS_HEAP_END_ADDR 1122303
#define CORTOS_TOTAL_HEAP_SIZE_IN_BYTES 1024000

// All program stacks sit here.
#define PROG_0_STACK_START_ADDR 1134496
#define PROG_0_STACK_SIZE 8191
#define PROG_1_STACK_START_ADDR 1146784
#define PROG_1_STACK_SIZE 8191
#define PROG_2_STACK_START_ADDR 1159072
#define PROG_2_STACK_SIZE 8191
#define PROG_3_STACK_START_ADDR 1171360
#define PROG_3_STACK_SIZE 8191
#define PROG_4_STACK_START_ADDR 1183648
#define PROG_4_STACK_SIZE 8191
#define PROG_5_STACK_START_ADDR 1195936
#define PROG_5_STACK_SIZE 8191
#define PROG_6_STACK_START_ADDR 1208224
#define PROG_6_STACK_SIZE 8191
#define PROG_7_STACK_START_ADDR 1220512
#define PROG_7_STACK_SIZE 8191

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_memory_layout
////////////////////////////////////////////////////////////////////////////////


#endif
