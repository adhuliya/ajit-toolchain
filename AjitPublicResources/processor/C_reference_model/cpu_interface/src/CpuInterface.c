//CpuInterfaces.c

//cpu interface to other blocks.
//Implemented as pipes.
//
//AUTHORS: 	Sarath Mohan
//		Neha Karanjkar


#include <stdint.h>
#include "Ancillary.h"
#include "Pipes.h"
#include "CpuInterface.h"
#ifdef SW
	#include <stdio.h>
#endif



//#define REQUEST_TYPE_IFETCH  0
//#define REQUEST_TYPE_READ   1
//#define REQUEST_TYPE_WRITE  2
//#define REQUEST_TYPE_STBAR  3
//#define REQUEST_TYPE_WRFSRFAR  4



//read an Instruction by accessing the instruction fetch interface
void readInstruction(uint8_t asi, uint32_t addr, uint8_t* mae, uint32_t *inst, uint32_t* mmu_fsr)
{

	uint64_t instr64;
	
	//send request
	write_uint8 ("CPU_to_ICACHE_asi"	 , (asi | 0x80));  // set the top bit of the asi to 1 to indicate "thread head"
	write_uint32("CPU_to_ICACHE_addr"	 , addr);
	
	//read response
	*mae 	= read_uint8 ("ICACHE_to_CPU_mae");
	*mae 	= (*mae & 0x1);

	instr64	= read_uint64("ICACHE_to_CPU_instr_pair");
	*mmu_fsr	= read_uint32("ICACHE_to_CPU_fsr");
	
	//check if we need to return the even or odd word
	if(getBit32(addr,2)) *inst = instr64;
	else *inst = instr64>>32;

#ifdef DEBUG
	printf("\nCPU : IFETCH addr=0x%x, asi=0x%x, Instruction Fetched = 0x%x, MAE = 0x%x, MMU_FSR=0x%x",addr, asi, *inst, *mae, *mmu_fsr);
#endif
}



//Request ICACHE to flush line containing a given doubleword.
//returns mae=0 after flush is complete
void flushIcacheLine(uint8_t asi, uint32_t addr, uint8_t* mae)
{

	
	//send request
	write_uint8 ("CPU_to_ICACHE_asi"	 , (asi | 0x80) ); // set the top bit of the asi to 1 to indicate "thread head"
	write_uint32("CPU_to_ICACHE_addr"   	 , addr);
	
	//read response
	*mae 	= read_uint8 ("ICACHE_to_CPU_mae");
	*mae 	= (*mae & 0x1);
	read_uint64("ICACHE_to_CPU_instr_pair");
	uint32_t mmu_fsr = read_uint32("ICACHE_to_CPU_fsr");

#ifdef DEBUG
	printf("\nCPU : ICACHE FLUSH addr=0x%x, asi=0x%x, MAE=0x%x, MMU_FSR=0x%x",addr, asi, *mae, mmu_fsr);
#endif
	return;
}

//Read a doubleword from Dcache
void readData64Base(uint8_t debug_flag, uint8_t asi, uint32_t addr, uint8_t* mae, uint64_t *data64)
{

	uint8_t  request_type = (debug_flag ? REQUEST_TYPE_CCU_CACHE_READ : (REQUEST_TYPE_READ | IS_NEW_THREAD));
	if(asi==0)
	{
		printf("\nCPU : Trying to read data with asi =0 ! addr=0x%x",addr);
		//set breakpoint here
		exit(1);
	}

	//make sure the address is double-word-aligned
	//clear the last 3 bits.
	addr=addr&(0xFFFFFFF8);

	//send request
	write_uint8 ("CPU_to_DCACHE_asi"	 , asi);
	write_uint32("CPU_to_DCACHE_addr"	 , addr);
	write_uint8 ("CPU_to_DCACHE_request_type", request_type);
	write_uint8 ("CPU_to_DCACHE_byte_mask"   ,0);
	write_uint64("CPU_to_DCACHE_data",0);
	
	//read response
	*mae 	= read_uint8 ("DCACHE_to_CPU_mae");
	*mae 	= (*mae & 0x1);

	*data64	= read_uint64("DCACHE_to_CPU_data");
}

//read a word from DCACHE.
void readDataBase(uint8_t debug_flag, uint8_t asi, uint32_t addr, uint8_t* mae, uint32_t *data)
{

	uint64_t data64;
	readData64Base(debug_flag, asi, addr, mae, &data64);
	if(getBit32(addr,2)) 
		*data = data64;
	else
		*data = (data64)>>32;
}

