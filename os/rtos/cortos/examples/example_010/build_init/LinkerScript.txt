/* linker script for a program (0,0) (= a process) */

/*========================================================*/
/*                                                        */
/* Sample Linker script for Sparc simulator 	          */
/*                                                        */
/*========================================================*/

ENTRY(_start)
__DYNAMIC = 0;
SECTIONS
{
  . = 0x00000000; /* (0,0) starts at zero.*/
  .text ALIGN(4) : {
    KEEP(*(.text.ajitstart))  /* NOTE: in file `init.s` */
    KEEP(*(.text.ajitstart.cortosloop))  /* NOTE: in file `init.s` */
    *(.text)
    *(.text.*)
    /* KEEP(*(.text.pagetablesetup)) */ /* NOTE: not needed */
    KEEP(*(.text.traphandlers))  /* NOTE: in file `trap_handlers.s` */
    KEEP(*(.text.traptablebase))  /* NOTE: in file `trap_handlers.s` */
  }

  .rodata ALIGN(4) : { * (.rodata) * (.rodata.*) }
  .data   ALIGN(4) : { * (.data) * (.data.*) *(.bss)}
}
