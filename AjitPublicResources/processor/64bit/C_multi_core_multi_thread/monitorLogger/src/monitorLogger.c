#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "SocketLib.h"
#include "SockPipes.h"
#include "monitorLogger.h"

int in_socket_mode = 0;

uint32_t ml_read_uint32(char* pname)
{
	uint32_t ret_val = 0;
	if(in_socket_mode) 
		ret_val = sock_read_uint32(pname);
	else
		ret_val = read_uint32(pname);

	return(ret_val);
}



// utility function.
uint8_t __signature_8 (uint32_t raw_val)
{
	uint8_t ret_val = 0;
	ret_val = ((raw_val >> 24) & 0xff) ^ ((raw_val >> 16) & 0xff) ^ ((raw_val >> 8) & 0xff) ^ (raw_val & 0xff);
	return(ret_val);
}

MonitorLoggerState* makeMonitorLoggerState (uint32_t core_id, uint32_t thread_id,
						char *reg_write_file, char *long_reg_write_file,
						char* server_ip_addr, int server_port_number,
							int global_verbose_flag)
{

	MonitorLoggerState* mls = (MonitorLoggerState*) malloc (sizeof (MonitorLoggerState));

	mls->reg_write_file = NULL;
	mls->long_reg_write_file = NULL;

	mls->core_id = core_id;
	mls->thread_id = thread_id;

	sprintf(mls->logger_pipe_name,"AJIT_to_ENV_logger_%d_%d", core_id, thread_id);

	char file_name [4096];

	if(reg_write_file != NULL)
	{
		sprintf(file_name,"%s.%d_%d", reg_write_file, core_id, thread_id);
		mls->reg_write_file = fopen(file_name,"w");
		assert(mls->reg_write_file);
		fprintf(mls->reg_write_file,"//============== C model register-write trace (core,thread=%d,%d) ============\n",
				core_id, thread_id);
		fprintf(mls->reg_write_file,"//=========================================================================\n");
	}

	if(global_verbose_flag && (long_reg_write_file != NULL))
	{
		sprintf(file_name,"%s.%d_%d", long_reg_write_file, core_id, thread_id);
		mls->long_reg_write_file = fopen(file_name,"w");
		assert(mls->long_reg_write_file);
	}

	if(server_ip_addr != NULL)
		mls->logger_server_ip_address  = strdup (server_ip_addr);
	else
		mls->logger_server_ip_address  = NULL;

	if(server_port_number > 0)
		mls->logger_server_port_number = server_port_number;
	else
		mls->logger_server_port_number = 0;

	mls->global_verbose_flag = global_verbose_flag;
}

//
// bits are as follows
//  31  	flag to indicate that psr-has-been-updated.
//  30  	S
//  29  	PS
//  28  	ET 
//  27:24	PIL
//  23:20	CWP (4-bits)
//  19          wim-updated
//  18		tbr-updated
//  17		y-updated
//  16          GPR-updated
//  15		0
//  14		0
//  13		double-word GPR update
//  12:8        write-register-id
//  7:0         register signature  calculated as xor of
//		  all written bytes from GPR, WIM, TBR, Y
uint32_t assembleRegisterWriteSignature( uint8_t psr_updated, uint32_t psr_value,
		uint8_t wim_updated, uint32_t wim_value,
		uint8_t tbr_updated, uint32_t tbr_value,
		uint8_t y_updated, uint32_t y_value,
		uint8_t gpr_updated, uint8_t double_word_write,
		uint8_t reg_id, uint32_t reg_val_high, uint32_t reg_val_low)
{
	uint32_t ret_val = 0;

	// if nothing modified, then send 0.
	if(!(psr_updated | wim_updated | tbr_updated | y_updated | gpr_updated))
		return(ret_val);

	// PSR fields.
	uint8_t S = (psr_value >> 7) & 0x1;
	uint8_t PS = (psr_value >> 6) & 0x1;
	uint8_t ET = (psr_value >> 5) & 0x1;
	uint8_t CWP = (psr_value & 0x1f);
	uint8_t PIL = ((psr_value >> 8) & 0xf);
	uint8_t ICC = ((psr_value >> 20) & 0xf);

	// pack.
	ret_val = (ret_val | (psr_updated << 31)); // psr-updated flag.
	ret_val = (ret_val | (S << 30));
	ret_val = (ret_val | (PS << 29));
	ret_val = (ret_val | (ET << 28));
	ret_val = (ret_val | (PIL << 24));
	ret_val = (ret_val | (CWP << 20));
	ret_val = (ret_val | (wim_updated << 19));
	ret_val = (ret_val | (tbr_updated << 18));
	ret_val = (ret_val | (y_updated << 17));
	ret_val = (ret_val | (gpr_updated << 16));

	uint8_t data_signature = 0;
	if(gpr_updated)
	{
		ret_val = (ret_val | (double_word_write << 13));
		ret_val = (ret_val | (reg_id << 8));
		if(double_word_write)
		{
			data_signature = (__signature_8(reg_val_high) ^ __signature_8(reg_val_low));
		}
		else
		{
			data_signature = __signature_8(reg_val_low);
		}
	}

	if(wim_updated)
		data_signature = data_signature ^ __signature_8(wim_value);
	if(tbr_updated)
		data_signature = data_signature ^ __signature_8(tbr_value);
	if(y_updated)
		data_signature = data_signature ^ __signature_8(y_value);

	ret_val = (ret_val | data_signature);
	return(ret_val);

}

