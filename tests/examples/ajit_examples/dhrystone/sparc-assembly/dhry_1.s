	.file	"dhry_1.c"
	.section	".text"
	.align 4
	.global put_g1
	.type	put_g1, #function
	.proc	020
put_g1:
	save	%sp, -96, %sp
	st	%i0, [%fp+68]
	ld	[%fp+68], %g1
#APP
! 24 "dhry_1.c" 1
	mov %g1, %g1
	
! 0 "" 2
#NO_APP
	restore
	jmp	%o7+8
	 nop
	.size	put_g1, .-put_g1
	.align 4
	.global put_g2
	.type	put_g2, #function
	.proc	020
put_g2:
	save	%sp, -96, %sp
	st	%i0, [%fp+68]
	ld	[%fp+68], %g1
#APP
! 28 "dhry_1.c" 1
	mov %g1, %g2
	
! 0 "" 2
#NO_APP
	restore
	jmp	%o7+8
	 nop
	.size	put_g2, .-put_g2
	.align 4
	.global put_g3
	.type	put_g3, #function
	.proc	020
put_g3:
	save	%sp, -96, %sp
	st	%i0, [%fp+68]
	ld	[%fp+68], %g1
#APP
! 32 "dhry_1.c" 1
	mov %g1, %g3
	
! 0 "" 2
#NO_APP
	restore
	jmp	%o7+8
	 nop
	.size	put_g3, .-put_g3
	.align 4
	.global put_g4
	.type	put_g4, #function
	.proc	020
put_g4:
	save	%sp, -96, %sp
	st	%i0, [%fp+68]
	ld	[%fp+68], %g1
#APP
! 36 "dhry_1.c" 1
	mov %g1, %g4
	
! 0 "" 2
#NO_APP
	restore
	jmp	%o7+8
	 nop
	.size	put_g4, .-put_g4
	.align 4
	.global put_g5
	.type	put_g5, #function
	.proc	020
put_g5:
	save	%sp, -96, %sp
	st	%i0, [%fp+68]
	ld	[%fp+68], %g1
#APP
! 40 "dhry_1.c" 1
	mov %g1, %g5
	
! 0 "" 2
#NO_APP
	restore
	jmp	%o7+8
	 nop
	.size	put_g5, .-put_g5
	.align 4
	.global halt
	.type	halt, #function
	.proc	020
halt:
	save	%sp, -96, %sp
#APP
! 44 "dhry_1.c" 1
	ta 0; nop; nop;
! 0 "" 2
#NO_APP
	restore
	jmp	%o7+8
	 nop
	.size	halt, .-halt
	.align 4
	.global store_word_mmureg
	.type	store_word_mmureg, #function
	.proc	020
store_word_mmureg:
	save	%sp, -96, %sp
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	ld	[%fp+68], %g1
	ld	[%fp+72], %g2
#APP
! 50 "dhry_1.c" 1
	sta %g1, [%g2] 4
	
! 0 "" 2
#NO_APP
	restore
	jmp	%o7+8
	 nop
	.size	store_word_mmureg, .-store_word_mmureg
	.common	Ptr_Glob,4,4
	.common	Next_Ptr_Glob,4,4
	.common	Int_Glob,4,4
	.common	Bool_Glob,4,4
	.common	Ch_1_Glob,1,1
	.common	Ch_2_Glob,1,1
	.common	Arr_1_Glob,200,4
	.common	Arr_2_Glob,10000,4
	.global Reg
	.section	".bss"
	.align 4
	.type	Reg, #object
	.size	Reg, 4
Reg:
	.skip	4
	.common	time_info,16,4
	.common	Begin_Time,4,4
	.common	End_Time,4,4
	.common	User_Time,4,4
	.common	Microseconds,4,4
	.common	Dhrystones_Per_Second,4,4
	.common	g_rec,48,8
	.common	p_rec,48,8
	.section	".rodata"
	.align 8
.LC0:
	.asciz	"DHRYSTONE PROGRAM, SOME STRING"
	.align 8
