#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <BitVectors.h>
#include <pipeHandler.h>
void            fpunit_exec_exec__set_trace_file(FILE * fp);
void            fpunit_exec_exec___init_aa_globals__();
void            _fpunit_exec_exec_DoubleToExtendedFp_(bit_vector *,
						      bit_vector *,
						      bit_vector *);
void            _fpunit_exec_exec_DoubleToSingle_(double *, bit_vector *,
						  bit_vector *);
void            fpunit_exec_exec_SingleToDouble(float, double *);
void            _fpunit_exec_exec_SingleToDouble_(float *, double *);
void            _fpunit_exec_exec_SingleToExtendedFp_(bit_vector *,
						      bit_vector *,
						      bit_vector *);
void            fpunit_exec_exec_absVal(uint16_t, uint16_t *);
void            _fpunit_exec_exec_absVal_(bit_vector *, bit_vector *);
void            _fpunit_exec_exec_adder_11_(bit_vector *, bit_vector *,
					    bit_vector *, bit_vector *,
					    bit_vector *);
void            _fpunit_exec_exec_adder_18_(bit_vector *, bit_vector *,
					    bit_vector *, bit_vector *,
					    bit_vector *);
void            _fpunit_exec_exec_adder_19_(bit_vector *, bit_vector *,
					    bit_vector *, bit_vector *,
					    bit_vector *);
void            _fpunit_exec_exec_adder_35_with_carry_(bit_vector *,
						       bit_vector *,
						       bit_vector *,
						       bit_vector *,
						       bit_vector *);
void            _fpunit_exec_exec_adder_58_with_carry_(bit_vector *,
						       bit_vector *,
						       bit_vector *,
						       bit_vector *,
						       bit_vector *);
void            _fpunit_exec_exec_adder_64_with_carry_(bit_vector *,
						       bit_vector *,
						       bit_vector *,
						       bit_vector *,
						       bit_vector *);
void            _fpunit_exec_exec_adder_65_(bit_vector *, bit_vector *,
					    bit_vector *);
void            fpunit_exec_exec_alignDivisorToDividend(uint64_t, uint64_t,
							uint64_t *,
							uint64_t *);
void            _fpunit_exec_exec_alignDivisorToDividend_(bit_vector *,
							  bit_vector *,
							  bit_vector *,
							  bit_vector *);
void            _fpunit_exec_exec_break_number_32_(bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *);
void            _fpunit_exec_exec_break_number_64_(bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *);
void            fpunit_exec_exec_calculate_imm_offset_for_dti(uint32_t,
							      uint32_t *);
void            _fpunit_exec_exec_calculate_imm_offset_for_dti_(bit_vector
								*,
								bit_vector
								*);
void            _fpunit_exec_exec_check_fh_exponent_overflow_(bit_vector *,
							      bit_vector *,
							      bit_vector
							      *);
void            _fpunit_exec_exec_classFp32_(float *, bit_vector *,
					     bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *,
					     bit_vector *);
void            _fpunit_exec_exec_classFp32IntoClassWord_(float *,
							  bit_vector *);
void            _fpunit_exec_exec_classFp64_(double *, bit_vector *,
					     bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *,
					     bit_vector *);
void            _fpunit_exec_exec_classFpBase_(bit_vector *, bit_vector *,
					       bit_vector *, bit_vector *,
					       bit_vector *, bit_vector *,
					       bit_vector *, bit_vector *,
					       bit_vector *, bit_vector *,
					       bit_vector *, bit_vector *,
					       bit_vector *, bit_vector *,
					       bit_vector *);
void            _fpunit_exec_exec_classifyFp16_(bit_vector *, bit_vector *,
						bit_vector *, bit_vector *,
						bit_vector *);
void            _fpunit_exec_exec_classify_32_(float *, bit_vector *,
					       bit_vector *, bit_vector *,
					       bit_vector *, bit_vector *);
void            _fpunit_exec_exec_classify_64_(double *, bit_vector *,
					       bit_vector *, bit_vector *,
					       bit_vector *, bit_vector *);
void            _fpunit_exec_exec_classify_and_prepare_32_(float *,
							   bit_vector *,
							   bit_vector *,
							   bit_vector *,
							   float *);
void            _fpunit_exec_exec_classify_and_prepare_64_(double *,
							   bit_vector *,
							   bit_vector *,
							   bit_vector *,
							   double *);
