	.file	"utils.c"
	.section	".text"
	.align 4
	.global setXfftArgs
	.type	setXfftArgs, #function
	.proc	020
setXfftArgs:
	st	%o1, [%o0]
	st	%o2, [%o0+4]
	jmp	%o7+8
	 st	%o3, [%o0+8]
	.size	setXfftArgs, .-setXfftArgs
	.align 4
	.global setXtwiddleArgs
	.type	setXtwiddleArgs, #function
	.proc	020
setXtwiddleArgs:
	ld	[%sp+92], %g1
	st	%o1, [%o0]
	st	%g1, [%o0+20]
	st	%o2, [%o0+4]
	ld	[%sp+96], %g1
	st	%o3, [%o0+8]
	st	%o4, [%o0+12]
	st	%o5, [%o0+16]
	jmp	%o7+8
	 st	%g1, [%o0+24]
	.size	setXtwiddleArgs, .-setXtwiddleArgs
	.align 4
	.global twiddle_factors_thread
	.type	twiddle_factors_thread, #function
	.proc	020
twiddle_factors_thread:
	save	%sp, -104, %sp
	ld	[%i0+4], %g1
	ld	[%i0], %o0
	st	%g1, [%sp+92]
	ld	[%i0+8], %o1
	ld	[%i0+12], %o2
	ld	[%i0+16], %o3
	ld	[%i0+20], %o4
	call	twiddle_factors, 0
	 ld	[%i0+24], %o5
	jmp	%i7+8
	 restore
	.size	twiddle_factors_thread, .-twiddle_factors_thread
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.asciz	"%s (dim=%d):"
	.align 8
.LC1:
	.asciz	"\n"
	.align 8
.LC2:
	.asciz	" %5.2f,%5.2f "
	.section	".text"
	.align 4
	.global print_vector
	.type	print_vector, #function
	.proc	020
print_vector:
	save	%sp, -104, %sp
	sethi	%hi(.LC0), %o0
	mov	%i0, %o1
	or	%o0, %lo(.LC0), %o0
	call	cortos_printf, 0
	 mov	%i2, %o2
	sethi	%hi(.LC2), %i4
	mov	0, %i5
	cmp	%i2, 0
	ble	.L7
	 or	%i4, %lo(.LC2), %i4
.L8:
	ld	[%i1+4], %f8
	ld	[%i1], %f10
	fstod	%f10, %f10
	std	%f10, [%fp-8]
	ldd	[%fp-8], %g2
	fstod	%f8, %f8
	mov	%g2, %o1
	mov	%g3, %o2
	std	%f8, [%fp-8]
	ldd	[%fp-8], %g2
	mov	%i4, %o0
	mov	%g2, %o3
	call	cortos_printf, 0
	 mov	%g3, %o4
	add	%i5, 1, %i5
	cmp	%i5, %i2
	bne	.L8
	 add	%i1, 8, %i1
.L7:
	sethi	%hi(.LC1), %i0
	call	cortos_printf, 0
	 restore %i0, %lo(.LC1), %o0
	.size	print_vector, .-print_vector
	.align 4
	.global fft_thread
	.type	fft_thread, #function
	.proc	020
fft_thread:
	mov	%o0, %g1
	ld	[%o0+4], %o0
	ld	[%g1], %o1
	ld	[%g1+8], %o2
	or	%o7, %g0, %g1
	call	fft, 0
	 or	%g1, %g0, %o7
	.size	fft_thread, .-fft_thread
	.align 4
	.global ifft_thread
	.type	ifft_thread, #function
	.proc	020
ifft_thread:
	mov	%o0, %g1
	ld	[%o0+4], %o0
	ld	[%g1], %o1
	ld	[%g1+8], %o2
	or	%o7, %g0, %g1
	call	ifft, 0
	 or	%g1, %g0, %o7
	.size	ifft_thread, .-ifft_thread
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
