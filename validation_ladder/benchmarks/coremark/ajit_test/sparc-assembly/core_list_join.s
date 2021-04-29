	.file	"core_list_join.c"
	.section	".text"
	.align 4
	.global cmp_idx
	.type	cmp_idx, #function
	.proc	04
cmp_idx:
	cmp	%o2, 0
	be,a	.L4
	 lduh	[%o0], %g1
	ldsh	[%o0+2], %o0
	ldsh	[%o1+2], %g1
	jmp	%o7+8
	 sub	%o0, %g1, %o0
.L4:
	sll	%g1, 16, %g2
	and	%g1, -256, %g1
	srl	%g2, 24, %g2
	or	%g2, %g1, %g1
	sth	%g1, [%o0]
	lduh	[%o1], %g1
	sll	%g1, 16, %g2
	and	%g1, -256, %g1
	srl	%g2, 24, %g2
	or	%g2, %g1, %g1
	ldsh	[%o0+2], %o0
	sth	%g1, [%o1]
	ldsh	[%o1+2], %g1
	jmp	%o7+8
	 sub	%o0, %g1, %o0
	.size	cmp_idx, .-cmp_idx
	.align 4
	.type	core_list_mergesort.constprop.1, #function
	.proc	0110
core_list_mergesort.constprop.1:
	save	%sp, -96, %sp
	cmp	%i0, 0
	be	.L6
	 mov	1, %g3
.L37:
	mov	0, %o5
	mov	0, %g4
	mov	0, %i3
	add	%i3, 1, %i3
.L42:
	mov	%i0, %g2
	mov	0, %g1
	ld	[%g2], %g2
.L40:
	cmp	%g2, 0
	be	.L10
	 add	%g1, 1, %g1
	cmp	%g1, %g3
	bl,a	.L40
	 ld	[%g2], %g2
.L10:
	mov	%i0, %i4
	mov	%g3, %i5
	cmp	%g1, 0
	be	.L33
	 mov	%g2, %i0
	cmp	%i0, 0
.L41:
	bne	.L34
	 cmp	%i5, 0
.L32:
	mov	%i4, %g2
.L43:
	add	%g1, -1, %g1
	ld	[%i4], %i4
.L11:
	cmp	%g4, 0
	be,a	.L23
	 mov	%g2, %o5
	st	%g2, [%g4]
	mov	%g2, %g4
.L38:
	cmp	%g1, 0
	bne	.L41
	 cmp	%i0, 0
.L33:
	cmp	%i0, 0
	bne	.L35
	 cmp	%i5, 0
	cmp	%i0, 0
.L44:
	bne,a	.L42
	 add	%i3, 1, %i3
	cmp	%i3, 1
	be	.L36
	 st	%g0, [%g4]
	mov	%o5, %i0
	cmp	%i0, 0
	bne	.L37
	 add	%g3, %g3, %g3
.L6:
	st	%g0, [%g0+0]
	jmp	%i7+8
	 restore
.L23:
	b	.L38
	 mov	%g2, %g4
.L34:
	be	.L43
	 mov	%i4, %g2
	ld	[%i4+4], %i2
	ld	[%i0+4], %g2
	lduh	[%i2], %i1
	sll	%i1, 16, %o7
	and	%i1, -256, %i1
	srl	%o7, 24, %o7
	or	%o7, %i1, %i1
	sth	%i1, [%i2]
	lduh	[%g2], %i1
	sll	%i1, 16, %o7
	and	%i1, -256, %i1
	srl	%o7, 24, %o7
	or	%o7, %i1, %i1
	sth	%i1, [%g2]
	ldsh	[%i2+2], %i2
	ldsh	[%g2+2], %g2
	sub	%i2, %g2, %g2
	cmp	%g2, 0
	ble	.L32
	 mov	%i0, %g2
.L39:
	add	%i5, -1, %i5
	b	.L11
	 ld	[%i0], %i0
.L35:
	ble	.L44
	 cmp	%i0, 0
	b	.L39
	 mov	%i0, %g2
