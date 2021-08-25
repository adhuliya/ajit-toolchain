	.file	"unified.c"
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
	.global halt
	.type	halt, #function
	.proc	020
halt:
#APP
! 40 "../unified.c" 1
	ta 0; nop; nop;
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 nop
	.size	halt, .-halt
	.align 4
	.global store_word_mmureg
	.type	store_word_mmureg, #function
	.proc	020
store_word_mmureg:
#APP
! 46 "../unified.c" 1
	sta %o0, [%o1] 4
	
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 nop
	.size	store_word_mmureg, .-store_word_mmureg
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.asciz	"DHRYSTONE PROGRAM, SOME STRING"
	.align 8
.LC1:
	.asciz	"DHRYSTONE PROGRAM, 1'ST STRING"
	.align 8
.LC2:
	.asciz	"\n"
	.align 8
.LC3:
	.asciz	"Dhrystone Benchmark, Version 2.1 (Language: C)\n"
	.align 8
.LC4:
	.asciz	"Program compiled with 'register' attribute\n"
	.align 8
.LC5:
	.asciz	"Program compiled without 'register' attribute\n"
	.align 8
.LC6:
	.asciz	"Execution starts, %d runs through Dhrystone\n"
	.align 8
.LC7:
	.asciz	"DHRYSTONE PROGRAM, 2'ND STRING"
	.align 8
.LC8:
	.asciz	"Execution ends\n"
	.align 8
.LC9:
	.asciz	"Final values of the variables used in the benchmark:\n"
	.align 8
.LC10:
	.asciz	"Int_Glob:            %d\n"
	.align 8
.LC11:
	.asciz	"        should be:   %d\n"
	.align 8
.LC12:
	.asciz	"Bool_Glob:           %d\n"
	.align 8
.LC13:
	.asciz	"Ch_1_Glob:           %d\n"
	.align 8
.LC14:
	.asciz	"Ch_2_Glob:           %d\n"
	.align 8
.LC15:
	.asciz	"Arr_1_Glob[8]:       %d\n"
	.align 8
.LC16:
	.asciz	"Arr_2_Glob[8][7]:    %d\n"
	.align 8
.LC17:
	.asciz	"        should be:   Number_Of_Runs + 10\n"
	.align 8
.LC18:
	.asciz	"Ptr_Glob->\n"
	.align 8
.LC19:
	.asciz	"  Ptr_Comp:          %d\n"
	.align 8
.LC20:
	.asciz	"        should be:   (implementation-dependent)\n"
	.align 8
.LC21:
	.asciz	"  Discr:             %d\n"
	.align 8
.LC22:
	.asciz	"  Enum_Comp:         %d\n"
	.align 8
.LC23:
	.asciz	"  Int_Comp:          %d\n"
	.align 8
.LC24:
	.asciz	"  Str_Comp:          %s\n"
	.align 8
.LC25:
	.asciz	"        should be:   DHRYSTONE PROGRAM, SOME STRING\n"
	.align 8
.LC26:
	.asciz	"Next_Ptr_Glob->\n"
	.align 8
.LC27:
	.asciz	"        should be:   (implementation-dependent), same as above\n"
	.align 8
.LC28:
	.asciz	"Int_1_Loc:           %d\n"
	.align 8
.LC29:
	.asciz	"Int_2_Loc:           %d\n"
	.align 8
.LC30:
	.asciz	"Int_3_Loc:           %d\n"
	.align 8
.LC31:
	.asciz	"Enum_Loc:            %d\n"
	.align 8
.LC32:
	.asciz	"Str_1_Loc:           %s\n"
	.align 8
.LC33:
	.asciz	"        should be:   DHRYSTONE PROGRAM, 1'ST STRING\n"
	.align 8
.LC34:
	.asciz	"Str_2_Loc:           %s\n"
	.align 8
.LC35:
	.asciz	"        should be:   DHRYSTONE PROGRAM, 2'ND STRING\n"
	.align 8
.LC36:
	.asciz	"Number_Of_Runs=%d, Begin_Time=%d, End_Time=%d, User_time=%d\n"
	.align 8
.LC37:
	.asciz	"Measured time too small to obtain meaningful results\n"
	.align 8
.LC38:
	.asciz	"Please increase number of runs\n"
	.align 8
.LC41:
	.asciz	"Microseconds for one run through Dhrystone: "
	.align 8
.LC42:
	.asciz	"%f \n"
	.align 8
