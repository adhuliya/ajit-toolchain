#ifndef ajit_ipi_h___
#define ajit_ipi_h___

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
void __ajit_set_ipi_interrupt__ (uint8_t source_core_id, uint8_t source_thread_id,
					uint8_t dest_core_id, uint8_t dest_thread_id,
						void* ptr);

//
// Clear the IPI interrupt for (dest_core_id, dest_thread_id)
//
void __ajit_clear_ipi_interrupt__ (uint8_t dest_core_id, uint8_t dest_thread_id);

//
// Read the IPI related information for (dest_core_id, dest_thread_id)
//
void __ajit_read_ipi_info__ (uint8_t dest_core_id, 
					uint8_t dest_thread_id, 
					uint32_t* mask,  // bottom-bit has ipi mask for thread.
					uint32_t* val,   // bottom-bit has ipi value for thread.
					IpiMessage** mesg_ptr // pointer to ipi message
				);

// utility functions.
void __ajit_set_ipi_mask_register__  (uint32_t m);
uint32_t __ajit_get_ipi_mask_register__ ();

void __ajit_set_ipi_value_register__  (uint32_t m);
uint32_t __ajit_get_ipi_value_register__ ();

IpiMessage* __ajit_get_ipi_message_pointer__ (uint8_t dest_core_id, uint8_t dest_thread_id);




#endif
