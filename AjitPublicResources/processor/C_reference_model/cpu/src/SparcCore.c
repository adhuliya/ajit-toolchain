//-------------------------------------------------------------------------
// Describes the cpu thread 
//-------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "SparcCore.h"
#include "Opcodes.h"
#include "Traps.h"
#include "Flags.h"
#include "Ancillary.h"
#include "RegisterFile.h"
#include "CpuInterface.h"
#include "Decode.h"
#include "Execute.h"
#include "monitorLogger.h"
#include "Pipes.h"
#include "StatsKeeping.h"
#include "CpuLogging.h"
#include "CpuHWserverInterface.h"



//variable to keep count of number of instructions fetched
long unsigned int num_ifetches=0;
uint32_t num_traps = 0;

long unsigned int num_instructions_executed=0;
void increment_instruction_count() { num_instructions_executed++; };
long get_instruction_count() { return num_instructions_executed; };


//period after which instruction fetch statistics are printed
long unsigned int IFETCH_PRINT_PERIOD = 100000; //100,000 hundred thousand
//For time-keeping during simulation:
#include <time.h>
time_t simulation_time;

void init( ProcessorState *s);
void clearStateUpdateFlags( ProcessorState *s);
void generateLogMessage( ProcessorState *s);
uint8_t isBranchInstruction(Opcode op, InstructionType type);
uint8_t isFloatCompareInstruction(Opcode op);
uint8_t fetchInstruction( uint8_t addr_space, uint32_t addr, uint32_t *inst, uint32_t* mmu_fsr);
uint32_t completeFPExecution( Opcode opcode, uint32_t operand2_3, uint32_t operand2_2, uint32_t operand2_1, 
			     	uint32_t operand2_0, uint32_t operand1_3, uint32_t operand1_2, uint32_t operand1_1, uint32_t operand1_0,
				uint8_t dest_reg, StatusRegisters *ptr,	uint32_t trap_vector);
void writeBackResult( uint8_t dest_reg, uint32_t result_h, uint32_t result_l, uint8_t flags, uint8_t cwp, uint32_t pc, StateUpdateFlags* reg_update_flags);