void readData(uint8_t asi, uint32_t addr, uint8_t* mae, uint32_t *data)
{
	readDataBase(0,asi,addr,mae,data);
	#ifdef DEBUG
	printf("\nCPU : DCACHE READ WORD addr=0x%x, asi=0x%x, WORD read = 0x%x, MAE = 0x%x",addr, asi, *data, *mae);
	#endif

}

void readDataToDebug(uint8_t asi, uint32_t addr, uint8_t* mae, uint32_t *data)
{
	readDataBase(1,asi,addr,mae,data);
	#ifdef DEBUG
	printf("\nCPU : DCACHE CCU READ WORD addr=0x%x, asi=0x%x, WORD read = 0x%x, MAE = 0x%x",addr, asi, *data, *mae);
	#endif
}
void readData64(uint8_t asi, uint32_t addr, uint8_t* mae, uint64_t *data)
{
	readData64Base(0,asi,addr,mae,data);
	#ifdef DEBUG
	printf("\nCPU : DCACHE READ DWORD addr=0x%x, asi=0x%x, DWORD read = 0x%lx, MAE = 0x%x",addr, asi, *data, *mae);
	#endif
}


// Write MMU FSR, FAR through DCACHE.
void updateMmuFsrFar(uint32_t mmu_fsr, uint32_t mmu_far)
{
	uint64_t data64 = 0;
	uint8_t mae;
	data64 = setSlice64(data64, 63,32, mmu_fsr);
	data64 = setSlice64(data64, 31,0,  mmu_far);

	write_uint8 ("CPU_to_DCACHE_asi"	 , 0);
	write_uint32("CPU_to_DCACHE_addr"	 , 0);
	write_uint8 ("CPU_to_DCACHE_request_type", REQUEST_TYPE_WRFSRFAR);
	write_uint8 ("CPU_to_DCACHE_byte_mask"   , 0);
	write_uint64("CPU_to_DCACHE_data"        , data64);

	printf("\nCPU: wrote FSR=0x%x, FAR=0x%x to MMU through DCACHE", mmu_fsr, mmu_far);

	mae 	= read_uint8 ("DCACHE_to_CPU_mae");
	mae 	= (mae & 0x1);

	data64 	= read_uint64("DCACHE_to_CPU_data");
	
	#ifdef DEBUG
	printf("\nCPU : MMU FSR FAR UPDATE. FSR=0x%x, FAR=0x%x to MMU through DCACHE", mmu_fsr, mmu_far);
	#endif

}

//write a double word (with a byte mask) to DCACHE.
void writeData64Base(uint8_t debug_flag, uint8_t asi, uint32_t addr, uint8_t byte_mask, uint64_t data64, uint8_t* mae)
{

	uint8_t  request_type = (debug_flag ? REQUEST_TYPE_CCU_CACHE_WRITE : (REQUEST_TYPE_WRITE | IS_NEW_THREAD));
	if(asi==0)
	{
		printf("\nCPU : Trying to write data with asi =0 ! addr=0x%x",addr);
		//set breakpoint here
	}
	
	//make sure the address is double-word-aligned
	//clear the last 3 bits.
	addr=addr&(0xFFFFFFF8);

	//send request
	write_uint8 ("CPU_to_DCACHE_asi"	 , asi);
	write_uint32("CPU_to_DCACHE_addr"	 , addr);
	write_uint8 ("CPU_to_DCACHE_request_type", request_type);
	write_uint8 ("CPU_to_DCACHE_byte_mask"   , byte_mask);
	write_uint64("CPU_to_DCACHE_data"        , data64);

	
	//read response
	*mae 	= read_uint8 ("DCACHE_to_CPU_mae");
	*mae 	= (*mae & 0x1);

	uint64_t data64_read = read_uint64("DCACHE_to_CPU_data");

	#ifdef DEBUG
	printf("\nCPU : DCACHE WRITE addr=0x%x, asi=0x%x, request_type=0x%x, byte_mask=0x%x, data64 = 0x%lx, MAE = 0x%x",addr, asi, request_type, byte_mask, data64, *mae);
	#endif
}

void writeDataBase(uint8_t debug_flag, uint8_t asi, uint32_t addr, uint8_t byte_mask, uint32_t data, uint8_t* mae)
{

	uint64_t data64 = data;
	if(getBit32(addr,2)==0)
	{
		byte_mask=byte_mask<<4;
		data64=data64<<32;
	}
	writeData64Base(debug_flag, asi, addr, byte_mask, data64, mae);

}

