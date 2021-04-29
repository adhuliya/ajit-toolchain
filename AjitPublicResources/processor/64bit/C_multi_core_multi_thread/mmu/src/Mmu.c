//Mmu.c
//
//
//For documentation see MmuBehavior.txt
//and Appendix H in Sparc V8 Reference Manual
//AUTHOR: Neha Karanjkar

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "Ajit_Hardware_Configuration.h"
#include "Ancillary.h"
#include "MmuInterface.h"
#include "ASI_values.h"
#include "RequestTypeValues.h"
#ifndef USE_NEW_TLB
#include "TLB.h"
#else
#include "tlbs.h"
#include "TlbNew.h"
#endif
#include "CacheInterface.h"
#include "rlut.h"
#include "bridge.h"


#ifdef SW
#include<stdio.h>
#endif


//#define MMU_DEBUG




//class of a fault
#define NOFAULT 0
#define IACCESS_FAULT 1
#define DACCESS_FAULT 2
#define __CACHEABLE__(ms) ((ms->MmuControlRegister & 0x100) != 0)



//Helper functions for Mmu
uint8_t   isValidMmuRequest(uint8_t asi);
uint8_t	  isCacheRelatedRequest(uint8_t asi);
uint8_t   MmuEnabled(MmuState* ms);
uint8_t   get_AT(uint8_t asi, uint8_t req_type);
uint8_t   getFaultType(uint8_t AT, uint32_t PTE);
void      updateFsrFar(MmuState* ms, uint32_t Fsr_val, uint32_t Far_val, uint8_t fault_class);
uint32_t  readMmuRegister(MmuState* ms,  uint32_t addr);
void 	  writeMmuRegister(MmuState* ms, uint32_t addr, uint8_t byte_mask, uint64_t data64);
uint8_t   translateToPhysicalAddress(MmuState* ms, uint8_t asi, uint32_t virt_addr, 
					uint8_t request_type, uint64_t* physical_addr, 
					uint8_t*  cacheable, uint8_t* acc, uint32_t* mmu_fsr_to_be_returned);
uint32_t  readPageTableEntryFromMemory(MmuState* ms, uint64_t physical_addr);
void      writePageTableEntryToMemory(MmuState* ms, uint32_t pte, uint64_t physical_addr);
uint8_t   walkPageTables(MmuState* ms,
				uint32_t virt_addr, uint32_t* pte, uint8_t* pte_level, 
				uint64_t* phy_addr_of_pte);
uint8_t   checkPageFaults(MmuState* ms,
			uint8_t pte_found, uint32_t pte, uint8_t pte_level, 
			uint8_t asi, uint32_t virt_addr, uint8_t request_type, 
			uint32_t* mmu_fsr_to_be_returned);
uint64_t  constructPhysicalAddr(uint32_t pte, uint8_t pte_level, uint32_t virt_addr);
uint8_t   isCacheable(uint32_t pte);
#ifndef USE_NEW_TLB
uint8_t   flushPTEfromTLB(MmuState* ms, uint32_t TLB_index);
uint32_t  getEmptyTLBLocation(MmuState* ms);
uint8_t   flushEntireTLB(MmuState* ms);
#endif
uint8_t   performMmuProbe(MmuState* ms, 
			uint32_t virt_addr, uint8_t asi, uint8_t request_type, uint32_t* PTE);






