/* Default linker script, for normal executables */
OUTPUT_FORMAT("a.out-sunos-big", "a.out-sunos-big",
	      "a.out-sunos-big")
OUTPUT_ARCH(sparc)
SEARCH_DIR("/lindata/My-work/Professional/iitb/development/ajit-branch/ajit-toolchain/src/development/amv-ajit-code/trial-install/sparc-install/sparc-sun-sunos4/lib");
PROVIDE (__stack = 0);
SECTIONS
{
  . = 0x2020;
  .text :
  {
    CREATE_OBJECT_SYMBOLS
    *(.text)
    /* The next six sections are for SunOS dynamic linking.  The order
       is important.  */
    *(.dynrel)
    *(.hash)
    *(.dynsym)
    *(.dynstr)
    *(.rules)
    *(.need)
    _etext = .;
    __etext = .;
  }
  . = ALIGN(0x2000);
  .data :
  {
    /* The first three sections are for SunOS dynamic linking.  */
    *(.dynamic)
    *(.got)
    *(.plt)
    *(.data)
    *(.linux-dynamic) /* For Linux dynamic linking.  */
    CONSTRUCTORS
    _edata  =  .;
    __edata  =  .;
  }
  .bss :
  {
    __bss_start = .;
   *(.bss)
   *(COMMON)
   . = ALIGN(8);
   _end = . ;
   __end = . ;
  }
}
