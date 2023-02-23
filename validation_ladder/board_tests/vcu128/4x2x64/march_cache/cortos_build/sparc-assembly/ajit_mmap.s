	.file	"ajit_mmap.c"
	.section	".text"
	.align 4
	.global initPageTableAllocator
	.type	initPageTableAllocator, #function
	.proc	020
initPageTableAllocator:
	save	%sp, -96, %sp
	mov	0, %i4
	mov	%i3, %l0
	mov	0, %i5
	mov	%i2, %i3
	cmp	%l0, 0
	mov	%i1, %i2
	be	.L4
	 mov	0, %i1
	addcc	%i5, %i3, %g3
.L11:
	addx	%i4, %i2, %g2
	mov	%g3, %o2
	mov	%g2, %o1
	call	__ajit_store_word_to_physical_address__, 0
	 mov	0, %o0
	addcc	%i5, 4, %g3
	addx	%i4, 0, %g2
	mov	%g3, %i5
	cmp	%i1, %g2
	bne	.L4
	 mov	%g2, %i4
	cmp	%l0, %g3
	bgu	.L11
	 addcc	%i5, %i3, %g3
.L4:
	std	%i2, [%i0]
	st	%g0, [%i0+8]
	st	%l0, [%i0+12]
	st	%g0, [%i0+16]
	st	%g0, [%i0+20]
	jmp	%i7+8
	 restore
	.size	initPageTableAllocator, .-initPageTableAllocator
	.align 4
	.global allocatePageTableBlock
	.type	allocatePageTableBlock, #function
	.proc	016
allocatePageTableBlock:
	save	%sp, -96, %sp
	mov	0, %i4
	cmp	%i1, 1
	bleu	.L22
	 mov	256, %i5
.L13:
	ldd	[%i0+16], %o0
	addcc	%i5, %o1, %g3
	ldd	[%i0], %o2
	addx	%i4, %o0, %g2
	addcc	%i5, %o3, %o5
	addx	%i4, %o2, %o4
	cmp	%g2, %o4
	bgu	.L17
	 nop
	be	.L20
	 cmp	%g3, %o5
	std	%o0, [%i2]
.L21:
	std	%g2, [%i0+16]
	jmp	%i7+8
	 restore %g0, 0, %o0
.L20:
	bleu,a	.L21
	 std	%o0, [%i2]
.L17:
	jmp	%i7+8
	 restore %g0, 1, %o0
.L22:
	b	.L13
	 mov	1024, %i5
	.size	allocatePageTableBlock, .-allocatePageTableBlock
	.align 4
	.global ajit_mmap_index_into_table
	.type	ajit_mmap_index_into_table, #function
	.proc	016
ajit_mmap_index_into_table:
	cmp	%o0, 2
	be	.L26
	 cmp	%o0, 3
	be	.L27
	 cmp	%o0, 1
	be	.L30
	 nop
	jmp	%o7+8
	 mov	0, %o0
.L30:
	jmp	%o7+8
	 srl	%o1, 24, %o0
.L27:
	srl	%o1, 12, %o0
	jmp	%o7+8
	 and	%o0, 63, %o0
.L26:
	srl	%o1, 18, %o0
	jmp	%o7+8
	 and	%o0, 63, %o0
	.size	ajit_mmap_index_into_table, .-ajit_mmap_index_into_table
	.align 4
	.global ajit_mmap_is_pte
	.type	ajit_mmap_is_pte, #function
	.proc	014
ajit_mmap_is_pte:
	and	%o0, 3, %o0
	xor	%o0, 2, %o0
	subcc	%g0, %o0, %g0
	jmp	%o7+8
	 subx	%g0, -1, %o0
	.size	ajit_mmap_is_pte, .-ajit_mmap_is_pte
	.align 4
	.global ajit_mmap_is_ptd
	.type	ajit_mmap_is_ptd, #function
	.proc	014
ajit_mmap_is_ptd:
	and	%o0, 3, %o0
	xor	%o0, 1, %o0
	subcc	%g0, %o0, %g0
	jmp	%o7+8
	 subx	%g0, -1, %o0
	.size	ajit_mmap_is_ptd, .-ajit_mmap_is_ptd
	.align 4
	.global ajit_mmap_get_phy_addr_from_ptd
	.type	ajit_mmap_get_phy_addr_from_ptd, #function
	.proc	017
