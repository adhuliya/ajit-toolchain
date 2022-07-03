#ifndef scoreboard_h____
#define scoreboard_h____

#define INARG_BUFFER_SIZE    256
#define OUTARG_BUFFER_SIZE   256

#define MAX_NCORES	       4
#define NTHREADS_PER_CORE      2

// 
// Idea: the two threads synchronize
//       on the score-board. No mutex
//       is needed.
//
typedef ScoreBoardBase__ {

	// which thread owns (can write)
	// this scoreboard?
	uint32_t owner_core;
	uint32_t owner_thread;
	uint32_t state;

	// synchronization ...
	uint32_t clock_counter;

	// jobs for the other guy.
	//   job_pointer is a pointer to a function.
	uint32_t job_pointer;
	uint32_t job_sequence_id;
	uint32_t job_core;
	uint32_t job_thread;
	
	//
	// arguments to be passed to
	// job
	//
	//
	uint32_t inarg_pointer;
	uint32_t inarg_count;


	// sequence id.
	uint32_t completed_job_sequence_id;
	uint32_t caller_core;
	uint32_t caller_thread;

	//
	// results from executing job.
	//
	uint32_t outarg_pointer;
	uint32_t outarg_count;

} ScoreBoardBase;

typedef ScoreBoard__ {
	ScoreBoardBase base[MAX_NCORES][NTHREADS_PER_CORE];
} ScoreBoard; 

// init all to 0.
void initScoreBoard(ScoreBoard* sb, uint32_t core_id, uint32_t thread_id);

// schedule job.
void scheduleJob(ScoreBoard* sb, 
			uint32_t owner_core, 
			uint32_t owner_thread,
			uint32_t job_core,  
			uint32_t job_thread,
			uint32_t fn_ptr,
			uint32_t arg_ptr);


// return 1 if there is a job.
uint32_t getJob(ScoreBoard* sb, 
			uint32_t scheduler_core,
			uint32_t scheduler_thread,
			uint32_t job_core,
			uint32_t job_thread,
			uint32_t sequence_id,
			uint32_t** inarg_buffer,
			uint32_t* inarg_count);

// complete the job..
void completeJob (ScoreBoard* sb,
				uint32_t  sequence_id,
				uint32_t* outarg_buffer,
				uint32_t  outarg_count);

#endif