//Mmu Behavior
void Mmu(MmuState* ms,
			uint8_t mmu_command,
			uint8_t request_type,
			uint8_t asi, uint32_t addr,	
			uint8_t byte_mask, uint64_t write_data,
			uint8_t* mae, 
			uint8_t* cacheable, 
			uint8_t* acc,
			uint64_t* read_data,
			uint32_t* mmu_fsr,
			uint32_t* synonym_invalidate_word)
{
	// FSR value will be returned by 
	// the MMU when there is a fault.
	// The update of the FSR value will
	// happen only if there is a DCACHE access.
	*mmu_fsr = 0;
	*acc = 0;
	*synonym_invalidate_word = 0;

	#ifdef MMU_DEBUG
	printf("\nMMU: Received MMU request from Cache : asi=0x%x, addr=0x%x, mmu-command=0x%x, byte_mask=0x%x, data=0x%lx",asi,addr, mmu_command, byte_mask,data);
	#endif
				
	// bit with index 6.
	uint8_t lock_mask = (request_type & 0x40);

	// bits 7,6 are ignored.
	request_type = request_type & 0x3f;

	//-------------------------------------
	// CASE 0:
	//-------------------------------------
	// Check if this is an fsr,far update coming from the Dcache
	if(mmu_command == MMU_WRITE_FSR)
	{
		uint32_t fsr_from_dcache = getSlice64(write_data, 63, 32);
		uint32_t far_from_dcache = getSlice64(write_data, 31, 0);

		// update based on fault-type etc.
		// Note that a WRFSRFAR request can be
		// created only due to an Ifetch that faulted.
		updateFsrFar(ms, fsr_from_dcache, far_from_dcache, IACCESS_FAULT);

		*mae=0;
		*read_data=0;
		*cacheable=0;
		return;
	}
	//Check if this is a valid request.
	else if(!isValidMmuRequest(asi)) 
		exit(1);

	//-------------------------------------
	// CASE 1:
	//-------------------------------------
	//Check if this is a cache-related
	//request and should be ignored by the Mmu
	if(isCacheRelatedRequest(asi))
	{
		if(ASI_ICACHE_FLUSH(asi))
		{
			flushRlutInManager (ms->cpu_id, 1);
		}	

		if(ASI_DCACHE_FLUSH(asi))
		{
			flushRlutInManager (ms->cpu_id, 0);
		}

		//send a dummy response
		*mae=0;
		*read_data=0;
		*cacheable=0;
		return;
	}

	//-------------------------------------
	// CASE 2:
	//-------------------------------------
	//Check if this request should bypass the Mmu
	//and be forwarded untranslated to the system bus
	else if(ASI_MMU_PASS_THROUGH(asi) 
			|| (!MmuEnabled(ms) && !__CACHEABLE__(ms)  && //Mmu disabled and I/D request
				(  asi==ASI_USER_INSTRUCTION
				   ||asi==ASI_SUPERVISOR_INSTRUCTION
				   ||asi==ASI_USER_DATA
				   ||asi==ASI_SUPERVISOR_DATA
				)
			   ))
	{


		//wait for a response from Memory
		//
		// on MMU_READ_LINE slot the  word in the right place in the line.
		//
		uint64_t* ptr = ((mmu_command == MMU_READ_LINE) ? (read_data + cacheLineOffset(addr)) 
						: read_data);
		//forward the request to System bus
		while(1)
		{
			int ok = sysMemBusRequest(ms->cpu_id, (request_type | lock_mask),
							byte_mask, addr, write_data, ptr);
			if(ok)
				break;
		}

		//send the response back to the cache
		//that created this request
		*mae=0;
		*cacheable  = __CACHEABLE__(ms)  && !ASI_MMU_PASS_THROUGH(asi);
		ms->Num_Mmu_bypass_accesses+=1;

		ms->lock_flag = (lock_mask != 0);
		return;
	}

	//-------------------------------------
	// CASE 3:
	//-------------------------------------
	//Check if this is an Mmu Flush/Probe request
	else if(asi==ASI_MMU_FLUSH_PROBE)
	{
		//Probe operation
		if(request_type==REQUEST_TYPE_READ)
		{
#ifdef MMU_DEBUG
			printf("\nMMU: Received PROBE request : asi=0x%x, addr=0x%x, request_type=0x%x, byte_mask=0x%x, data=0x%lx",asi,addr, request_type, byte_mask, write_data);
#endif


			//Only type 4 probe (entire) is supported (Ref Sparc V8 manual pg 250).
			//On a probe operation, the TLB is first searched to find a 
			//page table entry (PTE) for a given address. If it is not found in the 
			//TLB, the page tables in memory are walked until the entry is found
			//or an error occurs.

			//If an error occurs :
			//- the FSR and FAR registers are updated
			//- a fault is not sent to the cpu, and 
			//a 0 is returned instead of PTE.
			//If no error occurs, a PTE is returned.
			uint8_t probe_success=0;
			uint32_t pte=0;
			probe_success = performMmuProbe(ms, addr, asi, request_type, &pte);
			if(probe_success)
			{
				*mae=0;
				*cacheable=0;
				*read_data=pte;
				if(getBit32(addr,2)==0) 
					*read_data = *read_data << 32;

				// If an error was caused, the FSR/FAR are modified inside
				// the performMmuProbe() routine. 

				return;
			}
			else
			{
				*read_data=0;
				*mae=0;
				*cacheable=0;

				return;
			}
			ms->Num_Mmu_probe_requests+=1;
		}
		//Flush operation
		else if(request_type==REQUEST_TYPE_WRITE)
		{
			//Flush operation is supported only at the
			//coarsest level. The entire TLB is flushed
			//on any flush request.

#ifdef MMU_DEBUG
			printf("\nMMU: Received FLUSH request : asi=0x%x, addr=0x%x, request_type=0x%x, byte_mask=0x%x, data=0x%lx",asi,addr, request_type, byte_mask,data);
#endif

#ifndef USE_NEW_TLB
			uint8_t success = flushEntireTLB(ms);
			if(success) *mae =0; else *mae=1;
#else
			// clear everything..
			initializeTlbNew(ms);
#endif 

#ifdef MMU_DEBUG
			fprintf(stderr,"----------- MMU-%d flushed TLB due to MMU-FLUSH-PROBE-WRITE ----------------- \n",ms->cpu_id);
#endif

			//send response to cpu
			*read_data=0;	*cacheable=0;
			ms->Num_Mmu_flush_requests+=1;

			return;
		}
		else
		{
#ifdef SW
			fprintf(stderr,"\nMMU: ERROR. asi=0x%x : Mmu flush/probe request\
					with invalid request type = 0x%x",asi,request_type);
			exit(1);
#endif
		}


	}

	//-------------------------------------
	// CASE 4:
	//-------------------------------------
	//Check if this is an Mmu Register read/write request
	else if(asi==ASI_MMU_REGISTER)
	{

		if(request_type==REQUEST_TYPE_READ)
		{
			*read_data=readMmuRegister(ms, addr);
			//send the value on bits 63:32 of the 64 bit data-bus
			//because all mmu-register addresses are even-addresses.
			*read_data =  *read_data << 32; 
			//send response to cpu
			*mae=0; 	*cacheable=0;
			ms->Num_Mmu_register_reads+=1;

		}
		else if(request_type==REQUEST_TYPE_WRITE)
		{
			// will flush TLB if write to context-pointer-regiser.
			writeMmuRegister(ms, addr,byte_mask,write_data);
			//send response to cpu
			*mae=0; *read_data=0; 	*cacheable=0;
			ms->Num_Mmu_register_writes+=1;
		}

		return;
	}

	//-------------------------------------
	// CASE 5:
	//-------------------------------------
	//Check if this is an Mmu Diagnostic request
	else if(  asi==ASI_MMU_DIAGNOSTIC_I
			||asi==ASI_MMU_DIAGNOSTIC_I_D
			||asi==ASI_MMU_DIAGNOSTIC_IO)
	{
#ifdef SW
		fprintf(stderr,"\nMMU: ERROR MMU-DIAGNOSTIC OPERATIONS with asi=0x%x not implemented YET ",asi);
		exit(1);
#endif
	}
	else
		//-------------------------------------
		// CASE 6:
		//-------------------------------------
		//This is an instruction/data access.
		//Perform virtual to physical translation!
	{
		uint64_t physical_addr=0;
		uint8_t translation_success=0;

		//perform translation of virtual
		//address to physical address.
		translation_success = 
			translateToPhysicalAddress(ms, asi, addr, request_type, 
							&physical_addr, 
							cacheable, 
							acc,
							mmu_fsr);



		//If translation was successful,
		//perform the memory access
		//and send response to cpu
		//If translation was unsuccessful,
		//the FAR and FSR registers have been updated.
		//Send error signal to the cpu.
		if(translation_success)
		{
			
			int I;

			uint64_t line_physical_addr = physical_addr & 0xffffffffffffffc0;
			uint32_t physical_line_addr =  (physical_addr >> LOG_BYTES_PER_CACHE_LINE);
			uint32_t virtual_line_addr  =  (addr >> LOG_BYTES_PER_CACHE_LINE);

			if(mmu_command == MMU_READ_LINE)
			{
				if(*cacheable)
				{

					// invalidate the synonym in the VIVT cache.
					*synonym_invalidate_word = 
						lookupAndUpdateRlutInManager(ms->cpu_id,		
										physical_line_addr,
										virtual_line_addr,
										ASI_ICACHE_VALID(asi));		
					// fetch the line.
					int N_DWORDS =  BYTES_PER_CACHE_LINE/8;
					for (I = 0; I < N_DWORDS; I++)
					{
						//forward the request to System bus
						while(1)
						{
						 	int ok = 
						    	   sysMemBusRequest(ms->cpu_id,
									(lock_mask | REQUEST_TYPE_READ), 
									byte_mask, 
									line_physical_addr+(8*I), 
									write_data,
									(read_data + I));
							if(ok)
								break;
						}
					}
				}
				else
					// not cacheable... do not read the whole line...
				{
					I = cacheLineOffset(addr);
					while(1)
					{
						int ok = 
							sysMemBusRequest(ms->cpu_id, 
									(lock_mask | REQUEST_TYPE_READ), 
									byte_mask,
									line_physical_addr+(8*I), 
									write_data, 
									read_data + I);

						if(ok)
							break;
					}
				}
			}
			else 
			{
				while(1)
				{
					int ok = sysMemBusRequest(ms->cpu_id, 
								(lock_mask | request_type), 
								byte_mask,
								physical_addr,
								write_data,
								read_data );
					if(ok)
						break;
				}

			}

			//send the response back to the cache
			//that created this request
			*mae=0;
			*mmu_fsr=0;

			if(MmuEnabled(ms))
				ms->Num_Mmu_translated_accesses+=1;

		}
		else
		{
			//******A fault has occured*****.
			//If this was a request coming from DCACHE,
			//	The FSR and FAR MMU registers
			//	have been updated by the translation routine.
			//If this was a request coming from ICACHE:
			//	the FSR/FAR have not been updated,
			//	as this could have been a speculated instruction.
			//	We send the FSR value back to the ICACHE,
			//	to be updated later when it is confirmed that the 
			//	instruction was real.
			//send error signal to the cpu, depending on the
			//value of NF (no fault) bit in the Control register

			//First compute the values of mae and fsr
			uint8_t NF = getBit32(ms->MmuControlRegister,1);
			if(NF==0 || asi==0x09)
			{
				//send error signal to processor
				*mae=1;
				*read_data=0;
				*cacheable=0;

				//
				// if no dword response is expected, we do not expect
				// mae to be 0.
				//
				assert (mmu_command != MMU_WRITE_DWORD_NO_RESPONSE);
#ifdef MMU_DEBUG
				printf("\n MMU : Sending mae=1 to the cpu due to translation error for addr=0x%x",addr);
#endif
			}
			else
			{
				*mae=0;
				*read_data=0;
				*cacheable=0;
#ifdef MMU_DEBUG
				printf("\n MMU : Not sending mae=1 to the cpu due to translation error for addr=0x%x as NoFault bit =1",addr);
#endif

			}

		}
		ms->lock_flag = (lock_mask != 0);
		return;
	}
}



