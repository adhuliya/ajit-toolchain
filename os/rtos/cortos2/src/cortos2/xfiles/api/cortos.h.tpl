
// NOTE:
// All symbols for cortos' internal use are prefixed with `__`.

#ifndef CORTOS_H
#define CORTOS_H

#include <stdint.h>

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

// Memory region reserved for cortos' misc internal use.
#define RESERVED_MEM_START_ADDR {{ confObj.memoryLayout.reserved.getFirstByteAddr() }}
#define RESERVED_MEM_END_ADDR {{ confObj.memoryLayout.reserved.getLastByteAddr() }}

// Details of the cortos reserved lock vars (not available to the user)
#define RES_LOCK_VARS_START_ADDR {{ confObj.software.locks.resLocksStartAddr }}
#define RES_LOCK_VARS_END_ADDR {{ confObj.software.locks.resLocksStartAddr + confObj.software.locks.resLocks - 1 }}
#define MAX_RES_LOCK_VARS {{ confObj.software.locks.resLocks }}

// Details of the lock vars available to the user.
#define LOCK_VARS_START_ADDR {{ confObj.software.locks.userLocksStartAddr }}
#define LOCK_VARS_END_ADDR {{ confObj.software.locks.userLocksStartAddr + confObj.software.locks.userLocks - 1 }}
#define MAX_LOCK_VARS {{ confObj.software.locks.userLocks }}

// Details of the lock vars available to the user.
#define Q_LOCK_VARS_START_ADDR {{ confObj.software.locks.queueLocksStartAddr }}
#define Q_LOCK_VARS_END_ADDR {{ confObj.software.locks.queueLocksStartAddr + confObj.software.locks.queueLocks - 1 }}
#define MAX_Q_LOCK_VARS {{ confObj.software.locks.queueLocks }}

// Details of the queue header array (one queue header per queue).
#define Q_HEADERS_START_ADDR {{ confObj.software.queueSeq.headersStartAddr }}
#define Q_HEADERS_END_ADDR {{ confObj.software.queueSeq.getHeadersEndAddr() }}
#define MAX_Q_HEADERS {{ confObj.software.queueSeq.getTotalQueues() }}

// Queues available to the user (all the queues sit here).
#define QUEUE_START_ADDR {{ confObj.software.queueSeq.msgStartAddr }}
#define QUEUE_END_ADDR {{ confObj.software.queueSeq.getMsgEndAddr() }}
#define MAX_QUEUES {{ confObj.software.queueSeq.getTotalQueues() }}
#define QUEUE_MSG_SIZE_IN_BYTES {{ confObj.software.queueSeq.queueMsgSizeInBytes }}
#define MAX_ELEMENTS_PER_QUEUE {{ confObj.software.queueSeq.elementsPerQueue }}
#define MAX_QUEUE_SIZE_IN_BYTES {{ confObj.software.queueSeq.getTotalQueueSizeInBytes() }}

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
