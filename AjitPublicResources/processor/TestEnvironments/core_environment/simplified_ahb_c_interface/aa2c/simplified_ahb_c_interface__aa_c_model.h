#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <BitVectors.h>
#include <pipeHandler.h>
void            simplified_ahb_c_interface___set_trace_file(FILE * fp);
// object initialization 
void            simplified_ahb_c_interface____init_aa_globals__();
void           
simplified_ahb_c_interface__get_simplified_ahb_command(uint8_t use_socket_flag,
							uint8_t *,
						       uint8_t *,
						       uint64_t *,
						       uint32_t *);
void           
_simplified_ahb_c_interface__get_simplified_ahb_command_(uint8_t use_socket_flag, 
							     bit_vector *,
							 bit_vector *,
							 bit_vector *,
							 bit_vector *);

#define simplified_ahb_c_interface___get_simplified_ahb_command_inner_inarg_prep_macro__ __declare_static_bit_vector(rw,8);\
__declare_static_bit_vector(transfer_size,8);\
__declare_static_bit_vector(byte_address,64);\
__declare_static_bit_vector(write_data,32);\
__declare_static_bit_vector(command,73);\
__declare_static_bit_vector(lock_bus_1,1);\
__declare_static_bit_vector(rw_1,1);\
__declare_static_bit_vector(transfer_size_1,3);\
__declare_static_bit_vector(addr_36,36);\

#define simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_16_c_macro_ __declare_static_bit_vector(RPIPE_AFB_TO_AHB_COMMAND_15,73);\
if (use_socket_flag) sock_read_bit_vector_from_pipe("AFB_TO_AHB_COMMAND",&(RPIPE_AFB_TO_AHB_COMMAND_15));\
else read_bit_vector_from_pipe("AFB_TO_AHB_COMMAND",&(RPIPE_AFB_TO_AHB_COMMAND_15));\
bit_vector_cast_to_bit_vector(0, &(command), &(RPIPE_AFB_TO_AHB_COMMAND_15));\
;

#define simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_21_c_macro_ __declare_static_bit_vector(slice_20,1);\
bit_vector_slice(&(command), &(slice_20), 72);\
bit_vector_cast_to_bit_vector(0, &(lock_bus_1), &(slice_20));\
;

#define simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_25_c_macro_ __declare_static_bit_vector(slice_24,1);\
bit_vector_slice(&(command), &(slice_24), 71);\
bit_vector_cast_to_bit_vector(0, &(rw_1), &(slice_24));\
;

#define simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_30_c_macro_ __declare_static_bit_vector(slice_29,3);\
bit_vector_slice(&(command), &(slice_29), 68);\
bit_vector_cast_to_bit_vector(0, &(transfer_size_1), &(slice_29));\
;

#define simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_35_c_macro_ __declare_static_bit_vector(slice_34,36);\
bit_vector_slice(&(command), &(slice_34), 32);\
bit_vector_cast_to_bit_vector(0, &(addr_36), &(slice_34));\
;

#define simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_39_c_macro_ __declare_static_bit_vector(slice_38,32);\
bit_vector_slice(&(command), &(slice_38), 0);\
bit_vector_cast_to_bit_vector(0, &(write_data), &(slice_38));\
;

#define simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_43_c_macro_ __declare_static_bit_vector(type_cast_42,8);\
bit_vector_bitcast_to_bit_vector( &(type_cast_42), &(rw_1));\
bit_vector_cast_to_bit_vector(0, &(rw), &(type_cast_42));\
;

#define simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_47_c_macro_ __declare_static_bit_vector(type_cast_46,8);\
bit_vector_bitcast_to_bit_vector( &(type_cast_46), &(transfer_size_1));\
bit_vector_cast_to_bit_vector(0, &(transfer_size), &(type_cast_46));\
;

#define simplified_ahb_c_interface___simplified_ahb_c_interface__get_simplified_ahb_command_assign_stmt_51_c_macro_ __declare_static_bit_vector(type_cast_50,64);\
bit_vector_bitcast_to_bit_vector( &(type_cast_50), &(addr_36));\
bit_vector_cast_to_bit_vector(0, &(byte_address), &(type_cast_50));\
;

#define simplified_ahb_c_interface___get_simplified_ahb_command_inner_outarg_prep_macro__ bit_vector_cast_to_bit_vector(0, &((*__prw)), &(rw));\
bit_vector_cast_to_bit_vector(0, &((*__ptransfer_size)), &(transfer_size));\
bit_vector_cast_to_bit_vector(0, &((*__pbyte_address)), &(byte_address));\
bit_vector_cast_to_bit_vector(0, &((*__pwrite_data)), &(write_data));\
;

