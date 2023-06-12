#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<cortos.h>
#include"a64string.h"
int a=0,b=0;
uint32_t volatile state; 
char random_char(int index) {
        char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        return charset[index];
}
/*
int rndm()
{
	//A linear congruential PRNG. Values taken from standard glibc implementations.

	int32_t val = state;
	val = ((state *1103515245) + 12345) % 2147483648;
	state = val;
	int result = (int) val;
	return result;
}
*/

int i;
void main() {
/*
while(1)

{

	// Get initial seed use clock, get random string using rndm()
	uint64_t t = cortos_get_clock_time();
	state = t & (0xffffffff);                 
	
	int STRLEN = rndm() % 1200;
	cortos_printf("length is %d \n", STRLEN);
         _Alignas(8) char str[STRLEN];
        int i, index;

        for (i = 0; i < STRLEN - 1; i++) {
                index = rndm() % 51;
                str[i] = random_char(index);

	}
	str[i]="\0";
         _Alignas(8) char str0[STRLEN];

        for (i = 0; i < STRLEN - 1; i++) {
                index = rndm() % 51;
                str0[i] = random_char(index);

        
        }
        str0[i]="\0";
     
*/

char str[100] ="";
//----string length-------

char *strl = "vlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsi";
for (i=0;i<9;i++)
{
b= strlen(strl+i);
a = a64strlen(strl+i);

cortos_printf("string length is %d \n",a);

if (a!=b)
{
        cortos_printf("error in strlen at i = %d \n", i);
        break;

}
}
//-----string concatenate-------
char *strcon2  = "vlsivlsivlsivlsi";
 
for (i=0;i<9;i++)
{
char strcon0[100]  = "vlsivlsivlsivlsi";
cortos_printf("value of intial string for concatenate %s \n", strcon0);          
//a = strcat(strcon0, (strcon2+i));      
//cortos_printf("value of string after concatentaion %s \n", strcon0);
         
a = a64strcat(strcon0, (strcon2+i));

cortos_printf("value of string after concatentaion %s \n", strcon0);                      
}


//------- string compares ----------


char *strcomp = "vlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsi";
char *strcomp2="vlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsivlsi";

for (i=0;i<9;i++)

{
a =  a64strcmp(strcomp, (strcomp2 +i));           
b = strcmp (strcomp,(strcomp2+i));
if (a!=b)
{
        cortos_printf("error in strcmp at i = %d , a = %d and b = %d\n", i,a,b);
        break;

}
} 
//------string case compare----

char *strcase ="vVVVVvVVVVVVVVVVVVVVVVVVVvvvvvVVvVVVvVVvvvVVVvvVVVVVVVvvvvvvvVVVVVvVvvvVVVVVVvVVVVVVvvvvv";
char *strcase2="VvvvvvvvvvvvvvvvvvvvvvvvvvvvvVVvvvvvVvvVVVvvvVVvvvvvvVVVVVVVVvvvvvvvVVVVvvvvVvvvvvvVVVVVV";

for (i=0;i<9;i++)
{
a =  a64strcasecmp(strcase, (strcase2+i));      
b = strcasecmp(strcase,(strcase2+i));
if (a!=b)
{
        cortos_printf("error in strcasecmp at i = %d \n",i);
        break;
}
}
// --------striing copy -------

char *strcop ="vlsivlsivlsivlsivlsivlsivlsivlsivlsi";
char *strcop2="nullnullnullnull";
for (i=0;i<9;i++)
{
cortos_printf("value of intial string for copy %s \n", strcop2);
a =a64strcpy( strcop2,(strcop+i) );
a =strcpy( str,(strcop+i) );
cortos_printf("value of string after  copy %s \n", strcop2);

}

//-----string copy n bytes-------

char *strncop ="vlsivlsivlsivlsivlsivlsivlsivlsivlsi";
char *strncop2="nullnullnullnullnullnullnullnullnull";
for (i=0;i<9;i++)
{
cortos_printf("value of intial string for n byte copy %s \n", strncop2);

a =a64strncpy( strncop2,(strcop+i),30);
cortos_printf("value of string after n byte copy %s \n", strncop2);

}


/*

_Alignas(8) char *s9  = "VVVvvvVVVVVVVVVVvvvvvvvvVVVvVVvvVVVVVVVVVVVVVVVVVVVVVVvv";

_Alignas(8) char *s0  = "vVvVvVvVvvvvvvVVVVVVVVvVVVVvvvvvvvvvvvvvvvvvVVVVVVVVVVVV";

//test aligns source 
for (i=0;i<9;i++)
{
cortos_printf("string s0 is %s \n",s0);
cortos_printf("string s9 is %s \n",(s9+i));
//_Alignas(8) char s0[50]  = "nullnullnullnullnullnyllnyll";
a = strcasecmp(s0,(s9+i));

cortos_printf("value of a is %d \n", a);
b = a64strcasecmp(s0,(s9+i));
cortos_printf("test printi value of a is  = %d \n", b);
for (j=0;j<60;j++)
{
cortos_printf("value of string n is %x and j is %d \n", *(s0+j),j);
}
cortos_printf("test print again \n");
*/
	}
