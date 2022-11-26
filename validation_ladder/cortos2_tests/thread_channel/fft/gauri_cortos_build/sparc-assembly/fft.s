	.file	"fft.c"
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	1075388923
	.long	1413754136
	.section	".text"
	.align 4
	.global twiddle_factors
	.type	twiddle_factors, #function
	.proc	020
twiddle_factors:
	save	%sp, -128, %sp
	ld	[%fp+92], %g1
	srl	%g1, 31, %l2
	add	%l2, %g1, %l2
	sra	%l2, 1, %l2
	cmp	%i1, %l2
	bge	.L10
	 sll	%i1, 3, %g2
	st	%g1, [%fp-24]
	sll	%i2, 3, %l0
	ld	[%fp-24], %f9
	add	%i4, %g2, %i4
	fitod	%f9, %f8
	add	%i5, %g2, %i5
	add	%i3, %g2, %i3
	sll	%l2, 3, %l1
	b	.L5
	 std	%f8, [%fp-8]
.L9:
	call	sin, 0
	 nop
	ld	[%fp-20], %f10
.L4:
	ld	[%i4], %f9
	ld	[%i4+4], %f11
	ld	[%i5], %f12
	fmuls	%f10, %f9, %f13
	fdtos	%f0, %f0
	fmuls	%f10, %f11, %f10
	fmuls	%f0, %f11, %f8
	fmuls	%f0, %f9, %f0
	fsubs	%f13, %f8, %f8
	fadds	%f10, %f0, %f10
	fadds	%f8, %f12, %f12
	st	%f12, [%i3]
	ld	[%i5+4], %f9
	fadds	%f10, %f9, %f9
	st	%f9, [%i3+4]
	ld	[%i5], %f9
	fsubs	%f9, %f8, %f8
	st	%f8, [%i3+%l1]
	add	%i3, %l1, %g1
	ld	[%i5+4], %f8
	fsubs	%f8, %f10, %f10
	st	%f10, [%g1+4]
	add	%i1, %i2, %i1
	add	%i4, %l0, %i4
	add	%i5, %l0, %i5
	cmp	%i1, %l2
	bge	.L10
	 add	%i3, %l0, %i3
.L5:
	st	%i1, [%fp-24]
	ld	[%fp-24], %f10
	sethi	%hi(.LC0), %g1
	fitod	%f10, %f8
	ldd	[%g1+%lo(.LC0)], %f10
	fmuld	%f8, %f10, %f8
	ldd	[%fp-8], %f10
	fdivd	%f8, %f10, %f8
	std	%f8, [%fp-32]
	std	%f8, [%fp-16]
	call	cos, 0
	 ldd	[%fp-32], %o0
	ldd	[%fp-16], %f8
	fdtos	%f0, %f10
	std	%f8, [%fp-32]
	st	%f10, [%fp-20]
	cmp	%i0, 0
	bne	.L9
	 ldd	[%fp-32], %o0
	call	sin, 0
	 nop
	ld	[%fp-20], %f10
	b	.L4
	 fnegs	%f0, %f0
.L10:
	jmp	%i7+8
	 restore
	.size	twiddle_factors, .-twiddle_factors
	.align 4
	.global fft
	.type	fft, #function
	.proc	020
fft:
	save	%sp, -104, %sp
	cmp	%i1, 1
	ble	.L15
	 sra	%i1, 1, %i3
	mov	%i0, %g2
	sll	%i3, 3, %i5
	mov	0, %g1
	add	%i2, %i5, %i5
	mov	0, %g3
.L13:
	ld	[%g2], %g4
	st	%g4, [%i2+%g1]
	add	%i2, %g1, %g4
	ld	[%g2+4], %i4
	st	%i4, [%g4+4]
	ld	[%g2+8], %g4
	st	%g4, [%i5+%g1]
	add	%i5, %g1, %g4
	ld	[%g2+12], %i4
	st	%i4, [%g4+4]
	add	%g3, 1, %g3
	add	%g2, 16, %g2
	cmp	%i3, %g3
	bg	.L13
	 add	%g1, 8, %g1
	mov	%i2, %o0
	mov	%i3, %o1
	call	fft, 0
	 mov	%i0, %o2
	mov	%i5, %o0
	mov	%i3, %o1
	call	fft, 0
	 mov	%i0, %o2
	mov	0, %o0
	st	%i1, [%sp+92]
	mov	0, %o1
	mov	1, %o2
	mov	%i0, %o3
	mov	%i5, %o4
	call	twiddle_factors, 0
	 mov	%i2, %o5
