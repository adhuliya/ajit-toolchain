#ifndef dq_h____
#define dq_h____

#define DISPATCH_QUEUE_SIZE 8
#define DISPATCH_QUEUE_MASK (DISPATCH_QUEUE_SIZE - 1)

typedef struct dispatchRec__ {

	uint32_t thread_id;
	void*  fn;
	void*  arg;

} dispatchRec;

typedef struct dispatchQueue__ {
	dispatchRec jobs[DISPATCH_QUEUE_SIZE];
	int write_pointer;
	int read_pointer;
} dispatchQueue;

int initDispatchQueue(dispatchQueue* dq);

//return 1 if initialized
int isDispatchQueueInitialized(dispatchQueue* dq);

//return 0 on success.
int pushIntoDispatchQueue(dispatchQueue* dq, int thread_id, void* fn, void* arg);

//return non-zero thread-id on success.
int popFromDispatchQueue(dispatchQueue* dq, void** fn, void** arg);

#endif
