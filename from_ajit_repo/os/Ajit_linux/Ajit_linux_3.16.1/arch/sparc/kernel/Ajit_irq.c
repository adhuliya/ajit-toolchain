//Ajit_irq.c
//
//Board-specific routines for handling timer and serial 
//interrupts and linking them with the kernel.
//The routines here are derived from leon_kernel.c
//
//Authors:
//Neha Karanjkar
//Aniket Deshmukh


#include <linux/slab.h>

#include <asm/timer.h>
#include <asm/traps.h>
#include <asm/pgalloc.h>
#include <asm/pgtable.h>
#include <asm/irq.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <asm/cacheflush.h>
#include <linux/jiffies.h>
#include <asm/asi.h>
#include "irq.h"
#include "kernel.h"
#include <asm/prom.h> //to access the device tree



static int Ajit_read_timer_register(int* paddr);
static void Ajit_write_timer_control_word(int value);
void Ajit_write_IRC_control_word(int value);



//Read timer register.
//Reading clears the timer interrupt
static inline int Ajit_read_timer_register(int* paddr)
{
        int retval;
        __asm__ __volatile__("lda [%1] %2, %0\n\t" :
                             "=r"(retval) : "r"(paddr), "i"(ASI_M_BYPASS));
        return retval;
}
static unsigned int Ajit_startup_irq(struct irq_data *data)
{
	irq_link(data->irq);
	return 0;
}
static void Ajit_shutdown_irq(struct irq_data *data)
{
	irq_unlink(data->irq);
}
static void Ajit_mask_irq(struct irq_data *data)
{	
}
static void Ajit_eoi_irq(struct irq_data *data)
{
}
static void Ajit_unmask_irq(struct irq_data *data)
{
}
static int Ajit_set_affinity(struct irq_data *data, const struct cpumask *dest,
			     bool force)
{
 return 0;
}
	
static struct irq_chip Ajit_irq = {
	.name			= "Ajit",
	.irq_startup		= Ajit_startup_irq,
	.irq_shutdown		= Ajit_shutdown_irq,
	.irq_mask		= Ajit_mask_irq,
	.irq_unmask		= Ajit_unmask_irq,
	.irq_eoi		= Ajit_eoi_irq,
	.irq_set_affinity	= Ajit_set_affinity,
};


//Device information to be populated
//by reading the device-tree
static unsigned int ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER=0;
static unsigned int ADDR_TIMER_CONTROL_REGISTER=0;
static unsigned int TIMER_IRQ_LEVEL=0;
static unsigned int TIMER_TICK_REAL_FREQUENCY=0;
static unsigned int TIMER_TICK_VIRTUAL_FREQUENCY=0;


//read the device tree to obtain
//hardware information.
static void read_dev_tree(void)
{
	struct device_node *node;
	struct device_node *rootnode;
	struct property* prop;
	int len=0;

	prom_printf("\nReading device tree...");
	//find the root node in device tree
	rootnode = of_find_node_by_path("/");
	if(!rootnode)  
	{
		prom_printf("\nERROR: While reading device tree, could not find node /.\n");
		return;
	}
	
	//get information about the interrupt controller device
	node = of_find_node_by_name(rootnode, "ajit_interrupt_controller");
	if (!node) { prom_printf("\nERROR: While reading device tree, could not find node ajit_interrupt_controller.\n"); return; }
	prop = of_find_property(node, "reg", &len);
	if (!prop) { prom_printf("\nERROR: While reading device tree, could not find property reg in node ajit_interrupt_controller.\n"); return; }
	ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER = *(unsigned int *)prop->value;
	prom_printf("\nRead information from device tree: ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER=0x%x",ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER);
	
	//get information about the timer device
	node = of_find_node_by_name(rootnode, "ajit_timer");
	if (!node) { prom_printf("\nERROR: While reading device tree, could not find node ajit_timer.\n"); return; }
	
	prop = of_find_property(node, "reg", &len);
	if (!prop) { prom_printf("\nERROR: While reading device tree, could not find property reg in node ajit_timer.\n"); return; }
	ADDR_TIMER_CONTROL_REGISTER = *(unsigned int *)prop->value;
	prom_printf("\nRead information from device tree: ADDR_TIMER_CONTROL_REGISTER=0x%x",ADDR_TIMER_CONTROL_REGISTER);
	
	prop = of_find_property(node, "interrupts", &len);
	if (!prop) { prom_printf("\nERROR: While reading device tree, could not find property interrupts in node ajit_timer.\n"); return; }
	TIMER_IRQ_LEVEL = *(unsigned int *)prop->value;
	prom_printf("\nRead information from device tree: TIMER_IRQ_LEVEL=%d",TIMER_IRQ_LEVEL);
	
	prop = of_find_property(node, "tick-real-freq", &len);
	if (!prop) { prom_printf("\nERROR: While reading device tree, could not find property tick-real-freq in node ajit_timer.\n"); TIMER_TICK_REAL_FREQUENCY=100;}
	else 
	{
		TIMER_TICK_REAL_FREQUENCY = *(unsigned int *)prop->value;
		prom_printf("\nRead information from device tree: TIMER_TICK_REAL_FREQUENCY=%d",TIMER_TICK_REAL_FREQUENCY);
	}

	prop = of_find_property(node, "tick-virtual-freq", &len);
	if (!prop) { prom_printf("\nERROR: While reading device tree, could not find property tick-virtual-freq in node ajit_timer.\n"); TIMER_TICK_VIRTUAL_FREQUENCY=100000;}
	else
	{
		TIMER_TICK_VIRTUAL_FREQUENCY = *(unsigned int *)prop->value;
		prom_printf("\nRead information from device tree: TIMER_TICK_VIRTUAL_FREQUENCY=%d",TIMER_TICK_VIRTUAL_FREQUENCY);
	}
}





