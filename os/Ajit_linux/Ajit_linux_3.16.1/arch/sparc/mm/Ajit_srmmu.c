//Ajit cache and tlb flush/read operations

#include <linux/kernel.h>
#include <linux/mm.h>
#include <asm/asi.h>
#include <asm/Ajit_srmmu.h>
#include <asm/tlbflush.h>
#include "mm_32.h"
//#include <asm/oplib_32.h> //include this if you need prom_printf


//Flush all lines in icache
inline void Ajit_flush_icache_all(void)
{
	//prom_printf("\n------ %s",__FUNCTION__);
	//The flush instruction flushes the dcache
	//and then flushes the icache
	__asm__ __volatile__(" flush ");
}

//Flush all lines in dcache
inline void Ajit_flush_dcache_all(void)
{
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_M_FLUSH_CTX) : "memory");
}


inline void Ajit_flush_pcache_all(struct vm_area_struct *vma, unsigned long page)
{
	//	if (vma->vm_flags & VM_EXEC)
	//		Ajit_flush_icache_all();
	//	Ajit_flush_dcache_all();
	
	//flush dcache
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_M_FLUSH_CTX) : "memory");
	//flush icache
	__asm__ __volatile__(" flush ");

}


inline void Ajit_flush_cache_all(void)
{
	//flush dcache
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_M_FLUSH_CTX) : "memory");
	//flush icache
	__asm__ __volatile__(" flush ");
}


inline void Ajit_flush_tlb_all(void)
{
	//flush dcache
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_M_FLUSH_CTX) : "memory");
	//flush icache
	__asm__ __volatile__(" flush ");

	//flush TLB
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			"i"(ASI_M_FLUSH_PROBE) : "memory");
}

inline void Ajit_switch_mm(void)
{
	//flush dcache
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_M_FLUSH_CTX) : "memory");
	//flush icache
	__asm__ __volatile__(" flush ");

	//flush TLB
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			"i"(ASI_M_FLUSH_PROBE) : "memory");
}

inline void Ajit_flush_cache_mm(struct mm_struct *mm)
{
	//flush dcache
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_M_FLUSH_CTX) : "memory");
	//flush icache
	__asm__ __volatile__(" flush ");

}

inline void Ajit_flush_cache_page(struct vm_area_struct *vma, unsigned long page)
{
	//Ajit_flush_pcache_all(vma, page);
	//flush dcache
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_M_FLUSH_CTX) : "memory");
	//flush icache
	__asm__ __volatile__(" flush ");

}

inline void Ajit_flush_cache_range(struct vm_area_struct *vma,
				   unsigned long start,
				   unsigned long end)
{
	//flush dcache
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_M_FLUSH_CTX) : "memory");
	//flush icache
	__asm__ __volatile__(" flush ");

}

static void Ajit_flush_tlb_mm(struct mm_struct *mm)
{
	Ajit_flush_tlb_all();
}

static void Ajit_flush_tlb_page(struct vm_area_struct *vma,
				unsigned long page)
{
	Ajit_flush_tlb_all();
}

static void Ajit_flush_tlb_range(struct vm_area_struct *vma,
				 unsigned long start,
				 unsigned long end)
{
	Ajit_flush_tlb_all();
}

static void Ajit_flush_page_to_ram(unsigned long page)
{
	Ajit_flush_tlb_all();
}

static void Ajit_flush_sig_insns(struct mm_struct *mm, unsigned long page)
{
	Ajit_flush_tlb_all();
}

static void Ajit_flush_page_for_dma(unsigned long page)
{
	Ajit_flush_tlb_all();
}

void  poke_Ajit_srmmu(void)
{
	Ajit_flush_tlb_all();
}

//These are the operations we need to supply to the kernel:
static const struct sparc32_cachetlb_ops Ajit_ops = {
	.cache_all	= Ajit_flush_cache_all,
	.cache_mm	= Ajit_flush_cache_mm,
	.cache_page	= Ajit_flush_cache_page,
	.cache_range	= Ajit_flush_cache_range,
	.tlb_all	= Ajit_flush_tlb_all,
	.tlb_mm		= Ajit_flush_tlb_mm,
	.tlb_page	= Ajit_flush_tlb_page,
	.tlb_range	= Ajit_flush_tlb_range,
	.page_to_ram	= Ajit_flush_page_to_ram,
	.sig_insns	= Ajit_flush_sig_insns,
	.page_for_dma	= Ajit_flush_page_for_dma,
};

void  init_Ajit(void)
{
	//prom_printf("\n------ %s",__FUNCTION__);
	srmmu_name = "Ajit";
	sparc32_cachetlb_ops = &Ajit_ops;
	poke_srmmu = poke_Ajit_srmmu;
}

