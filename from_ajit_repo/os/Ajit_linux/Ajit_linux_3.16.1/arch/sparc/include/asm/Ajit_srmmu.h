//Ajit_srmmu.h

#ifndef AJIT_SRMMU_H
#define AJIT_SRMMU_H


struct vm_area_struct;

void Ajit_flush_icache_all(void);
void Ajit_flush_dcache_all(void);
void Ajit_flush_pcache_all(struct vm_area_struct *vma, unsigned long page);
void Ajit_flush_cache_all(void);
void Ajit_flush_tlb_all(void);
void Ajit_switch_mm(void);
void  poke_Ajit_srmmu(void);
void  init_Ajit(void);
#endif
