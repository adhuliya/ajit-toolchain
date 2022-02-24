#ifndef _ATHREAD_H___
#define _ATHREAD_H___

#define MAX_ACTIVE_THREADS   256

// thread status
#define THREAD_UNALLOCATED   0
#define THREAD_ALLOCATED     1
#define THREAD_RUNNING	     2
#define THREAD_COMPLETED     3


#ifdef CORTOS
#define AMUTEX_ACQUIRE(x) cortos_lock_acquire_buzy(x);
#define AMUTEX_RELEASE(x) cortos_lock_release(x);
#else
#define AMUTEX_ACQUIRE(x) acquire_mutex_using_swap((int) &(x));
#define AMUTEX_RELEASE(x) release_mutex_using_swap((int) &(x));
#endif

typedef struct athreadRec__ {

	uint32_t thread_id;
	uint32_t thread_status;
	uint32_t priority;

	uint64_t sequence_id;


	// function returns an integer value
	int*  fn;
	
	// an argument to the function..
	void*  arg;

	int    return_value;
} athread_t;

typedef struct _athreadManager {


	// initialized to 0.  For inter-core
	// synchronization, this variable should
	// be mapped to an uncacheable location.
	uint32_t        atm_mutex_var; 
	uint64_t        thread_counter;
	athread_t 	threads[MAX_ACTIVE_THREADS];

} athreadManager;

// start up..  Create athread manager.
uint32_t athreadManagerInit(athreadManager* atm);

// returns a non-zero thread id between 1 and MAX_ACTIVE_THREADS
// on success, 0 on failure.
uint32_t athreadCreateThread(athreadManager* atm, 
					uint32_t priority, int* fn, void* arg);

// returns 0 on success.
uint32_t athreadDestroyThread(athreadManager* atm, uint32_t thread_id);

// marks the thread as allocated and restarts it...
// Note: returns 0 if this was successful.  It will fail if
// the thread is not in COMPLETED state.
uint32_t athreadRestartThread(athreadManager* atm, uint32_t thread_id);

// returns thread status as listed above.
uint32_t athreadThreadStatus (athreadManager* atm, uint32_t thread_id);

// returns  0 on success, thread function and args are returned.
uint32_t athreadThreadGetArgs (athreadManager* atm, uint32_t thread_id, int** fn, void** arg);

// returns  0 on success, thread function and return value are returned.
uint32_t athreadThreadGetReturnValue (athreadManager* atm, uint32_t thread_id, int* ret_value);
//
// inform the atm that thread thread_id has finished
//
uint32_t athreadReturn (athreadManager* atm, uint32_t thread_id);

// spin-wait for thread to complete..
uint32_t athreadJoinThread (athreadManager* atm, uint32_t thread_id);

//
// Will look for the highest-priority thread in the specified priority range.
// If there is more than one such thread, it will use the earliest creation time as a tie-breaker.
//
// The selected thread if any is immediately started.  The function returns when
// the selected thread completes (or immediately if no thread is found).
//
uint32_t athreadSelectAndRunThread(athreadManager* atm, uint32_t min_priority, uint32_t max_priority);

#endif

