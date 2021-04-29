#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


FILE* vmap_file = NULL;
FILE* mmap_file = NULL;
FILE* remapped_mmap_file = NULL;



typedef struct RemapStruct__  RemapStruct;
struct RemapStruct__ {
	uint8_t level;			// level of the PDTE
	uint32_t vpn;				// vpn 
	uint32_t ppn;				// ppn 
	RemapStruct* next;
};


RemapStruct* make_remap_struct (uint8_t level,  uint32_t vpn, uint32_t ppn)
{
	RemapStruct* ret_rs = (RemapStruct*) malloc(sizeof(RemapStruct));
	ret_rs->level = level;
	ret_rs->vpn = vpn;
	ret_rs->ppn = ppn;
	ret_rs->next = NULL;

	fprintf(stderr,"Info: new RemapStruct: level=0x%x, vpn=0x%x, ppn=0x%x\n", 
				ret_rs->level, ret_rs->vpn, ret_rs->ppn);
	return(ret_rs);
}

uint32_t remap_va (RemapStruct* rs, uint32_t va)
{
	uint32_t pa = va;
	while(rs != NULL)
	{
		if((va >= rs->vpn) && 
			((rs->level == 0)
				||
			 ((rs->level == 1) && ((va - rs->vpn) < (1 << 24))) 
				||
			 ((rs->level == 2) && ((va - rs->vpn) < (1 << 18))) 
				||
			 ((rs->level == 3) && ((va - rs->vpn) < (1 << 12))) ))
		{
			pa = (rs->ppn + (va - rs->vpn));
			break;
		}

		rs = rs->next;
	}

	return (pa);
}


//
//
//
int main(int argc, char* argv[])
{


	if(argc < 4) 
	{
		fprintf(stderr,"Usage: %s <vmap-file> <mmap-file> <remapped-mmap-file\n", argv[0]);
		return(1);
	}

	vmap_file = fopen(argv[1],"r");
	if(vmap_file == NULL)
	{
		fprintf(stderr,"Error: could not open vmap-file %s\n", argv[1]);
	}

	mmap_file = fopen(argv[2],"r");
	if(mmap_file == NULL)
	{
		fprintf(stderr,"Error: could not open mmap-file %s\n", argv[2]);
	}

	remapped_mmap_file = fopen(argv[3],"w");
	if(remapped_mmap_file == NULL)
	{
		fprintf(stderr,"Error: could not open out-file %s\n", argv[3]);
	}

	RemapStruct* remaps = NULL;
	char data_line[1024];
	while(fgets(data_line,1023, vmap_file) != NULL)
	{

		uint32_t vpn, ppn, level, context;

		// comments in vmap file start with !
		if(data_line[0] != '!')
		{


			char* tbuf = strtok(data_line, " \t");
			if (tbuf == NULL) break;
			sscanf (tbuf, "0x%x", &context);

			tbuf = strtok(NULL, " \t");
			if (tbuf == NULL) break;
			sscanf (tbuf, "0x%x", &vpn);

			tbuf = strtok(NULL, " \t");
			if (tbuf == NULL) break;
			sscanf (tbuf, "0x%x", &ppn);

			tbuf = strtok(NULL, " \t");
			if (tbuf == NULL) break;
			sscanf (tbuf, "0x%x", &level);

			fprintf(stderr,"Info:remap: vpn=0x%x, ppn=0%x, level=0x%x\n",vpn, ppn, level);

			RemapStruct* rs = make_remap_struct (level, vpn, ppn);
			rs->next = remaps;
			remaps = rs;
		}
		if(feof(vmap_file))
			break;
	}

	int byte_count = 0;
	while(!feof(mmap_file))
	{
		uint32_t byte, va;
		int rr = fscanf (mmap_file, "%x %x", &va, &byte);

		if(rr < 2)
			break;

		uint32_t pa = remap_va (remaps, va);
		fprintf(remapped_mmap_file,"%x %x\n", pa, byte);

#ifdef DEBUG
		fprintf(stderr,"Info:remap: map %x -> %x, %x\n", va,pa,byte);
#endif

		byte_count++;
	}

	fprintf(stderr,"Info:remap: re-mapped %d bytes\n", byte_count);

	fclose (vmap_file);
	fclose (mmap_file);
	fclose (remapped_mmap_file);

	return(0);
}