.L36:
	jmp	%i7+8
	 restore %g0, %o5, %o0
	.size	core_list_mergesort.constprop.1, .-core_list_mergesort.constprop.1
	.align 4
	.global calc_func
	.type	calc_func, #function
	.proc	03
calc_func:
	save	%sp, -96, %sp
	lduh	[%i0], %i5
	andcc	%i5, 128, %g0
	bne	.L55
	 sll	%i5, 16, %g1
	sra	%g1, 19, %g1
	andcc	%i5, 7, %g2
	and	%g1, 15, %g1
	sll	%g1, 4, %o1
	or	%o1, %g1, %o1
	be	.L49
	 mov	%o1, %o4
	cmp	%g2, 1
	be	.L56
	 mov	%i5, %i4
.L48:
	lduh	[%i1+56], %o1
	call	crcu8, 0
	 and	%i4, 0xff, %o0
	sll	%i4, 16, %g1
	sll	%o0, 16, %o1
	srl	%g1, 24, %o0
	call	crcu8, 0
	 srl	%o1, 16, %o1
	sth	%o0, [%i1+56]
	and	%i4, 127, %i4
	and	%i5, -256, %i5
	mov	%i4, %g1
	or	%i5, 128, %i5
	or	%i5, %i4, %i4
	sth	%i4, [%i0]
	and	%g1, 127, %i0
	jmp	%i7+8
	 restore
.L49:
	cmp	%o1, 33
	ble,a	.L51
	 mov	34, %o4
.L51:
	ld	[%i1+24], %o0
	ld	[%i1+20], %o1
	ldsh	[%i1], %o2
	ldsh	[%i1+2], %o3
	and	%o4, 0xff, %o4
	call	core_bench_state, 0
	 lduh	[%i1+56], %o5
	lduh	[%i1+62], %g1
	cmp	%g1, 0
	bne	.L48
	 mov	%o0, %i4
	b	.L48
	 sth	%o0, [%i1+62]
.L55:
	and	%i5, 127, %g1
	and	%g1, 127, %i0
	jmp	%i7+8
	 restore
.L56:
	add	%i1, 40, %o0
	call	core_bench_matrix, 0
	 lduh	[%i1+56], %o2
	lduh	[%i1+60], %g1
	cmp	%g1, 0
	bne	.L48
	 mov	%o0, %i4
	b	.L48
	 sth	%o0, [%i1+60]
	.size	calc_func, .-calc_func
	.align 4
	.global cmp_complex
	.type	cmp_complex, #function
	.proc	04
cmp_complex:
	save	%sp, -96, %sp
	mov	%i2, %o1
	call	calc_func, 0
	 mov	%i0, %o0
	mov	%i2, %o1
	mov	%o0, %i5
	mov	%i1, %o0
	call	calc_func, 0
	 sll	%i5, 16, %i5
	sra	%i5, 16, %i5
	sll	%o0, 16, %o0
	sra	%o0, 16, %i0
	sub	%i5, %i0, %i0
	jmp	%i7+8
	 restore
	.size	cmp_complex, .-cmp_complex
	.align 4
	.global copy_info
	.type	copy_info, #function
	.proc	020
copy_info:
	lduh	[%o1], %g2
	lduh	[%o1+2], %g1
	sth	%g2, [%o0]
	jmp	%o7+8
	 sth	%g1, [%o0+2]
	.size	copy_info, .-copy_info
	.align 4
	.global core_list_init
	.type	core_list_init, #function
	.proc	0110
core_list_init:
	save	%sp, -96, %sp
	wr	%g0, 0, %y
	nop
	nop
	nop
	udiv	%i0, 20, %i0
	st	%g0, [%i1]
	add	%i0, -2, %i3
	sll	%i3, 3, %g1
	add	%i1, %g1, %i5
	st	%i5, [%i1+4]
	sethi	%hi(-32768), %g2
	sth	%g0, [%i5+2]
	or	%g2, 128, %g2
	sth	%g2, [%i1+%g1]
	sll	%i3, 2, %i0
	add	%i1, 16, %g1
	add	%i5, %i0, %i0
	add	%i1, 8, %g3
	add	%i5, 4, %i4
	cmp	%i5, %g1
	bleu	.L60
	 mov	0, %g2
	add	%i5, 8, %g4
	cmp	%i0, %g4
	bgu,a	.L74
	 st	%g3, [%i1]
