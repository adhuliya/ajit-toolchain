#include <stdio.h>
#include <stdint.h>

#define _BITCAST_(Type,val) *((Type*)&val)

int main()
{
	char c;
	uint32_t fh = 0;
	uint64_t dh = 0;

	printf("Enter f or d\n");
	scanf("%c",&c);
	printf("Enter the hex pattern:\n");
	if(c=='f')
		scanf("%x",&fh);
	else
		scanf("%llx",&dh);
		
	float f = _BITCAST_(float,fh);
	double d = _BITCAST_(double,dh);
	
	if(c=='f')
		printf("The float no: is %0.10f\n",f);
	else
		printf("The double no: is %0.10lf\n",d);
		
}
