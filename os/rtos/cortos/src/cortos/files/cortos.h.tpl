% qHdrs = confObj.reservedMem.cortosQueueHeaders
% qQ = confObj.reservedMem.cortosQueues

#ifndef CORTOS_H
#define CORTOS_H

////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_locking_declarations
////////////////////////////////////////////////////////////////////////////////

int cortos_lock_acquire_buzy(int index);
int cortos_lock_acquire(int index);
void cortos_lock_release(int index);

// Only for AjitCoRTOS internal use (reserved: hence `_res_` in name.)
int cortos_res_lock_acquire_buzy(int index);
int cortos_res_lock_acquire(int index);
void cortos_res_lock_release(int index);

#define RES_LOCK_INDEX_BGET 0
#define RES_LOCK_INDEX_PRINTF 1

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_locking_declarations
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_message_queues_declarations
////////////////////////////////////////////////////////////////////////////////

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
Sends a CortosMessage.
  - Returns zero if the queue is full.
  - Returns non-zero if the msg was added.
*/
int writeCortosMessage(int queueId, CortosMessage *msg);

/*
Gets a CortosMessage.
  - Returns zero if the queue is empty.
  - Returns non-zero if the msg was put into the *msg location.
*/
int readCortosMessage(int queueId, CortosMessage *msg);


int cortos_q_lock_acquire_buzy(int index);
int cortos_q_lock_acquire(int index);
void cortos_q_lock_release(int index);


#define Q_START_INDEX 0
#define AJIT_Q_BASE {{qQ.startAddr}}
#define AJIT_Q_LEN {{cortosQueueLength}}
#define AJIT_Q_MSG_SIZE {{cortosQueueMsgSize}}

#define AJIT_Q_HEADER_BASE {{qHdrs.startAddr}}
#define AJIT_Q_HEADER_SIZE {{cortosQueueHeaderSize}}

#define GET_MSG_ADDR(_BASE, _INDEX) \
((_BASE) + ((_INDEX) * (AJIT_Q_MSG_SIZE)))

#define INCREMENT_INDEX(_INDEX) \
(((((_INDEX)+1) % AJIT_Q_LEN)) ? \
((((_INDEX)+1) % AJIT_Q_LEN)) : Q_START_INDEX)

/*
This computes the base address of the queue with id `queueId`.
*/
#define GET_Q_ADDR(_Q_ID) \
((AJIT_Q_BASE) + \
((AJIT_Q_MSG_SIZE) * (AJIT_Q_LEN) * (_Q_ID)));

/*
This computes the base address of the queue header with id `queueId`.
*/
#define GET_Q_HEADER_ADDR(_Q_ID) \
((AJIT_Q_HEADER_BASE) + \
((AJIT_Q_HEADER_SIZE) * (_Q_ID)));

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_message_queues_declarations
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_bget_declarations
////////////////////////////////////////////////////////////////////////////////

typedef long cortos_bufsize;

// This function is called only once by AjitCoRTOS.
void __cortos_bpool(void);

// get/allocate a memory of `size` bytes
// Note: Some internal space is wasted to make size align to 2^3 boundary.
void *cortos_bget(cortos_bufsize size);

// release/free an allocated memory
void cortos_brel(void *buf);

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_bget_declarations
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_shared_integers_addresses
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
// BLOCK END  : cortos_shared_integers_addresses
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_debug_routines
////////////////////////////////////////////////////////////////////////////////

// exits after putting code into asr16.
// Any non-zero code is considered error.
// Any error code >= 4096 is reserved for CoRTOS.
void cortos_exit(unsigned int error_code);

// Enable serial device to use printf
void cortos_enable_serial();

// printf routine offered by Cortos
int cortos_printf(const char *fmt, ...);

// specially defined for logging purposes
int cortos_log_printf(const char *level, const char *fileName,
  const char *funcName, int lineNum, const char *fmt, ...);

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
cortos_log_printf("{{level.name}}", __FILE__, __func__, __LINE__, __VA_ARGS__);
% else:
#define CORTOS_{{level.name}}(...)     /*blank*/
% end
% end


////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_logging_declarations
////////////////////////////////////////////////////////////////////////////////


#endif
