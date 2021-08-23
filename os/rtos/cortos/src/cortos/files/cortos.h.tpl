
// NOTE:
// All symbols for cortos' internal use are prefixed with `__`,
// and can be mostly found in `cortos_internal.h` header file.

#ifndef CORTOS_H
#define CORTOS_H

////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_global_constants
////////////////////////////////////////////////////////////////////////////////

// Maximum synchronization vars available to the user.
#define MAX_SYNC_VARS TODO

// Maximum queues available to the user.
#define MAX_QUEUES TODO

// Total heap space available in bytes.
#define TOTAL_HEAP_SPACE_IN_BYTES TODO

// Total scratch space in bytes.
#define TOTAL_SCRATCH_SPACE_IN_BYTES TODO

// For current logging level see the logging declarations ahead.

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_global_constants
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


typedef struct _CortosQueueHeader {
  int totalMsgs; // current total messages
  int readIndex;
  int writeIndex;
  int __; // to pad 4 bytes to make it 16 bytes.
} CortosQueueHeader;

/*
Write a CortosMessage.
  - Returns zero if the queue is full.
  - Returns non-zero if the msg was added.
*/
int writeCortosMessage(int queueId, CortosMessage *msg);

/*
Read a CortosMessage.
  - Returns zero if the queue is empty.
  - Returns non-zero if the msg was put into the *msg location.
*/
int readCortosMessage(int queueId, CortosMessage *msg);

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

#define LOG_LEVEL_ALL       10
#define LOG_LEVEL_TRACE     20
#define LOG_LEVEL_DEBUG     30
#define LOG_LEVEL_INFO      40
#define LOG_LEVEL_ERROR     50
#define LOG_LEVEL_CRITICAL  60
#define LOG_LEVEL_NONE      100

#define CORTOS_LOG_LEVEL {{confObj.logLevel.value}}
#define CORTOS_LOG_LEVEL_NAME "{{confObj.logLevel.name}}"

% for level in consts.LEVEL_ORDER:
% if level.value >= confObj.logLevel.value:
#define CORTOS_{{level.name}}(...) \
__cortos_log_printf("{{level.name}}", __FILE__, __func__, __LINE__, __VA_ARGS__);
% else:
#define CORTOS_{{level.name}}(...)     /*blank*/
% end
% end

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_logging_declarations
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_scratch_pad_area
////////////////////////////////////////////////////////////////////////////////
% count = 0
% intVarsMemRegion = confObj.reservedMem.cortosSharedIntVars
% for i in range(intVarsMemRegion.sizeInBytes):
% if i % 4 == 0:
% addr = intVarsMemRegion.startAddr + i
#define SHARED_INT_ADDR_{{count}} {{hex(addr)}}  // Decimal: {{addr}}
% count += 1
% end
% end
////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_scratch_pad_area
////////////////////////////////////////////////////////////////////////////////


#endif
