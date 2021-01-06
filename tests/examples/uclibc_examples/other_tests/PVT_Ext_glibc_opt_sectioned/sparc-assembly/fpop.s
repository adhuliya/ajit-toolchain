	.file	"fpop.c"
	.section	.text.sqrt_ajit_asm_double,"ax",@progbits
	.align 4
	.global sqrt_ajit_asm_double
	.type	sqrt_ajit_asm_double, #function
	.proc	020
sqrt_ajit_asm_double:
#APP
! 14 "fpop.c" 1
	ldd [%o0], %f0 
! 0 "" 2
! 15 "fpop.c" 1
	fsqrtd %f0, %f2 
! 0 "" 2
! 16 "fpop.c" 1
	std %f2, [%o1]
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 nop
	.size	sqrt_ajit_asm_double, .-sqrt_ajit_asm_double
	.section	.text.sqrt_ajit_asm_single,"ax",@progbits
	.align 4
	.global sqrt_ajit_asm_single
	.type	sqrt_ajit_asm_single, #function
	.proc	020
sqrt_ajit_asm_single:
#APP
! 23 "fpop.c" 1
	ld [%o0], %f0 
! 0 "" 2
! 24 "fpop.c" 1
	fsqrts %f0, %f2 
! 0 "" 2
! 25 "fpop.c" 1
	st %f2, [%o1]
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 nop
	.size	sqrt_ajit_asm_single, .-sqrt_ajit_asm_single
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
