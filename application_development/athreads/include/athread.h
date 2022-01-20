#ifndef _ATHREAD_H___
#define _ATHREAD_H___

#define MAX_ACTIVE_THREADS   256

#define THREAD_UNALLOCATED   0
#define THREAD_ALLOCATED     1
#define THREAD_ON_DISPATCH_Q 2
#define THREAD_RUNNING	     3
#define THREAD_COMPLETED     4

#define AMUTEX_ACQUIRE(x) acquire_mutex_using_swap((int) &(x));
#define AMUTEX_RELEASE(x) release_mutex_using_swap((int) &(x));

typedef struct _athreadManager {


	// initialized to 0.  For inter-core
	// synchronization, this variable should
	// be mapped to an uncacheable location.
	uint32_t        atm_mutex_var; 

	uint8_t 	thread_status[MAX_ACTIVE_THREADS];
	dispatchQueue 	dq;

} athreadManager;

// start up..  Create athread manager.
int athreadManagerInit(athreadManager* atm);


// returns a non-zero thread id between 1 and MAX_ACTIVE_THREADS
int athreadAllocateThread(athreadManager* atm);

// deallocates the thread thread_id
int athreadDeallocateThread(athreadManager* atm, int thread_id);

// puts the thread on the dispatch queue.
int athreadDispatchThread (athreadManager* atm, int thread_id, void* fn, void* arg);

// short cut: allocate and dispatch (return allocated thread_id).
int athreadCreateThread(void* fn, void *arg);

// returns thread status as listed above.
int athreadThreadStatus (athreadManager* atm, int thread_id);

//
// inform the atm that thread thread_id has finished
//
int athreadReturn (athreadManager* atm, int thread_id);

// spin-wait for thread to complete..
int athreadJoinThread (athreadManager* atm, int thread_id);

// get thread from atm in order to run it.
int athreadGetThreadToRun(athreadManager* atm, void** fn, void** arg);

// Find an athread to run, run it, and mark it as returned,
// and finally deallocate it... return the thread-id of
// the thread that was just run.
int athreadRunDispatchedThread (athreadManager* atm);

#endif

