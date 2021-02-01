#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <BitVectors.h>
#include <pipeHandler.h>
void            cache_c_interface___set_trace_file(FILE * fp);
// object initialization 
void            cache_c_interface____init_aa_globals__();
void            cache_c_interface__dcache_interface_daemon();
void            _cache_c_interface__dcache_interface_daemon_();

#define cache_c_interface___dcache_interface_daemon_inner_inarg_prep_macro__
#define cache_c_interface___cache_c_interface__dcache_interface_daemon_branch_block_stmt_520_c_export_decl_macro_ __declare_static_bit_vector(req_type,8);\
__declare_static_bit_vector(asi,8);\
__declare_static_bit_vector(byte_mask,8);\
__declare_static_bit_vector(addr,32);\
__declare_static_bit_vector(wdata,64);\
__declare_static_bit_vector(rsp,72);\
__declare_static_bit_vector(mae,8);\
__declare_static_bit_vector(rdata,64);\


#define cache_c_interface___cache_c_interface__dcache_interface_daemon_merge_stmt_521_c_preamble_macro_ uint8_t merge_stmt_521_entry_flag;\
merge_stmt_521_entry_flag = 1;\
uint8_t loopback_520_flag = 0;\
goto merge_stmt_521_run;\
loopback_520: loopback_520_flag = 1;\
goto merge_stmt_521_run;\
merge_stmt_521_run: ;\
;

#define cache_c_interface___cache_c_interface__dcache_interface_daemon_merge_stmt_521_c_postamble_macro_ loopback_520_flag = 0;\
merge_stmt_521_entry_flag = 0;

#define cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_524_c_macro_ __declare_static_bit_vector(RPIPE_CPU_to_DCACHE_request_type_523,8);\
read_bit_vector_from_pipe("CPU_to_DCACHE_request_type",&(RPIPE_CPU_to_DCACHE_request_type_523));\
bit_vector_cast_to_bit_vector(0, &(req_type), &(RPIPE_CPU_to_DCACHE_request_type_523));\
;

#define cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_527_c_macro_ __declare_static_bit_vector(RPIPE_CPU_to_DCACHE_asi_526,8);\
read_bit_vector_from_pipe("CPU_to_DCACHE_asi",&(RPIPE_CPU_to_DCACHE_asi_526));\
bit_vector_cast_to_bit_vector(0, &(asi), &(RPIPE_CPU_to_DCACHE_asi_526));\
;

#define cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_530_c_macro_ __declare_static_bit_vector(RPIPE_CPU_to_DCACHE_byte_mask_529,8);\
read_bit_vector_from_pipe("CPU_to_DCACHE_byte_mask",&(RPIPE_CPU_to_DCACHE_byte_mask_529));\
bit_vector_cast_to_bit_vector(0, &(byte_mask), &(RPIPE_CPU_to_DCACHE_byte_mask_529));\
;

#define cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_533_c_macro_ __declare_static_bit_vector(RPIPE_CPU_to_DCACHE_addr_532,32);\
read_bit_vector_from_pipe("CPU_to_DCACHE_addr",&(RPIPE_CPU_to_DCACHE_addr_532));\
bit_vector_cast_to_bit_vector(0, &(addr), &(RPIPE_CPU_to_DCACHE_addr_532));\
;

#define cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_536_c_macro_ __declare_static_bit_vector(RPIPE_CPU_to_DCACHE_data_535,64);\
read_bit_vector_from_pipe("CPU_to_DCACHE_data",&(RPIPE_CPU_to_DCACHE_data_535));\
bit_vector_cast_to_bit_vector(0, &(wdata), &(RPIPE_CPU_to_DCACHE_data_535));\
;

#define cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_549_c_macro_ __declare_static_bit_vector(CONCAT_u1_u9_540,9);\
__declare_static_bit_vector(CONCAT_u9_u17_542,17);\
__declare_static_bit_vector(CONCAT_u8_u40_545,40);\
__declare_static_bit_vector(CONCAT_u40_u104_547,104);\
__declare_static_bit_vector(CONCAT_u17_u121_548,121);\
bit_vector_concatenate( &(ONE_1), &(req_type), &(CONCAT_u1_u9_540));\
bit_vector_concatenate( &(CONCAT_u1_u9_540), &(asi), &(CONCAT_u9_u17_542));\
bit_vector_concatenate( &(byte_mask), &(addr), &(CONCAT_u8_u40_545));\
bit_vector_concatenate( &(CONCAT_u8_u40_545), &(wdata), &(CONCAT_u40_u104_547));\
bit_vector_concatenate( &(CONCAT_u9_u17_542), &(CONCAT_u40_u104_547), &(CONCAT_u17_u121_548));\
write_bit_vector_to_pipe("NOBLOCK_CPU_to_DCACHE_command",&(CONCAT_u17_u121_548));\
;

#define cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_552_c_macro_ __declare_static_bit_vector(RPIPE_DCACHE_to_CPU_response_551,72);\
read_bit_vector_from_pipe("DCACHE_to_CPU_response",&(RPIPE_DCACHE_to_CPU_response_551));\
bit_vector_cast_to_bit_vector(0, &(rsp), &(RPIPE_DCACHE_to_CPU_response_551));\
;

