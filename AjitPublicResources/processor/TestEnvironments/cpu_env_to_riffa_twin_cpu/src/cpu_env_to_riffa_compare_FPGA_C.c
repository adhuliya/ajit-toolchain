#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpu_env_to_riffa_compare_FPGA_C.h>
#ifdef USE_GNUPTH
#include <pth.h>
#include <GnuPthUtils.h>
#else
#include <pthread.h>
#include <pthreadUtils.h>
#endif
#include <pipeHandler.h>
#include <Pipes.h>
#ifdef USE_SOCKPIPES
#include <SockPipes.h>
#else
#ifdef USE_RIFFA
#include <riffa.h>
static fpga_t* fpga = NULL;
#endif
#endif

//Include the C model of the cpu here
#include "CpuInterface.h"
#include "StartCpuThreads.h"
#include "RequestTypeValues.h"


MUTEX_DECL(riffa_access_mutex);
MUTEX_DECL(fpga_mutex);
MUTEX_DECL(stop_comparison_mutex);


//The following flag generates logs to a fixed-sized queue
#define GENERATE_LOGS

//Stats keeping
int mismatch_count=0;
int MISMATCHES_BEFORE_EXIT=20;
unsigned long int num_ifetch_requests=0;
unsigned long int num_dcache_requests=0;
unsigned long int IFETCH_PERIOD=1000000; //print out information after every IFETCH_PERIOD ifetch requests




#ifdef GENERATE_LOGS
#include "Logger.h"
#include "CpuLogger.h"
extern int is_twin_cpu_testbench;
#endif


void cetr_send_u64_to_cpu(uint64_t* uword, int n_64bit_words)
{

	int I;
#ifdef USE_SOCKPIPES
	sock_write_uint64_n("Riffa_to_CPU", uword, n_64bit_words);
	fprintf(stderr,"cetr_send_u64_to_cpu: sent %d words %" PRIx64 ".\n", n_64bit_words, uword);
	for(I=0;I < n_64bit_words; I++)
	{
		fprintf(stderr,"\t%" PRIx64 ".\n", uword[I]);
	}
#else
#ifdef USE_RIFFA

	MUTEX_LOCK(fpga_mutex);
	if(fpga == NULL)
	{
		fprintf(stderr,"\ncetr_send_u64_to_cpu: FPGA = NULL, skipped.\n");
	}
	else
	{
		// fpga-struct, buf-ptr, length in uint32's, dest-offset, last-flag, timeout
		int ret_stat = fpga_send(fpga,0,uword,n_64bit_words*2,0,1,0);	
		//fprintf(stderr,"cetr_send_u64_to_cpu: sent %d words %" PRIx64 ".\n", ret_stat, uword);
		//for(I=0;I < ret_stat; I++)
		//{
			//fprintf(stderr,"\t%" PRIx64 ".\n", uword[I]);
		//}
	}
	MUTEX_UNLOCK(fpga_mutex);
#else
	assert(0);
#endif
#endif
}


void cetr_get_u64_from_cpu(uint64_t* uword, int n_64bit_words)
{
#ifdef USE_SOCKPIPES
	sock_read_uint64_n("CPU_to_Riffa",uword, n_64bit_words);
	fprintf(stderr,"cetr_get_u64_to_cpu: received %lx.\n", uword);

#else
#ifdef USE_RIFFA


	MUTEX_LOCK(fpga_mutex);
	if(fpga == NULL)
	{
		fprintf(stderr,"\ncetr_get_u64_from_cpu: FPGA = NULL, skipped.\n");
	}
	else
	{
		int expected_word_count = (2*n_64bit_words);
		int recv = fpga_recv(fpga, 0, (void*) uword, expected_word_count, 5000);	
		if(recv < 0)
		{
			fprintf(stderr,"Error:cetr_get_u64_to_cpu: read error.. resetting the FPGA and returning 0's.\n");
			fpga_reset(fpga);
			memset((void*) uword, 0, expected_word_count*4);
		}
		else if(recv == 0)
		{
			fprintf(stderr,"Warning:cetr_get_u64_to_cpu: riffa bug? 0 bytes received.\n");
		}
	}

	MUTEX_UNLOCK(fpga_mutex);
#else
	assert(0);
#endif
#endif
}

