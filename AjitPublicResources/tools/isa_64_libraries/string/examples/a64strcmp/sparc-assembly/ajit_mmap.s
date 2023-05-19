	.file	"ajit_mmap.c"
	.section	".text"
.Ltext0:
	.cfi_sections	.debug_frame
	.align 4
	.global initPageTableAllocator
	.type	initPageTableAllocator, #function
	.proc	020
initPageTableAllocator:
.LFB0:
	.file 1 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_mmap.c"
	.loc 1 11 0
	.cfi_startproc
	save	%sp, -112, %sp
.LCFI0:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp-16]
	st	%i2, [%fp-12]
	st	%i3, [%fp+80]
	.loc 1 15 0
	st	%g0, [%fp-8]
	st	%g0, [%fp-4]
	b	.L2
	 nop
.L3:
	.loc 1 17 0 discriminator 2
	ldd	[%fp-16], %i2
	ldd	[%fp-8], %i4
	addcc	%i3, %i5, %g3
	addx	%i2, %i4, %g2
	mov	0, %o0
	mov	%g2, %o1
	mov	%g3, %o2
	call	__ajit_store_word_to_physical_address__, 0
	 nop
	.loc 1 15 0 discriminator 2
	ldd	[%fp-8], %i4
	addcc	%i5, 4, %g3
	addx	%i4, 0, %g2
	std	%g2, [%fp-8]
.L2:
	.loc 1 15 0 is_stmt 0 discriminator 1
	ld	[%fp+80], %g1
	mov	0, %g2
	mov	%g1, %g3
	ld	[%fp-8], %g1
	cmp	%g1, %g2
	blu	.L3
	 nop
	ld	[%fp-8], %g1
	cmp	%g1, %g2
	bne	.L5
	 nop
	ld	[%fp-4], %g1
	cmp	%g1, %g3
	blu	.L3
	 nop
.L5:
	.loc 1 20 0 is_stmt 1
	ld	[%fp+68], %g1
	ldd	[%fp-16], %g2
	std	%g2, [%g1]
	.loc 1 21 0
	ld	[%fp+80], %g1
	mov	0, %g2
	mov	%g1, %g3
	ld	[%fp+68], %g1
	std	%g2, [%g1+8]
	.loc 1 22 0
	ld	[%fp+68], %g1
	st	%g0, [%g1+16]
	st	%g0, [%g1+20]
	.loc 1 23 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE0:
	.size	initPageTableAllocator, .-initPageTableAllocator
	.align 4
	.global allocatePageTableBlock
	.type	allocatePageTableBlock, #function
	.proc	016
allocatePageTableBlock:
.LFB1:
	.loc 1 28 0
	.cfi_startproc
	save	%sp, -120, %sp
.LCFI1:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	mov	%i1, %g1
	st	%i2, [%fp+76]
	stb	%g1, [%fp+72]
	.loc 1 29 0
	mov	1, %g1
	st	%g1, [%fp-4]
	.loc 1 30 0
	st	%g0, [%fp-16]
	st	%g0, [%fp-12]
	.loc 1 31 0
	ldub	[%fp+72], %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 1
	bgu	.L7
	 nop
	.loc 1 32 0
	mov	0, %g2
	mov	1024, %g3
	std	%g2, [%fp-16]
	b	.L8
	 nop
.L7:
	.loc 1 34 0
	mov	0, %g2
	mov	256, %g3
	std	%g2, [%fp-16]
.L8:
	.loc 1 36 0
	ld	[%fp+68], %g1
	ldd	[%g1+16], %i2
	ldd	[%fp-16], %i4
	addcc	%i3, %i5, %g3
	addx	%i2, %i4, %g2
	std	%g2, [%fp-24]
	.loc 1 37 0
	ld	[%fp+68], %g1
	ldd	[%g1], %i2
	ldd	[%fp-16], %i4
	addcc	%i3, %i5, %g3
	addx	%i2, %i4, %g2
	ld	[%fp-24], %g1
	cmp	%g1, %g2
	bgu	.L9
	 nop
	ld	[%fp-24], %g1
	cmp	%g1, %g2
	bne	.L12
	 nop
	ld	[%fp-20], %g1
	cmp	%g1, %g3
	bgu	.L9
	 nop
.L12:
	.loc 1 39 0
	ld	[%fp+68], %g1
	ldd	[%g1+16], %g2
	ld	[%fp+76], %g1
	std	%g2, [%g1]
	.loc 1 40 0
	ld	[%fp+68], %g1
	ldd	[%fp-24], %g2
	std	%g2, [%g1+16]
	.loc 1 41 0
	st	%g0, [%fp-4]
.L9:
	.loc 1 43 0
	ld	[%fp-4], %g1
	.loc 1 44 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE1:
	.size	allocatePageTableBlock, .-allocatePageTableBlock
	.align 4
	.global ajit_mmap_index_into_table
	.type	ajit_mmap_index_into_table, #function
	.proc	016
ajit_mmap_index_into_table:
.LFB2:
	.loc 1 48 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI2:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	st	%i1, [%fp+72]
	stb	%g1, [%fp+68]
	.loc 1 49 0
	st	%g0, [%fp-4]
	.loc 1 50 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 2
	be	.L16
	 nop
	cmp	%g1, 3
	be	.L17
	 nop
	cmp	%g1, 1
	bne	.L20
	 nop
.L15:
	.loc 1 53 0
	ld	[%fp+72], %g1
	srl	%g1, 24, %g1
	st	%g1, [%fp-4]
	.loc 1 54 0
	b	.L18
	 nop
.L16:
	.loc 1 56 0
	ld	[%fp+72], %g1
	srl	%g1, 18, %g1
	and	%g1, 63, %g1
	st	%g1, [%fp-4]
	.loc 1 57 0
	b	.L18
	 nop
