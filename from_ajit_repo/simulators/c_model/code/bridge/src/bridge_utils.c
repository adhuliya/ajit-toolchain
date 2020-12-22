#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "Ajit_Hardware_Configuration.h"
#include "Ancillary.h"
#include "RequestTypeValues.h"
#include "Serial.h"
#include "Timer.h"
#include "InterruptController.h"
#include "bridge.h"
#include "memory.h"
#include "Sdhc.h"
extern int global_verbose_flag;

bridgeTargets bridge_targets;
void initBridgeTargets()
{
	bridge_targets.pd_list = NULL;
	bridge_targets.md_list = NULL;
}
				
void addMem(char* mem_name, uint8_t permissions, uint64_t minaddr, uint64_t maxaddr)
{
	if(minaddr <= maxaddr)
	{
		memDescriptorList* mdl = bridge_targets.md_list;
		while(mdl != NULL)
		{
			if(strcmp(mdl->mem_name, mem_name) == 0)
			{
				fprintf(stderr,"Error: duplicate memory %s\n", mem_name);
				return;
			}
			mdl = mdl->next;
		}
		mdl =  (memDescriptorList*) malloc (sizeof(memDescriptorList));
		snprintf(mdl->mem_name,255,"%s", mem_name);

		mdl->min_address = minaddr;
		mdl->max_address = maxaddr;
		mdl->rw_permissions = permissions;
		
		mdl->next = bridge_targets.md_list;
		bridge_targets.md_list = mdl;

		fprintf(stderr,"Info:addMem: added mem target %s perms=0x%x, address-range %" PRIx64 " to %" PRIx64 "\n", mem_name, permissions, minaddr, maxaddr);
	}
	else
	{
		fprintf(stderr,"Error:addMem: for %s min-address is > max-address\n", mem_name);
		return;
	}
}

void addPeripheral(char* periph_name, uint64_t min_addr, uint64_t max_addr)
{
	// min address should be <= max address.
	if(min_addr > max_addr)
	{
		fprintf(stderr,"Error:addPeripheral: for %s min-address is > max-address\n", periph_name);
		return;
	}

	// ensure that there are no duplicate peripherals.
	peripheralDescriptorList* pdl = bridge_targets.pd_list;
	while(pdl != NULL)
	{
		if(strcmp(pdl->peripheral_name, periph_name) == 0)
		{
			fprintf(stderr,"Error: duplicate peripheral %s\n", periph_name);
			return;
		}
		pdl = pdl->next;
	}


	pdl =  (peripheralDescriptorList*) malloc (sizeof(peripheralDescriptorList));
	snprintf(pdl->peripheral_name,255,"%s", periph_name);

	pdl->min_address = min_addr;
	pdl->max_address = max_addr;

	pdl->next = bridge_targets.pd_list;
	bridge_targets.pd_list = pdl;

	snprintf(pdl->request_pipe_name, 255, "peripheral_bridge_to_%s_request", periph_name);
	register_pipe(pdl->request_pipe_name, 1, 64, PIPE_FIFO_MODE);

	snprintf(pdl->response_pipe_name, 255, "%s_to_peripheral_bridge_response", periph_name);
	register_pipe(pdl->response_pipe_name, 1, 32, PIPE_FIFO_MODE);

	set_pipe_is_written_into(pdl->request_pipe_name);
	set_pipe_is_read_from(pdl->response_pipe_name);

	fprintf(stderr,"Info: bridge: added peripheral %s with address range 0x%" PRIx64 " -> 0x%" PRIx64 "\n",
			periph_name, min_addr, max_addr);

}

void setupBridgeTargetsAndPeripherals(char* file_name)
{
	FILE* fp = fopen (file_name,"r");
	if(fp == NULL)
	{
		fprintf(stderr,"Error: could not open bridge targets file %s\n", file_name);
		return;
	}

	while(!feof(fp))
	{
		char line_buffer[1024];
		char* fs = fgets(line_buffer,1023, fp);
		if(fs == NULL)
			break;

		if(line_buffer[0] != '!')
		{
			char mem_name[256];
			uint64_t mina, maxa;
			uint8_t perms;

			char* save_ptr = NULL;
			char*strtok_buffer = strtok_r(line_buffer," \t\n", &save_ptr);
			if(strcmp(strtok_buffer, "ram") == 0)
			//
			// ram format:  ram <ram-name> <min-addr> <max-addr> <permissions (rw)>
			//
			{
				strtok_buffer = strtok_r(strtok_buffer," \t\n", &save_ptr);
				assert(strtok_buffer != NULL);
				sprintf(mem_name,"%s", strtok_buffer);

				strtok_buffer = strtok_r(strtok_buffer," \t\n", &save_ptr);
				assert(strtok_buffer != NULL);
				mina = atoll(strtok_buffer);

				strtok_buffer = strtok_r(strtok_buffer," \t\n", &save_ptr);
				assert(strtok_buffer != NULL);
				maxa = atoll(strtok_buffer);

				strtok_buffer = strtok_r(strtok_buffer," \t\n", &save_ptr);
				assert(strtok_buffer != NULL);
				perms = atoi(strtok_buffer);

				addMem(mem_name, perms, mina, maxa);
			}
			//
			// peripheral format:  peripheral <periph-name> <min-addr> <max-addr> 
			//
			else if(strcmp(strtok_buffer,"peripheral") == 0)
			{
				strtok_buffer = strtok_r(strtok_buffer," \t\n", &save_ptr);
				assert(strtok_buffer != NULL);
				char* pname = strtok_buffer;

				strtok_buffer = strtok_r(strtok_buffer," \t\n", &save_ptr);
				assert(strtok_buffer != NULL);
				mina = atoll(strtok_buffer);

				strtok_buffer = strtok_r(strtok_buffer," \t\n", &save_ptr);
				assert(strtok_buffer != NULL);
				maxa = atoll(strtok_buffer);

				addPeripheral(pname, mina, maxa);
			}
			else
			{
				fprintf(stderr,"Error: unknown target type %s in bridgeTarget file\n", strtok_buffer);
				return;
			}
		}
	}
}

