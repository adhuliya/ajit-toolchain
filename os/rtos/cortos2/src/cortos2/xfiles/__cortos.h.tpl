// NOTE:
// All symbols for internal cortos' use are prefixed with `__`.
// The declarations in this header is only for cortos' internal use.

#ifndef CORTOS_INTERNAL_H
#define CORTOS_INTERNAL_H

#include "cortos.h"

////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_memory_layout
////////////////////////////////////////////////////////////////////////////////

// All these memory layout macros (without the leading '__')
// are also defined in the cortos.h header file.

// First Address 0x0:
// Few instruction to start the bootup initializtion.

// Memory region reserved for cortos' misc internal use.
#define __RESERVED_MEM_START_ADDR {{ confObj.memoryLayout.reserved.getFirstByteAddr() }}
#define __RESERVED_MEM_END_ADDR {{ confObj.memoryLayout.reserved.getLastByteAddr() }}

// // Details related to the user scratch space.
// #define __SCRATCH_SPACE_START_ADDR
// #define __SCRATCH_SPACE_END_ADDR
// #define __TOTAL_SCRATCH_SPACE_IN_BYTES

// Details of the cortos reserved lock vars (not available to the user)
#define __RES_LOCK_VARS_START_ADDR {{ confObj.software.locks.resLocksStartAddr }}
#define __RES_LOCK_VARS_END_ADDR {{ confObj.software.locks.resLocksStartAddr + confObj.software.locks.resLocks - 1 }}
#define __MAX_RES_LOCK_VARS {{ confObj.software.locks.resLocks }}

// Details of the lock vars available to the user.
#define __LOCK_VARS_START_ADDR {{ confObj.software.locks.userLocksStartAddr }}
#define __LOCK_VARS_END_ADDR {{ confObj.software.locks.userLocksStartAddr + confObj.software.locks.userLocks - 1 }}
#define __MAX_LOCK_VARS {{ confObj.software.locks.userLocks }}

// Details of the lock vars available to the user.
#define __Q_LOCK_VARS_START_ADDR {{ confObj.software.locks.queueLocksStartAddr }}
#define __Q_LOCK_VARS_END_ADDR {{ confObj.software.locks.queueLocksStartAddr + confObj.software.locks.queueLocks - 1 }}
#define __MAX_Q_LOCK_VARS {{ confObj.software.locks.queueLocks }}

// Details of the queue header array (one queue header per queue).
#define __Q_HEADERS_START_ADDR {{ confObj.software.queueSeq.headersStartAddr }}
#define __Q_HEADERS_END_ADDR {{ confObj.software.queueSeq.getHeadersEndAddr() }}
#define __MAX_Q_HEADERS {{ confObj.software.queueSeq.getTotalQueues() }}

// Queues available to the user (all the queues sit here).
#define __QUEUE_START_ADDR {{ confObj.software.queueSeq.msgStartAddr }}
#define __QUEUE_END_ADDR {{ confObj.software.queueSeq.getMsgEndAddr() }}
#define __MAX_QUEUES {{ confObj.software.queueSeq.getTotalQueues() }}
#define __QUEUE_MSG_SIZE_IN_BYTES {{ confObj.software.queueSeq.queueMsgSizeInBytes }}
#define __MAX_ELEMENTS_PER_QUEUE {{ confObj.software.queueSeq.elementsPerQueue }}
#define __MAX_QUEUE_SIZE_IN_BYTES {{ confObj.software.queueSeq.getTotalQueueSizeInBytes() }}

// Total heap space available in bytes.
% if confObj.software.bget.enable:
#define __HEAP_START_ADDR {{ confObj.software.bget.getStartAddr() }}
#define __HEAP_END_ADDR {{ confObj.software.bget.getEndAddr() }}
#define __TOTAL_HEAP_SIZE_IN_BYTES {{ confObj.software.bget.sizeInBytes }}
% end

// All program stacks sit here.
% for i, progThread in enumerate(confObj.software.program.programThreads):
#define __PROG_{{i}}_STACK_START_ADDR {{ progThread.getStackStartAddr() }}
#define __PROG_{{i}}_STACK_SIZE {{ progThread.getStackSizeInBytes() }}
% end

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_memory_layout
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_locking_declarations
////////////////////////////////////////////////////////////////////////////////