void cpu()
{
	ProcessorState s;
	Opcode opcode = _UNASSIGNED_;
	InstructionType inst_type = _UNKNOWN_;
	uint32_t operand1_0, operand1_1, operand1_2, operand1_3, operand2_0, operand2_1, operand2_2, operand2_3, result_h, result_l;
	uint8_t rd, asi, rs1, rs2, shcnt, software_trap, i, a;
	uint8_t flags;
	uint16_t simm13;
	uint32_t disp30, disp22;
	uint32_t data0, data1;
	operand1_0 = operand1_1 = operand1_2 = operand1_3 = operand2_0 = operand2_1 = operand2_2 = operand2_3 = 0;
	
	init(&s);
	
	inform_HW_server(GDB_INITIAL_STOP, &s,0);
	
	uint8_t interrupt_level = 0;
	while(1)
		// processor executes an endless loop..
	{
		
		simulation_time = time(NULL);
		
		// Get processor mode.
		uint8_t reset_mode = (s.mode == _RESET_MODE_);
		uint8_t error_mode = (s.mode == _ERROR_MODE_);
		uint8_t execute_mode = (s.mode == _EXECUTE_MODE_);

		//-----------------------------------------------
		//RESET MODE :
		//-----------------------------------------------
		//move to execute mode, and set the reset-trap.
		uint8_t reset_in1 = (getBpReset() == 0);
		uint8_t reset_in_reset = reset_mode && reset_in1;
		if(reset_in_reset)
		{
			 s.mode = _EXECUTE_MODE_ ;
			 s.trap_vector = setBit32(s.trap_vector, _TRAP_, 1) ;
			 s.trap_vector = setBit32(s.trap_vector, _RESET_TRAP_, 1) ;
		}
		
		
		
		//-----------------------------------------------
		//ERROR MODE :
		//-----------------------------------------------
		if(error_mode)
		{
			inform_HW_server(DOVAL_PROC_ENTERED_ERROR_MODE, &s,0);

			//If this is a simulation, stop simulation
			//upon encoutering error mode.
			//assert AJIT_to_ENV_error to halt simulation.
			fprintf(stderr,"Processor entered ERROR MODE at PC=0x%x\n ",s.status_reg.pc);
			if(getBit32(s.trap_vector, _TRAP_INSTRUCTION_)!=0 && s.ticc_trap_type==0)
			{
				fprintf(stderr,"Program exited upon a ta 0\n ");
			}
			else
			{
				fprintf(stderr,"Program exited with a trap type = 0x%x",s.ticc_trap_type);
			}
			//Insert a gdb breakpoint here to examine register
			//contents at the end of program execution
			//write_uint8("AJIT_to_ENV_error", 1);
			setPbError(1);

			do{ sleep(10); }while(1);
		}



		//If this is real hardware,
		//indicate somehow that the machine 
		//is in error mode and wait for 
		//reset to be asserted
		uint8_t reset_in2 = (getBpReset() == 1);
		uint8_t reset_in_error = error_mode && reset_in2;
		s.mode = (reset_in_error ? _RESET_MODE_ : s.mode);
		if(reset_in_error)setPbError(0);


		//----------------------------------------------
		//EXECUTE MODE
		//----------------------------------------------
		
						
		// If reset is observed in execute mode, re-initialize
		// the processor.
		uint8_t reset_in3 = (getBpReset() == 1);
		uint8_t reset_in_execute = execute_mode && reset_in3;
		s.mode = (reset_in_execute ? _RESET_MODE_ : s.mode);
		if(reset_in_execute || reset_in_error)
		{ 
			init(&s);

			inform_HW_server(GDB_RESET, &s,0);
		}


		// enable trap if !reset in execute and bit-5 of psr is 1.
		// bit-5 of psr is the enable-trap bit.
		uint8_t enable_trap = !reset_in_execute && (getBit32(s.status_reg.psr, 5) == 1);


		// Read external interrupts....
		if(s.mode == _EXECUTE_MODE_) 
			interrupt_level = getBpIRL();

		// check if interrupt level is greater than the minimum interrupt
		// level which the processor will accept (psr[11:8])
		uint8_t is_interrupt = enable_trap && ((interrupt_level == 15) || (interrupt_level > getSlice32(s.status_reg.psr, 11, 8)));

		if(is_interrupt)
		{
#ifdef DEBUG
			printf("\nCPU : Detected external interrupt when enable_trap=1. Interrupt_level = 0x%x",interrupt_level);
#endif

			s.trap_vector =  setBit32(s.trap_vector, _TRAP_, 1) ;
			s.interrupt_level = interrupt_level ;

		}

		uint8_t skip_trap_execution = !((s.mode == _EXECUTE_MODE_) && (getBit32(s.trap_vector, _TRAP_) == 1));

		if(!skip_trap_execution)
		{
			num_traps++;
			executeTrap(&(s.trap_vector), &(s.status_reg.psr), &(s.status_reg.tbr), &(s.interrupt_level), &(s.mode),
				s.ticc_trap_type, &(s.status_reg.pc), &(s.status_reg.npc));
			
			
			//Have gdb ignore windows overflow, underflow and timer traps,
			//as these are very frequent during kernel boot.
			uint8_t TRAP_TYPE= getSlice32(s.status_reg.tbr, 11, 4);
			if ( TRAP_TYPE!=0 && TRAP_TYPE!=5 && TRAP_TYPE!=6 && TRAP_TYPE!=0xA)
			{
				inform_HW_server(GDB_TRAP_OCCURED, &s,0);
			}
		}
		s.addr_space = (getBit32(s.status_reg.psr, 7) == 0) ? 8 : 9; // Supervisor bit

		uint8_t skip_fetch = !(s.mode == _EXECUTE_MODE_);
		// Only MAE trap from fetchInstruction
		uint8_t post_fetch_trap=0;
		s.mmu_fsr = 0;
		if(!skip_fetch)
		{
			
			//clear register-update flags 
			//(which maintain information for logging)
			//at the start of this instruction cycle.
			clearStateUpdateFlags(&s);
			s.reg_update_flags.pc = s.status_reg.pc;
			
			post_fetch_trap = fetchInstruction(s.addr_space, s.status_reg.pc, &(s.instruction),
								&(s.mmu_fsr)); //memory_read

			//================================
			//increment count of instructions fetched
			num_ifetches++;
			if(num_ifetches%IFETCH_PRINT_PERIOD==0)
			{
				fprintf(stderr,"\n==============================================\n");
				fprintf(stderr,"Real time = %s\n",(ctime(&simulation_time)));
				fprintf(stderr,"num_ifetches = %lu\n",num_ifetches);
				fprintf(stderr,"num_traps = %lu\n",num_traps);
				fprintf(stderr,"PC=0x%x\n",s.status_reg.pc);
				fprintf(stderr,"nPC=0x%x\n",s.status_reg.npc);
				fprintf(stderr,"trap_vector=0x%x\n",s.trap_vector);
				fprintf(stderr,"==============================================\n");
			}

			//================================

			s.trap_vector = setBit32(s.trap_vector, _MAE_, post_fetch_trap);
			#ifdef DEBUG
			fprintf(stderr,"Fetched instruction 0x%x at PC = 0x%x\n",s.instruction, s.status_reg.pc);
			#endif

			// update mmu fsr, far
			// This is done separately to match the behaviour of
			// the instruction pipeline.
			if(s.mmu_fsr != 0)
				updateMmuFsrFar(s.mmu_fsr, s.status_reg.pc);
		}

		uint8_t annul_trap = getBit32(s.trap_vector, _ANNUL_);
		uint8_t update_post_fetch_trap = !skip_fetch && post_fetch_trap && !annul_trap;

		if(update_post_fetch_trap)
		{
			s.trap_vector = setBit32(s.trap_vector, _TRAP_, 1);
			s.trap_vector = setBit32(s.trap_vector, _INSTRUCTION_ACCESS_EXCEPTION_, 1);
		}

		uint8_t annul_inst = !skip_fetch && annul_trap; //Annul the current instruction
		
		if(annul_inst)
		{
			s.trap_vector    =  setBit32(s.trap_vector, _ANNUL_, 0) ;
			s.status_reg.pc  =  s.status_reg.npc ;
			s.status_reg.npc =  s.status_reg.npc + 4 ;
			#ifdef DEBUG
			fprintf(stderr,"\tcurrent instruction is annulled\n");
			#endif

		}

		uint8_t skip_decode = skip_fetch || post_fetch_trap || annul_trap;

		if(!skip_decode)
		{
			inform_HW_server(GDB_IFETCH, &s,0);
		}

		uint8_t fp_uimp_inst = 0;
		uint8_t fp_invalid_reg = 0;	//to check fp_invalid_reg exception

		if(!skip_decode)
			decodeInstruction(s.instruction, &opcode, s.trap_vector, &rs1, &rs2, &simm13, &shcnt, &disp30, 
					&disp22, &software_trap, &rd, &i, &a, &asi, &inst_type, &fp_uimp_inst);

		// Generating Invalid_FP_Register trap
		if(fp_uimp_inst) {
			s.trap_vector = setBit32(s.trap_vector, _TRAP_, 1) ;
			s.trap_vector = setBit32(s.trap_vector, _FP_EXCEPTION_, 1) ;
			s.status_reg.fsr = setSlice32(s.status_reg.fsr, 16, 14, _UNIMPLEMENTED_FPOP_);
		}

		flags = 0;
		flags = ((a == 1) ? setBit8(flags, _ANNUL_FLAG_, 1) : flags);

		uint8_t cwp = getSlice32(s.status_reg.psr, 4, 0);
		if(!skip_decode)
			readOperands(opcode, rs1, rs2, rd, simm13, shcnt, disp30, disp22, software_trap, i, &operand2_3, &operand2_2,
				&operand2_1, &operand2_0, &operand1_3, &operand1_2, &operand1_1, &operand1_0, inst_type, cwp, &data1, &data0, &fp_invalid_reg);

		// Generating Invalid_FP_Register trap
		if(fp_invalid_reg) {
			s.trap_vector = setBit32(s.trap_vector, _TRAP_, 1) ;
			s.trap_vector = setBit32(s.trap_vector, _FP_EXCEPTION_, 1) ;
			s.status_reg.fsr = setSlice32(s.status_reg.fsr, 16, 14, _INVALID_FP_REGISTER_);
		}

		uint8_t is_fp_op = (inst_type == _FPop1_INS_) || (inst_type == _FPop2_INS_);

		uint8_t skip_fp_execute = (skip_decode || !is_fp_op);
		uint32_t post_fp_execute_trap_vector = 0;
		if(!skip_fp_execute)
		{
			post_fp_execute_trap_vector = completeFPExecution( opcode, operand2_3, operand2_2, operand2_1, operand2_0, 								operand1_3, operand1_2, operand1_1, operand1_0, rd, &(s.status_reg), s.trap_vector);
			s.trap_vector = post_fp_execute_trap_vector;
		}

		uint8_t skip_execute = (skip_decode || is_fp_op);
		uint32_t post_execute_trap_vector = 0;
		if(!skip_execute)
		{
			//Execute instruction 
			post_execute_trap_vector = executeInstruction( opcode, operand2_0, operand1_0, &result_h, &result_l,
					&flags, &s, rs1, rd, asi, data1, data0);
			s.trap_vector = post_execute_trap_vector;
		}
		uint8_t post_execute_trap = getBit32(s.trap_vector, _TRAP_);


		uint8_t skip_write_back = skip_execute || post_execute_trap || !getBit8(flags, _NEED_WRITE_BACK_);
		if(!skip_write_back)
		{
			writeBackResult( rd, result_h, result_l, flags, getSlice32(s.status_reg.psr, 4, 0), s.status_reg.pc, &(s.reg_update_flags));
		}
       			
		if((!skip_fetch) && (!skip_execute))
		{
			//Increment a count of instructions executed.
			increment_instruction_count();
			
			//long icount = get_instruction_count();
										
			//set a gdb breakpoint here  to examine 
			//register contents at the end of each instruction:
			//
			//to examine pc, 		(gdb) x s.status_reg.pc
			//to examine the instruction 	(gdb) x s.instruction
		}
		
		
		if(!skip_fetch && (getBit32(s.trap_vector, _TRAP_)==0))
		{
			//if logging is enabled,
			//Compute a signature containing information about
			//processor state updated by this instruction
			//and send it out to the logger.
			if(is_logging_enabled())
			{
				generateLogMessage(&s);
			}
		}

		uint8_t update_pc = (!skip_execute || !skip_fp_execute) && !post_execute_trap && !isBranchInstruction(opcode, inst_type);
		if(update_pc)
		{
		s.status_reg.pc = s.status_reg.npc ;
		s.status_reg.npc = s.status_reg.npc + 4 ;
		}
		#ifdef DEBUG
		fprintf(stderr,"Info:ProcessorCore: finished an execution cycle. Next PC = 0x%x\n",s.status_reg.pc);
		#endif

	
	}
}

