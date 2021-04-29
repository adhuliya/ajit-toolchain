	.file	"core_main.c"
	.section	".text"
	.align 4
	.global iterate
	.type	iterate, #function
	.proc	0120
iterate:
	save	%sp, -96, %sp
	sth	%g0, [%i0+56]
	sth	%g0, [%i0+58]
	sth	%g0, [%i0+60]
	sth	%g0, [%i0+62]
	ld	[%i0+28], %i4
	cmp	%i4, 0
	be	.L8
	 mov	0, %i5
	mov	1, %o1
.L10:
	call	core_bench_list, 0
	 mov	%i0, %o0
	lduh	[%i0+56], %o1
	sll	%o0, 16, %o0
	call	crcu16, 0
	 srl	%o0, 16, %o0
	mov	-1, %o1
	sth	%o0, [%i0+56]
	call	core_bench_list, 0
	 mov	%i0, %o0
	lduh	[%i0+56], %o1
	sll	%o0, 16, %o0
	call	crcu16, 0
	 srl	%o0, 16, %o0
	cmp	%i5, 0
	bne	.L3
	 sth	%o0, [%i0+56]
	sth	%o0, [%i0+58]
.L3:
	add	%i5, 1, %i5
	cmp	%i5, %i4
	bne	.L10
	 mov	1, %o1
.L8:
	jmp	%i7+8
	 restore %g0, 0, %o0
	.size	iterate, .-iterate
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC2:
	.asciz	"Note: iterations = %lu!\n"
	.align 8
.LC3:
	.asciz	"6k performance run parameters for coremark.\n"
	.align 8
.LC4:
	.asciz	"6k validation run parameters for coremark.\n"
	.align 8
.LC5:
	.asciz	"Profile generation run parameters for coremark.\n"
	.align 8
.LC6:
	.asciz	"2K performance run parameters for coremark.\n"
	.align 8
.LC7:
	.asciz	"2K validation run parameters for coremark.\n"
	.align 8
.LC8:
	.asciz	"[%u]ERROR! list crc 0x%04x - should be 0x%04x\n"
	.align 8
.LC9:
	.asciz	"[%u]ERROR! matrix crc 0x%04x - should be 0x%04x\n"
	.align 8
.LC10:
	.asciz	"[%u]ERROR! state crc 0x%04x - should be 0x%04x\n"
	.align 8
.LC11:
	.asciz	"CoreMark Size    : %lu\n"
	.align 8
.LC12:
	.asciz	"Total ticks      : %lu\n"
	.align 8
.LC13:
	.asciz	"Total time (secs): %f\n"
	.align 8
.LC16:
	.asciz	"Iterations/Sec   : %f\n"
	.align 8
.LC18:
	.asciz	"ERROR! Must execute for at least 10 secs for a valid result!\n"
	.align 8
.LC19:
	.asciz	"Iterations       : %lu\n"
	.align 8
.LC20:
	.asciz	"Compiler version : %s\n"
	.align 8
.LC21:
	.asciz	"sparc-linux-gcc 4.7.4"
	.align 8
.LC22:
	.asciz	"Compiler flags   : %s\n"
	.align 8
.LC23:
	.asciz	" -m32 -mcpu=v8 -nostdlib -ffreestanding -O3 -funroll-loops -fgcse-sm "
	.align 8
.LC24:
	.asciz	"Memory location  : %s\n"
	.align 8
.LC25:
	.asciz	"STATIC"
	.align 8
.LC26:
	.asciz	"seedcrc          : 0x%04x\n"
	.align 8
.LC27:
	.asciz	"[%d]crclist       : 0x%04x\n"
	.align 8
.LC28:
	.asciz	"[%d]crcmatrix     : 0x%04x\n"
	.align 8
.LC29:
	.asciz	"[%d]crcstate      : 0x%04x\n"
	.align 8
.LC30:
	.asciz	"[%d]crcfinal      : 0x%04x\n"
	.align 8
