#ifndef ajit_context_h__
#define ajit_context_h__
#define NWINDOWS 8

// optimized context data structure.
// Keeps track of 
//           status registers (excluding ASR's)
//           global registers
//           stack-pointer
//           fp registers.
// 
typedef struct ajit_mcontext_t__ {

	uint32_t y;
	uint32_t fsr;

	uint32_t scratch[6];

	// global registers.
	uint32_t g[8];

	// locals and ins
	uint32_t locals[8]; 
	uint32_t ins[8]; 

	// FP registers
	uint32_t f[32]; 

	

} ajit_mcontext_t;

typedef struct ajit_context_t__ ajit_context_t;
struct ajit_context_t__ {

	uint32_t  func;
	uint32_t  func_arg;
	ajit_context_t*  uc_link;

	uint32_t  stack_pointer;
	uint32_t  stack_size_in_bytes;

	// 3 scratch values.
	uint32_t scratch[3];

	// base mcontext.
	ajit_mcontext_t mctxt;
};

// initialize to all zeros..
void __ajit_context_init__(ajit_context_t* ctxt);


void __ajit_context_set_stack__(ajit_context_t* ctxt, uint32_t stack_base_addr, uint32_t stack_size);
void __ajit_context_set_link__ (ajit_context_t* ctxt, ajit_context_t* link);



/* Get user context and keep it in UCP.                  			 */
/*   ie., 									 */
/*    save status registers, globals and stack-pointer  into __ucp->mctxt 	 */
/*    save all active user window registers onto stack                           */
int __ajit_getcontext__ (ajit_context_t *__ucp);

/* Set user context from information of variable pointed to by UCP.  */
/*  recover active user window registers from stack		     */
/*  recover globals from __ucp->mctxt                                */
/*  setcontext will execute a ret after registers are restored.      */
/*  and continue from where __ucp had its return pointer             */
int __ajit_setcontext__ (const ajit_context_t *__ucp);

/* 
   Save current context in context variable pointed to by OUCP and set
   context from variable pointed to by UCP.  
*/
int __ajit_swapcontext__ (ajit_context_t *__oucp, const ajit_context_t *__ucp);

/* make a context, and set func etc.. */
void __ajit_makecontext__ (ajit_context_t *__ucp, void (*__func) (void*), void* arg);

void __ajit_print_mcontext__ (ajit_context_t* t);
void __ajit_print_context__ (ajit_context_t* t);

#endif /* ajit_context.h */