ajit_mmap_get_phy_addr_from_ptd:
	and	%o0, -4, %o0
	sll	%o2, 2, %o2
	srl	%o0, 28, %g2
	mov	%o2, %o3
	sll	%o0, 4, %g3
	mov	0, %o2
	or	%o3, %g3, %g3
	or	%o2, %g2, %g2
	mov	%g3, %o1
	jmp	%o7+8
	 mov	%g2, %o0
	.size	ajit_mmap_get_phy_addr_from_ptd, .-ajit_mmap_get_phy_addr_from_ptd
	.align 4
	.global ajit_mmap_get_phy_addr_from_pte
	.type	ajit_mmap_get_phy_addr_from_pte, #function
	.proc	017
ajit_mmap_get_phy_addr_from_pte:
	cmp	%o1, 3
	be	.L39
	 cmp	%o1, 2
	be	.L40
	 mov	0, %o4
	cmp	%o1, 1
	be	.L41
	 mov	%o2, %o5
	srl	%o0, 8, %g1
	srl	%o0, 28, %g2
	sll	%g1, 12, %g3
	or	%o4, %g2, %g2
	or	%o5, %g3, %g3
	mov	%g2, %o0
	jmp	%o7+8
	 mov	%g3, %o1
.L39:
	and	%o2, 4095, %o4
	srl	%o0, 8, %g1
	mov	%o4, %o5
	srl	%o0, 28, %g2
	mov	0, %o4
	sll	%g1, 12, %g3
	or	%o4, %g2, %g2
	or	%o5, %g3, %g3
	mov	%g2, %o0
	jmp	%o7+8
	 mov	%g3, %o1
.L40:
	sethi	%hi(-16384), %o4
	andn	%o2, %o4, %o4
	srl	%o0, 8, %g1
	mov	%o4, %o5
	srl	%o0, 28, %g2
	mov	0, %o4
	sll	%g1, 12, %g3
	or	%o4, %g2, %g2
	or	%o5, %g3, %g3
	mov	%g2, %o0
	jmp	%o7+8
	 mov	%g3, %o1
.L41:
	sethi	%hi(-16777216), %o4
	andn	%o2, %o4, %o4
	srl	%o0, 8, %g1
	mov	%o4, %o5
	srl	%o0, 28, %g2
	mov	0, %o4
	sll	%g1, 12, %g3
	or	%o4, %g2, %g2
	or	%o5, %g3, %g3
	mov	%g2, %o0
	jmp	%o7+8
	 mov	%g3, %o1
	.size	ajit_mmap_get_phy_addr_from_pte, .-ajit_mmap_get_phy_addr_from_pte
	.align 4
	.global ajit_mmap_make_ptd
	.type	ajit_mmap_make_ptd, #function
	.proc	016
ajit_mmap_make_ptd:
	sll	%o1, 26, %g1
	srl	%o2, 6, %o2
	or	%g1, %o2, %o2
	sll	%o2, 2, %g3
	jmp	%o7+8
	 or	%g3, 1, %o0
	.size	ajit_mmap_make_ptd, .-ajit_mmap_make_ptd
	.align 4
	.global ajit_mmap_make_pte
	.type	ajit_mmap_make_pte, #function
	.proc	016
ajit_mmap_make_pte:
	sll	%o3, 20, %o3
	sll	%o1, 2, %o1
	srl	%o4, 12, %o4
	or	%o1, 2, %o1
	or	%o3, %o4, %o4
	sll	%o4, 8, %o0
	jmp	%o7+8
	 or	%o1, %o0, %o0
	.size	ajit_mmap_make_pte, .-ajit_mmap_make_pte
	.align 4
	.global ajit_lookup_mmap
	.type	ajit_lookup_mmap, #function
	.proc	04
