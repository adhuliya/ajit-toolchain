#ifndef ajit_mt_irc___
#define ajit_mt_irc___

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
//

uint32_t readInterruptControlRegister(int core_id, int thread_id);
void     writeInterruptControlRegister(int core_id, int thread_id, uint32_t value);


// set bit [0] = 1 in control register for core, thread
void enableInterruptController(int core_id, int thread_id);
// set bit [0] = 0 in control register for core, thread
void disableInterruptController(int core_id, int thread_id);

// set bit [interrupt_id] = 1 in control register for core, thread
void enableInterrupt(int core_id, int thread_id, int interrupt_id);
// set bit [interrupt_id] = 0 in control register for core, thread
void disableInterrupt(int core_id, int thread_id, int interrupt_id);



#endif