//Mmu Probe operation
//Only type 4 probe (entire) is supported (Ref Sparc V8 manual pg 250).
//On a probe operation, the TLB is first searched to find a 
//page table entry (PTE) for a given address and current context. If it is not found in the 
//TLB, the page tables in memory are walked until the entry is found
//or an error occurs.
//If an error occurs :
//- the FSR and FAR registers are updated
//- a fault is *not* sent to the cpu, and 
//a 0 is returned instead of PTE.
//If no error occurs, a PTE is returned.
uint8_t performMmuProbe(MmuState* ms,
		uint32_t virt_addr, uint8_t asi, uint8_t request_type, uint32_t* PTE)
{
	uint8_t    TLB_hit=0;		//whether PTE was found in TLB
	//stores the index of the TLB entry
	uint8_t	   pte_found=0;		//whether PTE was found after walking page tables in memory
	uint32_t   pte=0;		//the value of PTE read from TLB or fetched from page tables in memory
	uint8_t	   pte_level=0;		//the level of PTE read from TLB or fetched from memory
	uint64_t   phy_addr_of_pte=0;   //the physical address where this PTE was found in memory
	uint32_t   va_tag=getSlice32(virt_addr, 31,12);
	*PTE=0;


	if(TLB_ENABLED)
	{
		//Check if the access HITS in the TLB,
		//If HIT, get  index of the 
		//corresponding page table entry in TLB
#ifndef USE_NEW_TLB
		uint32_t   TLB_index;		//If a valid PTE was found in TLB, this variable
		TLB_hit = isTLBHit(ms, va_tag, ms->MmuContextRegister, &TLB_index);
#else
		TLB_hit = isTlbNewHit(ms, virt_addr,va_tag, &pte, &pte_level);
#endif
		if(TLB_hit)
		{

#ifndef USE_NEW_TLB
			//get the pte
			pte=ms->TLB_entries[TLB_index].pte;
			pte_level=ms->TLB_entries[TLB_index].pte_level;
#endif

			*PTE=pte;
			pte_found=1;
			return 1;

		}
	}
	if(!TLB_ENABLED || !TLB_hit)
	{
		//a matching PTE was not found.
		//Need to walk the page tables in memory
		//to search for a valid PTE
		pte_found = walkPageTables(ms, virt_addr, &pte, &pte_level, &phy_addr_of_pte);

		//check if PTE is valid, else update FSR and FAR registers
		if(!pte_found)
		{
			uint32_t fsr_to_be_updated_after_probe =0;
			checkPageFaults(ms, pte_found, pte, pte_level, asi, virt_addr, request_type, &fsr_to_be_updated_after_probe); 
			*PTE=0;
			return 0;
		}
		else
		{
			*PTE=pte;
		}

	}
	return 1;
}







