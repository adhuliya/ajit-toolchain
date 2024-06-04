#ifndef __AJIT_HW_CONFIG_H__
#define  __AJIT_HW_CONFIG_H__

// Ajit_Hardware_Configuration.h
// Global Cofiguration settings for the Ajit processor model

#define MAX_NCORES 		4
#define MAX_NTHREADS_PER_CORE 	2



//---------------------------------
//Cpu parameters
//---------------------------------
//The reset values for pc and npc.
//
//Booting linux kernel requires these values to be 0x00000000 and 0x00000004
//Other processor validation tests assume this value to be 0xf0004000 and 0xf0004004.

//For C/asm test programs :
#define PC_RESET_VALUE 	0x0
#define NPC_RESET_VALUE	0x4

//
// instruction data buffer parameters.
//
#define INSTRUCTION_BUFFER_N_ENTRIES	     128	 // 1KB
#define INSTRUCTION_BUFFER_ASSOCIATIVITY       1

//
//  data buffer parameters.
//
#define DATA_BUFFER_N_ENTRIES	     128	 // 1KB
#define DATA_BUFFER_ASSOCIATIVITY       1



//---------------------------------
// Cache Parameters.
//---------------------------------
#define BYTES_PER_CACHE_LINE 		64
#define LOG_BYTES_PER_CACHE_LINE 	6





//----------------------------------
//Memory Parameters
//----------------------------------
#define LOG_OF_MEMORY_SIZE 	32 //4 GB of main memory
#define MEMORY_SIZE 		(1<<LOG_OF_MEMORY_SIZE) //memory size in Bytes
//----------------------------------



//----------------------------------
// MMU Parameters
//----------------------------------
//TLB_ENABLED:
//This option is applicable only when 
//the real MMU is used (USE_DUMMY_MMU =0)
//If set to 1, TLB is enabled.
#define TLB_ENABLED	1

//TLB_SIZE
//Relevant only when USE_DUMMY_MMU =0 and TLB_ENABLE=1
//Sets the number of TLB entries.
#define TLB_SIZE	64

//ASI definitions needed in the 
//Ajit-specific code for Linux kernel
#define AJIT_ASI_MMU_BYPASS 0x20
//----------------------------------



//Devices:
//**** NOTE: all device register addresses must be word-aligned.

#define USE_INTERRUPT_CONTROLLER_MODEL 1
#define USE_TIMER_MODEL 1
#define USE_SERIAL_MODEL 1
#define USE_SCRATCH_PAD_MODEL 1


//----------------------------------
//Interrupt Controller parameters
//----------------------------------
//If set to 1, a thread modelling the interurpt controller
//is started.

//Interrupt levels for interrupting sources in basic system
#define TIMER_IRL    10
#define SERIAL_IRL   12
#define IPI_IRL      13
#define EXTERNAL_IRL 14


//----------------------------------
//Timer Parameters
//----------------------------------
//If USE_TIMER_MODEL is set to 1,
//a thread to model a timer is created.
//the timer thread is connected to memoryAccess thread
//using pipes. The memory access thread examines the 
//address of each memory reference. If it is equal to
//the timer-register address, the memoryAccess forwards the access
//to the timer, else performs read/write on memory.

#define TIMER_TICK_VIRTUAL_FREQUENCY 100000
#define TIMER_TICK_REAL_FREQUENCY 100 
//frequency of clock source to the timer.
//TIMER_TICK_REAL_FREQUENCY is the real frequency,
//and TIMER_TICK_VIRTUAL_FREQUENCY is the frequency 
//that linux kernel thinks exists. We so this
//because simulation is about a 1000x slower than
//real hardware
//----------------------------------



//----------------------------------
//Console
//----------------------------------
//The console consists of input and output threads.
//The input thread keeps waiting for user input (keystroke)
//and sends the received character to the serial device on the CONCOLE_to_SERIAL_RX line
//The output thread reads characters sent by the serial device on SERIAL_TX_to_CONSOLE line and displays them on the screen.

#define ENABLE_CONSOLE_OUTPUT 1
//If set to 1, start console output thread
#define ENABLE_CONSOLE_INPUT 1
//If set to 1, start console input thread



// estimates of penalties..
#define TLB_MISS_PENALTY   	250
#define CACHE_MISS_PENALTY  	70
#define IU_DIV_PENALTY      	30

#define FP_SP_DIV_PENALTY      	16
#define FP_DP_DIV_PENALTY      	24

#define FP_SP_SQROOT_PENALTY    16
#define FP_DP_SQROOT_PENALTY    24

#define TRAP_PENALTY		16
#define CTI_MISPREDICT_PENALTY   4


// invalidate queue size.
#define INVALIDATE_QUEUE_SIZE	1024

typedef   struct __ThreadArchDescription {
	int fpu_not_present;
	int div_not_present;
} ThreadArchDescription;


typedef   struct __CoreArchDescription {
	int has_multi_context_munit;
	int mmu_not_present;
	ThreadArchDescription thread_descriptions[MAX_NTHREADS_PER_CORE];
} CoreArchDescription;

void initCoreArchDescriptions();

// descr format
//    <core-id>:<thread-id>:<fp/nofp>:<mmu/nommu>
//
//    example  0:1:fp:nommu
//
//    means  for core 0, thread 1, fp is enabled, mmu is disabled.
int setArchitectureDescription(char* descr);

int isMmuPresent (int core_id);
int hasMultiContextMunit (int core_id);
int isFpuPresent  (int core_id, int thread_id); 
int isDivPresent  (int core_id, int thread_id);

 #endif