.LC43:
	.asciz	"Dhrystones per Second:                      "
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC39:
	.long	1074035425
	.long	1202590843
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC40:
	.long	1232348160
	.section	".text"
	.align 4
	.global run_dhrystone
	.type	run_dhrystone, #function
	.proc	020
run_dhrystone:
	save	%sp, -192, %sp
	sethi	%hi(p_rec), %g4
	sethi	%hi(g_rec), %i5
	or	%g4, %lo(p_rec), %g3
	or	%i5, %lo(g_rec), %i5
	st	%i5, [%g4+%lo(p_rec)]
	mov	2, %g4
	sethi	%hi(.LC0), %g1
	st	%g4, [%g3+8]
	or	%g1, %lo(.LC0), %g2
	sethi	%hi(Next_Ptr_Glob), %l0
	sethi	%hi(Ptr_Glob), %l1
	st	%i5, [%l0+%lo(Next_Ptr_Glob)]
	st	%g3, [%l1+%lo(Ptr_Glob)]
	st	%g0, [%g3+4]
	mov	40, %g4
	sethi	%hi(-16843776), %i4
	st	%g4, [%g3+12]
	sethi	%hi(-2139062272), %i5
	ld	[%g1+%lo(.LC0)], %g1
	add	%g3, 16, %g3
	add	%g2, 4, %g2
	or	%i4, 767, %i4
	or	%i5, 128, %i5
.L5:
	st	%g1, [%g3]
	add	%g1, %i4, %g4
	add	%g3, 4, %g3
	andn	%g4, %g1, %g4
	ld	[%g2], %g1
	andcc	%g4, %i5, %g0
	be	.L5
	 add	%g2, 4, %g2
	sethi	%hi(.LC1), %g1
	sethi	%hi(-16843776), %i4
	or	%g1, %lo(.LC1), %g3
	sethi	%hi(-2139062272), %i5
	ld	[%g1+%lo(.LC1)], %g1
	add	%g3, 4, %g3
	mov	0, %g2
	add	%fp, -64, %i3
	or	%i4, 767, %i4
	or	%i5, 128, %i5
.L6:
	st	%g1, [%i3+%g2]
	add	%g1, %i4, %g4
	add	%g2, 4, %g2
	andn	%g4, %g1, %g4
	ld	[%g3], %g1
	andcc	%g4, %i5, %g0
	be	.L6
	 add	%g3, 4, %g3
	mov	10, %g1
	sethi	%hi(.LC2), %l2
	sethi	%hi(Arr_2_Glob), %i2
	or	%l2, %lo(.LC2), %o0
	or	%i2, %lo(Arr_2_Glob), %i2
	call	ee_printf, 0
	 st	%g1, [%i2+1628]
	sethi	%hi(.LC3), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC3), %o0
	call	ee_printf, 0
	 or	%l2, %lo(.LC2), %o0
	sethi	%hi(Reg), %g1
	ld	[%g1+%lo(Reg)], %g1
	cmp	%g1, 0
	be,a	.L7
	 sethi	%hi(.LC5), %o0
	sethi	%hi(.LC4), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC4), %o0
	call	ee_printf, 0
	 or	%l2, %lo(.LC2), %o0
	call	ee_printf, 0
	 or	%l2, %lo(.LC2), %o0
	mov	%i0, %o1
	sethi	%hi(.LC6), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC6), %o0
	call	ajit_barebones_clock, 0
	 nop
	sethi	%hi(Begin_Time), %g1
	cmp	%i0, 0
	ble	.L23
	 st	%o0, [%g1+%lo(Begin_Time)]
.L47:
	sethi	%hi(.LC7), %g1
	sethi	%hi(.LC7+4), %l5
	add	%fp, -32, %i5
	sethi	%hi(Arr_1_Glob), %i1
	sethi	%hi(Ptr_Glob), %o0
	sethi	%hi(-16843776), %g4
	sethi	%hi(-2139062272), %g3
	sethi	%hi(5120), %l4
	ld	[%g1+%lo(.LC7)], %l6
	mov	1, %o4
	or	%l5, %lo(.LC7+4), %l5
	or	%i1, %lo(Arr_1_Glob), %i1
	or	%o0, %lo(Ptr_Glob), %o0
	or	%g4, 767, %g4
	or	%g3, 128, %g3
	mov	7, %o5
	mov	8, %o7
	or	%l4, 512, %l4
	mov	5, %o2
	mov	17, %l3
	mov	%i5, %o3
	mov	%l5, %i5
.L48:
	mov	%l6, %g1
	mov	0, %g2