void cetr_icache_to_cpu_daemon()
{
	while(1)
	{
		uint8_t buf[14];
		// read from icache pipes
		uint64_t data64 = read_uint64("ICACHE_to_CPU_instr_pair");
		uint8_t mae = read_uint8("ICACHE_to_CPU_mae");
		uint32_t mmu_fsr = read_uint32("ICACHE_to_CPU_fsr");

		*((uint64_t*) &(buf[0])) = data64;
		*((uint32_t*) &(buf[8])) = mmu_fsr;
		buf[12] = mae;
		buf[13] = 1;
		//send to the FPGA cpu
		write_uint8_n("noblock_icache_to_cpu", buf, 14);

		//also forward to C model
		write_uint64("C_ICACHE_to_CPU_instr_pair",data64);
		write_uint8 ("C_ICACHE_to_CPU_mae",mae);
		write_uint32("C_ICACHE_to_CPU_fsr",mmu_fsr);

#ifdef GENERATE_LOGS
		log_message("ICACHE_to_CPU : data = 0x%lx, mae = 0x%x, mmu_fsr=0x%x\n", data64, mae, mmu_fsr);
#endif	
	}
}

// return 1 if something found, else 0.
uint8_t cetr_icache_to_cpu_probe(uint64_t* data64, uint8_t* mae, uint32_t* mmu_fsr)
{
	uint8_t ret_val = 0;

	uint8_t buf[14];
	read_uint8_n("noblock_icache_to_cpu", buf, 14);

	if(buf[13] == 1)
	{
		*data64 = *((uint64_t*) &(buf[0]));
		*mmu_fsr = *((uint32_t*) &(buf[8]));
		*mae    = buf[12];
		ret_val = 1;
#ifndef USE_RIFFA
		fprintf(stderr,"cetr_icache_to_cpu_daemon: icache-data = %lx, mae = %x, mmu_fsr=%x\n", *data64, *mae, *mmu_fsr);
#endif
	}
	return(ret_val);
}

//STOP_COMPARISON:
//A global flag to indicate that comparison 
//between C and FPGA models should be stopped.
//the flag is set whenever a memory access is generated
//by gdb server or do_val.
uint8_t STOP_COMPARISON=0;
//STOP_COMPARISON_LOCAL has value always equal to STOP_COMPARISON
//but is used only by one thread, and so a mutex is not necessary
//for its use.
uint8_t STOP_COMPARISON_LOCAL=0;

void cetr_dcache_to_cpu_daemon()
{
	while(1)
	{
		uint8_t buf[10];
		// read from dcache pipes
		uint64_t data64 = read_uint64("DCACHE_to_CPU_data");
		uint8_t mae = read_uint8("DCACHE_to_CPU_mae");
			
		*((uint64_t*) &(buf[0])) = data64;
		buf[8] = mae;
		buf[9] = 1;
		
		//send to FPGA
		write_uint8_n("noblock_dcache_to_cpu", buf, 10);
		
		//also forward to C model
		//as long as STOP_COMPARISON ==1
		MUTEX_LOCK(stop_comparison_mutex);
		if(!STOP_COMPARISON)
		{
			write_uint64("C_DCACHE_to_CPU_data",data64);
			write_uint8 ("C_DCACHE_to_CPU_mae",mae);
		}
		MUTEX_UNLOCK(stop_comparison_mutex);
#ifdef GENERATE_LOGS
		log_message("DCACHE_to_CPU : data = 0x%lx, mae = 0x%x\n", data64, mae);
#endif
	}
}

uint8_t cetr_dcache_to_cpu_probe(uint64_t* data64, uint8_t* mae)
{
	uint8_t ret_val = 0;

	uint8_t buf[10];
	read_uint8_n("noblock_dcache_to_cpu", buf, 10);

	if(buf[9] == 1)
	{
		*data64 = *((uint64_t*)&buf);
		*mae    = buf[8];
		ret_val = 1;
#ifndef USE_RIFFA
		fprintf(stderr,"cetr_dcache_to_cpu_daemon: dcache-data = %lx, mae = %x.\n", *data64, *mae);
#endif
	}
	return(ret_val);
}

uint8_t cetr_irl_to_cpu_probe()
{
	uint8_t irl = read_uint8("ENV_to_AJIT_irl");
	return(irl);
}

uint8_t cetr_reset_to_cpu_probe()
{
	uint8_t rst = read_uint8("ENV_to_AJIT_reset");
	//also forward to C model...
	//write_uint8("C_ENV_to_AJIT_reset_in",rst);
	//...C model does a selft-reset. No need to forward 
	//the reset signal to the C model
	return(rst);
}