void splitRegisterWriteSignature(uint32_t reg_write_signature,
		uint8_t* psr_updated,
		uint8_t* S,
		uint8_t* PS,
		uint8_t* ET,
		uint8_t* PIL,
		uint8_t* CWP,
		uint8_t* wim_write,
		uint8_t* tbr_write,
		uint8_t* y_write,
		uint8_t* gpr_write,
		uint8_t* double_word_write,
		uint8_t* reg_id,
		uint8_t* reg_val_signature)
{
	*psr_updated = (reg_write_signature >> 31);
	*S = ((reg_write_signature >> 30) & 0x1);
	*PS = ((reg_write_signature >> 29) & 0x1);
	*ET = ((reg_write_signature >> 28) & 0x1);
	*PIL = ((reg_write_signature >> 24) & 0xf);
	*CWP = ((reg_write_signature >> 20) & 0xf);
	*wim_write = ((reg_write_signature >> 19) & 0x1);
	*tbr_write = ((reg_write_signature >> 18) & 0x1);
	*y_write = ((reg_write_signature >> 17) & 0x1);
	*gpr_write = ((reg_write_signature >> 16) & 0x1);
	*double_word_write = ((reg_write_signature >> 13) & 0x1);
	*reg_id = ((reg_write_signature >> 8) & 0x1f);
	*reg_val_signature = reg_write_signature & 0xff;
}

// returns 32-bit fp register write signature
//   31 write-fpreg-from-fp
//   30 write-fpreg-from-ccu
//   29 write-fsr-from-fp
//   28 write-fsr-from-ccu
//   27 write-fsr
//   26 write-ftt
//   25 write-fcc
//   24 write-h-gpr
//   23:21
//       unused
//   20:16
//       write-reg-id
//   15:8
//       written-fsr-signature
//   7:0 
//       written-gpr-signature
//
uint32_t assembleFpRegisterWriteSignature( uint8_t write_fpreg_from_fpunit, 
						uint8_t write_fpreg_from_ccu,
						uint8_t write_fsr_from_fpunit,
						uint8_t write_fsr_from_ccu,
						uint8_t write_full_fsr,
						uint8_t write_ftt,
						uint8_t write_fcc,
						uint8_t write_double,
						uint8_t write_reg_id,
						uint32_t fsr_val,
						uint32_t reg_val_h,
						uint32_t reg_val_l)
{
	uint32_t ret_val = 0;
	// bottom nibble contains fcc, top nibble ftt.
	uint8_t fsr_signature =  ((fsr_val >> 10) & 0x3) | ((fsr_val >> 10) & 0xf0);
	uint8_t fpreg_signature = (write_double ?  __signature_8(reg_val_h) : 0) ^ __signature_8(reg_val_l);
	ret_val |=  (write_fpreg_from_fpunit << 31); 
	ret_val |=  (write_fpreg_from_ccu << 30);
	ret_val |=  (write_fsr_from_fpunit << 29);
	ret_val |=  (write_fsr_from_ccu << 28);
	ret_val |=  (write_full_fsr << 27);
	ret_val |=  (write_ftt << 26);
	ret_val |=  (write_fcc << 25);
	ret_val |=  (write_double << 24);
	ret_val |=  (write_reg_id << 16);
	ret_val |=  (fsr_signature << 8);
	ret_val |=  fpreg_signature;


	return(ret_val);
}