.L17:
	.loc 1 59 0
	ld	[%fp+72], %g1
	srl	%g1, 12, %g1
	and	%g1, 63, %g1
	st	%g1, [%fp-4]
	.loc 1 60 0
	b	.L18
	 nop
.L20:
	.loc 1 62 0
	nop
.L18:
	.loc 1 64 0
	ld	[%fp-4], %g1
	.loc 1 65 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE2:
	.size	ajit_mmap_index_into_table, .-ajit_mmap_index_into_table
	.align 4
	.global ajit_mmap_is_pte
	.type	ajit_mmap_is_pte, #function
	.proc	014
ajit_mmap_is_pte:
.LFB3:
	.loc 1 68 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI3:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	.loc 1 69 0
	ld	[%fp+68], %g1
	and	%g1, 3, %g1
	xor	%g1, 2, %g1
	subcc	%g0, %g1, %g0
	subx	%g0, -1, %g1
	stb	%g1, [%fp-1]
	.loc 1 70 0
	ldub	[%fp-1], %g1
	and	%g1, 0xff, %g1
	.loc 1 71 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE3:
	.size	ajit_mmap_is_pte, .-ajit_mmap_is_pte
	.align 4
	.global ajit_mmap_is_ptd
	.type	ajit_mmap_is_ptd, #function
	.proc	014
ajit_mmap_is_ptd:
.LFB4:
	.loc 1 74 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI4:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	.loc 1 75 0
	ld	[%fp+68], %g1
	and	%g1, 3, %g1
	xor	%g1, 1, %g1
	subcc	%g0, %g1, %g0
	subx	%g0, -1, %g1
	stb	%g1, [%fp-1]
	.loc 1 76 0
	ldub	[%fp-1], %g1
	and	%g1, 0xff, %g1
	.loc 1 77 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE4:
	.size	ajit_mmap_is_ptd, .-ajit_mmap_is_ptd
	.align 4
	.global ajit_mmap_get_phy_addr_from_ptd
	.type	ajit_mmap_get_phy_addr_from_ptd, #function
	.proc	017
ajit_mmap_get_phy_addr_from_ptd:
.LFB5:
	.loc 1 80 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI5:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	mov	%i1, %g1
	st	%i2, [%fp+76]
	stb	%g1, [%fp+72]
	.loc 1 81 0
	ld	[%fp+68], %g1
	mov	0, %g2
	mov	%g1, %g3
	mov	0, %o4
	sethi	%hi(4294966272), %o5
	or	%o5, 1020, %o5
	and	%g2, %o4, %g2
	and	%g3, %o5, %g3
	std	%g2, [%fp-8]
	.loc 1 83 0
	ld	[%fp-4], %g1
	srl	%g1, 28, %g1
	ld	[%fp-8], %g2
	sll	%g2, 4, %g2
	or	%g2, %g1, %g1
	st	%g1, [%fp-8]
	ld	[%fp-4], %g1
	sll	%g1, 4, %g1
	st	%g1, [%fp-4]
	.loc 1 84 0
	ld	[%fp+76], %g1
	sll	%g1, 2, %g1
	mov	0, %g2
	mov	%g1, %g3
	ldd	[%fp-8], %i4
	or	%i4, %g2, %g2
	or	%i5, %g3, %g3
	std	%g2, [%fp-8]
	.loc 1 86 0
	ldd	[%fp-8], %g2
	.loc 1 88 0
	mov	%g2, %i0
	mov	%g3, %i1
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE5:
	.size	ajit_mmap_get_phy_addr_from_ptd, .-ajit_mmap_get_phy_addr_from_ptd
	.align 4
	.global ajit_mmap_get_phy_addr_from_pte
	.type	ajit_mmap_get_phy_addr_from_pte, #function
	.proc	017
ajit_mmap_get_phy_addr_from_pte:
.LFB6:
	.loc 1 91 0
	.cfi_startproc
	save	%sp, -120, %sp
.LCFI6:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	mov	%i1, %g1
	st	%i2, [%fp+76]
	stb	%g1, [%fp+72]
	.loc 1 92 0
	st	%g0, [%fp-8]
	st	%g0, [%fp-4]
	.loc 1 93 0
	ldub	[%fp+72], %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 3
	bne	.L28
	 nop
	.loc 1 94 0
	ld	[%fp+76], %g1
	mov	0, %g2
	mov	%g1, %g3
	and	%g2, 0, %g2
	and	%g3, 4095, %g3
	std	%g2, [%fp-8]
	b	.L29
	 nop
.L28:
	.loc 1 95 0
	ldub	[%fp+72], %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 2
	bne	.L30
	 nop
	.loc 1 96 0
	ld	[%fp+76], %g1
	mov	0, %i4
	mov	%g1, %i5
	mov	0, %g2
	sethi	%hi(15360), %g3
	or	%g3, 1023, %g3
	and	%i4, %g2, %g2
	and	%i5, %g3, %g3
	std	%g2, [%fp-8]
	b	.L29
	 nop
.L30:
	.loc 1 97 0
	ldub	[%fp+72], %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 1
	bne	.L31
	 nop
	.loc 1 98 0
	ld	[%fp+76], %g1
	mov	0, %i4
	mov	%g1, %i5
	mov	0, %g2
	sethi	%hi(16776192), %g3
	or	%g3, 1023, %g3
	and	%i4, %g2, %g2
	and	%i5, %g3, %g3
	std	%g2, [%fp-8]
	b	.L29
	 nop
.L31:
	.loc 1 100 0
	ld	[%fp+76], %g1
	mov	0, %g2
	mov	%g1, %g3
	std	%g2, [%fp-8]