#define cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_556_c_macro_ __declare_static_bit_vector(slice_555,8);\
bit_vector_slice(&(rsp), &(slice_555), 64);\
bit_vector_cast_to_bit_vector(0, &(mae), &(slice_555));\
;

#define cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_560_c_macro_ __declare_static_bit_vector(slice_559,64);\
bit_vector_slice(&(rsp), &(slice_559), 0);\
bit_vector_cast_to_bit_vector(0, &(rdata), &(slice_559));\
;

#define cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_563_c_macro_ write_bit_vector_to_pipe("DCACHE_to_CPU_mae",&(mae));\
;

#define cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_566_c_macro_ write_bit_vector_to_pipe("DCACHE_to_CPU_data",&(rdata));\
;
;

#define cache_c_interface___cache_c_interface__dcache_interface_daemon_branch_block_stmt_520_c_export_apply_macro_ ;

#define cache_c_interface___dcache_interface_daemon_inner_outarg_prep_macro__ ;

#define cache_c_interface___dcache_interface_daemon_outer_arg_decl_macro__ ;

#define cache_c_interface___dcache_interface_daemon_outer_op_xfer_macro__ ;
void            cache_c_interface__global_storage_initializer_();
void            _cache_c_interface__global_storage_initializer__();

#define cache_c_interface___global_storage_initializer__inner_inarg_prep_macro__
#define cache_c_interface___global_storage_initializer__inner_outarg_prep_macro__ ;

#define cache_c_interface___global_storage_initializer__outer_arg_decl_macro__ ;

#define cache_c_interface___global_storage_initializer__outer_op_xfer_macro__ ;
void            cache_c_interface__icache_interface_daemon();
void            _cache_c_interface__icache_interface_daemon_();

#define cache_c_interface___icache_interface_daemon_inner_inarg_prep_macro__
#define cache_c_interface___cache_c_interface__icache_interface_daemon_branch_block_stmt_574_c_export_decl_macro_ __declare_static_bit_vector(asi,8);\
__declare_static_bit_vector(addr,32);\
__declare_static_bit_vector(rsp,90);\
__declare_static_bit_vector(mmu_fsr,18);\
__declare_static_bit_vector(mae,8);\
__declare_static_bit_vector(ipair,64);\


#define cache_c_interface___cache_c_interface__icache_interface_daemon_merge_stmt_575_c_preamble_macro_ uint8_t merge_stmt_575_entry_flag;\
merge_stmt_575_entry_flag = 1;\
uint8_t loopback_574_flag = 0;\
goto merge_stmt_575_run;\
loopback_574: loopback_574_flag = 1;\
goto merge_stmt_575_run;\
merge_stmt_575_run: ;\
;

#define cache_c_interface___cache_c_interface__icache_interface_daemon_merge_stmt_575_c_postamble_macro_ loopback_574_flag = 0;\
merge_stmt_575_entry_flag = 0;

#define cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_578_c_macro_ __declare_static_bit_vector(RPIPE_CPU_to_ICACHE_asi_577,8);\
read_bit_vector_from_pipe("CPU_to_ICACHE_asi",&(RPIPE_CPU_to_ICACHE_asi_577));\
bit_vector_cast_to_bit_vector(0, &(asi), &(RPIPE_CPU_to_ICACHE_asi_577));\
;

#define cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_581_c_macro_ __declare_static_bit_vector(RPIPE_CPU_to_ICACHE_addr_580,32);\
read_bit_vector_from_pipe("CPU_to_ICACHE_addr",&(RPIPE_CPU_to_ICACHE_addr_580));\
bit_vector_cast_to_bit_vector(0, &(addr), &(RPIPE_CPU_to_ICACHE_addr_580));\
;

#define cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_588_c_macro_ __declare_static_bit_vector(CONCAT_u1_u9_585,9);\
__declare_static_bit_vector(CONCAT_u9_u41_587,41);\
bit_vector_concatenate( &(ONE_1), &(asi), &(CONCAT_u1_u9_585));\
bit_vector_concatenate( &(CONCAT_u1_u9_585), &(addr), &(CONCAT_u9_u41_587));\
write_bit_vector_to_pipe("NOBLOCK_CPU_to_ICACHE_command",&(CONCAT_u9_u41_587));\
;

#define cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_591_c_macro_ __declare_static_bit_vector(RPIPE_ICACHE_to_CPU_response_590,90);\
read_bit_vector_from_pipe("ICACHE_to_CPU_response",&(RPIPE_ICACHE_to_CPU_response_590));\
bit_vector_cast_to_bit_vector(0, &(rsp), &(RPIPE_ICACHE_to_CPU_response_590));\
;

#define cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_595_c_macro_ __declare_static_bit_vector(slice_594,18);\
bit_vector_slice(&(rsp), &(slice_594), 72);\
bit_vector_cast_to_bit_vector(0, &(mmu_fsr), &(slice_594));\
;