// splits 32-bit fp-register write signature into specified values.
void splitFpRegisterWriteSignature(uint32_t reg_write_signature,
						uint8_t* write_fpreg_from_fpunit, 
						uint8_t* write_fpreg_from_ccu,
						uint8_t* write_fsr_from_fpunit,
						uint8_t* write_fsr_from_ccu,
						uint8_t* write_full_fsr,
						uint8_t* write_ftt,
						uint8_t* write_fcc,
						uint8_t* write_double,
						uint8_t* write_reg_id,
						uint32_t* fsr_signature,
						uint32_t* fp_reg_signature)
{
	*write_fpreg_from_fpunit = (reg_write_signature >> 31) & 0x1;
	*write_fpreg_from_ccu = ((reg_write_signature >> 30) & 0x1);
	*write_fsr_from_fpunit = ((reg_write_signature >> 29) & 0x1);
	*write_fsr_from_ccu = ((reg_write_signature >> 28) & 0x1);
	*write_full_fsr = ((reg_write_signature >> 27) & 0xf);
	*write_ftt = ((reg_write_signature >> 26) & 0xf);
	*write_fcc = ((reg_write_signature >> 25) & 0x1);
	*write_double = ((reg_write_signature >> 24) & 0x1);
	*write_reg_id = ((reg_write_signature >> 16) & 0x1f);
	*fsr_signature = (reg_write_signature >> 8) & 0xff;
	*fp_reg_signature = reg_write_signature & 0xff;
}



// returns 32-bit signature for store, based on supplied info.
//  bits are as follows
//  31		store-is-completed
//  30		double-word-store
//  29:24	asi (6 bits used).
//  23:16	byte-mask
//  15:8	address-signature
//		  xor of all bytes in address.
//  7:0		data-signature
//                xor of all bytes written.
uint32_t assembleStoreSignature( uint8_t store_active,
		uint8_t  asi,
		uint8_t  byte_mask,
		uint8_t  double_word_write,
		uint32_t addr,
		uint32_t word_high,
		uint32_t word_low)
{
	uint32_t ret_val = 0;
	if(store_active)
	{
		ret_val = (ret_val | (store_active  << 31));
		ret_val = (ret_val | (double_word_write << 30));
		ret_val = (ret_val | (asi << 24));
		ret_val = (ret_val | (byte_mask << 16));
		ret_val = (ret_val | (__signature_8(addr) << 8));
		if(double_word_write)
			ret_val = (ret_val | (__signature_8(word_high) ^ __signature_8(word_low)));
		else
			ret_val = (ret_val |  __signature_8(word_low));
	}
	return(ret_val);
}

void splitStoreSignature(uint32_t store_signature,
		uint8_t* store_active,
		uint8_t* double_word,
		uint8_t* asi,
		uint8_t* byte_mask,
		uint8_t* addr_signature,
		uint8_t* data_signature)
{
	*store_active = (store_signature >> 31);
	*double_word  = ((store_signature >> 30) & 0x1);
	*asi  = ((store_signature >> 24) & 0x3f);
	*byte_mask  = ((store_signature >> 16) & 0x3f);
	*addr_signature = ((store_signature >> 8) & 0xff);
	*data_signature = (store_signature & 0xff);
}

