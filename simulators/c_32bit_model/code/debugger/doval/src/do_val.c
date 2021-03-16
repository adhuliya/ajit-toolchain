
// Author : Piyush Soni
// The C program parses the results file using antlr3 and communicates 
// with the processor to get its register values according to the results 
// file, compares them and generates a log file.

#include"ajit_validationLexer.h"
#include"ajit_validationParser.h"
#include"spi_common.h"
#include"Record.h"
#include "Ancillary.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "do_val.h"
#include <stdlib.h>	//for strtol

// local functions.
void parser ();
int register_id (const char* reg, int intgr);
int hex_strg_to_int();
uint8_t gen_log(uint32_t line_num, gpb_spi_rsp resp_pckt);
void setup(char* input_file);
void perform_validation(uint32_t line_num);
int fill_send_struct (gpb_spi_cmd* send_pckt);

// globals
int reg_id;
FILE *log_file;
Record rec;

pajit_validationParser psr;
pANTLR3_UINT8      		finput; //The template for generating code
pANTLR3_INPUT_STREAM   		input;
pajit_validationLexer		lxr;
pANTLR3_COMMON_TOKEN_STREAM	tstream;

uint32_t exptd_value, mem_asi, address, compare_mask;
char *logfile;
char* log_f;
int global_error_flag = 0;

int doval(char* input_file, char* logf)
{	
	rec.c = NULL;
	rec.reg_int = 0;
	rec.address = NULL;
	rec.expected_value = NULL;
	rec.mask = NULL;

	//processor = (*proc_state);
	log_f = logf;
	log_file = fopen(log_f, "w");

	setup (input_file);

	parser ();

	// Free up everything
	if(psr!=NULL) 	{psr->free(psr); 	psr  = NULL;}
	if(tstream!=NULL){tstream ->free  (tstream);  	tstream = NULL;}
	if(lxr!=NULL)	{lxr->free(lxr);	lxr = NULL;}
	if(input!=NULL)	{input ->close (input);    input   = NULL;}

	// printf("\n");
	return global_error_flag;
}


void parser ()
{
	uint32_t lin = 1;
	
	// pass the pointer of data structure to the parser
	psr->rec= &rec;
	psr->mask_flag = 0;

	// Now start parsing
	psr->line(psr);

	// parse till EOF
	while (rec.c[0] != 'x')	{
		perform_validation (lin);

		// parse next line
		psr->line(psr);

		//printf("\nrec.c = %s", rec.c);
		//printf("\nindex = %d", rec.reg_int);
		//printf("\nreg id = %d\n", reg_id);

		lin++;
	}

	fclose(log_file);
	return;
}


void perform_validation (uint32_t line_num)
{
	gpb_spi_cmd send_pckt;
	gpb_spi_rsp resp_pckt;


	// get values in hex from string
	hex_strg_to_int();

	// get reg id
	register_id(rec.c, rec.reg_int);

	fill_send_struct (&send_pckt);

	// send and receive response
	send_gpb_spi_cmd (&send_pckt);
	recv_gpb_spi_cmd (&resp_pckt);
	// printf ("resp_pckt.content = %u\n", resp_pckt.content);

	//exe_spi_cmd (&send_pckt, &resp_pckt);

	// write log
	uint8_t err = gen_log(line_num, resp_pckt);


	if (err)
	{
		//printf ("Error in %s\n", log_f);
		global_error_flag = 1;
	}

	return;
}


// to write in log file
uint8_t gen_log (uint32_t line_num, gpb_spi_rsp resp_pckt)
{
	uint8_t err = 0;
	char result[10];

	if ((resp_pckt.content & compare_mask) != (exptd_value & compare_mask))
	{
		strcpy(result, "ERROR");
		err = 1;
	}
	else
	{
		strcpy(result, "correct");
	}

	// convert to integer index of register.
	int reg_id = register_id(rec.c, rec.reg_int);

	const char* reg = rec.c;

	// write mmu and mem
	if (reg[0] == 'm') {
		if (reg[1] == 'm') {
			fprintf(log_file, "%u. %s :\t%s%d,\tid = %d,", line_num, result, rec.c, rec.reg_int, 
									reg_id);
			fprintf(log_file, " \texpected = 0x%x,  \t\tactual = 0x%x (mask=0x%x)\n", exptd_value,
												resp_pckt.content,
												compare_mask);
		} else {
			fprintf(log_file, "%u. %s : \t%s,\tmem_asi = 0x%x,", line_num, result, rec.c, mem_asi);
			fprintf(log_file, "\texpected = 0x%x,  \t\tactual = 0x%x, \t\taddr = 0x%x (mask=0x%x)\n", 
							exptd_value, resp_pckt.content, address, compare_mask);
		}

		// write g, o, l, i, f, asr
	} else if (((reg[1] == '\0') & (reg[0] != 'y')) | (reg[0] == 'a')) {
		fprintf(log_file, "%u. %s :	%s%d,	id = %d,", line_num, result ,rec.c, rec.reg_int, reg_id);
		fprintf(log_file, " \texpected = 0x%x,  \t\tactual = 0x%x (mask=0x%x)\n", exptd_value, resp_pckt.content, compare_mask);

		// write psr, y, wim etc
	} else {
		fprintf(log_file, "%u. %s :\t%s,\tid = %d,", line_num, result, rec.c, reg_id);
		fprintf(log_file, " \texpected = 0x%x,  \t\tactual = 0x%x (mask=0x%x)\n", exptd_value, resp_pckt.content, compare_mask);
	}
	return err;		
}