.L10:
	st	%g1, [%o3+%g2]
	add	%g1, %g4, %i4
	add	%g2, 4, %g2
	andn	%i4, %g1, %i4
	ld	[%i5], %g1
	andcc	%i4, %g3, %g0
	be	.L10
	 add	%i5, 4, %i5
	ldsb	[%fp-62], %g2
	ldsb	[%fp-29], %g1
	cmp	%g2, %g1
	be	.L43
	 mov	0, %g2
.L11:
	ld	[%i3+%g2], %i5
	ld	[%o3+%g2], %g1
	add	%i5, %g4, %i4
	sub	%i5, %g1, %g1
	andn	%i4, %i5, %i5
	and	%i5, %g3, %i5
	orcc	%i5, %g1, %g0
	be	.L11
	 add	%g2, 4, %g2
	ld	[%i2+1628], %g2
	add	%g2, 1, %g2
	st	%o7, [%i1+152]
	st	%g2, [%i2+1628]
	st	%o7, [%i2+1632]
	ld	[%o0], %g2
	st	%o7, [%i2+1636]
	st	%o5, [%i2+%l4]
	ldd	[%g2], %i4
	st	%o5, [%i1+32]
	st	%o5, [%i1+36]
	ld	[%g2], %o1
	std	%i4, [%o1]
	ldd	[%g2+8], %i4
	std	%i4, [%o1+8]
	ldd	[%g2+16], %i4
	std	%i4, [%o1+16]
	ldd	[%g2+24], %i4
	std	%i4, [%o1+24]
	ldd	[%g2+32], %i4
	std	%i4, [%o1+32]
	ldd	[%g2+40], %i4
	std	%i4, [%o1+40]
	st	%o2, [%g2+12]
	st	%o1, [%o1]
	st	%o2, [%o1+12]
	ld	[%g2], %i5
	st	%i5, [%o1]
	ld	[%o0], %i5
	st	%l3, [%i5+12]
	sra	%g1, 31, %i4
	ld	[%o1+4], %l7
	sub	%i4, %g1, %g1
	cmp	%l7, 0
	srl	%g1, 31, %g1
	be	.L45
	 xor	%g1, 1, %g1
	ld	[%g2], %o1
	ldd	[%o1], %i4
	std	%i4, [%g2]
	ldd	[%o1+8], %i4
	std	%i4, [%g2+8]
	ldd	[%o1+16], %i4
	std	%i4, [%g2+16]
	ldd	[%o1+24], %i4
	std	%i4, [%g2+24]
	ldd	[%o1+32], %i4
	std	%i4, [%g2+32]
	ldd	[%o1+40], %i4
	std	%i4, [%g2+40]
.L18:
	mov	65, %g2
.L25:
	and	%g2, 67, %g2
	cmp	%g2, 66
	bne,a	.L25
	 mov	66, %g2
	add	%o4, 1, %o4
	cmp	%i0, %o4
	bge,a	.L48
	 mov	%l5, %i5
	sethi	%hi(Bool_Glob), %l5
	st	%g1, [%l5+%lo(Bool_Glob)]
	mov	5, %g1
	sethi	%hi(Ch_1_Glob), %l4
	sethi	%hi(Ch_2_Glob), %l3
	sethi	%hi(Int_Glob), %i4
	mov	65, %g3
	stb	%g2, [%l3+%lo(Ch_2_Glob)]
	st	%g1, [%i4+%lo(Int_Glob)]
	mov	%o3, %i5
	stb	%g3, [%l4+%lo(Ch_1_Glob)]
	mov	1, %l7
	mov	5, %g2
	mov	13, %g1