void cetr_debug_to_cpu_daemon()
{
	while(1)
	{
		uint8_t buf[5];
		uint32_t dbg_cmd = read_uint32("ENV_to_AJIT_debug_command");

		#ifndef USE_RIFFA
		fprintf(stderr,"cetr_debug_to_cpu_daemon: dbg_cmd = %x.\n",  dbg_cmd);
		#endif

		*((uint32_t*) &(buf[0])) = dbg_cmd;
		buf[4] = 1;
		write_uint8_n("noblock_debug_to_cpu", buf, 5);
	}
}

uint8_t cetr_debug_to_cpu_probe(uint32_t* dbg_cmd)
{
	uint8_t ret_val = 0;
	uint8_t buf[5];
	read_uint8_n("noblock_debug_to_cpu", buf, 5);
	if(buf[4] != 0)
	{
		*dbg_cmd = *((uint32_t*) &(buf[0]));
		ret_val = 1;
	}
	return(ret_val);
}


void cetr_probe_and_send_to_cpu(uint8_t counter)
{
	uint64_t icache_data  = 0;
	uint32_t mmu_fsr = 0;
	uint8_t  icache_mae   = 0;
	uint8_t  icache_valid = 0;

	uint64_t dcache_data  = 0;
	uint8_t  dcache_mae   = 0;
	uint8_t  dcache_valid = 0;

	uint8_t  reset = 0;
	uint8_t  irl = 0;

	uint32_t dbg_command  = 0;
	uint8_t  dbg_valid    = 0;

	icache_valid = cetr_icache_to_cpu_probe(&icache_data, &icache_mae, &mmu_fsr);
	dcache_valid = cetr_dcache_to_cpu_probe(&dcache_data, &dcache_mae);
	dbg_valid    = cetr_debug_to_cpu_probe(&dbg_command);
	reset	     = cetr_reset_to_cpu_probe();
	irl	     = cetr_irl_to_cpu_probe();


	uint64_t header = reset;
	header = (header << 8) | ((uint64_t) irl);
	header = (header << 8) | ((uint64_t) dbg_valid);
	header = (header << 8) | ((uint64_t) dcache_valid);
	header = (header << 8) | ((uint64_t) dcache_mae);
	header = (header << 8) | ((uint64_t) icache_valid);
	header = (header << 8) | ((uint64_t) icache_mae);
	header = (header << 8) | ((uint64_t) counter);

	
	uint64_t txbuf[4];
	txbuf[0] = header;
	txbuf[1] = icache_data;
	txbuf[2] = dcache_data;

	//
	// txbuf[3] = concat (dbg-command, mmu-fsr)
	//
	uint64_t dbg_mmu_fsr = dbg_command;
	dbg_mmu_fsr = (dbg_mmu_fsr << 32);
	dbg_mmu_fsr = dbg_mmu_fsr | mmu_fsr;
	txbuf[3] = dbg_mmu_fsr;

	#ifndef USE_RIFFA
	fprintf(stderr,"cetr_from_tb: reset=%x.\n", reset);
	#endif

	cetr_send_u64_to_cpu(txbuf, 4);
}

