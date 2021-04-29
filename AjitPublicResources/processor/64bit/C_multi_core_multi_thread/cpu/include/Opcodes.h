//-------------------------------------------------------------------------
// Describes all the opcodes used
//-------------------------------------------------------------------------

#ifndef __OPCODES_H__
#define __OPCODES_H__

typedef enum _Opcode
{
	//Load
	_LDSB_, // 001001 Load Signed Byte
	_LDSH_, // 001010 Load Signed Halfword
	_LDUB_, // 000001 Load Unsigned Byte
	_LDUH_, // 000010 Load Unsigned Halfword
	_LD_,   // 000000 Load Word
	_LDD_,  // 000011 Load Doubleword

	_LDF_,   // 100000 Load Floating-point Register
	_LDDF_,  // 100011 Load Double Floating-point Register
	_LDFSR_, // 100001 Load Floating-point State Register

	_LDC_,   // 110000 Load Coprocessor Register
	_LDDC_,  // 110011 Load Double Coprocessor Register
	_LDCSR_, // 110001 Load Coprocessor State Register

	_LDSBA_, // 011001 Load Signed Byte from Alternate space
	_LDSHA_, // 011010 Load Signed Halfword from Alternate space
	_LDUBA_, // 010001 Load Unsigned Byte from Alternate space
	_LDUHA_, // 010010 Load Unsigned Halfword from Alternate space
	_LDA_,   // 010000 Load Word from Alternate space
	_LDDA_,  // 010011 Load Doubleword from Alternate space

	//Store
	_STB_, // 000101 Store Byte
	_STH_, // 000110 Store Halfword
	_ST_, // 000100 Store Word
	_STD_, // 000111 Store Doubleword

	_STF_, // 100100 Store Floating-point
	_STDF_, // 100111 Store Double Floating-point
	_STFSR_, // 100101 Store Floating-point State Register
	_STDFQ_, // 100110 Store Double Floating-point deferred-trap Queue

	_STC_, // 110100 Store Coprocessor
	_STDC_, // 110111 Store Double Coprocessor
	_STCSR_, // 110101 Store Coprocessor State Register
	_STDCQ_, // 110110 Store Double Coprocessor Queue

	_STBA_, // 010101 Store Byte into Alternate space
	_STHA_, // 010110 Store Halfword into Alternate space
	_STA_, // 010100 Store Word into Alternate space
	_STDA_, // 010111 Store Doubleword into Alternate space

	//Atomic Load/Store
	_LDSTUB_, // 001101 Atomic Load-Store Unsigned Byte
	_LDSTUBA_, // 011101 Atomic Load-Store Unsigned Byte into Alternate space

	//SWAP Register with Memory,
	_SWAP_, // 001111 SWAP register with memory
	_SWAPA_, // 011111 SWAP register with Alternate space memory
	_CSWAP_, // 101111 COMPARE-AND-SWAP  register with memory
	_CSWAPA_, // 111111 COMPARE-AND-SWAP register with Alternate space memory

	//SETHI Instruction
	_SETHI_, // 00 100 Set High-Order 22 bits

	//NOP Instruction
	_NOP_, // 00 100 No Operation

	//Logical
	_AND_, // 000001 And
	_ANDcc_, // 010001 And and modify icc
	_ANDN_, // 000101 And Not
	_ANDNcc_, // 010101 And Not and modify icc
	_OR_, // 000010 Inclusive Or
	_ORcc_, // 010010 Inclusive Or and modify icc
	_ORN_, // 000110 Inclusive Or Not
	_ORNcc_, // 010110 Inclusive Or Not and modify icc
	_XOR_, // 000011 Exclusive Or
	_XORcc_, // 010011 Exclusive Or and modify icc
	_XNOR_, // 000111 Exclusive Nor
	_XNORcc_, // 010111 Exclusive Nor and modify icc
	//64-bit extensions.
	_ANDD_,
	_ANDDcc_,
	_ANDDN_,
	_ANDDNcc_,
	_ORD_,
	_ORDcc_,
	_ORDN_,
	_ORDNcc_,
	_XORD_,
	_XORDcc_,
	_XNORD_,
	_XNORDcc_,


	//Shift
	_SLL_, // 100101 Shift Left Logical
	_SRL_, // 100110 Shift Right Logical
	_SRA_, // 100111 Shift Right Arithmetic
	// 64-bit extensions.
	_SLLD_,
	_SRLD_,
	_SRAD_,

	//Add
	_ADD_, // 000000 Add
	_ADDcc_, // 010000 Add and modify icc
	_ADDX_, // 001000 Add with Carry
	_ADDXcc_, // 011000 Add with Carry and modify icc
	// 64-bit extensions
	_ADDD_,
	_ADDDcc_,

	//Tagged Add
	_TADDcc_, // 100000 Tagged Add and modify icc
	_TADDccTV_, // 100010 Tagged Add, modify icc and Trap on Overflow

	//Subtract
	_SUB_, // 000100 Subtract
	_SUBcc_, // 010100 Subtract and modify icc
	_SUBX_, // 001100 Subtract with Carry
	_SUBXcc_, // 011100 Subtract with Carry and modify icc
	//64-bit extensions.
	_SUBD_,
	_SUBDcc_,

	//Tagged Subtract
	_TSUBcc_, // 100001 Tagged Subtract and modify icc
	_TSUBccTV_, // 100011 Tagged Subtract, modify icc and Trap on Overflow

	//Multiply Step
	_MULScc_, // 100100 Multiply Step and modify iccif

	// Multiply
	_UMUL_, // 001010 Unsigned Integer Multiply
	_SMUL_, // 001011 Signed Integer Multiply
	_UMULcc_, // 011010 Unsigned Integer Multiply and modify icc
	_SMULcc_, // 011011 Signed Integer Multiply and modify icc
	// 64-bit extensions.
	_UMULD_,
	_UMULDcc_,
	_SMULD_,
	_SMULDcc_,

	//Divide
	_UDIV_, // 001110 Unsigned Integer Divide
	_SDIV_, // 001111 Signed Integer Divide
	_UDIVcc_, // 011110 Unsigned Integer Divide and modify icc
	_SDIVcc_, // 011111 Signed Integer Divide and modify icc
	//64-bit extensions.
	_UDIVD_,
	_UDIVDcc_,
	_SDIVD_,
	_SDIVDcc_,

	//SAVE and RESTORE
	_SAVE_, // 111100 Save caller’s window
	_RESTORE_, // 111101 Restore caller’s window

	//Branch on Integer Condition Codes
	//opcode cond operation icc test
	_BA_, // 1000 Branch Always 1
	_BN_, // 0000 Branch Never 0
	_BNE_, // 1001 Branch on Not Equal not Z
	_BE_, // 0001 Branch on Equal Z
	_BG_, // 1010 Branch on Greater not (Z or (N xor V))
	_BLE_, // 0010 Branch on Less or Equal Z or (N xor V)
	_BGE_, // 1011 Branch on Greater or Equal not (N xor V)
	_BL_, // 0011 Branch on Less N xor V
	_BGU_, // 1100 Branch on Greater Unsigned not (C or Z)
	_BLEU_, // 0100 Branch on Less or Equal Unsigned (C or Z)
	_BCC_, // 1101 Branch on Carry Clear (Greater than or Equal, Unsigned) not C
	_BCS_, // 0101 Branch on Carry Set (Less than, Unsigned) C
	_BPOS_, // 1110 Branch on Positive not N
	_BNEG_, // 0110 Branch on Negative N
	_BVC_, // 1111 Branch on Overflow Clear not V
	_BVS_, // 0111 Branch on Overflow Set V

	//Branch on Floating Point Condition Codes
	//opcode cond operation fcc test
	_FBA_, // 1000 Branch Always 1
	_FBN_, // 0000 Branch Never 0
	_FBU_, // 0111 Branch on Unordered U
	_FBG_, // 0110 Branch on Greater G
	_FBUG_, // 0101 Branch on Unordered or Greater G or U
	_FBL_, // 0100 Branch on Less L
	_FBUL_, // 0011 Branch on Unordered or Less L or U
	_FBLG_, // 0010 Branch on Less or Greater L or G
	_FBNE_, // 0001 Branch on Not Equal L or G or U
	_FBE_, // 1001 Branch on Equal E
	_FBUE_, // 1010 Branch on Unordered or Equal E or U
	_FBGE_, // 1011 Branch on Greater or Equal E or G
	_FBUGE_, // 1100 Branch on Unordered or Greater or Equal E or G or U
	_FBLE_, // 1101 Branch on Less or Equal E or L
	_FBULE_, // 1110 Branch on Unordered or Less or Equal E or L or U
	_FBO_, // 1111 Branch on Ordered E or L or G

	//Branch on Coprocessor Condition Codes
	//opcode cond bp_CP_cc[1:0] test
	_CBA_, // 1000 Always
	_CBN_, // 0000 Never
	_CB3_, // 0111 3
	_CB2_, // 0110 2
	_CB23_, // 0101 2 or 3
	_CB1_, // 0100 1
	_CB13_, // 0011 1 or 3
	_CB12_, // 0010 1 or 2
	_CB123_, // 0001 1 or 2 or 3
	_CB0_, // 1001 0
	_CB03_, // 1010 0 or 3
	_CB02_, // 1011 0 or 2
	_CB023_, // 1100 0 or 2 or 3
	_CB01_, // 1101 0 or 1
	_CB013_, // 1110 0 or 1 or 3
	_CB012_, // 1111 0 or 1 or 2

	//Call and Link
	//Instruction opcode op operation
	_CALL_, // 01 Call and Link

	//Jump and Link
	//Instruction
	_JMPL_, // 111000 Jump and Link

	//Return from Trap
	//Instruction
	_RETT_, // 111001 Return from Trap

	//Trap on Integer Condition Codes Instruction
	//opcode cond operation icc test
	_TA_, // 1000 Trap Always 1
	_TN_, // 0000 Trap Never 0
	_TNE_, // 1001 Trap on Not Equal not Z
	_TE_, // 0001 Trap on Equal Z
	_TG_, // 1010 Trap on Greater not (Z or (N xor V))
	_TLE_, // 0010 Trap on Less or Equal Z or (N xor V)
	_TGE_, // 1011 Trap on Greater or Equal not (N xor V)
	_TL_, // 0011 Trap on Less N xor V
	_TGU_, // 1100 Trap on Greater Unsigned not (C or Z)
	_TLEU_, // 0100 Trap on Less or Equal Unsigned (C or Z)
	_TCC_, // 1101 Trap on Carry Clear (Greater than or Equal, Unsigned) not C
	_TCS_, // 0101 Trap on Carry Set (Less Than, Unsigned) C
	_TPOS_, // 1110 Trap on Positive not N
	_TNEG_, // 0110 Trap on Negative N
	_TVC_, // 1111 Trap on Overflow Clear not V
	_TVS_, // 0111 Trap on Overflow Set V

	//Read State Register
	//opcode op3 rs1 operation
	_RDY_, // 101000 0 Read Y Register
	_RDASR_, // 101000 1 - 15 Read Ancillary State Register (reserved)
	_RDPSR_, // 101001 reserved Read Processor State Register
	_RDWIM_, // 101010 reserved Read Window Invalid Mask Register
	_RDTBR_, // 101011 reserved Read Trap Base Register

	//Write State Register
	//opcode op3 rd operation
	_WRY_, // 110000 0 Write Y Register
	_WRASR_, // 110000 1 - 15 Write Ancillary State Register (reserved)
	_WRPSR_, // 110001 reserved Write Processor State Register
	_WRWIM_, // 110010 reserved Write Window Invalid Mask Register
	_WRTBR_, // 110011 reserved Write Trap Base Register

	//STBAR Instruction
	_STBAR_, // 101000 Store Barrier

	//Unimplemented Instruction
	//opcode op op2 operation
	_UNIMP_, // 00 000 Unimplemented

	//Flush Instruction
	//Memory
	_FLUSH_, // 111011 Flush Instruction Memory

	//Convert Integer to Floating
	//point   opcode opf operation
	_FiTOs_, // 011000100 Convert Integer to Single
	_FiTOd_, // 011001000 Convert Integer to Double
	_FiTOq_, // 011001100 Convert Integer to Quad

	////Convert Floating point to
	//Integer   opcode opf operation
	_FsTOi_, // 011010001 Convert Single to Integer
	_FdTOi_, // 011010010 Convert Double to Integer
	_FqTOi_, // 011010011 Convert Quad to Integer

	//Convert Between Floatingpoint
	//Formats   opcode opf operation
	_FsTOd_, // 011001001 Convert Single to Double
	_FsTOq_, // 011001101 Convert Single to Quad
	_FdTOs_, // 011000110 Convert Double to Single
	_FdTOq_, // 011001110 Convert Double to Quad
	_FqTOs_, // 011000111 Convert Quad to Single
	_FqTOd_, // 011001011 Convert Quad to Double

	//Floating-point Move
	//  opcode opf operation
	_FMOVs_, // 000000001 Move
	_FNEGs_, // 000000101 Negate
	_FABSs_, // 000001001 Absolute Value

	//Floating-point Square Root
	//  opcode opf operation
	_FSQRTs_, // 000101001 Square Root Single
	_FSQRTd_, // 000101010 Square Root Double
	_FSQRTq_, // 000101011 Square Root Quad

	//Floating-point Add and
	//Subtract   opcode opf operation
	_FADDs_, // 001000001 Add Single
	_FADDd_, // 001000010 Add Double
	_FADDq_, // 001000011 Add Quad
	_FSUBs_, // 001000101 Subtract Single
	_FSUBd_, // 001000110 Subtract Double
	_FSUBq_, // 001000111 Subtract Quad

	//Floating-point Multiply and Divide
	//opcode opf operation
	_FMULs_, // 001001001 Multiply Single
	_FMULd_, // 001001010 Multiply Double
	_FMULq_, // 001001011 Multiply Quad
	_FsMULd_, // 001101001 Multiply Single to Double
	_FdMULq_, // 001101110 Multiply Double to Quad
	_FDIVs_, // 001001101 Divide Single
	_FDIVd_, // 001001110 Divide Double
	_FDIVq_, // 001001111 Divide Quad

	//Floating-point Compare
	//opcode opf operation
	_FCMPs_, // 001010001 Compare Single
	_FCMPd_, // 001010010 Compare Double
	_FCMPq_, // 001010011 Compare Quad
	_FCMPEs_, // 001010101 Compare Single and Exception if Unordered
	_FCMPEd_, // 001010110 Compare Double and Exception if Unordered
	_FCMPEq_, // 001010111 Compare Quad and Exception if Unordered

	//
	// 64-bit FP SIMD
	//   (each will do 2x Single-precision ops)
	_VFADD32_,	// new op-code (op=2, op3=0x34, opf=0x142)
	_VFADD16_,	// new op-code (op=2, op3=0x34, opf=0x143)
	_VFSUB32_,	// new op-code (op=2, op3=0x34, opf=0x144)
	_VFSUB16_,	// new op-code (op=2, op3=0x34, opf=0x145)
	_VFMUL32_,	// new op-code (op=2, op3=0x34, opf=0x146)
	_VFMUL16_,	// new op-code (op=2, op3=0x34, opf=0x147)
	
	// 64-bit SIMD conversion between i16 and half precision
	_VFI16TOH_,	// new op-code (op=2, op3=0x34, opf=0x148)
	_VFHTOI16_,	// new op-code (op=2, op3=0x34, opf=0x149)

	_FADDREDUCE16_, // new op-code (op=2, op3=0x34, opf=0x150)

	// half-precision to single and vice-versa
	_FSTOH_, 	// new op-code (op=2, op3=0x34, opf=0x151)
	_FHTOS_, 	// new op-code (op=2, op3=0x34, opf=0x152)
	
	// 64-bit IU SIMD instructions.
	_VADDD8_, 	_VADDD16_, 	_VADDD32_, 	
	_VSUBD8_, 	_VSUBD16_, 	_VSUBD32_,
	_VUMULD8_,	_VUMULD16_,	_VUMULD32_,	
	_VSMULD8_,	_VSMULD16_, 	_VSMULD32_,

	// byte,half-word reduce instructions
	_ADDDREDUCE8_,		// new op-code
	_ADDDREDUCE16_,		// new op-code
	_ORDREDUCE8_,		// new op-code
	_ORDREDUCE16_,		// new op-code
	_ANDDREDUCE8_,		// new op-code
	_ANDDREDUCE16_,		// new op-code
	_XORDREDUCE8_,		// new op-code
	_XORDREDUCE16_,		// new op-code

	// byte-pos
	_ZBYTEDPOS_,	// new op-code

	//Coprocessor Operate
	_CPop1_, // 110110 Coprocessor Operate
	_CPop2_, // 110111 Coprocessor Operate
	_UNIMPLEMENTED_, //
	_UNASSIGNED_ //causes an exception

} Opcode;

typedef enum _InstructionType
{
	_CALL_INS_,
	_SETHI_INS_,
	_CC_INS_,
	_ARITH_LOGICAL_INS_,
	_SHIFT_INS_,
	_WRITE_STATE_REG_INS_,
	_JMPL_RETT_FLUSH_SAVE_RESTORE_INS_,
	_LOAD_STORE_INS_,
	_TICC_INS_,
	_FPop1_INS_,
	_FPop2_INS_,
	_REDUCE_INS_,
	_BYTEPOS_INS_,
	_UNKNOWN_

} InstructionType;

int is64BitAluInstr  (Opcode opcode);
int is64BitShiftInstr  (Opcode opcode);
int isByteReduceInstr(Opcode opcode);
int isBytePosInstr   (Opcode opcode);
int isSimdAluInstr   (Opcode opcode);
int isFpReduceInstr  (Opcode opcode);
int isFpHalfConvertInstr (Opcode opcode);
int isSimdFpHalfConvertInstr (Opcode opcode);
int isSimdFpuInstr   (Opcode opcode);
int isCswapInstr   (Opcode opcode);

#endif
