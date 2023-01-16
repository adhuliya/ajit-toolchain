	.file	"main.c"
	.section	".text"
	.align 4
	.global runMarch
	.type	runMarch, #function
	.proc	020
runMarch:
	save	%sp, -96, %sp
	sethi	%hi(global_storage_matrix), %o7
	and	%i0, 1, %i3
	and	%i0, 6, %o5
	add	%i3, 1, %g4
	sll	%o5, 3, %o5
	sll	%i3, 5, %i3
	add	%o5, 16, %i1
	sll	%g4, 5, %g4
	mov	0, %i2
	or	%o7, %lo(global_storage_matrix), %o7
	cmp	%o5, %i1
.L16:
	bgeu	.L5
	 mov	%o5, %i4
	cmp	%g4, %i3
.L15:
	bleu,a	.L14
	 add	%i4, 1, %i4
	sll	%i4, 6, %g2
	add	%i4, %i2, %i5
	add	%g2, %i3, %g2
	mov	%i3, %g1
	sll	%g2, 2, %g2
	add	%g2, %o7, %g2
.L6:
	add	%g1, %i5, %g3
	st	%g3, [%g2]
	add	%g1, 1, %g1
	cmp	%g4, %g1
	bne	.L6
	 add	%g2, 4, %g2
	add	%i4, 1, %i4
.L14:
	cmp	%i1, %i4
	bne	.L15
	 cmp	%g4, %i3
.L5:
	add	%i2, 1, %i2
	cmp	%i2, 1000
	bne,a	.L16
	 cmp	%o5, %i1
	sll	%i0, 2, %i0
	mov	1, %g2
	sethi	%hi(done), %g1
	or	%g1, %lo(done), %g1
	st	%g2, [%g1+%i0]
	jmp	%i7+8
	 restore
	.size	runMarch, .-runMarch
	.align 4
	.global callfn
	.type	callfn, #function
	.proc	04
callfn:
	save	%sp, -96, %sp
	call	runMarch, 0
	 ld	[%i0], %o0
	jmp	%i7+8
	 restore
	.size	callfn, .-callfn
	.global __floatundidf
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.asciz	"Error in thread = %d\n"
	.align 8
.LC2:
	.asciz	"thread = %d sucess.\n"
	.align 8
.LC3:
	.asciz	"time taken for core %d is = %lf \n"
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	1045092338
	.long	2596056904
	.align 8
.LC4:
	.long	1083129856
	.long	0
	.section	".text"
	.align 4
	.global main_00
	.type	main_00, #function
	.proc	020
main_00:
	save	%sp, -112, %sp
	sethi	%hi(tc0), %i3
	mov	1, %o1
	call	initChannel, 0
	 or	%i3, %lo(tc0), %o0
	mov	1, %o1
	sethi	%hi(tc1), %o0
	call	initChannel, 0
	 or	%o0, %lo(tc1), %o0
	mov	1, %o1
	sethi	%hi(tc2), %o0
	call	initChannel, 0
	 or	%o0, %lo(tc2), %o0
	mov	1, %o1
	sethi	%hi(tc3), %o0
	call	initChannel, 0
	 or	%o0, %lo(tc3), %o0
	sethi	%hi(go_flag), %g1
	mov	1, %i2
	st	%i2, [%g1+%lo(go_flag)]
	call	cortos_get_clock_time, 0
	 nop
	add	%fp, -8, %o2
	mov	%o0, %i4
	mov	%o1, %i5
	or	%i3, %lo(tc0), %o0
	st	%i2, [%fp-8]
	sethi	%hi(callfn), %o1
	call	scheduleChannelJob, 0
	 or	%o1, %lo(callfn), %o1
	mov	0, %o0
	call	runMarch, 0
	 or	%i3, %lo(tc0), %i3
	mov	%i3, %o0
.L34:
	call	getChannelResponse, 0
	 add	%fp, -4, %o1
	cmp	%o0, 0
	bne,a	.L34
	 mov	%i3, %o0
	call	cortos_get_clock_time, 0
	 nop
	subcc	%o1, %i5, %o1
	call	__floatundidf, 0
	 subx	%o0, %i4, %o0
	sethi	%hi(.LC0), %g1
	sethi	%hi(time), %g2
	ldd	[%g1+%lo(.LC0)], %f8
	sethi	%hi(done), %g3
	fmuld	%f0, %f8, %f0
	mov	0, %g1
	std	%f0, [%g2+%lo(time)]
	or	%g3, %lo(done), %g3
.L32:
	sll	%g1, 2, %g2
	ld	[%g3+%g2], %g2
	cmp	%g2, 0
	be,a	.L32
	 mov	0, %g1
	add	%g1, 1, %g1
	cmp	%g1, 7
	ble	.L32
	 mov	0, %i5
	sethi	%hi(err_flg), %i4
	sethi	%hi(.LC2), %i3
	sethi	%hi(.LC1), %o0
	or	%i4, %lo(err_flg), %i4
	or	%i3, %lo(.LC2), %i3
	b	.L24
	 or	%o0, %lo(.LC1), %i2