void            _fpunit_exec_exec_classify_utility_(bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *);
void            _fpunit_exec_exec_compare11_(bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *);
void            _fpunit_exec_exec_compare16_(bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *);
void            _fpunit_exec_exec_compare24_(bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *);
void            _fpunit_exec_exec_compare32_(bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *);
void            _fpunit_exec_exec_compare35_(bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *);
void            _fpunit_exec_exec_compare4_(bit_vector *, bit_vector *,
					    bit_vector *, bit_vector *);
void            _fpunit_exec_exec_compare53_(bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *);
void            _fpunit_exec_exec_compare64_(bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *);
void            _fpunit_exec_exec_compare8_(bit_vector *, bit_vector *,
					    bit_vector *, bit_vector *);
void           
_fpunit_exec_exec_comparison_greater_equal_less_26_(bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *);
void           
_fpunit_exec_exec_comparison_greater_equal_less_55_(bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *);
void            _fpunit_exec_exec_decode_alu_ispec_(bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *);
void            _fpunit_exec_exec_decode_cp_ispec_(bit_vector *,
						   bit_vector *,
						   bit_vector *);
void           
_fpunit_exec_exec_decode_cti_for_offset_calculation_(bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *);
void            _fpunit_exec_exec_decode_cti_ispec_(bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *);
void            _fpunit_exec_exec_decode_dti_ispec_(bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *);
void            _fpunit_exec_exec_decode_fp_ispec_(bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *);
void            _fpunit_exec_exec_decode_instruction_stage_1_(bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector
							      *);
void            _fpunit_exec_exec_decode_is_flush_asi_(bit_vector *,
						       bit_vector *);
void            _fpunit_exec_exec_decode_misc_ispec_(bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *);
void            _fpunit_exec_exec_decode_stream_corrector_info_(bit_vector
								*,
								bit_vector
								*,
								bit_vector
								*,
								bit_vector
								*,
								bit_vector
								*,
								bit_vector
								*,
								bit_vector
								*);
void            _fpunit_exec_exec_decode_thread_control_word_(bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector *,
							      bit_vector
							      *);
void            fpunit_exec_exec_delay_32_2(uint32_t, uint32_t *);
void            _fpunit_exec_exec_delay_32_2_(bit_vector *, bit_vector *);
void            fpunit_exec_exec_delay_64_3(uint64_t, uint64_t *);
void            _fpunit_exec_exec_delay_64_3_(bit_vector *, bit_vector *);
void            _fpunit_exec_exec_denormalize_32_(bit_vector *,
						  bit_vector *,
						  bit_vector *,
						  bit_vector *);
void            _fpunit_exec_exec_denormalize_64_(bit_vector *,
						  bit_vector *,
						  bit_vector *,
						  bit_vector *);
void            _fpunit_exec_exec_denormalize_fp_32_(bit_vector *,
						     bit_vector *);
void            _fpunit_exec_exec_denormalize_fp_64_(bit_vector *,
						     bit_vector *);
void            _fpunit_exec_exec_early_decode_for_fetch_(bit_vector *,
							  bit_vector *,
							  bit_vector *,
							  bit_vector *,
							  bit_vector *,
							  bit_vector *,
							  bit_vector *,
							  bit_vector *);
void            _fpunit_exec_exec_exec_bicc_generic_(bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *,
						     bit_vector *);
void            fpunit_exec_exec_exec_daemon();
void            _fpunit_exec_exec_exec_daemon_();
void            _fpunit_exec_exec_exec_fbfcc_generic_(bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *);
void            fpunit_exec_exec_exec_fhtoi16(uint16_t, uint16_t *);
void            _fpunit_exec_exec_exec_fhtoi16_(bit_vector *,
						bit_vector *);
void            fpunit_exec_exec_exec_fhtos(uint16_t, uint32_t *);
void            _fpunit_exec_exec_exec_fhtos_(bit_vector *, bit_vector *);
void            fpunit_exec_exec_exec_fi16toh(uint16_t, uint16_t *);
void            _fpunit_exec_exec_exec_fi16toh_(bit_vector *,
						bit_vector *);
void            _fpunit_exec_exec_exec_fp_simd_16_op_(bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *);
void            fpunit_exec_exec_exec_fstoh(uint32_t, uint16_t *);
void            _fpunit_exec_exec_exec_fstoh_(bit_vector *, bit_vector *);
void            fpunit_exec_exec_exec_vfhtoi16(uint64_t, uint64_t *);
void            _fpunit_exec_exec_exec_vfhtoi16_(bit_vector *,
						 bit_vector *);