void monitorLogger_core(MonitorLoggerState* mls)
{
	uint32_t counter = 0;
	while(1)
	{

		//
		// bits are as follows
		//  31  	flag to indicate that psr-has-been-updated.
		//  30  	S
		//  29  	PS
		//  28  	ET 
		//  27:24	PIL
		//  23:20	CWP (4-bits)
		//  19          wim-updated
		//  18		tbr-updated
		//  17		y-updated
		//  16          GPR-updated
		//  15		0
		//  14		0
		//  13		double-word GPR update
		//  12:8        write-register-id
		//  7:0         register signature  calculated as xor of
		//		  all written bytes from GPR, WIM, TBR, Y
		uint32_t reg_write_log = ml_read_uint32(mls->logger_pipe_name);


		// bits are as follows
		//   31 write-fpreg-from-fp
		//   30 write-fpreg-from-ccu
		//   29 write-fsr-from-fp
		//   28 write-fsr-from-ccu
		//   27 write-fsr
		//   26 write-ftt
		//   25 write-fcc
		//   24 write-h-gpr
		//   23:21
		//       unused
		//   20:16
		//       write-reg-id
		//   15:8
		//       written-fsr-signature
		//   7:0 
		//       written-gpr-signature
		//
		uint32_t fp_reg_write_log = ml_read_uint32(mls->logger_pipe_name);



		//  bits are as follows
		//  31		store-is-completed
		//  30		double-word-store
		//  29:24	asi (6 bits used).
		//  23:16	byte-mask
		//  15:8	address-signature
		//		  xor of all bytes in address.
		//  7:0		data-signature
		//                xor of all bytes written.
		uint32_t store_log = ml_read_uint32(mls->logger_pipe_name);

		// 32-bit PC
		uint32_t pc_log = ml_read_uint32(mls->logger_pipe_name);
		if(mls->reg_write_file)
		{

			int v_flag  = 0;
			fprintf(mls->reg_write_file,"%d. PC=%08x, Reg-Log=%08x Fp-Reg-log=%08x  Store-log= %08x\n", counter, 
					pc_log,
					reg_write_log,
					fp_reg_write_log,
					store_log);
			fflush(mls->reg_write_file);

			if(mls->global_verbose_flag)
			{
				fprintf(stderr,"%d. PC=%08x, Reg-Log=%08x Fp-Reg-log=%08x  Store-log= %08x\n", counter, 
						pc_log,
						reg_write_log,
						fp_reg_write_log,
						store_log);
			}

			if(mls->global_verbose_flag && (mls->long_reg_write_file!=NULL))
			{
				uint8_t psr_updated,
					S,
					PS,
					ET,
					PIL,
					CWP,
					wim_write,
					tbr_write,
					y_write,
					gpr_write,
					double_word_write,
					reg_id,
					reg_val_signature;
				splitRegisterWriteSignature(reg_write_log,
						&psr_updated,
						&S,
						&PS,
						&ET,
						&PIL,
						&CWP,
						&wim_write,
						&tbr_write,
						&y_write,
						&gpr_write,
						&double_word_write,
						&reg_id,
						&reg_val_signature);

				uint8_t store_active,
					double_word,
					asi,
					byte_mask,
					addr_signature,
					data_signature;
				splitStoreSignature(store_log,
						&store_active,
						&double_word,
						&asi,
						&byte_mask,
						&addr_signature,
						&data_signature);

				fprintf(mls->long_reg_write_file,
						" pc=%08x, wrPSR=%x, S=%x, PS=%x, ET=%x, PIL=%x, CWP=%x, wrWim=%x, wrTbr=%x, wrY=%x, wrGPR=%x, doubleRegWrite=%x, rid=%x, reg-signature=0x%x, storeActive=%x, doubleStore=%x, asi=%x, byteMask=%x, addr_signature=%08x, data_signature=%08x\n",
						pc_log, 
						psr_updated,
						S,
						PS,
						ET,
						PIL,
						CWP,
						wim_write,
						tbr_write,
						y_write,
						gpr_write,
						double_word_write,
						reg_id,
						reg_val_signature,
						store_active,
						double_word,
						asi,
						byte_mask,
						addr_signature,
						data_signature);
				fflush(mls->long_reg_write_file);
			}
		}
		if((mls->logger_server_ip_address != NULL) && (mls->logger_server_port_number > 0))
		{
			uint32_t sbuf[4];
			sbuf[0] = reg_write_log;
			sbuf[1] = fp_reg_write_log;
			sbuf[2] = store_log;
			sbuf[3] = pc_log;
			send_packet_and_wait_for_response((char*)& sbuf, 16, 
								mls->logger_server_ip_address, 
								mls->logger_server_port_number);
		}
		counter++;
	}
}

