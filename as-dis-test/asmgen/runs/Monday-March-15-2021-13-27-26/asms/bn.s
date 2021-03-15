        .file           "."
        .section        ".text"
        .align 4
        .psize          0,200
        .global main
        .type   main, #function
main:
        nop
	 bn 0x00000000
	 bn 0x003FFFFF
	 bn 0x00000000
	 bn 0x003FFFFF
	 bn,a 0x00000000
	 bn,a 0x003FFFFF
	 bn,a 0x00000000
	 bn,a 0x003FFFFF
        nop
        .ident  "GCC: (Buildroot 2014.08) 4.7.4"
        .section  .note.GNU-stack,"",@progbits