void            fpunit_exec_exec_exec_vfi16toh(uint64_t, uint64_t *);
void            _fpunit_exec_exec_exec_vfi16toh_(bit_vector *,
						 bit_vector *);
void            _fpunit_exec_exec_execute_fbfcc_(bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *);
void            _fpunit_exec_exec_expDiffDouble_(bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *);
void            _fpunit_exec_exec_expDiffSingle_(bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *);
void            fpunit_exec_exec_fadd16_wrap(uint16_t, uint16_t,
					     uint16_t *);
void            _fpunit_exec_exec_fadd16_wrap_(bit_vector *, bit_vector *,
					       bit_vector *);
void            _fpunit_exec_exec_faddsub16_(bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *);
void            fpunit_exec_exec_fdtoi_op(double, int32_t *);
void            _fpunit_exec_exec_fdtoi_op_(double *, bit_vector *);
void            fpunit_exec_exec_fdtoi_wrap(double, int32_t *);
void            _fpunit_exec_exec_fdtoi_wrap_(double *, bit_vector *);
void            fpunit_exec_exec_fdtos_wrap(double, float *);
void            _fpunit_exec_exec_fdtos_wrap_(double *, float *);
void            _fpunit_exec_exec_find_left_16_(bit_vector *, bit_vector *,
						bit_vector *);
void            _fpunit_exec_exec_find_left_24_(bit_vector *, bit_vector *,
						bit_vector *);
void            _fpunit_exec_exec_find_left_32_(bit_vector *, bit_vector *,
						bit_vector *);
void            _fpunit_exec_exec_find_left_4_(bit_vector *, bit_vector *,
					       bit_vector *);
void            _fpunit_exec_exec_find_left_53_(bit_vector *, bit_vector *,
						bit_vector *);
void            _fpunit_exec_exec_find_left_8_(bit_vector *, bit_vector *,
					       bit_vector *);
void            _fpunit_exec_exec_find_leftmost_35_(bit_vector *,
						    bit_vector *,
						    bit_vector *);
void            _fpunit_exec_exec_find_leftmost_64_(bit_vector *,
						    bit_vector *,
						    bit_vector *);
void            fpunit_exec_exec_fitod64(uint32_t, double *);
void            _fpunit_exec_exec_fitod64_(bit_vector *, double *);
void            fpunit_exec_exec_fitod64_wrap(uint32_t, double *);
void            _fpunit_exec_exec_fitod64_wrap_(bit_vector *, double *);
void            fpunit_exec_exec_fitos32_wrap(uint32_t, float *);
void            _fpunit_exec_exec_fitos32_wrap_(bit_vector *, float *);
void            fpunit_exec_exec_fmul16(uint16_t, uint16_t, uint16_t *);
void            _fpunit_exec_exec_fmul16_(bit_vector *, bit_vector *,
					  bit_vector *);
void            fpunit_exec_exec_fmul16_wrap(uint16_t, uint16_t,
					     uint16_t *);
void            _fpunit_exec_exec_fmul16_wrap_(bit_vector *, bit_vector *,
					       bit_vector *);
void            fpunit_exec_exec_fnegs_64(double, double *);
void            _fpunit_exec_exec_fnegs_64_(double *, double *);
void            _fpunit_exec_exec_fpadd32_op_(bit_vector *, bit_vector *,
					      bit_vector *, bit_vector *,
					      bit_vector *, bit_vector *);
void            fpunit_exec_exec_fpadd32_wrap(float, float, float *);
void            _fpunit_exec_exec_fpadd32_wrap_(float *, float *, float *);
void            fpunit_exec_exec_fpadd32_wrap_new(float, float, float *);
void            _fpunit_exec_exec_fpadd32_wrap_new_(float *, float *,
						    float *);
void            _fpunit_exec_exec_fpadd64_op_(bit_vector *, bit_vector *,
					      bit_vector *, bit_vector *,
					      bit_vector *, bit_vector *,
					      bit_vector *, bit_vector *,
					      bit_vector *, bit_vector *,
					      bit_vector *, bit_vector *);
void            fpunit_exec_exec_fpadd64_wrap(double, double, double *);
void            _fpunit_exec_exec_fpadd64_wrap_(double *, double *,
						double *);
void            _fpunit_exec_exec_fpcmp32_(float *, float *, bit_vector *,
					   bit_vector *);
