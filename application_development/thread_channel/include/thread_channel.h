#ifndef scoreboard_h____
#define scoreboard_h____

#define MAX_NCORES	       4
#define NTHREADS_PER_CORE      2
#define MAX_NTHREADS	       (MAX_NCORES * NTHREADS_PER_CORE)
#define NCHANNELS 	       (MAX_NTHREADS * MAX_NTHREADS)

#define __THREAD_ID(c,t)      ((NTHREADS_PER_CORE*c) + t)

#ifdef NO_CORTOS
#define PRINTF ee_printf
#else
#define PRINTF cortos_printf
#endif
/*
typedef enum {
	FREE=1,
	REQUESTED=2,
	IN_PROGRESS=3,
	COMPLETED=4
} ChannelStatus;
*/

#define CH_FREE        1
#define CH_REQUESTED   2
#define CH_IN_PROGRESS 3
#define CH_COMPLETED   4


typedef struct ThreadChannel__ {

	uint32_t id;
	uint32_t request_id;
	uint32_t response_id;
	void*    fn_ptr;
	void*    arg_ptr;

	// FREE, REQUESTED, COMPLETED
	int status;

} ThreadChannel;
#define __CHANNEL_IS_FREE(tc) (tc->status == CH_FREE)
#define __CHANNEL_IS_BUSY(tc) ((tc->status == CH_REQUESTED) || (tc->status == CH_IN_PROGRESS))
#define __CHANNEL_JOB_COMPLETED(tc) (tc->status == CH_COMPLETED)

void initChannel   (ThreadChannel* tc, uint32_t id);

// return 0 on success.
uint32_t scheduleChannelJob (ThreadChannel* tc, void *fn_ptr, void* arg_ptr);
// return 0 on success.
uint32_t getChannelResponse (ThreadChannel* tc, void** arg_ptr);
// return 0 on success.
uint32_t setChannelResponse (ThreadChannel* tc, void* arg_ptr);
// return 0 on success.
uint32_t getChannelJob (ThreadChannel* tc, void** __fn, void** __arg);

#endif
