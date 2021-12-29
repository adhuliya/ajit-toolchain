/* linker script for a program (except (0,0)) (= a process) */

/*========================================================*/
/*                                                        */
/* Sample Linker script for Sparc simulator 	          */
/*                                                        */
/*========================================================*/

ENTRY(_start)
__DYNAMIC = 0;
SECTIONS
{
  . = {{ hex(confObj.software.program.getTextRegionStartAddr()) }};
  .text ALIGN(4) : {
    KEEP(*(.text.ajitstart))  /* NOTE: in file `init_00.s` */
    *(.text)
    *(.text.*)
    KEEP(*(.text.pagetablesetup)) /* NOTE: not needed */
    KEEP(*(.text.traphandlers))  /* NOTE: in file `trap_handlers.s` */
    KEEP(*(.text.traptablebase))  /* NOTE: in file `trap_handlers.s` */
  }

  . = {{ hex(confObj.software.program.getDataRegionStartAddr()) }};
  .rodata ALIGN(4) : { * (.rodata) * (.rodata.*) }
  .data   ALIGN(4) : { * (.data) * (.data.*)}

  . = {{ hex(confObj.software.program.getBssRegionStartAddr()) }};
  .bss   ALIGN(4) : { * (.bss) }
}
