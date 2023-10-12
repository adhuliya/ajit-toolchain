//Ajit_irq.h
#ifndef __AJIT_IRQ_H___
#define


#include <linux/slab.h>

#include <asm/timer.h>
#include <asm/irq.h>

#define  AJIT_IRQ_TICKER      10
#define  AJIT_IRQ_IPI_DEFAULT 13
#define  AJIT_IRQ_CROSS_CALL  15 // TODO: !!

// BEGIN : ajit_mt_irc
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
// END : ajit_mt_irc

unsigned int Ajit_build_device_irq(struct platform_device *op,
					   unsigned int real_irq);

void Ajit_clear_clock_irq(void);

void  Ajit_init_timers(void);

void  Ajit_init_IRQ(void);

void Ajit_write_IRC_control_word(int value);

#endif
