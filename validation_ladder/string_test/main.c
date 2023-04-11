#include<string.h>
#include<stdio.h>
#include"a64string.h"
int a,b=0;
void main() {

char *s1  = "vlsivlsi";
char *s2  = "Vlsivlsi";

 a =  a64strcmp(s1, s2);           //return value should be 32
 cortos_printf("value of a is %d \n",a);

char *s3  = "vlsivlsi";
char *s4  = "Vlsivlsi";
 b =  a64strcasecmp(s3, s4);      //return value should be 0

cortos_printf("value of b is %d \n",b);


char * s5  = "vlsivlsi";
char * s6  = "null"; 
char * ret;

cortos_printf("value of string %s \n", s6);
ret = a64strcpy(s6, s5);

cortos_printf("string copied");

cortos_printf("value of changed string %s \n", s6);

char * s7  = "vlsivlsi";
char s8[20]  = "vlsivlsi";
cortos_printf("value of cat string %s \n", s8);                              
ret = a64strcat(s8, s7);
        
cortos_printf("value of changed cat string %s \n", s8);                      


char *s9  = "vlsivlsss";
char *s0  = "";

cortos_printf("value of string n is %s \n", s9);

ret = a64strncpy(s0, s9,5);

cortos_printf("value of string n is %s \n", s0);
}