.L15:
	jmp	%i7+8
	 restore
	.size	fft, .-fft
	.align 4
	.global fft_top
	.type	fft_top, #function
	.proc	020
fft_top:
	save	%sp, -112, %sp
	sethi	%hi(tc), %g1
	or	%g1, %lo(tc), %g1
	st	%g1, [%fp-8]
	srl	%i1, 31, %i3
	mov	%i0, %g2
	add	%i3, %i1, %i3
	mov	0, %g1
	sra	%i3, 1, %i3
	sll	%i3, 3, %i4
	cmp	%i3, 0
	ble	.L20
	 add	%i2, %i4, %i5
.L24:
	ld	[%g2], %g3
	st	%g3, [%i2+%g1]
	add	%i2, %g1, %g3
	ld	[%g2+4], %g4
	st	%g4, [%g3+4]
	ld	[%g2+8], %g3
	st	%g3, [%i5+%g1]
	add	%i5, %g1, %g3
	ld	[%g2+12], %g4
	st	%g4, [%g3+4]
	add	%g1, 8, %g1
	cmp	%i4, %g1
	bne	.L24
	 add	%g2, 16, %g2
.L20:
	sethi	%hi(fft_args), %l1
	mov	%i3, %o1
	or	%l1, %lo(fft_args), %o0
	mov	%i2, %o2
	mov	%i0, %o3
	mov	%o0, %l1
	call	setXfftArgs, 0
	 sethi	%hi(fft_thread), %l0
	or	%l0, %lo(fft_thread), %l0
.L18:
	ld	[%fp-8], %o0
	mov	%l0, %o1
	call	scheduleChannelJob, 0
	 mov	%l1, %o2
	cmp	%o0, 0
	bne	.L18
	 mov	%i5, %o0
	mov	%i3, %o1
	call	fft, 0
	 add	%i0, %i4, %o2
	st	%g0, [%fp-4]
.L21:
	ld	[%fp-8], %o0
	call	getChannelResponse, 0
	 add	%fp, -4, %o1
	cmp	%o0, 0
	bne	.L21
	 sethi	%hi(twiddle_args), %i3
	st	%i5, [%sp+92]
	or	%i3, %lo(twiddle_args), %o0
	st	%i2, [%sp+96]
	mov	0, %o1
	mov	%i1, %o2
	mov	0, %o3
	mov	2, %o4
	mov	%i0, %o5
	mov	%o0, %i3
	call	setXtwiddleArgs, 0
	 sethi	%hi(twiddle_factors_thread), %i4
	or	%i4, %lo(twiddle_factors_thread), %i4
.L22:
	ld	[%fp-8], %o0
	mov	%i4, %o1
	call	scheduleChannelJob, 0
	 mov	%i3, %o2
	cmp	%o0, 0
	bne	.L22
	 mov	1, %o1
	st	%i1, [%sp+92]
	mov	2, %o2
	mov	%i0, %o3
	mov	%i5, %o4
	call	twiddle_factors, 0
	 mov	%i2, %o5
	st	%g0, [%fp-4]
.L23:
	ld	[%fp-8], %o0
	call	getChannelResponse, 0
	 add	%fp, -4, %o1
	cmp	%o0, 0
	bne	.L23
	 nop
	jmp	%i7+8
	 restore
	.size	fft_top, .-fft_top
	.align 4
	.global ifft
	.type	ifft, #function
	.proc	020
ifft:
	save	%sp, -104, %sp
	cmp	%i1, 1
	ble	.L34
	 sra	%i1, 1, %i3
	mov	%i0, %g2
	sll	%i3, 3, %i5
	mov	0, %g1
	add	%i2, %i5, %i5
	mov	0, %g3
