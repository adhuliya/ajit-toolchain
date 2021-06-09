#include <pthread.h>
#include <pthreadUtils.h>
#include <Pipes.h>
#include <simplified_ahb_c_interface__aa_c_model.h>
FILE           *simplified_ahb_c_interface____report_log_file__ = NULL;
int             simplified_ahb_c_interface____trace_on__ = 0;
void
simplified_ahb_c_interface___set_trace_file(FILE * fp)
{
    simplified_ahb_c_interface____report_log_file__ = fp;
}
bit_vector      default_mem_pool[1];
void
simplified_ahb_c_interface____init_aa_globals__()
{
    register_pipe("AFB_TO_AHB_COMMAND", 20, 8, 0);
    register_pipe("AHB_TO_AFB_RESPONSE", 10, 8, 0);
    init_static_bit_vector(&(default_mem_pool[0]), 8);
}
void
_simplified_ahb_c_interface__get_simplified_ahb_command_(uint8_t use_socket_flag,
							bit_vector *
							 __prw,
							 bit_vector *
							 __ptransfer_size,
							 bit_vector *
							 __pbyte_address,
							 bit_vector *
							 __pwrite_data)
{
    MUTEX_DECL
	(simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_series_block_stmt_7_c_mutex_);
    MUTEX_LOCK
	(simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_series_block_stmt_7_c_mutex_);
    simplified_ahb_c_interface___get_simplified_ahb_command_inner_inarg_prep_macro__;
    // command := AFB_TO_AHB_COMMAND
    simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_16_c_macro_;
    // lock_bus_1 := ( $slice command 72 72 ) 
    simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_21_c_macro_;
    // rw_1 := ( $slice command 71 71 ) 
    simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_25_c_macro_;
    // transfer_size_1 := ( $slice command 70 68 ) 
    simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_30_c_macro_;
    // addr_36 := ( $slice command 67 32 ) 
    simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_35_c_macro_;
    // write_data := ( $slice command 31 0 ) 
    simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_39_c_macro_;
    // rw := ($bitcast ($uint<8>) rw_1 )
    simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_43_c_macro_;
    // transfer_size := ($bitcast ($uint<8>) transfer_size_1 )
    simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_47_c_macro_;
    // byte_address := ($bitcast ($uint<64>) addr_36 )
    simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_51_c_macro_;
    simplified_ahb_c_interface___get_simplified_ahb_command_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_series_block_stmt_7_c_mutex_);
}
void
simplified_ahb_c_interface__get_simplified_ahb_command(uint8_t use_socket_flag,
						       uint8_t * rw,
						       uint8_t *
						       transfer_size,
						       uint64_t *
						       byte_address,
						       uint32_t *
						       write_data)
{
    simplified_ahb_c_interface___get_simplified_ahb_command_outer_arg_decl_macro__;
    _simplified_ahb_c_interface__get_simplified_ahb_command_(use_socket_flag, 
							     &__rw,
							     &__transfer_size,
							     &__byte_address,
							     &__write_data);
    simplified_ahb_c_interface___get_simplified_ahb_command_outer_op_xfer_macro__;
}


void
_simplified_ahb_c_interface__global_storage_initializer__()
{
    MUTEX_DECL
	(simplified_ahb_c_interface___simplified_ahb_c_interface__global_storage_initializer__series_block_stmt_53_c_mutex_);
    MUTEX_LOCK
	(simplified_ahb_c_interface___simplified_ahb_c_interface__global_storage_initializer__series_block_stmt_53_c_mutex_);
    simplified_ahb_c_interface___global_storage_initializer__inner_inarg_prep_macro__;
    /*
     * null 
     */ ;
    simplified_ahb_c_interface___global_storage_initializer__inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(simplified_ahb_c_interface___simplified_ahb_c_interface__global_storage_initializer__series_block_stmt_53_c_mutex_);
}
void
simplified_ahb_c_interface__global_storage_initializer_()
{
    simplified_ahb_c_interface___global_storage_initializer__outer_arg_decl_macro__;
    _simplified_ahb_c_interface__global_storage_initializer__();
    simplified_ahb_c_interface___global_storage_initializer__outer_op_xfer_macro__;
}


