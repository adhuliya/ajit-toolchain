#ifndef ajit_ncram__
#define ajit_ncram__

#define AJIT_PAGE_SIZE  4096
#define BUFFER_SIZE 	2048

typedef struct __ncramAllocator {
	uint32_t va_base;
	uint32_t number_of_buffers;
	uint64_t pa_base;


	uint8_t* free_status;
	uint32_t c_lock;
} ncramAllocator;

// ncram is non-cacheable RAM which provides non-cacheable
// shared memory buffers for I/O devices and the processor
// threads to exchange information.    I/O devices can 
// write into this memory by DMA, and the processor can
// then read from the memory etc.

// allocation will be 1 buffer at a time, with a fixed
// buffer-size of 2048 bytes.

// Note that the allocator needs to know the virtual address
// of the region (used by software) as well as the physical
// address of the region (used by the high speed I/O devices
// such as a NIC).
//
// Arguments:
//   v_page_pbase : The base page address (ie bits 31:12) of the VA 
//   p_page_base  : The base page address (ie bits 36:12) of the PA
//   number_of_buffers: size of region in multiples of 2KB.
void ajit_ncram_allocator_init (uint32_t v_page_base, uint32_t p_page_base, uint32_t number_of_buffers);

// return 0 on success, 1 on failure. 
//    returns the va and pa of the allocated buffer.
// Arguments:
//    *va : return pointer to keep base virtual address of allocated buffer.
//    *pa : return pointer to keep base physical address of allocated buffer.
int ajit_ncram_allocate_buffer(uint32_t* va, uint64_t* pa);

// deallocate buffer.
// Arguments:
//    va: base virtual address of the buffer to be de-allocated.
void ajit_ncram_deallocate_buffer(uint32_t va);

#endif
