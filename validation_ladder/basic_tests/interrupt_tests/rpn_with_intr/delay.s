	.file	"delay.c"
	.section	".text"
	.align 4
	.global add_delay
	.type	add_delay, #function
	.proc	020
add_delay:
	cmp	%o0, 0
	ble	.L7
	 nop
.L4:
#APP
! 7 "delay.c" 1
	nop;
! 0 "" 2
#NO_APP
	addcc	%o0, -1, %o0
	bne	.L4
	 nop
.L7:
	jmp	%o7+8
	 nop
	.size	add_delay, .-add_delay
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