//Write control word to timer register
//using MMU-bypass ASI
static inline void Ajit_write_timer_control_word(int value)
{
	int* paddr=(int*) ADDR_TIMER_CONTROL_REGISTER;
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(value), "r"(paddr),  "i"(ASI_M_BYPASS) : "memory");
}

//Write control word to Interrupt control register
//using MMU-bypass ASI
void Ajit_write_IRC_control_word(int value)
{
	int* paddr = (int*)ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER;
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(value), "r"(paddr),  "i"(ASI_M_BYPASS) : "memory");
}



static void Ajit_load_profile_irq(int cpu, unsigned int limit)
{
	//prom_printf("\n------Ajit_load_profile_irq()");
}



unsigned int Ajit_build_device_irq_inner(unsigned int real_irq,
				    	irq_flow_handler_t flow_handler,
				    	const char *name, int do_ack)
{
	unsigned int irq;
	unsigned long mask;
	struct irq_desc *desc;
	
	//Processor interrupt level
        //int timer_irq_level = 10;

	irq = 0;
	//Set mask manually to 1 for now. 
	//It affects the irq_set_chip_data function.
	mask = 1;

	// Allocates entries in the irq_table
	irq = irq_alloc(real_irq, real_irq);
	if (irq == 0)
		goto out;
	desc = irq_to_desc(irq);

	//The two functions below are kernal related. They essentially set
	//some of the remaining parameters in the irq_desc struct
	
	//irq_set_chip_and_handler_name is probably an important 
	//function as it sets the handler. 
	//However, it also requires an irq_chip variable to be initalized 	

	if (!desc || !desc->handle_irq || desc->handle_irq == handle_bad_irq) 
	{
		irq_set_chip_and_handler_name(irq, &Ajit_irq,
					      flow_handler, name);
		irq_set_chip_data(irq, (void *)mask);
	}

out:
	return irq;
}



unsigned int Ajit_build_device_irq(struct platform_device *op, unsigned int real_irq)
{
	// Need to complete this function to intialize the irq_desc struct
	//real_irq is the acutal irq number on the processor interrupt pins
        // unsigned int irq=0;
	prom_printf("\n------Ajit_build_device_irq()");
	
	//The interrupt handler is a simple (preconfigured) 
	//handler provided by the kernel.
	return Ajit_build_device_irq_inner(real_irq, handle_simple_irq, "level", 0); 	

}



//This function is called by timer_interrupt() routine
//We clear the current interrupt and re-set the one-shot timer
static void Ajit_clear_clock_irq(void)
{
	//Steps:
	//1. Disable IRC
	//2. Disable Timer
	//3. Enable Timer
	//4. Enable IRC
	
	uint32_t timer_control_word;
	//Timer control word :
	//bit 0     : timer_enable
	//bits 31:1 : timer_count to generate interrupts with 
	//a frequency = HZ
	timer_control_word=sparc_config.cs_period;
	timer_control_word=(timer_control_word<<1)|1;

	//Disable IRC
	Ajit_write_IRC_control_word(0x00);
	//Disable timer
	Ajit_write_timer_control_word(0x00);
	//Enable the IRC
	Ajit_write_IRC_control_word(0x01);
	//Enable timer
	Ajit_write_timer_control_word(timer_control_word);
}


