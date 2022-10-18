#ifndef scoreboard_h____
#define scoreboard_h____

#define MAX_SCOREBOARD_REQUEST_SIZE    16
#define MAX_SCOREBOARD_RESPONSE_SIZE   16

#define MAX_NCORES	       4
#define NTHREADS_PER_CORE      2

#define MAX_CHANNELS	       256

// 
// Idea: multiple threads synchronize
//       on the score-board. No mutex
//       is needed.
//
// For threads I, J (I new J), there is
// an I->J channel and J->I channel.
//
// The I->J channel contains a request
// message field and a response message
// field.
//
// Thread I can send a request to J by
// writing a message in the I->J request
// field (and setting a flag).  Thread j
// will eventually pick up the request
// and at some point write a response
// into the I->J response field. 
// 
//

//
// Request types
//
// Just call the function pointed to by request_words[0]
// The function is void *func(uint32_t argc, uint32_t* argv, uint32_t* resp_argc, uint32_t* resp_argv) 
//
#define  CALL_FUNCTION		1

//
// request_words[0] is a pointer to an ajit_context.
// The server should switch to the context using swapcontext ...
//
#define  SWITCH_TO_CONTEXT	2


typedef struct ThreadChannel__ {

	uint32_t request_type;
	uint32_t request_id;
	uint32_t request_size; // in words.
	uint32_t request_words[MAX_SCOREBOARD_REQUEST_SIZE];

	uint32_t response_id;
	uint32_t response_size;
	uint32_t response_words[MAX_SCOREBOARD_RESPONSE_SIZE];
	
	uint32_t error_flag;

} ThreadChannel;

void initChannel(ThreadChannel* tc);
uint32_t checkChannelStatus(ThreadChannel* tc, uint32_t *no_job, uint32_t* job_completed, uint32_t* job_pending);
uint32_t isChannelFree(ThreadChannel* tc);
uint32_t channelHasPendingJob(ThreadChannel* tc);
void registerRequestToChannel(ThreadChannel* tc);
void registerResponseToChannel(ThreadChannel* tc);
uint32_t responseReadyInChannel(uint32_t* last_request_id, ThreadChannel* tc);

typedef struct ThreadScoreboard__ {
	
	uint32_t ncores;
	uint32_t nthreads_per_core;

	ThreadChannel channels[MAX_CHANNELS];

} ThreadScoreboard;

// clear all channels.
void initScoreboard(ThreadScoreboard* sb, uint32_t ncores, uint32_t nthreads_per_core);

// channel ID...  row major indexing of NxN matrix, where N is the total number of threads.
uint32_t channelId(ThreadScoreboard* sb,
				uint32_t req_core, uint32_t req_thread, 
				uint32_t resp_core, uint32_t resp_thread);
// return 0 on success.
uint32_t scheduleChannelJob (uint32_t job_type,
				uint32_t fn_or_ctxt, 
				uint32_t argc, 
				uint32_t* argv, 
				ThreadChannel* tc);

uint32_t checkScoreboardSlotStatus(ThreadScoreboard* sb,
				uint32_t req_core, uint32_t req_thread, 
				uint32_t resp_core, uint32_t resp_thread,
				uint32_t *no_job, uint32_t* job_completed, uint32_t* job_pending);

// return 1 if slot is free
uint32_t isScoreboardSlotFree(ThreadScoreboard* sb,
				uint32_t req_core, uint32_t req_thread, 
				uint32_t resp_core, uint32_t resp_thread);

// return 1 if slot has pending job
uint32_t jobPendingInScoreboardSlot(ThreadScoreboard* sb,
				uint32_t req_core, uint32_t req_thread, 
				uint32_t resp_core, uint32_t resp_thread);

//
// find a worker thread..
//    thread 0,0 can request thread 0,1
//    thread i,j  can request thread p,q if
//           - thread p,0 and thread p,1 are free
//           - thread p,0 is selected...
//
// return 0 on success
uint32_t selectScoreboardWorker(ThreadScoreboard* sb, 
					uint32_t requester_core,
					uint32_t requester_thread,
					uint32_t insist_on_same_core,
					ThreadChannel** tc);
		

// job
uint32_t selectScoreboardJob (ThreadScoreboard* sb, uint32_t job_core, uint32_t job_thread, ThreadChannel** tc);
		

// Note:  max_job_count = 0 implies no limit on jobs (run forever)
//	  else, after max_job_count jobs, scheduler exits.
void sidekickServer  (uint32_t max_job_count,
					uint32_t core_id, uint32_t thread_id, ThreadChannel* tc);
void scoreboardServer(uint32_t max_job_count,
					uint32_t core_id, uint32_t thread_id, ThreadScoreboard* sb); 

// return 0 on success.
uint32_t scheduleScoreboardJob (uint32_t requester_core, uint32_t requester_thread,
					uint32_t job_type,
					uint32_t fn_or_ctxt, 
					uint32_t argc, 
					uint32_t* argv, 
					ThreadScoreboard* sb);

#endif
