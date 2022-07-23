#ifndef ajit_context_h__
#define ajit_context_h__
#define NWINDOWS 8
typedef struct ajit_mcontext_t__ {

	uint32_t psr;     
	uint32_t wim;    
	uint32_t tbr;    
	uint32_t y;      
	uint32_t fsr; 	  

	// reserved. 
	uint32_t reserved_0;
	uint32_t reserved_1;
	uint32_t reserved_2;

	// global registers.
	uint32_t g[8];

	// Window registers..  These include the stack and frame pointers.
	//
	// for window 0, r[0:7] are outs and r[8:15] are locals.
	// for window k, r[(16*k):(16*k)+7] are outs and r[((16*k)+ 8) : ((16*K)+15)]
	//                  are locals.
	//
	uint32_t r[16 * NWINDOWS]; 

	// FP registers
	uint32_t f[32]; 
	

} ajit_mcontext_t;

typedef struct ajit_context_t__ ajit_context_t;
struct ajit_context_t__ {

	uint32_t  func;
	uint32_t  func_arg;
	ajit_context_t*  uc_link;
	uint32_t  stack_base_addr;
	uint32_t  stack_size_in_bytes;
	uint32_t  reserved_0;
	uint32_t  reserved_1;
	uint32_t  reserved_2;

	ajit_mcontext_t mctxt;
};

// initialize to all zeros..
void __ajit_context_init__(ajit_context_t* ctxt);


void __ajit_context_set_stack__(ajit_context_t* ctxt, uint32_t stack_base_addr, uint32_t stack_size);
void __ajit_context_set_link__ (ajit_context_t* ctxt, ajit_context_t* link);



/* Get user context and store it in variable pointed to by UCP.  */
/*   ie., save all registers into __ucp 			 */
/*   Note: register i7 (r31) will contain return address in caller of getcontext */
int __ajit_getcontext__ (ajit_context_t *__ucp);

/* Set user context from information of variable pointed to by UCP.  */
/*  ie., set registers from information stored in __ucp  	     */
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

#endif /* ajit_context.h */