.L29:
	.loc 1 102 0
	ld	[%fp+68], %g1
	srl	%g1, 8, %g1
	st	%g1, [%fp-12]
	.loc 1 103 0
	st	%g0, [%fp-24]
	st	%g0, [%fp-20]
	.loc 1 104 0
	ld	[%fp-12], %g1
	mov	0, %g2
	mov	%g1, %g3
	std	%g2, [%fp-24]
	.loc 1 105 0
	ld	[%fp-20], %g1
	srl	%g1, 20, %g1
	ld	[%fp-24], %g2
	sll	%g2, 12, %g2
	or	%g2, %g1, %g1
	st	%g1, [%fp-24]
	ld	[%fp-20], %g1
	sll	%g1, 12, %g1
	st	%g1, [%fp-20]
	.loc 1 106 0
	ldd	[%fp-24], %i4
	ldd	[%fp-8], %g2
	or	%i4, %g2, %g2
	or	%i5, %g3, %g3
	std	%g2, [%fp-24]
	.loc 1 108 0
	ldd	[%fp-24], %g2
	.loc 1 109 0
	mov	%g2, %i0
	mov	%g3, %i1
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE6:
	.size	ajit_mmap_get_phy_addr_from_pte, .-ajit_mmap_get_phy_addr_from_pte
	.align 4
	.global ajit_mmap_make_ptd
	.type	ajit_mmap_make_ptd, #function
	.proc	016
ajit_mmap_make_ptd:
.LFB7:
	.loc 1 112 0
	.cfi_startproc
	save	%sp, -120, %sp
.LCFI7:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	st	%i1, [%fp-24]
	st	%i2, [%fp-20]
	stb	%g1, [%fp+68]
	.loc 1 113 0
	ldd	[%fp-24], %i4
	std	%i4, [%fp-8]
	.loc 1 114 0
	ld	[%fp-8], %g1
	sll	%g1, 26, %g1
	ld	[%fp-4], %g4
	srl	%g4, 6, %g3
	or	%g1, %g3, %g3
	ld	[%fp-8], %g1
	srl	%g1, 6, %g2
	srl	%g3, 30, %g1
	sll	%g2, 2, %g4
	or	%g4, %g1, %g1
	st	%g1, [%fp-8]
	sll	%g3, 2, %g1
	st	%g1, [%fp-4]
	.loc 1 115 0
	ld	[%fp-4], %g1
	or	%g1, 1, %g1
	st	%g1, [%fp-12]
	.loc 1 116 0
	ld	[%fp-12], %g1
	.loc 1 117 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE7:
	.size	ajit_mmap_make_ptd, .-ajit_mmap_make_ptd
	.align 4
	.global ajit_mmap_make_pte
	.type	ajit_mmap_make_pte, #function
	.proc	016
ajit_mmap_make_pte:
.LFB8:
	.loc 1 120 0
	.cfi_startproc
	save	%sp, -120, %sp
.LCFI8:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g2
	mov	%i1, %g1
	st	%i2, [%fp+76]
	st	%i3, [%fp-24]
	st	%i4, [%fp-20]
	stb	%g2, [%fp+68]
	stb	%g1, [%fp+72]
	.loc 1 121 0
	ld	[%fp-24], %g1
	sll	%g1, 20, %g1
	ld	[%fp-20], %g2
	srl	%g2, 12, %g2
	or	%g2, %g1, %g1
	st	%g1, [%fp-4]
	ld	[%fp-24], %g1
	srl	%g1, 12, %g1
	st	%g1, [%fp-8]
	.loc 1 122 0
	ld	[%fp-4], %g1
	sll	%g1, 8, %g2
	ldub	[%fp+72], %g1
	and	%g1, 0xff, %g1
	sll	%g1, 2, %g1
	or	%g2, %g1, %g1
	or	%g1, 2, %g1
	st	%g1, [%fp-12]
	.loc 1 123 0
	ld	[%fp-12], %g1
	.loc 1 124 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE8:
	.size	ajit_mmap_make_pte, .-ajit_mmap_make_pte
	.align 4
	.global ajit_lookup_mmap
	.type	ajit_lookup_mmap, #function
	.proc	04
ajit_lookup_mmap:
.LFB9:
	.loc 1 151 0
	.cfi_startproc
	save	%sp, -136, %sp
.LCFI9:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	std	%i0, [%fp-40]
	mov	%i2, %g1
	st	%i3, [%fp+80]
	st	%i4, [%fp+84]
	st	%i5, [%fp+88]
	stb	%g1, [%fp+76]
	.loc 1 152 0
	mov	1, %g1
	st	%g1, [%fp-4]
	.loc 1 153 0
	ld	[%fp+84], %g1
	stb	%g0, [%g1]
	.loc 1 154 0
	ld	[%fp+88], %g1
	st	%g0, [%g1]
	st	%g0, [%g1+4]
	.loc 1 155 0
	ld	[%fp+92], %g1
	st	%g0, [%g1]
	st	%g0, [%g1+4]
	.loc 1 156 0
	ld	[%fp+96], %g1
	st	%g0, [%g1]
	.loc 1 162 0
	ldd	[%fp-40], %g2
	std	%g2, [%fp-24]
	.loc 1 163 0
	stb	%g0, [%fp-5]
	.loc 1 165 0
	ldub	[%fp-5], %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	bne	.L38
	 nop
	.loc 1 165 0 is_stmt 0 discriminator 1
	ldub	[%fp+76], %g1
	and	%g1, 0xff, %g1
	b	.L39
	 nop
.L38:
	.loc 1 165 0 discriminator 2
	ldub	[%fp-5], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	ld	[%fp+80], %o1
	call	ajit_mmap_index_into_table, 0
	 nop
	mov	%o0, %g1
