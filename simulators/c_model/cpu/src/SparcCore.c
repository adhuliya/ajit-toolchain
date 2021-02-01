//-------------------------------------------------------------------------
// Describes the cpu thread 
//-------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

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
#include "Mmu.h"
#include "rlut.h"
#include "ImplementationDependent.h"


void increment_instruction_count(ProcessorState* s) 
{ 
	s->num_instructions_executed++; 
};

uint64_t get_instruction_count(ProcessorState* s) 
{ 
	return s->num_instructions_executed; 
};

uint64_t getCycleEstimate (ProcessorState* s)
{
	uint64_t ret_val = s->num_instructions_executed;
	ret_val += (s->mmu_state->Num_Mmu_translated_accesses - s->mmu_state->Num_Mmu_TLB_hits)*
				TLB_MISS_PENALTY;
	ret_val += s->dcache->number_of_misses * CACHE_MISS_PENALTY;
	ret_val += s->icache->number_of_misses * CACHE_MISS_PENALTY;
	
	ret_val += s->num_fp_sp_sqroots_executed * FP_SP_SQROOT_PENALTY;
	ret_val += s->num_fp_dp_sqroots_executed * FP_DP_SQROOT_PENALTY;

	ret_val += s->num_fp_sp_divs_executed * FP_SP_DIV_PENALTY;
	ret_val += s->num_fp_dp_divs_executed * FP_DP_DIV_PENALTY;

	ret_val += s->num_iu_divs_executed * IU_DIV_PENALTY;

	ret_val += s->num_traps * TRAP_PENALTY;

	return(ret_val);
}

void  	printCpuStatistics (ProcessorState* s)
{
	fprintf(stderr,"\nStatistics for CPU %d:\n", s->cpu_id);

	fprintf(stderr,"    number-of-instructions-executed = %" PRIu64 "\n", 
						s->num_instructions_executed);
	fprintf(stderr,"    number-of-traps  = %u\n", 
						s->num_traps);
	fprintf(stderr,"    number-of-cti  = %u, mispredicts=%u\n", 
						s->branch_predictor.branch_count,
						s->branch_predictor.mispredicts);
	fprintf(stderr,"    cycle-count estimate = %lu\n",getCycleEstimate(s));

	dumpPageBits(s);
}


uint32_t getAsrValue (ProcessorState* cpu_state, int asr_id)
{
	uint32_t res = 0;
	if((asr_id == 31) || (asr_id == 30))
	{
		uint64_t cycle_count = getCycleEstimate (cpu_state);			
		if(asr_id == 31)
		{
			cycle_count = cycle_count >> 32;
		}
		res = cycle_count & 0xffffffff;
	}
	else
		res = cpu_state->status_reg.asr[asr_id] ;    

	return(res);
}

//For time-keeping during simulation:
#include <time.h>
time_t simulation_time;

void 	clearStateUpdateFlags( ProcessorState *s);
void 	generateLogMessage( ProcessorState *s);
uint8_t isBranchInstruction(Opcode op, InstructionType type);
uint8_t isFloatCompareInstruction(Opcode op);
uint8_t fetchInstruction(ProcessorState* s, 
				uint8_t addr_space, 
				uint32_t addr, 
				uint32_t *inst, 
				uint32_t* mmu_fsr);
uint32_t completeFPExecution (ProcessorState* s,
					Opcode opcode, 
					uint32_t operand2_3, 
					uint32_t operand2_2, 
					uint32_t operand2_1, 
			     		uint32_t operand2_0, 
					uint32_t operand1_3, 
					uint32_t operand1_2, 
					uint32_t operand1_1, 
					uint32_t operand1_0,
					uint8_t dest_reg, 
					StatusRegisters *ptr,	
					uint32_t trap_vector);
void writeBackResult( RegisterFile* rf,
					uint8_t dest_reg, 
					uint32_t result_h, 
					uint32_t result_l, 
					uint8_t flags, 
					uint8_t cwp, 
					uint32_t pc, 
					StateUpdateFlags* reg_update_flags);




