.section .text.ajitstart
.global _start;
_start:
	call ajit_main
	nop

	ta 0
