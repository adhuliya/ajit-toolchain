	.file	"AjitBootloader.c"
	.section	".text"
	.align 4
	.type	mmu_bypass_load, #function
	.proc	016
mmu_bypass_load:
	save	%sp, -104, %sp
	st	%i0, [%fp+68]
	ld	[%fp+68], %g1
#APP
! 20 "Ajit_putchar.h" 1
	lda [%g1] 32, %i5
	
! 0 "" 2
#NO_APP
	st	%i5, [%fp-4]
	ld	[%fp-4], %g1
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	mmu_bypass_load, .-mmu_bypass_load
	.align 4
	.type	mmu_bypass_store, #function
	.proc	020
mmu_bypass_store:
	save	%sp, -96, %sp
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	ld	[%fp+68], %g1
	ld	[%fp+72], %g2
#APP
! 35 "Ajit_putchar.h" 1
	sta %g1, [%g2] 32
	
! 0 "" 2
#NO_APP
	restore
	jmp	%o7+8
	 nop
	.size	mmu_bypass_store, .-mmu_bypass_store
	.align 4
	.type	mmu_bypass_store_byte, #function
	.proc	020
mmu_bypass_store_byte:
	save	%sp, -96, %sp
	mov	%i0, %g1
	st	%i1, [%fp+72]
	stb	%g1, [%fp+68]
	ldub	[%fp+68], %g1
	ld	[%fp+72], %g2
#APP
! 42 "Ajit_putchar.h" 1
	stuba %g1, [%g2] 32
	
! 0 "" 2
#NO_APP
	restore
	jmp	%o7+8
	 nop
	.size	mmu_bypass_store_byte, .-mmu_bypass_store_byte
	.align 4
	.type	enableTx, #function
	.proc	020
enableTx:
	save	%sp, -104, %sp
	sethi	%hi(-53248), %g1
	or	%g1, 512, %o0
	call	mmu_bypass_load, 0
	 nop
	st	%o0, [%fp-4]
	ld	[%fp-4], %g1
	or	%g1, 1, %g1
	st	%g1, [%fp-4]
	ld	[%fp-4], %o0
	sethi	%hi(-53248), %g1
	or	%g1, 512, %o1
	call	mmu_bypass_store, 0
	 nop
	restore
	jmp	%o7+8
	 nop
	.size	enableTx, .-enableTx
	.align 4
	.type	writetoTx, #function
	.proc	020
writetoTx:
	save	%sp, -96, %sp
	mov	%i0, %g1
	stb	%g1, [%fp+68]
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	sethi	%hi(-53248), %g1
	or	%g1, 528, %o1
	call	mmu_bypass_store_byte, 0
	 nop
	restore
	jmp	%o7+8
	 nop
	.size	writetoTx, .-writetoTx
	.align 4
	.type	getTxfull, #function
	.proc	014
getTxfull:
	save	%sp, -104, %sp
	sethi	%hi(-53248), %g1
	or	%g1, 512, %o0
	call	mmu_bypass_load, 0
	 nop
	st	%o0, [%fp-4]
	ld	[%fp-4], %g1
	and	%g1, 8, %g1
	st	%g1, [%fp-4]
	ld	[%fp-4], %g1
	cmp	%g1, 0
	be	.L8
	 nop
	mov	1, %g1
	b	.L9
	 nop
.L8:
	mov	0, %g1
.L9:
	and	%g1, 0xff, %g1
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	getTxfull, .-getTxfull
	.align 4
	.type	pv_nbputchar, #function
	.proc	04
pv_nbputchar:
	save	%sp, -96, %sp
	st	%i0, [%fp+68]
	call	enableTx, 0
	 nop
	ld	[%fp+68], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	mov	%g1, %o0
	call	writetoTx, 0
	 nop
	b	.L13
	 nop
.L15:
	nop
.L13:
	call	getTxfull, 0
	 nop
	mov	%o0, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	bne	.L15
	 nop
	nop
	mov	1, %g1
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	pv_nbputchar, .-pv_nbputchar
	.align 4
	.type	ajit_putstring, #function
	.proc	04
ajit_putstring:
	save	%sp, -104, %sp
	st	%i0, [%fp+68]
	st	%g0, [%fp-4]