// receive info
// header     counter logger-valid icache-valid icache-asi dcache-valid dcache-asi debug-valid cpu-mode
// 	       8         8            8           8            8             8          8       8
// i_d_addr   icache-addr  dcache-addr
//             32            32
// dcache_data     dcache-data
//                   64
// debug_etc      d-req-type d-byte-mask debug-response
//                     8          8          32
// logger etc     ignored  value
//                  32       32
void cetr_analyse_and_send_to_testbench(uint64_t header, uint64_t i_d_addr, uint64_t dcache_data, uint64_t debug_etc, uint64_t logger_etc)
{

	uint8_t counter = (header >> 56) & 0xff;
	#ifndef USE_RIFFA
	fprintf(stderr,"cetr_analyse_and_send_to_testbench: counter=%d.\n", counter);
	#endif	

	uint8_t  logger_valid = (header >> 48) & 0xff;
	uint8_t  icache_valid  = (header >> 40) & 0xff;
	uint8_t  icache_asi  = (header >> 32) & 0xff;
	uint8_t  dcache_valid  = (header >> 24) & 0xff;
	uint8_t  dcache_asi  = (header >> 16) & 0xff;
	uint8_t  debug_valid = (header >> 8) & 0xff;
	uint8_t  processor_mode_valid = header & 0xff;

	uint32_t icache_addr = (i_d_addr >> 32);
	uint32_t dcache_addr = (i_d_addr & 0xffffffff);

	uint8_t  dcache_request_type = (debug_etc >> 40) & 0xff;
	uint8_t  dcache_byte_mask  = (debug_etc >> 32) & 0xff;
	uint32_t debug_response = debug_etc & 0xffffffff;
	uint32_t logger_response = logger_etc & 0xffffffff;
	uint8_t  processor_mode = (logger_etc >> 32) & 0xff;

	if(processor_mode_valid)
	{
		// processor_mode:
		//   irl trap-bit unused pmode
		//   7:4  3        2     1:0
		
		//forward processor_mode to the testbench
		write_uint8("AJIT_to_ENV_processor_mode", processor_mode);
		
		//forward the irl field to the C model
		//if the processor is in execute mode
		if((processor_mode&0x3)==0x2)
		{
			// inform the C-model about IRL which is coded into
			// the top 4-bits of the p-mode word
			uint8_t C_irl = processor_mode>>4;
			write_uint8("C_ENV_to_AJIT_irl",C_irl);
#ifdef GENERATE_LOGS
			log_message("Processor_mode=0x%x, C model was sent irl = 0x%x\n",processor_mode,C_irl);
#endif
		}

#ifndef USE_RIFFA
	fprintf(stderr,"cetr_listen_to_cpu_daemon: processor_mode = %d.\n", processor_mode);
#endif
	}


	if(logger_valid)
	{
		//forward to logger_comparison_daemon
		write_uint32("FPGA_AJIT_to_ENV_logger", logger_response);
		
	}
	if(icache_valid)
	{

		//forward to icache_comparison_daemon
		write_uint32("FPGA_CPU_to_ICACHE_addr", icache_addr);
		write_uint8("FPGA_CPU_to_ICACHE_asi", icache_asi);
	}
	if(dcache_valid)
	{
		//forward to dcache_comparison_daemon
		write_uint32("FPGA_CPU_to_DCACHE_addr", dcache_addr);
		write_uint64("FPGA_CPU_to_DCACHE_data", dcache_data);
		write_uint8 ("FPGA_CPU_to_DCACHE_asi", dcache_asi);
		write_uint8 ("FPGA_CPU_to_DCACHE_byte_mask", dcache_byte_mask);
		write_uint8 ("FPGA_CPU_to_DCACHE_request_type", dcache_request_type);
	}

	if(debug_valid)
	{
		//forward to the environment
		write_uint32("AJIT_to_ENV_debug_response", debug_response);
		#ifdef GENERATE_LOGS
		log_message("debug_response = %x.\n", debug_response);
		#endif
	}
}



void cetr_probe_and_send_to_testbench()
{
	uint64_t rxbuf[5];
	cetr_get_u64_from_cpu(rxbuf, 5);

	uint64_t header = rxbuf[0];
	uint64_t i_d_addr = rxbuf[1];
	uint64_t dcache_data = rxbuf[2];
	uint64_t debug_etc = rxbuf[3];
	uint64_t logger_etc = rxbuf[4];

	cetr_analyse_and_send_to_testbench(header, i_d_addr, dcache_data, debug_etc, logger_etc);
}

