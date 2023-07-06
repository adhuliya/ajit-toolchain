#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<cortos.h>
#include<math.h>
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
 int r =0;
int s = 9;
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
int n,j;
char str[3000] ="v";
//----string length-------
for (n=11;n<12;n++)
{
int len = pow(2,n);
char strl[2050] = "";
int p;
for (p=0;p<len;p++)
{
strcat(strl,str);
}
//cortos_printf("print string - %s \n", strl);
j = strlen(strl);

cortos_printf("LENGTH IS %d \n",j); 
j=0;

for (i=r;i<9;i++)
{
//cortos_printf("string length is %d \n",a);

uint64_t t0 = cortos_get_clock_time();
a = strlen(strl+i);
uint64_t t1 = cortos_get_clock_time();
b = a64strlen(strl+i);
uint64_t t2 = cortos_get_clock_time();


uint32_t t00 = (t1-t0) & (0xffffffff);
uint32_t t01 = (t2-t1) & (0xffffffff);

//cortos_printf ("string length is = %d  and %d\n", a,b);
cortos_printf ("len i=%d 32 =  %d , 64 = %d \n",i, t00,t01);
//cortos_printf ("i=%d \n",i);

if (a!=b)
{
        cortos_printf("error in strlen at i = %d and strlen = %d, a64strlen= %d \n", i,a,b);
        
}
}

//-----string concatenate-------
char strcon2[2050]  = "";

for (p=0;p<len;p++)
{
strcat(strcon2,str);
}

for (j=r;j<s;j++)
{
for (i=0;i<9;i++)
{
char strcon0[2080]  = "vlsivlsivlsivlsivlsi";
char strcon1[2080]  = "vlsivlsivlsivlsivlsi";

uint64_t t0 = cortos_get_clock_time();
a = strcat((strcon1+j), (strcon2+i));
uint64_t t1 = cortos_get_clock_time();
a = a64strcat((strcon0+j), (strcon2+i));
uint64_t t2 = cortos_get_clock_time();

uint32_t t00 = (t1-t0) & (0xffffffff);
uint32_t t01 = (t2-t1) & (0xffffffff);

cortos_printf ("strcat at  i =%d,j=%d 32 bit time =  %u , 64 bit time = %u \n",i,j,t00,t01);

a = strcmp(strcon1+j,strcon0+j);

if (a!=0)
{
	cortos_printf("error in strcat , difference of two strings=%d, i =%d,j=%d \n",a,i,j);
}
         
}
}

//------- string compares ----------


char strcomp[2050] = "";
char strcomp2[2050]= "";
for (p=0;p<len;p++)
{
strcat(strcomp,str);
strcat(strcomp2,str);

}

for (j=r;j<s;j++)
{
for (i=0;i<9;i++)
{


uint64_t t0 = cortos_get_clock_time();
b = strcmp ((strcomp+j),(strcomp2+i));
uint64_t t1 = cortos_get_clock_time();
a =  a64strcmp((strcomp+j), (strcomp2 +i));           
uint64_t t2 = cortos_get_clock_time();

uint32_t t00 = (t1-t0) & (0xffffffff);
uint32_t t01 = (t2-t1) & (0xffffffff);

cortos_printf ("strcmp at  i =%d,j=%d 32 bit time =  %u , 64 bit time = %u \n",i,j,t00,t01);

if (a!=b)
{
        cortos_printf("error in strcmp at i = %d , a64strcmp = %d and strcmp = %d\n",i,a,b);
        

}
}
} 
//------string case compare----
char strcase[2050] ="";
char strcase2[2050]="";
for (p=0;p<len;p++)
{
strcat(strcase,str);
strcat(strcase2,str);
}

for (j=r;j<s;j++)
{
for (i=0;i<9;i++)
{

uint64_t t0 = cortos_get_clock_time();
b = strcasecmp((strcase+j),(strcase2+i));
uint64_t t1 = cortos_get_clock_time();
a =  a64strcasecmp((strcase+j), (strcase2+i));      
uint64_t t2 = cortos_get_clock_time();

uint32_t t00 = (t1-t0) & (0xffffffff);
uint32_t t01 = (t2-t1) & (0xffffffff);

cortos_printf ("strcasecmp at  i =%d,j=%d 32 bit time =  %u , 64 bit time = %u \n",i,j, t00,t01);

if (a!=b)
{
        cortos_printf("error in strcasecmp at i = %d and j = %d a64casecmp = %d and casecmp = %d \n",i,j,a,b);
        break;
}
}
}
// --------string copy -------

char strcop[2050] ="";

for (p=0;p<len;p++)
{
strcat(strcop,str);
}

for (j=r;j<s;j++)
{
for (i=0;i<9;i++)
{
char strcop1[2080]  = "vlsivlsivlsivlsivlsi";
char strcop2[2080]  = "vlsivlsivlsivlsivlsi";

uint64_t t0 = cortos_get_clock_time();
a = strcpy((strcop1+j), (strcop+i));
uint64_t t1 = cortos_get_clock_time();
a = a64strcpy((strcop2+j), (strcop+i));
uint64_t t2 = cortos_get_clock_time();

uint32_t t00 = (t1-t0) & (0xffffffff);
uint32_t t01 = (t2-t1) & (0xffffffff);

cortos_printf ("strcpy at i =%d,j=%d 32 bit time =  %u , 64 bit time = %u \n", i,j,t00,t01);

a = strcmp(strcop1+j,strcop2+j);

if (a!=0)
{
        cortos_printf("error in strcpy , a=%d, i =%d,j=%d \n",a,i,j);
}

}
}

//-----string copy n greater than string length-------


for (j=r;j<s;j++)
{
for (i=0;i<9;i++)
{

char strncop1[2080]  = "vlsivlsivlsivlsivlsi";
char strncop2[2080]  = "vlsivlsivlsivlsivlsi";

uint64_t t0 = cortos_get_clock_time();
a = strncpy((strncop1+j), (strcop+i),len+5);
uint64_t t1 = cortos_get_clock_time();
a = a64strncpy((strncop2+j), (strcop+i),len+5);
uint64_t t2 = cortos_get_clock_time();

uint32_t t00 = (t1-t0) & (0xffffffff);
uint32_t t01 = (t2-t1) & (0xffffffff);

cortos_printf ("strncpy at i =%d,j=%d 32 bit time =  %u , 64 bit time = %u \n",i,j, t00,t01);

a = strcmp(strncop1+j,strncop2+j);

if (a!=0)
{
        cortos_printf("error in strncpy-n>len , a=%d, i =%d,j=%d \n",a,i,j);
}

}
}

//-----string copy n less than string length-------
if (len>30)
{
for(j=0;j<9;j++)
{
for (i=0;i<9;i++)
{

char strnlcop1[2080]  = "vlsivlsivlsivlsivlsi";
char strnlcop2[2080]  = "vlsivlsivlsivlsivlsi";

uint64_t t0 = cortos_get_clock_time();
a = strncpy((strnlcop1+j), (strcop+i),len-5);
uint64_t t1 = cortos_get_clock_time();
a = a64strncpy((strnlcop2+j), (strcop+i),len-5);
uint64_t t2 = cortos_get_clock_time();

uint32_t t00 = (t1-t0) & (0xffffffff);
uint32_t t01 = (t2-t1) & (0xffffffff);

cortos_printf ("strncpy at i =%d,j=%d n<len 32 bit time =  %u , 64 bit time = %u \n",i,j,t00,t01);

a = strcmp(strnlcop1+j,strnlcop2+j);

if (a!=0)
{
        cortos_printf("error in strncpy-n<len , a=%d, i =%d,j=%d \n",a,i,j);
}

}
}
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
}	}