.LC1:
	.asciz	"DHRYSTONE PROGRAM, 1'ST STRING"
	.align 8
.LC2:
	.asciz	"DHRYSTONE PROGRAM, 2'ND STRING"
	.align 8
.LC3:
	.asciz	"DHRYSTONE PROGRAM, 3'RD STRING"
	.section	".text"
	.align 4
	.global run_dhrystone
	.type	run_dhrystone, #function
	.proc	020
run_dhrystone:
	save	%sp, -184, %sp
	st	%i0, [%fp+68]
	sethi	%hi(Next_Ptr_Glob), %g1
	or	%g1, %lo(Next_Ptr_Glob), %g1
	sethi	%hi(g_rec), %g2
	or	%g2, %lo(g_rec), %g2
	st	%g2, [%g1]
	sethi	%hi(Ptr_Glob), %g1
	or	%g1, %lo(Ptr_Glob), %g1
	sethi	%hi(p_rec), %g2
	or	%g2, %lo(p_rec), %g2
	st	%g2, [%g1]
	sethi	%hi(Ptr_Glob), %g1
	or	%g1, %lo(Ptr_Glob), %g1
	ld	[%g1], %g1
	sethi	%hi(Next_Ptr_Glob), %g2
	or	%g2, %lo(Next_Ptr_Glob), %g2
	ld	[%g2], %g2
	st	%g2, [%g1]
	sethi	%hi(Ptr_Glob), %g1
	or	%g1, %lo(Ptr_Glob), %g1
	ld	[%g1], %g1
	st	%g0, [%g1+4]
	sethi	%hi(Ptr_Glob), %g1
	or	%g1, %lo(Ptr_Glob), %g1
	ld	[%g1], %g1
	mov	2, %g2
	st	%g2, [%g1+8]
	sethi	%hi(Ptr_Glob), %g1
	or	%g1, %lo(Ptr_Glob), %g1
	ld	[%g1], %g1
	mov	40, %g2
	st	%g2, [%g1+12]
	sethi	%hi(Ptr_Glob), %g1
	or	%g1, %lo(Ptr_Glob), %g1
	ld	[%g1], %g1
	add	%g1, 16, %g1
	mov	%g1, %o0
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %o1
	call	__strcpy, 0
	 nop
	add	%fp, -56, %g1
	mov	%g1, %o0
	sethi	%hi(.LC1), %g1
	or	%g1, %lo(.LC1), %o1
	call	__strcpy, 0
	 nop
	sethi	%hi(Arr_2_Glob), %g1
	or	%g1, %lo(Arr_2_Glob), %g1
	mov	10, %g2
	st	%g2, [%g1+1628]
	mov	1, %g1
	st	%g1, [%fp-12]
	b	.L9
	 nop
.L15:
	call	Proc_5, 0
	 nop
	call	Proc_4, 0
	 nop
	mov	2, %g1
	st	%g1, [%fp-16]
	mov	3, %g1
	st	%g1, [%fp-4]
	add	%fp, -88, %g1
	mov	%g1, %o0
	sethi	%hi(.LC2), %g1
	or	%g1, %lo(.LC2), %o1
	call	__strcpy, 0
	 nop
	mov	1, %g1
	st	%g1, [%fp-24]
	add	%fp, -56, %g2
	add	%fp, -88, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	call	Func_2, 0
	 nop
	mov	%o0, %g1
	xor	%g1, 0, %g1
	subcc	%g0, %g1, %g0
	subx	%g0, -1, %g1
	and	%g1, 0xff, %g2
	sethi	%hi(Bool_Glob), %g1
	or	%g1, %lo(Bool_Glob), %g1
	st	%g2, [%g1]
	b	.L10
	 nop
.L11:
	ld	[%fp-16], %g2
	mov	%g2, %g1
	sll	%g1, 2, %g1
	add	%g1, %g2, %g2
	ld	[%fp-4], %g1
	sub	%g2, %g1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-16], %g2
	add	%fp, -20, %g1
	mov	%g2, %o0
	ld	[%fp-4], %o1
	mov	%g1, %o2
	call	Proc_7, 0
	 nop
	ld	[%fp-16], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-16]