.L9:
	st	%g1, [%fp-68]
	call	ajit_barebones_clock, 0
	 st	%g2, [%fp-80]
	sethi	%hi(End_Time), %l6
	st	%o0, [%l6+%lo(End_Time)]
	sethi	%hi(.LC8), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC8), %o0
	call	ee_printf, 0
	 or	%l2, %lo(.LC2), %o0
	sethi	%hi(.LC9), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC9), %o0
	call	ee_printf, 0
	 or	%l2, %lo(.LC2), %o0
	ld	[%i4+%lo(Int_Glob)], %o1
	sethi	%hi(.LC10), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC10), %o0
	sethi	%hi(.LC11), %i4
	mov	5, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC11), %o0
	ld	[%l5+%lo(Bool_Glob)], %o1
	sethi	%hi(.LC12), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC12), %o0
	mov	1, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC11), %o0
	ldsb	[%l4+%lo(Ch_1_Glob)], %o1
	sethi	%hi(.LC13), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC13), %o0
	mov	65, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC11), %o0
	ldsb	[%l3+%lo(Ch_2_Glob)], %o1
	sethi	%hi(.LC14), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC14), %o0
	mov	66, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC11), %o0
	ld	[%i1+32], %o1
	sethi	%hi(.LC15), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC15), %o0
	mov	7, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC11), %o0
	ld	[%i2+1628], %o1
	sethi	%hi(.LC16), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC16), %o0
	sethi	%hi(.LC17), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC17), %o0
	sethi	%hi(.LC18), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC18), %o0
	sethi	%hi(.LC19), %g3
	ld	[%l1+%lo(Ptr_Glob)], %g4
	or	%g3, %lo(.LC19), %o0
	ld	[%g4], %o1
	call	ee_printf, 0
	 st	%g3, [%fp-76]
	sethi	%hi(.LC20), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC20), %o0
	ld	[%l1+%lo(Ptr_Glob)], %g4
	sethi	%hi(.LC21), %l5
	ld	[%g4+4], %o1
	call	ee_printf, 0
	 or	%l5, %lo(.LC21), %o0
	mov	0, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC11), %o0
	ld	[%l1+%lo(Ptr_Glob)], %g4
	sethi	%hi(.LC22), %l4
	ld	[%g4+8], %o1
	call	ee_printf, 0
	 or	%l4, %lo(.LC22), %o0
	mov	2, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC11), %o0
	ld	[%l1+%lo(Ptr_Glob)], %g4
	sethi	%hi(.LC23), %l3
	ld	[%g4+12], %o1
	call	ee_printf, 0
	 or	%l3, %lo(.LC23), %o0
	mov	17, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC11), %o0
	sethi	%hi(.LC24), %i1
	ld	[%l1+%lo(Ptr_Glob)], %o1
	or	%i1, %lo(.LC24), %o0
	call	ee_printf, 0
	 add	%o1, 16, %o1
	sethi	%hi(.LC25), %i2
	call	ee_printf, 0
	 or	%i2, %lo(.LC25), %o0
	sethi	%hi(.LC26), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC26), %o0
	ld	[%fp-76], %g3
	or	%g3, %lo(.LC19), %o0
	ld	[%l0+%lo(Next_Ptr_Glob)], %g3
	call	ee_printf, 0
	 ld	[%g3], %o1
	sethi	%hi(.LC27), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC27), %o0
	ld	[%l0+%lo(Next_Ptr_Glob)], %g3
	or	%l5, %lo(.LC21), %o0
	call	ee_printf, 0
	 ld	[%g3+4], %o1
	mov	0, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC11), %o0
	ld	[%l0+%lo(Next_Ptr_Glob)], %g3
	or	%l4, %lo(.LC22), %o0
	call	ee_printf, 0
	 ld	[%g3+8], %o1
	mov	1, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC11), %o0
	ld	[%l0+%lo(Next_Ptr_Glob)], %g3
	or	%l3, %lo(.LC23), %o0
	call	ee_printf, 0
	 ld	[%g3+12], %o1
	mov	18, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC11), %o0
	ld	[%l0+%lo(Next_Ptr_Glob)], %o1
	or	%i1, %lo(.LC24), %o0
	call	ee_printf, 0
	 add	%o1, 16, %o1
	call	ee_printf, 0
	 or	%i2, %lo(.LC25), %o0
	ld	[%fp-80], %g2
	sethi	%hi(.LC28), %o0
	mov	%g2, %o1
	call	ee_printf, 0
	 or	%o0, %lo(.LC28), %o0
	mov	5, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC11), %o0
	ld	[%fp-68], %g1
	sethi	%hi(.LC29), %o0
	mov	%g1, %o1
	call	ee_printf, 0
	 or	%o0, %lo(.LC29), %o0
	mov	13, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC11), %o0
	mov	7, %o1
	sethi	%hi(.LC30), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC30), %o0
	mov	7, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC11), %o0
	mov	%l7, %o1
	sethi	%hi(.LC31), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC31), %o0
	mov	1, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC11), %o0
	mov	%i3, %o1
	sethi	%hi(.LC32), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC32), %o0
	sethi	%hi(.LC33), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC33), %o0
	mov	%i5, %o1
	sethi	%hi(.LC34), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC34), %o0
	sethi	%hi(.LC35), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC35), %o0
	call	ee_printf, 0
	 or	%l2, %lo(.LC2), %o0
	ld	[%l6+%lo(End_Time)], %o3
	sethi	%hi(Begin_Time), %i4
	sethi	%hi(User_Time), %g2
	ld	[%i4+%lo(Begin_Time)], %o2
	sub	%o3, %o2, %g1
	st	%g1, [%g2+%lo(User_Time)]
	cmp	%g1, 119
	ble	.L46
	 sethi	%hi(.LC2), %i5
	st	%g1, [%fp-84]
	ld	[%fp-84], %f8
	st	%i0, [%fp-84]
	ld	[%fp-84], %f10
	mov	%g1, %o4
	fitos	%f8, %f12
	sethi	%hi(.LC39), %g1
	fstod	%f12, %f12
	fitod	%f10, %f8
	ldd	[%g1+%lo(.LC39)], %f10
	fmuld	%f12, %f10, %f10
	fdivd	%f10, %f8, %f8
	sethi	%hi(.LC40), %g1
	fdtos	%f8, %f8
	ld	[%g1+%lo(.LC40)], %f9
	fdivs	%f9, %f8, %f9
	mov	%i0, %o1
	sethi	%hi(Microseconds), %i3
	sethi	%hi(Dhrystones_Per_Second), %i4
	st	%f8, [%i3+%lo(Microseconds)]
	st	%f9, [%i4+%lo(Dhrystones_Per_Second)]
	sethi	%hi(.LC36), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC36), %o0
	sethi	%hi(.LC41), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC41), %o0
	ld	[%i3+%lo(Microseconds)], %f8
	fstod	%f8, %f8
	std	%f8, [%fp-96]
	ldd	[%fp-96], %g2
	sethi	%hi(.LC42), %i2
	mov	%g2, %o1
	mov	%g3, %o2
	call	ee_printf, 0
	 or	%i2, %lo(.LC42), %o0
	sethi	%hi(.LC43), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC43), %o0
	ld	[%i4+%lo(Dhrystones_Per_Second)], %f8
	fstod	%f8, %f8
	std	%f8, [%fp-96]
	ldd	[%fp-96], %g2
	or	%i2, %lo(.LC42), %o0
	mov	%g2, %o1
	call	ee_printf, 0
	 mov	%g3, %o2
	call	ee_printf, 0
	 or	%i5, %lo(.LC2), %o0
	jmp	%i7+8
	 restore
