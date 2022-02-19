
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
#define CORTOS_TOTAL_HW_THREADS {{confObj.hardware.cpu.totalThreads()}}
#define CORTOS_TOTAL_SW_THREADS {{len(confObj.software.program.programThreads)}}

// For more information on the APIs read the respective headers.
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

// Details of the cortos reserved lock vars (not available to the user)
#define RES_LOCK_VARS_START_ADDR {{ confObj.software.locks.resLocksStartAddr }}
#define RES_LOCK_VARS_END_ADDR {{ confObj.software.locks.resLocksStartAddr + confObj.software.locks.resLocks - 1 }}
#define MAX_RES_LOCK_VARS {{ confObj.software.locks.resLocks }}

// Details of the lock vars available to the user.
#define LOCK_VARS_START_ADDR {{ confObj.software.locks.userLocksStartAddr }}
#define LOCK_VARS_END_ADDR {{ confObj.software.locks.userLocksStartAddr + confObj.software.locks.userLocks - 1 }}
#define MAX_LOCK_VARS {{ confObj.software.locks.userLocks }}

// Details the lock vars for user queues
#define Q_LOCK_VARS_START_ADDR {{ confObj.software.locks.queueLocksStartAddr }}
#define Q_LOCK_VARS_END_ADDR {{ confObj.software.locks.queueLocksStartAddr + confObj.software.locks.queueLocks - 1 }}
#define MAX_Q_LOCK_VARS {{ confObj.software.locks.queueLocks }}

// Details CoRTOS Queues
#define TOTAL_CORTOS_QUEUES {{ len(confObj.software.queueSeq) }}

% if confObj.software.bget.enable:
#define CORTOS_HEAP_START_ADDR {{ confObj.software.bget.getStartAddr() }}
#define CORTOS_HEAP_END_ADDR {{ confObj.software.bget.getEndAddr() }}
#define CORTOS_TOTAL_HEAP_SIZE_IN_BYTES {{ confObj.software.bget.sizeInBytes }}
% end

// All program stacks sit here.
% for i, progThread in enumerate(confObj.software.program.programThreads):
#define PROG_{{i}}_STACK_START_ADDR {{ progThread.getStackStartAddr() }}
#define PROG_{{i}}_STACK_SIZE {{ progThread.getStackSizeInBytes() }}
% end

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_memory_layout
////////////////////////////////////////////////////////////////////////////////


#endif