//translate a virtual address to physical address
//
//if translation succeeds :
//
//	if the modified/referenced bits for the PTE
//	have to be changed, write the updated PTE back into memory
//	
//	set physical_addr = the translated 64-bit physical address
//	
//	return cacheable = 1 or 0 to the cache 
//	indicating whether this instr/data should be kept in cache
//	depending on the PTE entry for this page.
//
//	return 1
//
//if translation fails (a fault has occured) :
//	update FSR and FAR registers to indicate fault information
//	return 0
uint8_t translateToPhysicalAddress(MmuState* ms,
					uint8_t   asi, 
					uint32_t  virt_addr, 
					uint8_t   request_type, 
					uint64_t* physical_addr, 
					uint8_t*  cacheable,
					uint8_t*  acc,
					uint32_t* mmu_fsr_to_be_returned)
{

	if(!MmuEnabled(ms))
	{
		*cacheable = __CACHEABLE__(ms);
		*acc = 3;
		*mmu_fsr_to_be_returned = 0;
		*physical_addr = virt_addr;
		return 1;
	}
	
	uint8_t    TLB_hit=0;		//whether PTE was found in TLB
	uint8_t	   pte_found=0;		//whether PTE was found after walking page tables in memory
	uint32_t   pte=0;		//the value of PTE read from TLB or fetched from page tables in memory
	uint8_t	   pte_level=0;		//the level of PTE read from TLB or fetched from memory
	uint64_t   phy_addr_of_pte=0;   //the physical address where this PTE was found in memory
	uint32_t   va_tag=getSlice32(virt_addr, 31,12); //virtual addr tag
	uint8_t    access_allowed;
#ifndef USE_NEW_TLB
	uint32_t TLB_index;
#endif
	
	// default 0.
	*mmu_fsr_to_be_returned = 0;

	if(TLB_ENABLED)
	{
		//Check if the access HITS in the TLB,
		//If HIT, get  index of the 
		//corresponding page table entry in TLB
#ifndef USE_NEW_TLB
		TLB_hit = isTLBHit(ms, va_tag, ms->MmuContextRegister, &TLB_index);
#else
		TLB_hit = isTlbNewHit(ms, virt_addr, va_tag, &pte, &pte_level);
#endif

		if(TLB_hit)
		{
			//get the pte
			ms->Num_Mmu_TLB_hits+=1;
#ifndef USE_NEW_TLB
			pte=ms->TLB_entries[TLB_index].pte;
			pte_level=ms->TLB_entries[TLB_index].pte_level;
#endif
			pte_found=1;
		}
	}

	if(!TLB_ENABLED || !TLB_hit)
	{
	
		//We need to walk the page tables in memory
		//to search for a valid PTE
		pte_found = walkPageTables(ms, virt_addr, &pte, &pte_level, &phy_addr_of_pte);
	}

	
	//We searched for a PTE.
	//At this point, if a PTE is not found, or PTE is found but 
	//permissions don't match, update FSR, FAR and return early.
	access_allowed = checkPageFaults(ms, pte_found, pte, pte_level, asi, virt_addr, request_type, mmu_fsr_to_be_returned);
	if(!pte_found || !access_allowed) return 0;


	//OK. a PTE has been found, and we have access permissions.
	//store the PTE in the TLB if required.
	if(TLB_ENABLED && !TLB_hit)
	{
		
#ifndef USE_NEW_TLB
		TLB_index = getEmptyTLBLocation(ms);
		writeTLBentry(ms,  TLB_index, va_tag, ms->MmuContextRegister, pte, pte_level);
#else
		writeTlbNewEntry(ms, virt_addr, va_tag, pte, pte_level);
#endif

		TLB_hit=1;
	}

	//Obtain phy address from virtual address and PTE 
	*physical_addr = constructPhysicalAddr(pte, pte_level, virt_addr);
	//check if this access is cacheable
	*cacheable=isCacheable(pte);
	*acc  = getSlice32(pte,4,2);

	//Update the PTE entry if necessary
	uint32_t updated_pte=pte;
	//set the M (modified) bit if it's a write access
	if(request_type==REQUEST_TYPE_WRITE) updated_pte=setBit32(updated_pte,6,0x1);
	//set the R (read) bit when the page is accessed
	updated_pte=setBit32(updated_pte,5,0x1);
		
	if(!(updated_pte==pte))
	{
		//write the updated pte back to memory.
		{
			uint8_t pte_found_in_mem =0;
			uint32_t pte_in_mem=0;
			uint8_t pte_level_in_mem=0;
			uint64_t phy_addr_of_pte_in_mem=0;
			pte_found_in_mem = walkPageTables(ms, 
						virt_addr, &pte_in_mem, &pte_level_in_mem, 
						&phy_addr_of_pte_in_mem);
			if(!pte_found_in_mem)
			{
				#ifdef SW
				printf("\n ERROR : PTE present in TLB but not found in page tables in memory for asi=0x%x, address=0x%x, request_type=0x%x",asi,virt_addr,request_type);
				printf("\n This should be a bug in the MMU.");
				printf("\n Exiting!");
				exit(1);
				#endif
			}
			else
			{
				phy_addr_of_pte = phy_addr_of_pte_in_mem;
				writePageTableEntryToMemory(ms, updated_pte, phy_addr_of_pte);
			}
		}

		//also update the value of PTE in TLB
		if(TLB_ENABLED)
		{
#ifndef USE_NEW_TLB
			updateTLBentry(ms, TLB_index, updated_pte);
#else
			writeTlbNewEntry(ms, virt_addr, va_tag, updated_pte, pte_level);
#endif
		}
	}

	//return success
	return 1;
}






//read a PTE/PTD entry from a given physical address
//in memory
uint32_t readPageTableEntryFromMemory(MmuState* ms,uint64_t physical_addr)
{
	
	uint8_t request_type=REQUEST_TYPE_READ;
	uint64_t data64=0;
	uint8_t byte_mask=0;
	uint32_t pte=0;

	uint8_t lock_mask = (ms->lock_flag << 6);
	while(1)
	{
		int ok = sysMemBusRequest (ms->cpu_id, (request_type | lock_mask),  byte_mask,
							physical_addr, data64, &data64);
		if(ok)
			break;
	}

	//check if even/odd word from the
	//fetched double word is to be used
	if(getBit64(physical_addr,2)==0)
		pte=(data64>>32);
	else
		pte=data64;
	return pte;
}


