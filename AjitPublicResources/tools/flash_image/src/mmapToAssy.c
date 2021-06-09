#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <mmapToAssy.h>

Segment* head = NULL;
Segment* tail = NULL;

Segment* makeSegment(int id, uint32_t starting_dest_addr)
{
	Segment* ret_seg = (Segment*) malloc(sizeof(Segment));
	ret_seg->segment_id = id;
	ret_seg->starting_dest_address = starting_dest_addr;
	ret_seg->segment_length = 0;
	ret_seg->data_head = NULL;
	ret_seg->data_tail = NULL;
	ret_seg->next = NULL;
}

void appendSegment(Segment* s)
{
	if(tail == NULL)
	{
		head = s;
		tail = s;
		s->next = NULL;
	}
	else
	{	
		tail->next = s;
		s->next = NULL;
		tail = s;
	}
}

void addDataLink(Segment* s, uint8_t data)
{
	DataLink* nl = (DataLink*) malloc(sizeof(DataLink));

	nl->byte = data;
	nl->next = NULL;

	if(s->data_tail == NULL)
	{
		s->data_tail = nl;
		s->data_head = nl;
	}
	else
	{
		s->data_tail->next = nl;
		s->data_tail = nl;
	}

	s->segment_length++;
}

void printAssembly (FILE* out_file)
{
	
	fprintf(out_file,".section .text.copy_program_image\n");
	fprintf(out_file,".global copy_program_image\n");
	fprintf(out_file,"copy_program_image:\n");
	fprintf(out_file,  "    save;\n");

	Segment*  cs;
	for(cs = head; cs != NULL; cs = cs->next)
	{	
	 	if(cs->segment_length > 0)
		{
			fprintf(out_file,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			fprintf(out_file,"!   starting source address of data segment %d\n", cs->segment_id);
			fprintf(out_file,"    set MMAP_SEGMENT_%d, %s\n", cs->segment_id, "%g3");
			fprintf(out_file,"!   length of data segment\n");
			fprintf(out_file,"    set %d, %s\n", cs->segment_length, "%g4");
			fprintf(out_file,"!   starting destination address of data segment\n");
			fprintf(out_file,"    set 0x%x, %s\n", cs->starting_dest_address, "%g5");
			fprintf(out_file,"!   call function defined in bootstrap.s \n");
			fprintf(out_file,"    call _copy_segment\n");
			fprintf(out_file,"    nop\n");
			fprintf(out_file,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		}
		else
		{
			fprintf(out_file,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			fprintf(out_file,"!    skipped empty MMAP_SEGMENT_%d\n", cs->segment_id);
			fprintf(out_file,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		}
	}

	fprintf(out_file,  "    restore\n");
	fprintf (out_file, "    retl\n");
	fprintf (out_file, "    nop\n");

	for(cs = head; cs != NULL; cs = cs->next)
	{
		fprintf(out_file,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		fprintf(out_file,"! Start segment %d, length=%d, starting_dest_addr=0x%x\n",
				cs->segment_id, cs->segment_length, cs->starting_dest_address);
		fprintf(out_file,".align 8\n");
		fprintf(out_file,".global MMAP_SEGMENT_%d\n", cs->segment_id);
		fprintf(out_file,"MMAP_SEGMENT_%d:\n", cs->segment_id);
		DataLink* dl;
		for(dl = cs->data_head; dl != NULL; dl = dl->next)
		{
			fprintf(out_file,".byte 0x%x\n", dl->byte);
		}
		fprintf(out_file,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	}
}

//
// generate assembly code to copy bytes to base-address + offset.
//
int main(int argc, char* argv[])
{


	FILE *in_file, *out_file;
	if(argc < 4) 
	{
		fprintf(stderr,"Usage: %s <in-file> <out-file> <base-address-value (0x...) >\n", argv[0]);
		return(1);
	}

	in_file = fopen(argv[1],"r");
	if(in_file == NULL)
	{
		fprintf(stderr,"Error: could not open infile %s\n", argv[1]);
	}

	out_file = fopen(argv[2],"w");
	if(out_file == NULL)
	{
		fprintf(stderr,"Error: could not open outfile %s\n", argv[2]);
	}


	uint32_t current_address_pointer;
	sscanf (argv[3], "%x", &current_address_pointer);
	fprintf(stderr,"Info: base address = 0x%x\n", current_address_pointer);

	Segment* curr_segment = makeSegment(0,current_address_pointer);
	fprintf(stderr,"Info: started segment %d\n", curr_segment->segment_id);
	appendSegment(curr_segment);

	char data_line[1024];
	while(fgets(data_line,1023,in_file) != NULL)
	{
		// comments start with !
		if(data_line[0] == '!') continue;

		char* addr_buf = strtok(data_line, " \t");
		if (addr_buf == NULL) break;

		uint32_t address = 0;
		sscanf (addr_buf, "%x", &address);
		if(address != current_address_pointer)
		{
			curr_segment = makeSegment((curr_segment->segment_id+1), address);
			appendSegment(curr_segment);
			fprintf(stderr,"Info: started segment %d\n", curr_segment->segment_id);
			current_address_pointer = address;
		}

		char* data_buf = strtok(NULL, " \t");
		if (data_buf == NULL) break;

		uint32_t byte_val;	
		sscanf (data_buf, "%x", &byte_val);
		addDataLink(curr_segment,byte_val);

		current_address_pointer++;
	}

	printAssembly(out_file);

	fclose(in_file);
	fclose(out_file);

	return(0);
}


