#include <stdlib.h>
#include <stdint.h>
#include <ajit_ipi.h>
#include <device_addresses.h>

IpiMessage* __ajit_get_ipi_message_pointer__ (uint8_t dest_core_id, uint8_t dest_thread_id)
{
	uint32_t base_addr = ADDR_INTERRUPT_CONTROLLER_IPI_BASE;
	uint32_t dest_tid = ((dest_core_id*2) + dest_thread_id);

	uint32_t ret_ptr  = (base_addr + 8 + (dest_tid*8));
	return ((IpiMessage*) ret_ptr);
}

void __ajit_set_ipi_interrupt__ (uint8_t source_core_id, uint8_t source_thread_id,
					uint8_t dest_core_id, uint8_t dest_thread_id,
						void* ptr)
					
{
	uint32_t base_addr = ADDR_INTERRUPT_CONTROLLER_IPI_BASE;
	uint32_t dest_tid = ((dest_core_id*2) + dest_thread_id);

	IpiMessage* imesg = __ajit_get_ipi_message_pointer__ (dest_core_id, dest_thread_id);

	// via vmap..
	imesg->source_core_id    = source_core_id;
	imesg->source_thread_id  = source_thread_id;
	imesg->dest_core_id      = dest_core_id;
	imesg->dest_thread_id    = dest_thread_id;
	imesg->pointer = ptr;

	cortos_printf("set-ipi-interrupt: imesg->pointer = 0x%x\n", (uint32_t) imesg->pointer);
	
	// update ipi_vals read modify write.
	uint32_t ipi_mask = (1 << dest_tid);
	uint32_t ipi_vals = *((uint32_t*) (base_addr + 4));
	ipi_vals = (ipi_vals & (~ipi_mask)) | ipi_mask;
	*((uint32_t*) (base_addr + 4)) = ipi_vals;
}

void __ajit_clear_ipi_interrupt__ (uint8_t dest_core_id, uint8_t dest_thread_id)
{
	uint32_t base_addr = ADDR_INTERRUPT_CONTROLLER_IPI_BASE;
	uint32_t dest_tid = ((dest_core_id*2) + dest_thread_id);

	uint32_t ipi_mask = (1 << dest_tid);
	uint32_t ipi_vals = *((uint32_t*) (base_addr + 4));

	ipi_vals = (ipi_vals & (~ipi_mask));
	*((uint32_t*) (base_addr + 4)) = ipi_vals;
}

void __ajit_set_ipi_mask_register__  (uint32_t m)
{
	uint32_t base_addr = ADDR_INTERRUPT_CONTROLLER_IPI_BASE;
	*((uint32_t*) base_addr) = m;
}

uint32_t __ajit_get_ipi_mask_register__ ()
{
	uint32_t base_addr = ADDR_INTERRUPT_CONTROLLER_IPI_BASE;
	return (*((uint32_t*) base_addr));
}

void __ajit_set_ipi_value_register__  (uint32_t m)
{
	uint32_t base_addr = ADDR_INTERRUPT_CONTROLLER_IPI_BASE;
	*((uint32_t*) (base_addr+4)) = m;
}

uint32_t __ajit_get_ipi_value_register__ ()
{
	uint32_t base_addr = ADDR_INTERRUPT_CONTROLLER_IPI_BASE;
	return (*((uint32_t*) (base_addr + 4)));
}

			
void __ajit_read_ipi_info__ (uint8_t dest_core_id, uint8_t dest_thread_id, uint32_t* mask, uint32_t* val,
					IpiMessage** mesg_ptr)
{
	uint32_t base_addr = ADDR_INTERRUPT_CONTROLLER_IPI_BASE;
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

