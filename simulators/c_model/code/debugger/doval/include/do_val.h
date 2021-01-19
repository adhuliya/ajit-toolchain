#ifndef do_val_h__
#define do_val_h__
#include "Mmu.h"
#include "CacheInterface.h"
#include "SparcCore.h"
#include "hwServer.h"
#include <stdio.h>


#include"ajit_validationLexer.h"
#include"ajit_validationParser.h"
#include <antlr3.h>
#include"Record.h"
#include"spi_common.h"

//
// arguments: 
//  1. command and response pipes to interact with 4 cores.
//  2. input-file
//  3. log file.
// returns 0 on success. 
int doval(ProcessorState** cpu_state_vector,
		char* input_file, char* logf);

//int exe_spi_cmd(spi_cmd *cmd_ptr, spi_rsp *resp_ptr);
#endif
