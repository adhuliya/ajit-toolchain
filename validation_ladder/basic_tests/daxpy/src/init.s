.section .text.ajitstart
.global _start
_start:
	mov %g0, %sp
        sub %sp, 64, %sp
	call ajit_main
	nop
	ta 0
