        .file           "."
        .section        ".text"
        .align 4
        .psize          0,200
        .global main
        .type   main, #function
main:
        nop
	 cb123 0x00000000
	 cb123 0x003FFFFF
	 cb123 0x00000000
	 cb123 0x003FFFFF
	 cb123,a 0x00000000
	 cb123,a 0x003FFFFF
	 cb123,a 0x00000000
	 cb123,a 0x003FFFFF
        nop
        .ident  "GCC: (Buildroot 2014.08) 4.7.4"
        .section  .note.GNU-stack,"",@progbits