.LC31:
	.asciz	"Correct operation validated. See readme.txt for run and reporting rules.\n"
	.align 8
.LC32:
	.asciz	"CoreMark 1.0 : %f / %s %s"
	.align 8
.LC33:
	.asciz	" / %s"
	.align 8
.LC34:
	.asciz	"\n"
	.align 8
.LC35:
	.asciz	"Errors detected\n"
	.align 8
.LC36:
	.asciz	"Cannot validate operation for these seed values, please compare with results on a known platform.\n"
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	1072693248
	.long	0
	.align 8
.LC1:
	.long	1105199104
	.long	0
	.align 8
.LC14:
	.long	0
	.long	0
	.align 8
.LC15:
	.long	1106247680
	.long	0
	.align 8
.LC17:
	.long	1076101120
	.long	0
	.section	".text"
	.align 4
	.global ajit_main
	.type	ajit_main, #function
	.proc	020
ajit_main:
	save	%sp, -2200, %sp
	call	portable_init, 0
	 add	%fp, -2006, %o0
	call	get_seed_32, 0
	 mov	1, %o0
	sth	%o0, [%fp-2072]
	call	get_seed_32, 0
	 mov	2, %o0
	sth	%o0, [%fp-2070]
	call	get_seed_32, 0
	 mov	3, %o0
	sth	%o0, [%fp-2068]
	call	get_seed_32, 0
	 mov	4, %o0
	st	%o0, [%fp-2044]
	call	get_seed_32, 0
	 mov	5, %o0
	orcc	%o0, 0, %g1
	be,a	.L12
	 mov	7, %g1
	and	%g1, 1, %g4
	st	%g1, [%fp-2040]
	mov	%g4, %i3
.L13:
	ld	[%fp-2072], %g2
	cmp	%g2, 0
	bne	.L151
	 sethi	%hi(65536), %g3
	ldsh	[%fp-2068], %g2
	cmp	%g2, 0
	be,a	.L133
	 sth	%g0, [%fp-2072]
	subcc	%g0, %g4, %g0
.L163:
	add	%fp, -2000, %g2
	sth	%g0, [%fp-2008]
	st	%g2, [%fp-2064]
	addx	%g0, 0, %i5
	andcc	%g1, 2, %g2
	bne	.L21
	 add	%i5, 1, %g3
	mov	%i5, %g3
.L21:
	andcc	%g1, 4, %i5
	be	.L23
	 add	%g3, 1, %i4
	mov	%i4, %g3
.L23:
	sll	%g3, 16, %g3
	mov	2000, %i4
	srl	%g3, 16, %g3
	wr	%g0, 0, %y
	nop
	nop
	nop
	udiv	%i4, %g3, %o0
	st	%o0, [%fp-2048]
	cmp	%g4, 0
	be	.L24
	 mov	0, %g3
	ld	[%fp-2064], %g4
	mov	1, %g3
	st	%g4, [%fp-2060]
.L24:
	cmp	%g2, 0
	be	.L152
	 cmp	%i5, 0
	sll	%g3, 16, %g4
	ld	[%fp-2064], %i4
	srl	%g4, 16, %g4
	add	%g3, 1, %g3
	smul	%g4, %o0, %g4
	add	%i4, %g4, %g4
	st	%g4, [%fp-2056]
.L152:
	be	.L153
	 cmp	%i3, 0
	sll	%g3, 16, %g3
	ld	[%fp-2064], %g4
	srl	%g3, 16, %g3
	smul	%g3, %o0, %g3
	add	%g4, %g3, %g3
	st	%g3, [%fp-2052]
.L153:
	be	.L154
	 cmp	%g2, 0
	ld	[%fp-2060], %o1
	call	core_list_init, 0
	 ldsh	[%fp-2072], %o2
	ld	[%fp-2040], %g1
	st	%o0, [%fp-2036]
	and	%g1, 2, %g2
	cmp	%g2, 0