.L19:
	ld	[%fp-4], %g1
	ld	[%fp+68], %g2
	add	%g2, %g1, %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	mov	%g1, %o0
	call	pv_nbputchar, 0
	 nop
	ld	[%fp-4], %g1
	ld	[%fp+68], %g2
	add	%g2, %g1, %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 0
	be	.L22
	 nop
.L17:
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-4]
	b	.L19
	 nop
.L22:
	nop
.L21:
	mov	0, %g1
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	ajit_putstring, .-ajit_putstring
	.global null_ptr
	.section	".bss"
	.align 4
	.type	null_ptr, #object
	.size	null_ptr, 4
null_ptr:
	.skip	4
	.common	Ajit_romvec,280,4
	.global Ajit_romvec_ptr
	.section	".data"
	.align 4
	.type	Ajit_romvec_ptr, #object
	.size	Ajit_romvec_ptr, 4
Ajit_romvec_ptr:
	.long	Ajit_romvec
	.global totphys
	.align 4
	.type	totphys, #object
	.size	totphys, 12
totphys:
	.long	0
	.long	-268435456
	.long	8388608
	.global avail
	.align 4
	.type	avail, #object
	.size	avail, 12
avail:
	.long	0
	.long	-268435456
	.long	8388608
	.global totphys_p
	.align 4
	.type	totphys_p, #object
	.size	totphys_p, 4
totphys_p:
	.long	totphys
	.global avail_p
	.align 4
	.type	avail_p, #object
	.size	avail_p, 4
avail_p:
	.long	avail
	.global AJIT_PROMDEV_TTYA
	.type	AJIT_PROMDEV_TTYA, #object
	.size	AJIT_PROMDEV_TTYA, 1
AJIT_PROMDEV_TTYA:
	.byte	1
	.local	EMPTY_sync_hook
	.common	EMPTY_sync_hook,4,4
	.section	".text"
	.align 4
	.global get_Ajit_romvec
	.type	get_Ajit_romvec, #function
	.proc	0110
get_Ajit_romvec:
	save	%sp, -96, %sp
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+4]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+8]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+12]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	sethi	%hi(totphys_p), %g2
	or	%g2, %lo(totphys_p), %g2
	st	%g2, [%g1+16]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	sethi	%hi(null_ptr), %g2
	or	%g2, %lo(null_ptr), %g2
	st	%g2, [%g1+20]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	sethi	%hi(avail_p), %g2
	or	%g2, %lo(avail_p), %g2
	st	%g2, [%g1+24]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+32]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+80]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+84]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+88]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+96]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+100]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+104]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+108]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+112]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+116]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+132]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+260]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+124]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+124]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g0, [%g1+72]
	sethi	%hi(null_ptr), %g1
	or	%g1, %lo(null_ptr), %g1
	ld	[%g1], %g2
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	st	%g2, [%g1+128]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	sethi	%hi(EMPTY_sync_hook), %g2
	or	%g2, %lo(EMPTY_sync_hook), %g2
	st	%g2, [%g1+120]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	sethi	%hi(AJIT_PROMDEV_TTYA), %g2
	or	%g2, %lo(AJIT_PROMDEV_TTYA), %g2
	st	%g2, [%g1+76]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	sethi	%hi(pv_nbputchar), %g2
	or	%g2, %lo(pv_nbputchar), %g2
	st	%g2, [%g1+92]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	sethi	%hi(dt_blob_start), %g2
	or	%g2, %lo(dt_blob_start), %g2
	st	%g2, [%g1+28]
	sethi	%hi(Ajit_romvec), %g1
	or	%g1, %lo(Ajit_romvec), %g1
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	get_Ajit_romvec, .-get_Ajit_romvec
	.section	.text.main,"ax",@progbits
	.align 4
	.global main
	.type	main, #function
	.proc	020
main:
	save	%sp, -96, %sp
#APP
! 70 "AjitBootloader.c" 1
	mov %g0, %g1 
	 
! 0 "" 2
! 70 "AjitBootloader.c" 1
	mov %g0, %g2 
	 
! 0 "" 2
! 71 "AjitBootloader.c" 1
	mov %g0, %g3 
	 
! 0 "" 2
! 71 "AjitBootloader.c" 1
	mov %g0, %g4 
	 
! 0 "" 2
! 72 "AjitBootloader.c" 1
	mov %g0, %g5 
	 