.L10:
	ld	[%fp-16], %g2
	ld	[%fp-4], %g1
	cmp	%g2, %g1
	bl	.L11
	 nop
	ld	[%fp-16], %g2
	ld	[%fp-20], %g1
	sethi	%hi(Arr_1_Glob), %g3
	or	%g3, %lo(Arr_1_Glob), %o0
	sethi	%hi(Arr_2_Glob), %g3
	or	%g3, %lo(Arr_2_Glob), %o1
	mov	%g2, %o2
	mov	%g1, %o3
	call	Proc_8, 0
	 nop
	sethi	%hi(Ptr_Glob), %g1
	or	%g1, %lo(Ptr_Glob), %g1
	ld	[%g1], %g1
	mov	%g1, %o0
	call	Proc_1, 0
	 nop
	mov	65, %g1
	stb	%g1, [%fp-5]
	b	.L12
	 nop
.L14:
	ldub	[%fp-5], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	mov	%g1, %o0
	mov	67, %o1
	call	Func_1, 0
	 nop
	mov	%o0, %g2
	ld	[%fp-24], %g1
	cmp	%g2, %g1
	bne	.L13
	 nop
	add	%fp, -24, %g1
	mov	0, %o0
	mov	%g1, %o1
	call	Proc_6, 0
	 nop
	add	%fp, -88, %g1
	mov	%g1, %o0
	sethi	%hi(.LC3), %g1
	or	%g1, %lo(.LC3), %o1
	call	__strcpy, 0
	 nop
	ld	[%fp-12], %g1
	st	%g1, [%fp-4]
	sethi	%hi(Int_Glob), %g1
	or	%g1, %lo(Int_Glob), %g1
	ld	[%fp-12], %g2
	st	%g2, [%g1]
.L13:
	ldub	[%fp-5], %g1
	add	%g1, 1, %g1
	stb	%g1, [%fp-5]
.L12:
	sethi	%hi(Ch_2_Glob), %g1
	or	%g1, %lo(Ch_2_Glob), %g1
	ldub	[%g1], %g1
	ldub	[%fp-5], %g2
	sll	%g2, 24, %g2
	sra	%g2, 24, %g2
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g2, %g1
	ble	.L14
	 nop
	ld	[%fp-16], %g1
	ld	[%fp-4], %g2
	smul	%g2, %g1, %g1
	st	%g1, [%fp-4]
	ld	[%fp-20], %g1
	ld	[%fp-4], %g2
	sra	%g2, 31, %g3
	wr	%g3, 0, %y
	nop
	nop
	nop
	sdiv	%g2, %g1, %g1
	st	%g1, [%fp-16]
	ld	[%fp-20], %g1
	ld	[%fp-4], %g2
	sub	%g2, %g1, %g2
	mov	%g2, %g1
	sll	%g1, 3, %g1
	sub	%g1, %g2, %g2
	ld	[%fp-16], %g1
	sub	%g2, %g1, %g1
	st	%g1, [%fp-4]
	add	%fp, -16, %g1
	mov	%g1, %o0
	call	Proc_2, 0
	 nop
	ld	[%fp-12], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-12]
.L9:
	ld	[%fp-12], %g2
	ld	[%fp+68], %g1
	cmp	%g2, %g1
	ble	.L15
	 nop
	restore
	jmp	%o7+8
	 nop
	.size	run_dhrystone, .-run_dhrystone
	.align 4
	.global Proc_1
	.type	Proc_1, #function
	.proc	020
