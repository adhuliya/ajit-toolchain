#include <stdint.h>
#include <stdarg.h>
#include <cortos.h>
#include <ajit_access_routines.h>
#include <ajit_generic_sys_calls.h>

#define VECTOR_SIZE   8

typedef struct Args__ {
	uint32_t address;
	uint32_t value;
} Args;
Args my_args;

void my_sys_call_trap_handler (void (*fn) (Args*), Args* my_args);

void setup_serial()
{
        __ajit_serial_configure_via_vmap__   (1, 0, 0);
}

// arg1 is function pointer, arg2 is function argument
void __my_sys_call_fn(Args* args)
{
	args->value = __ajit_load_word_from_physical_address__((uint64_t) args->address);
	cortos_printf("in __my_sys_call_fn 0x%x -> 0x%x\n", args->address, args->value);
}

// The trap handler.
void my_sys_call_trap_handler (void  (*fn) (Args*), Args* my_args)
{
	(*fn) ((Args*) my_args);
}

//
//
// This is the function you use to read a physical memory location 
//
void my_sys_call (void* fn, Args* my_args)
{
	// create a trap... will jump to
	// vectored trap handler.
	__AJIT_SW_TRAP(15);
}

void read_phy_mem()
{
	int I;
	for(I = 0; I < VECTOR_SIZE; I++)
	{
		uint32_t v;

		my_args.address = 0x40000000 + (I*4);
		my_args.value = 0x0;

		// set up the sys-call.
		my_sys_call(__my_sys_call_fn, &my_args);
	}
}

void cortos_printf_wrap(uint32_t fmt, uint32_t args, uint32_t ret_ptr)
{
	int ret_val = cortos_vprintf ((char*)fmt, (va_list)args);

	// return value here.
	*((int*) ret_ptr) = ret_val;
}


int cortos_uprintf_sys_call(char* fmt, va_list args, int* ret_val)
{
	__AJIT_SW_TRAP(14);
	return(*ret_val);
}


// user mode cortos-printf..
int cortos_uprintf (char* fmt, ...)
{
	int ret_val = 0;

	va_list args;
  	va_start(args, fmt);

	// generate trap and call cortos_vprintf
	// via wrapper.
	cortos_uprintf_sys_call (fmt, args, &ret_val);
	
  	va_end(args);


	return(ret_val);
}


int main()
{
	setup_serial();

	// Go to user mode.
	uint32_t psr;
	__AJIT_GET_PSR (psr);
	psr = (psr & (~(1 << 7)));
	__AJIT_SET_PSR (psr);

	int n = cortos_uprintf("User mode PSR = 0x%x\n", psr);
	cortos_uprintf("chars printed = %d.\n", n);

	// physical memory read..  this is a system
	// call which uses a software trap.
	read_phy_mem();

	uint32_t asr29 = ajit_sys_read_asr (29);
	n = cortos_uprintf("ASR29 = 0x%x\n", asr29);
	cortos_uprintf("chars printed = %d.\n", n);

	uint32_t asr28 = ajit_sys_read_asr (28);
	n = cortos_uprintf("ASR28 = 0x%x\n", asr28);
	cortos_uprintf("chars printed = %d.\n", n);
	
	
	// ta 17 and set psr S=1, ET=1.
	ajit_sys_go_to_supervisor_mode(1);
	

	__AJIT_GET_PSR (psr);
	n = cortos_printf("Supervisor mode PSR = 0x%x\n", psr);
	cortos_uprintf("chars printed = %d.\n", n);

	// goto user mode.
	__AJIT_GET_PSR (psr);
	psr = (psr & (~(1 << 7)));
	__AJIT_SET_PSR (psr);

	n = cortos_uprintf("User mode PSR = 0x%x\n", psr);
	cortos_uprintf("chars printed = %d.\n", n);

	return(0);
}