#define cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_599_c_macro_ __declare_static_bit_vector(slice_598,8);\
bit_vector_slice(&(rsp), &(slice_598), 64);\
bit_vector_cast_to_bit_vector(0, &(mae), &(slice_598));\
;

#define cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_603_c_macro_ __declare_static_bit_vector(slice_602,64);\
bit_vector_slice(&(rsp), &(slice_602), 0);\
bit_vector_cast_to_bit_vector(0, &(ipair), &(slice_602));\
;

#define cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_606_c_macro_ write_bit_vector_to_pipe("ICACHE_to_CPU_mae",&(mae));\
;

#define cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_609_c_macro_ write_bit_vector_to_pipe("ICACHE_to_CPU_instr_pair",&(ipair));\
;

#define cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_613_c_macro_ __declare_static_bit_vector(type_cast_612,32);\
bit_vector_bitcast_to_bit_vector( &(type_cast_612), &(mmu_fsr));\
write_bit_vector_to_pipe("ICACHE_to_CPU_fsr",&(type_cast_612));\
;
;

#define cache_c_interface___cache_c_interface__icache_interface_daemon_branch_block_stmt_574_c_export_apply_macro_ ;

#define cache_c_interface___icache_interface_daemon_inner_outarg_prep_macro__ ;

#define cache_c_interface___icache_interface_daemon_outer_arg_decl_macro__ ;

#define cache_c_interface___icache_interface_daemon_outer_op_xfer_macro__ ;
void            cache_c_interface__mem_load__(uint32_t, uint8_t *);
void            _cache_c_interface__mem_load___(bit_vector *,
						bit_vector *);

#define cache_c_interface___mem_load___inner_inarg_prep_macro__ __declare_static_bit_vector(address,32);\
bit_vector_cast_to_bit_vector(0, &(address), &((*__paddress)));\
__declare_static_bit_vector(data,8);\

#define cache_c_interface___cache_c_interface__mem_load___assign_stmt_627_c_macro_ __declare_static_bit_vector(konst_622,32);\
bit_vector_clear(&konst_622);\
konst_622.val.byte_array[0] = 1;\
__declare_static_bit_vector(MUL_u32_u32_623,32);\
__declare_static_bit_vector(konst_624,32);\
bit_vector_clear(&konst_624);\
__declare_static_bit_vector(ADD_u32_u32_625,32);\
bit_vector_clear(&konst_622);\
konst_622.val.byte_array[0] = 1;\
bit_vector_mul( &(address), &(konst_622), &(MUL_u32_u32_623));\
bit_vector_clear(&konst_624);\
bit_vector_plus( &(MUL_u32_u32_623), &(konst_624), &(ADD_u32_u32_625));\
bit_vector_cast_to_bit_vector(0, &(data), &((default_mem_pool[bit_vector_to_uint64(0, &ADD_u32_u32_625)])));\
;

#define cache_c_interface___mem_load___inner_outarg_prep_macro__ bit_vector_cast_to_bit_vector(0, &((*__pdata)), &(data));\
;

#define cache_c_interface___mem_load___outer_arg_decl_macro__ __declare_bit_vector(__address, 32);\
bit_vector_assign_uint64(0, &__address, address);\
__declare_bit_vector(__data, 8);\
;

#define cache_c_interface___mem_load___outer_op_xfer_macro__  *data =  bit_vector_to_uint64(0, &__data);\
;
void            cache_c_interface__mem_store__(uint32_t, uint8_t);
void            _cache_c_interface__mem_store___(bit_vector *,
						 bit_vector *);

#define cache_c_interface___mem_store___inner_inarg_prep_macro__ __declare_static_bit_vector(address,32);\
bit_vector_cast_to_bit_vector(0, &(address), &((*__paddress)));\
__declare_static_bit_vector(data,8);\
bit_vector_cast_to_bit_vector(0, &(data), &((*__pdata)));\

#define cache_c_interface___cache_c_interface__mem_store___assign_stmt_639_c_macro_ __declare_static_bit_vector(konst_633,32);\
bit_vector_clear(&konst_633);\
konst_633.val.byte_array[0] = 1;\
__declare_static_bit_vector(MUL_u32_u32_634,32);\
__declare_static_bit_vector(konst_635,32);\
bit_vector_clear(&konst_635);\
__declare_static_bit_vector(ADD_u32_u32_636,32);\
bit_vector_cast_to_bit_vector(0, &((default_mem_pool[bit_vector_to_uint64(0, &ADD_u32_u32_636)])), &(data));\
;

#define cache_c_interface___mem_store___inner_outarg_prep_macro__ ;

#define cache_c_interface___mem_store___outer_arg_decl_macro__ __declare_bit_vector(__address, 32);\
bit_vector_assign_uint64(0, &__address, address);\
__declare_bit_vector(__data, 8);\
bit_vector_assign_uint64(0, &__data, data);\
;

#define cache_c_interface___mem_store___outer_op_xfer_macro__ ;
void            cache_c_interface__start_daemons(FILE * fp);
void            cache_c_interface__stop_daemons();