// Each cpu is started with an id.
void cpu(void* id_ptr)
{
	ProcessorState* cpu_state = (ProcessorState*) id_ptr;



	// thread specific stuff.
	Opcode opcode = _UNASSIGNED_;
	InstructionType inst_type = _UNKNOWN_;
	uint32_t operand1_0, 
			operand1_1, 
			operand1_2, 
			operand1_3, 
			operand2_0, 
			operand2_1, 
			operand2_2, 
			operand2_3, 
			result_h, 
			result_l;
	uint8_t rd, asi, rs1, rs2, shcnt, software_trap, i, a;
	uint8_t flags;
	uint16_t simm13;
	uint32_t disp30, disp22;
	uint32_t data0, data1;
	uint8_t vector_data_type;
	operand1_0 = operand1_1 = operand1_2 = 
			operand1_3 = operand2_0 = operand2_1 = operand2_2 = operand2_3 = 0;
	
	
	inform_HW_server(cpu_state, GDB_INITIAL_STOP, 0);
	
	uint8_t interrupt_level = 0;
	while(1)
		// processor executes an endless loop..
	{
		
		simulation_time = time(NULL);
		
		// Get processor mode.
		uint8_t reset_mode = (cpu_state->mode == _RESET_MODE_);
		uint8_t error_mode = (cpu_state->mode == _ERROR_MODE_);
		uint8_t execute_mode = (cpu_state->mode == _EXECUTE_MODE_);

		//-----------------------------------------------
		//RESET MODE :
		//-----------------------------------------------
		//move to execute mode, and set the reset-trap.
		uint8_t reset_in1 = (getBpReset(cpu_state) == 0);
		uint8_t reset_in_reset = reset_mode && reset_in1;
		if(reset_in_reset)
		{
			 cpu_state->mode = _EXECUTE_MODE_ ;
			 cpu_state->trap_vector = setBit32(cpu_state->trap_vector, _TRAP_, 1) ;
			 cpu_state->trap_vector = setBit32(cpu_state->trap_vector, _RESET_TRAP_, 1) ;
		}
		
		
		
		//-----------------------------------------------
		//ERROR MODE :
		//-----------------------------------------------
		if(error_mode)
		{
			inform_HW_server(cpu_state, DOVAL_PROC_ENTERED_ERROR_MODE, 0);

			//If this is a simulation, stop simulation
			//upon encoutering error mode.
			//assert AJIT_to_ENV_error to halt simulation.
			fprintf(stderr,"Processor %d entered ERROR MODE at PC=0x%x\n ",cpu_state->cpu_id,
						cpu_state->status_reg.pc);
			if(getBit32(cpu_state->trap_vector, _TRAP_INSTRUCTION_)!=0 && cpu_state->ticc_trap_type==0)
			{
				fprintf(stderr,"Program exited upon a ta 0\n ");
			}
			else
			{
				fprintf(stderr,"Program exited with a trap type = 0x%x",cpu_state->ticc_trap_type);
			}

			//Insert a gdb breakpoint here to examine register
			//contents at the end of program execution
			//write_uint8("AJIT_to_ENV_error", 1);
			setPbError(cpu_state, 1);

			do{ sleep(10); }while(1);
		}



		//If this is real hardware,
		//indicate somehow that the machine 
		//is in error mode and wait for 
		//reset to be asserted
		uint8_t reset_in2 = (getBpReset(cpu_state) == 1);
		uint8_t reset_in_error = error_mode && reset_in2;
		cpu_state->mode = (reset_in_error ? _RESET_MODE_ : cpu_state->mode);
		if(reset_in_error)
			setPbError(cpu_state, 0);


		//----------------------------------------------
		//EXECUTE MODE
		//----------------------------------------------
		
						
		// If reset is observed in execute mode, re-initialize
		// the processor.
		uint8_t reset_in3 = (getBpReset(cpu_state) == 1);
		uint8_t reset_in_execute = execute_mode && reset_in3;
		cpu_state->mode = (reset_in_execute ? _RESET_MODE_ : cpu_state->mode);
		if(reset_in_execute || reset_in_error)
		{ 
			resetProcessorState(cpu_state);
			inform_HW_server(cpu_state, GDB_RESET, 0);
		}


		// enable trap if !reset in execute and bit-5 of psr is 1.
		// bit-5 of psr is the enable-trap bit.
		uint8_t enable_trap = !reset_in_execute && (getBit32(cpu_state->status_reg.psr, 5) == 1);


		// Read external interruptcpu_state->...
		if(cpu_state->mode == _EXECUTE_MODE_) 
			interrupt_level = getBpIRL(cpu_state);

		// check if interrupt level is greater than the minimum interrupt
		// level which the processor will accept (psr[11:8])
		uint8_t is_interrupt = enable_trap && ((interrupt_level == 15) || (interrupt_level > getSlice32(cpu_state->status_reg.psr, 11, 8)));

		if(is_interrupt)
		{
#ifdef DEBUG
			printf("\nCPU : Detected external interrupt when enable_trap=1. Interrupt_level = 0x%x",interrupt_level);
#endif

			cpu_state->trap_vector =  setBit32(cpu_state->trap_vector, _TRAP_, 1) ;
			cpu_state->interrupt_level = interrupt_level ;

		}

		uint8_t skip_trap_execution = !((cpu_state->mode == _EXECUTE_MODE_) && (getBit32(cpu_state->trap_vector, _TRAP_) == 1));

		if(!skip_trap_execution)
		{
			(cpu_state->num_traps)++;
			executeTrap(cpu_state,
					&(cpu_state->trap_vector), &(cpu_state->status_reg.psr), 
					&(cpu_state->status_reg.tbr), &(cpu_state->interrupt_level), &(cpu_state->mode),
					cpu_state->ticc_trap_type, &(cpu_state->status_reg.pc), &(cpu_state->status_reg.npc));
			
			
			//Have gdb ignore windows overflow, underflow and timer traps,
			//as these are very frequent during kernel boot.
#ifdef IGNORE_TRAPS_AND_INTERRUPTS
			uint8_t TRAP_TYPE= getSlice32(cpu_state->status_reg.tbr, 11, 4);
			if ( TRAP_TYPE!=0 && TRAP_TYPE!=5 && TRAP_TYPE!=6 && TRAP_TYPE!=0xA)
			{
				inform_HW_server(cpu_state, GDB_TRAP_OCCURED, 0);
			}
#endif 
		}
		cpu_state->addr_space = (getBit32(cpu_state->status_reg.psr, 7) == 0) ? 8 : 9; // Supervisor bit

		uint8_t skip_fetch = !(cpu_state->mode == _EXECUTE_MODE_);
		// Only MAE trap from fetchInstruction
		uint8_t post_fetch_trap=0;
		cpu_state->mmu_fsr = 0;
		if(!skip_fetch)
		{
			
			//clear register-update flags 
			//(which maintain information for logging)
			//at the start of this instruction cycle.
			clearStateUpdateFlags(cpu_state);
			cpu_state->reg_update_flags.pc = cpu_state->status_reg.pc;
			
			post_fetch_trap = fetchInstruction(cpu_state, cpu_state->addr_space, cpu_state->status_reg.pc, &(cpu_state->instruction),
								&(cpu_state->mmu_fsr)); //memory_read

			//================================
			//increment count of instructions fetched
			(cpu_state->num_ifetches)++;
			if((cpu_state->reporting_interval > 0) && ((cpu_state->num_ifetches)%(cpu_state->reporting_interval)==0) )
			{
				fprintf(stderr,"\n==============================================\n");
				fprintf(stderr,"Real time = %s\n",ctime(&simulation_time));
				fprintf(stderr,"Cycle-count estimate = %lu\n",getCycleEstimate(cpu_state));
				fprintf(stderr,"num_ifetches = %lu\n",cpu_state->num_ifetches);
				fprintf(stderr,"num_traps = %u\n",cpu_state->num_traps);
				fprintf(stderr,"PC=0x%x\n",cpu_state->status_reg.pc);
				fprintf(stderr,"nPC=0x%x\n",cpu_state->status_reg.npc);
				fprintf(stderr,"trap_vector=0x%x\n",cpu_state->trap_vector);
				fprintf(stderr,"==============================================\n");
			}

			//================================

			cpu_state->trap_vector = setBit32(cpu_state->trap_vector, _MAE_, post_fetch_trap);
			#ifdef DEBUG
			fprintf(stderr,"Fetched instruction 0x%x at PC = 0x%x\n",cpu_state->instruction, cpu_state->status_reg.pc);
			#endif

			// update mmu fsr, far
			// This is done separately to match the behaviour of
			// the instruction pipeline.
			if(cpu_state->mmu_fsr != 0)
				updateMmuFsrFar(cpu_state->mmu_state, 
							cpu_state->dcache,
							cpu_state->mmu_fsr, cpu_state->status_reg.pc);
		}

		uint8_t annul_trap = getBit32(cpu_state->trap_vector, _ANNUL_);
		uint8_t update_post_fetch_trap = !skip_fetch && post_fetch_trap && !annul_trap;

		if(update_post_fetch_trap)
		{
			cpu_state->trap_vector = setBit32(cpu_state->trap_vector, _TRAP_, 1);
			cpu_state->trap_vector = setBit32(cpu_state->trap_vector, _INSTRUCTION_ACCESS_EXCEPTION_, 1);
		}

		uint8_t annul_inst = !skip_fetch && annul_trap; //Annul the current instruction
		
		if(annul_inst)
		{
			cpu_state->trap_vector    =  setBit32(cpu_state->trap_vector, _ANNUL_, 0) ;
			cpu_state->status_reg.pc  =  cpu_state->status_reg.npc ;
			cpu_state->status_reg.npc =  cpu_state->status_reg.npc + 4 ;
			#ifdef DEBUG
			fprintf(stderr,"\tcurrent instruction is annulled\n");
			#endif

		}

		uint8_t skip_decode = skip_fetch || post_fetch_trap || annul_trap;

		if(!skip_decode)
		{
			inform_HW_server(cpu_state, GDB_IFETCH, 0);
		}

		uint8_t fp_uimp_inst = 0;
		uint8_t fp_invalid_reg = 0;	//to check fp_invalid_reg exception

		if(!skip_decode)
			decodeInstruction(cpu_state->instruction, cpu_state->isa_mode,
						&opcode, 
						cpu_state->trap_vector, 
						&rs1, &rs2, &simm13, 
						&shcnt, &disp30, 
						&disp22, &software_trap, 
						&rd, &i, &a, &asi, &inst_type, 
						&fp_uimp_inst, &vector_data_type);

		// Generating Invalid_FP_Register trap
		if(fp_uimp_inst) {
			cpu_state->trap_vector = setBit32(cpu_state->trap_vector, _TRAP_, 1) ;
			cpu_state->trap_vector = setBit32(cpu_state->trap_vector, _FP_EXCEPTION_, 1) ;
			cpu_state->status_reg.fsr = setSlice32(cpu_state->status_reg.fsr, 16, 14, _UNIMPLEMENTED_FPOP_);
		}

		flags = 0;
		flags = ((a == 1) ? setBit8(flags, _ANNUL_FLAG_, 1) : flags);

		uint8_t cwp = getSlice32(cpu_state->status_reg.psr, 4, 0);
		if(!skip_decode)
			readOperands(cpu_state->register_file,
					opcode, rs1, rs2, rd, simm13, shcnt, 
					disp30, disp22, software_trap, i, &operand2_3, &operand2_2,
					&operand2_1, &operand2_0, &operand1_3, &operand1_2, 
					&operand1_1, &operand1_0, inst_type, cwp, 
					&data1, &data0, &fp_invalid_reg);

		// Generating Invalid_FP_Register trap
		if(fp_invalid_reg) {
			cpu_state->trap_vector = setBit32(cpu_state->trap_vector, _TRAP_, 1) ;
			cpu_state->trap_vector = setBit32(cpu_state->trap_vector, _FP_EXCEPTION_, 1) ;
			cpu_state->status_reg.fsr = setSlice32(cpu_state->status_reg.fsr, 16, 14, _INVALID_FP_REGISTER_);
		}

		uint8_t is_fp_op = (inst_type == _FPop1_INS_) || (inst_type == _FPop2_INS_);

		uint8_t skip_fp_execute = (skip_decode || !is_fp_op);
		uint32_t post_fp_execute_trap_vector = 0;
		if(!skip_fp_execute)
		{
			post_fp_execute_trap_vector = 
				completeFPExecution(cpu_state,  opcode, 
						operand2_3, operand2_2, operand2_1, operand2_0,  
						operand1_3, operand1_2, operand1_1, operand1_0, 
						rd, &(cpu_state->status_reg), cpu_state->trap_vector);
			cpu_state->trap_vector = post_fp_execute_trap_vector;
		}

		uint8_t skip_execute = (skip_decode || is_fp_op);
		uint32_t post_execute_trap_vector = 0;

		uint8_t save_flag = 0;
		uint8_t restore_flag = 0;

		if(!skip_execute)
		{
			//Execute instruction 
			post_execute_trap_vector = 
				executeInstruction( cpu_state,
							opcode, 
							operand2_0, operand2_1, 
							operand1_0, operand1_1, 
							&result_h, &result_l,
							&flags, rs1, rd, asi, i,
							data1, data0, vector_data_type);

			cpu_state->trap_vector = post_execute_trap_vector;
			save_flag = (opcode == _SAVE_);
			restore_flag = (opcode == _RESTORE_);
		}
		uint8_t post_execute_trap = getBit32(cpu_state->trap_vector, _TRAP_);


		uint8_t skip_write_back = skip_execute || post_execute_trap || !getBit8(flags, _NEED_WRITE_BACK_);
		if(!skip_write_back)
		{
			writeBackResult(cpu_state->register_file, rd, result_h, result_l, flags, getSlice32(cpu_state->status_reg.psr, 4, 0), cpu_state->status_reg.pc, &(cpu_state->reg_update_flags));
		}
       			
		
		if(!skip_fetch && (getBit32(cpu_state->trap_vector, _TRAP_)==0))
		{
			increment_instruction_count(cpu_state);

			if((save_flag || restore_flag) && cpu_state->report_traps)
			{
				fprintf(stderr,"Info: at pc=0x%x, %s.. now fp=0x%x, sp=0x%x, wim=0x%x, psr=0x%x\n", cpu_state->status_reg.pc,  (save_flag ? "save" : "restore"),
						frame_pointer(cpu_state), stack_pointer(cpu_state),
						cpu_state->status_reg.wim,
						cpu_state->status_reg.psr);
			}

			//if logging is enabled,
			//Compute a signature containing information about
			//processor state updated by this instruction
			//and send it out to the logger.
			if(is_logging_enabled())
			{
				generateLogMessage(cpu_state);
			}
		}

		uint8_t update_pc = (!skip_execute || !skip_fp_execute) && !post_execute_trap && !isBranchInstruction(opcode, inst_type);
		if(update_pc)
		{
			cpu_state->status_reg.pc = cpu_state->status_reg.npc ;
			cpu_state->status_reg.npc = cpu_state->status_reg.npc + 4 ;
		}
#ifdef DEBUG
		fprintf(stderr,"Info:ProcessorCore: finished an execution cycle. Next PC = 0x%x\n",cpu_state->status_reg.pc);
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

	flags->fpreg_updated=0;
	flags->fpreg_double_word_write=0;
	flags->fpreg_id=0;
	flags->fpreg_val_high=0;
	flags->fpreg_val_low=0;
	flags->fsr_updated=0;
	flags->ftt_updated=0;
	flags->fcc_updated=0;
	flags->fsr_val=0; 

	flags->store_active = 0;
	flags->double_word_write=0;
	flags->reg_id=0;       
	flags->reg_val_high=0; 
	flags->reg_val_low=0;  
	flags->pc=0;
}

void init(ProcessorState *s, uint32_t cpu_id, uint32_t isa_mode, int bp_table_size, uint8_t report_traps, uint32_t init_pc)
{
	s->cpu_id = cpu_id;
	s->isa_mode = isa_mode;
	s->register_file  =  makeRegisterFile ();

	s->mmu_state      =  makeMmuState (cpu_id);
	startRlutDaemon(s->mmu_state->rlut);

	s->icache         =  makeCache (cpu_id, 1);
	start_icache_thread(s->icache);

	s->dcache         =  makeCache (cpu_id, 0);
	start_dcache_thread(s->dcache);


	// these maye get populated
	// by someone else.
	s->hw_server	  =  NULL;
	s->monitor_logger =  NULL;

	sprintf(s->mode_pipe_name,"AJIT_to_ENV_processor_mode_%d", cpu_id);
	sprintf(s->error_pipe_name,"AJIT_to_ENV_error_%d", cpu_id);
	sprintf(s->reset_pipe_name,"ENV_to_AJIT_reset_%d", cpu_id);
	sprintf(s->ilvl_pipe_name, "ENV_to_CPU_irl_%d", cpu_id);
	sprintf(s->logger_pipe_name, "AJIT_to_ENV_logger_%d", cpu_id);


	initBranchPredictorState(&(s->branch_predictor), bp_table_size);
	resetProcessorState (s);

	s->reset_called_once = 0;

	//input signals to the cpu hardwired to 
	//a certain value in the Ajit processor:
	s->bp_fpu_present = 1;
	s->bp_fpu_exception = 0;
	s->bp_fpu_cc=0;
	s->bp_cp_present = 0;
	s->bp_cp_exception = 0;
	s->bp_cp_cc=0;

	s->pb_error = 0;
	s->pb_block_ldst_word = 0;
	s->pb_block_ldst_byte = 0;

	s->report_traps = report_traps;
	s->init_pc = init_pc;
}

void resetProcessorState(ProcessorState *s)
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

	//
	// asr 29, maintains the cpu-id
	//
	status_reg->asr[29] = s->cpu_id;

	//
	// asr 28, maintains the half-precision floating
	// point format's exponent width.  This number has
	// a default value, but this value can be overridden
	// by the programmer.
	//
	status_reg->asr[28] = DEFAULT_HALF_PRECISION_EXPONENT_WIDTH;

	s->num_ifetches = 0;
	s->num_instructions_executed = 0;
	s->num_traps = 0;

	s->num_fp_sp_sqroots_executed = 0;
	s->num_fp_dp_sqroots_executed = 0;

	s->num_fp_sp_divs_executed = 0;
	s->num_fp_dp_divs_executed = 0;

	s->num_iu_divs_executed = 0;


	resetRegisterFile(s->register_file);

	clearStateUpdateFlags(s);
	resetMmuState (s->mmu_state);
	flushCache (s->dcache);
	flushCache (s->icache);
	resetBranchPredictorState(&(s->branch_predictor));


	s->CPU_HW_SERVER_ENABLED =0;
	s->CPU_GDB_FLAG=0;
	s->CPU_DOVAL_FLAG=0;


	int I;
	for(I=0; I < (32*1024); I++)
	{
		s->page_access_status[I] = 0;	
	}

}

