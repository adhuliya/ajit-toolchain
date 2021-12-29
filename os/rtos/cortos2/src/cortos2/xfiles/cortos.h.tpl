
// NOTE:
// All symbols for cortos' internal use are prefixed with `__`,
// and can be mostly found in `__cortos.h` header file.

#ifndef CORTOS_H
#define CORTOS_H

#include <stdint.h>

// A flag for the programmer to know if the environment
// is provided by CORTOS or not.
#define CORTOS

#define CORTOS_THREADS {{len(confObj.software.program.programThreads)}}

////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_memory_layout
////////////////////////////////////////////////////////////////////////////////

// All these memory layout macros (without the leading '__')
// are also defined in the cortos.h header file.

// First Address 0x0:
// Few instruction to start the bootup initializtion.

// Memory region reserved for cortos' misc internal use.
#define RESERVED_MEM_START_ADDR {{ confObj.memoryLayout.reserved.getFirstByteAddr() }}
#define RESERVED_MEM_END_ADDR {{ confObj.memoryLayout.reserved.getLastByteAddr() }}

// // Details related to the user scratch space.
// #define SCRATCH_SPACE_START_ADDR
// #define SCRATCH_SPACE_END_ADDR
// #define TOTAL_SCRATCH_SPACE_IN_BYTES

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

// Total heap space available in bytes.
% if confObj.software.bget.enable:
#define HEAP_START_ADDR {{ confObj.software.bget.getStartAddr() }}
#define HEAP_END_ADDR {{ confObj.software.bget.getEndAddr() }}
#define TOTAL_HEAP_SIZE_IN_BYTES {{ confObj.software.bget.sizeInBytes }}
% end

// All program stacks sit here.
% for i, progThread in enumerate(confObj.software.program.programThreads):
#define PROG_{{i}}_STACK_START_ADDR {{ progThread.getStackStartAddr() }}
#define PROG_{{i}}_STACK_SIZE {{ progThread.getStackSizeInBytes() }}
% end

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_memory_layout
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_locking_declarations
////////////////////////////////////////////////////////////////////////////////

// Usage Note:
// cortos_lock_acquire_buzy(<index: an-integer-index>);
//   CRITICAL_SECTION_CODE...
// cortos_lock_release(<index: an-integer-index>);
// ----or-------or--------
// status = cortos_lock_acquire(<index: an-integer-index>);
// if (status == 1) {
//   CRITICAL_SECTION_CODE...
//   cortos_lock_release(<index: an-integer-index>);
// }

// NOTE: Use the same index to synchronize two or more threads.

int cortos_lock_acquire_buzy(int index);
int cortos_lock_acquire(int index);
void cortos_lock_release(int index);

// Cacheable locks
int cortos_lock_acquire_buzy_cacheable(int index);
int cortos_lock_acquire_cacheable(int index);
void cortos_lock_release_cacheable(int index);

// Reserve an unused lock variable id from cortos.
//   It returns the lock variable id of the lock reserved.
//   If no lock is available it returns -1.
// Once a lock is reserved it is held by the caller,
// until it is freed.
int cortos_reserveLockVar();

// Free a lock variable for reuse by cortos.
void cortos_freeLockVar(int lockId);

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_locking_declarations
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_message_queues_declarations
////////////////////////////////////////////////////////////////////////////////

// A cortos' queue message.
typedef union _CortosMessage32Bytes {
  char charArr[32];
  int intArr[8];
  float floatArr[8];
  double doubleArr[4];

  struct {
    int a_code;
    void *a_ptr; // pointer to a location
    int *a_size; // in bytes
    int a_intArr[5];
  };

  struct {
    int b_code;
    int b_intArr[7];
  };

  struct {
    int c_code;
    char c_charArr[28];
  };

  struct {
    int d_code;
    int d_val1;
    double d_d1;
    double d_d2;
    double d_d3;
  };

} CortosMessage;


/* Write a CortosMessage.
  - Returns zero if the queue is full.
  - Returns non-zero if the msg was added.
*/
int cortos_writeMessage(int queueId, CortosMessage *msg);

/* Read a CortosMessage.
  - Returns zero if the queue is empty.
  - Returns non-zero if the msg was put into the *msg location.
*/
int cortos_readMessage(int queueId, CortosMessage *msg);

// Reserve an unused queue from cortos.
//   It returns the queue id of the queue reserved.
//   If no queue is available it returns -1.
// Once a queue is reserved it is held by the caller,
// until it is freed.
int cortos_reserveQueue();

// Free a queue for reuse by cortos.
void cortos_freeQueue(int queueId);

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_message_queues_declarations
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_bget_declarations
////////////////////////////////////////////////////////////////////////////////

typedef long cortos_bufsize;

// get/allocate a memory of `size` bytes
// Note: Some internal space is wasted to make size align to 2^3 boundary.
void *cortos_bget(cortos_bufsize size);

// release/free an allocated memory chunk
void cortos_brel(void *buf);

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_bget_declarations
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_debug_routines
////////////////////////////////////////////////////////////////////////////////

// Exit after putting error_code into asr16.
// Any non-zero code is considered error.
// Any error code <= 255 is reserved for CoRTOS.
// A user code may use 0 for successful exit,
// or a value >=256 as an error exit code.
// Cortos exit codes and their meaning:
//      0       Successful Exit
//      1       Error in init_00.s
void cortos_exit(unsigned int error_code);

// printf routine offered by Cortos
// This needs the serial device to be enabled.
// __cortos_enable_serial() enables the serial device and is
// automatically called in init_00.s file.
int cortos_printf(const char *fmt, ...);

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_debug_routines
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_logging_declarations
////////////////////////////////////////////////////////////////////////////////

// The programmer can log messages in CoRTOS using logging macros.
// These macros pass the arguments to printf function internally.
// For example, to log a TRACE message
//      CORTOS_TRACE("Current count: %d", count);
// When the user disables all logging or some log levels,
// all the macros of disabled log levels expand to a blank space,
// which removes the logging message entirely.

#define LOG_LEVEL_ALL       10
#define LOG_LEVEL_TRACE     20
#define LOG_LEVEL_DEBUG     30
#define LOG_LEVEL_INFO      40
#define LOG_LEVEL_ERROR     50
#define LOG_LEVEL_CRITICAL  60
#define LOG_LEVEL_NONE      100

#define CORTOS_LOG_LEVEL {{confObj.software.build.logLevel.value}}
#define CORTOS_LOG_LEVEL_NAME "{{ confObj.software.build.logLevel.name }}"

% for level in consts.LEVEL_ORDER:
% if level.value >= confObj.software.build.logLevel.value:
#define CORTOS_{{ level.name }}(...) \
__cortos_log_printf("{{ level.name }}", __FILE__, __func__, __LINE__, __VA_ARGS__);

% else:
#define CORTOS_{{ level.name }}(...)     /*blank*/

% end
% end

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_logging_declarations
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_utility_routines
////////////////////////////////////////////////////////////////////////////////

// reads high and low clock counters to return
// the value...   Returns the number of elapsed ticks
// where one thick is 256 clock cycles.
//   (Thus, if the clock is 100MHz, 1 tick is 2.56 micro-seconds).
inline uint64_t cortos_get_clock_time();

// sleep for specified number of clock cycles
inline void cortos_sleep(uint32_t clock_cycles);

// Returns the thread id of the system.
// 0 for Thread 00
// 1 for Thread 01
// 2 for Thread 10
// 3 for Thread 11
// ...
char cortos_get_thread_id();

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_utility_routines
////////////////////////////////////////////////////////////////////////////////



#endif
