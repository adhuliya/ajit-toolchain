#include <stdio.h>
#include <stdint.h>

#define _BITCAST_(Type,val) *((Type*)&val)

int main()
{
	char c;
	float f = 0;
	double d = 0;

	printf("Enter f or d\n");
	scanf("%c",&c);
	printf("Enter the no:\n");
	if(c=='f')
		scanf("%f",&f);
	else
		scanf("%lf",&d);
		
	uint32_t fh = _BITCAST_(uint32_t,f);
	uint64_t dh = _BITCAST_(uint64_t,d);
	
	if(c=='f')
		printf("The bit pattern is %x\n",fh);
	else
		printf("The bit pattern is %llx\n",dh);
		
}