//Enable the interrupt controller
//and 
//Start off the timer
//The timer is one-shot
//It generates an interrupt (level =10) 
//after a delay T. 
//The interrupt level remains high
//until explicitly lowered by the timer_interrupt handler.
//
//	T = timer_max_count X TIMER_INTERNAL_TICK
//	timer_max_count is configured in this function.
//	TIMER_INTERNAL_TICK is defined in Ajit_Hardware_Configuration.h,
//	and typically set to 1 milli seconds.
static void  Ajit_start_timer(void)
{
	uint32_t timer_control_word;
	uint32_t IRC_control_word;
	
	//Initialize timer connected to 
	//hardware interrupt level10
	//to generate periodic interrupts
		
	//Timer control word :
	//bit 0     : timer_enable
	//bits 31:1 : timer_count to generate interrupts with 
	//a frequency = HZ
	timer_control_word=sparc_config.cs_period;
	timer_control_word=(timer_control_word<<1)|1;

	//write timer control word
	Ajit_write_timer_control_word(timer_control_word);
	
	//Enable the IRC
	IRC_control_word =1; //bit[0] is enable bit
	//write control word in IRC
	Ajit_write_IRC_control_word(IRC_control_word);

}

void  Ajit_disable_timer(void)
{
	uint32_t timer_control_word;
	
	//Disable timer interrupts
		
	//Timer control word :
	//bit 0     : timer_enable
	//bits 31:1 : timer_count to generate interrupts with 
	//a frequency = HZ
	timer_control_word=0x00;

	//write timer control word
	Ajit_write_timer_control_word(timer_control_word);
}


//This dummy master_l10_counter is needed
//because a device register named master_l10_counter
//is read by timer_init routine in sbus_cycles_offset()
//in time_32.c
static volatile u32 dummy_master_l10_counter;



//Associate the timer interrupt (hardware int level=10)
//with the timer interrupt handler
static void  Ajit_associate_timer_interrupt_with_handler(void)	
{
	unsigned int irq;
	int err;
	int timer_irq_level = TIMER_IRQ_LEVEL;
	
	//the master_l10_counter is a pointer which points to a
	//timer register in sun4m machines and is read inside one of
	//the routines in time_32.c. We just use a dummy location
	//and set it to 0
	master_l10_counter = (u32 __iomem *)&dummy_master_l10_counter;
	dummy_master_l10_counter = 0;

	
	irq = Ajit_build_device_irq(NULL, timer_irq_level);
	err = request_irq(irq, timer_interrupt, IRQF_TIMER, "timer", NULL); 
	if (err) {
		pr_err("Unable to attach timer IRQ%d\n", irq);
		prom_halt();
	}
	else
	{
		pr_info("\n Timer request_irq() succeeded with irq=%d",irq);
	}
}


static u32 Ajit_get_cycles_offset(void)
{
	//return a dummy value for now	
	return 100;
}

//Associate timer interrupt (Interrupt level 10)
//with the timer interrupt handler.
//And start off the timer
static void  Ajit_init_timers(void)
{
	
	sparc_config.get_cycles_offset = Ajit_get_cycles_offset;
	sparc_config.cs_period = TIMER_TICK_VIRTUAL_FREQUENCY / HZ;
	sparc_config.clock_rate= TIMER_TICK_VIRTUAL_FREQUENCY;
	sparc_config.features |= FEAT_L10_CLOCKSOURCE;
	sparc_config.features |= FEAT_L10_CLOCKEVENT;
	
	Ajit_associate_timer_interrupt_with_handler();	
	Ajit_start_timer();

	//preset loops_per_jiffies kernel variable
	//to avoid running calibrate_delay() later
	//It is said to be roughly bogomips*5000
	//preset_lpj=20*5000;
}


void  Ajit_init_IRQ(void)
{
	//obtain device-related information from 
	//the device tree.
	read_dev_tree();

	sparc_config.init_timers      = Ajit_init_timers;
	
	//cs_period is the timer period of the timer device.
	//cs_period = freq of input clock to the timer divided
	//by the freq of interrupts generated by the timer to the kernel.
	
	//The clock input to the timer is 1MHz
	sparc_config.build_device_irq = Ajit_build_device_irq;
	sparc_config.clear_clock_irq  = Ajit_clear_clock_irq;
	sparc_config.load_profile_irq = Ajit_load_profile_irq;
	sparc_config.cs_period = TIMER_TICK_VIRTUAL_FREQUENCY / HZ;
	sparc_config.clock_rate= TIMER_TICK_VIRTUAL_FREQUENCY;

}
