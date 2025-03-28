#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define DBG_UTILS_MMAP_STRUCT_SIZE   16

typedef struct __DbgUtilsMmapDownloadStruct {
	uint32_t wdata[DBG_UTILS_MMAP_STRUCT_SIZE];
	uint32_t base_address;
	uint32_t number_of_writes;
} DbgUtilsMmapDownloadStruct;
	

DbgUtilsMmapDownloadStruct  mmap_download_struct;
void initMmapDownloadStruct()
{
	mmap_download_struct.number_of_writes = 0;
}

int insertWriteIntoMmapDownloadStructmmap(uint32_t addr, uint32_t data)
{
	int nw = 	mmap_download_struct.number_of_writes;

	if(nw == 0)
	{
		// update base address.
		mmap_download_struct.base_address = addr;
	}

	mmap_download_struct.wdata[nw] = data;
	mmap_download_struct.number_of_writes = nw + 1;

	return(mmap_download_struct.number_of_writes == DBG_UTILS_MMAP_STRUCT_SIZE);
}

int burst_counter = 0;
uint32_t exec_burst_mmap_download()
{
	burst_counter++;

	int I;

	fprintf (stdout, "---------------------------------  Start Burst %d  --------------------------------\n", burst_counter);
	uint32_t base_address = mmap_download_struct.base_address;
	for(I = 0; I < mmap_download_struct.number_of_writes; I++)
		// send the burst.
	{
		fprintf(stdout,"0x%x 0x%x\n", base_address, mmap_download_struct.wdata[I]);
		base_address += 4;
	}

	initMmapDownloadStruct();

	return(0x0);
}

int main()
{
	// clear.
	initMmapDownloadStruct();

	FILE * file;
	file= stdin;

	uint32_t addr;
	uint32_t  data;
	int file_read=0;

	int number_of_bytes_read = 0;

	int last_current_word_address = -1;
	int current_word_address = -1;

	int current_read_word    = 0;
	int written_word_count = 0;

	while (1)
	{
		int eof_reached = 0;
		data = 0;

		file_read=fscanf(file, "%x", &addr);
		if (feof(file)) 
		{
			eof_reached = 1;
		}
		else
		{
			file_read=fscanf(file, "%x", &data);
		}

		if(number_of_bytes_read == 0)
		{
			current_word_address = (addr & 0xfffffffc);
			if(!eof_reached)
				current_read_word = (data <<  8*(3 - (addr & 0x3)));
		}

		// word aligned value of addr.
		uint32_t masked_addr = addr & 0xfffffffc;

#if DEBBUGGGG
		fprintf(stderr,"Info: dbg_load_mmap_optimized: addr=0x%x, byte=0x%x, current_word_address=0x%x, masked_addr=0x%x, last_current_word_addr=0x%x\n",
					addr, data, current_word_address, masked_addr, current_word_address);
#endif

		// if current word address (that is, the last sent) is different from the masked value of addr that was just read...
		if ((current_word_address != masked_addr) || (eof_reached))
		{
			// always put the current word into the buffer.
			int sfull;
			sfull = insertWriteIntoMmapDownloadStructmmap(current_word_address, current_read_word);

			int continue_burst = (!eof_reached) && ((current_word_address + 4) == masked_addr);

			if(continue_burst && !sfull)
			// continue and not full... go on.
			{
				// burst can be continued..
#if DEBBUGGGG
				fprintf(stderr, "Continue burst.\n");
#endif
			}
			else
			// !continue or full
			{
				if(!eof_reached) 
					fprintf(stderr,"restart burst\n");
#if DEBBUGGGG
				fprintf(stderr,"Info: dbg_load_mmap_optimized: identified burst(%d) from 0x%x to 0x%x (sfull=%d, eof=%d)\n",
						mmap_download_struct.number_of_writes,
						mmap_download_struct.base_address,
						last_current_word_address,
						sfull, eof_reached);
#endif
				// send the burst..
				exec_burst_mmap_download();
			}


			current_word_address = masked_addr;
			current_read_word = (data <<  8*(3 - (addr & 0x3)));

			written_word_count++;

			if((written_word_count % 1024) == 0)
			{
				fprintf(stderr,"Info: initialized %d words..\n", written_word_count);
			}

			last_current_word_address    = current_word_address;
		}
		else if (current_word_address == masked_addr)
		{
			current_read_word = current_read_word | (data <<  8*(3 - (addr & 0x3)));
		}

		number_of_bytes_read++;

		if(eof_reached)
		{
			break;
		}

	}
	fprintf(stderr, "Last address written = %x\n", addr);


	return (written_word_count);
}