void icache_comparison_daemon()
{
	while(1)
	{
		//read values sent by the FPGA model
		uint32_t icache_addr=read_uint32("FPGA_CPU_to_ICACHE_addr");
		uint8_t  icache_asi=read_uint8("FPGA_CPU_to_ICACHE_asi");
		
		
		//print info after every IFETCH_PERIOD requests
		num_ifetch_requests++;
		if(num_ifetch_requests%IFETCH_PERIOD==0)
		{
			fprintf(stderr,"\n---------------------------------------------");
			fprintf(stderr,"\n num_ifetch_requests = %lu",num_ifetch_requests);
			fprintf(stderr,"\n num_dcache_requests = %lu",num_dcache_requests);
			#ifdef GENERATE_LOGS
			print_queue();
			#endif
			fprintf(stderr,"\n---------------------------------------------");
			fprintf(stderr,"\n");
		}

		//compare with the C model
		{
			uint32_t C_icache_addr=read_uint32("C_CPU_to_ICACHE_addr");
			uint8_t  C_icache_asi=read_uint8("C_CPU_to_ICACHE_asi")&0x7F;
			C_icache_addr=C_icache_addr&(0xFFFFFFF8);
			//we mask out the last 3 bits of addr 
			//because the FPGA model generates double-word 
			//aligned addresses only.


			if(!((C_icache_asi==(icache_asi&0x7F)) && (C_icache_addr==(icache_addr&0xFFFFFFF8))))
			{
				fprintf(stderr,"*********** MISMATCH ***********\n");
				fprintf(stderr,"C_CPU_to_ICACHE_asi = 0x%x,  CPU_to_ICACHE_asi = 0x%x \n",	C_icache_asi, icache_asi);
				fprintf(stderr,"C_CPU_to_ICACHE_addr = 0x%x, CPU_to_ICACHE_addr = 0x%x \n" ,C_icache_addr, icache_addr);
				
				#ifdef GENERATE_LOGS
				print_queue();
				#endif
				mismatch_count++;
				if(mismatch_count>=MISMATCHES_BEFORE_EXIT) exit(1);
			}
			else
			{

				#ifdef GENERATE_LOGS
				log_message("CPU_to_ICACHE : addr = 0x%x, asi = 0x%x.\n", icache_addr, icache_asi);
				#endif
			}
		}
		
		//forward to env
		write_uint32("CPU_to_ICACHE_addr", icache_addr);
		write_uint8("CPU_to_ICACHE_asi", icache_asi);
		#ifndef USE_RIFFA
		fprintf(stderr,"cetr_listen_to_cpu_daemon: cpu-to-icache addr = %x, asi = %x.\n", icache_addr, icache_asi);
		#endif

	}
}