//write a PTE/PTD entry to memory 
void writePageTableEntryToMemory(MmuState* ms, uint32_t pte, uint64_t physical_addr)
{
	
	uint8_t request_type=REQUEST_TYPE_WRITE;
	uint64_t data64=pte;
	uint8_t byte_mask=0;
	
	uint8_t lock_mask = (ms->lock_flag << 6);
	//fetched double word is to be used
	if(getBit64(physical_addr,2)==0)
	{
		data64=(data64<<32);
		byte_mask = 0xf0;
	}
	else
	{
		data64=pte;
		byte_mask=0x0f;
	}

	while(1)
	{
		//send WRITE request to System bus
		int ok = sysMemBusRequest(ms->cpu_id,
						request_type | lock_mask, 
						byte_mask,
						physical_addr, data64, &data64);
		if(ok)
			break;
	}
}



//Find out phy addr of an entry in a page table
//from a PTD and an index into the table
uint64_t getPhyAddrFromPTD(uint32_t PTD, uint32_t index)
{
	//zero out the last two bits in the PTD
	uint64_t phy_addr=setSlice32(PTD,1,0,0);
	uint64_t i = index;
	phy_addr = phy_addr<<4; //the page number in PTD appears on bits 35:4 on the physical addr bus.
	phy_addr = phy_addr | (i<<2); //index into the table
	return phy_addr;
}


//walk the page tables in memory to search for a valid PTE
uint8_t walkPageTables(MmuState* ms,
			uint32_t virt_addr, uint32_t* pte, uint8_t* pte_level, uint64_t* phy_addr_of_pte)
{
	uint8_t  pte_found=0;
	uint32_t PTE=0 ;
	uint32_t PTE_LEVEL=0;
	
	uint32_t context_table_index= ms->MmuContextRegister;	   //Index into context table
	uint32_t L1_page_table_index= getSlice32(virt_addr,31,24); //Index into level 1 page table
	uint32_t L2_page_table_index= getSlice32(virt_addr,23,18); //Index into level 2 page table
	uint32_t L3_page_table_index= getSlice32(virt_addr,17,12); //Index into level 3 page table
	
	uint64_t phy_addr=0;
	

	//read Level 0 PTD/PTE entry from context table
	PTE_LEVEL =0;
	phy_addr = getPhyAddrFromPTD(ms->MmuContextTablePointerRegister, context_table_index);
	PTE=readPageTableEntryFromMemory(ms, phy_addr);
	
	if(getSlice32(PTE,1,0)==0x1) //This is a PTD. Fetch entry from Level1 Table
	{
		PTE_LEVEL=1;
		phy_addr = getPhyAddrFromPTD(PTE, L1_page_table_index);
		PTE=readPageTableEntryFromMemory(ms, phy_addr);

		if(getSlice32(PTE,1,0)==0x1) //This is a PTD. Fetch entry from Level2 Table
		{
			PTE_LEVEL=2;
			phy_addr = getPhyAddrFromPTD(PTE, L2_page_table_index);
			PTE=readPageTableEntryFromMemory(ms, phy_addr);


			if(getSlice32(PTE,1,0)==0x1) //This is a PTD. Fetch entry from Level3 Table
			{
				PTE_LEVEL=3;
				phy_addr = getPhyAddrFromPTD(PTE, L3_page_table_index);
				PTE=readPageTableEntryFromMemory(ms, phy_addr);
			}
		}
	}
	
	//page walk ended.
	//We have either found a valid PTE or not
	
	if( getSlice32(PTE,1,0)==0x02) pte_found=1;//We have found a valid PTE
	else 	pte_found=0;

	
	*pte=PTE;
	*pte_level=PTE_LEVEL;
	*phy_addr_of_pte = phy_addr;
	return pte_found;
}







//check if a given memory access should be allowed
//to proceed as per the access permissions specified in ACC field in 
//the page table entry.
//
//If access should be allowed : 
//	return 1
//If access causes a page fault/protection fault/privilege fault:
//	update FSR/FAR registers to note the fault
//	return 0
//See ACC field in Appendix H, Sparc v8 manual.

uint8_t checkPageFaults(MmuState* ms, 
				uint8_t pte_found, uint32_t pte, uint8_t pte_level, 
				uint8_t asi, uint32_t virt_addr, uint8_t request_type, 
				uint32_t* fsr_to_cache)
{
	
	uint8_t AT=0;
	uint8_t fault_type=0;

	//Obtain Access Type from the asi and request_type:
	AT = get_AT(asi, request_type);

	//Get fault-type from the pte
	fault_type = getFaultType(AT, pte);
	
	//we have computed AT and FT.
	if(fault_type==0) return 1; //no fault has occured
	else
	{
		//A fault has occured. Calculate the new fsr value.
		uint32_t new_fsr_value = 0;

		//EBE
		new_fsr_value = setSlice32(new_fsr_value,17,10, 0x0);

		//L (pte level)
		new_fsr_value = setSlice32(new_fsr_value,9,8, pte_level);

		//AT (Access Type) 
		new_fsr_value = setSlice32(new_fsr_value,7,5, AT);

		//FT (Fault type) 
		new_fsr_value = setSlice32(new_fsr_value,4,2, fault_type);

		//FAV (Fault Addr Valid) = 1
		new_fsr_value = setSlice32(new_fsr_value,1,1, 0x1);

		//The OW (overflow) bit is determined inside
		//the updateFsrFar() routine.

		if(request_type != REQUEST_TYPE_IFETCH)
		{
			//if the request is NOT from ICACHE, 
			//then the FSR/FAR values are updated immediately.
			updateFsrFar(ms, new_fsr_value, virt_addr, DACCESS_FAULT);

		}
		else
		{
			//If the request is from ICACHE,
			//FSR is not written, but is instead communicated
			// to the pipeline via the ICACHE.
			*fsr_to_cache = new_fsr_value;
		}
#ifdef MMU_DEBUG
		printf(" MMU fault occured : ACC = 0x%x, AT=0x%x, fault_type=0x%x, Fault address=0x%x", ACC, AT, fault_type, virt_addr);
#endif

		return 0;
	}
}







