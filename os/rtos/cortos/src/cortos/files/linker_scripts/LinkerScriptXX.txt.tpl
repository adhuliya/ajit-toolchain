/* linker script for a program (except (0,0)) (= a process) */

/*========================================================*/
/*                                                        */
/* Sample Linker script for Sparc simulator 	          */
/*                                                        */
/*========================================================*/

% setdefault("startAddress", "0x00000000")

ENTRY(_start)
__DYNAMIC = 0;
SECTIONS
{
  . = {{startAddress}}; /* . = 0x00000000; */
  .text ALIGN(4) : {
    KEEP(*(.text.ajitstart.cortosloop))  /* NOTE: in file `init.s` */
    *(.text)
    *(.text.*)
  }

  /* . = 0x40000000; */ /* . = {ajitStartDataAddrHex}; */
  .rodata ALIGN(4) : { * (.rodata) * (.rodata.*) }
  .data   ALIGN(4) : { * (.data) * (.data.*) *(.bss)}
}
