#ifndef ajit_ipi_h___
#define ajit_ipi_h___

#define __AJIT_IPI_LOCK_ADDRESS(x) (x+72)

typedef struct __IpiMessage {
	uint8_t source_core_id;
	uint8_t source_thread_id;
	uint8_t dest_core_id;
	uint8_t dest_thread_id;
	void    *pointer;
} IpiMessage;



//
// Set the IPI interrupt for (dest_core_id, dest_thread_id) from
// (source_core_id, source_thread_id).
//
// returns 0 on success, non-zero on failure.  
//    note: failure means that there is already an ipi interrupt set for
//          the destination thread.
int __ajit_set_ipi_interrupt__ (uint32_t ipi_base_address,
					uint8_t source_core_id, uint8_t source_thread_id,
					uint8_t dest_core_id, uint8_t dest_thread_id,
					void* ptr);

//
// Clear the IPI interrupt for (dest_core_id, dest_thread_id)
//
// returns 0 on success, non-zero on failure.
//    note: failure here means the destination ipi interrupt was not enabled.
int __ajit_clear_ipi_interrupt__ (uint32_t ipi_base_address,
					uint8_t dest_core_id, uint8_t dest_thread_id);

//
// Read the IPI related information for (dest_core_id, dest_thread_id)
//
void __ajit_read_ipi_info__ (uint32_t ipi_base_address,
					uint8_t dest_core_id, 
					uint8_t dest_thread_id, 
					uint32_t* mask,  // bottom-bit has ipi mask for thread.
					uint32_t* val,   // bottom-bit has ipi value for thread.
					IpiMessage** mesg_ptr // pointer to ipi message
				);

// return 0 if interrupt enabled in this call, 1 if already enabled earlier.
int __ajit_enable_ipi_interrupt__ (uint32_t ipi_base_address,
					uint8_t dest_core_id, uint8_t dest_thread_id);

// return 0 if interrupt disabled in this call, 1 if already disabled earlier.
int __ajit_disable_ipi_interrupt__ (uint32_t ipi_base_address,
					uint8_t dest_core_id, uint8_t dest_thread_id);

// utility functions.
void __ajit_set_ipi_mask_register__  (uint32_t ipi_base_address, uint32_t m);
uint32_t __ajit_get_ipi_mask_register__ (uint32_t ipi_base_address);

void __ajit_set_ipi_value_register__  (uint32_t ipi_base_address, uint32_t m);
uint32_t __ajit_get_ipi_value_register__ (uint32_t ipi_base_address);

IpiMessage* __ajit_get_ipi_message_pointer__ (uint32_t ipi_base_address,
						uint8_t dest_core_id, uint8_t dest_thread_id);


	
// acquire release lock using swap.
void  __ajit_acquire_ipi_lock__ (uint32_t ipi_base_address);
void  __ajit_release_ipi_lock__ (uint32_t ipi_base_address);

// Initialize the IPI interrupt controller (zero out everything)
void __ajit_ipi_init__ (uint32_t ipi_base_address);

#endif