.L22:
	call	cortos_printf, 0
	 mov	%i3, %o0
	add	%i5, 1, %i5
	cmp	%i5, 8
	be,a	.L35
	 sethi	%hi(time), %i3
.L24:
	sll	%i5, 2, %g1
.L36:
	ld	[%i4+%g1], %g1
	cmp	%g1, 1
	bne	.L22
	 mov	%i5, %o1
	call	cortos_printf, 0
	 mov	%i2, %o0
	add	%i5, 1, %i5
	cmp	%i5, 8
	bne	.L36
	 sll	%i5, 2, %g1
	sethi	%hi(time), %i3
.L35:
	sethi	%hi(.LC3), %i4
	mov	0, %i5
	or	%i3, %lo(time), %i3
	or	%i4, %lo(.LC3), %i4
	sll	%i5, 3, %g1
.L37:
	ldd	[%i3+%g1], %f8
	sethi	%hi(.LC4), %g1
	ldd	[%g1+%lo(.LC4)], %f10
	fdivd	%f8, %f10, %f10
	mov	%i5, %o1
	std	%f10, [%fp-16]
	mov	%i4, %o0
	call	cortos_printf, 0
	 ldd	[%fp-16], %o2
	add	%i5, 1, %i5
	cmp	%i5, 4
	bne	.L37
	 sll	%i5, 3, %g1
	jmp	%i7+8
	 restore
	.size	main_00, .-main_00
	.align 4
	.global main_01
	.type	main_01, #function
	.proc	020
main_01:
	save	%sp, -104, %sp
	sethi	%hi(tc0), %i5
	or	%i5, %lo(tc0), %i5
	mov	%i5, %o0
.L41:
	add	%fp, -8, %o1
	call	getChannelJob, 0
	 add	%fp, -4, %o2
	cmp	%o0, 0
	bne	.L41
	 mov	%i5, %o0
	ld	[%fp-8], %g1
	call	%g1, 0
	 ld	[%fp-4], %o0
	mov	4, %g1
	st	%g1, [%i5+16]
	jmp	%i7+8
	 restore
	.size	main_01, .-main_01
	.section	.rodata.cst8
	.align 8
.LC5:
	.long	1045092338
	.long	2596056904
	.section	".text"
	.align 4
	.global main_10
	.type	main_10, #function
	.proc	020
main_10:
	save	%sp, -104, %sp
	sethi	%hi(go_flag), %g2
	or	%g2, %lo(go_flag), %g2
.L43:
	ld	[%g2], %g1
	cmp	%g1, 0
	be	.L43
	 nop
	call	cortos_get_clock_time, 0
	 sethi	%hi(tc1), %i3
	mov	3, %g1
	add	%fp, -8, %o2
	st	%g1, [%fp-8]
	mov	%o0, %i4
	mov	%o1, %i5
	or	%i3, %lo(tc1), %o0
	sethi	%hi(callfn), %o1
	call	scheduleChannelJob, 0
	 or	%o1, %lo(callfn), %o1
	mov	2, %o0
	call	runMarch, 0
	 or	%i3, %lo(tc1), %i3
	mov	%i3, %o0
.L50:
	call	getChannelResponse, 0
	 add	%fp, -4, %o1
	cmp	%o0, 0
	bne,a	.L50
	 mov	%i3, %o0
	call	cortos_get_clock_time, 0
	 nop
	subcc	%o1, %i5, %o1
	call	__floatundidf, 0
	 subx	%o0, %i4, %o0
	sethi	%hi(.LC5), %g1
	ldd	[%g1+%lo(.LC5)], %f8
	sethi	%hi(time), %g1
	fmuld	%f0, %f8, %f0
	or	%g1, %lo(time), %g1
	std	%f0, [%g1+8]
	jmp	%i7+8
	 restore
	.size	main_10, .-main_10
	.align 4
	.global main_11
	.type	main_11, #function
	.proc	020
main_11:
	save	%sp, -104, %sp
	sethi	%hi(tc1), %i5
	or	%i5, %lo(tc1), %i5
	mov	%i5, %o0
.L54:
	add	%fp, -8, %o1
	call	getChannelJob, 0
	 add	%fp, -4, %o2
	cmp	%o0, 0
	bne	.L54
	 mov	%i5, %o0
	ld	[%fp-8], %g1
	call	%g1, 0
	 ld	[%fp-4], %o0
	mov	4, %g1
	st	%g1, [%i5+16]
	jmp	%i7+8
	 restore
	.size	main_11, .-main_11
	.section	.rodata.cst8
	.align 8
.LC6:
	.long	1045092338
	.long	2596056904
	.section	".text"
	.align 4
	.global main_20
	.type	main_20, #function
	.proc	020
main_20:
	save	%sp, -104, %sp
	sethi	%hi(go_flag), %g2
	or	%g2, %lo(go_flag), %g2
