#include <stdint.h>
#include <stdio.h>

#ifdef AJIT
#include <ajit_access_routines.h>

inline void halt()
{
	__asm__ __volatile__("ta 0; nop; nop;");
}

int __enable_serial()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	return(0);
}

int __disable_serial()
{
	__ajit_write_serial_control_register__ (0);
	return(0);
}

int __putchar(char c) 
{
	int rval = 0;
	while(rval == 0)
	{
		rval = __ajit_serial_putchar__(c);
	}
	return((int) c);
}


int __getchar() 
{
	int rval = 0;
	while(rval == 0)
	{
		rval = __ajit_serial_getchar__();
	}
	return(rval);
}

#else
int __putchar(char c) {return(putchar(c));}
int __getchar() {return(getchar());}
#endif

// NULL terminated string.
void __putstring (char* s)
{
	while ((*s) != 0)
	{
		__putchar (*s);
		s++;
	}
}

void run_test (void)
{
	while(1)
	{
		char c = (char) __getchar();

		if(c == EOF)
			break;
		else
			__putchar(c);
	}
}

#ifdef AJIT
#define ASI_MMU_REGISTER                0x04
inline void store_word_mmureg(uint32_t value, uint32_t* addr)
{
        __asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(value), "r"(addr),
                             "i"(ASI_MMU_REGISTER) : "memory");
}


int ajit_main(void)
{	
	store_word_mmureg(0x100,(uint32_t*) 0x0);
	__enable_serial();
	__putstring ("Hello: I will echo whatever you type until you put a ctrl-D\n");	
	run_test();
	__putstring ("\nGoodbye!\n");
	halt();
	return 0;
}

#else

int main (void)
{
  __putstring ("Hello: I will echo whatever you type until you put a ctrl-D\n");	
  run_test();	
  __putstring ("\nGoodbye!\n");
  return(0);
}

#endif