.L39:
	.loc 1 164 0 is_stmt 1
	st	%g1, [%fp-28]
	.loc 1 167 0
	ld	[%fp-28], %g1
	sll	%g1, 2, %g1
	mov	0, %i2
	mov	%g1, %i3
	ldd	[%fp-24], %i4
	addcc	%i3, %i5, %g3
	addx	%i2, %i4, %g2
	std	%g2, [%fp-16]
.L45:
.LBB2:
	.loc 1 171 0
	ldd	[%fp-16], %o0
	call	__ajit_load_word_from_physical_address__, 0
	 nop
	st	%o0, [%fp-32]
	.loc 1 179 0
	ld	[%fp+84], %g1
	ldub	[%fp-5], %g2
	stb	%g2, [%g1]
	.loc 1 180 0
	ld	[%fp+92], %g1
	ldd	[%fp-16], %g2
	std	%g2, [%g1]
	.loc 1 181 0
	ld	[%fp+96], %g1
	ld	[%fp-32], %g2
	st	%g2, [%g1]
	.loc 1 184 0
	ld	[%fp-32], %o0
	call	ajit_mmap_is_ptd, 0
	 nop
	mov	%o0, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	be	.L40
	 nop
	.loc 1 187 0
	ldub	[%fp-5], %g1
	add	%g1, 1, %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	ld	[%fp+80], %o1
	call	ajit_mmap_index_into_table, 0
	 nop
	st	%o0, [%fp-28]
	.loc 1 195 0
	ldub	[%fp-5], %g1
	and	%g1, 0xff, %g1
	ld	[%fp-32], %o0
	mov	%g1, %o1
	ld	[%fp-28], %o2
	call	ajit_mmap_get_phy_addr_from_ptd, 0
	 nop
	std	%o0, [%fp-16]
	.loc 1 215 0
	ldub	[%fp-5], %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 3
	be	.L48
	 nop
	b	.L47
	 nop
.L40:
	.loc 1 199 0
	ld	[%fp-32], %o0
	call	ajit_mmap_is_pte, 0
	 nop
	mov	%o0, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	be	.L49
	 nop
	.loc 1 202 0
	ldub	[%fp-5], %g1
	and	%g1, 0xff, %g1
	ld	[%fp-32], %o0
	mov	%g1, %o1
	ld	[%fp+80], %o2
	call	ajit_mmap_get_phy_addr_from_pte, 0
	 nop
	mov	%o0, %g2
	mov	%o1, %g3
	ld	[%fp+88], %g1
	std	%g2, [%g1]
	.loc 1 209 0
	st	%g0, [%fp-4]
	.loc 1 210 0
	b	.L44
	 nop
.L47:
	.loc 1 220 0
	ldub	[%fp-5], %g1
	add	%g1, 1, %g1
	stb	%g1, [%fp-5]
.LBE2:
	.loc 1 221 0
	b	.L45
	 nop
.L48:
.LBB3:
	.loc 1 217 0
	nop
	b	.L44
	 nop
.L49:
	.loc 1 213 0
	nop
.L44:
.LBE3:
	.loc 1 222 0
	ld	[%fp-4], %g1
	.loc 1 223 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE9:
	.size	ajit_lookup_mmap, .-ajit_lookup_mmap
	.section	".rodata"
	.align 8
.LC0:
	.asciz	"ajit_mmap_operation: lookup-status = %d, pdte_level = %d\n"
	.section	".text"
	.align 4
	.global ajit_mmap_operation
	.type	ajit_mmap_operation, #function
	.proc	04
ajit_mmap_operation:
.LFB10:
	.loc 1 250 0
	.cfi_startproc
	save	%sp, -184, %sp
.LCFI10:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp-72]
	st	%i2, [%fp-68]
	mov	%i3, %g3
	mov	%i4, %g2
	mov	%i5, %g1
	stb	%g3, [%fp+80]
	stb	%g2, [%fp+84]
	stb	%g1, [%fp+88]
	ld	[%fp+100], %g1
	st	%g1, [%fp-80]
	ld	[%fp+104], %g1
	st	%g1, [%fp-76]
	.loc 1 256 0
	st	%g0, [%fp-4]
	.loc 1 262 0
	ldub	[%fp+84], %g1
	and	%g1, 0xff, %g3
	add	%fp, -29, %g2
	add	%fp, -56, %g1
	add	%fp, -48, %g4
	st	%g4, [%sp+92]
	add	%fp, -36, %g4
	st	%g4, [%sp+96]
	ldd	[%fp-72], %o0
	mov	%g3, %o2
	ld	[%fp+96], %o3
	mov	%g2, %o4
	mov	%g1, %o5
	call	ajit_lookup_mmap, 0
	 nop
	st	%o0, [%fp-20]
	.loc 1 268 0
	ldub	[%fp-29], %g1
	and	%g1, 0xff, %g1
	sethi	%hi(.LC0), %g2
	or	%g2, %lo(.LC0), %o0
	ld	[%fp-20], %o1
	mov	%g1, %o2
	call	cortos_printf, 0
	 nop
	.loc 1 269 0
	ld	[%fp-20], %g1
	cmp	%g1, 0
	bne	.L51
	 nop
	.loc 1 271 0
	ldub	[%fp+80], %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 1
	bne	.L52
	 nop
	.loc 1 273 0
	ldub	[%fp+88], %g1
	and	%g1, 0xff, %g2
	ldub	[%fp+95], %g1
	and	%g1, 0xff, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	ld	[%fp+96], %o2
	ld	[%fp-80], %o3
	ld	[%fp-76], %o4
	call	ajit_mmap_make_pte, 0
	 nop
	mov	%o0, %g1
	st	%g1, [%fp-36]
	b	.L53
	 nop
.L52:
	.loc 1 275 0
	ldub	[%fp+80], %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 2
	bne	.L53
	 nop
	.loc 1 277 0
	st	%g0, [%fp-36]