// return pointer to peripheral descriptor.
memDescriptorList* lookupMem(uint64_t addr)
{
	
	memDescriptorList* ret_val = NULL;
	memDescriptorList* mdl;		
	for(mdl = bridge_targets.md_list; mdl != NULL; mdl = mdl->next)
	{
		if((mdl->min_address <= addr) && (mdl->max_address >= addr))
		{
			ret_val = mdl;
			break;
		}
	}

	return(ret_val);
}

// return pointer to peripheral descriptor.
peripheralDescriptorList* lookupPeripheral(uint64_t addr)
{
	
	peripheralDescriptorList* ret_val = NULL;
	peripheralDescriptorList* pdl;		
	for(pdl = bridge_targets.pd_list; pdl != NULL; pdl = pdl->next)
	{
		if((pdl->min_address <= addr) && (pdl->max_address >= addr))
		{
			ret_val = pdl;
			break;
		}
	}		

	return(ret_val);
}

uint64_t executeMemAccess(memDescriptorList* mdl,
		uint8_t read_write_bar, 
		uint64_t addr, 
		uint8_t byte_mask, 
		uint64_t write_data)
{
	uint64_t ret_val = 0;
	uint8_t rt = (read_write_bar << 1) | (~read_write_bar);
	if(mdl->rw_permissions & rt)
	{
		if(!read_write_bar)
			setDoubleWordInMemory(addr, write_data, byte_mask);

		// read back and send for write-back cache.
		ret_val = getDoubleWordInMemory(addr);
	}
	else
	{
		fprintf(stderr,"Error: in accessing mem %s insufficient permissions\n", mdl->mem_name);
	}
	return(ret_val);
}


// request command
uint32_t execPeripheralAccess32(peripheralDescriptorList* pdl,
		uint8_t read_write_bar, 
		uint32_t addr32, uint8_t byte_mask, uint32_t write_data)
{
#ifdef DEBUG
	fprintf(stderr,"Info: execPeripheralAccess32 request: periph=%s rwb=%d addr=0x%x, bytemask=0x%x, wdata=0x%x\n",
			pdl->peripheral_name, read_write_bar, addr32, byte_mask, write_data);
#endif

	// command format
	//  63     [62:59]    [55:32]	[31:0]
	//  rwbar  byte-mask  address   write_data;
	uint64_t cmd = read_write_bar;
	cmd = (cmd << 4) | (byte_mask & 0xf);
	cmd = (cmd << 27) | (0xffffff & addr32);
	cmd = (cmd << 32) | write_data;

	write_uint64 (pdl->request_pipe_name, cmd);
	uint32_t ret_val = read_uint32(pdl->response_pipe_name);
#ifdef DEBUG
	fprintf(stderr,"Info: execPeripheralAccess32 response: read_data=0x%x\n", ret_val);
#endif
	if(global_verbose_flag)
	{
		if(read_write_bar)
			fprintf(stderr,"Peripheral Mem Read:  0x%x =  %s[0x%x]\n",
						ret_val, pdl->peripheral_name, addr32);
		else
			fprintf(stderr,"Peripheral Mem Write:  %s[0x%x] = 0x%x (bmask=0x%x)\n",
						pdl->peripheral_name, addr32, write_data, byte_mask);
	}
	return(ret_val);
}



// Peripheral access is executed as two 32-bit accesses with byte mask.
uint64_t executePeripheralAccess(peripheralDescriptorList* pdl, 
		uint8_t read_write_bar, 
		uint64_t addr, 
		uint8_t byte_mask, 
		uint64_t write_data)
{
	uint64_t retval = 0;
	if((byte_mask & 0xf0) != 0)
	{
		// double word aligned.
		uint32_t addr32 = (addr & 0xfffffffc);
		uint8_t sbyte_mask = byte_mask >> 4;
		write_data = write_data >> 32;
		uint32_t rval = 
			execPeripheralAccess32(pdl, read_write_bar, addr32, sbyte_mask,write_data&0xffffffff);
		retval = rval;
		retval = (retval << 32);
	}
	if((byte_mask & 0xf) != 0)
	{
		// double word aligned.
		uint32_t addr32 = ((addr & 0xfffffffc) + 4);
		uint8_t sbyte_mask = byte_mask & 0xf;
		write_data = write_data & 0xffffffff;
		uint32_t rval = 
			execPeripheralAccess32(pdl, read_write_bar, addr32, sbyte_mask,write_data);

		retval = retval | rval;
	}
	return(retval);
}
