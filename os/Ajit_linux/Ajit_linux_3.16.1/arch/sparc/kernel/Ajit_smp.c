/* leon_smp.c: Sparc-Leon SMP support.
 *
 * based on sun4m_smp.c
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 2009 Daniel Hellstrom (daniel@gaisler.com) Aeroflex Gaisler AB
 * Copyright (C) 2009 Konrad Eisele (konrad@gaisler.com) Aeroflex Gaisler AB
 *
 * For AJIT
 * Copyright (C) 2023 Madhav Desai (madhav@ee.iitb.ac.in) IIT Bombay
 *
 */

#include <asm/head.h>

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/threads.h>
#include <linux/smp.h>
#include <linux/interrupt.h>
#include <linux/kernel_stat.h>
#include <linux/of.h>
#include <linux/init.h>
#include <linux/spinlock.h>
#include <linux/mm.h>
#include <linux/swap.h>
#include <linux/profile.h>
#include <linux/pm.h>
#include <linux/delay.h>
#include <linux/gfp.h>
#include <linux/cpu.h>
#include <linux/clockchips.h>

#include <asm/cacheflush.h>
#include <asm/tlbflush.h>

#include <asm/ptrace.h>
#include <linux/atomic.h>
#include <asm/irq_regs.h>
#include <asm/traps.h>

#include <asm/delay.h>
#include <asm/irq.h>
#include <asm/page.h>
#include <asm/pgalloc.h>
#include <asm/pgtable.h>
#include <asm/oplib.h>
#include <asm/cpudata.h>
#include <asm/asi.h>
#include <asm/Ajit_smp.h>
#include <asm/timer.h>

#include "kernel.h"

#include "irq.h"

extern ctxd_t *srmmu_ctx_table_phys;
static int smp_processors_ready;
extern volatile unsigned long cpu_callin_map[NR_CPUS];
extern cpumask_t smp_commenced_mask;
void ajit_configure_cache_smp(void);
static void ajit_ipi_init(void);

/* IRQ number of LEON IPIs */
int ajit_ipi_irq = AJIT_IRQ_IPI_DEFAULT;

static inline unsigned long do_swap(volatile unsigned long *ptr,
				    unsigned long val)
{
	__asm__ __volatile__("swapa [%2] %3, %0\n\t" : "=&r"(val)
			     : "0"(val), "r"(ptr), "i"(ASI_M_BYPASS)
			     : "memory");
	return val;
}

void ajit_cpu_pre_starting(void *arg)
{
}

void ajit_pre_online(void *arg)
{
	int cpuid = hard_smp_processor_id();

	/* Allow master to continue. The master will then give us the
	 * go-ahead by setting the smp_commenced_mask and will wait without
	 * timeouts until our setup is completed fully (signified by
	 * our bit being set in the cpu_online_mask).
	 */
	do_swap(&cpu_callin_map[cpuid], 1);

	local_ops->cache_all();
	local_ops->tlb_all();

	/* Fix idle thread fields. */
	__asm__ __volatile__("ld [%0], %%g6\n\t" : : "r"(&current_set[cpuid])
			     : "memory" /* paranoid */);

	/* Attach to the address space of init_task. */
	atomic_inc(&init_mm.mm_count);
	current->active_mm = &init_mm;

	while (!cpumask_test_cpu(cpuid, &smp_commenced_mask))
		mb();
}

/*
 *	Cycle through the processors asking the PROM to start each one.
 */

extern struct linux_prom_registers smp_penguin_ctable;

void ajit_configure_cache_smp(void)
{
	local_ops->cache_all();
	local_ops->tlb_all();
}

static void ajit_smp_setbroadcast(unsigned int mask)
{
	prom_printf("ajit_smp_setbroadcast not implemented. continue anyway\n");
}

int ajit_smp_nrcpus(void)
{
	int nrcpu = 1;

	prom_printf("ajit_smp_nrcpus not implemented. continue anyway\n");
	return nrcpu;
}

void __init ajit_boot_cpus(void)
{
	int nrcpu = ajit_smp_nrcpus();
	int me = smp_processor_id();

	/* Setup IPI */
	ajit_ipi_init();

	printk(KERN_INFO "%d:(%d:%d) cpus mpirq at 0x%x\n", (unsigned int)me,
	       (unsigned int)nrcpu, (unsigned int)NR_CPUS,
	       (unsigned int)&(ajit_irqctrl_regs->mpstatus));

	ajit_enable_irq_cpu(AJIT_IRQ_CROSS_CALL, me);
	ajit_enable_irq_cpu(AJIT_IRQ_TICKER, me);
	ajit_enable_irq_cpu(ajit_ipi_irq, me);

	ajit_smp_setbroadcast(1 << LEON3_IRQ_TICKER);

	ajit_configure_cache_smp();
	local_ops->cache_all();

}

