#ifndef do_val_h__
#define do_val_h__
//#include "Mmu.h"
//#include "CacheInterface.h"
#include <stdio.h>


#include"ajit_validationLexer.h"
#include"ajit_validationParser.h"
#include <antlr3.h>
#include"Record.h"
#include"spi_common.h"

//
// arguments: 
//  1. input-file
//  2. log file.
// returns 0 on success. 
int doval(char* input_file, char* logf);

#endif