void
_simplified_ahb_c_interface__mem_load___(bit_vector * __paddress,
					 bit_vector * __pdata)
{
    MUTEX_DECL
	(simplified_ahb_c_interface___simplified_ahb_c_interface__mem_load___series_block_stmt_56_c_mutex_);
    MUTEX_LOCK
	(simplified_ahb_c_interface___simplified_ahb_c_interface__mem_load___series_block_stmt_56_c_mutex_);
    simplified_ahb_c_interface___mem_load___inner_inarg_prep_macro__;
    // data := default_mem_pool[((address * 1 ) + 0 )]
    simplified_ahb_c_interface___simplified_ahb_c_interface__mem_load___assign_stmt_66_c_macro_;
    simplified_ahb_c_interface___mem_load___inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(simplified_ahb_c_interface___simplified_ahb_c_interface__mem_load___series_block_stmt_56_c_mutex_);
}
void
simplified_ahb_c_interface__mem_load__(uint32_t address, uint8_t * data)
{
    simplified_ahb_c_interface___mem_load___outer_arg_decl_macro__;
    _simplified_ahb_c_interface__mem_load___(&__address, &__data);
    simplified_ahb_c_interface___mem_load___outer_op_xfer_macro__;
}


void
_simplified_ahb_c_interface__mem_store___(bit_vector * __paddress,
					  bit_vector * __pdata)
{
    MUTEX_DECL
	(simplified_ahb_c_interface___simplified_ahb_c_interface__mem_store___series_block_stmt_68_c_mutex_);
    MUTEX_LOCK
	(simplified_ahb_c_interface___simplified_ahb_c_interface__mem_store___series_block_stmt_68_c_mutex_);
    simplified_ahb_c_interface___mem_store___inner_inarg_prep_macro__;
    // default_mem_pool[((address * 1 ) + 0 )] := data
    simplified_ahb_c_interface___simplified_ahb_c_interface__mem_store___assign_stmt_78_c_macro_;
    simplified_ahb_c_interface___mem_store___inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(simplified_ahb_c_interface___simplified_ahb_c_interface__mem_store___series_block_stmt_68_c_mutex_);
}
void
simplified_ahb_c_interface__mem_store__(uint32_t address, uint8_t data)
{
    simplified_ahb_c_interface___mem_store___outer_arg_decl_macro__;
    _simplified_ahb_c_interface__mem_store___(&__address, &__data);
    simplified_ahb_c_interface___mem_store___outer_op_xfer_macro__;
}


void
_simplified_ahb_c_interface__send_simplified_ahb_response_(uint8_t use_socket_flag,
								bit_vector *
							   	__perr,
							   	bit_vector *
							   	__pread_data)
{
    MUTEX_DECL
	(simplified_ahb_c_interface___simplified_ahb_c_interface__send_simplified_ahb_response_series_block_stmt_80_c_mutex_);
    MUTEX_LOCK
	(simplified_ahb_c_interface___simplified_ahb_c_interface__send_simplified_ahb_response_series_block_stmt_80_c_mutex_);
    simplified_ahb_c_interface___send_simplified_ahb_response_inner_inarg_prep_macro__;
    // to_pipe := (( $mux (err != 0 ) ($bitcast ($uint<1>) 1 ) 0 ) &&
    // read_data)
    simplified_ahb_c_interface___simplified_ahb_c_interface__send_simplified_ahb_response_assign_stmt_93_c_macro_;
    // AHB_TO_AFB_RESPONSE := to_pipe
    simplified_ahb_c_interface___simplified_ahb_c_interface__send_simplified_ahb_response_assign_stmt_96_c_macro_;
    simplified_ahb_c_interface___send_simplified_ahb_response_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(simplified_ahb_c_interface___simplified_ahb_c_interface__send_simplified_ahb_response_series_block_stmt_80_c_mutex_);
}
void
simplified_ahb_c_interface__send_simplified_ahb_response(uint8_t use_socket_flag,
							uint8_t err,
							 uint32_t
							 read_data)
{
    simplified_ahb_c_interface___send_simplified_ahb_response_outer_arg_decl_macro__;
    _simplified_ahb_c_interface__send_simplified_ahb_response_(use_socket_flag,
								&__err,
							       	&__read_data);
    simplified_ahb_c_interface___send_simplified_ahb_response_outer_op_xfer_macro__;
}


void
simplified_ahb_c_interface__start_daemons(FILE * fp, int trace_on)
{
    simplified_ahb_c_interface____report_log_file__ = fp;
    simplified_ahb_c_interface____trace_on__ = trace_on;
    simplified_ahb_c_interface____init_aa_globals__();
}
void
simplified_ahb_c_interface__stop_daemons()
{
}
