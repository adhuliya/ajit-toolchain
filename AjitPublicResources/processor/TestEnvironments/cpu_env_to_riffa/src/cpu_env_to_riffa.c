#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpu_env_to_riffa.h>
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

MUTEX_DECL(riffa_access_mutex);
MUTEX_DECL(fpga_mutex);

unsigned long int num_ifetch_requests=0;
unsigned long int num_dcache_requests=0;
unsigned long int IFETCH_PERIOD=1000000; //print out information after every IFETCH_PERIOD ifetch requests


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

#ifdef USE_RIFFA
int receiveFromFPGA(int MAX_TRIES, uint64_t* uword, int expected_word_count)
{
	int received_word_count  = 0;
	uint32_t* uword_32_ptr = (uint32_t*) uword;
	while(received_word_count < expected_word_count)
	{
		int recv = fpga_recv(fpga, 0, (void*) (uword_32_ptr+received_word_count), 
				expected_word_count - received_word_count, 5000);	
		received_word_count += recv;
		MAX_TRIES--;
		if(MAX_TRIES == 0)
			break;
	}
	return(received_word_count);
}
#endif

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
		else if (recv < expected_word_count)
		{
			fprintf(stderr,"Warning:cetr_get_u64_to_cpu: possible incomplete read..  data may have been lost.. \n");
		}
	}
	MUTEX_UNLOCK(fpga_mutex);
#else
	assert(0);
#endif
#endif
}


#ifndef proto_board
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
		write_uint8_n("noblock_icache_to_cpu", buf, 14);
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
		write_uint8_n("noblock_dcache_to_cpu", buf, 10);
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
#endif


#ifdef proto_board
	void cetr_mem_to_cpu_daemon()
	{
		while(1)
		{
			uint8_t buf[13];
			// read from mem pipes
			uint64_t instr_pair = read_uint64("ENV_to_mem_initialize_instr_pair");
			uint32_t addr       = read_uint32("ENV_to_mem_initialize_instr_pair_addr");

			*((uint64_t*) &(buf[0])) = instr_pair;
			*((uint64_t*) &(buf[8])) = addr;

			buf[12] = 1;
			write_uint8_n("noblock_mem_to_cpu", buf, 13);
		}
	}

	uint8_t cetr_mem_to_cpu_probe(uint64_t* data64, uint32_t* addr)
	{
		uint8_t ret_val = 0;

		uint8_t buf[13];
		read_uint8_n("noblock_mem_to_cpu", buf, 13);
	
		if(buf[12] == 1)
		{
			*data64 = *((uint64_t*) &(buf[0]));
			*addr   = *((uint32_t*) &(buf[8]));
			ret_val = 1;

			#ifndef USE_RIFFA
			fprintf(stderr,"cetr_mem_to_cpu_daemon: mem-data = %lx.\n", *data64);
			#endif
		}
		return(ret_val);
	}


	void cetr_device_to_serial_daemon()
	{
		while(1)
		{
			uint8_t buf[5];
			uint32_t device_rsp = read_uint32("DEVICE_TO_SERIAL_RESPONSE");

			*((uint32_t*) &(buf[0])) = device_rsp;

			buf[4] = 1;
			write_uint8_n("noblock_device_to_serial", buf, 5);
		}
	}

	uint8_t cetr_device_to_serial_probe(uint32_t* device_rsp)
	{
		uint8_t ret_val = 0;

		uint8_t buf[5];
		read_uint8_n("noblock_device_to_serial", buf, 5);
	
		if(buf[4] == 1)
		{
			*device_rsp = *((uint32_t*) &(buf[0]));
			ret_val = 1;

			#ifndef USE_RIFFA
			fprintf(stderr,"cetr_device_to_serial_daemon: device_rsp = %x.\n", *device_rsp);
			#endif
		}
		return(ret_val);
	}


	void cetr_device_to_interrupt_daemon()
	{
		while(1)
		{
			uint8_t buf[5];
			uint32_t device_rsp = read_uint32("DEVICE_TO_INTERRUPT_RESPONSE");

			*((uint32_t*) &(buf[0])) = device_rsp;

			buf[4] = 1;
			write_uint8_n("noblock_device_to_interrupt", buf, 5);
		}
	}

	uint8_t cetr_device_to_interrupt_probe(uint32_t* device_rsp)
	{
		uint8_t ret_val = 0;

		uint8_t buf[5];
		read_uint8_n("noblock_device_to_interrupt", buf, 5);
	
		if(buf[4] == 1)
		{
			*device_rsp = *((uint32_t*) &(buf[0]));
			ret_val = 1;

			#ifndef USE_RIFFA
			fprintf(stderr,"cetr_device_to_interrupt_daemon: device_rsp = %x.\n", *device_rsp);
			#endif
		}
		return(ret_val);
	}


	void cetr_device_to_timer_daemon()
	{
		while(1)
		{
			uint8_t buf[5];
			uint32_t device_rsp = read_uint32("DEVICE_TO_TIMER_RESPONSE");

			*((uint32_t*) &(buf[0])) = device_rsp;

			buf[4] = 1;
			write_uint8_n("noblock_device_to_timer", buf, 5);
		}
	}

	uint8_t cetr_device_to_timer_probe(uint32_t* device_rsp)
	{
		uint8_t ret_val = 0;

		uint8_t buf[5];
		read_uint8_n("noblock_device_to_timer", buf, 5);
	
		if(buf[4] == 1)
		{
			*device_rsp = *((uint32_t*) &(buf[0]));
			ret_val = 1;

			#ifndef USE_RIFFA
			fprintf(stderr,"cetr_device_to_timer_daemon: device_rsp = %x.\n", *device_rsp);
			#endif
		}
		return(ret_val);
	}
