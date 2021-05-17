#ifndef do_val_h__
#define do_val_h__
//#include "SparcCore.h"
#include <stdio.h>


#include"ajit_validationLexer.h"
#include"ajit_validationParser.h"
#include <antlr3.h>
#include"Record.h"
#include"spi_common.h"

int doval(char* input_file, char* logf);

//int exe_spi_cmd(spi_cmd *cmd_ptr, spi_rsp *resp_ptr);
#endif
