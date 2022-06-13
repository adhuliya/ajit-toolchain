#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void *core_mark_0() = 0x40020000;
void *core_mark_1() = 0x40040000;

int main_00 ()
{
	*core_mark_0();
	return(1);
}

int main_01 ()
{
	*core_mark_1();
	return(1);
}

