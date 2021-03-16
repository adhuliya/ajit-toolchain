#include <stdint.h>
#include "Opcodes.h"
#include "Ancillary.h"
#include "RegisterFile.h"
#include "Traps.h"

// Appendix F Page - 227
//
// Prime candidate to be moved to a VHDL implementation.
// The entire decode function should be implemented in one clock
// cycle, in a pipelined manner.
//
//
// Implement a functionLibrary element ajitSp32InstrDecode
// 
//
uint32_t decodeInstruction(uint32_t instruction, Opcode *code, uint32_t trap_vector, uint8_t *rs1, uint8_t *rs2, 
				uint16_t *simm13, uint8_t *shcnt, uint32_t *disp30, uint32_t *disp22, uint8_t *software_trap, 
				uint8_t *dest_reg, uint8_t *i, uint8_t *a, uint8_t *asi, InstructionType *inst_type, uint8_t *fp_uimp_inst)
{


	Opcode opcode = _UNASSIGNED_;
	InstructionType itype = _UNKNOWN_;
	uint32_t tv = trap_vector;

	//
	// Appendix C.4 Page - 156
	//
	uint8_t op = getSlice32(instruction, 31, 30);
	uint8_t op2 = getSlice32(instruction, 24, 22);
	uint8_t op3 = getSlice32(instruction, 24, 19);
	uint16_t opf = getSlice32(instruction, 13, 5);
	uint16_t opc = getSlice32(instruction, 13, 5);
	*asi = getSlice32(instruction, 12, 5);
	*i = getBit32(instruction, 13);
	uint8_t rd = getSlice32(instruction, 29, 25);
	*dest_reg = rd;
	*a = getBit32(instruction, 29);
	uint8_t cond = getSlice32(instruction, 28, 25);
	*rs1 = getSlice32(instruction, 18, 14);
	*rs2 = getSlice32(instruction, 4, 0);
	*simm13 = getSlice32(instruction, 12, 0);
	*shcnt = getSlice32(instruction, 4, 0);
	*disp30 = getSlice32(instruction, 29, 0);
	*disp22 = getSlice32(instruction, 21, 0);
	*software_trap = getSlice32(instruction, 6, 0);

	//
	// Appendix F Page - 227
	//
	uint32_t imm22 = *disp22;
	uint8_t op_0 = (op == 0);
	uint8_t op_1 = (op == 1);
	uint8_t op_2 = (op == 2);
	uint8_t op_3 = (op == 3);

	if(op_1)
	{
		opcode = _CALL_;
		itype = _CALL_INS_ ;
	}

	uint8_t op2_0 = (op2 == 0);
	uint8_t op2_2 = (op2 == 2);
	uint8_t op2_4 = (op2 == 4);
	uint8_t op2_6 = (op2 == 6);
	uint8_t op2_7 = (op2 == 7);

	if(op_0 && op2_0) 
	{
		opcode = _UNIMP_ ;
	}

	uint8_t is_nop = (rd == 0) && (imm22 == 0);

	if (op_0 && op2_4 && is_nop) opcode = _NOP_ ;
	if (op_0 && op2_4 && !is_nop) opcode = _SETHI_ ;
	if (op_0 && op2_4 && !is_nop) itype= _SETHI_INS_;

	int8_t bicc = op_0 && op2_2;

	uint8_t cond_0 = (cond == 0);
	uint8_t cond_1 = (cond == 1);
	uint8_t cond_2 = (cond == 2);
	uint8_t cond_3 = (cond == 3);
	uint8_t cond_4 = (cond == 4);
	uint8_t cond_5 = (cond == 5);
	uint8_t cond_6 = (cond == 6);
	uint8_t cond_7 = (cond == 7);
	uint8_t cond_8 = (cond == 8);
	uint8_t cond_9 = (cond == 9);
	uint8_t cond_a = (cond == 0xA);
	uint8_t cond_b = (cond == 0xB);
	uint8_t cond_c = (cond == 0xC);
	uint8_t cond_d = (cond == 0xD);
	uint8_t cond_e = (cond == 0xE);
	uint8_t cond_f = (cond == 0xF);

	if(bicc)
	{
		if (cond_0 ) opcode = _BN_ ;
		else if(cond_1 ) opcode = _BE_ ;
		else if(cond_2 ) opcode = _BLE_ ;
		else if(cond_3 ) opcode = _BL_ ;
		else if(cond_4 ) opcode = _BLEU_ ;
		else if(cond_5 ) opcode = _BCS_ ;
		else if(cond_6 ) opcode = _BNEG_ ;
		else if(cond_7 ) opcode = _BVS_ ;
		else if(cond_8 ) opcode = _BA_ ;
		else if(cond_9 ) opcode = _BNE_ ;
		else if(cond_a ) opcode = _BG_ ;
		else if(cond_b ) opcode = _BGE_ ;
		else if(cond_c ) opcode = _BGU_ ;
		else if(cond_d ) opcode = _BCC_ ;
		else if(cond_e ) opcode = _BPOS_ ;
		else if(cond_f ) opcode = _BVC_ ;
	}

	int8_t fbfcc = op_0 && op2_6;

	if(fbfcc)
	{
		if ( cond_0 ) opcode = _FBN_ ;
		else if ( cond_1 ) opcode = _FBNE_ ;
		else if ( cond_2 ) opcode = _FBLG_ ;
		else if ( cond_3 ) opcode = _FBUL_ ;
		else if ( cond_4 ) opcode = _FBL_ ;
		else if ( cond_5 ) opcode = _FBUG_ ;
		else if ( cond_6 ) opcode = _FBG_ ;
		else if ( cond_7 ) opcode = _FBU_ ;
		else if ( cond_8 ) opcode = _FBA_ ;
		else if ( cond_9 ) opcode = _FBE_ ;
		else if ( cond_a ) opcode = _FBUE_ ;
		else if ( cond_b ) opcode = _FBGE_ ;
		else if ( cond_c ) opcode = _FBUGE_ ;
		else if ( cond_d ) opcode = _FBLE_ ;
		else if ( cond_e ) opcode = _FBULE_ ;
		else if ( cond_f ) opcode = _FBO_ ;
	}

	int8_t cbccc = op_0 && op2_7;

	if(cbccc)
	{
		if(cond_0 ) opcode = _CBN_ 	;
		else if(cond_1 ) opcode = _CB123_ 	;
		else if(cond_2 ) opcode = _CB12_ 	;
		else if(cond_3 ) opcode = _CB13_ 	;
		else if(cond_4 ) opcode = _CB1_ 	;
		else if(cond_5 ) opcode = _CB23_ 	;
		else if(cond_6 ) opcode = _CB2_ 	;
		else if(cond_7 ) opcode = _CB3_ 	;
		else if(cond_8 ) opcode = _CBA_ 	;
		else if(cond_9 ) opcode = _CB0_ 	;
		else if(cond_a ) opcode = _CB03_ 	;
		else if(cond_b ) opcode = _CB02_ 	;
		else if(cond_c ) opcode = _CB023_ 	;
		else if(cond_d ) opcode = _CB01_ 	;
		else if(cond_e ) opcode = _CB013_ 	;
		else if(cond_f ) opcode = _CB012_ 	;
	}

	if(bicc || fbfcc || cbccc) itype=_CC_INS_;

	uint8_t op3_30 = getSlice8(op3, 3, 0);
	uint8_t op3_54 = getSlice8(op3, 5, 4);

	uint8_t op3_30_0 = (op3_30 == 0);
	uint8_t op3_30_1 = (op3_30 == 1);
	uint8_t op3_30_2 = (op3_30 == 2);
	uint8_t op3_30_3 = (op3_30 == 3);
	uint8_t op3_30_4 = (op3_30 == 4);
	uint8_t op3_30_5 = (op3_30 == 5);
	uint8_t op3_30_6 = (op3_30 == 6);
	uint8_t op3_30_7 = (op3_30 == 7);
	uint8_t op3_30_8 = (op3_30 == 8);
	uint8_t op3_30_9 = (op3_30 == 9);
	uint8_t op3_30_a = (op3_30 == 0xA);
	uint8_t op3_30_b = (op3_30 == 0xB);
	uint8_t op3_30_c = (op3_30 == 0xC);
	uint8_t op3_30_d = (op3_30 == 0xD);
	uint8_t op3_30_e = (op3_30 == 0xE);
	uint8_t op3_30_f = (op3_30 == 0xF);

	uint8_t op3_54_0 = (op3_54 == 0);
	uint8_t op3_54_1 = (op3_54 == 1);
	uint8_t op3_54_2 = (op3_54 == 2);
	uint8_t op3_54_3 = (op3_54 == 3);

	uint8_t f3_0 = (op_2 && op3_54_0); // Column 0 of Table F-3
	uint8_t f3_1 = (op_2 && op3_54_1); // Column 1 of Table F-3
	uint8_t f3_2 = (op_2 && op3_54_2); // Column 2 of Table F-3
	uint8_t f3_3 = (op_2 && op3_54_3); // Column 3 of Table F-3

	if(f3_0)
	{
		if(op3_30_0 ) opcode = _ADD_ 	;
		else if(op3_30_1 ) opcode = _AND_ 	;
		else if(op3_30_2 ) opcode = _OR_ 	;
		else if(op3_30_3 ) opcode = _XOR_ 	;
		else if(op3_30_4 ) opcode = _SUB_ 	;
		else if(op3_30_5 ) opcode = _ANDN_ 	;
		else if(op3_30_6 ) opcode = _ORN_ 	;
		else if(op3_30_7 ) opcode = _XNOR_ 	;
		else if(op3_30_8 ) opcode = _ADDX_ 	;
		else if(op3_30_a ) opcode = _UMUL_ 	;
		else if(op3_30_b ) opcode = _SMUL_ 	;
		else if(op3_30_c ) opcode = _SUBX_ 	;
		else if(op3_30_e ) opcode = _UDIV_ 	;
		else if(op3_30_f ) opcode = _SDIV_ 	;
	}

	if(f3_1)
	{
		if(op3_30_0 ) opcode = _ADDcc_ 	;
		else if(op3_30_1 ) opcode = _ANDcc_ 	;
		else if(op3_30_2 ) opcode = _ORcc_ 	;
		else if(op3_30_3 ) opcode = _XORcc_ 	;
		else if(op3_30_4 ) opcode = _SUBcc_ 	;
		else if(op3_30_5 ) opcode = _ANDNcc_ ;
		else if(op3_30_6 ) opcode = _ORNcc_ 	;
		else if(op3_30_7 ) opcode = _XNORcc_ ;
		else if(op3_30_8 ) opcode = _ADDXcc_ ;
		else if(op3_30_a ) opcode = _UMULcc_ ;
		else if(op3_30_b ) opcode = _SMULcc_ ;
		else if(op3_30_c ) opcode = _SUBXcc_ ;
		else if(op3_30_e ) opcode = _UDIVcc_ ;
		else if(op3_30_f ) opcode = _SDIVcc_ ;
	}

	uint8_t stbar = ((*rs1 == 15) && (rd == 0));

	if(f3_2)
	{
		if( op3_30_0 ) opcode = _TADDcc_ 	;
		else if( op3_30_1 ) opcode = _TSUBcc_ 	;
		else if( op3_30_2 ) opcode = _TADDccTV_ ;
		else if( op3_30_3 ) opcode = _TSUBccTV_ ;
		else if( op3_30_4 ) opcode = _MULScc_ 	;
		else if( op3_30_5 ) opcode = _SLL_ 	;
		else if( op3_30_6 ) opcode = _SRL_ 	;
		else if( op3_30_7 ) opcode = _SRA_ 	;

		else if( op3_30_8 && (*rs1 == 0) ) opcode = _RDY_ 		;
		else if( op3_30_8 && stbar) opcode= _STBAR_ 			;
		else if( op3_30_8 && !stbar && !(*rs1 == 0) ) opcode = _RDASR_ 	;
		else if( op3_30_9 ) opcode = _RDPSR_ 	;
		else if( op3_30_a ) opcode = _RDWIM_ 	;
		else if( op3_30_b ) opcode = _RDTBR_ 	;
	}

	uint8_t fpop1 = (f3_3 && op3_30_4);
	uint8_t fpop2 = (f3_3 && op3_30_5);
	uint8_t ticc = (f3_3 && op3_30_a);

	if(fpop1 ) itype = _FPop1_INS_ ;
	else if(fpop2 ) itype = _FPop2_INS_ ;
	else if(ticc  ) itype = _TICC_INS_  ;

	if(f3_3)
	{
		if(op3_30_0 && !(rd == 0) ) opcode= _WRASR_ 	;
		else if(op3_30_0 && (rd == 0)  ) opcode= _WRY_ 	;	
		else if(op3_30_1 ) opcode = _WRPSR_ 		;
		else if(op3_30_2 ) opcode = _WRWIM_ 		;
		else if(op3_30_3 ) opcode = _WRTBR_ 		;
		else if(op3_30_6 ) opcode = _CPop1_ 		;
		else if(op3_30_7 ) opcode = _CPop2_ 		;
		else if(op3_30_8 ) opcode = _JMPL_ 		;
		else if(op3_30_9 ) opcode = _RETT_ 		;
		else if(op3_30_b ) opcode = _FLUSH_ 		;
		else if(op3_30_c ) opcode = _SAVE_ 		;
		else if(op3_30_d ) opcode = _RESTORE_ 		;
	}

	if(fpop1)
	{
		     if(opf == 0x1)  opcode = _FMOVs_ ;
		else if(opf == 0x5)  opcode = _FNEGs_ ;
		else if(opf == 0x9)  opcode = _FABSs_ ;
		else if(opf == 0x29) opcode = _FSQRTs_;
		else if(opf == 0x2A) opcode = _FSQRTd_;
		else if(opf == 0x2B) opcode = _FSQRTq_;
		else if(opf == 0x41) opcode = _FADDs_ ;
		else if(opf == 0x42) opcode = _FADDd_ ;
		else if(opf == 0x43) opcode = _FADDq_ ;
		else if(opf == 0x45) opcode = _FSUBs_ ;
		else if(opf == 0x46) opcode = _FSUBd_ ;
		else if(opf == 0x47) opcode = _FSUBq_ ;
		else if(opf == 0x49) opcode = _FMULs_ ;
		else if(opf == 0x4A) opcode = _FMULd_ ;
		else if(opf == 0x4B) opcode = _FMULq_ ;
		else if(opf == 0x4D) opcode = _FDIVs_ ;
		else if(opf == 0x4E) opcode = _FDIVd_ ;
		else if(opf == 0x4F) opcode = _FDIVq_ ;
		else if(opf == 0x69) opcode = _FsMULd_;
		else if(opf == 0x6E) opcode = _FdMULq_;
		else if(opf == 0xC4) opcode = _FiTOs_ ;
		else if(opf == 0xC6) opcode = _FdTOs_ ;
		else if(opf == 0xC7) opcode = _FqTOs_ ;
		else if(opf == 0xC8) opcode = _FiTOd_ ;
		else if(opf == 0xC9) opcode = _FsTOd_ ;
		else if(opf == 0xCB) opcode = _FqTOd_ ;
		else if(opf == 0xCC) opcode = _FiTOq_ ;
		else if(opf == 0xCD) opcode = _FsTOq_ ;
		else if(opf == 0xCE) opcode = _FdTOq_ ;
		else if(opf == 0xD1) opcode = _FsTOi_ ;
		else if(opf == 0xD2) opcode = _FdTOi_ ;
		else if(opf == 0xD3) opcode = _FqTOi_ ;
	}

	if(fpop2)
	{
		     if (opf == 0x51) opcode = _FCMPs_  ;
		else if (opf == 0x52) opcode = _FCMPd_  ;
		else if (opf == 0x53) opcode = _FCMPq_  ;
		else if (opf == 0x55) opcode = _FCMPEs_ ;
		else if (opf == 0x56) opcode = _FCMPEd_ ;
		else if (opf == 0x57) opcode = _FCMPEq_ ;
	}

	if(ticc)
	{
		     if(cond_0) opcode = _TN_ 	;
		else if(cond_1) opcode = _TE_ 	;
		else if(cond_2) opcode = _TLE_ 	;
		else if(cond_3) opcode = _TL_ 	;
		else if(cond_4) opcode = _TLEU_ ;
		else if(cond_5) opcode = _TCS_ 	;
		else if(cond_6) opcode = _TNEG_ ;
		else if(cond_7) opcode = _TVS_ 	;
		else if(cond_8) opcode = _TA_ 	;
		else if(cond_9) opcode = _TNE_ 	;
		else if(cond_a) opcode = _TG_ 	;
		else if(cond_b) opcode = _TGE_ 	;
		else if(cond_c) opcode = _TGU_ 	;
		else if(cond_d) opcode = _TCC_ 	;
		else if(cond_e) opcode = _TPOS_ ;
		else if(cond_f) opcode = _TVC_ 	;
	}

	uint8_t f4_0 = (op_3 && op3_54_0);

	if(f4_0)
	{
		     if(op3_30_0 ) opcode = _LD_ 	;
		else if(op3_30_1 ) opcode = _LDUB_ 	;
		else if(op3_30_2 ) opcode = _LDUH_ 	;
		else if(op3_30_3 ) opcode = _LDD_ 	;
		else if(op3_30_4 ) opcode = _ST_ 	;
		else if(op3_30_5 ) opcode = _STB_ 	;
		else if(op3_30_6 ) opcode = _STH_ 	;
		else if(op3_30_7 ) opcode = _STD_ 	;
		else if(op3_30_9 ) opcode = _LDSB_ 	;
		else if(op3_30_a ) opcode = _LDSH_ 	;
		else if(op3_30_d ) opcode = _LDSTUB_ 	;
		else if(op3_30_f ) opcode = _SWAP_ 	;
	}

	uint8_t f4_1 = (op_3 && op3_54_1);
	if (f4_1)
	{
		     if(op3_30_0 ) opcode = _LDA_ 	;
		else if(op3_30_1 ) opcode = _LDUBA_ 	;
		else if(op3_30_2 ) opcode = _LDUHA_ 	;
		else if(op3_30_3 ) opcode = _LDDA_ 	;
		else if(op3_30_4 ) opcode = _STA_ 	;
		else if(op3_30_5 ) opcode = _STBA_ 	;
		else if(op3_30_6 ) opcode = _STHA_ 	;
		else if(op3_30_7 ) opcode = _STDA_ 	;
		else if(op3_30_9 ) opcode = _LDSBA_ 	;
		else if(op3_30_a ) opcode = _LDSHA_ 	;
		else if(op3_30_d ) opcode = _LDSTUBA_ 	;
		else if(op3_30_f ) opcode = _SWAPA_ 	;
	}

	uint8_t f4_2 = (op_3 && op3_54_2);
	if(f4_2)
	{
		     if(op3_30_0) opcode = _LDF_ 	;
		else if(op3_30_1) opcode = _LDFSR_ 	;
		else if(op3_30_3) opcode = _LDDF_ 	;
		else if(op3_30_4) opcode = _STF_ 	;
		else if(op3_30_5) opcode = _STFSR_ 	;
		else if(op3_30_6) opcode = _STDFQ_ 	;
		else if(op3_30_7) opcode = _STDF_ 	;
	}

	uint8_t f4_3 = (op_3 && op3_54_3);
	if(f4_3)
	{
		     if(op3_30_0) opcode = _LDC_ 	;
		else if(op3_30_1) opcode = _LDCSR_ 	;
		else if(op3_30_3) opcode = _LDDC_ 	;
		else if(op3_30_4) opcode = _STC_ 	;
		else if(op3_30_5) opcode = _STCSR_ 	;
		else if(op3_30_6) opcode = _STDCQ_ 	;
		else if(op3_30_7) opcode = _STDC_ 	;
	}

	if 	(f3_0 || f3_1 || (f3_2 && (op3_30_0 || op3_30_1 || op3_30_2 || op3_30_3 || op3_30_4))) 	itype =_ARITH_LOGICAL_INS_;
	else if (f3_2 && (op3_30_5 || op3_30_6 || op3_30_7)) 						itype =_SHIFT_INS_;
	else if (f3_3 && (op3_30_0 || op3_30_1 || op3_30_2 || op3_30_3)) 				itype =_WRITE_STATE_REG_INS_ ;
	else if (f3_3 && (op3_30_8 || op3_30_9 || op3_30_b || op3_30_c || op3_30_d))			itype =_JMPL_RETT_FLUSH_SAVE_RESTORE_INS_ ;
	else if (op_3 ) itype = _LOAD_STORE_INS_ ;


	uint8_t is_alternate = (((op >= _LDSBA_) && (op <= _LDDA_)) || ((op >= _STBA_) && (op <= _STDA_)) || (op == _LDSTUBA_) || (op == _SWAPA_));
	if  (is_alternate && i) tv = setBit32(tv, _TRAP_, 1);
	if  (is_alternate && i) tv = setBit32(tv, _ILLEGAL_INSTRUCTION_, 1);

	 /* Unimplemented Instruction Exception
	  * Added by: Ashfaque Ahammed
	  * when ever following instructions occurs it generate a unimplemented FPop trap. That part is on SparcCore.c
	  */
         if(opcode == _FiTOq_ || opcode == _FqTOi_ || opcode == _FsTOq_ || opcode == _FdTOq_ || opcode == _FqTOd_ || opcode == _FqTOs_
                  || opcode == _FSQRTq_ || opcode == _FADDq_ || opcode == _FSUBq_ || opcode == _FMULq_ || opcode == _FDIVq_
                  || opcode == _FCMPq_ || opcode == _FCMPEq_ || opcode == _FdMULq_) {
                         *fp_uimp_inst = 1;
         }

	*code = opcode;
	*inst_type = itype;

	return tv;
}