.L154:
	bne,a	.L134
	 ldsh	[%fp-2072], %g1
.L28:
	andcc	%g1, 4, %g0
	bne	.L135
	 ld	[%fp-2048], %o0
	ld	[%fp-2044], %g1
.L147:
	cmp	%g1, 0
	be	.L136
	 sethi	%hi(.LC0), %i3
.L30:
	call	start_time, 0
	 mov	0, %i5
	call	get_seed_32, 0
	 mov	4, %o0
	sth	%g0, [%fp-2016]
	st	%o0, [%fp-2044]
	sth	%g0, [%fp-2014]
	sth	%g0, [%fp-2012]
	sth	%g0, [%fp-2010]
	cmp	%o0, 0
	be	.L49
	 mov	%o0, %i4
	mov	1, %o1
.L155:
	call	core_bench_list, 0
	 add	%fp, -2072, %o0
	lduh	[%fp-2016], %o1
	sll	%o0, 16, %o0
	call	crcu16, 0
	 srl	%o0, 16, %o0
	mov	-1, %o1
	sth	%o0, [%fp-2016]
	call	core_bench_list, 0
	 add	%fp, -2072, %o0
	lduh	[%fp-2016], %o1
	sll	%o0, 16, %o0
	call	crcu16, 0
	 srl	%o0, 16, %o0
	cmp	%i5, 0
	bne	.L48
	 sth	%o0, [%fp-2016]
	sth	%o0, [%fp-2014]
.L48:
	add	%i5, 1, %i5
	cmp	%i4, %i5
	bne,a	.L155
	 mov	1, %o1
.L49:
	call	stop_time, 0
	 nop
	call	get_time, 0
	 nop
	mov	0, %o1
	mov	%o0, %i2
	call	crc16, 0
	 ldsh	[%fp-2072], %o0
	sll	%o0, 16, %o1
	ldsh	[%fp-2070], %o0
	call	crc16, 0
	 srl	%o1, 16, %o1
	sll	%o0, 16, %o1
	ldsh	[%fp-2068], %o0
	call	crc16, 0
	 srl	%o1, 16, %o1
	sll	%o0, 16, %o1
	ldsh	[%fp-2046], %o0
	call	crc16, 0
	 srl	%o1, 16, %o1
	sll	%o0, 16, %o0
	sethi	%hi(30720), %g2
	srl	%o0, 16, %g1
	or	%g2, 773, %g2
	cmp	%g1, %g2
	be	.L44
	 st	%o0, [%fp-2076]
	cmp	%g1, %g2
	bleu	.L137
	 sethi	%hi(6144), %g2
	sethi	%hi(34816), %g2
	or	%g2, 514, %g2
	cmp	%g1, %g2
	be	.L45
	 sethi	%hi(59392), %g2
	or	%g2, 501, %g2
	cmp	%g1, %g2
	be	.L138
	 mov	3, %g3
	mov	-1, %g2
.L164:
	mov	-1, %i5
	sth	%g2, [%fp-2082]
	sethi	%hi(default_num_contexts), %i1
.L41:
	call	check_data_types, 0
	 nop
	and	%o0, 0xff, %o0
	ld	[%fp-2048], %o1
	add	%o0, %i5, %i5
	sethi	%hi(.LC11), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC11), %o0
	mov	%i2, %o1
	sethi	%hi(.LC12), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC12), %o0
	call	time_in_secs, 0
	 mov	%i2, %o0
	std	%f0, [%fp-2104]
	ldd	[%fp-2104], %g2
	sethi	%hi(.LC13), %o0
	mov	%g2, %o1
	mov	%g3, %o2
	call	ee_printf, 0
	 or	%o0, %lo(.LC13), %o0
	call	time_in_secs, 0
	 mov	%i2, %o0
	sethi	%hi(.LC14), %g1
	ldd	[%g1+%lo(.LC14)], %f8
	fcmped	%f0, %f8
	nop
	fbule	.L57
	 mov	%i5, %i3
	ld	[%i1+%lo(default_num_contexts)], %g2
	ld	[%fp-2044], %g1
	smul	%g2, %g1, %g1
	st	%g1, [%fp-2080]
	cmp	%g1, 0
	ld	[%fp-2080], %f10
	bl	.L139
	 fitod	%f10, %f8
