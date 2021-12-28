#ifndef ajit_mt_irc___
#define ajit_mt_irc___

////////////////////////////////////////////////////////////////////////////////////////////////////////
// The interrupt handler structure for bare-metal is set up as follows.
// 
// First, it is assumed that all invalid stack pointers are initialized to
// to 0 (clear_stack_pointers must be called in the init.s script).
//
// On an interrupt, the function ajit_generic_interrupt_handler is
// called with a tbr value.  Base on the tbr value, the  generic
// interrupt handler calls an interrupt level specific handler.
// 
// There are 15 interrupt specific handlers which populate
// a function pointer array.  Each function pointer in the array points
// to a function with form:  void foo ();
////////////////////////////////////////////////////////////////////////////////////////////////////////

// sets all interrupt specific handlers to null.
void ajit_initialize_interrupt_handlers_to_null();
// set function pointer of specific handler for interrupt_level.
void ajit_set_interrupt_handler (uint32_t interrupt_level, void (* foo) ());
// From the TBR, figure out the interrupt level and
// call the interrupt handler in the array (if it is not null).
// If it is null, halt the machine!
void ajit_generic_interrupt_handler(uint32_t tbr_value);

////////////////////////////////////////////////////////////////////////////////////////////////////////
// The AJIT multi-thread interrupt controller is a powerful mechanism
// for mapping interrupts to hardware threads.
//
// Interrupt scheme for AJIT multi-core.
//   1. There is one interrupt control register for every
//      thread.  The addresses for these registers are as
//      follows
//		(core,thread)	  address offset from base
//               (0,0)			0
//               (0,1)			4
//               (1,0)			8
//               (1,1)			12
//               (2,0)			16
//               (2,1)			20
//               (3,0)			24
//               (3,1)			28
//
//   2.  The control register for each thread has the following
//	 format
//        [31:17]    active interrupts.
//        [16]	     unused
//        [15:1]     interrupt mask (if 0, interrupt disabled).
//        [0]	     irc enable (for that thread).
//  
//   3.  For each thread specific interrupt controller:
//          a. the controller starts in an idle state
//          b. moves to an enabled state if a '1' is
//             written to bit [0] of the control register.
//          c. moves to an interrupting state if an interrupt
//             (after masking) is observed in the enabled state.
//          d. stays in the interrupting state until the irc
//              is disabled.
////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t readInterruptControlRegister(int core_id, int thread_id);
void     writeInterruptControlRegister(int core_id, int thread_id, uint32_t value);


// set bit [0] = 1 in control register for core, thread
void enableInterruptController(int core_id, int thread_id);
// set bit [0] = 0 in control register for core, thread
void disableInterruptController(int core_id, int thread_id);

// set bit [interrupt_id] = 1 in control register for core, thread
void enableInterrupt(int core_id, int thread_id, int interrupt_id);

// enable all 15 interrupts on core/thread.
//    Note: interrupt controller enable bit is not modified.
void enableAllInterrupts(int core_id, int thread_id);

// set bits [15:0] in control register core (core_id,thread_id) to 1.
// Note: interrupt controller is also enabled!
void enableInterruptControllerAndAllInterrupts(int core_id, int thread_id);


// Note: mask[15:1] is written into control register[15:1]
// for (core_id, thread_id).  Other bits of the control register
// are not modified.  Use with care.   This should be called
// only when the IRC is disabled.
void setInterruptMask(int core_id, int thread_id, uint32_t mask);


// set bit [interrupt_id] = 0 in control register for core, thread
void disableInterrupt(int core_id, int thread_id, int interrupt_id);



#endif