.L53:
	.loc 1 280 0
	ld	[%fp-36], %g1
	ldd	[%fp-48], %g2
	mov	%g1, %o0
	mov	%g2, %o1
	mov	%g3, %o2
	call	__ajit_store_word_to_physical_address__, 0
	 nop
	b	.L54
	 nop
.L51:
	.loc 1 283 0
	ldub	[%fp+80], %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 1
	bne	.L55
	 nop
.LBB4:
	.loc 1 294 0
	ldub	[%fp-29], %g1
	stb	%g1, [%fp-5]
	.loc 1 295 0
	ldd	[%fp-48], %g2
	std	%g2, [%fp-16]
	.loc 1 296 0
	b	.L56
	 nop
.L61:
.LBB5:
	.loc 1 303 0
	ldub	[%fp-5], %g1
	add	%g1, 1, %g1
	and	%g1, 0xff, %g2
	add	%fp, -64, %g1
	ld	[%fp+68], %o0
	mov	%g2, %o1
	mov	%g1, %o2
	call	allocatePageTableBlock, 0
	 nop
	st	%o0, [%fp-24]
	.loc 1 305 0
	ld	[%fp-24], %g1
	cmp	%g1, 0
	be	.L57
	 nop
	.loc 1 306 0
	mov	1, %g1
	b	.L62
	 nop
.L57:
	.loc 1 309 0
	ldub	[%fp-5], %g1
	and	%g1, 0xff, %g2
	ldub	[%fp+88], %g1
	and	%g1, 0xff, %g1
	cmp	%g2, %g1
	bne	.L59
	 nop
	.loc 1 311 0
	ldub	[%fp+88], %g1
	and	%g1, 0xff, %g2
	ldub	[%fp+95], %g1
	and	%g1, 0xff, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	ld	[%fp+96], %o2
	ld	[%fp-80], %o3
	ld	[%fp-76], %o4
	call	ajit_mmap_make_pte, 0
	 nop
	mov	%o0, %g1
	st	%g1, [%fp-36]
	b	.L60
	 nop
.L59:
	.loc 1 315 0
	ldd	[%fp-64], %g2
	ldub	[%fp-5], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	mov	%g2, %o1
	mov	%g3, %o2
	call	ajit_mmap_make_ptd, 0
	 nop
	mov	%o0, %g1
	st	%g1, [%fp-36]
.L60:
	.loc 1 317 0
	ld	[%fp-36], %g1
	mov	%g1, %o0
	ld	[%fp-16], %o1
	ld	[%fp-12], %o2
	call	__ajit_store_word_to_physical_address__, 0
	 nop
	.loc 1 323 0
	ldub	[%fp-5], %g1
	add	%g1, 1, %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	ld	[%fp+96], %o1
	call	ajit_mmap_index_into_table, 0
	 nop
	st	%o0, [%fp-28]
	.loc 1 324 0
	ld	[%fp-28], %g1
	sll	%g1, 2, %g1
	mov	0, %i2
	mov	%g1, %i3
	ldd	[%fp-64], %i4
	addcc	%i3, %i5, %g3
	addx	%i2, %i4, %g2
	std	%g2, [%fp-16]
	.loc 1 325 0
	ldub	[%fp-5], %g1
	add	%g1, 1, %g1
	stb	%g1, [%fp-5]
.L56:
.LBE5:
	.loc 1 296 0 discriminator 1
	ldub	[%fp-5], %g1
	and	%g1, 0xff, %g2
	ldub	[%fp+88], %g1
	and	%g1, 0xff, %g1
	cmp	%g2, %g1
	bleu	.L61
	 nop
	.loc 1 296 0 is_stmt 0
	b	.L54
	 nop
.L55:
.LBE4:
	.loc 1 331 0 is_stmt 1
	st	%g0, [%fp-4]
.L54:
	.loc 1 334 0
	ld	[%fp-4], %g1
.L62:
	.loc 1 335 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE10:
	.size	ajit_mmap_operation, .-ajit_mmap_operation