void  setPageBit(ProcessorState* s, uint32_t virtual_addr)
{
	uint32_t page_id = (virtual_addr >> 12);
	uint32_t idx = page_id >> 5;

	uint32_t offset = (page_id & 0x1f);
	s->page_access_status[idx] = s->page_access_status[idx] | (1 << offset);
}

void  dumpPageBits(ProcessorState* s)
{
	fprintf(stderr,"Info: for CPU %d: 4kB pages accessed are (starting virtual-address of the page is shown):\n", s->cpu_id);
	uint32_t I;
	for(I = 0; I < (32*1024); I++)
	{
		uint32_t prec = s->page_access_status[I];
		if(prec  != 0)
		{
			uint32_t J;
			for(J=0; J < 32; J++)
			{
				if((prec >> J)	 &  0x1) 
				{
					uint32_t pid = (I << 5) + J;
					fprintf(stderr,"     0x%08x\n", (pid << 12));
				}
			}
		}
	}
}


//if logging is enabled,
//generate a signature
//and send it out to the Logger pipes
void generateLogMessage( ProcessorState *s)
{

	static int64_t log_counter = 0;

	uint32_t reg_write_log=0;
	uint32_t fp_reg_write_log=0;
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

	 fp_reg_write_log = assembleFpRegisterWriteSignature(
                                        f->fpreg_updated,
                                        0,
                                        (f->fsr_updated | f->ftt_updated | f->fcc_updated),
                                        0,
                                        f->fsr_updated,
                                        f->ftt_updated,
                                        f->fcc_updated,
                                        f->fpreg_double_word_write,
                                        f->fpreg_id,
                                        f->fsr_val,
                                        f->fpreg_val_high,
                                        f->fpreg_val_low);

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
	writeToLoggerPipe(s, reg_write_log);
	writeToLoggerPipe(s, fp_reg_write_log);
	writeToLoggerPipe(s, store_log);
	writeToLoggerPipe(s, pc_log);

	log_counter++;
}

	