.L60:
	cmp	%i3, 0
	be,a	.L77
	 sethi	%hi(15360), %i0
	sethi	%hi(31744), %o3
	mov	%i2, %o2
	mov	0, %g1
	or	%o3, 1023, %o3
	add	%g3, 8, %g4
.L79:
	cmp	%i5, %g4
	bleu,a	.L78
	 add	%g1, 1, %g1
	add	%i4, 4, %o7
	cmp	%i0, %o7
	bleu,a	.L78
	 add	%g1, 1, %g1
	st	%g2, [%g3]
	st	%i4, [%g3+4]
	st	%g3, [%i1]
	and	%g1, 7, %o5
	xor	%g1, %o2, %o4
	sth	%o3, [%i4+2]
	and	%o4, 15, %o4
	mov	%g3, %g2
	sll	%o4, 3, %o4
	mov	%g4, %g3
	or	%o4, %o5, %g4
	sll	%g4, 8, %o5
	or	%o5, %g4, %g4
	sth	%g4, [%i4]
	mov	%o7, %i4
	add	%g1, 1, %g1
.L78:
	cmp	%i3, %g1
	bne,a	.L79
	 add	%g3, 8, %g4
	sethi	%hi(15360), %i0
.L77:
	wr	%g0, 0, %y
	nop
	nop
	nop
	udiv	%i3, 5, %i5
	mov	1, %g1
	mov	2, %g4
	b	.L64
	 or	%i0, 1023, %i0
.L76:
	sth	%g1, [%g2+2]
.L66:
	add	%g4, 1, %g4
	add	%g1, 1, %g1
	mov	%g3, %g2
.L64:
	ld	[%g2], %g3
	cmp	%g3, 0
	be	.L75
	 cmp	%i5, %g1
	bgu	.L76
	 ld	[%g2+4], %g2
	and	%g4, 7, %i4
	xor	%g1, %i2, %i3
	sll	%i4, 8, %i4
	or	%i4, %i3, %i4
	and	%i4, %i0, %i4
	b	.L66
	 sth	%i4, [%g2+2]
.L75:
	call	core_list_mergesort.constprop.1, 0
	 restore %g0, %i1, %o0
.L74:
	st	%i4, [%i1+12]
	st	%g0, [%i1+8]
	mov	%g3, %g2
	mov	-1, %g3
	sth	%g3, [%i5+4]
	sethi	%hi(31744), %g3
	or	%g3, 1023, %g3
	mov	%g4, %i4
	sth	%g3, [%i5+6]
	b	.L60
	 mov	%g1, %g3
	.size	core_list_init, .-core_list_init
	.align 4
	.global core_list_insert_new
	.type	core_list_insert_new, #function
	.proc	0110
core_list_insert_new:
	ld	[%o2], %g1
	add	%g1, 8, %g2
	cmp	%g2, %o4
	bgeu,a	.L84
	 mov	0, %g1
	ld	[%o3], %g3
	add	%g3, 4, %g3
	cmp	%o5, %g3
	bleu,a	.L83
	 mov	0, %g1
	st	%g2, [%o2]
	ld	[%o0], %g2
	st	%g2, [%g1]
	st	%g1, [%o0]
	ld	[%o3], %g2
	st	%g2, [%g1+4]
	ld	[%o3], %g2
	add	%g2, 4, %g2
	st	%g2, [%o3]
	lduh	[%o1], %g4
	ld	[%g1+4], %g2
	lduh	[%o1+2], %g3
	sth	%g4, [%g2]
	sth	%g3, [%g2+2]
	jmp	%o7+8
	 mov	%g1, %o0
.L83:
.L84:
	jmp	%o7+8
	 mov	%g1, %o0
	.size	core_list_insert_new, .-core_list_insert_new
	.align 4
	.global core_list_remove
	.type	core_list_remove, #function
	.proc	0110