.L59:
	mov	%i2, %o0
	call	time_in_secs, 0
	 std	%f8, [%fp-2096]
	ldd	[%fp-2096], %f8
	fdivd	%f8, %f0, %f0
	std	%f0, [%fp-2104]
	ldd	[%fp-2104], %g2
	sethi	%hi(.LC16), %o0
	mov	%g2, %o1
	or	%o0, %lo(.LC16), %o0
	call	ee_printf, 0
	 mov	%g3, %o2
.L57:
	call	time_in_secs, 0
	 mov	%i2, %o0
	sethi	%hi(.LC17), %g1
	ldd	[%g1+%lo(.LC17)], %f8
	fcmped	%f0, %f8
	nop
	fbl,a	.L140
	 add	%i5, 1, %i3
	ld	[%fp-2044], %g1
.L149:
	ld	[%i1+%lo(default_num_contexts)], %o1
	sethi	%hi(.LC19), %o0
	smul	%o1, %g1, %o1
	call	ee_printf, 0
	 or	%o0, %lo(.LC19), %o0
	sethi	%hi(.LC21), %i0
	sethi	%hi(.LC20), %o0
	or	%i0, %lo(.LC21), %o1
	call	ee_printf, 0
	 or	%o0, %lo(.LC20), %o0
	sethi	%hi(.LC23), %l0
	sethi	%hi(.LC22), %o0
	or	%l0, %lo(.LC23), %o1
	call	ee_printf, 0
	 or	%o0, %lo(.LC22), %o0
	sethi	%hi(.LC25), %l1
	sethi	%hi(.LC24), %o0
	or	%l1, %lo(.LC25), %o1
	call	ee_printf, 0
	 or	%o0, %lo(.LC24), %o0
	ld	[%fp-2076], %g3
	sethi	%hi(.LC26), %o0
	srl	%g3, 16, %o1
	call	ee_printf, 0
	 or	%o0, %lo(.LC26), %o0
	ld	[%fp-2040], %g2
	andcc	%g2, 1, %g0
	be	.L63
	 ld	[%i1+%lo(default_num_contexts)], %g1
	cmp	%g1, 0
	be	.L64
	 sethi	%hi(default_num_contexts), %i5
	sethi	%hi(.LC27), %l3
	mov	0, %i4
	or	%i5, %lo(default_num_contexts), %i5
	or	%l3, %lo(.LC27), %l3
	sll	%i4, 16, %o1
.L156:
	srl	%o1, 16, %o1
	sll	%o1, 2, %g2
	sll	%o1, 6, %g1
	add	%g2, %g1, %g1
	add	%fp, %g1, %g1
	mov	%l3, %o0
	call	ee_printf, 0
	 lduh	[%g1-2014], %o2
	add	%i4, 1, %i4
	ld	[%i5], %g1
	sll	%i4, 16, %g2
	srl	%g2, 16, %g2
	cmp	%g2, %g1
	blu	.L156
	 sll	%i4, 16, %o1
	ld	[%fp-2040], %g2
.L63:
	andcc	%g2, 2, %g0
	be	.L157
	 andcc	%g2, 4, %g0
	cmp	%g1, 0
	be,a	.L150
	 sll	%i3, 16, %i3
	sethi	%hi(default_num_contexts), %i5
	sethi	%hi(.LC28), %l3
	mov	0, %i4
	or	%i5, %lo(default_num_contexts), %i5
	or	%l3, %lo(.LC28), %l3
	sll	%i4, 16, %o1