uint8_t isBranchInstruction(Opcode op, InstructionType type)
{
	return ((op == _CALL_) || (op == _RETT_) || (op == _JMPL_) || (type == _CC_INS_) || (type == _TICC_INS_)); 
}

uint8_t isFloatCompareInstruction(Opcode op)
{
	return ((op == _FCMPs_) || (op == _FCMPd_) || (op == _FCMPq_) || (op == _FCMPEs_) || (op == _FCMPEd_) || (op == _FCMPEq_));
}

uint8_t fetchInstruction(ProcessorState* s,  
				uint8_t addr_space, uint32_t addr, uint32_t *inst, uint32_t* mmu_fsr)
{
	uint8_t mae_value;
	readInstruction(s->mmu_state, s->icache,  addr_space, addr, &mae_value, inst, mmu_fsr);
	setPageBit(s,addr);
	return mae_value;
}

void writeBackResult(RegisterFile* rf, uint8_t dest_reg, uint32_t result_h, uint32_t result_l, uint8_t flags, uint8_t cwp, uint32_t pc, StateUpdateFlags* reg_update_flags)
{
	uint8_t is_float_instruction = (getBit8(flags, _FLOAT_INSTRUCTION_) == 1);
	uint8_t is_double_result = (getBit8(flags, _DOUBLE_RESULT_) == 1);

	//IU write-back
	if(!is_float_instruction)
	{
		if(!is_double_result)
		{
			writeRegister(rf,  dest_reg, cwp, result_l);
		}
		else
		{
			writeRegister(rf,  setBit8(dest_reg, 0, 0), cwp, result_h);
			writeRegister(rf, setBit8(dest_reg, 0, 1), cwp, result_l);
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
		reg_update_flags->fpreg_updated = 1;
                reg_update_flags->fpreg_val_low = result_l;
                reg_update_flags->fpreg_id = dest_reg;

		if(!is_double_result)
		{
			writeFRegister(rf, dest_reg, result_l); 
		}
		else
		{
			dest_reg = setBit8(dest_reg, 0, 0) ;
			writeFRegister(rf, dest_reg, result_h);
			dest_reg = setBit8(dest_reg, 0, 1) ;
			writeFRegister(rf, dest_reg, result_l);

			reg_update_flags->fpreg_double_word_write = 1;
                        reg_update_flags->fpreg_val_high = result_h;
		}
	}
}

uint32_t completeFPExecution(ProcessorState* s,
			 	Opcode opcode, 
				uint32_t operand2_3, uint32_t operand2_2, 
				uint32_t operand2_1, uint32_t operand2_0, 
				uint32_t operand1_3, uint32_t operand1_2, 
				uint32_t operand1_1, uint32_t operand1_0,
				uint8_t dest_reg, StatusRegisters *ptr, uint32_t trap_vector)
{
	RegisterFile* rf = s->register_file;
	uint32_t tv, result_l2, result_l1, result_h2, result_h1;
	uint8_t texc, aexc, tem, c, tfcc;
	uint8_t flags = 0;
	uint8_t ft = 0;
	// StatusRegisters current_sr = *ptr; 

	tv = executeFPInstruction(s, opcode, operand2_3, operand2_2, operand2_1, operand2_0, operand1_3, operand1_2, operand1_1, operand1_0,
			&result_h2, &result_h1, &result_l2, &result_l1, trap_vector, &flags, &ft, ptr);
	c = getBit8(ft, 0);
	texc = getSlice8(ft, 5, 1);
	tfcc = getSlice8(ft, 7, 6);

	tem = getSlice32((*ptr).fsr, 27, 23);
	aexc = getSlice32((*ptr).fsr, 9, 5);

	uint8_t no_trap = (getBit32(tv, _TRAP_) == 0);
	uint8_t execute_fp_op =  no_trap;

	uint8_t no_fpu_present = (getBpFPUPresent(s) == 0);
	uint8_t unimplemented = execute_fp_op && no_fpu_present;
	if(unimplemented)
	{
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _FP_EXCEPTION_, 1);
		ptr->fsr = setSlice32((*ptr).fsr, 16, 14, _UNIMPLEMENTED_FPOP_) ;

		s->reg_update_flags.ftt_updated = 1;
		s->reg_update_flags.fsr_val = ptr->fsr;

	}

	uint8_t incomplete = (c == 0);
	uint8_t unfinished = execute_fp_op && !no_fpu_present && incomplete;
	if(unfinished)
	{
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _FP_EXCEPTION_, 1) ;
		ptr->fsr = setSlice32((*ptr).fsr, 16, 14, _UNFINISHED_FPOP_) ;
		s->reg_update_flags.ftt_updated = 1;
		s->reg_update_flags.fsr_val = ptr->fsr;

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

		s->reg_update_flags.ftt_updated = 1;
		s->reg_update_flags.fsr_val = ptr->fsr;

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

	if(!(!no_exception || !is_single_result)) {

		 writeFRegister(rf,dest_reg, result_l1);

		s->reg_update_flags.fpreg_updated = 1;
                s->reg_update_flags.fpreg_val_low = result_l1;
                s->reg_update_flags.fpreg_id = dest_reg;

	}
	if( (is_double_result)) dest_reg = setBit8(dest_reg, 0, 0) ;

	if(!(!no_exception || !is_double_result)) {

		writeFRegister(rf,dest_reg, result_l2);

		s->reg_update_flags.fpreg_updated = 1;
                s->reg_update_flags.fpreg_id = dest_reg;
                s->reg_update_flags.fpreg_val_low = result_l1;
                s->reg_update_flags.fpreg_val_high = result_l2;
                s->reg_update_flags.fpreg_double_word_write = 1;

	}

	if( (is_double_result)) dest_reg = setBit8(dest_reg, 0, 1) ;
	if(!(!no_exception || !is_double_result)) writeFRegister(rf,dest_reg, result_l1);

	if( (is_quad_result)) dest_reg = setSlice8(dest_reg, 1, 0, 0) ;
	if(!(!no_exception || !is_quad_result))	writeFRegister(rf, dest_reg, result_h2);
	if( (is_quad_result)) dest_reg = setBit8(dest_reg, 0, 1) ;
	if(!(!no_exception || !is_quad_result))	writeFRegister(rf, dest_reg, result_h1);
	if( (is_quad_result)) dest_reg = setBit8(dest_reg, 1, 1) ;
	if(!(!no_exception || !is_quad_result))	writeFRegister(rf, dest_reg, result_l1);
	if( (is_quad_result)) dest_reg = setBit8(dest_reg, 0, 0) ;
	if(!(!no_exception || !is_quad_result)) writeFRegister(rf, dest_reg, result_l2);

	uint8_t compare_inst = no_exception && isFloatCompareInstruction(opcode);

	if( (compare_inst)){
		 ptr->fsr = setSlice32((*ptr).fsr, 11, 10, tfcc) ;

		 s->reg_update_flags.fcc_updated = 1;
		 s->reg_update_flags.fsr_val = ptr->fsr;
	}

	if( (no_exception)) ptr->fsr = setSlice32((*ptr).fsr, 16, 14, 0) ;

	return tv;
}

