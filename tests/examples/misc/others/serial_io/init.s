.global main
main:
_start:
	mov %g0, %sp
	call ajit_main
	nop