int ajit_boot_one_cpu(int i, struct task_struct *idle)
{
	int timeout;

	current_set[i] = task_thread_info(idle);

	/* See trampoline.S:leon_smp_cpu_startup for details...
	 * Initialize the contexts table
	 * Since the call to prom_startcpu() trashes the structure,
	 * we need to re-initialize it for each cpu
	 */
	smp_penguin_ctable.which_io = 0;
	smp_penguin_ctable.phys_addr = (unsigned int)srmmu_ctx_table_phys;
	smp_penguin_ctable.reg_size = 0;

	/* whirrr, whirrr, whirrrrrrrrr... */
	printk(KERN_INFO "Starting CPU %d : (irqmp: 0x%x)\n", (unsigned int)i,
	       (unsigned int)&ajit_irqctrl_regs->mpstatus);
	local_ops->cache_all();

	/* Make sure all IRQs are of from the start for this new CPU */
	// LEON_BYPASS_STORE_PA(&leon3_irqctrl_regs->mask[i], 0);
	// TODO: clear all interrupts for this new CPU.

	/* Wake one CPU */
	// LEON_BYPASS_STORE_PA(&(leon3_irqctrl_regs->mpstatus), 1 << i);
	// TODO: wake one CPU.

	/* wheee... it's going... */
	for (timeout = 0; timeout < 10000; timeout++) {
		if (cpu_callin_map[i])
			break;
		udelay(200);
	}
	printk(KERN_INFO "Started CPU %d\n", (unsigned int)i);

	if (!(cpu_callin_map[i])) {
		printk(KERN_ERR "Processor %d is stuck.\n", i);
		return -ENODEV;
	} else {
		ajit_enable_irq_cpu(LEON3_IRQ_CROSS_CALL, i);
		ajit_enable_irq_cpu(LEON3_IRQ_TICKER, i);
		ajit_enable_irq_cpu(ajit_ipi_irq, i);
	}

	local_ops->cache_all();
	return 0;
}

void __init ajit_smp_done(void)
{

	int i, first;
	int *prev;

	/* setup cpu list for irq rotation */
	first = 0;
	prev = &first;
	for (i = 0; i < NR_CPUS; i++) {
		if (cpu_online(i)) {
			*prev = i;
			prev = &cpu_data(i).next;
		}
	}
	*prev = first;
	local_ops->cache_all();

	/* Free unneeded trap tables */
	if (!cpu_present(1)) {
		free_reserved_page(virt_to_page(&trapbase_cpu1));
	}
	if (!cpu_present(2)) {
		free_reserved_page(virt_to_page(&trapbase_cpu2));
	}
	if (!cpu_present(3)) {
		free_reserved_page(virt_to_page(&trapbase_cpu3));
	}
	/* Ok, they are spinning and ready to go. */
	smp_processors_ready = 1;

}

struct ajit_ipi_work {
	int single;
	int msk;
	int resched;
};

static DEFINE_PER_CPU_SHARED_ALIGNED(struct leon_ipi_work, leon_ipi_work);

/* Initialize IPIs on the LEON, in order to save IRQ resources only one IRQ
 * is used for all three types of IPIs.
 */
static void __init ajit_ipi_init(void)
{
	int cpu, len;
	struct ajit_ipi_work *work;
	struct property *pp;
	struct device_node *rootnp;
	struct tt_entry *trap_table;
	unsigned long flags;

	printk(KERN_INFO "leon: SMP IPIs at IRQ %d\n", leon_ipi_irq);

	/* Adjust so that we jump directly to smpajit_ipi */
	local_irq_save(flags);
	trap_table = &sparc_ttable[SP_TRAP_IRQ1 + (ajit_ipi_irq - 1)];
	trap_table->inst_three += smpajit_ipi - real_irq_entry;
	local_ops->cache_all();
	local_irq_restore(flags);

	for_each_possible_cpu(cpu) {
		work = &per_cpu(ajit_ipi_work, cpu);
		work->single = work->msk = work->resched = 0;
	}
}

static void ajit_send_ipi(int cpu, int level)
{
	unsigned long mask;
	mask = ajit_get_irqmask(level);

	// LEON3_BYPASS_STORE_PA(&leon3_irqctrl_regs->force[cpu], mask);
	// TODO: force cpu using mask.
}

static void ajit_ipi_single(int cpu)
{
	struct ajit_ipi_work *work = &per_cpu(ajit_ipi_work, cpu);

	/* Mark work */
	work->single = 1;

	/* Generate IRQ on the CPU */
	ajit_send_ipi(cpu, leon_ipi_irq);
}