.Letext0:
	.file 2 "/home/ajit4/ajit-toolchain/build/buildroot-2014.08/output/host/usr/lib/gcc/sparc-buildroot-linux-uclibc/4.7.4/include/stdint-gcc.h"
	.file 3 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/include/ajit_mmap.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.uaword	0x658
	.uahalf	0x2
	.uaword	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.uaword	.LASF60
	.byte	0x1
	.uaword	.LASF61
	.uaword	.Ltext0
	.uaword	.Letext0
	.uaword	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.uaword	.LASF0
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.uaword	.LASF1
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.asciz	"int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.uaword	.LASF2
	.uleb128 0x4
	.uaword	.LASF5
	.byte	0x2
	.byte	0x2e
	.uaword	0x48
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.uaword	.LASF3
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.uaword	.LASF4
	.uleb128 0x4
	.uaword	.LASF6
	.byte	0x2
	.byte	0x34
	.uaword	0x61
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF7
	.uleb128 0x4
	.uaword	.LASF8
	.byte	0x2
	.byte	0x37
	.uaword	0x73
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.uaword	.LASF9
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF10
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.uaword	.LASF11
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF12
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.uaword	.LASF13
	.uleb128 0x5
	.uaword	.LASF62
	.byte	0x18
	.byte	0x3
	.byte	0x11
	.uaword	0xcd
	.uleb128 0x6
	.uaword	.LASF14
	.byte	0x3
	.byte	0x12
	.uaword	0x68
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x6
	.uaword	.LASF15
	.byte	0x3
	.byte	0x13
	.uaword	0x68
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x6
	.uaword	.LASF16
	.byte	0x3
	.byte	0x14
	.uaword	0x68
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.byte	0
	.uleb128 0x4
	.uaword	.LASF17
	.byte	0x3
	.byte	0x16
	.uaword	0x96
	.uleb128 0x7
	.byte	0x1
	.uaword	.LASF48
	.byte	0x1
	.byte	0x9
	.byte	0x1
	.uaword	.LFB0
	.uaword	.LFE0
	.uaword	.LLST0
	.byte	0x1
	.uaword	0x12b
	.uleb128 0x8
	.asciz	"pts"
	.byte	0x1
	.byte	0x9
	.uaword	0x12b
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x9
	.uaword	.LASF18
	.byte	0x1
	.byte	0x9
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x9
	.uaword	.LASF15
	.byte	0x1
	.byte	0x9
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 80
	.uleb128 0xa
	.asciz	"I"
	.byte	0x1
	.byte	0xc
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.uaword	0xcd
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF24
	.byte	0x1
	.byte	0x1b
	.byte	0x1
	.uaword	0x56
	.uaword	.LFB1
	.uaword	.LFE1
	.uaword	.LLST1
	.byte	0x1
	.uaword	0x1a7
	.uleb128 0x8
	.asciz	"pts"
	.byte	0x1
	.byte	0x1b
	.uaword	0x12b
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x9
	.uaword	.LASF19
	.byte	0x1
	.byte	0x1b
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0x9
	.uaword	.LASF20
	.byte	0x1
	.byte	0x1b
	.uaword	0x1a7
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0xd
	.uaword	.LASF21
	.byte	0x1
	.byte	0x1d
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0xd
	.uaword	.LASF22
	.byte	0x1
	.byte	0x1e
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0xd
	.uaword	.LASF23
	.byte	0x1
	.byte	0x24
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.uaword	0x68
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF25
	.byte	0x1
	.byte	0x2f
	.byte	0x1
	.uaword	0x56
	.uaword	.LFB2
	.uaword	.LFE2
	.uaword	.LLST2
	.byte	0x1
	.uaword	0x1f7
	.uleb128 0x9
	.uaword	.LASF19
	.byte	0x1
	.byte	0x2f
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x8
	.asciz	"va"
	.byte	0x1
	.byte	0x2f
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0xd
	.uaword	.LASF21
	.byte	0x1
	.byte	0x31
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF26
	.byte	0x1
	.byte	0x43
	.byte	0x1
	.uaword	0x3d
	.uaword	.LFB3
	.uaword	.LFE3
	.uaword	.LLST3
	.byte	0x1
	.uaword	0x232
	.uleb128 0x9
	.uaword	.LASF27
	.byte	0x1
	.byte	0x43
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xa
	.asciz	"rv"
	.byte	0x1
	.byte	0x45
	.uaword	0x3d
	.byte	0x2
	.byte	0x91
	.sleb128 -1
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF28
	.byte	0x1
	.byte	0x49
	.byte	0x1
	.uaword	0x3d
	.uaword	.LFB4
	.uaword	.LFE4
	.uaword	.LLST4
	.byte	0x1
	.uaword	0x26d
	.uleb128 0x9
	.uaword	.LASF27
	.byte	0x1
	.byte	0x49
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xa
	.asciz	"rv"
	.byte	0x1
	.byte	0x4b
	.uaword	0x3d
	.byte	0x2
	.byte	0x91
	.sleb128 -1
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF29
	.byte	0x1
	.byte	0x4f
	.byte	0x1
	.uaword	0x68
	.uaword	.LFB5
	.uaword	.LFE5
	.uaword	.LLST5
	.byte	0x1
	.uaword	0x2c7
	.uleb128 0x8
	.asciz	"ptd"
	.byte	0x1
	.byte	0x4f
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x9
	.uaword	.LASF19
	.byte	0x1
	.byte	0x4f
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0x9
	.uaword	.LASF30
	.byte	0x1
	.byte	0x4f
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0xd
	.uaword	.LASF31
	.byte	0x1
	.byte	0x51
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF32
	.byte	0x1
	.byte	0x5a
	.byte	0x1
	.uaword	0x68
	.uaword	.LFB6
	.uaword	.LFE6
	.uaword	.LLST6
	.byte	0x1
	.uaword	0x33b
	.uleb128 0x8
	.asciz	"pte"
	.byte	0x1
	.byte	0x5a
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x9
	.uaword	.LASF19
	.byte	0x1
	.byte	0x5a
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0x8
	.asciz	"va"
	.byte	0x1
	.byte	0x5a
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0xd
	.uaword	.LASF33
	.byte	0x1
	.byte	0x5c
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0xa
	.asciz	"ppn"
	.byte	0x1
	.byte	0x66
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0xa
	.asciz	"pa"
	.byte	0x1
	.byte	0x67
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF34
	.byte	0x1
	.byte	0x6f
	.byte	0x1
	.uaword	0x56
	.uaword	.LFB7
	.uaword	.LFE7
	.uaword	.LLST7
	.byte	0x1
	.uaword	0x392
	.uleb128 0x9
	.uaword	.LASF19
	.byte	0x1
	.byte	0x6f
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x8
	.asciz	"pa"
	.byte	0x1
	.byte	0x6f
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xd
	.uaword	.LASF35
	.byte	0x1
	.byte	0x71
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0xa
	.asciz	"ptd"
	.byte	0x1
	.byte	0x73
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF36
	.byte	0x1
	.byte	0x77
	.byte	0x1
	.uaword	0x56
	.uaword	.LFB8
	.uaword	.LFE8
	.uaword	.LLST8
	.byte	0x1
	.uaword	0x406
	.uleb128 0x9
	.uaword	.LASF19
	.byte	0x1
	.byte	0x77
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x8
	.asciz	"acc"
	.byte	0x1
	.byte	0x77
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0x8
	.asciz	"va"
	.byte	0x1
	.byte	0x77
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0x8
	.asciz	"pa"
	.byte	0x1
	.byte	0x77
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xd
	.uaword	.LASF37
	.byte	0x1
	.byte	0x79
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0xa
	.asciz	"pte"
	.byte	0x1
	.byte	0x7a
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0xe
	.byte	0x1
	.uaword	.LASF38
	.byte	0x1
	.byte	0x87
	.byte	0x1
	.uaword	0x2f
	.uaword	.LFB9
	.uaword	.LFE9
	.uaword	.LLST9
	.byte	0x1
	.uaword	0x4e5
	.uleb128 0x9
	.uaword	.LASF39
	.byte	0x1
	.byte	0x89
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x9
	.uaword	.LASF40
	.byte	0x1
	.byte	0x8b
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0x8
	.asciz	"va"
	.byte	0x1
	.byte	0x8d
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 80
	.uleb128 0x9
	.uaword	.LASF19
	.byte	0x1
	.byte	0x8f
	.uaword	0x4e5
	.byte	0x3
	.byte	0x91
	.sleb128 84
	.uleb128 0x8
	.asciz	"pa"
	.byte	0x1
	.byte	0x91
	.uaword	0x1a7
	.byte	0x3
	.byte	0x91
	.sleb128 88
	.uleb128 0x9
	.uaword	.LASF41
	.byte	0x1
	.byte	0x93
	.uaword	0x1a7
	.byte	0x3
	.byte	0x91
	.sleb128 92
	.uleb128 0x9
	.uaword	.LASF42
	.byte	0x1
	.byte	0x96
	.uaword	0x4eb
	.byte	0x3
	.byte	0x91
	.sleb128 96
	.uleb128 0xd
	.uaword	.LASF21
	.byte	0x1
	.byte	0x98
	.uaword	0x2f
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0xd
	.uaword	.LASF43
	.byte	0x1
	.byte	0xa2
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xd
	.uaword	.LASF44
	.byte	0x1
	.byte	0xa3
	.uaword	0x3d
	.byte	0x2
	.byte	0x91
	.sleb128 -5
	.uleb128 0xd
	.uaword	.LASF45
	.byte	0x1
	.byte	0xa4
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xd
	.uaword	.LASF46
	.byte	0x1
	.byte	0xa7
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0xf
	.uaword	.Ldebug_ranges0+0
	.uleb128 0xd
	.uaword	.LASF47
	.byte	0x1
	.byte	0xab
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.uaword	0x3d
	.uleb128 0xb
	.byte	0x4
	.uaword	0x56
	.uleb128 0x10
	.byte	0x1
	.uaword	.LASF49
	.byte	0x1
	.byte	0xe8
	.byte	0x1
	.uaword	0x2f
	.uaword	.LFB10
	.uaword	.LFE10
	.uaword	.LLST10
	.byte	0x1
	.uleb128 0x8
	.asciz	"pts"
	.byte	0x1
	.byte	0xea
	.uaword	0x12b
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x9
	.uaword	.LASF50
	.byte	0x1
	.byte	0xec
	.uaword	0x68
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x9
	.uaword	.LASF51
	.byte	0x1
	.byte	0xee
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 80
	.uleb128 0x9
	.uaword	.LASF40
	.byte	0x1
	.byte	0xf0
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 84
	.uleb128 0x9
	.uaword	.LASF19
	.byte	0x1
	.byte	0xf2
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 88
	.uleb128 0x8
	.asciz	"acc"
	.byte	0x1
	.byte	0xf4
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 95
	.uleb128 0x8
	.asciz	"va"
	.byte	0x1
	.byte	0xf6
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 96
	.uleb128 0x8
	.asciz	"pa"
	.byte	0x1
	.byte	0xf8
	.uaword	0x68
	.byte	0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x11
	.uaword	.LASF21
	.byte	0x1
	.uahalf	0x100
	.uaword	0x2f
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0x11
	.uaword	.LASF52
	.byte	0x1
	.uahalf	0x102
	.uaword	0x3d
	.byte	0x2
	.byte	0x91
	.sleb128 -29
	.uleb128 0x11
	.uaword	.LASF53
	.byte	0x1
	.uahalf	0x103
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x11
	.uaword	.LASF54
	.byte	0x1
	.uahalf	0x104
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x11
	.uaword	.LASF55
	.byte	0x1
	.uahalf	0x105
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x11
	.uaword	.LASF56
	.byte	0x1
	.uahalf	0x106
	.uaword	0x2f
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x12
	.byte	0x1
	.uaword	.LASF63
	.byte	0x1
	.uahalf	0x10c
	.uaword	0x2f
	.byte	0x1
	.uaword	0x5ef
	.uleb128 0x13
	.byte	0
	.uleb128 0x14
	.uaword	.LBB4
	.uaword	.LBE4
	.uleb128 0x11
	.uaword	.LASF44
	.byte	0x1
	.uahalf	0x126
	.uaword	0x3d
	.byte	0x2
	.byte	0x91
	.sleb128 -5
	.uleb128 0x11
	.uaword	.LASF57
	.byte	0x1
	.uahalf	0x127
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x14
	.uaword	.LBB5
	.uaword	.LBE5
	.uleb128 0x11
	.uaword	.LASF58
	.byte	0x1
	.uahalf	0x12e
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x11
	.uaword	.LASF59
	.byte	0x1
	.uahalf	0x12f
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x15
	.uaword	.LASF64
	.byte	0x1
	.uahalf	0x134
	.uaword	0x56
	.uleb128 0x11
	.uaword	.LASF45
	.byte	0x1
	.uahalf	0x143
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.uaword	.LFB0-.Ltext0
	.uaword	.LCFI0-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI0-.Ltext0
	.uaword	.LFE0-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST1:
	.uaword	.LFB1-.Ltext0
	.uaword	.LCFI1-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI1-.Ltext0
	.uaword	.LFE1-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST2:
	.uaword	.LFB2-.Ltext0
	.uaword	.LCFI2-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI2-.Ltext0
	.uaword	.LFE2-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST3:
	.uaword	.LFB3-.Ltext0
	.uaword	.LCFI3-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI3-.Ltext0
	.uaword	.LFE3-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST4:
	.uaword	.LFB4-.Ltext0
	.uaword	.LCFI4-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI4-.Ltext0
	.uaword	.LFE4-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST5:
	.uaword	.LFB5-.Ltext0
	.uaword	.LCFI5-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI5-.Ltext0
	.uaword	.LFE5-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST6:
	.uaword	.LFB6-.Ltext0
	.uaword	.LCFI6-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI6-.Ltext0
	.uaword	.LFE6-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST7:
	.uaword	.LFB7-.Ltext0
	.uaword	.LCFI7-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI7-.Ltext0
	.uaword	.LFE7-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST8:
	.uaword	.LFB8-.Ltext0
	.uaword	.LCFI8-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI8-.Ltext0
	.uaword	.LFE8-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST9:
	.uaword	.LFB9-.Ltext0
	.uaword	.LCFI9-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI9-.Ltext0
	.uaword	.LFE9-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST10:
	.uaword	.LFB10-.Ltext0
	.uaword	.LCFI10-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI10-.Ltext0
	.uaword	.LFE10-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
	.section	.debug_aranges,"",@progbits
	.uaword	0x1c
	.uahalf	0x2
	.uaword	.Ldebug_info0
	.byte	0x4
	.byte	0
	.uahalf	0
	.uahalf	0
	.uaword	.Ltext0
	.uaword	.Letext0-.Ltext0
	.uaword	0
	.uaword	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.uaword	.LBB2-.Ltext0
	.uaword	.LBE2-.Ltext0
	.uaword	.LBB3-.Ltext0
	.uaword	.LBE3-.Ltext0
	.uaword	0
	.uaword	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF23:
	.asciz	"next_free_pointer"
