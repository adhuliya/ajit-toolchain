#include<string.h>
#include<stdio.h>
#include"a64string.h"
int a,b,c =0;
void main() {



///string length - caluclates length of string till \0.

char *s10 = "vlsivlsivlsii";

cortos_printf("strlen \n");
c = a64strlen(s10);
cortos_printf("string length is %d \n", c);


///string comapre - output is 0 if same, else difference in value of the different byte
char *s1  = "vlsivlsi";
char *s2  = "Vlsivlsi";

cortos_printf("strcmp \n");
 a =  a64strcmp(s1, s2);           //return value should be 32
 cortos_printf("value of a is %d \n",a);




///string case comapre - output is 0 if same, else difference in value of the different byte. Bytes of different cases are treated as equal
char *s3  = "vlsivlsi";
char *s4  = "Vlsivlsi";


cortos_printf("strcasecmp \n");
 b =  a64strcasecmp(s3, s4);      //return value should be 0

cortos_printf("value of b is %d \n",b);


///string copy - copy s5 into s6

char * s5  = "vlsivls";
char * s6  = "null"; 
char * ret;

cortos_printf("strcpy \n");
cortos_printf("inital value of string %s \n", s6);

a64strcpy(s6, s5);

cortos_printf("value of string  after copy %s \n", s6);

///string concatenate - concatenate source string to destination string

char * s7  = "vlsivlsi";
char s8[20]  = "vlsivlsi";

cortos_printf("strcat \n");
cortos_printf("initial vlaue of string %s \n", s8);                              

ret = a64strcat(s8, s7);
        
cortos_printf("value of string after concatenation  %s \n", s8);                      


///string copy n bhytes - copies source string into destination string for n bytes

char *s9  = "vlsivlsss";
char *s0  = "";

cortos_printf("strncpy \n");
cortos_printf("inital value of string is %s \n", s9);

ret = a64strncpy(s0, s9,5);

cortos_printf("value of string copied for n bytes is %s \n", s0);


}