// 
// Explore mapping this to a pipelined Aa module
// ajitSp32ReadOperand.
//
// potential candidate for direct implementation into 
// VHDL and mapping to a functionLibray element in
// ajitSp32ReadOperand
//
void readOperands(Opcode opcode, uint8_t rs1, uint8_t rs2, uint8_t rd, uint16_t simm13, uint8_t shcnt, uint32_t disp30,
		uint32_t disp22, uint8_t software_trap, uint8_t i, uint32_t *operand2_3, uint32_t *operand2_2, uint32_t *operand2_1,
		uint32_t *operand2_0, uint32_t *operand1_3, uint32_t *operand1_2, uint32_t *operand1_1, uint32_t *operand1_0, InstructionType instr_type,
		uint8_t cwp, uint32_t *data1, uint32_t *data0, uint8_t *fp_invalid_reg)
{
	uint32_t oprnd1_0, oprnd1_1, oprnd1_2, oprnd1_3;
	uint32_t oprnd2_0, oprnd2_1, oprnd2_2, oprnd2_3;
	uint32_t imm22 = disp22;
	uint32_t d1, d0;

	int invalid_rs1, invalid_rs2, invalid_rd;
	invalid_rs1 = invalid_rs2 = invalid_rd = 0;

	d1 = d0 = 0;

	oprnd1_0 = oprnd1_1 = oprnd1_2 = oprnd1_3 = 0;
	oprnd2_0 = oprnd2_1 = oprnd2_2 = oprnd2_3 = 0;

	     if(instr_type == _CALL_INS_)  oprnd1_0 = (disp30 << 2);
	else if(instr_type == _SETHI_INS_) oprnd1_0 =  imm22 ;
	else if(instr_type == _CC_INS_)    oprnd1_0 =  disp22 ;

	uint8_t std_oprnd_1 = ((instr_type == _ARITH_LOGICAL_INS_) || (instr_type == _SHIFT_INS_) || (instr_type == _WRITE_STATE_REG_INS_) || (instr_type
			== _JMPL_RETT_FLUSH_SAVE_RESTORE_INS_) || (instr_type == _TICC_INS_) || (instr_type == _LOAD_STORE_INS_));
	uint8_t std_oprnd_2 = (std_oprnd_1 && (i == 0));
	uint8_t std_imm_oprnd_2 = (((instr_type == _ARITH_LOGICAL_INS_) || (instr_type == _WRITE_STATE_REG_INS_) || (instr_type == _JMPL_RETT_FLUSH_SAVE_RESTORE_INS_)
			|| (instr_type == _LOAD_STORE_INS_)) && (i == 1));

	if (std_oprnd_1 ) oprnd1_0 = readRegister(rs1, cwp);

		if (std_oprnd_2 ) 	oprnd2_0 = readRegister(rs2, cwp);
	else 	if (std_imm_oprnd_2) 	oprnd2_0 = signExtend(simm13, 12) ;
	else 	if ((instr_type == _SHIFT_INS_) && (i == 1)) oprnd2_0 =  shcnt ;
	else 	if ((instr_type == _TICC_INS_) && (i == 1)) oprnd2_0 = signExtend(software_trap, 6);

	
	switch(opcode)
	{
		case _STF_ 	: {d0 = readFRegister(rd);		break;};
		case _STDF_ 	: {
					  d0 = readFRegister(rd & 0x1E);
					  d1 = readFRegister(rd | 1);
					  break;
				  };
		
		case _STD_ 	:
		case _STDA_	:
				  {
					  d0=readRegister((rd & 0x1E), cwp); 
					  d1=readRegister((rd | 1), cwp);
					  break;
				  };

		case _ST_ 	:
		case _STA_ 	:
		case _STH_ 	:
		case _STHA_ 	:
		case _STB_ 	:
		case _STBA_ 	: {d0=readRegister(rd, cwp); break;};

		case _SWAP_ 	:
		case _SWAPA_ 	: {d0=readRegister(rd, cwp); break;};
		default :	break;
	}

	
	// Operands for FPop1 and FPop2 (Appendix - C.10 Page 184)
	//
	//
	// Double Precision
	//
	uint8_t rs1_e = setBit8(rs1, 0, 0);
	uint8_t rs1_o = setBit8(rs1, 0, 1);
	uint8_t rs2_e = setBit8(rs2, 0, 0);
	uint8_t rs2_o = setBit8(rs2, 0, 1);

	//
	// Quad Precision
	//
	uint8_t rs1_ee = setBit8(rs1, 0, 0);
	rs1_ee = setBit8(rs1_ee, 1, 0);
	uint8_t rs1_eo = setBit8(rs1, 0, 1);
	rs1_eo = setBit8(rs1_eo, 1, 0);
	uint8_t rs1_oe = setBit8(rs1, 0, 0);
	rs1_oe = setBit8(rs1_oe, 1, 1);
	uint8_t rs1_oo = setBit8(rs1, 0, 1);
	rs1_oo = setBit8(rs1_oo, 1, 1);
	uint8_t rs2_ee = setBit8(rs2, 0, 0);
	rs2_ee = setBit8(rs2_ee, 1, 0);
	uint8_t rs2_eo = setBit8(rs2, 0, 1);
	rs2_eo = setBit8(rs2_eo, 1, 0);
	uint8_t rs2_oe = setBit8(rs2, 0, 0);
	rs2_oe = setBit8(rs2_oe, 1, 1);
	uint8_t rs2_oo = setBit8(rs2, 0, 1);
	rs2_oo = setBit8(rs2_oo, 1, 1);

	uint8_t ss = (opcode == _FiTOs_ || opcode == _FiTOd_ || opcode == _FiTOq_ || opcode == _FsTOi_ || opcode == _FsTOd_ || opcode == _FsTOq_ || opcode == _FMOVs_
			|| opcode == _FNEGs_ || opcode == _FABSs_ || opcode == _FSQRTs_); // Single operand Single precision
	uint8_t sd = (opcode == _FdTOi_ || opcode == _FdTOs_ || opcode == _FdTOq_ || opcode == _FSQRTd_); // Single operand Double precision
	uint8_t sq = (opcode == _FqTOi_ || opcode == _FqTOs_ || opcode == _FqTOd_ || opcode == _FSQRTq_); // Single operand Quad precision
	uint8_t ds = (opcode == _FADDs_ || opcode == _FSUBs_ || opcode == _FMULs_ || opcode == _FDIVs_ || opcode == _FsMULd_ || opcode == _FCMPs_
			|| opcode == _FCMPEs_); // Double operand Single precision
	uint8_t dd = (opcode == _FADDd_ || opcode == _FSUBd_ || opcode == _FMULd_ || opcode == _FDIVd_ || opcode == _FdMULq_ || opcode == _FCMPd_
			|| opcode == _FCMPEd_); // Double operand Double precision
	uint8_t dq = (opcode == _FADDq_ || opcode == _FSUBq_ || opcode == _FMULq_ || opcode == _FDIVq_ || opcode == _FCMPq_ || opcode == _FCMPEq_); // Double operand Quad precision


	/*
	 * Chekking for invalid_fp_register_trap
	 * Trap is generated when one (or more) operands
	 * misaligned, that is if double-precision register number
	 * is not 0 mod 2.
	 * Added by: Ashfaque Ahammed
	 */
	  //chekking source register 1
	 if(opcode == _FADDd_ || opcode == _FSUBd_ || opcode == _FMULd_ || opcode == _FDIVd_ || opcode == _FCMPd_ || opcode == _FCMPEd_) {
			invalid_rs1 = rs1_e % 2;
	 }
	 // Chekking source register 2
	 if(opcode == _FADDd_ || opcode == _FSUBd_ || opcode == _FMULd_ || opcode == _FDIVd_ || opcode == _FCMPd_ || opcode == _FCMPEd_
	        || opcode == _FdTOi_ || opcode == _FdTOs_ || opcode == _FSQRTd_) {
			invalid_rs2 = rs2_e % 2;
	}
	// CHekking destination register
	 if(opcode == _FADDd_ || opcode == _FSUBd_ || opcode == _FMULd_ || opcode == _FsMULd_ || opcode == _FDIVd_
	        || opcode == _FiTOd_ || opcode == _FsTOd_ || opcode == _FSQRTd_) {
			invalid_rd = rd % 2;
	}

	if(invalid_rs1 || invalid_rs2 || invalid_rd) {
		*fp_invalid_reg = 1;
	}
	/******************************************************************************/


	 if(ds) oprnd1_0 = readFRegister(rs1)    ;
	 if(dd) oprnd1_0 = readFRegister(rs1_o)  ;
	 if(dq) oprnd1_0 = readFRegister(rs1_oo) ;
	 if(dd) oprnd1_1 = readFRegister(rs1_e)  ;
	 if(dq) oprnd1_1 = readFRegister(rs1_oe) ;
	 if(dq) oprnd1_2 = readFRegister(rs1_eo) ;
	 if(dq) oprnd1_3 = readFRegister(rs1_ee) ;

	 if (ss || ds) oprnd2_0 = readFRegister(rs2)    ;
	 if (sd || dd) oprnd2_0 = readFRegister(rs2_o)  ;
	 if (sq || dq) oprnd2_0 = readFRegister(rs2_oo) ;
	 if (sd || dd) oprnd2_1 = readFRegister(rs2_e)  ;
	 if (sq || dq) oprnd2_1 = readFRegister(rs2_oe) ;
	 if (sq || dq) oprnd2_2 = readFRegister(rs2_eo) ;
	 if (sq || dq) oprnd2_3 = readFRegister(rs2_ee) ;

	*operand2_3 = oprnd2_3;
	*operand2_2 = oprnd2_2;
	*operand2_1 = oprnd2_1;
	*operand2_0 = oprnd2_0;
	*operand1_3 = oprnd1_3;
	*operand1_2 = oprnd1_2;
	*operand1_1 = oprnd1_1;
	*operand1_0 = oprnd1_0;

	*data0 = d0;
	*data1 = d1;
}