void            _fpunit_exec_exec_fpcmp64_(double *, double *,
					   bit_vector *, bit_vector *);
void            fpunit_exec_exec_fpdivide32(float, float, float *);
void            _fpunit_exec_exec_fpdivide32_(float *, float *, float *);
void            fpunit_exec_exec_fpdivide64(double, double, double *);
void            _fpunit_exec_exec_fpdivide64_(double *, double *,
					      double *);
void            _fpunit_exec_exec_fpmul32_op_(bit_vector *, bit_vector *,
					      bit_vector *, bit_vector *,
					      bit_vector *, bit_vector *);
void            fpunit_exec_exec_fpmul32_wrap(float, float, float *);
void            _fpunit_exec_exec_fpmul32_wrap_(float *, float *, float *);
void            fpunit_exec_exec_fpmul32_wrap_new(float, float, float *);
void            _fpunit_exec_exec_fpmul32_wrap_new_(float *, float *,
						    float *);
void            _fpunit_exec_exec_fpmul64_op_(bit_vector *, bit_vector *,
					      bit_vector *, bit_vector *,
					      bit_vector *, bit_vector *,
					      bit_vector *, bit_vector *,
					      bit_vector *, bit_vector *,
					      bit_vector *, bit_vector *);
void            fpunit_exec_exec_fpmul64_wrap(double, double, double *);
void            _fpunit_exec_exec_fpmul64_wrap_(double *, double *,
						double *);
void            fpunit_exec_exec_fpsqrt32_bit_wise(float, float *);
void            _fpunit_exec_exec_fpsqrt32_bit_wise_(float *, float *);
void            fpunit_exec_exec_fpsqrt64_bit_wise(double, double *);
void            _fpunit_exec_exec_fpsqrt64_bit_wise_(double *, double *);
void            fpunit_exec_exec_fpsub32_wrap(float, float, float *);
void            _fpunit_exec_exec_fpsub32_wrap_(float *, float *, float *);
void            fpunit_exec_exec_fpsub32_wrap_new(float, float, float *);
void            _fpunit_exec_exec_fpsub32_wrap_new_(float *, float *,
						    float *);
void            fpunit_exec_exec_fpsub64_wrap(double, double, double *);
void            _fpunit_exec_exec_fpsub64_wrap_(double *, double *,
						double *);
void            fpunit_exec_exec_fpu_increment_64(uint64_t, uint64_t *);
void            _fpunit_exec_exec_fpu_increment_64_(bit_vector *,
						    bit_vector *);
void            fpunit_exec_exec_fpunit_exec_pipe_merge_daemon();
void            _fpunit_exec_exec_fpunit_exec_pipe_merge_daemon_();
void            fpunit_exec_exec_fstod_wrap(float, double *);
void            _fpunit_exec_exec_fstod_wrap_(float *, double *);
void            fpunit_exec_exec_fstoi_wrap(float, int32_t *);
void            _fpunit_exec_exec_fstoi_wrap_(float *, bit_vector *);
void            fpunit_exec_exec_fsub16_wrap(uint16_t, uint16_t,
					     uint16_t *);
void            _fpunit_exec_exec_fsub16_wrap_(bit_vector *, bit_vector *,
					       bit_vector *);
void           
_fpunit_exec_exec_generate_pre_compute_exceptions_(bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *, float *,
						   float *, bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *, double *,
						   double *, bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *,
						   bit_vector *);
void            _fpunit_exec_exec_getHalfInf_(bit_vector *, bit_vector *);
void            _fpunit_exec_exec_getHalfNan_(bit_vector *, bit_vector *);
void            _fpunit_exec_exec_getHalfZero_(bit_vector *, bit_vector *);
void            fpunit_exec_exec_global_storage_initializer_();
void            _fpunit_exec_exec_global_storage_initializer__();
void            _fpunit_exec_exec_i16_sll_(bit_vector *, bit_vector *,
					   bit_vector *);
void            _fpunit_exec_exec_i24_sll_(bit_vector *, bit_vector *,
					   bit_vector *);
void            _fpunit_exec_exec_i32_sll_(bit_vector *, bit_vector *,
					   bit_vector *);
void            _fpunit_exec_exec_i32_srl_(bit_vector *, bit_vector *,
					   bit_vector *);
void            _fpunit_exec_exec_i35_sll_(bit_vector *, bit_vector *,
					   bit_vector *);
void            _fpunit_exec_exec_i53_sll_(bit_vector *, bit_vector *,
					   bit_vector *);
