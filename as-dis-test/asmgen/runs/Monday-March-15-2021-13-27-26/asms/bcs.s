        .file           "."
        .section        ".text"
        .align 4
        .psize          0,200
        .global main
        .type   main, #function
main:
        nop
	 bcs 0x00000000
	 bcs 0x003FFFFF
	 bcs 0x00000000
	 bcs 0x003FFFFF
	 bcs,a 0x00000000
	 bcs,a 0x003FFFFF
	 bcs,a 0x00000000
	 bcs,a 0x003FFFFF
        nop
        .ident  "GCC: (Buildroot 2014.08) 4.7.4"
        .section  .note.GNU-stack,"",@progbits
