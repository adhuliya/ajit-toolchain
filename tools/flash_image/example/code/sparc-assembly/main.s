	.file	"main.c"
	.section	".text"
	.align 4
	.global __enable_serial
	.type	__enable_serial, #function
	.proc	04
__enable_serial:
	save	%sp, -96, %sp
	mov	0, %i0
	call	__ajit_write_serial_control_register__, 0
	 mov	3, %o0
	jmp	%i7+8
	 restore
	.size	__enable_serial, .-__enable_serial
	.align 4
	.global __enable_serial_interrupt
	.type	__enable_serial_interrupt, #function
	.proc	04
__enable_serial_interrupt:
	save	%sp, -96, %sp
	mov	0, %i0
	call	__ajit_write_serial_control_register__, 0
	 mov	7, %o0
	jmp	%i7+8
	 restore
	.size	__enable_serial_interrupt, .-__enable_serial_interrupt
	.align 4
	.global __ajit_serial_getline__
	.type	__ajit_serial_getline__, #function
	.proc	04
__ajit_serial_getline__:
	save	%sp, -96, %sp
	mov	0, %i5
.L12:
	call	__ajit_serial_getchar__, 0
	 nop
	cmp	%o0, 0
	be	.L12
	 cmp	%o0, 10
	be	.L5
	 nop
	stb	%o0, [%i0+%i5]
	b	.L12
	 add	%i5, 1, %i5
.L5:
	jmp	%i7+8
	 restore %g0, %i5, %o0
	.size	__ajit_serial_getline__, .-__ajit_serial_getline__
	.align 4
	.global __ajit_dummy_read__
	.type	__ajit_dummy_read__, #function
	.proc	020
__ajit_dummy_read__:
	save	%sp, -96, %sp
.L15:
	call	__ajit_serial_getchar__, 0
	 nop
	cmp	%o0, 0
	be	.L15
	 nop
	jmp	%i7+8
	 restore
	.size	__ajit_dummy_read__, .-__ajit_dummy_read__
	.align 4
	.global __ajit_getchar__
	.type	__ajit_getchar__, #function
	.proc	04
__ajit_getchar__:
	save	%sp, -96, %sp
.L21:
	call	__ajit_serial_getchar__, 0
	 nop
	cmp	%o0, 0
	be	.L21
	 mov	%o0, %i0
	jmp	%i7+8
	 restore
	.size	__ajit_getchar__, .-__ajit_getchar__
	.align 4
	.global __serial_isr
	.type	__serial_isr, #function
	.proc	020
__serial_isr:
	sethi	%hi(-53248), %g1
	mov	0, %g2
#APP
! 81 "main.c" 1
	sta %g2, [%g1] 32
	
! 0 "" 2
#NO_APP
	or	%g1, 544, %g1
#APP
! 87 "main.c" 1
	lduba [%g1] 32, %g1
	
! 0 "" 2
#NO_APP
	cmp	%g1, 113
	be	.L41
	 sethi	%hi(k), %g3
	ld	[%g3+%lo(k)], %g2
	cmp	%g2, 9
	be	.L28
	 cmp	%g1, 10
	be	.L28
	 cmp	%g1, 0
	be	.L43
	 add	%g2, 1, %g4
.L42:
	st	%g4, [%g3+%lo(k)]
	sethi	%hi(expr), %g3
	or	%g3, %lo(expr), %g3
	stb	%g1, [%g3+%g2]
.L43:
	jmp	%o7+8
	 nop
.L41:
	mov	1, %g3
	sethi	%hi(exit_flag), %g2
	st	%g3, [%g2+%lo(exit_flag)]
	sethi	%hi(k), %g3
	ld	[%g3+%lo(k)], %g2
	cmp	%g2, 9
	bne	.L42
	 add	%g2, 1, %g4
.L28:
	sethi	%hi(expr), %g1
	or	%g1, %lo(expr), %g1
	st	%g0, [%g3+%lo(k)]
	stb	%g0, [%g1+%g2]
	mov	1, %g2
	sethi	%hi(flag_line_over), %g1
	jmp	%o7+8
	 st	%g2, [%g1+%lo(flag_line_over)]
	.size	__serial_isr, .-__serial_isr
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.asciz	"Wrong operator\n"
	.section	".text"
	.align 4
	.global calculate
	.type	calculate, #function
	.proc	04
calculate:
	save	%sp, -96, %sp
	sethi	%hi(.LC0), %i3
	ldub	[%i0], %g1
	add	%i0, 1, %i5
	sll	%g1, 24, %o1
	cmp	%o1, 0
	bne	.L56
	 or	%i3, %lo(.LC0), %i3
	b,a	.L55
.L58:
	mov	%i1, %o0
	call	push, 0
	 add	%o1, -48, %o1
	mov	%i5, %i0
