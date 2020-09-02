//Ajit_Bootloader.c
//
//A simple bootloader for the Ajit processor.
//The bootloader is located at physical address 0x0.
//It does the following:
//	1. Initialize registers
//	2. []OPTIONAL] Read the kernel image as (addr,byte) pairs from the serial port, and load it in memory
//	3. Initialize the MMU
//	4. Jump to start-address of the kernel.
//
//
// Author: Neha Karanjkar
// 4 November 2016



#include<stdint.h>
#include"Ajit_Hardware_Configuration.h"
#include"CommonSerialRoutines.h"



void     bootloader();

//write a 32b value into memory at a given address
#define STORE(val, addr)  {__asm__("st %0, [%1];\n\t" :/*no output*/:"r"(val),"r"(addr) /*input*/ : "memory" );}

//write an 8b value into memory at a given address
#define STORE_BYTE(val, addr)  {__asm__("stub %0, [%1];\n\t" :/*no output*/:"r"(val),"r"(addr) /*input*/ : "memory" );}

//read a 32b word from memory into a variable
#define LOAD(addr, variable)  {__asm__("ld [%1], %0;\n\t" :"=r"(variable)/* output*/:"r"(addr)/*input*/ :/*clobbered*/ );}




//NOTE : for the entry() function, using attribute
//"((section(".text.main")))" ensures that 
//this function is placed in the beginning 
//of the ".text" section in the generated executable.
int  __attribute__((section(".text.main")))entry()
{
	
	// Initialize PSR
	//PSR_INIT= 0xC0 (EC,PIL=0 EF=1   S,PS=1  ET=0, CWP=0)
	__asm__ __volatile__("set  0xC0,%g1 \n\t");
	__asm__ __volatile__("mov  %g1, %psr    \n\t");
	__asm__ __volatile__("nop               \n\t");
	__asm__ __volatile__("nop               \n\t");
	__asm__ __volatile__("nop               \n\t");


	//initialize registers in window 0
	__asm__ __volatile__( "mov %g0, %g1 \n\t ");
	__asm__ __volatile__( "mov %g0, %g2 \n\t ");
	__asm__ __volatile__( "mov %g0, %g3 \n\t ");
	__asm__ __volatile__( "mov %g0, %g4 \n\t ");
	__asm__ __volatile__( "mov %g0, %g5 \n\t ");
	__asm__ __volatile__( "mov %g0, %g6 \n\t ");
	__asm__ __volatile__( "mov %g0, %g7 \n\t ");

	__asm__ __volatile__( "mov %g0, %i0 \n\t ");
	__asm__ __volatile__( "mov %g0, %i1 \n\t ");
	__asm__ __volatile__( "mov %g0, %i2 \n\t ");
	__asm__ __volatile__( "mov %g0, %i3 \n\t ");
	__asm__ __volatile__( "mov %g0, %i4 \n\t ");
	__asm__ __volatile__( "mov %g0, %i5 \n\t ");
	__asm__ __volatile__( "mov %g0, %i6 \n\t ");
	__asm__ __volatile__( "mov %g0, %i7 \n\t ");

	__asm__ __volatile__( "mov %g0, %l0 \n\t ");
	__asm__ __volatile__( "mov %g0, %l1 \n\t ");
	__asm__ __volatile__( "mov %g0, %l2 \n\t ");
	__asm__ __volatile__( "mov %g0, %l3 \n\t ");
	__asm__ __volatile__( "mov %g0, %l4 \n\t ");
	__asm__ __volatile__( "mov %g0, %l5 \n\t ");
	__asm__ __volatile__( "mov %g0, %l6 \n\t ");
	__asm__ __volatile__( "mov %g0, %l7 \n\t ");

	__asm__ __volatile__( "mov %g0, %o0 \n\t "); 
	__asm__ __volatile__( "mov %g0, %o1 \n\t ");
	__asm__ __volatile__( "mov %g0, %o2 \n\t "); 
	__asm__ __volatile__( "mov %g0, %o3 \n\t ");
	__asm__ __volatile__( "mov %g0, %o4 \n\t "); 
	__asm__ __volatile__( "mov %g0, %o5 \n\t ");
	__asm__ __volatile__( "mov %g0, %o6 \n\t "); 
	__asm__ __volatile__( "mov %g0, %o7 \n\t ");
	
	//initialize registers in all other windows
	int w;
	for(w=7;w>=1;w--)
	{
		//move to window 'w'
		__asm__ __volatile__( "save\n\t "); 
		//clear registers
		__asm__ __volatile__( "mov %g0, %l0 \n\t ");
		__asm__ __volatile__( "mov %g0, %l1 \n\t ");
		__asm__ __volatile__( "mov %g0, %l2 \n\t "); 
		__asm__ __volatile__( "mov %g0, %l3 \n\t ");
		__asm__ __volatile__( "mov %g0, %l4 \n\t "); 
		__asm__ __volatile__( "mov %g0, %l5 \n\t ");
		__asm__ __volatile__( "mov %g0, %l6 \n\t "); 
		__asm__ __volatile__( "mov %g0, %l7 \n\t ");

		__asm__ __volatile__( "mov %g0, %o0 \n\t "); 
		__asm__ __volatile__( "mov %g0, %o1 \n\t ");
		__asm__ __volatile__( "mov %g0, %o2 \n\t ");
		__asm__ __volatile__( "mov %g0, %o3 \n\t ");
		__asm__ __volatile__( "mov %g0, %o4 \n\t "); 
		__asm__ __volatile__( "mov %g0, %o5 \n\t ");
		__asm__ __volatile__( "mov %g0, %o6 \n\t "); 
		__asm__ __volatile__( "mov %g0, %o7 \n\t ");
	}
	
	//Go back to window 0 and 	
	//initialize wim
	//WIM_INIT= 2 ( CWP =0 and window 1 is invalid)
	__asm__ __volatile__("set 0x2, %g3  \n\t");
	__asm__ __volatile__("mov %g3, %wim \n\t");
	__asm__ __volatile__("mov %g0, %g3  \n\t");
	__asm__ __volatile__("nop \n\t");
	__asm__ __volatile__("nop \n\t");
	__asm__ __volatile__("nop \n\t");

	//Now jump to the Bootloader.
	bootloader();
	//NOTE!! It is necessary to have the 
	//bootloader code as a separate function, 
	//and *not* as code within the context of this function.
	//This is because sp/fp registers are 0.
	//A call to bootloader() will initialize sp and fp correctly.
	

	//this code will never run:
	__asm__ __volatile__( "ta 0\n\t nop \n\t nop\n\t nop\n\t");
	return 0;
}