void writeData64( uint8_t asi, uint32_t addr, uint8_t byte_mask, uint64_t data, uint8_t* mae)
{
	writeData64Base(0,asi,addr,byte_mask, data, mae);
}

void writeData( uint8_t asi, uint32_t addr, uint8_t byte_mask, uint32_t data, uint8_t* mae)
{
	writeDataBase(0,asi,addr,byte_mask, data, mae);
}

void writeDataFromDebug( uint8_t asi, uint32_t addr, uint8_t byte_mask, uint32_t data, uint8_t* mae)
{
	writeDataBase(1,asi,addr,byte_mask, data, mae);
}

void sendSTBAR()
{
	//send an STBAR request to the Dcache

	//send request
	write_uint8 ("CPU_to_DCACHE_asi"	 , 0);
	write_uint32("CPU_to_DCACHE_addr"	 , 0);
	write_uint8 ("CPU_to_DCACHE_request_type", REQUEST_TYPE_STBAR | IS_NEW_THREAD);
	write_uint8 ("CPU_to_DCACHE_byte_mask"   , 0);
	write_uint64("CPU_to_DCACHE_data"        , 0);
	
	//read response, and ignore it
	read_uint8 ("DCACHE_to_CPU_mae");
	read_uint64("DCACHE_to_CPU_data");
	#ifdef DEBUG
	printf("\nCPU : Sent STBAR request to the Dcache");
	#endif

}

//--------------------------------------------------
//CPU Interfaces implemented as signals :
//--------------------------------------------------
//flags internal to the CPU
uint8_t bp_reset;
uint8_t bp_irl;

//functions to read interface pipes and set internal flags:
//void readBpIRL() { while(1) { bp_irl = read_uint8("ENV_to_AJIT_IRL"); }}
//void readBpReset() { while(1) { bp_reset = read_uint8("ENV_to_AJIT_reset_in"); }}
uint8_t getBpIRL() 
{
	//
	// ENV_to_AJIT_irl is read by interrupt controller
	// which will produce ENV_to_CPU_irl
	//
	bp_irl = read_uint8("ENV_to_CPU_irl"); 
	return bp_irl; 
}


#ifdef SW
//In the software model of the cpu, 
//reset should read as high, the first time 
//it is examined, and LOW for all subsequent reads.
int BpReset_called_once = 0;
uint8_t getBpReset()
{
	if(BpReset_called_once)
		return 0;
	else
	{
		BpReset_called_once=1;
		return 1;
	}
}
#else
//in the hardware model, reset is determined
//by reading from the interface pipe.
uint8_t getBpReset(){return bp_reset;}
#endif




//input signals to the cpu hardwired to 
//a certain value in the Ajit processor:
uint8_t bp_fpu_present = 1;
uint8_t bp_fpu_exception = 0;
uint8_t bp_fpu_cc;
uint8_t bp_cp_present = 0;
uint8_t bp_cp_exception = 0;
uint8_t bp_cp_cc=0;

uint8_t getBpFPUPresent() { return bp_fpu_present; } 
uint8_t getBpFPUException() { return bp_fpu_exception; }
uint8_t getBpFPUCc() { return bp_fpu_cc; }
uint8_t getBpCPPresent() { return bp_cp_present; }
uint8_t getBpCPException() { return bp_cp_exception; }
uint8_t getBpCPCc() { return bp_cp_cc; }


//output interfaces implemented as signals
uint8_t pb_error = 0;
uint8_t pb_block_ldst_word = 0;
uint8_t pb_block_ldst_byte = 0;


void setPbError( uint8_t val)
{
		pb_error = val;
		write_uint8("AJIT_to_ENV_error", val);
}

void setPbBlockLdstWord( uint8_t val)
{
                pb_block_ldst_word = val;
                //write_uint8("pb_block_ldst_word", val); 
}

void setPbBlockLdstByte( uint8_t val)
{
                pb_block_ldst_byte = val;
                //write_uint8("pb_block_ldst_byte", val); // TODO
}

uint8_t getPbError()
{
	return pb_error;
}

uint8_t getPbBlockLdstWord()
{
	return pb_block_ldst_word;
}

uint8_t getPbBlockLdstByte()
{
	return pb_block_ldst_byte;
}

//send a signature to logger pipe
void writeToLoggerPipe( uint32_t word)
{
	write_uint32("AJIT_to_ENV_logger", word);
}

