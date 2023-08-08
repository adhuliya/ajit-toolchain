#ifndef datastruct_h___
#define datastruct_h___


typedef struct __CoroutineControl {
	ajit_context_t*   pcc;
	ajit_context_t*   pscheduler;
} CoroutineControl;

void coroutine_0 (CoroutineControl* ptr);
void coroutine_1 (CoroutineControl* ptr);

#endif