static void ajit_ipi_mask_one(int cpu)
{
	struct ajit_ipi_work *work = &per_cpu(ajit_ipi_work, cpu);

	/* Mark work */
	work->msk = 1;

	/* Generate IRQ on the CPU */
	ajit_send_ipi(cpu, ajit_ipi_irq);
}

static void ajit_ipi_resched(int cpu)
{
	struct leon_ipi_work *work = &per_cpu(ajit_ipi_work, cpu);

	/* Mark work */
	work->resched = 1;

	/* Generate IRQ on the CPU (any IRQ will cause resched) */
	ajit_send_ipi(cpu, ajit_ipi_irq);
}

void ajitsmp_ipi_interrupt(void)
{
	struct ajit_ipi_work *work = &__get_cpu_var(ajit_ipi_work);

	if (work->single) {
		work->single = 0;
		smp_call_function_single_interrupt();
	}
	if (work->msk) {
		work->msk = 0;
		smp_call_function_interrupt();
	}
	if (work->resched) {
		work->resched = 0;
		smp_resched_interrupt();
	}
}

static struct smp_funcall {
	smpfunc_t func;
	unsigned long arg1;
	unsigned long arg2;
	unsigned long arg3;
	unsigned long arg4;
	unsigned long arg5;
	unsigned long processors_in[NR_CPUS];	/* Set when ipi entered. */
	unsigned long processors_out[NR_CPUS];	/* Set when ipi exited. */
} ccall_info;

static DEFINE_SPINLOCK(cross_call_lock);

/* Cross calls must be serialized, at least currently. */
static void ajit_cross_call(smpfunc_t func, cpumask_t mask, unsigned long arg1,
			    unsigned long arg2, unsigned long arg3,
			    unsigned long arg4)
{
	if (smp_processors_ready) {
		register int high = NR_CPUS - 1;
		unsigned long flags;

		spin_lock_irqsave(&cross_call_lock, flags);

		{
			/* If you make changes here, make sure gcc generates proper code... */
			register smpfunc_t f asm("i0") = func;
			register unsigned long a1 asm("i1") = arg1;
			register unsigned long a2 asm("i2") = arg2;
			register unsigned long a3 asm("i3") = arg3;
			register unsigned long a4 asm("i4") = arg4;
			register unsigned long a5 asm("i5") = 0;

			__asm__ __volatile__("std %0, [%6]\n\t"
					     "std %2, [%6 + 8]\n\t"
					     "std %4, [%6 + 16]\n\t" : :
					     "r"(f), "r"(a1), "r"(a2), "r"(a3),
					     "r"(a4), "r"(a5),
					     "r"(&ccall_info.func));
		}

		/* Init receive/complete mapping, plus fire the IPI's off. */
		{
			register int i;

			cpumask_clear_cpu(smp_processor_id(), &mask);
			cpumask_and(&mask, cpu_online_mask, &mask);
			for (i = 0; i <= high; i++) {
				if (cpumask_test_cpu(i, &mask)) {
					ccall_info.processors_in[i] = 0;
					ccall_info.processors_out[i] = 0;
					leon_send_ipi(i, LEON3_IRQ_CROSS_CALL);

				}
			}
		}

		{
			register int i;

			i = 0;
			do {
				if (!cpumask_test_cpu(i, &mask))
					continue;

				while (!ccall_info.processors_in[i])
					barrier();
			} while (++i <= high);

			i = 0;
			do {
				if (!cpumask_test_cpu(i, &mask))
					continue;

				while (!ccall_info.processors_out[i])
					barrier();
			} while (++i <= high);
		}

		spin_unlock_irqrestore(&cross_call_lock, flags);
	}
}

/* Running cross calls. */
void ajit_cross_call_irq(void)
{
	int i = smp_processor_id();

	ccall_info.processors_in[i] = 1;
	ccall_info.func(ccall_info.arg1, ccall_info.arg2, ccall_info.arg3,
			ccall_info.arg4, ccall_info.arg5);
	ccall_info.processors_out[i] = 1;
}

static const struct sparc32_ipi_ops ajit_ipi_ops = {
	.cross_call = ajit_cross_call,
	.resched    = ajit_ipi_resched,
	.single     = ajit_ipi_single,
	.mask_one   = ajit_ipi_mask_one,
};

void __init leon_ajit_smp(void)
{
	/* Patch ipi15 trap table */
	t_nmi[1] = t_nmi[1] + (linux_trap_ipi15_leon - linux_trap_ipi15_sun4m);

	sparc32_ipi_ops = &ajit_ipi_ops;
}
