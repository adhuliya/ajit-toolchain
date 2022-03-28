/*========================================================*/
/*                                                        */
/* Linker script for Ajit Sparc      	                  */
/*                                                        */
/*========================================================*/

ENTRY(_start)
__DYNAMIC = 0;
SECTIONS
{
  . = {{ hex(confObj.software.program.getTextRegionStartAddr()) }};
  .text ALIGN(8) : {
    KEEP(*(.text.ajitstart))  /* NOTE: in file `init_00.s` */
    *(.text)
    *(.text.*)
    KEEP(*(.text.pagetablesetup)) /* NOTE: not needed */
    KEEP(*(.text.traphandlers))  /* NOTE: in file `trap_handlers.s` */
    KEEP(*(.text.traptablebase))  /* NOTE: in file `trap_handlers.s` */
  }

  . = {{ hex(confObj.software.program.getDataRegionStartAddr()) }};
  .rodata ALIGN(8) : { * (.rodata) * (.rodata.*) }
  .data   ALIGN(8) : { * (.data) * (.data.*)}

  . = {{ hex(confObj.software.program.getBssRegionStartAddr()) }};
  .bss   ALIGN(8) : { * (.bss) }
}
