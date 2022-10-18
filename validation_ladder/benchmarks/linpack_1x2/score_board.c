#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <cortos.h>
#include "ajit_access_routines.h"
#include "score_board.h"


void initChannel(ThreadChannel* tc)
{
	tc->request_id = 0;	
	tc->response_id = 0;
	tc->error_flag = 1;
}

uint32_t checkChannelStatus(ThreadChannel* tc, uint32_t *no_job, 
					uint32_t* job_completed, uint32_t* job_pending)
{
	*no_job = (tc->request_id == 0);
	*job_completed = (tc->request_id > 0) &&
				(tc->response_id == tc->request_id);
	*job_pending = (tc->request_id > 0) &&
				(tc->response_id != tc->request_id);
}

//
// returns 1 when there is a response..  updates last_request_id to
//   reflect that job has completed its cycle.
//
uint32_t responseReadyInChannel(uint32_t* last_request_id, ThreadChannel* tc)
{
	uint32_t ret_val = 0;
	if((tc->request_id != last_request_id) && (tc->response_id == tc->request_id))
	{
		int J;
		*last_request_id = tc->request_id;
		CORTOS_DEBUG("waitOnChannelResponse: returned... response_id=%d.\n", tc->response_id);
		for(J = 0; J < tc->response_size; J++)
		{
			CORTOS_DEBUG(" 0x%x ", tc->response_words[J]);
		}

		ret_val = 1;
	}
	return(ret_val);
}

void registerResponseToChannel(ThreadChannel* tc)
{
	uint32_t u = tc->response_id + 1;
	if(u == 0) u  = 1;
	tc->response_id = u;
}

void registerRequestToChannel(ThreadChannel* tc)
{
	uint32_t u = tc->request_id + 1;
	if(u == 0) u  = 1;
	tc->request_id = u;
}

uint32_t isChannelFree(ThreadChannel* tc)
{
	uint32_t no_job, job_completed, job_pending;
	checkChannelStatus(tc, &no_job, &job_completed, &job_pending);
	uint32_t retval = no_job || job_completed;
	return(retval);
}

uint32_t channelHasPendingJob(ThreadChannel* tc)
{
	uint32_t no_job, job_completed, job_pending;
	checkChannelStatus(tc, &no_job, &job_completed, &job_pending);
	return(job_pending);
}
// clear all channels.
void initScoreboard(ThreadScoreboard* sb, uint32_t ncores, uint32_t nthreads_per_core)
{
	int I;
	for(I = 0; I < MAX_CHANNELS; I++)
	{
		sb->channels[I].request_id  = 0;
		sb->channels[I].response_id = 0;
	}
}


// channel ID...  row major indexing of NxN matrix, where N is the total number of threads.
uint32_t channelId(ThreadScoreboard* sb,
		uint32_t req_core, uint32_t req_thread, 
		uint32_t resp_core, uint32_t resp_thread)
{
	uint32_t nthreads = sb->ncores * sb->nthreads_per_core;

	uint32_t req_tid  = (sb->nthreads_per_core * req_core) + req_thread;
	uint32_t resp_tid = (sb->nthreads_per_core * resp_core) + resp_thread;

	// matrix in row-major form.
	uint32_t channel_id = (req_tid * nthreads) + resp_tid;

	return(channel_id);
}

uint32_t checkScoreboardSlotStatus(ThreadScoreboard* sb,
		uint32_t req_core, uint32_t req_thread, 
		uint32_t resp_core, uint32_t resp_thread,
		uint32_t *no_job, uint32_t* job_completed, uint32_t* job_pending)
{
	uint32_t C = channelId(sb,req_core, req_thread, resp_core, resp_thread);
	checkChannelStatus (&(sb->channels[C]), no_job, job_completed, job_pending);
	return(0);
}


uint32_t isScoreboardSlotFree(ThreadScoreboard* sb,
		uint32_t req_core, uint32_t req_thread, 
		uint32_t resp_core, uint32_t resp_thread)
{
	uint32_t C = channelId(sb,req_core, req_thread, resp_core, resp_thread);
	uint32_t ret_val = isChannelFree(&(sb->channels[C]));
	return(ret_val);
}

uint32_t jobPendingInScoreboardSlot(ThreadScoreboard* sb,
		uint32_t req_core, uint32_t req_thread, 
		uint32_t resp_core, uint32_t resp_thread)
{
	uint32_t C = channelId(sb,req_core, req_thread, resp_core, resp_thread);
	uint32_t ret_val = channelHasPendingJob(&(sb->channels[C]));
	return(ret_val);
}

