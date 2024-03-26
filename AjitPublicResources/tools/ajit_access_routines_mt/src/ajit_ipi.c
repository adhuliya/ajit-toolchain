#include <stdlib.h>
#include <stdint.h>
#include <ajit_ipi.h>
#include <device_addresses.h>
#include <cortos.h>

#define DEBUG_IPI   0

IpiMessage* __ajit_get_ipi_message_pointer__ (uint32_t ipi_base_address,
							uint8_t dest_core_id, uint8_t dest_thread_id)
{
	uint32_t base_addr = ipi_base_address;
	uint32_t dest_tid = ((dest_core_id*2) + dest_thread_id);

	uint32_t ret_ptr  = (base_addr + 8 + (dest_tid*8));
	return ((IpiMessage*) ret_ptr);
}

// returns 0 on success.
//     If the interrupt mask & val are both already set, then return 1
//     
int __ajit_set_ipi_interrupt__ (uint32_t ipi_base_address,
					uint8_t source_core_id, uint8_t source_thread_id,
					uint8_t dest_core_id, uint8_t dest_thread_id,
						void* ptr)
					
{
	#if DEBUG_IPI
		cortos_printf("__ajit_set_ipi_interrupt__ (0x%x, %d, %d, %d, %d, 0x%x)\n",
					ipi_base_address, source_core_id, source_thread_id,
					dest_core_id, dest_thread_id, (uint32_t) ptr);
	#endif

	uint32_t base_addr = ipi_base_address;
	uint32_t dest_tid = ((dest_core_id*2) + dest_thread_id);

	IpiMessage* imesg = __ajit_get_ipi_message_pointer__ (ipi_base_address, dest_core_id, dest_thread_id);

	// active ipi mask.
	uint32_t active_ipi_mask = (1 << dest_tid);

	__ajit_acquire_ipi_lock__ (base_addr);

	uint32_t ipi_vals = *((uint32_t*) (base_addr + 4));
	uint32_t current_ipi_mask = *((uint32_t*) base_addr);

	// via vmap..
	imesg->source_core_id    = source_core_id;
	imesg->source_thread_id  = source_thread_id;
	imesg->dest_core_id      = dest_core_id;
	imesg->dest_thread_id    = dest_thread_id;
	imesg->pointer = ptr;

	__ajit_release_ipi_lock__ (base_addr);

	// if already set, return failure.
	if(ipi_vals & active_ipi_mask & current_ipi_mask)
	{
#if DEBUG_IPI
		cortos_printf("__ajit_set_ipi_interrupt__ already set\n");
#endif
		return (1);
	}

	ipi_vals = (ipi_vals & (~active_ipi_mask)) | active_ipi_mask;
	*((uint32_t*) (base_addr + 4)) = ipi_vals;

#if DEBUG_IPI
		cortos_printf("__ajit_set_ipi_interrupt__ freshly set (mask=0x%x, val=0x%x)\n",
					*((uint32_t*) base_addr),
					*((uint32_t*) (base_addr + 4))
			);
#endif

	return(0);
}

int __ajit_enable_ipi_interrupt__ (uint32_t ipi_base_address, uint8_t dest_core_id, uint8_t dest_thread_id)
{
	int bit_index = ((2*dest_core_id) + dest_thread_id);
	uint32_t m = (1 << bit_index);
	
	uint32_t curr_mask = *((uint32_t*) ipi_base_address);
	if(curr_mask & m)
		return(1);

	curr_mask = curr_mask | m;
	*((uint32_t*) ipi_base_address) = curr_mask;
}

int __ajit_disable_ipi_interrupt__ (uint32_t ipi_base_address, uint8_t dest_core_id, uint8_t dest_thread_id)
{
	int bit_index = ((2*dest_core_id) + dest_thread_id);
	uint32_t m = (1 << bit_index);
	
	uint32_t curr_mask = *((uint32_t*) ipi_base_address);
	if((curr_mask & m) == 0)
		return(1);

	curr_mask = curr_mask & (~m);
	*((uint32_t*) ipi_base_address) = curr_mask;

	return(0);
}

int __ajit_clear_ipi_interrupt__ (uint32_t ipi_base_address, uint8_t dest_core_id, uint8_t dest_thread_id)
{
	uint32_t base_addr = ipi_base_address;
	uint32_t dest_tid = ((dest_core_id*2) + dest_thread_id);

	uint32_t ipi_mask = (1 << dest_tid);

	__ajit_acquire_ipi_lock__ (base_addr);

	uint32_t ipi_vals = *((uint32_t*) (base_addr + 4));
	ipi_vals = (ipi_vals & (~ipi_mask));
	*((uint32_t*) (base_addr + 4)) = ipi_vals;

	__ajit_release_ipi_lock__ (base_addr);

	return(0);
}

void __ajit_set_ipi_mask_register__  (uint32_t ipi_base_address, uint32_t m)
{
	uint32_t base_addr = ipi_base_address;
	*((uint32_t*) base_addr) = m;
}

uint32_t __ajit_get_ipi_mask_register__ (uint32_t ipi_base_address)
{
	uint32_t base_addr = ipi_base_address;
	return (*((uint32_t*) base_addr));
}

void __ajit_set_ipi_value_register__  (uint32_t ipi_base_address, uint32_t m)
{
	uint32_t base_addr = ipi_base_address;
	*((uint32_t*) (base_addr+4)) = m;
}

uint32_t __ajit_get_ipi_value_register__ (uint32_t ipi_base_address)
{
	uint32_t base_addr = base_addr;
	return (*((uint32_t*) (base_addr + 4)));
}

			
void __ajit_read_ipi_info__ (uint32_t ipi_base_address,
					uint8_t dest_core_id, uint8_t dest_thread_id, uint32_t* mask, uint32_t* val,
					IpiMessage** mesg_ptr)
{
	uint32_t base_addr = ipi_base_address;
	uint32_t dest_tid = ((dest_core_id*2) + dest_thread_id);

	if(mesg_ptr != NULL)
	{
		*mesg_ptr         = (IpiMessage*) (base_addr + 8 + (dest_tid*8));
	}


	if(mask != NULL)
	{
		uint32_t ipi_mask = *((uint32_t*) base_addr);
		*mask = (ipi_mask >> dest_tid) & 0x1;
	}
	if(val != NULL)
	{
		uint32_t ipi_vals = *((uint32_t*) (base_addr + 4));
		*val  = (ipi_vals >> dest_tid) & 0x1;
	}
}

void  __ajit_acquire_ipi_lock__ (uint32_t ipi_base_address)
{
#if DEBUG_IPI
	cortos_printf("___ipi_try_to_lock___\n");
#endif
	acquire_mutex_using_swap(__AJIT_IPI_LOCK_ADDRESS(ipi_base_address));
#if DEBUG_IPI
	cortos_printf("___ipi_locked___\n");
#endif
	return;
}


void  __ajit_release_ipi_lock__ (uint32_t ipi_base_address)
{
#if DEBUG_IPI
	cortos_printf("___ipi_try_to_unlock___\n");
#endif
	*((uint32_t*) __AJIT_IPI_LOCK_ADDRESS(ipi_base_address)) = 0;
#if DEBUG_IPI
	cortos_printf("___ipi_unlocked___\n");
#endif
}


void __ajit_ipi_init__ (uint32_t ipi_base_address)
{

	uint32_t addr;
	*((uint32_t*) ipi_base_address) = 0;	
	*((uint32_t*) (ipi_base_address + 4)) = 0;	
	*((uint32_t*) __AJIT_IPI_LOCK_ADDRESS(ipi_base_address)) = 0;
}