.L158:
	srl	%o1, 16, %o1
	sll	%o1, 2, %g2
	sll	%o1, 6, %g1
	add	%g2, %g1, %g1
	add	%fp, %g1, %g1
	mov	%l3, %o0
	call	ee_printf, 0
	 lduh	[%g1-2012], %o2
	add	%i4, 1, %i4
	ld	[%i5], %g1
	sll	%i4, 16, %g2
	srl	%g2, 16, %g2
	cmp	%g2, %g1
	blu	.L158
	 sll	%i4, 16, %o1
	ld	[%fp-2040], %g2
.L66:
	andcc	%g2, 4, %g0
.L157:
	be	.L159
	 cmp	%g1, 0
	be,a	.L150
	 sll	%i3, 16, %i3
	sethi	%hi(default_num_contexts), %i5
	sethi	%hi(.LC29), %l3
	mov	0, %i4
	or	%i5, %lo(default_num_contexts), %i5
	or	%l3, %lo(.LC29), %l3
	sll	%i4, 16, %o1
.L160:
	srl	%o1, 16, %o1
	sll	%o1, 2, %g2
	sll	%o1, 6, %g1
	add	%g2, %g1, %g1
	add	%fp, %g1, %g1
	mov	%l3, %o0
	call	ee_printf, 0
	 lduh	[%g1-2010], %o2
	add	%i4, 1, %i4
	ld	[%i5], %g1
	sll	%i4, 16, %g2
	srl	%g2, 16, %g2
	cmp	%g2, %g1
	blu,a	.L160
	 sll	%i4, 16, %o1
	cmp	%g1, 0
.L159:
	be,a	.L150
	 sll	%i3, 16, %i3
	sethi	%hi(default_num_contexts), %i5
	sethi	%hi(.LC30), %l3
	mov	0, %i4
	or	%i5, %lo(default_num_contexts), %i5
	or	%l3, %lo(.LC30), %l3
	sll	%i4, 16, %o1
.L161:
	srl	%o1, 16, %o1
	sll	%o1, 2, %g2
	sll	%o1, 6, %g1
	add	%g2, %g1, %g1
	add	%fp, %g1, %g1
	mov	%l3, %o0
	call	ee_printf, 0
	 lduh	[%g1-2016], %o2
	add	%i4, 1, %i4
	ld	[%i5], %g1
	sll	%i4, 16, %g2
	srl	%g2, 16, %g2
	cmp	%g2, %g1
	blu,a	.L161
	 sll	%i4, 16, %o1
	sll	%i3, 16, %i3
.L150:
	sra	%i3, 16, %i3
	cmp	%i3, 0
	be,a	.L141
	 sethi	%hi(.LC31), %o0
	ble,a	.L77
	 sethi	%hi(.LC36), %o0
	sethi	%hi(.LC35), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC35), %o0
.L78:
	call	portable_fini, 0
	 add	%fp, -2006, %o0
	jmp	%i7+8
	 restore
.L136:
	mov	1, %g1
	or	%i3, %lo(.LC0), %i3
.L36:
	add	%g1, %g1, %g2
	sll	%g1, 3, %g1
	add	%g2, %g1, %g1
	call	start_time, 0
	 st	%g1, [%fp-2044]
	sth	%g0, [%fp-2016]
	sth	%g0, [%fp-2014]
	sth	%g0, [%fp-2012]
	sth	%g0, [%fp-2010]
	ld	[%fp-2044], %i4
	cmp	%i4, 0
	be	.L35
	 mov	0, %i5
	mov	1, %o1
.L162:
	call	core_bench_list, 0
	 add	%fp, -2072, %o0
	lduh	[%fp-2016], %o1
	sll	%o0, 16, %o0
	call	crcu16, 0
	 srl	%o0, 16, %o0
	mov	-1, %o1
	sth	%o0, [%fp-2016]
	call	core_bench_list, 0
	 add	%fp, -2072, %o0
	lduh	[%fp-2016], %o1
	sll	%o0, 16, %o0
	call	crcu16, 0
	 srl	%o0, 16, %o0
	cmp	%i5, 0
	bne	.L34
	 sth	%o0, [%fp-2016]
	sth	%o0, [%fp-2014]
