#ifndef ajit_context_h__
#define ajit_context_h__
#define NWINDOWS 8

//
// optimized context data structure.
//
typedef struct ajit_context_t__ {

	uint32_t pc;
	uint32_t stack_pointer;

	uint32_t y;
	uint32_t fsr;
	
	uint32_t  func;
	uint32_t  func_arg;

	uint32_t scratch[3];

	// global registers.
	uint32_t g[8];
	
	// FP registers
	uint32_t f[32]; 
} ajit_context_t;


// initialize to all zeros..
void __ajit_context_init__(ajit_context_t* ctxt);



//
// set the function and argument.
//
void __ajit_context_set_func_and_arg__ (ajit_context_t* ctxt, uint32_t fn_pointer, uint32_t arg_pointer);


/* Get user context and keep it in UCP.                  			 */
/*   ie., 									 */
/*    save status registers, globals and stack-pointer  into __ucp->mctxt 	 */
/*    save all active user window registers onto stack                           */
int __ajit_getcontext__ (ajit_context_t *__ucp, uint32_t stack_pointer);

/* Set user context from information of variable pointed to by UCP.  */
/*  recover active user window registers from stack		     */
/*  recover globals from __ucp->mctxt                                */
/*  setcontext will execute a ret after registers are restored.      */
/*  and continue from where __ucp had its return pointer             */
int __ajit_setcontext__ (ajit_context_t *__ucp);

/* 
   Save current context in context variable pointed to by OUCP and set
   context from variable pointed to by UCP.  
*/
int __ajit_swapcontext__ (ajit_context_t *__oucp, uint32_t stack_pointer, const ajit_context_t *__ucp);
void __ajit_print_context__  (ajit_context_t* t);
void __ajit_context_save_all_windows__ ();

#endif /* ajit_context.h */