uint32_t wim(ProcessorState* s)
{
	return(s->status_reg.wim);
}

uint32_t stack_pointer(ProcessorState* s)
{	
	// Stack pointer is register o6 that is r14.
	uint32_t ret_val = readRegister(s->register_file, 14, (s->status_reg.psr & 0x7));
	return(ret_val);
}

uint32_t frame_pointer(ProcessorState* s)
{
	// Stack pointer is register i6 that is r30.
	uint32_t ret_val = readRegister(s->register_file, 30, (s->status_reg.psr & 0x7));
	return(ret_val);
}

void initBranchPredictorState(BranchPredictorState* bps, uint32_t tsize)
{
	bps->table_size = tsize;
	bps->pc_tags    = (uint32_t*) malloc(tsize*sizeof(uint32_t));
	bps->nnpc_values = (uint32_t*) malloc(tsize*sizeof(uint32_t));
}

void resetBranchPredictorState(BranchPredictorState* bps)
{
	bps->mispredicts = 0;
	bps->branch_count = 0;

	int I;
	for(I=0; I < bps->table_size; I++)
		bps->pc_tags[I] = 0;
}

void addBranchPredictEntry (BranchPredictorState* bps, uint32_t pc, uint32_t nnpc)
{
	// insert at random
	uint32_t index = (pc >> 2) % bps->table_size;
	bps->pc_tags[index] = pc | 1;
	bps->nnpc_values[index] = nnpc;	
}

int branchPrediction(BranchPredictorState* bps, uint32_t pc, uint32_t* bp_idx, uint32_t* nnpc)
{
	int ret_val = 0;
	*bp_idx = 0;

	uint32_t index = (pc >> 2) % bps->table_size;
	uint32_t pc_tag = bps->pc_tags[index];
	if(pc_tag & 0x1)
	{
		if(pc_tag == (pc | 1))
		{
			*nnpc = bps->nnpc_values[index];
			ret_val = 1;
			*bp_idx = index;
		}
	}

	bps->branch_count++;
	return(ret_val);
}
void updateBranchPredictEntry (BranchPredictorState* bps, uint32_t idx, uint32_t nnpc)
{
	bps->nnpc_values[idx] = nnpc;
}

void incrementMispredicts(BranchPredictorState* bps)
{
	bps->mispredicts++;
}
uint32_t numberOfMispredicts(BranchPredictorState* bps)
{
	return(bps->mispredicts);
}

uint32_t numberOfBranches(BranchPredictorState* bps)
{
	return(bps->branch_count);
}