#define simplified_ahb_c_interface___get_simplified_ahb_command_outer_arg_decl_macro__ __declare_bit_vector(__rw, 8);\
__declare_bit_vector(__transfer_size, 8);\
__declare_bit_vector(__byte_address, 64);\
__declare_bit_vector(__write_data, 32);\
;

#define simplified_ahb_c_interface___get_simplified_ahb_command_outer_op_xfer_macro__  *rw =  bit_vector_to_uint64(0, &__rw);\
 *transfer_size =  bit_vector_to_uint64(0, &__transfer_size);\
 *byte_address =  bit_vector_to_uint64(0, &__byte_address);\
 *write_data =  bit_vector_to_uint64(0, &__write_data);\
;
void            simplified_ahb_c_interface__global_storage_initializer_();
void           
_simplified_ahb_c_interface__global_storage_initializer__();

#define simplified_ahb_c_interface___global_storage_initializer__inner_inarg_prep_macro__
#define simplified_ahb_c_interface___global_storage_initializer__inner_outarg_prep_macro__ ;

#define simplified_ahb_c_interface___global_storage_initializer__outer_arg_decl_macro__ ;

#define simplified_ahb_c_interface___global_storage_initializer__outer_op_xfer_macro__ ;
void            simplified_ahb_c_interface__mem_load__(uint32_t,
						       uint8_t *);
void            _simplified_ahb_c_interface__mem_load___(bit_vector *,
							 bit_vector *);

#define simplified_ahb_c_interface___mem_load___inner_inarg_prep_macro__ __declare_static_bit_vector(address,32);\
bit_vector_cast_to_bit_vector(0, &(address), &((*__paddress)));\
__declare_static_bit_vector(data,8);\

#define simplified_ahb_c_interface___simplified_ahb_c_interface__mem_load___assign_stmt_66_c_macro_ __declare_static_bit_vector(konst_61,32);\
bit_vector_clear(&konst_61);\
konst_61.val.byte_array[0] = 1;\
__declare_static_bit_vector(MUL_u32_u32_62,32);\
__declare_static_bit_vector(konst_63,32);\
bit_vector_clear(&konst_63);\
__declare_static_bit_vector(ADD_u32_u32_64,32);\
bit_vector_clear(&konst_61);\
konst_61.val.byte_array[0] = 1;\
bit_vector_mul( &(address), &(konst_61), &(MUL_u32_u32_62));\
bit_vector_clear(&konst_63);\
bit_vector_plus( &(MUL_u32_u32_62), &(konst_63), &(ADD_u32_u32_64));\
bit_vector_cast_to_bit_vector(0, &(data), &((default_mem_pool[bit_vector_to_uint64(0, &ADD_u32_u32_64)])));\
;

#define simplified_ahb_c_interface___mem_load___inner_outarg_prep_macro__ bit_vector_cast_to_bit_vector(0, &((*__pdata)), &(data));\
;

#define simplified_ahb_c_interface___mem_load___outer_arg_decl_macro__ __declare_bit_vector(__address, 32);\
bit_vector_assign_uint64(0, &__address, address);\
__declare_bit_vector(__data, 8);\
;

#define simplified_ahb_c_interface___mem_load___outer_op_xfer_macro__  *data =  bit_vector_to_uint64(0, &__data);\
;
void            simplified_ahb_c_interface__mem_store__(uint32_t, uint8_t);
void            _simplified_ahb_c_interface__mem_store___(bit_vector *,
							  bit_vector *);

#define simplified_ahb_c_interface___mem_store___inner_inarg_prep_macro__ __declare_static_bit_vector(address,32);\
bit_vector_cast_to_bit_vector(0, &(address), &((*__paddress)));\
__declare_static_bit_vector(data,8);\
bit_vector_cast_to_bit_vector(0, &(data), &((*__pdata)));\

#define simplified_ahb_c_interface___simplified_ahb_c_interface__mem_store___assign_stmt_78_c_macro_ __declare_static_bit_vector(konst_72,32);\
bit_vector_clear(&konst_72);\
konst_72.val.byte_array[0] = 1;\
__declare_static_bit_vector(MUL_u32_u32_73,32);\
__declare_static_bit_vector(konst_74,32);\
bit_vector_clear(&konst_74);\
__declare_static_bit_vector(ADD_u32_u32_75,32);\
bit_vector_cast_to_bit_vector(0, &((default_mem_pool[bit_vector_to_uint64(0, &ADD_u32_u32_75)])), &(data));\
;