void dcache_comparison_daemon()
{
	while(1)
	{
		
		//read values sent by the FPGA model
		uint32_t dcache_addr = read_uint32("FPGA_CPU_to_DCACHE_addr");
		uint64_t dcache_data = read_uint64("FPGA_CPU_to_DCACHE_data");
		uint8_t  dcache_asi  = read_uint8 ("FPGA_CPU_to_DCACHE_asi");
		uint8_t  dcache_byte_mask = read_uint8("FPGA_CPU_to_DCACHE_byte_mask");
		uint8_t  dcache_request_type = read_uint8("FPGA_CPU_to_DCACHE_request_type");
		
		//increment dcache request count
		num_dcache_requests++;

		//clear the top bit corresponding to thread head
		uint8_t req_type = dcache_request_type & 0x7F; 
		
		//Check if this is a memory access generated
		//by gdb/doval. In this case stop comparison
		//between the FPGA and the C models.
		if(req_type==REQUEST_TYPE_CCU_CACHE_READ || req_type==REQUEST_TYPE_CCU_CACHE_WRITE)
		{
			MUTEX_LOCK(stop_comparison_mutex);
			STOP_COMPARISON=1;
			STOP_COMPARISON_LOCAL=1;
			fprintf(stderr,"****STOP comparison\n");
			MUTEX_UNLOCK(stop_comparison_mutex);
		}
		else
		{
			//if STOP_COMPARISON was set,
			//and a new request has arrived,
			//reset the STOP_COMPARISON flag
			if(STOP_COMPARISON_LOCAL==1) 
			{
				MUTEX_LOCK(stop_comparison_mutex);
				STOP_COMPARISON=0;
				STOP_COMPARISON_LOCAL=0;
				fprintf(stderr,"****RESUME comparison\n");
				MUTEX_UNLOCK(stop_comparison_mutex);
			}
		}

		//compare with the C model
		if(!STOP_COMPARISON_LOCAL)
		{

			uint32_t C_dcache_addr = read_uint32("C_CPU_to_DCACHE_addr");
			uint64_t C_dcache_data = read_uint64("C_CPU_to_DCACHE_data");
			uint8_t  C_dcache_asi  = read_uint8 ("C_CPU_to_DCACHE_asi");
			uint8_t  C_dcache_byte_mask = read_uint8("C_CPU_to_DCACHE_byte_mask");
			uint8_t  C_dcache_request_type = read_uint8("C_CPU_to_DCACHE_request_type") & 0x7F;
			uint8_t  dcache_request_type_compare = dcache_request_type & 0x7F;

			uint8_t MISMATCH =0;
			
			if((C_dcache_request_type)==REQUEST_TYPE_STBAR )
			{
				//For STBAR requests, ignore comparison of all feilds
				//other than request_type.
				MISMATCH =  (!(C_dcache_request_type==dcache_request_type_compare));
			}
			else if((C_dcache_request_type)!=REQUEST_TYPE_WRITE || dcache_asi==0x13)
			{
				//For reads and flush instructions, ignore the byte_mask for comparison.
				MISMATCH =  (!( (C_dcache_addr==dcache_addr) 
						&& (C_dcache_data ==dcache_data)
						&& (C_dcache_asi==dcache_asi) 
						&&(C_dcache_request_type==dcache_request_type_compare)));
			}
			else
			{
					//For write requests, compare all feilds.
					MISMATCH = (!( (C_dcache_addr==dcache_addr) 
						&& (C_dcache_data ==dcache_data)
						&& (C_dcache_asi==dcache_asi) 
						&& (C_dcache_byte_mask==dcache_byte_mask)
						&&(C_dcache_request_type==dcache_request_type_compare)));
			}
			if(MISMATCH)
			{

				fprintf(stderr,"********** MISMATCH ********** \n: \
						C_CPU_to_DCACHE_addr		=0x%x, 	CPU_to_DCACHE_addr	      =0x%x \n \
						C_CPU_to_DCACHE_data            =0x%lx, CPU_to_DCACHE_data           =0x%lx \n \
						C_CPU_to_DCACHE_asi             =0x%x,  CPU_to_DCACHE_asi             =0x%x \n \
						C_CPU_to_DCACHE_byte_mask       =0x%x,  CPU_to_DCACHE_byte_mask       =0x%x \n \
						C_CPU_to_DCACHE_request_type    =0x%x,  CPU_to_DCACHE_request_type    =0x%x \n",\
						C_dcache_addr, dcache_addr,
						C_dcache_data, dcache_data,
						C_dcache_asi, dcache_asi,
						C_dcache_byte_mask, dcache_byte_mask,
						C_dcache_request_type, dcache_request_type_compare );
				
				
				#ifdef GENERATE_LOGS
				print_queue();
				#endif
				mismatch_count++;
				if(mismatch_count>=MISMATCHES_BEFORE_EXIT) exit(1);

			}
		}

		//forward to env		
		write_uint32("CPU_to_DCACHE_addr", dcache_addr);
		write_uint64("CPU_to_DCACHE_data", dcache_data);
		write_uint8("CPU_to_DCACHE_asi", dcache_asi);
		write_uint8("CPU_to_DCACHE_byte_mask", dcache_byte_mask);
		write_uint8("CPU_to_DCACHE_request_type", dcache_request_type);
		
		#ifdef GENERATE_LOGS
		log_message("CPU_to_DCACHE : addr = %x, data = %lx,  asi = %x, byte-mask = %x, req-type = %d. \n", dcache_addr, dcache_data, dcache_asi, dcache_byte_mask, dcache_request_type);
		#endif

		#ifndef USE_RIFFA
		fprintf(stderr,"cetr_listen_to_cpu_daemon: cpu-to-dcache addr = %x, data = %lx,  asi = %x, byte-mask = %x, req-type = %d. \n", dcache_addr, dcache_data, dcache_asi, dcache_byte_mask, dcache_request_type);
		#endif

	}
}	

void logger_comparison_daemon()
{
	while(1)
	{
		//read log sent by the FPGA model
		uint32_t FPGA_log = read_uint32("FPGA_AJIT_to_ENV_logger");
		
		//compare with the C model
		if(!STOP_COMPARISON_LOCAL)
		{
			uint32_t C_log = read_uint32("C_AJIT_to_ENV_logger");
			if(!( C_log == FPGA_log))
			{

				fprintf(stderr,"********** MISMATCH ********** \n");
				fprintf(stderr,"C_AJIT_to_ENV_logger=0x%x, AJIT_to_ENV_logger=0x%x\n ",C_log, FPGA_log);
				#ifdef GENERATE_LOGS
				print_queue();
				#endif
				mismatch_count++;
				if(mismatch_count>=MISMATCHES_BEFORE_EXIT) exit(1);

			}
		}

		//forward to the environment
		write_uint32("AJIT_to_ENV_logger", FPGA_log);
		
		#ifdef GENERATE_LOGS
		log_message("AJIT_to_ENV_logger: logger_response=0x%x\n", FPGA_log);
		#endif

	}
}


