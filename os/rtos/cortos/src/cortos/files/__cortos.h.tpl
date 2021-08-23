% qHdrs = confObj.reservedMem.cortosQueueHeaders
% qQ = confObj.reservedMem.cortosQueues

// NOTE:
// All symbols for internal cortos' use are prefixed with `__`.
// The declarations in this header is only for cortos' internal use.

#ifndef CORTOS_INTERNAL_H
#define CORTOS_INTERNAL_H

#include "cortos.h"

////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_locking_declarations
////////////////////////////////////////////////////////////////////////////////

int __cortos_lock_acquire_buzy(int index);
int __cortos_lock_acquire(int index);
void __cortos_lock_release(int index);

#define __RES_LOCK_INDEX_BGET 0
#define __RES_LOCK_INDEX_PRINTF 1

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_locking_declarations
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_message_queues_declarations
////////////////////////////////////////////////////////////////////////////////

int __cortos_q_lock_acquire_buzy(int index);
int __cortos_q_lock_acquire(int index);
void __cortos_q_lock_release(int index);


#define __Q_START_INDEX 0
#define __AJIT_Q_BASE {{qQ.startAddr}}
#define __AJIT_Q_LEN {{cortosQueueLength}}
#define __AJIT_Q_MSG_SIZE {{cortosQueueMsgSize}}

#define __AJIT_Q_HEADER_BASE {{qHdrs.startAddr}}
#define __AJIT_Q_HEADER_SIZE {{cortosQueueHeaderSize}}

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