! 0 "" 2
! 72 "AjitBootloader.c" 1
	mov %g0, %g6 
	 
! 0 "" 2
! 73 "AjitBootloader.c" 1
	mov %g0, %g7 
	 
! 0 "" 2
! 75 "AjitBootloader.c" 1
	mov %g0, %i0 
	 
! 0 "" 2
! 75 "AjitBootloader.c" 1
	mov %g0, %i1 
	 
! 0 "" 2
! 76 "AjitBootloader.c" 1
	mov %g0, %i2 
	 
! 0 "" 2
! 76 "AjitBootloader.c" 1
	mov %g0, %i3 
	 
! 0 "" 2
! 77 "AjitBootloader.c" 1
	mov %g0, %i4 
	 
! 0 "" 2
! 77 "AjitBootloader.c" 1
	mov %g0, %i5 
	 
! 0 "" 2
! 78 "AjitBootloader.c" 1
	mov %g0, %i6 
	 
! 0 "" 2
! 78 "AjitBootloader.c" 1
	mov %g0, %i7 
	 
! 0 "" 2
! 80 "AjitBootloader.c" 1
	mov %g0, %l0 
	 
! 0 "" 2
! 80 "AjitBootloader.c" 1
	mov %g0, %l1 
	 
! 0 "" 2
! 81 "AjitBootloader.c" 1
	mov %g0, %l2 
	 
! 0 "" 2
! 81 "AjitBootloader.c" 1
	mov %g0, %l3 
	 
! 0 "" 2
! 82 "AjitBootloader.c" 1
	mov %g0, %l4 
	 
! 0 "" 2
! 82 "AjitBootloader.c" 1
	mov %g0, %l5 
	 
! 0 "" 2
! 83 "AjitBootloader.c" 1
	mov %g0, %l6 
	 
! 0 "" 2
! 83 "AjitBootloader.c" 1
	mov %g0, %l7 
	 
! 0 "" 2
! 85 "AjitBootloader.c" 1
	mov %g0, %o0 
	 
! 0 "" 2
! 85 "AjitBootloader.c" 1
	mov %g0, %o1 
	 
! 0 "" 2
! 86 "AjitBootloader.c" 1
	mov %g0, %o2 
	 
! 0 "" 2
! 86 "AjitBootloader.c" 1
	mov %g0, %o3 
	 
! 0 "" 2
! 87 "AjitBootloader.c" 1
	mov %g0, %o4 
	 
! 0 "" 2
! 87 "AjitBootloader.c" 1
	mov %g0, %o5 
	 
! 0 "" 2
! 88 "AjitBootloader.c" 1
	mov %g0, %o6 
	 
! 0 "" 2
! 88 "AjitBootloader.c" 1
	mov %g0, %o7 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	save
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %l0 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %l1 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %l2 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %l3 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %l4 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %l5 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %l6 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %l7 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %o0 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %o1 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %o2 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %o3 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %o4 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %o5 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %o6 
	 
! 0 "" 2
! 91 "AjitBootloader.c" 1
	mov %g0, %o7 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	save
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %l0 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %l1 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %l2 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %l3 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %l4 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %l5 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %l6 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %l7 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %o0 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %o1 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %o2 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %o3 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %o4 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %o5 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %o6 
	 
! 0 "" 2
! 92 "AjitBootloader.c" 1
	mov %g0, %o7 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	save
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %l0 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %l1 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %l2 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %l3 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %l4 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %l5 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %l6 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %l7 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %o0 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %o1 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %o2 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %o3 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %o4 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %o5 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %o6 
	 
! 0 "" 2
! 93 "AjitBootloader.c" 1
	mov %g0, %o7 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	save
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %l0 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %l1 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %l2 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %l3 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %l4 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %l5 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %l6 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %l7 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %o0 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %o1 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %o2 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %o3 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %o4 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %o5 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %o6 
	 
! 0 "" 2
! 94 "AjitBootloader.c" 1
	mov %g0, %o7 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	save
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %l0 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %l1 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %l2 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %l3 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %l4 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %l5 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %l6 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %l7 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %o0 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %o1 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %o2 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %o3 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %o4 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %o5 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %o6 
	 