Proc_1:
	save	%sp, -104, %sp
	st	%i0, [%fp+68]
	ld	[%fp+68], %g1
	ld	[%g1], %g1
	st	%g1, [%fp-4]
	ld	[%fp+68], %g1
	ld	[%g1], %g2
	sethi	%hi(Ptr_Glob), %g1
	or	%g1, %lo(Ptr_Glob), %g1
	ld	[%g1], %g1
	mov	%g2, %o0
	mov	%g1, %o1
	mov	48, %o2
	call	__memcpy, 0
	 nop
	ld	[%fp+68], %g1
	mov	5, %g2
	st	%g2, [%g1+12]
	ld	[%fp+68], %g1
	ld	[%g1+12], %g2
	ld	[%fp-4], %g1
	st	%g2, [%g1+12]
	ld	[%fp+68], %g1
	ld	[%g1], %g2
	ld	[%fp-4], %g1
	st	%g2, [%g1]
	ld	[%fp-4], %g1
	mov	%g1, %o0
	call	Proc_3, 0
	 nop
	ld	[%fp-4], %g1
	ld	[%g1+4], %g1
	cmp	%g1, 0
	bne	.L17
	 nop
	ld	[%fp-4], %g1
	mov	6, %g2
	st	%g2, [%g1+12]
	ld	[%fp+68], %g1
	ld	[%g1+8], %g2
	ld	[%fp-4], %g1
	add	%g1, 8, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	call	Proc_6, 0
	 nop
	sethi	%hi(Ptr_Glob), %g1
	or	%g1, %lo(Ptr_Glob), %g1
	ld	[%g1], %g1
	ld	[%g1], %g2
	ld	[%fp-4], %g1
	st	%g2, [%g1]
	ld	[%fp-4], %g1
	ld	[%g1+12], %g2
	ld	[%fp-4], %g1
	add	%g1, 12, %g1
	mov	%g2, %o0
	mov	10, %o1
	mov	%g1, %o2
	call	Proc_7, 0
	 nop
	b	.L16
	 nop
.L17:
	ld	[%fp+68], %g1
	ld	[%g1], %g1
	ld	[%fp+68], %o0
	mov	%g1, %o1
	mov	48, %o2
	call	__memcpy, 0
	 nop
.L16:
	restore
	jmp	%o7+8
	 nop
	.size	Proc_1, .-Proc_1
	.align 4
	.global Proc_2
	.type	Proc_2, #function
	.proc	020
Proc_2:
	save	%sp, -104, %sp
	st	%i0, [%fp+68]
	ld	[%fp+68], %g1
	ld	[%g1], %g1
	add	%g1, 10, %g1
	st	%g1, [%fp-4]
.L21:
	sethi	%hi(Ch_1_Glob), %g1
	or	%g1, %lo(Ch_1_Glob), %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 65
	bne	.L20
	 nop
	ld	[%fp-4], %g1
	add	%g1, -1, %g1
	st	%g1, [%fp-4]
	sethi	%hi(Int_Glob), %g1
	or	%g1, %lo(Int_Glob), %g1
	ld	[%g1], %g1
	ld	[%fp-4], %g2
	sub	%g2, %g1, %g2
	ld	[%fp+68], %g1
	st	%g2, [%g1]
	st	%g0, [%fp-8]
.L20:
	ld	[%fp-8], %g1
	cmp	%g1, 0
	bne	.L21
	 nop
	restore
	jmp	%o7+8
	 nop
	.size	Proc_2, .-Proc_2
	.align 4
	.global Proc_3
	.type	Proc_3, #function
	.proc	020
Proc_3:
	save	%sp, -96, %sp
	st	%i0, [%fp+68]
	sethi	%hi(Ptr_Glob), %g1
	or	%g1, %lo(Ptr_Glob), %g1
	ld	[%g1], %g1
	cmp	%g1, 0
	be	.L23
	 nop
	sethi	%hi(Ptr_Glob), %g1
	or	%g1, %lo(Ptr_Glob), %g1
	ld	[%g1], %g1
	ld	[%g1], %g2
	ld	[%fp+68], %g1
	st	%g2, [%g1]
.L23:
	sethi	%hi(Int_Glob), %g1
	or	%g1, %lo(Int_Glob), %g1
	ld	[%g1], %g2
	sethi	%hi(Ptr_Glob), %g1
	or	%g1, %lo(Ptr_Glob), %g1
	ld	[%g1], %g1
	add	%g1, 12, %g1
	mov	10, %o0
	mov	%g2, %o1
	mov	%g1, %o2
	call	Proc_7, 0
	 nop
	restore
	jmp	%o7+8
	 nop
	.size	Proc_3, .-Proc_3
	.align 4
	.global Proc_4
	.type	Proc_4, #function
	.proc	020
