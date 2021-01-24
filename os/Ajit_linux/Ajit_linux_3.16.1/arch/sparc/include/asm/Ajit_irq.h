//Ajit_irq.h


#include <linux/slab.h>

#include <asm/timer.h>
#include <asm/irq.h>




unsigned int Ajit_build_device_irq(struct platform_device *op,
					   unsigned int real_irq);

void Ajit_clear_clock_irq(void);

void  Ajit_init_timers(void);

void  Ajit_init_IRQ(void);

void Ajit_write_IRC_control_word(int value);

