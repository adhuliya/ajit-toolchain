        .file           "."
        .section        ".text"
        .align 4
        .psize          0,200
        .global main
        .type   main, #function
main:
        nop
	 fbl 0x00000000
	 fbl 0x003FFFFF
	 fbl 0x00000000
	 fbl 0x003FFFFF
	 fbl,a 0x00000000
	 fbl,a 0x003FFFFF
	 fbl,a 0x00000000
	 fbl,a 0x003FFFFF
        nop
        .ident  "GCC: (Buildroot 2014.08) 4.7.4"
        .section  .note.GNU-stack,"",@progbits
