        .file           "."
        .section        ".text"
        .align 4
        .psize          0,200
        .global main
        .type   main, #function
main:
        nop
	 bgu 0x00000000
	 bgu 0x003FFFFF
	 bgu 0x00000000
	 bgu 0x003FFFFF
	 bgu,a 0x00000000
	 bgu,a 0x003FFFFF
	 bgu,a 0x00000000
	 bgu,a 0x003FFFFF
        nop
        .ident  "GCC: (Buildroot 2014.08) 4.7.4"
        .section  .note.GNU-stack,"",@progbits