.L32:
	ld	[%g2], %g4
	st	%g4, [%i2+%g1]
	add	%i2, %g1, %g4
	ld	[%g2+4], %i4
	st	%i4, [%g4+4]
	ld	[%g2+8], %g4
	st	%g4, [%i5+%g1]
	add	%i5, %g1, %g4
	ld	[%g2+12], %i4
	st	%i4, [%g4+4]
	add	%g3, 1, %g3
	add	%g2, 16, %g2
	cmp	%i3, %g3
	bg	.L32
	 add	%g1, 8, %g1
	mov	%i2, %o0
	mov	%i3, %o1
	call	ifft, 0
	 mov	%i0, %o2
	mov	%i5, %o0
	mov	%i3, %o1
	call	ifft, 0
	 mov	%i0, %o2
	mov	1, %o0
	st	%i1, [%sp+92]
	mov	0, %o1
	mov	1, %o2
	mov	%i0, %o3
	mov	%i5, %o4
	call	twiddle_factors, 0
	 mov	%i2, %o5
.L34:
	jmp	%i7+8
	 restore
	.size	ifft, .-ifft
	.align 4
	.global ifft_top
	.type	ifft_top, #function
	.proc	020
ifft_top:
	save	%sp, -112, %sp
	mov	0, %g1
	srl	%i1, 31, %i3
	mov	%i0, %g2
	add	%i3, %i1, %i3
	sra	%i3, 1, %i3
	sll	%i3, 3, %i4
	cmp	%i3, 0
	ble	.L39
	 add	%i2, %i4, %i5
.L41:
	ld	[%g2], %g3
	st	%g3, [%i2+%g1]
	add	%i2, %g1, %g3
	ld	[%g2+4], %g4
	st	%g4, [%g3+4]
	ld	[%g2+8], %g3
	st	%g3, [%i5+%g1]
	add	%i5, %g1, %g3
	ld	[%g2+12], %g4
	st	%g4, [%g3+4]
	add	%g1, 8, %g1
	cmp	%i4, %g1
	bne	.L41
	 add	%g2, 16, %g2
.L39:
	mov	%i0, %o3
	sethi	%hi(fft_args), %l0
	mov	%i3, %o1
	or	%l0, %lo(fft_args), %o0
	call	setXfftArgs, 0
	 mov	%i2, %o2
	sethi	%hi(tc), %l1
	or	%l0, %lo(fft_args), %o2
	or	%l1, %lo(tc), %o0
	sethi	%hi(ifft_thread), %o1
	call	scheduleChannelJob, 0
	 or	%o1, %lo(ifft_thread), %o1
	add	%i0, %i4, %o2
	mov	%i5, %o0
	mov	%i3, %o1
	call	ifft, 0
	 or	%l1, %lo(tc), %i4
	st	%g0, [%fp-4]
	mov	%i4, %o0
.L45:
	call	getChannelResponse, 0
	 add	%fp, -4, %o1
	cmp	%o0, 0
	bne	.L45
	 mov	%i4, %o0
	mov	0, %o3
	mov	2, %o4
	mov	%i0, %o5
	sethi	%hi(twiddle_args), %i3
	mov	1, %o1
	mov	%i1, %o2
	or	%i3, %lo(twiddle_args), %o0
	st	%i5, [%sp+92]
	call	setXtwiddleArgs, 0
	 st	%i2, [%sp+96]
	or	%i3, %lo(twiddle_args), %o2
	mov	%i4, %o0
	sethi	%hi(twiddle_factors_thread), %o1
	call	scheduleChannelJob, 0
	 or	%o1, %lo(twiddle_factors_thread), %o1
	mov	1, %o0
	st	%i1, [%sp+92]
	mov	1, %o1
	mov	2, %o2
	mov	%i0, %o3
	mov	%i5, %o4
	call	twiddle_factors, 0
	 mov	%i2, %o5
	st	%g0, [%fp-4]
	mov	%i4, %o0