void clearStateUpdateFlags( ProcessorState *s)
{
	StateUpdateFlags *flags = &(s->reg_update_flags);
	flags->psr_updated=0;   
	flags->wim_updated=0;   
	flags->tbr_updated=0;   
	flags->y_updated=0;     
	flags->gpr_updated=0;   
	flags->store_active = 0;
	flags->double_word_write=0;
	flags->reg_id=0;       
	flags->reg_val_high=0; 
	flags->reg_val_low=0;  
	flags->pc=0;
}
	
void init( ProcessorState *s)
{
	StatusRegisters *status_reg = &(s->status_reg);

	s->instruction = 0;		
	s->addr_space = 0;		
	s->mode =  _RESET_MODE_;	
	s->trap_vector = 0;		
	s->interrupt_level = 0;		
	s->ticc_trap_type = 0;		
	s->store_barrier_pending = 0;	

	status_reg->psr =  0x10C0 ;
	//PSR fields:
	//	current window pointer CWP (bits 4:0 )	= 0000
	//	enable traps		ET (bit  5   )	= 0
	//	previous supervisor	PS (bit  6   )	= 1
	//	supervisor		S  (bit  7   )	= 1
	//	proc interrupt level   PIL (bits 11:8)	= 0000
	//	enable FPU              EF (bit 12   )	= 1
	//	---all others are zero-------
	status_reg->wim =  0 ;
	status_reg->tbr =  0 ;
	status_reg->y   =  0 ;
	status_reg->pc  =  0 ;
	status_reg->npc =  0 ;
	status_reg->iq  =  0 ;
	status_reg->fsr =  0 ;
	status_reg->fq  =  0 ;
	status_reg->csr =  0 ;
	status_reg->cq  =  0 ;

	uint8_t i = 0;
	for(; i < 32; i++)
	{
		//
		// initialize status registers to 0.
		// 
		status_reg->asr[i] = 0x0;
	}

	initRegisterFile();
	clearStateUpdateFlags(s);
}
//if logging is enabled,
//generate a signature
//and send it out to the Logger pipes
void generateLogMessage( ProcessorState *s)
{
	
	uint32_t reg_write_log=0;
	uint32_t store_log=0;
	uint32_t pc_log=0;

	StatusRegisters *r = &(s->status_reg);
	StateUpdateFlags *f = &(s->reg_update_flags);

	//Generate the signatures
	reg_write_log = assembleRegisterWriteSignature(
		f->psr_updated, r->psr, // uint8_t psr_updated, uint32_t psr_value,
		f->wim_updated, r->wim, //uint8_t wim_updated, uint32_t wim_value,
		f->tbr_updated, r->tbr, //uint8_t tbr_updated, uint32_t tbr_value,
		f->y_updated,   r->y,	//uint8_t y_updated, uint32_t y_value,
		f->gpr_updated,		//uint8_t gpr_updated,
		f->double_word_write, 	//uint8_t double_word_write,
		f->reg_id, 
		f->reg_val_high, 
		f->reg_val_low);
	store_log = assembleStoreSignature( 
		f->store_active, 	
		f->store_asi,		
		f->store_byte_mask,	
		f->store_double_word,
		f->store_addr,
		f->store_word_high,
		f->store_word_low);

	pc_log = f->pc;

	//if(f->pc) pc_log = f->pc; //pc was updated inside an instruction
	//else      pc_log = r->pc; //pc to be logged is same as the current pc

	//send to logger pipe
	writeToLoggerPipe(reg_write_log);
	writeToLoggerPipe(store_log);
	writeToLoggerPipe(pc_log);
}