.L34:
	add	%i5, 1, %i5
	cmp	%i5, %i4
	bne	.L162
	 mov	1, %o1
.L35:
	call	stop_time, 0
	 nop
	call	get_time, 0
	 nop
	call	time_in_secs, 0
	 nop
	ldd	[%i3], %f8
	fcmped	%f0, %f8
	nop
	fbuge	.L142
	 nop
	b	.L36
	 ld	[%fp-2044], %g1
.L135:
	ldsh	[%fp-2072], %o1
	call	core_init_state, 0
	 ld	[%fp-2052], %o2
	b	.L147
	 ld	[%fp-2044], %g1
.L134:
	ldsh	[%fp-2070], %o2
	ld	[%fp-2048], %o0
	sll	%o2, 16, %o2
	ld	[%fp-2056], %o1
	or	%o2, %g1, %o2
	call	core_init_matrix, 0
	 add	%fp, -2032, %o3
	b	.L28
	 ld	[%fp-2040], %g1
.L133:
	sth	%g0, [%fp-2070]
	mov	102, %g3
	ld	[%fp-2072], %g2
	sth	%g3, [%fp-2068]
	sethi	%hi(65536), %g3
.L151:
	cmp	%g2, %g3
	bne	.L163
	 subcc	%g0, %g4, %g0
	ldsh	[%fp-2068], %g2
	cmp	%g2, 0
	bne	.L163
	 subcc	%g0, %g4, %g0
	sethi	%hi(13312), %g2
	mov	102, %g3
	or	%g2, 21, %g2
	sth	%g3, [%fp-2068]
	sth	%g2, [%fp-2072]
	b	.L163
	 sth	%g2, [%fp-2070]
.L142:
	sethi	%hi(.LC1), %g1
	ldd	[%g1+%lo(.LC1)], %f8
	fcmped	%f0, %f8
	nop
	fbul	.L143
	 nop
	fsubd	%f0, %f8, %f8
	sethi	%hi(-2147483648), %g2
	fdtoi	%f8, %f10
	st	%f10, [%fp-2080]
	ld	[%fp-2080], %g1
	xor	%g1, %g2, %g1
.L38:
	cmp	%g1, 0
	be,a	.L39
	 mov	1, %g1
.L39:
	mov	10, %g2
	wr	%g0, 0, %y
	nop
	nop
	nop
	udiv	%g2, %g1, %o1
	ld	[%fp-2044], %g1
	sethi	%hi(.LC2), %o0
	add	%o1, 1, %o1
	or	%o0, %lo(.LC2), %o0
	smul	%o1, %g1, %o1
	call	ee_printf, 0
	 st	%o1, [%fp-2044]
	b,a	.L30
.L12:
	mov	1, %i3
	st	%g1, [%fp-2040]
	b	.L13
	 mov	1, %g4
.L137:
	or	%g2, 242, %g2
	cmp	%g1, %g2
	be	.L42
	 sethi	%hi(19456), %g2
	or	%g2, 687, %g2
	cmp	%g1, %g2
	bne	.L164
	 mov	-1, %g2
	mov	2, %g2
	sethi	%hi(.LC5), %o0
	mov	2, %l2
	or	%o0, %lo(.LC5), %o0
	call	ee_printf, 0
	 sth	%g2, [%fp-2082]
	sethi	%hi(default_num_contexts), %i1
.L148:
	ld	[%i1+%lo(default_num_contexts)], %g1
	cmp	%g1, 0
	be	.L41
	 mov	0, %i5
	mov	0, %l3
	mov	0, %l7
	or	%i1, %lo(default_num_contexts), %i5
	sethi	%hi(list_known_crc), %l1
	sethi	%hi(matrix_known_crc), %l0
	b	.L56
	 sethi	%hi(state_known_crc), %i0