.LASF8:
	.asciz	"uint64_t"
.LASF27:
	.asciz	"entry"
.LASF9:
	.asciz	"long long unsigned int"
.LASF37:
	.asciz	"ppn_64"
.LASF2:
	.asciz	"long long int"
.LASF0:
	.asciz	"signed char"
.LASF22:
	.asciz	"request_size"
.LASF38:
	.asciz	"ajit_lookup_mmap"
.LASF58:
	.asciz	"allocated_block_address"
.LASF11:
	.asciz	"long int"
.LASF20:
	.asciz	"block_base_address"
.LASF55:
	.asciz	"ign_pa"
.LASF28:
	.asciz	"ajit_mmap_is_ptd"
.LASF26:
	.asciz	"ajit_mmap_is_pte"
.LASF39:
	.asciz	"page_table_base_phy_addr"
.LASF7:
	.asciz	"unsigned int"
.LASF10:
	.asciz	"long unsigned int"
.LASF46:
	.asciz	"current_entry_address"
.LASF19:
	.asciz	"level"
.LASF4:
	.asciz	"short unsigned int"
.LASF45:
	.asciz	"index_into_table"
.LASF18:
	.asciz	"base_addr"
.LASF16:
	.asciz	"free_pointer"
.LASF12:
	.asciz	"sizetype"