Proc_4:
	save	%sp, -104, %sp
	sethi	%hi(Ch_1_Glob), %g1
	or	%g1, %lo(Ch_1_Glob), %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	xor	%g1, 65, %g1
	subcc	%g0, %g1, %g0
	subx	%g0, -1, %g1
	and	%g1, 0xff, %g1
	st	%g1, [%fp-4]
	sethi	%hi(Bool_Glob), %g1
	or	%g1, %lo(Bool_Glob), %g1
	ld	[%g1], %g2
	ld	[%fp-4], %g1
	or	%g2, %g1, %g2
	sethi	%hi(Bool_Glob), %g1
	or	%g1, %lo(Bool_Glob), %g1
	st	%g2, [%g1]
	sethi	%hi(Ch_2_Glob), %g1
	or	%g1, %lo(Ch_2_Glob), %g1
	mov	66, %g2
	stb	%g2, [%g1]
	restore
	jmp	%o7+8
	 nop
	.size	Proc_4, .-Proc_4
	.align 4
	.global Proc_5
	.type	Proc_5, #function
	.proc	020
Proc_5:
	save	%sp, -96, %sp
	sethi	%hi(Ch_1_Glob), %g1
	or	%g1, %lo(Ch_1_Glob), %g1
	mov	65, %g2
	stb	%g2, [%g1]
	sethi	%hi(Bool_Glob), %g1
	or	%g1, %lo(Bool_Glob), %g1
	st	%g0, [%g1]
	restore
	jmp	%o7+8
	 nop
	.size	Proc_5, .-Proc_5
	.align 4
	.global ajit_main
	.type	ajit_main, #function
	.proc	04
ajit_main:
	save	%sp, -96, %sp
	mov	256, %o0
	mov	0, %o1
	call	store_word_mmureg, 0
	 nop
#APP
! 427 "dhry_1.c" 1
	rd %asr30, %l3 
	 
! 0 "" 2
! 428 "dhry_1.c" 1
	rd %asr31, %l4 
	 
! 0 "" 2
! 429 "dhry_1.c" 1
	wr %l3, 0x00, %asr24 
	
! 0 "" 2
! 430 "dhry_1.c" 1
	wr %l4, 0x00, %asr25 
	
! 0 "" 2
#NO_APP
	mov	1, %o0
	call	run_dhrystone, 0
	 nop
	sethi	%hi(Int_Glob), %g1
	or	%g1, %lo(Int_Glob), %g1
	ld	[%g1], %g1
	mov	%g1, %o0
	call	put_g2, 0
	 nop
	sethi	%hi(Bool_Glob), %g1
	or	%g1, %lo(Bool_Glob), %g1
	ld	[%g1], %g1
	mov	%g1, %o0
	call	put_g3, 0
	 nop
	sethi	%hi(Ch_1_Glob), %g1
	or	%g1, %lo(Ch_1_Glob), %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	mov	%g1, %o0
	call	put_g4, 0
	 nop
	sethi	%hi(Arr_1_Glob), %g1
	or	%g1, %lo(Arr_1_Glob), %g1
	ld	[%g1+32], %g1
	mov	%g1, %o0
	call	put_g5, 0
	 nop
#APP
! 441 "dhry_1.c" 1
	rd %asr30, %l3 
	 
! 0 "" 2
! 442 "dhry_1.c" 1
	rd %asr31, %l4 
	 
! 0 "" 2
! 443 "dhry_1.c" 1
	wr %l3, 0x00, %asr26 
	
! 0 "" 2
! 444 "dhry_1.c" 1
	wr %l4, 0x00, %asr27 
	
! 0 "" 2
#NO_APP
	call	halt, 0
	 nop
	mov	0, %g1
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	ajit_main, .-ajit_main
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