.L145:
	add	%fp, %g4, %g4
	lduh	[%g4-2008], %g1
.L54:
	add	%l7, 1, %l7
	add	%g1, %l3, %g1
	sll	%l7, 16, %g4
	ld	[%i5], %g3
	srl	%g4, 16, %g4
	cmp	%g4, %g3
	bgeu	.L144
	 mov	%g1, %l3
.L56:
	sll	%l7, 16, %i3
	srl	%i3, 16, %i3
	sll	%i3, 2, %l6
	sll	%i3, 6, %l5
	add	%l6, %l5, %l4
	add	%fp, %l4, %i4
	sth	%g0, [%i4-2008]
	ld	[%i4-2040], %g1
	andcc	%g1, 1, %g0
	be	.L165
	 andcc	%g1, 2, %g0
	or	%l1, %lo(list_known_crc), %o3
	add	%l2, %l2, %o7
	lduh	[%i4-2014], %o2
	lduh	[%o3+%o7], %o3
	cmp	%o2, %o3
	be	.L51
	 mov	%i3, %o1
	sethi	%hi(.LC8), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC8), %o0
	lduh	[%i4-2008], %o7
	ld	[%i4-2040], %g1
	add	%o7, 1, %o7
	sth	%o7, [%i4-2008]
.L51:
	andcc	%g1, 2, %g0
.L165:
	be	.L166
	 andcc	%g1, 4, %g0
	add	%fp, %l4, %i4
	or	%l0, %lo(matrix_known_crc), %o3
	add	%l2, %l2, %o7
	lduh	[%i4-2012], %o2
	lduh	[%o3+%o7], %o3
	cmp	%o2, %o3
	be	.L52
	 mov	%i3, %o1
	sethi	%hi(.LC9), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC9), %o0
	lduh	[%i4-2008], %o7
	ld	[%i4-2040], %g1
	add	%o7, 1, %o7
	sth	%o7, [%i4-2008]
.L52:
	andcc	%g1, 4, %g0
.L166:
	be	.L145
	 add	%l6, %l5, %g4
	add	%fp, %l4, %i4
	or	%i0, %lo(state_known_crc), %g3
	add	%l2, %l2, %g1
	lduh	[%i4-2010], %o2
	lduh	[%g3+%g1], %o3
	cmp	%o2, %o3
	bne,a	.L55
	 sethi	%hi(.LC10), %o0
	lduh	[%i4-2008], %g1
	add	%l7, 1, %l7
	add	%g1, %l3, %g1
	sll	%l7, 16, %g4
	ld	[%i5], %g3
	srl	%g4, 16, %g4
	cmp	%g4, %g3
	blu	.L56
	 mov	%g1, %l3
.L144:
	b	.L41
	 mov	%g1, %i5
.L143:
	fdtoi	%f0, %f8
	st	%f8, [%fp-2080]
	b	.L38
	 ld	[%fp-2080], %g1
.L138:
	mov	3, %l2
	sethi	%hi(.LC6), %o0
	sth	%g3, [%fp-2082]
	call	ee_printf, 0
	 or	%o0, %lo(.LC6), %o0
	b	.L148
	 sethi	%hi(default_num_contexts), %i1
.L55:
	mov	%i3, %o1
	call	ee_printf, 0
	 or	%o0, %lo(.LC10), %o0
	lduh	[%i4-2008], %g3
	add	%g3, 1, %g3
	mov	%g3, %g1
	b	.L54
	 sth	%g3, [%i4-2008]