#endif


uint8_t cetr_irl_to_cpu_probe()
{
	uint8_t irl = read_uint8("ENV_to_AJIT_irl");
	return(irl);
}

uint8_t cetr_reset_to_cpu_probe()
{
	uint8_t rst = read_uint8("ENV_to_AJIT_reset");
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
#ifndef proto_board
	uint64_t icache_data  = 0;
	uint32_t mmu_fsr = 0;
	uint8_t  icache_mae   = 0;
	uint8_t  icache_valid = 0;

	uint64_t dcache_data  = 0;
	uint8_t  dcache_mae   = 0;
	uint8_t  dcache_valid = 0;
#endif

	uint8_t  reset = 0;
	uint8_t  irl = 0;

	uint32_t dbg_command  = 0;
	uint8_t  dbg_valid    = 0;

#ifdef proto_board
	uint32_t mem_initialize_addr       = 0;
	uint64_t mem_initialize_instr_pair = 0;
	uint8_t  mem_initialize_valid      = 0;
	uint8_t  serial_rsp_valid          = 0;
	uint32_t serial_rsp                = 0;
	uint8_t  interrupt_rsp_valid       = 0;
	uint32_t interrupt_rsp             = 0;
	uint8_t  timer_rsp_valid           = 0;
	uint32_t timer_rsp                 = 0;
#endif

#ifndef proto_board
	icache_valid = cetr_icache_to_cpu_probe(&icache_data, &icache_mae, &mmu_fsr);
	dcache_valid = cetr_dcache_to_cpu_probe(&dcache_data, &dcache_mae);
#endif

	dbg_valid    = cetr_debug_to_cpu_probe(&dbg_command);
	reset	     = cetr_reset_to_cpu_probe();
	irl	     = cetr_irl_to_cpu_probe();

#ifdef proto_board
	mem_initialize_valid = cetr_mem_to_cpu_probe(&mem_initialize_instr_pair, &mem_initialize_addr);
	serial_rsp_valid     = cetr_device_to_serial_probe(&serial_rsp);
	interrupt_rsp_valid  = cetr_device_to_interrupt_probe(&interrupt_rsp);
	timer_rsp_valid      = cetr_device_to_timer_probe(&timer_rsp);
#endif

	uint64_t header = reset;
	header = (header << 8) | ((uint64_t) irl);
	header = (header << 8) | ((uint64_t) dbg_valid);

#ifndef proto_board
	header = (header << 8) | ((uint64_t) dcache_valid);
	header = (header << 8) | ((uint64_t) dcache_mae);
	header = (header << 8) | ((uint64_t) icache_valid);
	header = (header << 8) | ((uint64_t) icache_mae);
#endif

#ifdef proto_board
	header = (header << 8) | ((uint64_t) serial_rsp_valid);
	header = (header << 8) | ((uint64_t) interrupt_rsp_valid);
	header = (header << 8) | ((uint64_t) timer_rsp_valid);
	header = (header << 8) | ((uint64_t) mem_initialize_valid);
#endif

	header = (header << 8) | ((uint64_t) counter);

#ifndef proto_board	
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
#endif

#ifdef proto_board
	uint64_t txbuf[6];
	txbuf[3] = 0; txbuf[4] = 0; txbuf[5] = 0;
	txbuf[0] = header;

	uint64_t dbg_initialize_addr = 0;
	dbg_initialize_addr = dbg_command;
	dbg_initialize_addr = (dbg_initialize_addr << 32);
	dbg_initialize_addr = dbg_initialize_addr | mem_initialize_addr;
	txbuf[1] = dbg_initialize_addr;

	txbuf[2] = mem_initialize_instr_pair;
	txbuf[3] = serial_rsp;	
	txbuf[4] = interrupt_rsp;	
	txbuf[5] = timer_rsp;				
					
	#ifndef USE_RIFFA
	fprintf(stderr,"cetr_from_tb: reset=%x.\n", reset);
	#endif

	cetr_send_u64_to_cpu(txbuf, 6);
#endif
}