int hex_strg_to_int()
{
	exptd_value = (uint32_t) strtoll(rec.expected_value, NULL, 0);
	compare_mask = (uint32_t) strtoll(rec.mask, NULL, 0);
	// printf("\nexptd_value = %d, hex string = %s\n", exptd_value, rec.expected_value);



	if ((rec.c[0] == 'm') & (rec.c[1] == 'e')) {

		address = (uint32_t) strtoll(rec.address, NULL, 0);
		// printf("address = %d, hex string = %s\n", address, rec.address);

		psr->line(psr);
		mem_asi = (uint32_t) strtoll(rec.expected_value, NULL, 0);
		// printf("mem_asi = %d, hex string = %s\n", mem_asi, rec.expected_value);
	}
	return 0;
}


int fill_send_struct (gpb_spi_cmd *send_pckt)
{
	// fill the send strcuture
	if ((rec.c[0] == 'm') & (rec.c[1] == 'e')) {
		send_pckt->cmd = 'm';
		send_pckt->reg_id = mem_asi;
		send_pckt->address = address;
		send_pckt->data = 0;
	}

	else {
		send_pckt->cmd = 'r';
		send_pckt->reg_id = reg_id;
		send_pckt->address = 0;	
		send_pckt->data = 0;
	}
	return 0;
}


int register_id (const char* reg, int intgr)
{
	//	int reg_id;

	if (reg[0] == 'g') 
		reg_id = 0 + intgr;		

	else if (reg[0] == 'o')
		reg_id = 8 + intgr;

	else if (reg[0] == 'l') 
		reg_id = 16 + intgr;

	else if (reg[0] == 'i') 
		reg_id = 24 + intgr;

	else if (reg[0] == 'y')			//y
		reg_id = 64;

	else if (reg[0] == 'p') {
		if (reg[1] == 's')		//psr
			reg_id = 65;		
		else	
			reg_id = 68;		//pc
	}
	else if (reg[0] == 'w')			//wim
		reg_id = 66;

	else if (reg[0] == 't') 		//tbr
		reg_id = 67;

	else if (reg[0] == 'n') 		//npc
		reg_id = 69;

	else if (reg[0] == 'f') { 
		if (reg[1] == 'p')
			reg_id = 70;		//fpsr
		else
			reg_id = 32 + intgr;	//f
	}

	else if (reg[0] == 'c') 		//cpsr
		reg_id = 71;

	else if (reg[0] == 'a') 		//asr
		reg_id = 77 + intgr;

	else					//mmu
		reg_id = 72 + intgr;

	return (reg_id);
}

void setup (char *input_file)
{
	//start translation
	finput=(pANTLR3_UINT8)(input_file);   
	input = antlr3FileStreamNew ((pANTLR3_UINT8)finput, ANTLR3_ENC_8BIT);

	if ( input == NULL)
	{
		printf("Failed to open file %s\n", (char *)finput);
	}
	lxr        = ajit_validationLexerNew(input);

	if ( lxr == NULL )
	{
		printf("Unable to create the lexer due to malloc() failure1\n");
	}
	tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lxr));

	if (tstream == NULL)
	{
		printf("Out of memory trying to allocate token stream\n");
	}
	// Finally, now that we have our lexer constructed, we can create the parser
	//
	psr        = ajit_validationParserNew(tstream);  // CParserNew is generated by ANTLR3

	if (psr == NULL)
	{
		printf("Out of memory trying to allocate token stream\n");
	}

	return;
}