.L43:
	b,a	.L43
.L45:
	mov	6, %i4
	st	%i4, [%o1+12]
	ld	[%g2+8], %g2
	cmp	%g2, 2
	be	.L14
	 mov	3, %l7
	cmp	%g2, 4
	be	.L17
	 st	%l7, [%o1+8]
	cmp	%g2, 0
	be,a	.L15
	 st	%g0, [%o1+8]
.L15:
	ld	[%i5], %g2
	mov	18, %l7
	st	%g2, [%o1]
	b	.L18
	 st	%l7, [%o1+12]
.L17:
	mov	2, %g2
	b	.L15
	 st	%g2, [%o1+8]
.L14:
	mov	1, %i4
	b	.L15
	 st	%i4, [%o1+8]
.L7:
	call	ee_printf, 0
	 or	%o0, %lo(.LC5), %o0
	call	ee_printf, 0
	 or	%l2, %lo(.LC2), %o0
	call	ee_printf, 0
	 or	%l2, %lo(.LC2), %o0
	mov	%i0, %o1
	sethi	%hi(.LC6), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC6), %o0
	call	ajit_barebones_clock, 0
	 nop
	sethi	%hi(Begin_Time), %g1
	cmp	%i0, 0
	bg	.L47
	 st	%o0, [%g1+%lo(Begin_Time)]
.L23:
	sethi	%hi(Arr_1_Glob), %i1
	mov	0, %l7
	mov	0, %g2
	mov	0, %g1
	add	%fp, -32, %i5
	or	%i1, %lo(Arr_1_Glob), %i1
	sethi	%hi(Ch_1_Glob), %l4
	sethi	%hi(Bool_Glob), %l5
	sethi	%hi(Ch_2_Glob), %l3
	b	.L9
	 sethi	%hi(Int_Glob), %i4
.L46:
	mov	%i0, %o1
	mov	%g1, %o4
	sethi	%hi(.LC36), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC36), %o0
	sethi	%hi(.LC37), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC37), %o0
	sethi	%hi(.LC38), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC38), %o0
	call	ee_printf, 0
	 or	%i5, %lo(.LC2), %o0
	jmp	%i7+8
	 restore
	.size	run_dhrystone, .-run_dhrystone
	.align 4
	.global Proc_1
	.type	Proc_1, #function
	.proc	020
