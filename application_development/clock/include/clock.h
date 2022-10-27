#include <stdint.h>
#include <stdlib.h>

#define MAX_CLOCK_THREADS   16

typedef struct __ajit_clock {
	uint32_t number_of_threads;

	uint64_t time_stamps[MAX_CLOCK_THREADS];
	void*    arg_array[MAX_CLOCK_THREADS];

	uint8_t  used_arg_flags[MAX_CLOCK_THREADS]; 

	uint32_t free_thread_id;
	uint32_t synched_flags[MAX_CLOCK_THREADS];
} Aclock;


// initialize
void initAclock(Aclock* clk, uint32_t number_of_threads);

// number of threads synched using clock.
uint32_t getNumberOfThreads(Aclock* clk);

// return non-zero thread id on success
uint32_t registerThreadWithAclock(Aclock* clk);

// broadcast arg etc.
uint32_t synchStart (Aclock* clk, uint64_t time_stamp, uint32_t thread_id, void* arg);

// get arg.
//  0 on success..
uint32_t getSynchedArg (Aclock* clk, uint64_t time_stamp, uint32_t from_thread_id, void** arg);

// mark as used.
//  0 on success.
uint32_t markArgsAsUsed (Aclock* clk, uint64_t time_stamp, uint32_t thread_id);


// return 0 on success.
//   error codes
#define NOT_ALL_SYNCHED  1
#define NOT_ALL_USED_ARG 2
uint32_t synchComplete (Aclock* clk, uint64_t time_stamp, uint32_t thread_id);