.L46:
	call	getChannelResponse, 0
	 add	%fp, -4, %o1
	cmp	%o0, 0
	bne	.L46
	 mov	%i4, %o0
	jmp	%i7+8
	 restore
	.size	ifft_top, .-ifft_top
	.align 4
	.global setup
	.type	setup, #function
	.proc	020
setup:
	save	%sp, -96, %sp
	mov	0, %o2
	mov	1, %o0
	call	__ajit_serial_configure_via_vmap__, 0
	 mov	0, %o1
	sethi	%hi(80000000), %o1
	sethi	%hi(114688), %o0
	call	__ajit_serial_set_baudrate_via_vmap__, 0
	 or	%o0, 512, %o0
	mov	0, %o0
	sethi	%hi(tc), %i0
	call	__ajit_serial_set_uart_reset_via_vmap__, 0
	 mov	1, %i1
	call	initChannel, 0
	 restore %i0, %lo(tc), %o0
	.size	setup, .-setup
	.section	.rodata.cst8
	.align 8
.LC1:
	.long	1075388923
	.long	1413754136
	.align 8
.LC2:
	.long	1062207488
	.long	0
	.align 8
.LC3:
	.long	1069547520
	.long	0
	.align 8
.LC4:
	.long	1070805811
	.long	858993459
	.align 8
.LC5:
	.long	-1076677837
	.long	858993459
	.section	".text"
	.align 4
	.global set_values
	.type	set_values, #function
	.proc	020
set_values:
	save	%sp, -120, %sp
	sethi	%hi(.LC3), %l0
	sethi	%hi(vg), %i2
	sethi	%hi(.LC4), %i0
	sethi	%hi(v1g), %i3
	sethi	%hi(.LC5), %i1
	mov	0, %i5
	or	%l0, %lo(.LC3), %l0
	or	%i2, %lo(vg), %i2
	or	%i0, %lo(.LC4), %i0
	or	%i3, %lo(v1g), %i3
	or	%i1, %lo(.LC5), %i1
	st	%i5, [%fp-20]
.L51:
	ld	[%fp-20], %f10
	sethi	%hi(.LC1), %g1
	fitod	%f10, %f8
	ldd	[%g1+%lo(.LC1)], %f10
	sethi	%hi(.LC2), %g1
	fmuld	%f8, %f10, %f8
	ldd	[%g1+%lo(.LC2)], %f10
	fmuld	%f8, %f10, %f10
	std	%f10, [%fp-8]
	call	cos, 0
	 ldd	[%fp-8], %o0
	sll	%i5, 3, %i4
	ldd	[%l0], %f8
	fmuld	%f0, %f8, %f0
	fdtos	%f0, %f0
	st	%f0, [%i2+%i4]
	ldd	[%fp-8], %o0
	call	sin, 0
	 std	%f8, [%fp-16]
	ldd	[%fp-16], %f8
	add	%i2, %i4, %g1
	fmuld	%f0, %f8, %f0
	fdtos	%f0, %f8
	ldd	[%fp-8], %o0
	st	%f8, [%g1+4]
	call	cos, 0
	 nop
	ldd	[%i0], %f8
	fmuld	%f0, %f8, %f0
	fdtos	%f0, %f8
	ldd	[%fp-8], %o0
	st	%f8, [%i3+%i4]
	call	sin, 0
	 add	%i3, %i4, %i4
	ldd	[%i1], %f8
	fmuld	%f0, %f8, %f0
	fdtos	%f0, %f8
	st	%f8, [%i4+4]
	add	%i5, 1, %i5
	cmp	%i5, 1024
	bne,a	.L51
	 st	%i5, [%fp-20]
	jmp	%i7+8
	 restore
	.size	set_values, .-set_values
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC6:
	.asciz	"Single-thread fft "
	.align 8
.LC7:
	.asciz	"Single-thread ifft "
	.align 8
.LC8:
	.asciz	"Single thread Times: %f %f\n"
	.global __floatundidf
	.align 8
.LC9:
	.asciz	"Orig"
	.align 8
.LC10:
	.asciz	" FFT"
	.align 8
.LC11:
	.asciz	"iFFT"
	.align 8
.LC12:
	.asciz	"Times: %f %f %f %f\n"
	.section	".text"
	.align 4
	.global main_00
	.type	main_00, #function
	.proc	04