Proc_1:
	sethi	%hi(Ptr_Glob), %o5
	ld	[%o5+%lo(Ptr_Glob)], %g4
	ldd	[%g4], %g2
	ld	[%o0], %g1
	std	%g2, [%g1]
	ldd	[%g4+8], %g2
	std	%g2, [%g1+8]
	ldd	[%g4+16], %g2
	std	%g2, [%g1+16]
	ldd	[%g4+24], %g2
	std	%g2, [%g1+24]
	ldd	[%g4+32], %g2
	std	%g2, [%g1+32]
	ldd	[%g4+40], %g2
	std	%g2, [%g1+40]
	st	%g1, [%g1]
	mov	5, %g2
	st	%g2, [%o0+12]
	ld	[%g4], %g3
	st	%g2, [%g1+12]
	st	%g3, [%g1]
	sethi	%hi(Int_Glob), %g3
	ld	[%o5+%lo(Ptr_Glob)], %g2
	ld	[%g3+%lo(Int_Glob)], %g3
	add	%g3, 12, %g4
	st	%g4, [%g2+12]
	ld	[%g1+4], %g4
	cmp	%g4, 0
	be,a	.L64
	 mov	6, %g4
	ld	[%o0], %g1
	ldd	[%g1], %g2
	std	%g2, [%o0]
	ldd	[%g1+8], %g2
	std	%g2, [%o0+8]
	ldd	[%g1+16], %g2
	std	%g2, [%o0+16]
	ldd	[%g1+24], %g2
	std	%g2, [%o0+24]
	ldd	[%g1+32], %g2
	std	%g2, [%o0+32]
	ldd	[%g1+40], %g2
	jmp	%o7+8
	 std	%g2, [%o0+40]
.L64:
	st	%g4, [%g1+12]
	ld	[%o0+8], %g4
	cmp	%g4, 2
	be	.L51
	 cmp	%g4, 1
	mov	3, %o5
	be	.L54
	 st	%o5, [%g1+8]
	cmp	%g4, 1
	blu,a	.L65
	 ld	[%g2], %g2
	cmp	%g4, 2
	be	.L51
	 cmp	%g4, 4
	bne,a	.L66
	 ld	[%g2], %g2
	mov	2, %g3
	st	%g3, [%g1+8]
.L52:
	ld	[%g2], %g2
.L66:
	st	%g2, [%g1]
	mov	18, %g2
	jmp	%o7+8
	 st	%g2, [%g1+12]
.L54:
	cmp	%g3, 100
	ble	.L66
	 ld	[%g2], %g2
.L65:
	st	%g0, [%g1+8]
	st	%g2, [%g1]
	mov	18, %g2
	jmp	%o7+8
	 st	%g2, [%g1+12]
.L51:
	mov	1, %g3
	b	.L52
	 st	%g3, [%g1+8]
	.size	Proc_1, .-Proc_1
	.align 4
	.global Proc_2
	.type	Proc_2, #function
	.proc	020
Proc_2:
	sethi	%hi(Ch_1_Glob), %g1
	ldsb	[%g1+%lo(Ch_1_Glob)], %g1
	cmp	%g1, 65
	be	.L69
	 ld	[%o0], %g2
	jmp	%o7+8
	 nop
.L69:
	add	%g2, 9, %g2
	sethi	%hi(Int_Glob), %g1
	ld	[%g1+%lo(Int_Glob)], %g1
	sub	%g2, %g1, %g2
	jmp	%o7+8
	 st	%g2, [%o0]
	.size	Proc_2, .-Proc_2
	.align 4
	.global Proc_3
	.type	Proc_3, #function
	.proc	020
Proc_3:
	sethi	%hi(Ptr_Glob), %g1
	ld	[%g1+%lo(Ptr_Glob)], %g2
	cmp	%g2, 0
	be,a	.L74
	 mov	0, %g2
	ld	[%g2], %g2
	st	%g2, [%o0]
	ld	[%g1+%lo(Ptr_Glob)], %g2
	sethi	%hi(Int_Glob), %g1
	ld	[%g1+%lo(Int_Glob)], %g1
	add	%g1, 12, %g1
	jmp	%o7+8
	 st	%g1, [%g2+12]
.L74:
	sethi	%hi(Int_Glob), %g1
	ld	[%g1+%lo(Int_Glob)], %g1
	add	%g1, 12, %g1
	jmp	%o7+8
	 st	%g1, [%g2+12]
	.size	Proc_3, .-Proc_3
	.align 4
	.global Proc_4
	.type	Proc_4, #function
	.proc	020
