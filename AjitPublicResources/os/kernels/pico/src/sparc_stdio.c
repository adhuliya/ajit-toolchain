#include "sparc_stdio.h"

//Indicate SUCCESS and HALT processor

void halt(void)
{
	//halt simulation by putting the processor into error mode.
	//Sparc enters error mode when a trap is caused while ET=0.
	//So make ET=0 and cause a software trap.
	__asm__ __volatile__("  mov %%g0, %%psr \n"
			     "	nop	\n"
			     "	nop	\n" 
			     "	nop	\n"
			     "  ta 0    \n\t"
				: /* no outputs */
				: /* no inputs */
				: "cc");
}


void putChar(char val)
{
	char console_flag = CHAR_TYPE_DATA;
	//wait till display driver reads the last character
	//and clears console flag.
	while(console_flag > 0)
	{
		console_flag = load_char((char*)CONSOLE_FLAG_ADDRESS);
	}

	//write value into the buffer
	store_char((char*) CONSOLE_BUFFER_START_ADDRESS, val);
	//set flag
	store_char((char*) CONSOLE_FLAG_ADDRESS, CHAR_TYPE_DATA);
}


void putString(char word[])
{
	int i;
	for(i = 0; word[i] != '\0'; i++)
	{
		putChar(word[i]);	
	}
}


void putInt(int val)
{
	char console_flag = INT_TYPE_DATA;
	while(console_flag > 0)
	{
		console_flag = load_char((char*)CONSOLE_FLAG_ADDRESS);
	}
	store_int((int*) CONSOLE_BUFFER_START_ADDRESS, val);
	store_char((char*) CONSOLE_FLAG_ADDRESS, INT_TYPE_DATA);
}

void putFloat(float val)
{
	char console_flag = FLOAT_TYPE_DATA;
	
	while(console_flag > 0)
	{
		console_flag = load_char((char*) CONSOLE_FLAG_ADDRESS);
	}
	store_float((float*)CONSOLE_BUFFER_START_ADDRESS, val);
	store_char((char*) CONSOLE_FLAG_ADDRESS,FLOAT_TYPE_DATA);
}

void putDouble(double val)
{
	char console_flag = DOUBLE_TYPE_DATA;
	
	while(console_flag > 0)
	{
		console_flag = load_char((char*) CONSOLE_FLAG_ADDRESS);
	}
	store_double((double*)CONSOLE_BUFFER_START_ADDRESS, val);
	store_char((char*) CONSOLE_FLAG_ADDRESS,DOUBLE_TYPE_DATA);
}


char getChar()
{

	char kb_flag = CHAR_TYPE_DATA;
	char val;
	//set kb flag
	store_char((char*) KB_FLAG_ADDRESS, kb_flag);
	while(kb_flag  > 0)
	{
		//wait for flag to be reset by driver
		kb_flag = load_char((char*) KB_FLAG_ADDRESS);
	}
	//return value in the buffer
	val = load_char((char*)KB_BUFFER_START_ADDRESS);
	return val;
}

int getInt()
{
	char kb_flag = INT_TYPE_DATA;
	int val;
	//set kb flag
	store_char((char*) KB_FLAG_ADDRESS, kb_flag);
	while(kb_flag  > 0)
	{
		//wait for flag to be reset by driver
		kb_flag = load_char((char*) KB_FLAG_ADDRESS);
	}
	//return value in the buffer
	val = load_int((int*)KB_BUFFER_START_ADDRESS);
	return val;
}

float getFloat()
{
	char kb_flag = FLOAT_TYPE_DATA;
	float val;
	//set kb flag
	store_char((char*) KB_FLAG_ADDRESS, kb_flag);
	while(kb_flag  > 0)
	{
		//wait for flag to be reset by driver
		kb_flag = load_char((char*) KB_FLAG_ADDRESS);
	}
	//return value in the buffer
	val = load_float((float*)KB_BUFFER_START_ADDRESS);
	return val;
}

double getDouble()
{
	char kb_flag = DOUBLE_TYPE_DATA;
	double val;
	//set kb flag
	store_char((char*) KB_FLAG_ADDRESS, kb_flag);
	while(kb_flag  > 0)
	{
		//wait for flag to be reset by driver
		kb_flag = load_char((char*) KB_FLAG_ADDRESS);
	}
	//return value in the buffer
	val = load_double((double*)KB_BUFFER_START_ADDRESS);
	return val;
}

void getString(char* str)
{
	char kb_flag = STRING_TYPE_DATA;
	int i;
	char c;

	//set kb flag
	store_char((char*) KB_FLAG_ADDRESS, kb_flag);
	//wait for flag to be reset by driver
	while(kb_flag  > 0)
	{
		kb_flag = load_char((char*) KB_FLAG_ADDRESS);
	}
	for(i = 0;i < KB_BUFFER_SIZE ; i++)
	{
		c = load_char((char*)(KB_BUFFER_START_ADDRESS + i));
		str[i] = c;
		if(c == '\0')
			break;
	}
}
