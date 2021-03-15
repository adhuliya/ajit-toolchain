        .file           "."
        .section        ".text"
        .align 4
        .psize          0,200
        .global main
        .type   main, #function
main:
        nop
	 bcc 0x00000000
	 bcc 0x003FFFFF
	 bcc 0x00000000
	 bcc 0x003FFFFF
	 bcc,a 0x00000000
	 bcc,a 0x003FFFFF
	 bcc,a 0x00000000
	 bcc,a 0x003FFFFF
        nop
        .ident  "GCC: (Buildroot 2014.08) 4.7.4"
        .section  .note.GNU-stack,"",@progbits
