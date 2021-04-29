#ifndef __TRAPS_H__
#define __TRAPS_H__

//
//  DO NOT TAMPER WITH THIS  PLEASE.
//
typedef enum _TrapType
{
	_TRAP_,
	_RESET_TRAP_,
	_MAE_,
	_ANNUL_,
	_INSTRUCTION_ACCESS_EXCEPTION_,
	_DATA_STORE_ERROR_,
	_INSTRUCTION_ACCESS_ERROR_,
	_R_REGISTER_ACCESS_ERROR_,
	_PRIVILEGED_INSTRUCTION_,
	_ILLEGAL_INSTRUCTION_,
	_ILLEGAL_IU_INSTRUCTION_,
	_FP_DISABLED_,
	_CP_DISABLED_,
	_UNIMPLEMENTED_FLUSH_,
	_WINDOW_OVERFLOW_,
	_WINDOW_UNDERFLOW_,
	_MEM_ADDRESS_NOT_ALIGNED_,
	_FP_EXCEPTION_,
	_CP_EXCEPTION_,
	_DATA_ACCESS_ERROR_,
	_DATA_ACCESS_EXCEPTION_,
	_TAG_OVERFLOW_,
	_DIVISION_BY_ZERO_,
	_TRAP_INSTRUCTION_

} TrapType;

// Page 36, Table 4-4
typedef enum _FloatTrapType
{
	_NONE_,
	_IEEE_754_EXCEPTION_,
	_UNFINISHED_FPOP_,
	_UNIMPLEMENTED_FPOP_,
	_SEQUENCE_ERROR_,
	_HARDWARE_ERROR_,
	_INVALID_FP_REGISTER_,
	_RESERVED_,

} FloatTrapType;

// IEEE_754 Floating Point Exceptions (cexc and aexc fields on FSR)
typedef enum _FPExceptionFields
{
	_NXC_,
	_DZC_,
	_UFC_,
	_OFC_,
	_NVC_,
	_NXA_,
	_DZA_,
	_UFA_,
	_OFA_,
	_NVM_
} FPExceptionFields;


//
// convert tv to a human readable tag.
//
void trapToString (uint32_t tv, uint8_t intrpt_level, uint8_t ticc_trap_type, char* tt);

#endif