uint8_t  toHexDigit(char c);
uint32_t get_uint32();
uint8_t  get_uint8();
void 	 put_uint32(uint32_t n);
void 	 put_uint8(uint8_t n);



//the main bootloader code
void  bootloader()
{

	//Enable Tx and Rx in the serial device
	enableTx();
	enableRx();
	
	sendAString("\nAjit Bootloader : Downloading kernel image...\n");
	
	//inputs
	uint32_t NUM_PAGES=0;   	//number of pages to download
	uint32_t PAGE_SIZE=0;		//size of each page
	uint32_t PAGE_START_ADDR=0;	//start addr for each page
	uint8_t	 BYTE=0; 		//program byte

	uint8_t  PAGE_PARITY=0;  	//xor of all bytes in a page
	uint8_t  EXPECTED_PAGE_PARITY=0;

	uint32_t PAGE_TERMINATION=0;
	uint32_t EXPECTED_PAGE_TERMINATION = 0xdeadc0de;
	uint32_t STARTADDR=0; //start addr to which control is passed
	

	//read the values:
	NUM_PAGES = get_uint32();
	PAGE_SIZE = get_uint32();

	int n= NUM_PAGES;
	int failure=0;

	while(n > 0)
	{
		PAGE_START_ADDR = get_uint32();
		EXPECTED_PAGE_PARITY=0;


		uint32_t b;
		for(b=0;b<PAGE_SIZE;b++)
		{
			BYTE = get_uint8();
			EXPECTED_PAGE_PARITY ^= BYTE;
			
			//store the byte in memory
			STORE_BYTE(BYTE, PAGE_START_ADDR+b);
		}
		PAGE_PARITY = get_uint8();
		PAGE_TERMINATION = get_uint32();
		
		//check correctness
		if(!((PAGE_PARITY == EXPECTED_PAGE_PARITY) && (PAGE_TERMINATION == EXPECTED_PAGE_TERMINATION)))
		{
			failure=1;
			break;
		}
		
		//next page
		n -= 1;
		
		sendAString("\nFinished downloading page ");
		put_uint32(NUM_PAGES-n);
		sendAString("\n");
	}

	
	if(!failure)
	{
		STARTADDR = get_uint32();
		sendAString("\nSuccessful load, passes checksum.");
		sendAString("\nEnabling the Mmu and jumping to kernel_start address: 0x");
		put_uint32(STARTADDR);
		sendAString("\n\n");
		__asm__ __volatile__( "jmp %0\n\t " "nop\n\t" ::"r"(STARTADDR):);
	}
	else
	{
		sendAString("\nERROR: Parity/termination check failed!");
		sendAString("\n          page   = ");put_uint32(n);
		sendAString("\n          parity = ");put_uint32(PAGE_PARITY);
		sendAString("\n computed parity = ");put_uint32(EXPECTED_PAGE_PARITY);
		sendAString("\n       page term = ");put_uint32(PAGE_TERMINATION);
		sendAString("\n   expected term = ");put_uint32(EXPECTED_PAGE_TERMINATION);

	}

	//halt
	__asm__ __volatile__( "ta 0\n\t nop \n\t nop\n\t nop\n\t");

}