#define simplified_ahb_c_interface___mem_store___inner_outarg_prep_macro__ ;

#define simplified_ahb_c_interface___mem_store___outer_arg_decl_macro__ __declare_bit_vector(__address, 32);\
bit_vector_assign_uint64(0, &__address, address);\
__declare_bit_vector(__data, 8);\
bit_vector_assign_uint64(0, &__data, data);\
;

#define simplified_ahb_c_interface___mem_store___outer_op_xfer_macro__ ;
void           
simplified_ahb_c_interface__send_simplified_ahb_response(uint8_t use_socket_flag,
							uint8_t,
							 uint32_t);
void           
_simplified_ahb_c_interface__send_simplified_ahb_response_(uint8_t use_socket_flag,
								bit_vector *,
							   	bit_vector *);

#define simplified_ahb_c_interface___send_simplified_ahb_response_inner_inarg_prep_macro__ __declare_static_bit_vector(err,8);\
bit_vector_cast_to_bit_vector(0, &(err), &((*__perr)));\
__declare_static_bit_vector(read_data,32);\
bit_vector_cast_to_bit_vector(0, &(read_data), &((*__pread_data)));\
__declare_static_bit_vector(to_pipe,33);\

#define simplified_ahb_c_interface___simplified_ahb_c_interface__send_simplified_ahb_response_assign_stmt_93_c_macro_ __declare_static_bit_vector(konst_85,8);\
bit_vector_clear(&konst_85);\
__declare_static_bit_vector(NEQ_u8_u1_86,1);\
__declare_static_bit_vector(konst_87,1);\
bit_vector_clear(&konst_87);\
konst_87.val.byte_array[0] = 1;\
__declare_static_bit_vector(type_cast_88,1);\
bit_vector_clear(&type_cast_88);\
type_cast_88.val.byte_array[0] = 1;\
__declare_static_bit_vector(konst_89,1);\
bit_vector_clear(&konst_89);\
__declare_static_bit_vector(MUX_90,1);\
__declare_static_bit_vector(CONCAT_u1_u33_92,33);\
bit_vector_clear(&konst_85);\
bit_vector_not_equal(0, &(err), &(konst_85), &NEQ_u8_u1_86);\
if (has_undefined_bit(&NEQ_u8_u1_86)) {fprintf(stderr, "Error: variable NEQ_u8_u1_86 has undefined value (%s) at test point.\n", to_string(&NEQ_u8_u1_86));assert(0);} \
bit_vector_clear(&konst_87);\
konst_87.val.byte_array[0] = 1;\
bit_vector_bitcast_to_bit_vector( &(type_cast_88), &(konst_87));\
bit_vector_clear(&konst_89);\
if(bit_vector_to_uint64(0, &NEQ_u8_u1_86)){\
bit_vector_cast_to_bit_vector(0, &(MUX_90), &(type_cast_88));\
}\
else\
{\
bit_vector_cast_to_bit_vector(0, &(MUX_90), &(konst_89));\
}\
bit_vector_concatenate( &(MUX_90), &(read_data), &(CONCAT_u1_u33_92));\
bit_vector_cast_to_bit_vector(0, &(to_pipe), &(CONCAT_u1_u33_92));\
;

#define simplified_ahb_c_interface___simplified_ahb_c_interface__send_simplified_ahb_response_assign_stmt_96_c_macro_ if (use_socket_flag) sock_write_bit_vector_to_pipe("AHB_TO_AFB_RESPONSE",&(to_pipe));\
 else write_bit_vector_to_pipe("AHB_TO_AFB_RESPONSE",&(to_pipe));\
;

#define simplified_ahb_c_interface___send_simplified_ahb_response_inner_outarg_prep_macro__ ;

#define simplified_ahb_c_interface___send_simplified_ahb_response_outer_arg_decl_macro__ __declare_bit_vector(__err, 8);\
bit_vector_assign_uint64(0, &__err, err);\
__declare_bit_vector(__read_data, 32);\
bit_vector_assign_uint64(0, &__read_data, read_data);\
;

#define simplified_ahb_c_interface___send_simplified_ahb_response_outer_op_xfer_macro__ ;
void            simplified_ahb_c_interface__start_daemons(FILE * fp,
							  int trace_on);
void            simplified_ahb_c_interface__stop_daemons();