uint8_t isBranchInstruction(Opcode op, InstructionType type)
{
	return ((op == _CALL_) || (op == _RETT_) || (op == _JMPL_) || (type == _CC_INS_) || (type == _TICC_INS_)); 
}

uint8_t isFloatCompareInstruction(Opcode op)
{
	return ((op == _FCMPs_) || (op == _FCMPd_) || (op == _FCMPq_) || (op == _FCMPEs_) || (op == _FCMPEd_) || (op == _FCMPEq_));
}

uint8_t fetchInstruction( uint8_t addr_space, uint32_t addr, uint32_t *inst, uint32_t* mmu_fsr)
{
	uint8_t mae_value;
	readInstruction( addr_space, addr, &mae_value, inst, mmu_fsr);
	return mae_value;
}

void writeBackResult( uint8_t dest_reg, uint32_t result_h, uint32_t result_l, uint8_t flags, uint8_t cwp, uint32_t pc, StateUpdateFlags* reg_update_flags)
{
	uint8_t is_float_instruction = (getBit8(flags, _FLOAT_INSTRUCTION_) == 1);
	uint8_t is_double_result = (getBit8(flags, _DOUBLE_RESULT_) == 1);

	//IU write-back
	if(!is_float_instruction)
	{
		if(!is_double_result)
		{
			writeRegister(  dest_reg, cwp, result_l);
		}
		else
		{
			writeRegister(  setBit8(dest_reg, 0, 0), cwp, result_l);
			writeRegister( setBit8(dest_reg, 0, 1), cwp, result_h);
		}
		
		//Information to be logged:
		reg_update_flags->gpr_updated=1;
		if(is_double_result) 
		{
			reg_update_flags->double_word_write=1; 
		}
		else
		{
			reg_update_flags->double_word_write=0; 
		}
		reg_update_flags->reg_id=dest_reg;
		reg_update_flags->reg_val_high=result_h;
		reg_update_flags->reg_val_low=result_l;
	}
	//FP write-back
	else
	{
		if(!is_double_result)
		{
			writeFRegister( dest_reg, result_l); 
		}
		else
		{
			dest_reg = setBit8(dest_reg, 0, 0) ;
			writeFRegister(dest_reg, result_l);
			dest_reg = setBit8(dest_reg, 0, 1) ;
			writeFRegister( dest_reg, result_h);
		}
	}
}