main_00:
	save	%sp, -176, %sp
	sethi	%hi(vg), %l6
	sethi	%hi(scratchg), %l7
	sethi	%hi(.LC6), %l5
	sethi	%hi(.LC7), %l4
	sethi	%hi(.LC8), %l3
	mov	16, %l2
	or	%l6, %lo(vg), %l6
	or	%l7, %lo(scratchg), %l7
	or	%l5, %lo(.LC6), %l5
	or	%l4, %lo(.LC7), %l4
	or	%l3, %lo(.LC8), %l3
.L53:
	call	set_values, 0
	 nop
	call	__ajit_get_clock_time, 0
	 nop
	mov	%l7, %o2
	mov	%o0, %i0
	mov	%o1, %i1
	mov	%l6, %o0
	call	fft, 0
	 mov	1024, %o1
	call	__ajit_get_clock_time, 0
	 nop
	mov	1024, %o2
	mov	%o0, %l0
	mov	%o1, %l1
	mov	%l5, %o0
	call	print_vector, 0
	 mov	%l6, %o1
	call	__ajit_get_clock_time, 0
	 nop
	mov	%l7, %o2
	mov	%o0, %i4
	mov	%o1, %i5
	mov	%l6, %o0
	call	ifft, 0
	 mov	1024, %o1
	call	__ajit_get_clock_time, 0
	 nop
	mov	1024, %o2
	mov	%o0, %i2
	mov	%o1, %i3
	mov	%l4, %o0
	call	print_vector, 0
	 mov	%l6, %o1
	subcc	%l1, %i1, %o1
	call	__floatundidf, 0
	 subx	%l0, %i0, %o0
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	subcc	%i3, %i5, %o1
	std	%f8, [%fp-40]
	call	__floatundidf, 0
	 subx	%i2, %i4, %o0
	ldd	[%fp-40], %f8
	std	%f8, [%fp-56]
	ldd	[%fp-56], %g2
	std	%f0, [%fp-56]
	mov	%g2, %o1
	mov	%g3, %o2
	ldd	[%fp-56], %g2
	mov	%l3, %o0
	mov	%g2, %o3
	call	cortos_printf, 0
	 mov	%g3, %o4
	addcc	%l2, -1, %l2
	bne	.L53
	 nop
	call	set_values, 0
	 sethi	%hi(.LC9), %i5
	mov	1024, %o2
	mov	%l6, %o1
	call	print_vector, 0
	 or	%i5, %lo(.LC9), %o0
	call	__ajit_get_clock_time, 0
	 nop
	mov	%l7, %o2
	mov	%o0, %l2
	mov	%o1, %l3
	mov	%l6, %o0
	call	fft_top, 0
	 mov	1024, %o1
	call	__ajit_get_clock_time, 0
	 nop
	sethi	%hi(.LC10), %g2
	mov	%o0, %l4
	st	%g2, [%fp-24]
	or	%g2, %lo(.LC10), %o0
	mov	%o1, %l5
	mov	1024, %o2
	call	print_vector, 0
	 mov	%l6, %o1
	call	__ajit_get_clock_time, 0
	 nop
	mov	%l7, %o2
	mov	%o0, %i0
	mov	%o1, %i1
	mov	%l6, %o0
	call	ifft_top, 0
	 mov	1024, %o1
	call	__ajit_get_clock_time, 0
	 nop
	sethi	%hi(.LC11), %g1
	mov	%o0, %l0
	st	%g1, [%fp-12]
	or	%g1, %lo(.LC11), %o0
	mov	%o1, %l1
	mov	1024, %o2
	call	print_vector, 0
	 mov	%l6, %o1
	sethi	%hi(v1g), %l6
	mov	1024, %o2
	or	%i5, %lo(.LC9), %o0
	call	print_vector, 0
	 or	%l6, %lo(v1g), %o1
	call	__ajit_get_clock_time, 0
	 nop
	mov	%l7, %o2
	mov	%o0, %i4
	mov	%o1, %i5
	or	%l6, %lo(v1g), %o0
	call	fft_top, 0
	 mov	1024, %o1
	call	__ajit_get_clock_time, 0
	 nop
	ld	[%fp-24], %g2
	mov	%o0, %i2
	mov	%o1, %i3
	or	%g2, %lo(.LC10), %o0
	mov	1024, %o2
	call	print_vector, 0
	 or	%l6, %lo(v1g), %o1
	call	__ajit_get_clock_time, 0
	 nop
	mov	%o0, %o4
	mov	%o1, %o5
	mov	%l7, %o2
	std	%o4, [%fp-32]
	or	%l6, %lo(v1g), %o0
	call	ifft_top, 0
	 mov	1024, %o1
	call	__ajit_get_clock_time, 0
	 nop
	ld	[%fp-12], %g1
	mov	%o0, %g2
	mov	%o1, %g3
	or	%g1, %lo(.LC11), %o0
	mov	1024, %o2
	std	%g2, [%fp-24]
	call	print_vector, 0
	 or	%l6, %lo(v1g), %o1
	subcc	%l5, %l3, %o1
	call	__floatundidf, 0
	 subx	%l4, %l2, %o0
	fmovs	%f0, %f10
	fmovs	%f1, %f11
	subcc	%l1, %i1, %o1
	std	%f10, [%fp-48]
	call	__floatundidf, 0
	 subx	%l0, %i0, %o0
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	subcc	%i3, %i5, %o1
	std	%f8, [%fp-40]
	call	__floatundidf, 0
	 subx	%i2, %i4, %o0
	ldd	[%fp-32], %o4
	ldd	[%fp-24], %g2
	st	%f0, [%fp-60]
	subcc	%g3, %o5, %o1
	ld	[%fp-60], %i5
	subx	%g2, %o4, %o0
	call	__floatundidf, 0
	 st	%f1, [%fp-60]
	ldd	[%fp-48], %f10
	std	%f0, [%fp-8]
	std	%f10, [%fp-56]
	ld	[%fp-8], %g1
	ldd	[%fp-56], %g2
	ldd	[%fp-40], %f8
	mov	%g2, %o1
	mov	%g3, %o2
	std	%f8, [%fp-56]
	st	%g1, [%sp+96]
	ldd	[%fp-56], %g2
	ld	[%fp-4], %g1
	ld	[%fp-60], %i4
	mov	%g2, %o3
	mov	%g3, %o4
	st	%g1, [%sp+100]
	mov	%i5, %g2
	mov	%i4, %g3
	std	%g2, [%fp-8]
	ld	[%fp-4], %g1
	mov	%i5, %o5
	st	%g1, [%sp+92]
	sethi	%hi(.LC12), %o0
	call	cortos_printf, 0
	 or	%o0, %lo(.LC12), %o0
	mov	1, %i0
	mov	0, %o1
	mov	0, %o2
	sethi	%hi(tc), %o0
	call	scheduleChannelJob, 0
	 or	%o0, %lo(tc), %o0
	jmp	%i7+8
	 restore
	.size	main_00, .-main_00
	.align 4
	.global main_01
	.type	main_01, #function
	.proc	04
main_01:
	save	%sp, -104, %sp
	sethi	%hi(tc), %i5
	or	%i5, %lo(tc), %i5
	mov	%i5, %i4
	add	%fp, -8, %o1
.L62:
	add	%fp, -4, %o2
	call	getChannelJob, 0
	 mov	%i5, %o0
	cmp	%o0, 0
	bne	.L62
	 add	%fp, -8, %o1
	ld	[%fp-8], %g1
	cmp	%g1, 0
	be	.L57
	 nop
	call	%g1, 0
	 ld	[%fp-4], %o0
	mov	%i4, %o0
	call	setChannelResponse, 0
	 ld	[%fp-4], %o1
	b	.L62
	 add	%fp, -8, %o1
.L57:
	jmp	%i7+8
	 restore %g0, 1, %o0
	.size	main_01, .-main_01
	.common	scratchg,8192,4
	.common	v1g,8192,4
	.common	vg,8192,4
	.common	twiddle_args,28,4
	.common	fft_args,12,4
	.common	tc,20,4
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