//return value of cacheable bit in a PTE
uint8_t isCacheable(uint32_t pte)
{
	return  getBit32(pte,7);
}

//construct physical address
//from pte, virtual address and pte_level
uint64_t constructPhysicalAddr(uint32_t pte, uint8_t pte_level, uint32_t virt_addr)
{
	//get page offset
	uint64_t page_offset;
	if	(pte_level==3) page_offset=getSlice32(virt_addr,11,0);
	else if (pte_level==2) page_offset=getSlice32(virt_addr,17,0);
	else if (pte_level==1) page_offset=getSlice32(virt_addr,23,0);
	else                   page_offset=getSlice32(virt_addr,31,0);

	//get page number from pte
	uint32_t PPN = getSlice32(pte,31,8);

	//construct physical address:
	uint64_t phy_addr=0;
	phy_addr = PPN;
	phy_addr = phy_addr<<12;
	phy_addr = phy_addr | page_offset;

	return phy_addr;
}



MmuState* makeMmuState (uint32_t cpu_id)
{
	MmuState* ms = (MmuState*) malloc (sizeof (MmuState));
	ms->cpu_id = cpu_id;

	sprintf(ms->req_pipe, "AJIT_to_ENV_request_type_%d", cpu_id);
	sprintf(ms->addr_pipe, "AJIT_to_ENV_addr_%d", cpu_id);
	sprintf(ms->wdata_pipe, "AJIT_to_ENV_data_%d", cpu_id);
	sprintf(ms->byte_mask_pipe, "AJIT_to_ENV_byte_mask_%d", cpu_id);
	sprintf(ms->rdata_pipe, "ENV_to_AJIT_data_%d", cpu_id);

#ifdef USE_NEW_TLB
	// fully associative TLB with 2 entries.
	ms->tlb_0 = findOrAllocateSetAssociativeMemory(0,32,32,1,1);
	// fully associative with 8 entries.
	ms->tlb_1 = findOrAllocateSetAssociativeMemory(1,32,32,3,3);
	// fully associative with 16 entries.
	ms->tlb_2 = findOrAllocateSetAssociativeMemory(2,32,32,4,4);
	// 8-way set associative with 64 entries.
	ms->tlb_3 = findOrAllocateSetAssociativeMemory(3,32,32,6,3);
#endif

	resetMmuState (ms);

	return(ms);
}

//Initialize mmu state
void resetMmuState(MmuState* ms)
{
	ms->MmuControlRegister=0;
	ms->MmuContextTablePointerRegister=0;
	ms->MmuContextRegister=0;
	ms->MmuFaultStatusRegister=0;
	ms->MmuFaultAddressRegister=0;
	ms->Mmu_FSR_FAULT_CLASS=NOFAULT;

	ms->Num_Mmu_bypass_accesses=0;
	ms->Num_Mmu_probe_requests=0;
	ms->Num_Mmu_flush_requests=0;
	ms->Num_Mmu_register_reads=0;
	ms->Num_Mmu_register_writes=0;
	ms->Num_Mmu_translated_accesses=0;
	ms->Num_Mmu_TLB_hits=0;

#ifndef USE_NEW_TLB
	initializeTLB(ms);
#else
	initializeTlbNew(ms);
#endif

	ms->lock_flag = 0;
}

void printMmuStatistics(MmuState* ms)
{
#ifdef SW
	assert(ms != NULL);

	printf("\nMmu statistics for cpuid=%d: MMU ENABLED = %d", ms->cpu_id, MmuEnabled(ms) );
	printf("\n	TLB size (L0 %d L1 %d L2 %d L3 %d)",TLB0_SIZE, TLB1_SIZE, TLB2_SIZE, TLB3_SIZE);
	printf("\n	Accesses with Mmu bypassed or disabled 	= %d",    ms->Num_Mmu_bypass_accesses);
	printf("\n	Mmu_probe_requests  	= %d",     ms->Num_Mmu_probe_requests);
	printf("\n	Mmu_flush_requests  	= %d",     ms->Num_Mmu_flush_requests);
	printf("\n	Mmu_register_reads   	= %d",     ms->Num_Mmu_register_reads);
	printf("\n	Mmu_register_writes 	= %d",    ms->Num_Mmu_register_writes);
	printf("\n	Mmu_translated_accesses = %d",    ms->Num_Mmu_translated_accesses);
	printf("\n	Mmu_TLB_hits            = %d",    ms->Num_Mmu_TLB_hits);
	printf("\n");
	printf("\nMmu Register values :");
	printf("\n	Control register 	= 0x%x",    ms->MmuControlRegister);
	printf("\n	Context table ptr 	= 0x%x",    ms->MmuContextTablePointerRegister);
	printf("\n	Context register   	= 0x%x",    ms->MmuContextRegister);
	printf("\n	FSR		   	= 0x%x",    ms->MmuFaultStatusRegister);
	printf("\n	FAR		 	= 0x%x",    ms->MmuFaultAddressRegister);
	printf("\n");


#endif
};



//Mmu Register read/write functions
//The addr field is interpreted as follows:
//(see Table H-5 in Sparc V8 Ref. Manual)
//	VA[31:0]			Register
//	---------------------------------------------
//	0X000000xx			Control Register
//	0X000001xx                      Context Table Pointer Register
//	0X000002xx                      Context Register
//	0X000003xx                      Fault Status Register
//	0X000004xx                      Fault Address Register
//	0X000005xx to 0X00000Fxx        Reserved
//	0X000010xx to 0XFFFFFFxx        Unassigned


