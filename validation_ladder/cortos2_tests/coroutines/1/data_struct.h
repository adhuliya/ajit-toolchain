#ifndef datastruct_h___
#define datastruct_h___


typedef enum __CoroutineStatus {
	WAITING_FOR_INIT,
	INIT_DONE	
} CoroutineStatus;

typedef struct __CoroutineControl {
	ajit_context_t*   context;
	CoroutineStatus status;
} CoroutineControl;

void coroutine_0 (void* ptr);
void coroutine_1 (void* ptr);

#endif
