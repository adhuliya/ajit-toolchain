#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<cortos.h>
#include"a64string.h"
int a,b=0;
void main() {

int i,j;

///define aligned strings
_Alignas(8) char *s9  = "vlsivlsivlsivlsivlsivlsi";
_Alignas(8) char s0[50]  = "nullnullnullnullnullnyllnyll";

//loop to check all alignemnts
for (i=0;i<9;i++)
{

cortos_printf("value of src string is %s \n", (s9+i));
a64strcpy(s0, (s9+i));
cortos_printf("value of dest string after copy is %s \n", s0);
}	}