//interpret the value represented by a char as a hex digit
inline uint8_t toHexDigit(char c)
{
	if	(c>='0'&& c<='9') return (c-'0')& 0xf;
	else if (c>='a'&& c<='f') return (0xa + (c-'a'))& 0xf;
	else if (c>='A'&& c<='F') return (0xa + (c-'A')) &0xf;
	else {sendAString("\ninvalid input!"); return(0);}
}

//convert the numerical value of a hex digit
//to a char
inline char toChar(uint8_t n)
{
	char c =0;
	if	(n>=0x0 && n<=0x9) c = '0' + n;
	else if (n>=0xa && n<=0xf) c = 'a' + (n-0xa);
	return c;
}

//read an 8b number represented as 2 hex digits
//terminated by a newline from the serial port.
inline uint8_t get_uint8()
{
	uint8_t ret_val=0;
	char c1 = getAChar();
	char c0 = getAChar();
	
	ret_val = (toHexDigit(c1)<<4) | toHexDigit(c0);

	//read a newline
	char c = getAChar();
	if(c!='\n') {sendAString("\ninvalid input!"); return(0);}
	else return(ret_val);
}



//read a 32b number represented as 8 hex digits
//terminated by a newline from the serial port.
inline uint32_t get_uint32()
{
	uint32_t ret_val=0;
	char c7 =getAChar();
	char c6 =getAChar();
	char c5 =getAChar();
	char c4 =getAChar();
	char c3 =getAChar();
	char c2 =getAChar();
	char c1 =getAChar();
	char c0 =getAChar();
	
	ret_val = (toHexDigit(c7)<<4) | toHexDigit(c6);
	ret_val = (ret_val<<8) | (toHexDigit(c5)<<4) | toHexDigit(c4);
	ret_val = (ret_val<<8) | (toHexDigit(c3)<<4) | toHexDigit(c2);
	ret_val = (ret_val<<8) | (toHexDigit(c1)<<4) | toHexDigit(c0);

	//read a newline
	char c = getAChar();
	if(c!='\n') {sendAString("\ninvalid input!"); return(0);}
	
	return(ret_val);
}




//write a 32b number as 8 hex digits
//terminated by a newline from the serial port.
void put_uint32(uint32_t n)
{
	uint8_t b7 = (n>>(7*4)) & ((uint32_t)0x0f); sendAChar( toChar(b7));
	uint8_t b6 = (n>>(6*4)) & ((uint32_t)0x0f); sendAChar( toChar(b6));
	uint8_t b5 = (n>>(5*4)) & ((uint32_t)0x0f); sendAChar( toChar(b5));
	uint8_t b4 = (n>>(4*4)) & ((uint32_t)0x0f); sendAChar( toChar(b4));
	uint8_t b3 = (n>>(3*4)) & ((uint32_t)0x0f); sendAChar( toChar(b3));
	uint8_t b2 = (n>>(2*4)) & ((uint32_t)0x0f); sendAChar( toChar(b2));
	uint8_t b1 = (n>>(1*4)) & ((uint32_t)0x0f); sendAChar( toChar(b1));
	uint8_t b0 = (n>>(0*4)) & ((uint32_t)0x0f); sendAChar( toChar(b0));

}

//write an 8b number as 2 hex digits
//terminated by a newline from the serial port.
void put_uint8(uint8_t n)
{

	uint8_t b1 = (n>>(1*4)) & ((uint8_t)0x0f); sendAChar( toChar(b1));
	uint8_t b0 = (n>>(0*4)) & ((uint8_t)0x0f); sendAChar( toChar(b0));
}
