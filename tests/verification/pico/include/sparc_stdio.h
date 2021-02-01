#ifndef __SPARC_STDIO_H__
#define __SPARC_STDIO__


//------------------------------------
//Memory addresses used by Keyboard/Display threads
//as flag and buffer
#include "Ajit_Hardware_Configuration.h"


//flag values to indicate the type of
//data to keyboard/console drivers
#define CHAR_TYPE_DATA	1
#define INT_TYPE_DATA	2
#define FLOAT_TYPE_DATA	3
#define DOUBLE_TYPE_DATA 4
#define STRING_TYPE_DATA 5
//---------------------------------



void halt(void);



//Routines for performing loads/stores
//to a physical memory address 
//bypassing the MMU and caches.
#include<stdint.h>
#define ASI_MMU_BYPASS 0x2F
 

// Size of char     = 1   bytes
// Size of int      = 4   bytes
// Size of float    = 4   bytes
// Size of double   = 8   bytes
// Size of long int = 4   bytes


//load char
static inline char load_char(char* paddr)
{
        char retval;
        __asm__ __volatile__("lduba [%1] %2, %0\n\t" :
                             "=r"(retval) : "r"(paddr), "i"(ASI_MMU_BYPASS));
        return retval;
}

//load int
static inline int load_int(int* paddr)
{
        int retval;
        __asm__ __volatile__("lda [%1] %2, %0\n\t" :
                             "=r"(retval) : "r"(paddr), "i"(ASI_MMU_BYPASS));
        return retval;
}
//load float
static inline float load_float(float* paddr)
{
        float retval;
        __asm__ __volatile__("lda [%1] %2, %0\n\t" :
                             "=r"(retval) : "r"(paddr), "i"(ASI_MMU_BYPASS));
        return retval;
}

//load double
static inline double load_double(double* paddr)
{
        double retval;
        __asm__ __volatile__("ldda [%1] %2, %0\n\t" :
                             "=r"(retval) : "r"(paddr), "i"(ASI_MMU_BYPASS));
        return retval;
}

//store char
static inline void store_char(char* paddr, char value)
{
	__asm__ __volatile__("stuba %0, [%1] %2\n\t" : : "r"(value), "r"(paddr),
			     "i"(ASI_MMU_BYPASS) : "memory");
}
//store int
static inline void store_int(int* paddr, int value)
{
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(value), "r"(paddr),
			     "i"(ASI_MMU_BYPASS) : "memory");
}
//store float
static inline void store_float(float* paddr, float value)
{
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(value), "r"(paddr),
			     "i"(ASI_MMU_BYPASS) : "memory");
}

//store double
static inline void store_double(double* paddr, double value)
{
	__asm__ __volatile__("stda %0, [%1] %2\n\t" : : "r"(value), "r"(paddr),
			     "i"(ASI_MMU_BYPASS) : "memory");
}




void putChar(char val);
void putString(char word[]);
void putInt(int val);
void putFloat(float val);
void putDouble(double val);
void getString(char* str);

char getChar();
int getInt();
float getFloat();
double getDouble();

#endif