void            _fpunit_exec_exec_i64_sll_(bit_vector *, bit_vector *,
					   bit_vector *);
void            _fpunit_exec_exec_i64_srl_(bit_vector *, bit_vector *,
					   bit_vector *);
void            fpunit_exec_exec_increment_16(uint16_t, uint16_t *);
void            _fpunit_exec_exec_increment_16_(bit_vector *,
						bit_vector *);
void            fpunit_exec_exec_increment_32(uint32_t, uint32_t *);
void            _fpunit_exec_exec_increment_32_(bit_vector *,
						bit_vector *);
void            fpunit_exec_exec_increment_64(uint64_t, uint64_t *);
void            _fpunit_exec_exec_increment_64_(bit_vector *,
						bit_vector *);
void            _fpunit_exec_exec_isSnand_(double *, bit_vector *);
void            _fpunit_exec_exec_isSnans_(float *, bit_vector *);
void            _fpunit_exec_exec_make_new_estimate_32_(bit_vector *,
							bit_vector *,
							bit_vector *,
							bit_vector *,
							bit_vector *,
							bit_vector *);
void            _fpunit_exec_exec_make_new_estimate_56_(bit_vector *,
							bit_vector *,
							bit_vector *,
							bit_vector *,
							bit_vector *,
							bit_vector *);
void            fpunit_exec_exec_mem_load__(uint32_t, uint8_t *);
void            _fpunit_exec_exec_mem_load___(bit_vector *, bit_vector *);
void            fpunit_exec_exec_mem_store__(uint32_t, uint8_t);
void            _fpunit_exec_exec_mem_store___(bit_vector *, bit_vector *);
void            _fpunit_exec_exec_mul24_(bit_vector *, bit_vector *,
					 bit_vector *);
void            _fpunit_exec_exec_mul53_(bit_vector *, bit_vector *,
					 bit_vector *);
void            _fpunit_exec_exec_needSignalFromRetire_(bit_vector *,
							bit_vector *,
							bit_vector *);
void            fpunit_exec_exec_negateVal(uint16_t, uint16_t *);
void            _fpunit_exec_exec_negateVal_(bit_vector *, bit_vector *);
void            _fpunit_exec_exec_negate_classification_(bit_vector *,
							 bit_vector *);
void            _fpunit_exec_exec_normalize_32_(bit_vector *, bit_vector *,
						bit_vector *,
						bit_vector *);
void            _fpunit_exec_exec_normalize_64_(bit_vector *, bit_vector *,
						bit_vector *,
						bit_vector *);
void            _fpunit_exec_exec_pre_op_preparation_(bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      float *, float *,
						      double *, double *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *);
void            _fpunit_exec_exec_round_32_extn_(bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *);
void            _fpunit_exec_exec_round_64_extn_(bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *);
void            _fpunit_exec_exec_round_e_32_(bit_vector *, bit_vector *,
					      bit_vector *, float *);
void            _fpunit_exec_exec_round_e_64_(bit_vector *, bit_vector *,
					      bit_vector *, double *);
void            _fpunit_exec_exec_round_fp_32_(bit_vector *, bit_vector *);
void            _fpunit_exec_exec_round_fp_64_(bit_vector *, bit_vector *);
void            _fpunit_exec_exec_shifter_left_right_32_(bit_vector *,
							 bit_vector *,
							 bit_vector *,
							 bit_vector *);
void            _fpunit_exec_exec_shifter_left_right_64_(bit_vector *,
							 bit_vector *,
							 bit_vector *,
							 bit_vector *);
void            _fpunit_exec_exec_short_divide_24_core_(bit_vector *,
							bit_vector *,
							bit_vector *,
							bit_vector *,
							bit_vector *,
							bit_vector *,
							bit_vector *);
void           
_fpunit_exec_exec_short_divide_24_pipelined_optimised_(bit_vector *,
						       bit_vector *,
						       bit_vector *);
void            _fpunit_exec_exec_short_divide_53_core_(bit_vector *,
							bit_vector *,
							bit_vector *,
							bit_vector *,
							bit_vector *,
							bit_vector *,
							bit_vector *);
void           
_fpunit_exec_exec_short_divide_53_pipelined_optimised_(bit_vector *,
						       bit_vector *,
						       bit_vector *);
void            _fpunit_exec_exec_short_sqrt_32_(bit_vector *,
						 bit_vector *,
						 bit_vector *);