int __cortos_lock_acquire_buzy(int index);
int __cortos_lock_acquire(int index);
void __cortos_lock_release(int index);

#define __RES_LOCK_INDEX_BGET 0
#define __RES_LOCK_INDEX_PRINTF 1
#define __RES_LOCK_GET_Q_ID 2
#define __RES_LOCK_GET_LOCK_ID 3

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_locking_declarations
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_message_queues_declarations
////////////////////////////////////////////////////////////////////////////////

int __cortos_q_lock_acquire_buzy(int index);
int __cortos_q_lock_acquire(int index);
void __cortos_q_lock_release(int index);


typedef struct _CortosQueueHeader {
  int totalMsgs; // current total messages
  int readIndex;
  int writeIndex;
  int __; // to pad 4 bytes to make it 16 bytes.
} __CortosQueueHeader;

// Details of the queue header array (one queue header per queue).
#define __Q_HEADERS_START_ADDR {{ confObj.software.queueSeq.headersStartAddr }}
#define __Q_HEADERS_END_ADDR {{ confObj.software.queueSeq.getHeadersEndAddr() }}
#define __MAX_Q_HEADERS {{ confObj.software.queueSeq.getTotalQueues() }}

// Queues available to the user (all the queues sit here).
#define __QUEUE_START_ADDR {{ confObj.software.queueSeq.msgStartAddr }}
#define __QUEUE_END_ADDR {{ confObj.software.queueSeq.getMsgEndAddr() }}
#define __MAX_QUEUES {{ confObj.software.queueSeq.getTotalQueues() }}
#define __QUEUE_MSG_SIZE_IN_BYTES {{ confObj.software.queueSeq.queueMsgSizeInBytes }}
#define __MAX_ELEMENTS_PER_QUEUE {{ confObj.software.queueSeq.elementsPerQueue }}
#define __MAX_QUEUE_SIZE_IN_BYTES {{ confObj.software.queueSeq.getTotalQueueSizeInBytes() }}


#define __Q_START_INDEX 0
#define __AJIT_Q_BASE {{ confObj.software.queueSeq.msgStartAddr }}
#define __AJIT_Q_LEN {{ confObj.software.queueSeq.elementsPerQueue }}
#define __AJIT_Q_MSG_SIZE {{ confObj.software.queueSeq.queueMsgSizeInBytes }}

#define __AJIT_Q_HEADER_BASE {{ confObj.software.queueSeq.headersStartAddr }}
#define __AJIT_Q_HEADER_SIZE {{ confObj.software.queueSeq.queueHeaderSizeInBytes }}

#define __GET_MSG_ADDR(_BASE, _INDEX) \
((_BASE) + ((_INDEX) * (__AJIT_Q_MSG_SIZE)))

#define __INCREMENT_INDEX(_INDEX) \
(((((_INDEX)+1) % __AJIT_Q_LEN)) ? \
((((_INDEX)+1) % __AJIT_Q_LEN)) : __Q_START_INDEX)

/*
This computes the base address of the queue with id `queueId`.
*/
#define __GET_Q_ADDR(_Q_ID) \
((__AJIT_Q_BASE) + \
((__AJIT_Q_MSG_SIZE) * (__AJIT_Q_LEN) * (_Q_ID)));

/*
This computes the base address of the queue header with id `queueId`.
*/
#define __GET_Q_HEADER_ADDR(_Q_ID) \
((__AJIT_Q_HEADER_BASE) + \
((__AJIT_Q_HEADER_SIZE) * (_Q_ID)));

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_message_queues_declarations
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_bget_declarations
////////////////////////////////////////////////////////////////////////////////

// This function is called only once by AjitCoRTOS.
void __cortos_bpool(void);

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_bget_declarations
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_debug_routines
////////////////////////////////////////////////////////////////////////////////

// Enable serial device to use printf etc.
// This function is automatically called by cortos in `init_00.s`.
void __cortos_enable_serial();

// specially defined for logging purposes
int __cortos_log_printf(const char *level, const char *fileName,
  const char *funcName, int lineNum, const char *fmt, ...);

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_debug_routines
////////////////////////////////////////////////////////////////////////////////


#endif
