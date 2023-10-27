#ifndef __ajit_ctask_h____
#define __ajit_ctask_h____

#include <ajit_coroutine.h>

#define MAX_NUMBER_OF_CTASKS 64

typedef struct __ajit_ctask_pool_t  ajit_ctask_pool_t;
typedef struct __ajit_ctask_t       ajit_ctask_t;

typedef struct __ajit_ctask_args_t {

	uint32_t args[8];
	ajit_ctask_t* ct;

} ajit_ctask_args_t;




struct __ajit_ctask_t {
	ajit_coroutine_t coroutine; 
	int index_in_pool;

	uint32_t sequence_id;

	// Pool in which this ctask is present.
	ajit_ctask_pool_t* pool;

	ajit_ctask_t* next;
	ajit_ctask_t* prev;

}  __attribute__((aligned(8)));

void ajit_init_ctask (ajit_ctask_t* ctask);

typedef struct __ajit_ctask_list_t {
	ajit_ctask_t* head;
	ajit_ctask_t* tail;
} ajit_ctask_list_t;

void ajit_init_ctask_list (ajit_ctask_list_t* tl);

void   ajit_push_back_ctask (ajit_ctask_t* t, ajit_ctask_list_t* tl);
ajit_ctask_t* ajit_pop_back_ctask (ajit_ctask_list_t* tl);

void   ajit_push_front_ctask (ajit_ctask_t* t, ajit_ctask_list_t* tl);
ajit_ctask_t* ajit_pop_front_ctask (ajit_ctask_list_t* tl);




typedef struct __ajit_ctask_pool_t {
	ajit_ctask_t tasks[MAX_NUMBER_OF_CTASKS];
	uint8_t valid[MAX_NUMBER_OF_CTASKS];
} ajit_ctask_pool_t;

// init..
void ajit_init_ctask_pool (ajit_ctask_pool_t* cpool);

// return NULL if there is no room.
ajit_ctask_t*  ajit_reserve_ctask_from_pool (ajit_ctask_pool_t* cpool);

// return to pool
void ajit_release_ctask_to_pool (ajit_ctask_t* t,  ajit_ctask_pool_t* cpool);



typedef struct __ajit_ctask_scheduler_t {
	uint8_t* lock;
	ajit_ctask_pool_t pool;
	ajit_ctask_list_t active_list;
} ajit_ctask_scheduler_t;

int ajit_init_ctask_scheduler(ajit_ctask_scheduler_t* sched);
int ajit_run_ctask_scheduler (ajit_ctask_scheduler_t* sched);

// ct : the ajit_ctask_t* which is being scheduled.
// fn : pointer to void fn (ajit_ctask_t* ct, void* arg);
// arg: pointer to ctask args (the ct pointer and in addtion,
//         up to 32 bytes of arg can be passed) for use by fn.
// stack_size_in_bytes:  size of stack allocated for ct.
// cts: scheduler assigned to manage ct.
//
// return 1 on success.
//     
int  ajit_schedule_ctask (ajit_ctask_t* ct,
					void *fn, 
					ajit_ctask_args_t* arg, 
					uint32_t stack_size_in_bytes,
					ajit_ctask_scheduler_t* cts);

// resume..
int ajit_resume_ctask (ajit_ctask_t* ct, ajit_ctask_scheduler_t* cts);

// wait on ctask.
int ajit_join_ctask (ajit_ctask_t* ct,  ajit_ctask_scheduler_t* cts);

//
// ajit_ctask_yield (ct)..   ct is the ajit_ctask_t* which will yield.
#define ajit_ctask_yield(ct)  ajit_coroutine_yield((&(ct->coroutine)))

// ajit_ctask_resume (ct)..   ct is the ajit_ctask_t* which will be resumed.
#define ajit_ctask_resume(ct) ajit_coroutine_resume((&(ct->coroutine)))

// ajit_ctask_return (ct)..   ct is the ajit_ctask_t* which will return.
#define ajit_ctask_return(ct) ajit_coroutine_return((&(ct->coroutine)))


#endif
