#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "SockPipes.h"
#include "pipeHandler.h"
#include "spi_slave_cluster.h"


uint8_t spi_slave_cluster_mode = SPI_SLAVE_CLUSTER_NORMAL_MODE;
void setSpiSlaveClusterMode(uint8_t cmode)
{
	spi_slave_cluster_mode = cmode;
}
void setSpiSlaveClusterInSocketMode()
{
	spi_slave_cluster_mode = spi_slave_cluster_mode | SPI_SLAVE_CLUSTER_SOCKET_MODE;
}

// 64 kB
uint8_t bootrom_memory [(1 << 16)];
void initBootrom()
{
	FILE* fp = NULL;
	fp = fopen ("BOOTROM.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr,"Warning: initBootrom: BOOTROM.txt not found, zero-ing bootrom\n");
		int I;
		for (I = 0; I < (1 << 16); I++)
		{
			bootrom_memory[I] = 0;
		}
	}
	else
	{
		fprintf(stderr,"Info: initBootrom: initializing from BOOTROM.txt\n");
		while (!feof(fp))
		{
			uint32_t addr, data;
			int n = fscanf(	fp, "%x %x", &addr, &data);
			if(n == 2)
			{
				bootrom_memory [(addr & 0xffff)] = data & 0xff;
			}
			else
				break;
		}
		fclose(fp);
	}
}


uint8_t SpiSlaveClusterBootrom (uint8_t deselect, uint8_t data)
{
	static int d_count = 0;
	static uint16_t addr = 0;
	uint8_t  ret_val = 0;

	switch(d_count)
	{
	   case 0:
		addr = data;
		d_count++;
		break;
	   case 1:
		addr = (addr << 8) | data;
		d_count++;
		break;
	   case 2:
		ret_val = bootrom_memory[addr];
		addr = addr + 1;
		if(deselect)
			d_count = 0;
		break;
	    default:
		break;
	}

	return(ret_val);
	
}

uint8_t SpiSlaveClusterGpio(uint8_t gpio_out_val)
{
	uint8_t rval;
	if(spi_slave_cluster_mode == SPI_SLAVE_CLUSTER_NORMAL_MODE)
	{
		write_uint8("AJIT_to_ENV_gpio_out", gpio_out_val);
		rval = read_uint8("ENV_to_AJIT_gpio_in");
	}
	else
	{
		sock_write_uint8("AJIT_to_ENV_gpio_out", gpio_out_val);
		rval = sock_read_uint8("ENV_to_AJIT_gpio_in");
	}

	return(rval);
}

void SpiSlaveClusterMasterDaemon ()
{
	uint8_t control_status_register = 0;

	uint8_t spi_data_buf_h = 0;
	uint8_t spi_data_buf_l = 0;

	uint8_t spi_shift_reg_h = 0;
	uint8_t spi_shift_reg_l = 0;



	while(1)
	{
		uint16_t command;
		uint8_t ret_val = 0;

		if(spi_slave_cluster_mode == SPI_SLAVE_CLUSTER_NORMAL_MODE)
			command = read_uint16("SPI_to_SPI_MASTER");
		else
			command = sock_read_uint16("SPI_to_SPI_MASTER");

		uint8_t rw = (command >> 10) & 0x1;
		uint8_t addr = (command >> 8) & 0x3;
		uint8_t data = (command & 0xff);	

		ret_val = 0;
		if(rw)
		{
			switch(addr){
				case 0: 
					ret_val = spi_shift_reg_l;
					break;
				case 1: 
					ret_val = spi_shift_reg_h;
					break;
				case 2: 
					// send back deselect bit..
					ret_val = (control_status_register & 0x2);
					break;
				default:
					break;
			}

		}
		else
		{
			switch(addr) {
				case 0:
					spi_data_buf_l = data;
					break;
				case 1:
					spi_data_buf_h = data;
					break;
				case 2:
					control_status_register = data;
					break;
				default:
					break;
			};

			if(control_status_register & 0x1) // start?
			{
				uint8_t slave_id = (control_status_register >> 4) & 0x3;
				uint8_t deselect = (control_status_register >> 1) & 0x1;
				uint8_t read_data = 0;
				if(slave_id == 0) {
					read_data = SpiSlaveClusterBootrom(deselect, spi_data_buf_l);
				}
				else if(slave_id == 1) {
					read_data = SpiSlaveClusterGpio (spi_data_buf_l);
				}

				spi_shift_reg_l = read_data;
			}
		}

		if(spi_slave_cluster_mode == SPI_SLAVE_CLUSTER_NORMAL_MODE)
			write_uint8("SPI_MASTER_to_SPI", ret_val);
		else
			sock_write_uint8("SPI_MASTER_to_SPI", ret_val);
	}
}

DEFINE_THREAD (SpiSlaveClusterMasterDaemon);
void startSpiSlaveClusterThreads()
{
	register_signal ("AJIT_to_ENV_gpio_out",8);
	register_signal ("ENV_to_AJIT_gpio_in",8);

	register_pipe ("SPI_MASTER_to_SPI", 8, 8,  PIPE_FIFO_MODE);
	register_pipe ("SPI_to_SPI_MASTER", 8, 16,  PIPE_FIFO_MODE);

	initBootrom();
	PTHREAD_DECL(SpiSlaveClusterMasterDaemon);
	PTHREAD_CREATE(SpiSlaveClusterMasterDaemon);
}



