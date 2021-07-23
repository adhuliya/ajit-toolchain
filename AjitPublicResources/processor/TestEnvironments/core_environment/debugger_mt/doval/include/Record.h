#ifndef _RECORD_H_
#define _RECORD_H_
#include <stdint.h>

typedef struct Record_Struct_
{	
	const char *c;
	int reg_int;
	const char *address;
	const char *expected_value;
	const char* mask;
	uint32_t core_id;
	uint32_t thread_id;

} Record;

#endif