! 0 "" 2
! 95 "AjitBootloader.c" 1
	mov %g0, %o7 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	save
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %l0 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %l1 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %l2 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %l3 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %l4 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %l5 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %l6 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %l7 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %o0 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %o1 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %o2 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %o3 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %o4 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %o5 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %o6 
	 
! 0 "" 2
! 96 "AjitBootloader.c" 1
	mov %g0, %o7 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	save
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %l0 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %l1 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %l2 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %l3 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %l4 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %l5 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %l6 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %l7 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %o0 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %o1 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %o2 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %o3 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %o4 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %o5 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %o6 
	 
! 0 "" 2
! 97 "AjitBootloader.c" 1
	mov %g0, %o7 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	save
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %l0 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %l1 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %l2 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %l3 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %l4 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %l5 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %l6 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %l7 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %o0 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %o1 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %o2 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %o3 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %o4 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %o5 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %o6 
	 
! 0 "" 2
! 98 "AjitBootloader.c" 1
	mov %g0, %o7 
	 
! 0 "" 2
! 100 "AjitBootloader.c" 1
	restore
	 
! 0 "" 2
! 101 "AjitBootloader.c" 1
	restore
	 
! 0 "" 2
! 102 "AjitBootloader.c" 1
	restore
	 
! 0 "" 2
! 103 "AjitBootloader.c" 1
	restore
	 
! 0 "" 2
! 104 "AjitBootloader.c" 1
	restore
	 
! 0 "" 2
! 105 "AjitBootloader.c" 1
	restore
	 
! 0 "" 2
! 106 "AjitBootloader.c" 1
	restore
	 
! 0 "" 2
! 107 "AjitBootloader.c" 1
	restore
	 
! 0 "" 2
#NO_APP
	sethi	%hi(-268423168), %g1
#APP
! 110 "AjitBootloader.c" 1
	mov %g1, %sp
	
! 0 "" 2
#NO_APP
	call	bootloader, 0
	 nop
	restore
	jmp	%o7+8
	 nop
	.size	main, .-main
	.section	".rodata"
	.align 8
.LC0:
	.asciz	"\n Ajit Bootloader\n"
	.section	.text.main
	.align 4
	.global bootloader
	.type	bootloader, #function
	.proc	04
bootloader:
	save	%sp, -112, %sp
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %o0
	call	ajit_putstring, 0
	 nop
	sethi	%hi(-268431360), %g1
	st	%g1, [%fp-4]
	ld	[%fp-4], %g1
	sethi	%hi(251658240), %g2
	or	%g2, 513, %g2
	st	%g2, [%g1]
	sethi	%hi(-268427264), %g1
	st	%g1, [%fp-8]
	ld	[%fp-8], %g1
	add	%g1, 960, %g1
	sethi	%hi(251658240), %g2
	or	%g2, 158, %g2
	st	%g2, [%g1]
	sethi	%hi(251658240), %g1
	or	%g1, 256, %g1
	st	%g1, [%fp-12]
	mov	0, %g1
	mov	512, %g2
#APP
! 150 "AjitBootloader.c" 1
	sta %g1, [%g2] 4
	
! 0 "" 2
#NO_APP
	ld	[%fp-12], %g1
	mov	256, %g2
#APP
! 152 "AjitBootloader.c" 1
	sta %g1, [%g2] 4
	
! 0 "" 2
#NO_APP
	call	get_Ajit_romvec, 0
	 nop
	mov	%o0, %g1
	st	%g1, [%fp-16]
	ld	[%fp-16], %g1
#APP
! 161 "AjitBootloader.c" 1
	mov %g1, %o0 
	
! 0 "" 2
#NO_APP
	mov	1, %g1
	mov	0, %g2
#APP
! 169 "AjitBootloader.c" 1
	sta %g1, [%g2] 4
	
! 0 "" 2
! 171 "AjitBootloader.c" 1
	set 0xf0004000, %g2 
	 			      jmpl %g2, %g0
	
! 0 "" 2
! 173 "AjitBootloader.c" 1
	nop 
	 			      nop 
	 			      nop 
	
! 0 "" 2
! 180 "AjitBootloader.c" 1
	ta 0 
	 			      nop 
	 			      nop 
	
! 0 "" 2
#NO_APP
	mov	0, %g1
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	bootloader, .-bootloader
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
