        .file           "."
        .section        ".text"
        .align 4
        .psize          0,200
        .global main
        .type   main, #function
main:
        nop
	 fblg 0x00000000
	 fblg 0x003FFFFF
	 fblg 0x00000000
	 fblg 0x003FFFFF
	 fblg,a 0x00000000
	 fblg,a 0x003FFFFF
	 fblg,a 0x00000000
	 fblg,a 0x003FFFFF
        nop
        .ident  "GCC: (Buildroot 2014.08) 4.7.4"
        .section  .note.GNU-stack,"",@progbits