Proc_4:
	sethi	%hi(Ch_1_Glob), %g3
	ldsb	[%g3+%lo(Ch_1_Glob)], %g3
	xor	%g3, 65, %g3
	subcc	%g0, %g3, %g0
	sethi	%hi(Ch_2_Glob), %g3
	sethi	%hi(Bool_Glob), %g1
	mov	66, %g4
	ld	[%g1+%lo(Bool_Glob)], %g2
	stb	%g4, [%g3+%lo(Ch_2_Glob)]
	subx	%g0, -1, %g3
	or	%g3, %g2, %g2
	jmp	%o7+8
	 st	%g2, [%g1+%lo(Bool_Glob)]
	.size	Proc_4, .-Proc_4
	.align 4
	.global Proc_5
	.type	Proc_5, #function
	.proc	020
Proc_5:
	sethi	%hi(Ch_1_Glob), %g1
	mov	65, %g2
	stb	%g2, [%g1+%lo(Ch_1_Glob)]
	sethi	%hi(Bool_Glob), %g1
	jmp	%o7+8
	 st	%g0, [%g1+%lo(Bool_Glob)]
	.size	Proc_5, .-Proc_5
	.align 4
	.global ajit_main
	.type	ajit_main, #function
	.proc	04
ajit_main:
	save	%sp, -96, %sp
	call	__ajit_write_serial_control_register__, 0
	 mov	3, %o0
	mov	0, %g2
	mov	256, %g1
#APP
! 46 "../unified.c" 1
	sta %g1, [%g2] 4
	
! 0 "" 2
#NO_APP
	call	run_dhrystone, 0
	 mov	2, %o0
#APP
! 40 "../unified.c" 1
	ta 0; nop; nop;
! 0 "" 2
#NO_APP
	jmp	%i7+8
	 restore %g0, 0, %o0
	.size	ajit_main, .-ajit_main
	.align 4
	.global Proc_6
	.type	Proc_6, #function
	.proc	020
Proc_6:
	cmp	%o0, 2
	be	.L79
	 mov	3, %g1
	cmp	%o0, 1
	be	.L82
	 st	%g1, [%o1]
	cmp	%o0, 1
	bgeu	.L91
	 cmp	%o0, 2
	jmp	%o7+8
	 st	%g0, [%o1]
.L91:
	be	.L79
	 cmp	%o0, 4
	bne	.L92
	 mov	2, %g1
	st	%g1, [%o1]
.L92:
	jmp	%o7+8
	 nop
.L79:
	mov	1, %g1
	jmp	%o7+8
	 st	%g1, [%o1]
.L82:
	sethi	%hi(Int_Glob), %g1
	ld	[%g1+%lo(Int_Glob)], %g1
	cmp	%g1, 100
	ble	.L92
	 nop
	jmp	%o7+8
	 st	%g0, [%o1]
	.size	Proc_6, .-Proc_6
	.align 4
	.global Proc_7
	.type	Proc_7, #function
	.proc	020
Proc_7:
	add	%o0, 2, %o0
	add	%o1, %o0, %o1
	jmp	%o7+8
	 st	%o1, [%o2]
	.size	Proc_7, .-Proc_7
	.align 4
	.global Proc_8
	.type	Proc_8, #function
	.proc	020
Proc_8:
	add	%o2, 5, %g1
	sll	%g1, 2, %g2
	st	%o3, [%o0+%g2]
	add	%o2, 6, %g3
	sll	%g3, 2, %g3
	st	%o3, [%o0+%g3]
	add	%o2, 35, %g4
	sll	%g4, 2, %g4
	st	%g1, [%o0+%g4]
	smul	%g1, 200, %g4
	add	%o1, %g4, %o1
	st	%g1, [%o1+%g2]
	st	%g1, [%o1+%g3]
	add	%o2, 4, %o2
	sll	%o2, 2, %o2
	ld	[%o1+%o2], %g1
	add	%g1, 1, %g1
	st	%g1, [%o1+%o2]
	add	%o1, %g2, %o1
	ld	[%o0+%g2], %g1
	st	%g1, [%o1+4000]
	mov	5, %g2
	sethi	%hi(Int_Glob), %g1
	jmp	%o7+8
	 st	%g2, [%g1+%lo(Int_Glob)]
	.size	Proc_8, .-Proc_8
	.align 4
	.global Func_1
	.type	Func_1, #function
	.proc	012
Func_1:
	sll	%o0, 24, %g1
	sll	%o1, 24, %o1
	sra	%g1, 24, %g2
	cmp	%o1, %g1
	be	.L98
	 mov	0, %o0
	jmp	%o7+8
	 nop
