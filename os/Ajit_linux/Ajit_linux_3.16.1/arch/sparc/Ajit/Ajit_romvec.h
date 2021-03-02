//Ajit_romvec.h

//generate a romvec to replace the one provided by bootloader

#ifndef AJIT_ROMVEC_H
#define AJIT_ROMVEC_H

#include <asm/openprom.h>
#include "Ajit_nodeops.h"


//generate a version 0 Romvec		
void update_Ajit_romvec(struct linux_romvec* rp) 
{
						
	//prom nodeops to navigate the romvec structure
	void* fdt_blob_address = rp->pv_nodeops;
	set_fdt_blob_addr(fdt_blob_address); 
	rp->pv_nodeops = get_Ajit_nodeops(); // implemented using fdt routines
}


#endif

