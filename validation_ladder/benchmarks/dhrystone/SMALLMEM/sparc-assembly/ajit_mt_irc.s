	.file	"ajit_mt_irc.c"
	.section	".text"
	.align 4
	.global readInterruptControlRegister
	.type	readInterruptControlRegister, #function
	.proc	016
readInterruptControlRegister:
	add	%o0, %o0, %o0
	sethi	%hi(-53248), %g1
	add	%o0, %o1, %o1
	sll	%o1, 2, %o0
	add	%o0, %g1, %o0
	or	%o7, %g0, %g1
	call	__ajit_load_word_mmu_bypass__, 0
	 or	%g1, %g0, %o7
	.size	readInterruptControlRegister, .-readInterruptControlRegister
	.align 4
	.global writeInterruptControlRegister
	.type	writeInterruptControlRegister, #function
	.proc	020
writeInterruptControlRegister:
	add	%o0, %o0, %o0
	sethi	%hi(-53248), %g1
	add	%o0, %o1, %o0
	mov	%o2, %o1
	sll	%o0, 2, %o0
	add	%o0, %g1, %o0
	or	%o7, %g0, %g1
	call	__ajit_store_word_mmu_bypass__, 0
	 or	%g1, %g0, %o7
	.size	writeInterruptControlRegister, .-writeInterruptControlRegister
	.align 4
	.global enableInterruptController
	.type	enableInterruptController, #function
	.proc	020
enableInterruptController:
	save	%sp, -96, %sp
	sethi	%hi(-53248), %g1
	add	%i0, %i0, %i0
	add	%i1, %i0, %i1
	sll	%i1, 2, %i0
	add	%i0, %g1, %i0
	call	__ajit_load_word_mmu_bypass__, 0
	 mov	%i0, %o0
	or	%o0, 1, %i1
	call	__ajit_store_word_mmu_bypass__, 0
	 restore
	.size	enableInterruptController, .-enableInterruptController
	.align 4
	.global disableInterruptController
	.type	disableInterruptController, #function
	.proc	020
disableInterruptController:
	save	%sp, -96, %sp
	sethi	%hi(-53248), %g1
	add	%i0, %i0, %i0
	add	%i1, %i0, %i1
	sll	%i1, 2, %i0
	add	%i0, %g1, %i0
	call	__ajit_load_word_mmu_bypass__, 0
	 mov	%i0, %o0
	and	%o0, -2, %i1
	call	__ajit_store_word_mmu_bypass__, 0
	 restore
	.size	disableInterruptController, .-disableInterruptController
	.align 4
	.global enableInterrupt
	.type	enableInterrupt, #function
	.proc	020
enableInterrupt:
	save	%sp, -96, %sp
	sethi	%hi(-53248), %g1
	add	%i0, %i0, %i0
	add	%i1, %i0, %i1
	sll	%i1, 2, %i0
	add	%i0, %g1, %i0
	call	__ajit_load_word_mmu_bypass__, 0
	 mov	%i0, %o0
	mov	1, %g1
	sll	%g1, %i2, %i1
	or	%o0, %i1, %i1
	call	__ajit_store_word_mmu_bypass__, 0
	 restore
	.size	enableInterrupt, .-enableInterrupt
	.align 4
	.global disableInterrupt
	.type	disableInterrupt, #function
	.proc	020
disableInterrupt:
	save	%sp, -96, %sp
	sethi	%hi(-53248), %g1
	add	%i0, %i0, %i0
	add	%i1, %i0, %i1
	sll	%i1, 2, %i0
	add	%i0, %g1, %i0
	call	__ajit_load_word_mmu_bypass__, 0
	 mov	%i0, %o0
	mov	1, %g1
	sll	%g1, %i2, %i1
	andn	%o0, %i1, %i1
	call	__ajit_store_word_mmu_bypass__, 0
	 restore
	.size	disableInterrupt, .-disableInterrupt
	.ident	"GCC: (Buildroot 2014.08-g9d8f423-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