.LASF35:
	.asciz	"pa_shifted"
.LASF31:
	.asciz	"phy_addr"
.LASF53:
	.asciz	"pdte"
.LASF42:
	.asciz	"ptde"
.LASF51:
	.asciz	"operation"
.LASF48:
	.asciz	"initPageTableAllocator"
.LASF33:
	.asciz	"page_offset"
.LASF60:
	.asciz	"GNU C 4.7.4"
.LASF63:
	.asciz	"cortos_printf"
.LASF62:
	.asciz	"__PageTableAllocator"
.LASF57:
	.asciz	"current_pdte_a"
.LASF3:
	.asciz	"unsigned char"
.LASF52:
	.asciz	"pdte_level"
.LASF49:
	.asciz	"ajit_mmap_operation"
.LASF41:
	.asciz	"ptde_a"
.LASF1:
	.asciz	"short int"
.LASF54:
	.asciz	"pdte_a"
.LASF47:
	.asciz	"current_entry"
.LASF59:
	.asciz	"alloc_status"
.LASF21:
	.asciz	"ret_val"
.LASF6:
	.asciz	"uint32_t"
.LASF50:
	.asciz	"page_table_base_phy_address"
.LASF13:
	.asciz	"char"
.LASF29:
	.asciz	"ajit_mmap_get_phy_addr_from_ptd"
.LASF32:
	.asciz	"ajit_mmap_get_phy_addr_from_pte"
.LASF34:
	.asciz	"ajit_mmap_make_ptd"
.LASF36:
	.asciz	"ajit_mmap_make_pte"
.LASF40:
	.asciz	"context"
.LASF43:
	.asciz	"context_table_base_address"
.LASF15:
	.asciz	"allocated_size"
.LASF25:
	.asciz	"ajit_mmap_index_into_table"
.LASF56:
	.asciz	"status"
.LASF17:
	.asciz	"PageTableAllocator"
.LASF61:
	.asciz	"/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_mmap.c"
.LASF5:
	.asciz	"uint8_t"
.LASF30:
	.asciz	"index"
.LASF24:
	.asciz	"allocatePageTableBlock"
.LASF44:
	.asciz	"current_level"
.LASF14:
	.asciz	"base_physical_address"
.LASF64:
	.asciz	"new_ptde"
	.ident	"GCC: (Buildroot 2014.08-ga2bdb80-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