void cetr_interface_daemon()
{
	uint16_t counter = 0;
#ifdef GENERATE_LOGS
	reset_logger();
	is_twin_cpu_testbench=1;
#endif
	while(1)
	{
		cetr_probe_and_send_to_cpu(counter);
		cetr_probe_and_send_to_testbench();
		counter++;
	}
}


DEFINE_THREAD(cetr_icache_to_cpu_daemon);
DEFINE_THREAD(cetr_dcache_to_cpu_daemon);
DEFINE_THREAD(cetr_debug_to_cpu_daemon);
DEFINE_THREAD(cetr_interface_daemon);
DEFINE_THREAD(icache_comparison_daemon);
DEFINE_THREAD(dcache_comparison_daemon);
DEFINE_THREAD(logger_comparison_daemon);

PTHREAD_DECL(cetr_icache_to_cpu_daemon);
PTHREAD_DECL(cetr_dcache_to_cpu_daemon);
PTHREAD_DECL(cetr_debug_to_cpu_daemon);
PTHREAD_DECL(cetr_interface_daemon);
PTHREAD_DECL(icache_comparison_daemon);
PTHREAD_DECL(dcache_comparison_daemon);
PTHREAD_DECL(logger_comparison_daemon);

void cetr_start_daemons()
{
	int depth = 2;
	fprintf(stderr,"In cetr_start_daemons().\n");
#ifdef USE_RIFFA
	MUTEX_LOCK(fpga_mutex);
	fpga = fpga_open(0);
	if(fpga == NULL)	
	{
		fprintf(stderr,"Error: could not open FPGA.\n");
		return;
	}
	else
	{
		fprintf(stderr,"FPGA opened successfully\n");
	}
	fpga_reset(fpga);
	MUTEX_UNLOCK(fpga_mutex);
#endif

	register_signal ("ENV_to_AJIT_irl", 8);
	set_pipe_is_read_from ("ENV_to_AJIT_irl");
	register_signal ("ENV_to_AJIT_reset", 8);
	set_pipe_is_read_from ("ENV_to_AJIT_reset");
	register_pipe ("ENV_to_AJIT_debug_command", depth, 32, 0);
	set_pipe_is_read_from ("ENV_to_AJIT_debug_command");

	register_pipe ("CPU_to_DCACHE_addr", depth, 32, 0);
	set_pipe_is_written_into ("CPU_to_DCACHE_addr");
	register_pipe ("CPU_to_DCACHE_asi", depth, 8, 0);
	set_pipe_is_written_into ("CPU_to_DCACHE_asi");
	register_pipe ("CPU_to_DCACHE_byte_mask", depth, 8, 0);
	set_pipe_is_written_into ("CPU_to_DCACHE_byte_mask");
	register_pipe ("CPU_to_DCACHE_data", depth, 64, 0);
	set_pipe_is_written_into ("CPU_to_DCACHE_data");
	register_pipe ("CPU_to_DCACHE_request_type", depth, 8, 0);
	set_pipe_is_written_into ("CPU_to_DCACHE_request_type");
	register_pipe ("CPU_to_ICACHE_addr", depth, 32, 0);
	set_pipe_is_written_into ("CPU_to_ICACHE_addr");
	register_pipe ("CPU_to_ICACHE_asi", depth, 8, 0);
	set_pipe_is_written_into ("CPU_to_ICACHE_asi");

	register_pipe ("AJIT_to_ENV_debug_response", depth, 32, 0);
	set_pipe_is_written_into ("AJIT_to_ENV_debug_response");

	// note: changed to blocking pipe.
	int processor_mode_depth=1;
	register_pipe ("AJIT_to_ENV_processor_mode", processor_mode_depth, 8, 0);
	set_pipe_is_written_into ("AJIT_to_ENV_processor_mode");

	register_pipe ("DCACHE_to_CPU_data", depth, 64, 0);
	set_pipe_is_read_from ("DCACHE_to_CPU_data");
	register_pipe ("DCACHE_to_CPU_mae", depth, 8, 0);
	set_pipe_is_read_from ("DCACHE_to_CPU_mae");

	register_pipe ("ICACHE_to_CPU_instr_pair", depth, 64, 0);
	set_pipe_is_read_from ("ICACHE_to_CPU_instr_pair");
	register_pipe ("ICACHE_to_CPU_mae", depth, 8, 0);
	set_pipe_is_read_from ("ICACHE_to_CPU_mae");
	register_pipe ("ICACHE_to_CPU_fsr", depth, 32, 0);
	set_pipe_is_read_from ("ICACHE_to_CPU_fsr");

	//intermediate pipes used by the comparison daemons
	int FPGA_pipe_depth =1;
	register_pipe("FPGA_CPU_to_ICACHE_addr", FPGA_pipe_depth, 32, 0);
	register_pipe("FPGA_CPU_to_ICACHE_asi", FPGA_pipe_depth, 8, 0);
	register_pipe("FPGA_CPU_to_DCACHE_addr", FPGA_pipe_depth, 32, 0);
	register_pipe("FPGA_CPU_to_DCACHE_data", FPGA_pipe_depth, 64, 0);
	register_pipe("FPGA_CPU_to_DCACHE_asi", FPGA_pipe_depth, 8, 0);
	register_pipe("FPGA_CPU_to_DCACHE_byte_mask", FPGA_pipe_depth, 8, 0);
	register_pipe("FPGA_CPU_to_DCACHE_request_type", FPGA_pipe_depth, 8, 0);
	register_pipe("FPGA_AJIT_to_ENV_logger", FPGA_pipe_depth, 32, 0);

	set_pipe_is_read_from("FPGA_CPU_to_ICACHE_addr");
	set_pipe_is_read_from("FPGA_CPU_to_ICACHE_asi");
	set_pipe_is_read_from("FPGA_CPU_to_DCACHE_addr");
	set_pipe_is_read_from("FPGA_CPU_to_DCACHE_data");
	set_pipe_is_read_from("FPGA_CPU_to_DCACHE_asi");
	set_pipe_is_read_from("FPGA_CPU_to_DCACHE_byte_mask");
	set_pipe_is_read_from("FPGA_CPU_to_DCACHE_request_type");
	set_pipe_is_read_from("FPGA_AJIT_to_ENV_logger");
	
	set_pipe_is_written_into("FPGA_CPU_to_ICACHE_addr");
	set_pipe_is_written_into("FPGA_CPU_to_ICACHE_asi");
	set_pipe_is_written_into("FPGA_CPU_to_DCACHE_addr");
	set_pipe_is_written_into("FPGA_CPU_to_DCACHE_data");
	set_pipe_is_written_into("FPGA_CPU_to_DCACHE_asi");
	set_pipe_is_written_into("FPGA_CPU_to_DCACHE_byte_mask");
	set_pipe_is_written_into("FPGA_CPU_to_DCACHE_request_type");
	set_pipe_is_written_into("FPGA_AJIT_to_ENV_logger");

	// nonblocking pipes used internally..
	register_pipe("noblock_icache_to_cpu", 14, 8, 2); //noblock-pipe
	register_pipe("noblock_dcache_to_cpu", 10, 8, 2); //noblock-pipe
	register_pipe("noblock_debug_to_cpu", 5, 8, 2); //noblock-pipe
	
	//start threads corresponding to C model of the cpu
	start_C_cpu_threads();

	PTHREAD_CREATE(cetr_icache_to_cpu_daemon);
	PTHREAD_CREATE(cetr_dcache_to_cpu_daemon);
	PTHREAD_CREATE(cetr_debug_to_cpu_daemon);
	PTHREAD_CREATE(cetr_interface_daemon);
	PTHREAD_CREATE(icache_comparison_daemon);
	PTHREAD_CREATE(dcache_comparison_daemon);
	PTHREAD_CREATE(logger_comparison_daemon);
}

void cetr_stop_daemons()
{
	PTHREAD_CANCEL(cetr_icache_to_cpu_daemon);
	PTHREAD_CANCEL(cetr_dcache_to_cpu_daemon);
	PTHREAD_CANCEL(cetr_debug_to_cpu_daemon);
	PTHREAD_CANCEL(cetr_interface_daemon);
	PTHREAD_CANCEL(icache_comparison_daemon);
	PTHREAD_CANCEL(dcache_comparison_daemon);
	PTHREAD_CANCEL(logger_comparison_daemon);

#ifdef USE_RIFFA
	MUTEX_LOCK(fpga_mutex);
	if(fpga != NULL)
	{
		fpga_close(fpga);
		fpga = NULL;
	}
	MUTEX_UNLOCK(fpga_mutex);
#endif
}