.L141:
	call	ee_printf, 0
	 or	%o0, %lo(.LC31), %o0
	lduh	[%fp-2082], %g2
	sll	%g2, 16, %g1
	sra	%g1, 16, %g1
	cmp	%g1, 3
	bne	.L78
	 ld	[%i1+%lo(default_num_contexts)], %g2
	ld	[%fp-2044], %g1
	smul	%g2, %g1, %g1
	st	%g1, [%fp-2080]
	cmp	%g1, 0
	ld	[%fp-2080], %f10
	bl	.L146
	 fitod	%f10, %f8
.L76:
	mov	%i2, %o0
	call	time_in_secs, 0
	 std	%f8, [%fp-2096]
	ldd	[%fp-2096], %f8
	fdivd	%f8, %f0, %f0
	std	%f0, [%fp-2104]
	ldd	[%fp-2104], %g2
	or	%i0, %lo(.LC21), %o3
	mov	%g2, %o1
	or	%l0, %lo(.LC23), %o4
	mov	%g3, %o2
	sethi	%hi(.LC32), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC32), %o0
	or	%l1, %lo(.LC25), %o1
	sethi	%hi(.LC33), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC33), %o0
	sethi	%hi(.LC34), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC34), %o0
	b,a	.L78
.L140:
	sethi	%hi(.LC18), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC18), %o0
	b	.L149
	 ld	[%fp-2044], %g1
.L77:
	call	ee_printf, 0
	 or	%o0, %lo(.LC36), %o0
	call	portable_fini, 0
	 add	%fp, -2006, %o0
	jmp	%i7+8
	 restore
.L45:
	mov	0, %l2
	sethi	%hi(.LC3), %o0
	sth	%g0, [%fp-2082]
	call	ee_printf, 0
	 or	%o0, %lo(.LC3), %o0
	b	.L148
	 sethi	%hi(default_num_contexts), %i1
.L44:
	mov	1, %g1
	mov	1, %l2
	sethi	%hi(.LC4), %o0
	sth	%g1, [%fp-2082]
	call	ee_printf, 0
	 or	%o0, %lo(.LC4), %o0
	b	.L148
	 sethi	%hi(default_num_contexts), %i1
.L42:
	mov	4, %g1
	mov	4, %l2
	sethi	%hi(.LC7), %o0
	sth	%g1, [%fp-2082]
	call	ee_printf, 0
	 or	%o0, %lo(.LC7), %o0
	b	.L148
	 sethi	%hi(default_num_contexts), %i1
.L139:
	sethi	%hi(.LC15), %g1
	ldd	[%g1+%lo(.LC15)], %f10
	b	.L59
	 faddd	%f8, %f10, %f8
.L146:
	sethi	%hi(.LC15), %g1
	ldd	[%g1+%lo(.LC15)], %f10
	b	.L76
	 faddd	%f8, %f10, %f8
.L64:
	andcc	%g2, 2, %g0
	be	.L66
	 mov	0, %g1
	b	.L150
	 sll	%i3, 16, %i3
	.size	ajit_main, .-ajit_main
	.global mem_name
	.section	.rodata.str1.8
	.align 8
.LC37:
	.asciz	"Static"
	.align 8
.LC38:
	.asciz	"Heap"
	.align 8
.LC39:
	.asciz	"Stack"
	.section	".data"
	.align 4
	.type	mem_name, #object
	.size	mem_name, 12
mem_name:
	.long	.LC37
	.long	.LC38
	.long	.LC39
	.section	".rodata"
	.align 2
	.type	list_known_crc, #object
	.size	list_known_crc, 10
list_known_crc:
	.half	-11088
	.half	13120
	.half	27257
	.half	-6380
	.half	-7231
	.align 2
	.type	matrix_known_crc, #object
	.size	matrix_known_crc, 10
matrix_known_crc:
	.half	-16814
	.half	4505
	.half	22024
	.half	8151
	.half	1863
	.align 2
	.type	state_known_crc, #object
	.size	state_known_crc, 10
state_known_crc:
	.half	24135
	.half	14783
	.half	-6748
	.half	-29126
	.half	-29308
	.ident	"GCC: (Buildroot 2014.08-g9aeb387) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