ajit_lookup_mmap:
	save	%sp, -96, %sp
	stb	%g0, [%i4]
	st	%g0, [%i5]
	st	%g0, [%i5+4]
	ld	[%fp+92], %l3
	sll	%i2, 2, %i2
	st	%g0, [%l3]
	st	%g0, [%l3+4]
	mov	%i3, %l2
	addcc	%i1, %i2, %i1
	ld	[%fp+96], %i3
	srl	%l2, 24, %l5
	srl	%l2, 16, %l4
	srl	%l2, 10, %g1
	st	%g0, [%i3]
	addx	%i0, 0, %i0
	sll	%l5, 2, %l5
	and	%l4, 252, %l4
	and	%g1, 252, %i2
	mov	0, %l6
.L62:
	mov	%i0, %o0
	call	__ajit_load_word_from_physical_address__, 0
	 mov	%i1, %o1
	stb	%l6, [%i4]
	std	%i0, [%l3]
	and	%o0, 3, %g1
	cmp	%g1, 1
	bne	.L46
	 st	%o0, [%i3]
.L63:
	add	%l6, 1, %l6
	and	%l6, 0xff, %g1
	cmp	%g1, 2
	be	.L57
	 cmp	%g1, 3
	be	.L50
	 cmp	%g1, 1
	mov	0, %i0
	be	.L49
	 mov	%l5, %i1
	and	%o0, -4, %o0
	cmp	%g1, 4
	srl	%o0, 28, %i0
	bne	.L62
	 sll	%o0, 4, %i1
	jmp	%i7+8
	 restore %g0, 1, %o0
.L57:
	mov	0, %i0
	mov	%l4, %i1
.L49:
	and	%o0, -4, %o0
	srl	%o0, 28, %l0
	sll	%o0, 4, %l1
	or	%i0, %l0, %i0
	or	%i1, %l1, %i1
.L65:
	mov	%i0, %o0
	call	__ajit_load_word_from_physical_address__, 0
	 mov	%i1, %o1
	stb	%l6, [%i4]
	std	%i0, [%l3]
	and	%o0, 3, %g1
	cmp	%g1, 1
	be	.L63
	 st	%o0, [%i3]
.L46:
	cmp	%g1, 2
	be	.L64
	 mov	1, %i0
	jmp	%i7+8
	 restore
.L50:
	and	%o0, -4, %o0
	mov	0, %i0
	mov	%i2, %i1
	srl	%o0, 28, %l0
	sll	%o0, 4, %l1
	or	%i0, %l0, %i0
	b	.L65
	 or	%i1, %l1, %i1
.L64:
	and	%l6, 0xff, %l6
	cmp	%l6, 3
	be	.L66
	 cmp	%l6, 2
	be	.L67
	 cmp	%l6, 1
	mov	0, %i2
	be	.L68
	 mov	%l2, %i3
.L54:
	srl	%o0, 8, %g1
	srl	%o0, 28, %g2
	sll	%g1, 12, %g3
	or	%i2, %g2, %g2
	or	%i3, %g3, %g3
	std	%g2, [%i5]
	jmp	%i7+8
	 restore %g0, 0, %o0
.L66:
	and	%l2, 4095, %i2
	mov	%i2, %i3
	b	.L54
	 mov	0, %i2
.L67:
	sethi	%hi(-16384), %i2
	andn	%l2, %i2, %i2
	mov	%i2, %i3
	b	.L54
	 mov	0, %i2
.L68:
	sethi	%hi(-16777216), %i2
	andn	%l2, %i2, %i2
	mov	%i2, %i3
	b	.L54
	 mov	0, %i2
	.size	ajit_lookup_mmap, .-ajit_lookup_mmap
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.asciz	"ajit_mmap_operation: lookup-status = %d, pdte_level = %d\n"
	.section	".text"
	.align 4
	.global ajit_mmap_operation
	.type	ajit_mmap_operation, #function
	.proc	04
