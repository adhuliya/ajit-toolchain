	.file	"main.c"
	.section	.text.startup,"ax",@progbits
	.align 4
	.global main
	.type	main, #function
	.proc	04
main:
	save	%sp, -96, %sp
	call	ajit_serial_init, 0
	 mov	0, %i0
	call	acquisition, 0
	 nop
	jmp	%i7+8
	 restore
	.size	main, .-main
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