.L98:
	sethi	%hi(Ch_1_Glob), %g1
	mov	1, %o0
	jmp	%o7+8
	 stb	%g2, [%g1+%lo(Ch_1_Glob)]
	.size	Func_1, .-Func_1
	.align 4
	.global Func_2
	.type	Func_2, #function
	.proc	04
Func_2:
	ldsb	[%o0+2], %g2
	ldsb	[%o1+3], %g3
	cmp	%g3, %g2
	be	.L112
	 mov	0, %g1
	sethi	%hi(-16843776), %o4
	sethi	%hi(-2139062272), %o5
	or	%o4, 767, %o4
	or	%o5, 128, %o5
.L109:
	ld	[%o0+%g1], %g2
	ld	[%o1+%g1], %g3
	add	%g2, %o4, %g4
	sub	%g2, %g3, %g3
	andn	%g4, %g2, %g2
	and	%g2, %o5, %g2
	orcc	%g2, %g3, %g0
	be	.L109
	 add	%g1, 4, %g1
	cmp	%g3, 0
	ble	.L106
	 mov	10, %g2
	sethi	%hi(Int_Glob), %g1
	mov	1, %o0
	jmp	%o7+8
	 st	%g2, [%g1+%lo(Int_Glob)]
.L112:
	b,a	.L112
.L106:
	jmp	%o7+8
	 mov	0, %o0
	.size	Func_2, .-Func_2
	.align 4
	.global Func_3
	.type	Func_3, #function
	.proc	04
Func_3:
	xor	%o0, 2, %o0
	subcc	%g0, %o0, %g0
	jmp	%o7+8
	 subx	%g0, -1, %o0
	.size	Func_3, .-Func_3
	.align 4
	.global __memcpy
	.type	__memcpy, #function
	.proc	0120
__memcpy:
	ldd	[%o1], %g2
	mov	0, %g1
.L115:
	std	%g2, [%o0+%g1]
	add	%g1, 8, %g1
	cmp	%o2, %g1
	bgu	.L115
	 ldd	[%o1+%g1], %g2
	jmp	%o7+8
	 nop
	.size	__memcpy, .-__memcpy
	.align 4
	.global __strcpy
	.type	__strcpy, #function
	.proc	0102
__strcpy:
	sethi	%hi(-16843776), %o5
	sethi	%hi(-2139062272), %g4
	ld	[%o1], %g2
	mov	0, %g1
	or	%o5, 767, %o5
	or	%g4, 128, %g4
.L118:
	st	%g2, [%o0+%g1]
	add	%g2, %o5, %g3
	add	%g1, 4, %g1
	andn	%g3, %g2, %g3
	andcc	%g3, %g4, %g0
	be	.L118
	 ld	[%o1+%g1], %g2
	jmp	%o7+8
	 nop
	.size	__strcpy, .-__strcpy
	.align 4
	.global __strcmp
	.type	__strcmp, #function
	.proc	04
__strcmp:
	sethi	%hi(-16843776), %o3
	sethi	%hi(-2139062272), %o4
	mov	%o0, %o5
	mov	0, %g1
	or	%o3, 767, %o3
	or	%o4, 128, %o4
.L124:
	ld	[%o5+%g1], %g2
	ld	[%o1+%g1], %g4
	add	%g2, %o3, %g3
	sub	%g2, %g4, %o0
	andn	%g3, %g2, %g2
	and	%g2, %o4, %g2
	orcc	%g2, %o0, %g0
	be	.L124
	 add	%g1, 4, %g1
	jmp	%o7+8
	 nop
	.size	__strcmp, .-__strcmp
	.common	p_rec,48,8
	.common	g_rec,48,8
	.common	Dhrystones_Per_Second,4,4
	.common	Microseconds,4,4
	.common	User_Time,4,4
	.common	End_Time,4,4
	.common	Begin_Time,4,4
	.common	time_info,16,4
	.global Reg
	.section	".bss"
	.align 4
	.type	Reg, #object
	.size	Reg, 4
Reg:
	.skip	4
	.common	Arr_2_Glob,10000,4
	.common	Arr_1_Glob,200,4
	.common	Ch_2_Glob,1,1
	.common	Ch_1_Glob,1,4
	.common	Bool_Glob,4,4
	.common	Int_Glob,4,4
	.common	Next_Ptr_Glob,4,4
	.common	Ptr_Glob,4,4
	.ident	"GCC: (Buildroot 2014.08-g9d8f423-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
