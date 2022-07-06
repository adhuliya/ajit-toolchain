#ifndef VTHREAD_H___
#define VTHREAD_H___

#define NWINDOWS 8
#define MAX_VTHREAD_COUNT      	    256

//
//   Enough information to resume a thread..  The thread is resumed
//   using a JMPL/RETT pair
// 
typedef struct __VthreadState 
{
	// Global registers
	uint32_t g[8];

	// Window registers..  These include the stack and frame pointers.
	//
	// for window 0, r[0:7] are outs and r[7:15] are locals.
	// for window k, r[(16*k):(16*k)+7] are outs and r[((16*k)+ 8) : ((16*K)+15)]
	//                  are locals.
	//
	uint32_t r[16 * NWINDOWS]; 

	// FP registers
	uint32_t f[32]; 

	// status registers
	uint32_t psr;     
	uint32_t wim;    
	uint32_t tbr;    
	uint32_t y;      

	// fsrm at point of suspension.
	uint32_t fsr; 	  //floating point status register


	// bget is used to allocate a stack to the 
	// thread at creation time.  The scheduler
	// sets up the stack pointer just before
	// jmpl/rett combo is called to resume the thread.
	uint8_t* stack;

	uint32_t thread_id;

} VthreadState __attribute__ ((aligned 8));

#define VTHREAD_SET_REGISTER(rf, cwp, r_index, rval) {\
	r_index = r_index & 0x1f;\
	if(r_index < 8)\
	rf->g[r_index] = rval;\
	else\
	{\
		cwp = cwp & 0x7;\
		uint32_t index = ((cwp * 16) + (r_index-8));\
		rf->r[index] = rval;\
	}} 

#define VTHREAD_GET_REGISTER(rf, cwp, r_index, rval) {\
	r_index = r_index & 0x1f;\
	if(r_index < 8)\
	rval = rf->g[r_index];\
	else\
	{\
		cwp = cwp & 0x7;\
		uint32_t index = ((cwp * 16) + (r_index-8));\
		rval = rf->r[index];\
	}} 




//
// The running thread is saved into running_thread, and we switch to new_thread 
//
int  __ajit_vt_switch_threads__ (VthreadState* running_thread, VthreadState* new_thread);



#endif
