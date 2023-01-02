#ifndef datastruct_h___
#define datastruct_h___


typedef struct __CoroutineControl {
	ajit_context_t*   context;
	int id;
	int counter;
} CoroutineControl;

void coroutine_0 (void* ptr);
void coroutine_1 (void* ptr);

#endif
