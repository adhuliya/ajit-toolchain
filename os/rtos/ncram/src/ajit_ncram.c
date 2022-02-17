#include <stdint.h>
#include <stdio.h>
#include <cortos.h>
#include <ajit_ncram.h>

ncramAllocator ncram_allocator;

// The base page address (ie bits 31:12) of the VA 
// and the base page address (ie bits 36:12) of the PA
// are supplied to the allocator.
void ajit_ncram_allocator_init (uint32_t v_page_base, uint32_t p_page_base, 
					uint32_t number_of_buffers);
{
	ncram_allocator.va_base = (v_page_base << 12);
	ncram_allocator.pa_base = ((uint64_t) p_page_base) << 12;	

	ncram_allocator.number_of_buffers = number_of_buffers;
	ncram_allocator.free_status = cortos_bget(number_of_buffers);

	ncram_allocator.c_lock = cortos_reserveLockVar();

	int I;
	for(I = 0; I < number_of_buffers; I++)
		ncram_allocator.free_status[I] = 1;
}

// return 0 on success, 1 on failure. 
//    returns the va and pa of the allocated buffer.
int ajit_ncram_allocate_buffer(uint32_t* va, uint64_t* pa)
{
	cortos_lock_acquire_buzy(ncram_allocator.c_lock);

	int I;
	int ret_val = 1;

	*va = ncram_allocator.va_base;
	*pa = ncram_allocator.pa_base;

	for(I = 0; I < ncram_allocator.number_of_buffers; I++)
	{
		if(ncram_allocator.free_status[I])
		{
			ret_val  = 0;
			ncram_allocator.free_status[I] = 0;
			break;
		}
		*va += BUFFER_SIZE;
		*pa += BUFFER_SIZE;
	}

	cortos_lock_release(ncram_allocator.c_lock);
	return(ret_val);
}

// deallocate
void ajit_ncram_deallocate_buffer(uint32_t va)
{
	cortos_lock_acquire_buzy(ncram_allocator.c_lock);
	if((va > ncram_allocator.va_base) && ((va & (BUFFER_SIZE-1)) == 0))
	{
		int I = (va - ncram_allocator.va_base)/BUFFER_SIZE;
		if(I < ncram_allocator.number_of_buffers)
		{
			ncram_allocator.free_status[I] = 1;
		}
	}
	cortos_lock_release(ncram_allocator.c_lock);
}