ajit_mmap_operation:
	save	%sp, -128, %sp
	add	%fp, -16, %g1
	st	%g1, [%sp+92]
	add	%fp, -20, %g1
	mov	%i4, %o2
	mov	%i2, %o1
	ld	[%fp+96], %l6
	add	%fp, -21, %o4
	mov	%l6, %o3
	add	%fp, -8, %o5
	mov	%i1, %o0
	st	%g1, [%sp+96]
	ld	[%fp+100], %i4
	ld	[%fp+104], %i2
	call	ajit_lookup_mmap, 0
	 ldub	[%fp+95], %i1
	ldub	[%fp-21], %o2
	mov	%o0, %l2
	mov	%o0, %o1
	sethi	%hi(.LC0), %o0
	call	cortos_printf, 0
	 or	%o0, %lo(.LC0), %o0
	cmp	%l2, 0
	bne	.L70
	 mov	%i5, %l3
	cmp	%i3, 1
	be	.L92
	 cmp	%i3, 2
	bne	.L72
	 ld	[%fp-20], %o0
	st	%g0, [%fp-20]
	mov	0, %o0
.L72:
	ld	[%fp-16], %o1
	ld	[%fp-12], %o2
	call	__ajit_store_word_to_physical_address__, 0
	 mov	0, %i0
	jmp	%i7+8
	 restore
.L70:
	cmp	%i3, 1
	be	.L75
	 ldub	[%fp-21], %g4
.L76:
	jmp	%i7+8
	 restore %g0, 0, %o0
.L75:
	and	%g4, 0xff, %g2
	cmp	%g2, %i5
	bgu	.L76
	 ldd	[%fp-16], %l4
	sll	%i4, 20, %i4
	srl	%i2, 12, %i2
	or	%i4, %i2, %i2
	sll	%i2, 8, %i2
	srl	%l6, 24, %l2
	srl	%l6, 16, %g1
	sll	%i1, 2, %i1
	srl	%l6, 10, %l6
	or	%i1, 2, %i1
	sll	%l2, 2, %l2
	or	%i1, %i2, %i1
	and	%l6, 252, %i3
	b	.L85
	 and	%g1, 252, %i2
.L95:
	bne	.L96
	 and	%g4, 0xff, %g4
	cmp	%o5, %o3
	bgu	.L87
	 nop
.L96:
	cmp	%g4, %l3
	be	.L93
	 std	%o4, [%i0+16]
	sll	%i4, 26, %g4
	srl	%i5, 6, %g2
	or	%g4, %g2, %g2
	sll	%g2, 2, %l1
	or	%l1, 1, %g3
	mov	%g3, %o0
	st	%g3, [%fp-20]
.L80:
	mov	%l4, %o1
	call	__ajit_store_word_to_physical_address__, 0
	 mov	%l5, %o2
	mov	0, %g2
	cmp	%l6, 2
	be	.L81
	 mov	%i2, %g3
	cmp	%l6, 3
	be	.L81
	 mov	%i3, %g3
	cmp	%l6, 1
	be	.L81
	 mov	%l2, %g3
	mov	0, %g3
.L81:
	addcc	%g3, %i5, %l5
	addx	%g2, %i4, %l4
	cmp	%l6, %l3
	bgu	.L76
	 mov	%l7, %g4
.L85:
	add	%g4, 1, %l7
	mov	0, %g2
	and	%l7, 0xff, %l6
	cmp	%l6, 1
	bleu	.L97
	 mov	256, %g3
.L77:
	ldd	[%i0+16], %i4
	addcc	%g3, %i5, %o5
	ldd	[%i0], %o0
	addx	%g2, %i4, %o4
	addcc	%g3, %o1, %o3
	addx	%g2, %o0, %o2
	cmp	%o4, %o2
	bleu	.L95
	 nop
.L87:
	jmp	%i7+8
	 restore %g0, 1, %o0
.L92:
	sll	%i1, 2, %o0
	sll	%i4, 20, %i4
	ld	[%fp-16], %o1
	ld	[%fp-12], %o2
	or	%o0, 2, %o0
	srl	%i2, 12, %i2
	mov	0, %i0
	or	%i4, %i2, %i2
	sll	%i2, 8, %i2
	or	%o0, %i2, %o0
	call	__ajit_store_word_to_physical_address__, 0
	 st	%o0, [%fp-20]
	jmp	%i7+8
	 restore
.L97:
	b	.L77
	 mov	1024, %g3
.L93:
	st	%i1, [%fp-20]
	b	.L80
	 mov	%i1, %o0
	.size	ajit_mmap_operation, .-ajit_mmap_operation
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
