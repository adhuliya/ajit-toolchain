	.file	"delay.c"
	.section	".text"
	.align 4
	.global add_delay
	.type	add_delay, #function
	.proc	020
add_delay:
#APP
! 13 "delay.c" 1
	nop;
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 nop
	.size	add_delay, .-add_delay
	.global run_forever
	.section	".data"
	.align 4
	.type	run_forever, #object
	.size	run_forever, 4
run_forever:
	.long	1
	.ident	"GCC: (Buildroot 2014.08-gde406ae-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