.L60:
	add	%i5, 1, %i5
	ldub	[%i5-1], %g1
	sll	%g1, 24, %o1
	cmp	%o1, 0
	be	.L55
	 nop
.L56:
	add	%g1, -48, %g1
.L61:
	and	%g1, 0xff, %g1
	cmp	%g1, 9
	bleu	.L58
	 sra	%o1, 24, %o1
	call	pop, 0
	 mov	%i1, %o0
	mov	%o0, %i4
	call	pop, 0
	 mov	%i1, %o0
	ldsb	[%i0], %g1
	cmp	%g1, 43
	be	.L50
	 mov	%o0, %o1
	cmp	%g1, 43
	bg	.L53
	 cmp	%g1, 45
	cmp	%g1, 42
	be	.L59
	 mov	%i1, %o0
.L48:
	call	ee_printf, 0
	 mov	%i3, %o0
	mov	%i5, %i0
	add	%i5, 1, %i5
	ldub	[%i5-1], %g1
	sll	%g1, 24, %o1
	cmp	%o1, 0
	bne	.L61
	 add	%g1, -48, %g1
.L55:
	call	pop, 0
	 restore %g0, %i1, %o0
.L53:
	be	.L51
	 cmp	%g1, 47
	bne	.L48
	 nop
	sra	%o1, 31, %g1
	wr	%g1, 0, %y
	nop
	nop
	nop
	sdiv	%o1, %i4, %o1
	call	push, 0
	 mov	%i1, %o0
	b	.L60
	 mov	%i5, %i0
.L51:
	mov	%i1, %o0
	call	push, 0
	 sub	%o1, %i4, %o1
	b	.L60
	 mov	%i5, %i0
.L50:
	mov	%i1, %o0
	call	push, 0
	 add	%o1, %i4, %o1
	b	.L60
	 mov	%i5, %i0
.L59:
	call	push, 0
	 smul	%o1, %i4, %o1
	b	.L60
	 mov	%i5, %i0
	.size	calculate, .-calculate
	.section	.rodata.str1.8
	.align 8
.LC1:
	.asciz	"?? : \n"
	.align 8
.LC2:
	.asciz	"\nR: %d\n"
	.align 8
.LC3:
	.asciz	"?? :\n "
	.align 8
.LC4:
	.asciz	"\nBYE(%d)\n"
	.section	.text.startup,"ax",@progbits
	.align 4
	.global main
	.type	main, #function
	.proc	04
main:
	save	%sp, -144, %sp
	call	initStack, 0
	 add	%fp, -44, %o0
	call	__enable_serial_interrupt, 0
	 sethi	%hi(flag_line_over), %i4
	sethi	%hi(.LC1), %o0
	or	%o0, %lo(.LC1), %o0
	sethi	%hi(exit_flag), %i0
	sethi	%hi(expr), %i1
	sethi	%hi(.LC2), %l1
	sethi	%hi(.LC3), %l0
	mov	1, %i2
	sethi	%hi(-53248), %i5
	call	ee_printf, 0
	 mov	0, %i3
	or	%i4, %lo(flag_line_over), %i4
	or	%i0, %lo(exit_flag), %i0
	or	%i1, %lo(expr), %i1
	or	%l1, %lo(.LC2), %l1
	or	%l0, %lo(.LC3), %l0
.L68:
#APP
! 179 "main.c" 1
	sta %i2, [%i5] 32
	
! 0 "" 2
#NO_APP
	call	add_delay, 0
	 nop
#APP
! 183 "main.c" 1
	sta %i3, [%i5] 32
	
! 0 "" 2
#NO_APP
	ld	[%i4], %g1
	cmp	%g1, 1
	bne	.L68
	 mov	%i1, %o0
	st	%g0, [%i4]
	ld	[%i0], %g1
	cmp	%g1, 0
	bne	.L64
	 add	%fp, -44, %o1
	call	calculate, 0
	 nop
	mov	%o0, %o1
	call	ee_printf, 0
	 mov	%l1, %o0
	call	ee_printf, 0
	 mov	%l0, %o0
	b,a	.L68
.L64:
	mov	0, %i0
	mov	%g1, %o1
	sethi	%hi(.LC4), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC4), %o0
	jmp	%i7+8
	 restore
	.size	main, .-main
	.global exit_flag
	.section	".bss"
	.align 4
	.type	exit_flag, #object
	.size	exit_flag, 4
exit_flag:
	.skip	4
	.global flag_line_over
	.align 4
	.type	flag_line_over, #object
	.size	flag_line_over, 4
flag_line_over:
	.skip	4
	.global k
	.align 4
	.type	k, #object
	.size	k, 4
k:
	.skip	4
	.common	expr,10,8
	.ident	"GCC: (Buildroot 2014.08-gde406ae-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