.L56:
	ld	[%g2], %g1
	cmp	%g1, 0
	be	.L56
	 nop
	call	cortos_get_clock_time, 0
	 sethi	%hi(tc2), %i3
	mov	5, %g1
	add	%fp, -8, %o2
	st	%g1, [%fp-8]
	mov	%o0, %i4
	mov	%o1, %i5
	or	%i3, %lo(tc2), %o0
	sethi	%hi(callfn), %o1
	call	scheduleChannelJob, 0
	 or	%o1, %lo(callfn), %o1
	mov	4, %o0
	call	runMarch, 0
	 or	%i3, %lo(tc2), %i3
	mov	%i3, %o0
.L63:
	call	getChannelResponse, 0
	 add	%fp, -4, %o1
	cmp	%o0, 0
	bne,a	.L63
	 mov	%i3, %o0
	call	cortos_get_clock_time, 0
	 nop
	subcc	%o1, %i5, %o1
	call	__floatundidf, 0
	 subx	%o0, %i4, %o0
	sethi	%hi(.LC6), %g1
	ldd	[%g1+%lo(.LC6)], %f8
	sethi	%hi(time), %g1
	fmuld	%f0, %f8, %f0
	or	%g1, %lo(time), %g1
	std	%f0, [%g1+16]
	jmp	%i7+8
	 restore
	.size	main_20, .-main_20
	.align 4
	.global main_21
	.type	main_21, #function
	.proc	020
main_21:
	save	%sp, -104, %sp
	sethi	%hi(tc2), %i5
	or	%i5, %lo(tc2), %i5
	mov	%i5, %o0
.L67:
	add	%fp, -8, %o1
	call	getChannelJob, 0
	 add	%fp, -4, %o2
	cmp	%o0, 0
	bne	.L67
	 mov	%i5, %o0
	ld	[%fp-8], %g1
	call	%g1, 0
	 ld	[%fp-4], %o0
	mov	4, %g1
	st	%g1, [%i5+16]
	jmp	%i7+8
	 restore
	.size	main_21, .-main_21
	.section	.rodata.cst8
	.align 8
.LC7:
	.long	1045092338
	.long	2596056904
	.section	".text"
	.align 4
	.global main_30
	.type	main_30, #function
	.proc	020
main_30:
	save	%sp, -104, %sp
	sethi	%hi(go_flag), %g2
	or	%g2, %lo(go_flag), %g2
.L69:
	ld	[%g2], %g1
	cmp	%g1, 0
	be	.L69
	 nop
	call	cortos_get_clock_time, 0
	 sethi	%hi(tc3), %i3
	mov	7, %g1
	add	%fp, -8, %o2
	st	%g1, [%fp-8]
	mov	%o0, %i4
	mov	%o1, %i5
	or	%i3, %lo(tc3), %o0
	sethi	%hi(callfn), %o1
	call	scheduleChannelJob, 0
	 or	%o1, %lo(callfn), %o1
	mov	6, %o0
	call	runMarch, 0
	 or	%i3, %lo(tc3), %i3
	mov	%i3, %o0
.L76:
	call	getChannelResponse, 0
	 add	%fp, -4, %o1
	cmp	%o0, 0
	bne,a	.L76
	 mov	%i3, %o0
	call	cortos_get_clock_time, 0
	 nop
	subcc	%o1, %i5, %o1
	call	__floatundidf, 0
	 subx	%o0, %i4, %o0
	sethi	%hi(.LC7), %g1
	ldd	[%g1+%lo(.LC7)], %f8
	sethi	%hi(time), %g1
	fmuld	%f0, %f8, %f0
	or	%g1, %lo(time), %g1
	std	%f0, [%g1+24]
	jmp	%i7+8
	 restore
	.size	main_30, .-main_30
	.align 4
	.global main_31
	.type	main_31, #function
	.proc	020
main_31:
	save	%sp, -104, %sp
	sethi	%hi(tc3), %i5
	or	%i5, %lo(tc3), %i5
	mov	%i5, %o0
.L80:
	add	%fp, -8, %o1
	call	getChannelJob, 0
	 add	%fp, -4, %o2
	cmp	%o0, 0
	bne	.L80
	 mov	%i5, %o0
	ld	[%fp-8], %g1
	call	%g1, 0
	 ld	[%fp-4], %o0
	mov	4, %g1
	st	%g1, [%i5+16]
	jmp	%i7+8
	 restore
	.size	main_31, .-main_31
	.global err_flg
	.section	".bss"
	.align 4
	.type	err_flg, #object
	.size	err_flg, 32
err_flg:
	.skip	32
	.global time
	.align 8
	.type	time, #object
	.size	time, 32
time:
	.skip	32
	.global count
	.align 4
	.type	count, #object
	.size	count, 32
count:
	.skip	32
	.global go_flag
	.align 4
	.type	go_flag, #object
	.size	go_flag, 4
go_flag:
	.skip	4
	.global done
	.align 4
	.type	done, #object
	.size	done, 32
done:
	.skip	32
	.global init_done
	.align 4
	.type	init_done, #object
	.size	init_done, 4
init_done:
	.skip	4
	.common	tc3,20,4
	.common	tc2,20,4
	.common	tc1,20,4
	.common	tc0,20,4
	.common	global_storage_matrix,16384,4
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