//
// find a worker thread..
//     bias towards finding a thread other than the requester...
//     but may select itself..
//
// returns 0 on success.
//
uint32_t selectScoreboardWorker (ThreadScoreboard* sb, 
					uint32_t requester_core,
					uint32_t requester_thread,
					uint32_t insist_on_same_core,
					ThreadChannel** tc)
{
	uint32_t ret_val = 1;
	uint32_t core_id, thread_id, score, sthread;
	uint32_t I;
	for(I = 0; I < sb->nthreads_per_core; I++)
	{
		thread_id  = (I + requester_thread + 1) & (sb->nthreads_per_core - 1);
		if(insist_on_same_core)
		{
			if(isScoreboardSlotFree(sb, requester_core, requester_thread,
						requester_core, thread_id))
			{
				score = requester_core;
				sthread = thread_id;
				ret_val = 0;
			}
		}
		else
		{
			uint32_t J;
			for(J = 0; J < sb->ncores; J++)
			{
				// give priority to a different core...
				core_id = (J + requester_core + 1) & (sb->ncores - 1);
				if(isScoreboardSlotFree(sb, requester_core, requester_thread,
							core_id, thread_id))
				{
					score = core_id;
					sthread = thread_id;
					ret_val = 0;
					break;
				}
			}
		}	
		if(ret_val == 0) break;
	}

	if(ret_val == 0)
	{
		uint32_t C = channelId(sb,requester_core, requester_thread, score, sthread);
		*tc = &(sb->channels[C]);
	}

	return(ret_val);
}

//
uint32_t selectScoreboardJob 
	(ThreadScoreboard* sb, uint32_t job_core, uint32_t job_thread, ThreadChannel** tc)
{
	uint32_t req_core, req_thread;
	uint32_t ret_val = 1;

	*tc = NULL;
	for(req_core = 0; req_core < sb->ncores; req_core++)
	{
		for(req_thread = 0; req_thread < sb->nthreads_per_core; req_thread++)
		{
			if(jobPendingInScoreboardSlot(sb, req_core, req_thread, job_core, job_thread))
			{
				uint32_t C = channelId(sb, req_core, req_thread, job_core, job_thread);
				*tc = &(sb->channels[C]);
				ret_val = 0;
				break;
			}
		}
		if(ret_val == 0)
			break;
	}
	return(ret_val);
}

void sidekickServer  (uint32_t max_job_count, uint32_t core_id, uint32_t thread_id, ThreadChannel* tc)
{
	void (*__fn)(uint32_t, uint32_t*, uint32_t*, uint32_t*);
	uint32_t job_count = 0;
	while(1)
	{
		if(channelHasPendingJob(tc))
			// job is waiting
		{
			CORTOS_DEBUG("sidekickServer: found job %d.\n", tc->request_id);
			__fn  =  tc->request_words[0];

			// strip off argv[0], use [1:...]
			(*__fn)(tc->request_size-1, &(tc->request_words[1]), 
					&(tc->response_size), tc->response_words);
			registerResponseToChannel(tc);
			CORTOS_DEBUG("sidekickServer: registered response %d.\n",
					tc->response_id);

			job_count++;
		}
		if((max_job_count > 0) && (job_count == max_job_count))
		{
			CORTOS_DEBUG("sidekickServer: job limit %d reached.\n", max_job_count);
			break;
		}
	}

}

void scoreboardServer(uint32_t max_job_count, uint32_t core_id, uint32_t thread_id, ThreadScoreboard* sb)
{
	uint32_t score, sthread;
	void (*__fn)(uint32_t, uint32_t*, uint32_t*, uint32_t*);
	uint32_t job_count = 0;
	while(1) 
	{
		ThreadChannel* tc;
		uint32_t not_found = selectScoreboardJob(sb, core_id, thread_id,  &tc);
		if(!not_found)
		{
			__fn = (void*) tc->request_words[0];
			(*__fn)(tc->request_size, tc->request_words, &(tc->response_size), tc->response_words);
			registerResponseToChannel(tc);
			job_count++;
		}
		if((max_job_count > 0) && (job_count == max_job_count))
		{
			CORTOS_DEBUG("sidekickScheduler: job limit %d reached.\n", max_job_count);
			break;
		}

	}
} 

// return 0 on success
uint32_t scheduleChannelJob (uint32_t job_type,
		uint32_t fn_or_ctxt, 
		uint32_t argc, 
		uint32_t* argv, 
		ThreadChannel* tc)
{
	uint32_t ret_val = 1;
	if(job_type == CALL_FUNCTION)
	{
		tc->request_type = job_type;
		tc->request_size = (argc + 1);
		tc->request_words[0] = fn_or_ctxt;
		int I;
		for(I = 0; I < argc; I++)
			tc->request_words[I+1] = argv[I];

		registerRequestToChannel(tc);
		ret_val = 0;
	}
	else
	{
		CORTOS_ERROR("scheduleChannelJob:  only CALL_FUNCTION (job_type = 1) jobs supported.\n");
	}
	return(ret_val);

}


// return 0 on success.
uint32_t scheduleScoreboardJob (uint32_t requester_core, uint32_t requester_thread,
		uint32_t job_type,
		uint32_t fn_or_ctxt, 
		uint32_t argc, 
		uint32_t* argv, 
		ThreadScoreboard* sb)
{
	uint32_t ret_val = 1;
	ThreadChannel* tc = NULL;
	if(!selectScoreboardWorker(sb, requester_core, requester_thread, 0, &tc))
	{
		if(job_type == CALL_FUNCTION)
		{
			tc->request_type = job_type;
			tc->request_size = (argc + 1);
			tc->request_words[0] = fn_or_ctxt;
			int I;
			for(I = 0; I < argc; I++)
				tc->request_words[I+1] = argv[I];

			registerRequestToChannel(tc);
			ret_val = 0;
		}
		else
		{
			CORTOS_ERROR("scheduleScoreboardJob:  only CALL_FUNCTION (job_type = 1) jobs supported.\n");
		}
	}
	return(ret_val);
}

