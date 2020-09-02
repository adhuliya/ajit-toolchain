//Ajit_romvec.h
//A romvec is a structure that the bootloader uses
//to pass hardware information 
//and a basic putchar routine to the linux kernel

#ifndef AJIT_ROMVEC_H
#define AJIT_ROMVEC_H

#include "openprom.h"
#include "Ajit_putchar.h"
#include "Ajit_memory_map.h"

//start adddress of the device tree blob
extern void* dt_blob_start; 


#define add_kernel_offset(x) ((void*)((uint32_t)(x) + (uint32_t)(KERNEL_OFFSET)))

#define NULL 0
void * null_ptr = NULL;
#define NULL_PTR (null_ptr)
#define NULL_PPTR (add_kernel_offset(&null_ptr))


struct linux_romvec Ajit_romvec;
struct linux_romvec* Ajit_romvec_ptr = add_kernel_offset(&Ajit_romvec);

//available memory
struct linux_mlist_v0 totphys = {NULL, RAM_START, RAM_NUM_BYTES};
struct linux_mlist_v0 avail = {NULL, RAM_START, RAM_NUM_BYTES};
struct linux_mlist_v0 *totphys_p = add_kernel_offset(&totphys);
struct linux_mlist_v0 *avail_p = add_kernel_offset(&avail);

//empty  fields in the romvec
//struct linux_dev_v0_funcs EMPTY_v0devops = {NULL,NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
//struct linux_dev_v2_funcs EMPTY_v2devops = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL} ;
//struct linux_bootargs_v2 EMPTY_v2bootargs= {NULL, NULL, NULL, NULL};
char AJIT_PROMDEV_TTYA = 1; //a constant to be placed into romvec
static void (*EMPTY_sync_hook)(void)=NULL;



//**HACK**
//In the original kernel, the bootloader passes "nodeops"
//to the kernel. The nodeops consist of a 
//tree data structure containing hardware info 
//and routines to traverse it.
//
//In the Ajit system, we pass just the tree data structure.
//The data structure is implemented in a standard format, known as
//a flattened-device-tree (fdt).
///We need to pass a pointer to the device tree blob to the kernel.
//The kernel then itself implements the nodeops routines 
//to traverse this device tree blob.
//
//So in the romvec, we pass a pointer to the blob where 
//originally the nodeops were passed. The kernel code
//first reads this pointer, stores it, and then updates the
//nodeops field.
#define store_pointer_to_device_tree_blob_in_romvec() {Ajit_romvec.pv_nodeops = add_kernel_offset(& dt_blob_start);}


//generate a version 0 Romvec		
struct linux_romvec * get_Ajit_romvec() 
{
						
	//romvec version information		
	Ajit_romvec.pv_magic_cookie	    =0;	
	Ajit_romvec.pv_romvers              =0;	
	Ajit_romvec.pv_plugin_revision      =0;	
	Ajit_romvec.pv_printrev             =0; 

	//information about available memory
	Ajit_romvec.pv_v0mem.v0_totphys		=add_kernel_offset(&totphys_p);
	Ajit_romvec.pv_v0mem.v0_prommap		=NULL_PPTR;
	Ajit_romvec.pv_v0mem.v0_available	=add_kernel_offset(&avail_p);

	
	//parts that can be set to NULL (not used)
	Ajit_romvec.pv_bootstr=NULL;
	Ajit_romvec.pv_getchar=NULL;
	Ajit_romvec.pv_putchar=NULL;
	Ajit_romvec.pv_nbgetchar=NULL;
	Ajit_romvec.pv_putstr   =NULL;
	Ajit_romvec.pv_reboot   =NULL;
	Ajit_romvec.pv_printf   =NULL;
	Ajit_romvec.pv_abort    =NULL;
	Ajit_romvec.pv_ticks    =NULL;
	Ajit_romvec.pv_halt     =NULL;
	Ajit_romvec.pv_enaddr   =NULL;
	Ajit_romvec.pv_setctxt  =NULL;
	Ajit_romvec.pv_fortheval.v0_eval  = NULL;
	Ajit_romvec.pv_fortheval.v2_eval  = NULL;
	Ajit_romvec.pv_stdin = NULL;
	Ajit_romvec.pv_v0bootargs = NULL_PTR;
	//Ajit_romvec.pv_v2bootargs = EMPTY_v2bootargs;
	//Ajit_romvec.pv_v0devops   = EMPTY_v0devops;
	//Ajit_romvec.pv_v2devops   = EMPTY_v2devops;
	Ajit_romvec.pv_synchook   = add_kernel_offset(&EMPTY_sync_hook); // empty function 
	
	
	//these are needed:
	Ajit_romvec.pv_stdout= add_kernel_offset(&AJIT_PROMDEV_TTYA); //just a constant
	Ajit_romvec.pv_nbputchar=add_kernel_offset(&pv_nbputchar); //defined in Ajit_putchar.h
	
	//Pass a pointer to the device tree blob.
	//The nodeops field later gets updated in the kernel.
	store_pointer_to_device_tree_blob_in_romvec();
	
	return &Ajit_romvec;

}

#endif

