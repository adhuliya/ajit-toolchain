#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

int  ok_flag[4] = {0,0,0,0};

int f0=0;
int f1=0;
int f2=0;
int f3=0;


int march_test(int CPUID);

void main_0 () 
{

	int err = march_test(0);
	ok_flag[0] = !err;

	f0 = 1;

}

void main_1 () 
{
	int err = march_test(1);
	ok_flag[1] = !err;

	f1 = 1;
}

void main_2 () 
{
	int err = march_test(2);
	ok_flag[2] = !err;

	f2 = 1;
}

void main_3 () 
{
	int err = march_test(3);
	ok_flag[3] = !err;

	f3 = 1;
}