core_list_remove:
	ld	[%o0], %g1
	ld	[%o0+4], %g2
	ld	[%g1+4], %g4
	ld	[%g1], %g3
	st	%g4, [%o0+4]
	st	%g3, [%o0]
	st	%g2, [%g1+4]
	st	%g0, [%g1]
	jmp	%o7+8
	 mov	%g1, %o0
	.size	core_list_remove, .-core_list_remove
	.align 4
	.global core_list_undo_remove
	.type	core_list_undo_remove, #function
	.proc	0110
core_list_undo_remove:
	ld	[%o0+4], %g2
	ld	[%o1+4], %g4
	ld	[%o1], %g3
	st	%g4, [%o0+4]
	st	%g3, [%o0]
	st	%g2, [%o1+4]
	jmp	%o7+8
	 st	%o0, [%o1]
	.size	core_list_undo_remove, .-core_list_undo_remove
	.align 4
	.global core_list_find
	.type	core_list_find, #function
	.proc	0110
core_list_find:
	ldsh	[%o1+2], %g2
	cmp	%g2, 0
	bl	.L88
	 cmp	%o0, 0
	be	.L117
	 nop
	ld	[%o0+4], %g1
	ldsh	[%g1+2], %g1
	cmp	%g2, %g1
	bne,a	.L115
	 ld	[%o0], %o0
	b,a	.L117
.L111:
	ldsh	[%g1+2], %g1
	cmp	%g2, %g1
	be	.L117
	 nop
	ld	[%o0], %o0
.L115:
	cmp	%o0, 0
	bne,a	.L111
	 ld	[%o0+4], %g1
	jmp	%o7+8
	 nop
.L88:
	be	.L117
	 nop
	ldsh	[%o1], %g2
	ld	[%o0+4], %g1
	ldub	[%g1+1], %g1
	cmp	%g1, %g2
	bne,a	.L116
	 ld	[%o0], %o0
	b,a	.L117
.L113:
	ldub	[%g1+1], %g1
	cmp	%g1, %g2
	be	.L117
	 nop
	ld	[%o0], %o0
.L116:
	cmp	%o0, 0
	bne,a	.L113
	 ld	[%o0+4], %g1
.L117:
	jmp	%o7+8
	 nop
	.size	core_list_find, .-core_list_find
	.align 4
	.global core_list_reverse
	.type	core_list_reverse, #function
	.proc	0110
core_list_reverse:
	cmp	%o0, 0
	be	.L122
	 mov	0, %g2
	b	.L124
	 ld	[%o0], %g1
.L123:
	mov	%g1, %o0
	ld	[%o0], %g1
.L124:
	st	%g2, [%o0]
	cmp	%g1, 0
	bne	.L123
	 mov	%o0, %g2
	jmp	%o7+8
	 nop
.L122:
	jmp	%o7+8
	 mov	0, %o0
	.size	core_list_reverse, .-core_list_reverse
	.align 4
	.global core_list_mergesort
	.type	core_list_mergesort, #function
	.proc	0110
core_list_mergesort:
	save	%sp, -96, %sp
	cmp	%i0, 0
	be	.L126
	 mov	1, %i3
.L156:
	mov	%i0, %l1
	mov	0, %l3
	mov	0, %l0
	mov	0, %i0
	add	%l3, 1, %l3
.L161:
	mov	%l1, %i5
	mov	0, %i4
	ld	[%i5], %i5
.L159:
	cmp	%i5, 0
	be	.L130
	 add	%i4, 1, %i4
	cmp	%i3, %i4
	bg,a	.L159
	 ld	[%i5], %i5
.L130:
	cmp	%i4, 0
	be	.L153
	 mov	%i3, %l2
	cmp	%i5, 0
.L160:
	bne	.L154
	 cmp	%l2, 0
.L152:
	mov	%l1, %g1
.L162:
	add	%i4, -1, %i4
	ld	[%l1], %l1
.L131:
	cmp	%l0, 0
	be,a	.L143
	 mov	%g1, %i0
	st	%g1, [%l0]
	mov	%g1, %l0
.L157:
	cmp	%i4, 0
	bne	.L160
	 cmp	%i5, 0