//returns contents of  Mmu register
//reading FSR register should clear it
uint32_t readMmuRegister(MmuState* ms, uint32_t addr)
{
	
	
	uint32_t register_id = getSlice32(addr,31,8);
	uint32_t result;
	if	(register_id==0) result = ms->MmuControlRegister;
	else if (register_id==1) result = ms->MmuContextTablePointerRegister;
	else if (register_id==2) result = ms->MmuContextRegister;
	else if (register_id==3) 
	{
		result = ms->MmuFaultStatusRegister;
		//A read to the FSR clears it
		ms->MmuFaultStatusRegister = 0;
		ms->Mmu_FSR_FAULT_CLASS = NOFAULT;
	}
	else if (register_id==4) result = ms->MmuFaultAddressRegister;
	else
	{
		#ifdef SW
		fprintf(stderr,"\nMMU: ERROR. In command READ_MMU_REGISTER,\
		addr = 0x%x does not correspond to a valid register",addr);
		#endif
		result=0;

	}
	
	#ifdef MMU_DEBUG
	printf("\nMMU: Received MMU register READ request to register ");
	if	(register_id==0) printf(" MmuControlRegister");
	else if (register_id==1) printf(" MmuContextTablePointerRegister");
	else if (register_id==2) printf(" MmuContextRegister");
	else if (register_id==3) printf(" MmuFaultStatusRegister");
	else if (register_id==4) printf(" MmuFaultAddressRegister");
	printf(",  addr=0x%x, data read = 0x%x",addr,result);
	#endif

	
	return result;
}

//write to Mmu registers
void writeMmuRegister(MmuState* ms, uint32_t addr, uint8_t byte_mask, uint64_t data64)
{
	uint32_t register_id = getSlice32(addr,31,8);
	uint32_t data32=data64;
	if     (byte_mask==0x0f) data32=data64;
	else if(byte_mask==0xf0) data32=getSlice64(data64,63,32);
	if(!(byte_mask==0x0f || byte_mask==0xf0) || register_id >4)
	{
		#ifdef MMU_DEBUG
		fprintf(stderr,"\nMMU-%d: ERROR. Invalid WRITE_MMU_REGISTER command,\
		ms->cpu_id, addr = 0x%x, byte_mask=0x%x, data=0x%lx", addr, byte_mask, data64);
		#endif
	}

	if	(register_id==0)  {
		ms->MmuControlRegister		=data32;
	}
	else if (register_id==1) {
		 ms->MmuContextTablePointerRegister=data32;
	}
	else if (register_id==2) {
		 ms->MmuContextRegister 		=data32;
#ifdef MMU_DEBUG
		 fprintf(stderr,"------ Mmu-%d context-register = %x --------------\n", ms->cpu_id, data32);
#endif
	}
	
	#ifdef MMU_DEBUG
	printf("\nMMU-%d: Written word=0x%x to register ",ms->cpu_id, data32);
	if	(register_id==0) printf(" MmuControlRegister		");
	else if (register_id==1) printf(" MmuContextTablePointerRegister");
	else if (register_id==2) printf(" MmuContextRegister 		");
	printf("\n");
	#endif

	//writes to FSR and FAR registers should be ignored
	//else if (register_id==3)  MmuFaultStatusRegister	=data32;
	//else if (register_id==4)  MmuFaultAddressRegister	=data32;
	
	//Writes to MmuContextTablePointerRegister 
	//should flush the entire TLB.
	if (TLB_ENABLED && register_id==1)
	{
#ifndef USE_NEW_TLB
		flushEntireTLB(ms);
#else
		initializeTlbNew(ms);
#endif 
		fprintf(stderr,"------ MMU-%d TLB flushed due to context-table-pointer-write (=%x) ------\n", ms->cpu_id, data32);
		
	}
	
}


	
	
//returns true if the 
//Enable bit in the Mmu is set
uint8_t MmuEnabled(MmuState* ms)
{
	uint8_t Enable_bit = getBit32(ms->MmuControlRegister,0);
	return Enable_bit;
}

//return true if this is a cache-related request
//(such as cache flush/read cache data/tag)
//and should be ignored by the Mmu

uint8_t isCacheRelatedRequest(uint8_t asi)
{
	if(  asi==ASI_CACHE_TAG_I
	   ||asi==ASI_CACHE_DATA_I
	   ||asi==ASI_CACHE_TAG_I_D
	   ||asi==ASI_CACHE_DATA_I_D
	   || ASI_ICACHE_FLUSH(asi)
	   || ASI_DCACHE_FLUSH(asi)
	)
		{
			return 1;
		} 
	else
		return 0;
}



//returns true, if the request coming from cpu-side 
//is a valid request
uint8_t isValidMmuRequest(uint8_t asi)
{
	if(  asi==ASI_BLOCK_COPY
	   ||asi==ASI_BLOCK_FILL
	   ||ASI_reserved(asi)
	   ||ASI_unassigned(asi)
	  )
	{
		#ifdef SW
		fprintf(stderr,"\nMMU: ERROR. asi=0x%x not valid or not supported",asi);
		#endif 
		return 0;
	}
	return 1;
}



#ifndef USE_NEW_TLB


//flush a TLB entry 
//return 1 if flush was successful
uint8_t  flushPTEfromTLB(MmuState* ms, uint32_t TLB_index)
{
	//Just invalidate the PTE entry
	ms->TLB_entries[TLB_index].va_tag=0;
	ms->TLB_entries[TLB_index].ctx_tag=0;
	ms->TLB_entries[TLB_index].pte=0;
	ms->TLB_entries[TLB_index].pte_level=0;
	return 1;
}



//flush the entire TLB 
////return 1 if flush was successful
uint8_t  flushEntireTLB(MmuState* ms)
{
	uint32_t i;
	if(TLB_ENABLED)
	{
		for(i=0;i<TLB_SIZE;i++)
		{
			if(flushPTEfromTLB(ms, i)==0) return 0; //there was an error
		}
	}
	return 1; //success
}




	
//return the first empty location in TLB
//to store a new entry. If all TLB entries
//are valid, pick a random entry, flush 
//it to memory and use that location
uint32_t getEmptyTLBLocation(MmuState* ms)
{
	uint32_t i;
	uint32_t pte;
	for(i=0;i<TLB_SIZE;i++)
	{
		pte=ms->TLB_entries[i].pte;
		if(getSlice32(pte,1,0)==0) //empty TLB entry
		{
			return i;
		}
	}
	
	//None of the TLB entries are empty.
	//Pick an entry randomly
	i = rand()%TLB_SIZE;

	//flush/invalidate the existing TLB entry
	flushPTEfromTLB(ms, i);
	
	return i;
}