//#ifndef proto_board:
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
//
//#ifdef proto_board:
// receive info
// header     counter logger-valid debug-valid cpu-mode-valid  serial_request_type  serial_valid  interrupt_request_type  interrupt_valid
// 	       8         8            8           8              	8		 8	    	    8		         8
// debug_etc      ignored 	timer_request_type    timer_valid   debug-response
//                   16                 8		  8	         32
// logger etc     processor_mode      value
//                  32       		32
// serial_addr_data   serial_addr  serial_data 
//			 32		32
// interrupt_addr_data   interrupt_addr  interrupt_data 
//			 	32		32
// timer_addr_data   timer_addr  timer_data 
//			 32	    32

#ifndef proto_board
void cetr_analyse_and_send_to_testbench(uint64_t header, uint64_t i_d_addr, uint64_t dcache_data, uint64_t debug_etc, uint64_t logger_etc)
{
#endif

#ifdef proto_board
void cetr_analyse_and_send_to_testbench(uint64_t header, uint64_t debug_etc, uint64_t logger_etc, uint64_t serial_addr_data, uint64_t interrupt_addr_data, uint64_t timer_addr_data)
{
#endif

	uint8_t counter = (header >> 56) & 0xff;
	#ifndef USE_RIFFA
	fprintf(stderr,"cetr_analyse_and_send_to_testbench: counter=%d.\n", counter);
	#endif	

	uint8_t  logger_valid = (header >> 48) & 0xff;
#ifndef proto_board
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
#endif

#ifdef proto_board
	uint8_t  debug_valid  = (header >> 40) & 0xff;
	uint8_t  processor_mode_valid = (header >> 32) & 0xff;
	uint8_t  serial_request_type = (header >> 24) & 0xff;
	uint8_t  serial_valid = (header >> 16) & 0xff;

	uint8_t  interrupt_request_type = (header >> 8) & 0xff;
	uint8_t  interrupt_valid = (header >> 0) & 0xff;

	uint8_t  timer_request_type = (debug_etc >> 40) & 0xff;
	uint8_t  timer_valid = (debug_etc >> 32) & 0xff;

	uint32_t serial_addr = (serial_addr_data >> 32) & 0xffffffff;
	uint32_t serial_data = (serial_addr_data) & 0xffffffff;

	uint32_t interrupt_addr = (interrupt_addr_data >> 32) & 0xffffffff;
	uint32_t interrupt_data = (interrupt_addr_data) & 0xffffffff;

	uint32_t timer_addr = (timer_addr_data >> 32) & 0xffffffff;
	uint32_t timer_data = (timer_addr_data) & 0xffffffff;
#endif

	uint32_t debug_response = debug_etc & 0xffffffff;
	uint32_t logger_response = logger_etc & 0xffffffff;
	uint8_t processor_mode = (logger_etc >> 32) & 0xff;


	if(logger_valid)
	{
		write_uint32("AJIT_to_ENV_logger", logger_response);
		//fprintf(stderr,"cetr_analyse_and_send_to_testbench: AJIT_to_ENV_logger=%x\n", logger_response);
	}

#ifndef proto_board
	if(icache_valid)
	{
		
		write_uint32("CPU_to_ICACHE_addr", icache_addr);
		write_uint8("CPU_to_ICACHE_asi", icache_asi);
		#ifndef USE_RIFFA
		fprintf(stderr,"cetr_listen_to_cpu_daemon: cpu-to-icache addr = %x, asi = %x.\n", icache_addr, icache_asi);
		#endif
		
		//print info after every IFETCH_PERIOD requests
		num_ifetch_requests++;
		if(num_ifetch_requests%IFETCH_PERIOD==0)
		{
			fprintf(stderr,"\n---------------------------------------------");
			fprintf(stderr,"\n num_ifetch_requests = %lu",num_ifetch_requests);
			fprintf(stderr,"\n num_dcache_requests = %lu",num_dcache_requests);
			fprintf(stderr,"\n---------------------------------------------");
			fprintf(stderr,"\n");
		}

	}
	if(dcache_valid)
	{
		write_uint32("CPU_to_DCACHE_addr", dcache_addr);
		write_uint64("CPU_to_DCACHE_data", dcache_data);
		write_uint8("CPU_to_DCACHE_asi", dcache_asi);
		write_uint8("CPU_to_DCACHE_byte_mask", dcache_byte_mask);
		write_uint8("CPU_to_DCACHE_request_type", dcache_request_type);
		
		//increment dcache request count
		num_dcache_requests++;


		#ifndef USE_RIFFA
		fprintf(stderr,"cetr_listen_to_cpu_daemon: cpu-to-dcache addr = %x, data = %lx,  asi = %x, byte-mask = %x, req-type = %d. \n", dcache_addr, dcache_data, dcache_asi, dcache_byte_mask, dcache_request_type);
		#endif
	}
#endif

#ifdef proto_board
	if(serial_valid)
	{
		write_uint8("SERIAL_TO_DEVICE_REQUEST_TYPE", serial_request_type);
		write_uint32("SERIAL_TO_DEVICE_ADDR", serial_addr);
		write_uint32("SERIAL_TO_DEVICE_DATA", serial_data);
	}

	if(interrupt_valid)
	{
		write_uint8("INTERRUPT_TO_DEVICE_REQUEST_TYPE", interrupt_request_type);
		write_uint32("INTERRUPT_TO_DEVICE_ADDR", interrupt_addr);
		write_uint32("INTERRUPT_TO_DEVICE_DATA", interrupt_data);
	}

	if(timer_valid)
	{
		write_uint8("TIMER_TO_DEVICE_REQUEST_TYPE", timer_request_type);
		write_uint32("TIMER_TO_DEVICE_ADDR", timer_addr);
		write_uint32("TIMER_TO_DEVICE_DATA", timer_data);
	}
#endif

	if(processor_mode_valid)
	{
		// processor_mode:
		//   irl trap-bit unused pmode
		//   7:4  3        2     1:0
		//
		write_uint8("AJIT_to_ENV_processor_mode", processor_mode);
	}

	#ifndef USE_RIFFA
	fprintf(stderr,"cetr_listen_to_cpu_daemon: processor_mode = %d.\n", processor_mode);
	#endif

	if(debug_valid)
	{
		write_uint32("AJIT_to_ENV_debug_response", debug_response);
		//fprintf(stderr,"cetr_listen_to_cpu_daemon: debug_response = %x.\n", debug_response);
	}
}


#ifndef proto_board
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
#endif

#ifdef proto_board
void cetr_probe_and_send_to_testbench()
{
	uint64_t rxbuf[6];
	cetr_get_u64_from_cpu(rxbuf, 6);

	uint64_t header = rxbuf[0];
	uint64_t debug_etc = rxbuf[1];
	uint64_t logger_etc = rxbuf[2];
	uint64_t serial_addr_data = rxbuf[3];
	uint64_t interrupt_addr_data = rxbuf[4];
	uint64_t timer_addr_data = rxbuf[5];

	cetr_analyse_and_send_to_testbench(header, debug_etc, logger_etc, serial_addr_data, interrupt_addr_data, timer_addr_data);
}
#endif

void cetr_interface_daemon()
{
	uint16_t counter = 0;
	while(1)
	{
		cetr_probe_and_send_to_cpu(counter);
		cetr_probe_and_send_to_testbench();
		counter++;
	}
}

#ifndef proto_board
DEFINE_THREAD(cetr_icache_to_cpu_daemon);
DEFINE_THREAD(cetr_dcache_to_cpu_daemon);
PTHREAD_DECL(cetr_icache_to_cpu_daemon);
PTHREAD_DECL(cetr_dcache_to_cpu_daemon);
#endif
#ifdef proto_board
DEFINE_THREAD(cetr_mem_to_cpu_daemon);
PTHREAD_DECL(cetr_mem_to_cpu_daemon);
DEFINE_THREAD(cetr_device_to_serial_daemon);
PTHREAD_DECL(cetr_device_to_serial_daemon);

DEFINE_THREAD(cetr_device_to_interrupt_daemon);
PTHREAD_DECL(cetr_device_to_interrupt_daemon);
DEFINE_THREAD(cetr_device_to_timer_daemon);
PTHREAD_DECL(cetr_device_to_timer_daemon);
#endif

DEFINE_THREAD(cetr_debug_to_cpu_daemon);
DEFINE_THREAD(cetr_interface_daemon);
PTHREAD_DECL(cetr_debug_to_cpu_daemon);
PTHREAD_DECL(cetr_interface_daemon);


void cetr_start_daemons()
{
	int depth = 2;
#ifdef USE_RIFFA
	MUTEX_LOCK(fpga_mutex);
	fpga = fpga_open(0);
	if(fpga == NULL)	
	{
		fprintf(stderr,"Error: could not open FPGA.\n");
		return;
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

#ifndef proto_board
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

	// nonblocking pipes used internally..
	register_pipe("noblock_icache_to_cpu", 14, 8, 2); //noblock-pipe
	register_pipe("noblock_dcache_to_cpu", 10, 8, 2); //noblock-pipe
#endif

	register_pipe ("AJIT_to_ENV_debug_response", depth, 32, 0);
	set_pipe_is_written_into ("AJIT_to_ENV_debug_response");

	// note: changed processor mode to blocking mode. MPD
	int processor_mode_depth=1;
	register_pipe ("AJIT_to_ENV_processor_mode", processor_mode_depth, 8, 0);
	set_pipe_is_written_into ("AJIT_to_ENV_processor_mode");

	register_pipe("noblock_debug_to_cpu", 5, 8, 2); //noblock-pipe

#ifdef proto_board
	register_pipe ("ENV_to_mem_initialize_instr_pair", depth, 64, 0);
	set_pipe_is_read_from ("ENV_to_mem_initialize_instr_pair");
	register_pipe ("ENV_to_mem_initialize_instr_pair_addr", depth, 32, 0);
	set_pipe_is_read_from ("ENV_to_mem_initialize_instr_pair_addr");

	register_pipe ("SERIAL_TO_DEVICE_REQUEST_TYPE", depth, 8, 0);
	set_pipe_is_written_into ("SERIAL_TO_DEVICE_REQUEST_TYPE");
	register_pipe ("SERIAL_TO_DEVICE_ADDR", depth, 32, 0);
	set_pipe_is_written_into ("SERIAL_TO_DEVICE_ADDR");
	register_pipe ("SERIAL_TO_DEVICE_DATA", depth, 32, 0);
	set_pipe_is_written_into ("SERIAL_TO_DEVICE_DATA");

	register_pipe  ("DEVICE_TO_SERIAL_RESPONSE", depth, 32, 0);
	set_pipe_is_read_from ("DEVICE_TO_SERIAL_RESPONSE");

	register_pipe ("INTERRUPT_TO_DEVICE_REQUEST_TYPE", depth, 8, 0);
	set_pipe_is_written_into ("INTERRUPT_TO_DEVICE_REQUEST_TYPE");
	register_pipe ("INTERRUPT_TO_DEVICE_ADDR", depth, 32, 0);
	set_pipe_is_written_into ("INTERRUPT_TO_DEVICE_ADDR");
	register_pipe ("INTERRUPT_TO_DEVICE_DATA", depth, 32, 0);
	set_pipe_is_written_into ("INTERRUPT_TO_DEVICE_DATA");

	register_pipe  ("DEVICE_TO_INTERRUPT_RESPONSE", depth, 32, 0);
	set_pipe_is_read_from ("DEVICE_TO_INTERRUPT_RESPONSE");

	register_pipe ("TIMER_TO_DEVICE_REQUEST_TYPE", depth, 8, 0);
	set_pipe_is_written_into ("TIMER_TO_DEVICE_REQUEST_TYPE");
	register_pipe ("TIMER_TO_DEVICE_ADDR", depth, 32, 0);
	set_pipe_is_written_into ("TIMER_TO_DEVICE_ADDR");
	register_pipe ("TIMER_TO_DEVICE_DATA", depth, 32, 0);
	set_pipe_is_written_into ("TIMER_TO_DEVICE_DATA");

	register_pipe  ("DEVICE_TO_TIMER_RESPONSE", depth, 32, 0);
	set_pipe_is_read_from ("DEVICE_TO_TIMER_RESPONSE");

	register_pipe("noblock_mem_to_cpu", 13, 8, 2); //noblock-pipe
	register_pipe("noblock_device_to_serial", 5, 8, 2); //noblock-pipe
	register_pipe("noblock_device_to_interrupt", 5, 8, 2); //noblock-pipe
	register_pipe("noblock_device_to_timer", 5, 8, 2); //noblock-pipe

	PTHREAD_CREATE(cetr_mem_to_cpu_daemon);
	PTHREAD_CREATE(cetr_device_to_serial_daemon)
	PTHREAD_CREATE(cetr_device_to_interrupt_daemon)
	PTHREAD_CREATE(cetr_device_to_timer_daemon)
#endif

#ifndef proto_board
	PTHREAD_CREATE(cetr_icache_to_cpu_daemon);
	PTHREAD_CREATE(cetr_dcache_to_cpu_daemon);
#endif
	PTHREAD_CREATE(cetr_debug_to_cpu_daemon);
	PTHREAD_CREATE(cetr_interface_daemon);

}

void cetr_stop_daemons()
{
#ifndef proto_board
	PTHREAD_CANCEL(cetr_icache_to_cpu_daemon);
	PTHREAD_CANCEL(cetr_dcache_to_cpu_daemon);
#endif
#ifdef proto_board
	PTHREAD_CANCEL(cetr_mem_to_cpu_daemon);
	PTHREAD_CANCEL(cetr_device_to_serial_daemon);
	PTHREAD_CANCEL(cetr_device_to_interrupt_daemon);
	PTHREAD_CANCEL(cetr_device_to_timer_daemon);
#endif
	PTHREAD_CANCEL(cetr_debug_to_cpu_daemon);
	PTHREAD_CANCEL(cetr_interface_daemon);

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
