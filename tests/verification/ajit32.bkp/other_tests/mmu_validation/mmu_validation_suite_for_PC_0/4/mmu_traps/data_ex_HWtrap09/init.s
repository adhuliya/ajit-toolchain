.section .text.main
.global main
main:
_start:
	mov %g0, %fp
	sub %fp, 96, %sp

	set TRAP_TABLE, %l0
	mov %l0, %tbr

	call ajit_main
	nop