void            _fpunit_exec_exec_short_sqrt_32_core_(bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *);
void            _fpunit_exec_exec_short_sqrt_56_(bit_vector *,
						 bit_vector *,
						 bit_vector *);
void            _fpunit_exec_exec_short_sqrt_56_core_(bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *,
						      bit_vector *);
void            fpunit_exec_exec_signature_8(uint32_t, uint8_t *);
void            _fpunit_exec_exec_signature_8_(bit_vector *, bit_vector *);
void            _fpunit_exec_exec_splitFp16_(bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *);
void            fpunit_exec_exec_twos_complement_16(uint16_t, uint16_t *);
void            _fpunit_exec_exec_twos_complement_16_(bit_vector *,
						      bit_vector *);
void            fpunit_exec_exec_twos_complement_32(uint32_t, uint32_t *);
void            _fpunit_exec_exec_twos_complement_32_(bit_vector *,
						      bit_vector *);
void            fpunit_exec_exec_twos_complement_64(uint64_t, uint64_t *);
void            _fpunit_exec_exec_twos_complement_64_(bit_vector *,
						      bit_vector *);
void            _fpunit_exec_exec_u32_sll_(bit_vector *, bit_vector *,
					   bit_vector *);
void            _fpunit_exec_exec_u35_sr_special_(bit_vector *,
						  bit_vector *,
						  bit_vector *,
						  bit_vector *);
void            _fpunit_exec_exec_u64_shift_(bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *,
					     bit_vector *);
void            _fpunit_exec_exec_u64_shift_sticky_(bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *,
						    bit_vector *);
void            _fpunit_exec_exec_u64_sll_(bit_vector *, bit_vector *,
					   bit_vector *);
void            _fpunit_exec_exec_u64_sr_special_(bit_vector *,
						  bit_vector *,
						  bit_vector *,
						  bit_vector *);
void            _fpunit_exec_exec_u64_srl_(bit_vector *, bit_vector *,
					   bit_vector *);
void            fpunit_exec_exec_u64_true_divide(uint64_t, uint64_t,
						 uint64_t *);
void            _fpunit_exec_exec_u64_true_divide_(bit_vector *,
						   bit_vector *,
						   bit_vector *);
void            _fpunit_exec_exec_u_cmp_32_(bit_vector *, bit_vector *,
					    bit_vector *, bit_vector *,
					    bit_vector *);
void            _fpunit_exec_exec_u_cmp_34_(bit_vector *, bit_vector *,
					    bit_vector *, bit_vector *,
					    bit_vector *);
void            _fpunit_exec_exec_u_cmp_64_(bit_vector *, bit_vector *,
					    bit_vector *, bit_vector *,
					    bit_vector *);
void            _fpunit_exec_exec_u_set_index_64_(bit_vector *,
						  bit_vector *);
void            _fpunit_exec_exec_uaddsub32_(bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *,
					     bit_vector *, bit_vector *);
void            fpunit_exec_exec_umul32(uint32_t, uint32_t, uint64_t *);
void            _fpunit_exec_exec_umul32_(bit_vector *, bit_vector *,
					  bit_vector *);
void            _fpunit_exec_exec_ushift32_(bit_vector *, bit_vector *,
					    bit_vector *, bit_vector *,
					    bit_vector *);
void            fpunit_exec_exec_vfadd16_wrap(uint64_t, uint64_t,
					      uint64_t *);
void            _fpunit_exec_exec_vfadd16_wrap_(bit_vector *, bit_vector *,
						bit_vector *);
void            fpunit_exec_exec_vfaddreduce16_wrap(uint64_t, uint64_t,
						    uint32_t *);
void            _fpunit_exec_exec_vfaddreduce16_wrap_(bit_vector *,
						      bit_vector *,
						      bit_vector *);
void            fpunit_exec_exec_vfmul16_wrap(uint64_t, uint64_t,
					      uint64_t *);
void            _fpunit_exec_exec_vfmul16_wrap_(bit_vector *, bit_vector *,
						bit_vector *);
void            fpunit_exec_exec_vfsub16_wrap(uint64_t, uint64_t,
					      uint64_t *);
void            _fpunit_exec_exec_vfsub16_wrap_(bit_vector *, bit_vector *,
						bit_vector *);
void            _fpunit_exec_exec_writeback_fsm_(bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *,
						 bit_vector *);
void            fpunit_exec_exec_start_daemons(FILE * fp, int trace_on);
void            fpunit_exec_exec_stop_daemons();