#endif

//Compute access type (AT)
//from asi and request_type values.
//See Sparc manual appendix H
uint8_t get_AT(uint8_t asi, uint8_t req_type)
{
	uint8_t AT=0;

	//reads
	if(req_type==REQUEST_TYPE_READ)
	{
		if	(asi==ASI_USER_DATA) 		  AT = 0; //0       Load from User Data Space
		else if	(asi==ASI_SUPERVISOR_DATA)	  AT = 1; //1       Load from Supervisor Data Space
		else if	(asi==ASI_USER_INSTRUCTION)	  AT = 2; //2       Load/Execute from User Instruction Space
		else if	(asi==ASI_SUPERVISOR_INSTRUCTION) AT = 3; //3       Load/Execute from Supervisor Instruction Space
	}
	else if(req_type==REQUEST_TYPE_IFETCH)
	{
		if	(asi==ASI_USER_INSTRUCTION)	  AT = 2; //2       Load/Execute from User Instruction Space
		else if	(asi==ASI_SUPERVISOR_INSTRUCTION) AT = 3; //3       Load/Execute from Supervisor Instruction Space
	}
	else if(req_type==REQUEST_TYPE_WRITE)
	{
		if	(asi==ASI_USER_DATA)		 AT = 4; //4       Store to User Data Space
		else if	(asi==ASI_SUPERVISOR_DATA)	 AT = 5; //5       Store to Supervisor Data Space
		else if	(asi==ASI_USER_INSTRUCTION)   	 AT = 6; //6       Store to User Instruction Space
		else if	(asi==ASI_SUPERVISOR_INSTRUCTION)AT = 7; //7       Store to Supervisor Instruction Space
	}
	return AT;
}


//Compute fault-type for an access, by checking the
//page permissions (ACC field in the PTE).
//Returns 
//	- 0 if there is no fault 
//	- a non-zero fault-type value if the access causes a fault. 

uint8_t getFaultType(uint8_t AT, uint32_t PTE)
{
	uint32_t ET  = getSlice32(PTE,1,0);   	//type of PTE entry
	uint32_t ACC = getSlice32(PTE,4,2);   	//page access permissions
	uint8_t fault_type=0;   		//fault type
		
	//Compute fault-type	
	if(ET==0) fault_type=1; //PTE not found
	else if(ET==0x1 || ET==0x3) fault_type=4; //Invalid PTE
	else //check PTE permissions
	{
		switch(ACC)
		{
			case 0 : {
					 switch(AT)
					 {
						 case 2: case 3: case 4 : case 5 : case 6: case 7 : {fault_type = 2; break;} 
						 default : {fault_type=0; break;}
					 }
					 break;
				 }

			case 1 : {
					 switch(AT)
					 {
						 case 2: case 3: case 6: case 7 : {fault_type = 2; break;} 
						 default : {fault_type=0; break;}
					 }
					 break;
				 }

			case 2 : {
					 switch(AT)
					 {
						 case 4 : case 5 : case 6: case 7 : {fault_type = 2; break;} 
						 default : {fault_type=0; break;}
					 }
					 break;
				 }

			case 3 : {
					 {fault_type=0;}
					 break;
				 }


			case 4 : {
					 switch(AT)
					 {
						 case 0 : case 1: case 4 : case 5 : case 6: case 7 : {fault_type = 2; break;} 
						 default : {fault_type=0; break;}
					 }
					 break;
				 }

			case 5 : {
					 switch(AT)
					 {
						 case 2: case 3: case 4 : case 6: case 7 : {fault_type = 2; break;} 
						 default : {fault_type=0; break;}
					 }
					 break;
				 }

				
			case 6 : {
					 switch(AT)
					 {
						 case 5 : case 7 : {fault_type = 2; break;} 
						 case 0 : case 2 : case 4 : case 6 : {fault_type=3; break;} 								   
						 default : {fault_type=0; break;}
					 }
					 break;
				 }
			case 7 : {
					 switch(AT)
					 {
						 case 0 : case 2 : case 4 : case 6 : {fault_type=3; break;} 								   
						 default : {fault_type=0; break;}
					 }
					 break;
				 }
			default : fault_type = 0;
		}
	}
	return fault_type;
}


void updateFsrFar(MmuState* ms, uint32_t Fsr_val, uint32_t Far_val, uint8_t fault_class)
{
	//Overwrite (OW)=1 only if one IACCESS_FAULT tries to overwrite an existing IACCESS_FAULT
	//or a DACCESS_FAULT tries to overwrite another DACCESS_FAULT.
	if( ((ms->Mmu_FSR_FAULT_CLASS == IACCESS_FAULT) && (fault_class==IACCESS_FAULT)) 
	 || ((ms->Mmu_FSR_FAULT_CLASS == DACCESS_FAULT) && (fault_class==DACCESS_FAULT)) )
	{
		//set the OW bit
		Fsr_val = setBit32(Fsr_val,0,1);
	}
	else
	{	//clear the OW bit
		Fsr_val = setBit32(Fsr_val,0,0);
	}


	//The FSR/FAR registers can be updated if
	//the existing fault class was NOFAULT or IACCESS_FAULT.
	//A DACCESS_FAULT cannot be overwritten by an IACCESS_FAULT.
	if((ms->Mmu_FSR_FAULT_CLASS == NOFAULT) || (ms->Mmu_FSR_FAULT_CLASS==IACCESS_FAULT) || (fault_class==DACCESS_FAULT))
	{
		//Write the new fault status/addr
		ms->MmuFaultStatusRegister = Fsr_val;
		ms->MmuFaultAddressRegister = Far_val;
		ms->Mmu_FSR_FAULT_CLASS = fault_class;
#ifdef MMU_DEBUG
		fprintf(stderr,"Info: MmuFrontReq: Updated FSR=0x%x, FAR=0x%x\n", Fsr_val, Far_val);
#endif
	}
}