.L153:
	cmp	%i5, 0
	bne	.L155
	 cmp	%l2, 0
	orcc	%i5, 0, %l1
.L163:
	bne,a	.L161
	 add	%l3, 1, %l3
	cmp	%l3, 1
	be	.L164
	 st	%g0, [%l0]
	cmp	%i0, 0
	bne	.L156
	 add	%i3, %i3, %i3
.L126:
	st	%g0, [%g0+0]
.L164:
	jmp	%i7+8
	 restore
.L143:
	b	.L157
	 mov	%g1, %l0
.L154:
	be	.L162
	 mov	%l1, %g1
	ld	[%l1+4], %o0
	ld	[%i5+4], %o1
	call	%i1, 0
	 mov	%i2, %o2
	cmp	%o0, 0
	ble	.L152
	 mov	%i5, %g1
.L158:
	add	%l2, -1, %l2
	b	.L131
	 ld	[%i5], %i5
.L155:
	ble,a	.L163
	 orcc	%i5, 0, %l1
	b	.L158
	 mov	%i5, %g1
	.size	core_list_mergesort, .-core_list_mergesort
	.align 4
	.global core_bench_list
	.type	core_bench_list, #function
	.proc	015
core_bench_list:
	save	%sp, -96, %sp
	ldsh	[%i0+4], %o5
	cmp	%o5, 0
	ble	.L193
	 ld	[%i0+36], %i5
	mov	%i1, %i2
	mov	0, %g4
	mov	0, %o4
	mov	0, %o7
	mov	0, %i4
	sll	%i2, 16, %i3
	and	%g4, 255, %g1
.L241:
	sra	%i3, 16, %g3
	cmp	%g3, 0
	bl	.L167
	 mov	%g1, %l0
	cmp	%i5, 0
	be,a	.L238
	 ld	[%i5], %g1
	ld	[%i5+4], %g1
	ldsh	[%g1+2], %g2
	cmp	%g3, %g2
	bne	.L214
	 mov	%i5, %g1
	b	.L174
	 mov	0, %g3
.L230:
	ldsh	[%g2+2], %g2
	cmp	%g3, %g2
	be,a	.L174
	 mov	0, %g3
.L214:
	ld	[%g1], %g1
	cmp	%g1, 0
	bne,a	.L230
	 ld	[%g1+4], %g2
	mov	0, %g1
	b	.L174
	 mov	0, %g3
.L196:
	mov	%g2, %i5
.L174:
	ld	[%i5], %g2
	st	%g3, [%i5]
	cmp	%g2, 0
	bne	.L196
	 mov	%i5, %g3
	cmp	%g1, 0
	be,a	.L238
	 ld	[%i5], %g1
	ld	[%g1+4], %g2
	lduh	[%g2], %g2
	andcc	%g2, 1, %g0
	be	.L177
	 add	%o7, 1, %o7
	srl	%g2, 9, %g2
	and	%g2, 1, %g2
	add	%g2, %i4, %i4
.L177:
	ld	[%g1], %g2
	cmp	%g2, 0
	be	.L239
	 cmp	%i3, 0
	ld	[%g2], %g3
	st	%g3, [%g1]
	ld	[%i5], %g1
	st	%g1, [%g2]
	st	%g2, [%i5]
.L176:
	cmp	%i3, 0
.L239:
	bl	.L240
	 add	%g4, 1, %g4
	add	%i2, 1, %i2
	sll	%i2, 16, %i3
.L240:
	sll	%g4, 16, %g1
	sra	%g1, 16, %g1
	cmp	%g1, %o5
	bne	.L241
	 and	%g4, 255, %g1
	sll	%o7, 2, %o7
	sub	%o7, %o4, %o4
	add	%o4, %i4, %i4
.L166:
	cmp	%i1, 0
	ble	.L180
	 mov	%i5, %o0
	mov	%i0, %o2
	sethi	%hi(cmp_complex), %o1
	call	core_list_mergesort, 0
	 or	%o1, %lo(cmp_complex), %o1
	mov	%o0, %i5
