#ifndef _RECORD_H_
#define _RECORD_H_

typedef struct Record_Struct_
{	
	const char *c;
	int reg_int;
	const char *address;
	const char *expected_value;
	const char* mask;
} Record;

#endif
