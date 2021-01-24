//Print out context and page tables by reading the tables directly from memory using mmu context table ptr register 

#include <asm/oplib_32.h>
#include <asm/pgtsrmmu.h>



//load a 32 bit word from given physical address, 
//bypassing the mmu translation
inline int __attribute__((optimize("O0")))mmu_bypass_read(int* paddr)
{
        int retval;
        __asm__ __volatile__("lda [%1] %2, %0\n\t" :
                             "=r"(retval) : "r"(paddr), "i"(ASI_M_BYPASS));
        return retval;
}

//read mmu register
inline int __attribute__((optimize("O0")))mmu_read_register(int* paddr)
{
        int retval;
        __asm__ __volatile__("lda [%1] %2, %0\n\t" :
                             "=r"(retval) : "r"(paddr), "i"(ASI_M_MMUREGS));
        return retval;
}

//read mmu-context table pointer register
inline int __attribute__((optimize("O0")))mmu_read_context_table_pointer(void)
{
	return mmu_read_register((int*) SRMMU_CTXTBL_PTR);
}

unsigned long int getPhyAddrFromPTD(unsigned int PTD, unsigned int index)
{
	unsigned long int addr = PTD;
	addr=(addr>>2)<<6;
	addr=addr|(index <<2);
	return addr;
}

unsigned long int getPhyAddrFromPTE(unsigned int PTE)
{
	unsigned long int addr = PTE;
	addr=(addr>>8)<<12;
	return addr;
}

void Ajit_print_page_tables(void)
{
	int i;
	unsigned int context_table_ptr_reg;
	unsigned int context_table_ptr_phy;
	unsigned int PTD, PTD0;
	long unsigned int phy_addr; //temp avariable to store phy addresses


	prom_printf("\n ========================");
	prom_printf("\n Printing page tables : ");
	prom_printf("\n ========================");
	
	context_table_ptr_reg = mmu_read_context_table_pointer();
	prom_printf("\n context_table_ptr_reg = 0x%x", context_table_ptr_reg);
	context_table_ptr_phy = getPhyAddrFromPTD(context_table_ptr_reg,0);
	prom_printf("\n context_table_ptr_phy = 0x%x", context_table_ptr_phy);

	prom_printf("\n Context Table : ");
	for(i=0;i<256;i++)
	{
		PTD = mmu_bypass_read((int*)(context_table_ptr_phy + (i<<2) ));
		prom_printf("\n Context Table[0x%x] = 0x%x, phy_addr=0x%lx ",i,PTD, getPhyAddrFromPTD(PTD,0));
	}
	
	//L1 page table
	//read PTD for context 0
	PTD = mmu_bypass_read((int*)(context_table_ptr_phy));
	phy_addr = getPhyAddrFromPTD(PTD,0);
	prom_printf("\n L1 entries : ");
	for(i=0;i<256;i++)
	{
		PTD = mmu_bypass_read((int*)(phy_addr + (i<<2) ));
		prom_printf("\n L1 entry [0x%x] = 0x%x, phy_addr=0x%lx ",i,PTD, getPhyAddrFromPTD(PTD,0));
	}
	
	//Read L2 page tables for kernel addr space (0xf0...)
	PTD = mmu_bypass_read((int*)(phy_addr + (0xF0<<2)));
	phy_addr = getPhyAddrFromPTD(PTD,0);
	prom_printf("\n L2 entries for 0xf0... : ");
	PTD0=0;
	for(i=0;i<64;i++)
	{
		PTD = mmu_bypass_read((int*)(phy_addr + (i<<2) ));
		
		if(i==0 ) PTD0 = PTD; //remember PTD for index 0
		prom_printf("\n L2 entry [0x%x] = 0x%x, phy_addr=0x%lx ",i,PTD, getPhyAddrFromPTD(PTD,0));
	}
	
	//Read L3 page tables for kernel addr space (0xf000..)
	phy_addr = getPhyAddrFromPTD(PTD0,0);
	prom_printf("\n L3 entries for 0xf000 starting from location 0x%lx... : ",phy_addr);
	for(i=0;i<64;i++)
	{
		PTD = mmu_bypass_read((int*)(phy_addr + (i<<2) ));
		prom_printf("\n L3 entry [0x%x] = 0x%x, Phy_addr=0x%lx  ",i,PTD, getPhyAddrFromPTE(PTD));
	}


	prom_printf("\n ");
}