.L180:
	ld	[%i5], %g1
	ld	[%g1], %i2
	ld	[%g1+4], %g3
	ld	[%i2+4], %g4
	ld	[%i2], %g2
	st	%g4, [%g1+4]
	st	%g2, [%g1]
	st	%g3, [%i2+4]
	st	%g0, [%i2]
	sra	%i3, 16, %i3
	cmp	%i3, 0
	bl	.L231
	 mov	%i5, %g1
	ld	[%g1+4], %g2
.L242:
	ldsh	[%g2+2], %g2
	cmp	%i3, %g2
	be,a	.L232
	 mov	%g1, %i3
	ld	[%g1], %g1
	cmp	%g1, 0
	bne,a	.L242
	 ld	[%g1+4], %g2
	ld	[%i5], %g1
	orcc	%g1, 0, %i3
	be,a	.L237
	 ld	[%g1+4], %g4
	ld	[%i5+4], %g1
.L245:
	sll	%i4, 16, %o1
	ldsh	[%g1], %o0
	call	crc16, 0
	 srl	%o1, 16, %o1
	ld	[%i3], %i3
	cmp	%i3, 0
	bne	.L212
	 mov	%o0, %i4
	ld	[%i2+4], %g3
.L236:
	ld	[%i5], %g1
	ld	[%g1+4], %g4
.L237:
	ld	[%g1], %g2
	st	%g4, [%i2+4]
	st	%g2, [%i2]
	mov	%i5, %o0
	st	%g3, [%g1+4]
	call	core_list_mergesort.constprop.1, 0
	 st	%i2, [%g1]
	ld	[%o0], %i5
	cmp	%i5, 0
	be	.L190
	 mov	%o0, %i3
.L211:
	ld	[%i3+4], %g1
	sll	%i4, 16, %o1
	ldsh	[%g1], %o0
	call	crc16, 0
	 srl	%o1, 16, %o1
	ld	[%i5], %i5
	cmp	%i5, 0
	bne	.L211
	 mov	%o0, %i4
.L190:
	sll	%i4, 16, %i4
	srl	%i4, 16, %i0
	jmp	%i7+8
	 restore
.L167:
	cmp	%i5, 0
	be	.L168
	 mov	%g1, %g3
	ld	[%i5+4], %g1
	ldub	[%g1+1], %g1
	cmp	%g1, %g3
	bne	.L172
	 mov	%i5, %g1
	b	.L174
	 mov	0, %g3
.L233:
	ldub	[%g2+1], %g2
	cmp	%g2, %g3
	be,a	.L174
	 mov	0, %g3
.L172:
	ld	[%g1], %g1
	cmp	%g1, 0
	bne,a	.L233
	 ld	[%g1+4], %g2
	b	.L174
	 mov	0, %g3
.L168:
	ld	[%i5], %g1
.L238:
	add	%o4, 1, %o4
	ld	[%g1+4], %g1
	ldsb	[%g1], %g1
	and	%g1, 1, %g1
	b	.L176
	 add	%g1, %i4, %i4
.L232:
.L212:
	ld	[%i5+4], %g1
.L243:
	sll	%i4, 16, %o1
	ldsh	[%g1], %o0
	call	crc16, 0
	 srl	%o1, 16, %o1
	ld	[%i3], %i3
	cmp	%i3, 0
	bne	.L212
	 mov	%o0, %i4
	b	.L236
	 ld	[%i2+4], %g3
.L231:
	and	%l0, 0xff, %l0
	mov	%i5, %i3
	ld	[%i3+4], %g1
.L244:
	ldub	[%g1+1], %g1
	cmp	%g1, %l0
	be,a	.L243
	 ld	[%i5+4], %g1
	ld	[%i3], %i3
	cmp	%i3, 0
	bne,a	.L244
	 ld	[%i3+4], %g1
	ld	[%i5], %g1
	orcc	%g1, 0, %i3
	bne,a	.L245
	 ld	[%i5+4], %g1
	b	.L237
	 ld	[%g1+4], %g4
.L193:
	mov	0, %i4
	mov	0, %l0
	b	.L166
	 sll	%i1, 16, %i3
	.size	core_bench_list, .-core_bench_list
	.ident	"GCC: (Buildroot 2014.08-g9aeb387) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
