.section .text.traphandlers

.align 8
!
! at entry, %o0 contains the pointer to the context data structure.
! Note:  getcontext can be executed in user mode!
!
.global __ajit_getcontext__
__ajit_getcontext__:

	! save 
	save %sp, -96, %sp

	! Register %i0 now holds the pointer to the 
	! context data structure.
	!


        ! store the globals..
	std %g0, [%i0 + 64]
	std %g2, [%i0 + 72]
	std %g4, [%i0 + 80]
	std %g6, [%i0 + 88]

	
	! save the y register and the fsr
	mov %y, %g1
	st %g1,  [%i0 + 32]
	st %fsr, [%i0 + 36]

	! store the locals and the ins
	std %l0, [%i0 + 96]
	std %l2, [%i0 + 104]
	std %l4, [%i0 + 112]
	std %l6, [%i0 + 120]

	std %i0, [%i0 + 128]
	std %i2, [%i0 + 136]
	std %i4, [%i0 + 144]
	std %i6, [%i0 + 152]
	

        ! valid stack.. if stack size != 0
	ld [%i0 + 16], %g1
	subcc %g1, %g0, %g1

	bz done_setting_stack_from_context
	nop

	! stack is from context..
	ld [%i0 + 12], %sp

done_setting_stack_from_context:


	! save FP? check if bit is set.	
        mov %psr, %g1
	srl %g1, 0xc, %g1
	andcc %g1, 0x1, %g1

	bz continue_after_saving_fp
	nop

        ! save floating point registers to stack, if FP is enabled
	std %f0,  [%i0 + 160]
	std %f2,  [%i0 + 168]
	std %f4,  [%i0 + 176]
	std %f6,  [%i0 + 184]
	std %f8,  [%i0 + 192]
	std %f10, [%i0 + 200]
	std %f12, [%i0 + 208]
	std %f14, [%i0 + 216]
	std %f16, [%i0 + 224]
	std %f18, [%i0 + 232]
	std %f20, [%i0 + 240]
	std %f22, [%i0 + 248]
	std %f24, [%i0 + 256]
	std %f26, [%i0 + 264]
	std %f28, [%i0 + 272]
	std %f30, [%i0 + 280]

continue_after_saving_fp:
	ld [%i0 + 68], %g1

	ret
	restore


!
! %o0 contains the address to the context data structure.
! %o7 contains the return pointer.
!
!  This function is passed a context data structure pointer
!  in register %o0.   The entire machine state is read from
!  this into the registers, and the thing runs...
!
! Note: setcontext can be executed only in supervisor mode.
!
.global __ajit_setcontext__
__ajit_setcontext__:
	save %sp, -96, %sp

	! i0 contains the context, i7 the return address.

	! Save the context pointer.
	mov %i0, %g2
	
	! save the return address for this call.
	mov %i7, %g3

	!
	! if the function to be called is NULL,
	! and if the link context is NULL, then
	! return -1.
	!

	!
	! Register %i0 holds the pointer to the 
	! context data structure, but it has been saved into 
	! g2.
	!

	!
	! get the y register and the fsr
	!
	ld [%g2+ 32], %g1
	mov %g1, %y
	ld [%g2 + 36], %fsr

	! get the locals and ins from the context.
	! includes the stack pointer!
	ldd [%g2 + 96],  %l0
	ldd [%g2 + 104], %l2
	ldd [%g2 + 112], %l4
	ldd [%g2 + 120], %l6

	ldd [%g2 + 128],  %i0
	ldd [%g2 + 136],  %i2
	ldd [%g2 + 144],  %i4
	ldd [%g2 + 152],  %i6

	!
	! update the return pointer
	!
	mov %g3, %i7

	! FP enabled?
	rd   %psr, %g1
	srl   %g1, 0xc, %g1
	andcc %g1, 0x1, %g1

	bz continue_after_loading_fp
	nop

        ! load floating point registers to stack, if FP is enabled
	ldd [%g2 + 160], %f0
	ldd [%g2 + 168], %f2
	ldd [%g2 + 176], %f4
	ldd [%g2 + 184], %f6
	ldd [%g2 + 192], %f8
	ldd [%g2 + 200], %f10
	ldd [%g2 + 208], %f12
	ldd [%g2 + 216], %f14
	ldd [%g2 + 224], %f16
	ldd [%g2 + 232], %f18
	ldd [%g2 + 240], %f20
	ldd [%g2 + 248], %f22
	ldd [%g2 + 256], %f24
	ldd [%g2 + 264], %f26
	ldd [%g2 + 272], %f28
	ldd [%g2 + 280], %f30

continue_after_loading_fp:
	
	! get back the globals.. except for g2 g3
	ld  [%g2 + 68], %g1
	ldd [%g2+ 80],  %g4
	ldd [%g2+ 88],  %g6 


all_regs_restored:

	! g1 holds the current return pointer.
	! g2 holds the context pointer.

	! save context pointer 
	mov %g2, %l4

	ld [%g2],     %o5        ! function to be called.
	ld [%g2 + 4], %o0        ! argument for function.

	! recover g1, g2, g3 which was used here...
	ld  [%g2+ 68], %g1
	ldd [%g2+ 72], %g2

	! will call func if function pointer
	! is not null.
	subcc %o5, 0, %o5

	! switch to link context...
	bz  switch_to_link_context
	nop


	!
	! call the link function...
	!
	call %o5
	nop


switch_to_link_context:

	ld [%l4 + 8], %o0   ! link context.

	subcc %o0, 0, %o0

	bz  skip_to_return
	nop


	!
	! return pointer stays in 
	! i7
        !
	call __ajit_setcontext__
	nop

skip_to_return:
	mov -1,  %i0

	ret
	restore
	nop	

! o0 contains old-context, o1 new-context.
! o7 as usual, contains the caller.
! called from window T
.global __ajit_swapcontext__
__ajit_swapcontext__:
	save %sp, -64, %sp

	!
	! get the context. %o0 contains
	! the source context pointer.
	!
	call __ajit_getcontext__
	nop

	! now move i1 to o0 and call
	! setcontext
	mov %i1, %o0
	call __ajit_setcontext__
	nop


return_from_swap_context:
	ret
	restore

	nop

	ta 0
	