uint32_t completeFPExecution( Opcode opcode, uint32_t operand2_3, uint32_t operand2_2, uint32_t operand2_1, 
				uint32_t operand2_0, uint32_t operand1_3, uint32_t operand1_2, uint32_t operand1_1, uint32_t operand1_0,
				uint8_t dest_reg, StatusRegisters *ptr, uint32_t trap_vector)
{
	uint32_t tv, result_l2, result_l1, result_h2, result_h1;
	uint8_t texc, aexc, tem, c, tfcc;
	uint8_t flags = 0;
	uint8_t ft = 0;
	// StatusRegisters current_sr = *ptr; 

	tv = executeFPInstruction( opcode, operand2_3, operand2_2, operand2_1, operand2_0, operand1_3, operand1_2, operand1_1, operand1_0,
			&result_h2, &result_h1, &result_l2, &result_l1, trap_vector, &flags, &ft, ptr);
	c = getBit8(ft, 0);
	texc = getSlice8(ft, 5, 1);
	tfcc = getSlice8(ft, 7, 6);

	tem = getSlice32((*ptr).fsr, 27, 23);
	aexc = getSlice32((*ptr).fsr, 9, 5);

	uint8_t no_trap = (getBit32(tv, _TRAP_) == 0);
	uint8_t execute_fp_op =  no_trap;

	uint8_t no_fpu_present = (getBpFPUPresent() == 0);
	uint8_t unimplemented = execute_fp_op && no_fpu_present;
	if(unimplemented)
	{
	tv = setBit32(tv, _TRAP_, 1) ;
	tv = setBit32(tv, _FP_EXCEPTION_, 1);
	ptr->fsr = setSlice32((*ptr).fsr, 16, 14, _UNIMPLEMENTED_FPOP_) ;
	}

	uint8_t incomplete = (c == 0);
	uint8_t unfinished = execute_fp_op && !no_fpu_present && incomplete;
	if(unfinished)
	{
	 tv = setBit32(tv, _TRAP_, 1) ;
	 tv = setBit32(tv, _FP_EXCEPTION_, 1) ;
	 ptr->fsr = setSlice32((*ptr).fsr, 16, 14, _UNFINISHED_FPOP_) ;
	}

	uint8_t ex = (texc != 0) && (tem != 0);
	uint8_t execute = execute_fp_op && !no_fpu_present && !incomplete;
	uint8_t exception = execute && ex;

	if( (exception)) 
	{
		ptr->fsr = setSlice32((*ptr).fsr, 4, 0, (getBit8(texc, 5) & getBit8(tem, 5))) ;
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _FP_EXCEPTION_, 1) ;
		ptr->fsr = setSlice32((*ptr).fsr, 16, 14, _IEEE_754_EXCEPTION_) ;
	}

	uint8_t no_exception = execute && !ex;
	if( (no_exception))
	{
		ptr->fsr = setSlice32((*ptr).fsr, 4, 0, texc) ;
		ptr->fsr = setSlice32((*ptr).fsr, 9, 5, (aexc | texc)) ;
	}

	uint8_t is_single_result = (getBit8(flags, _SINGLE_RESULT_) == 1);
	uint8_t is_double_result = (getBit8(flags, _DOUBLE_RESULT_) == 1);
	uint8_t is_quad_result = (getBit8(flags, _QUAD_RESULT_) == 1);

	if(!(!no_exception || !is_single_result)) writeFRegister(dest_reg, result_l1);
	if( (is_double_result)) dest_reg = setBit8(dest_reg, 0, 0) ;
	
	if(!(!no_exception || !is_double_result)) writeFRegister(dest_reg, result_l2);
		
	if( (is_double_result)) dest_reg = setBit8(dest_reg, 0, 1) ;
	if(!(!no_exception || !is_double_result)) writeFRegister(dest_reg, result_l1);
	
	if( (is_quad_result)) dest_reg = setSlice8(dest_reg, 1, 0, 0) ;
	if(!(!no_exception || !is_quad_result))	writeFRegister( dest_reg, result_h2);
	if( (is_quad_result)) dest_reg = setBit8(dest_reg, 0, 1) ;
	if(!(!no_exception || !is_quad_result))	writeFRegister( dest_reg, result_h1);
	if( (is_quad_result)) dest_reg = setBit8(dest_reg, 1, 1) ;
	if(!(!no_exception || !is_quad_result))	writeFRegister( dest_reg, result_l1);
	if( (is_quad_result)) dest_reg = setBit8(dest_reg, 0, 0) ;
	if(!(!no_exception || !is_quad_result)) writeFRegister( dest_reg, result_l2);

	uint8_t compare_inst = no_exception && isFloatCompareInstruction(opcode);
	
	if( (compare_inst)) ptr->fsr = setSlice32((*ptr).fsr, 11, 10, tfcc) ;

	if( (no_exception)) ptr->fsr = setSlice32((*ptr).fsr, 16, 14, 0) ;

	return tv;
}
