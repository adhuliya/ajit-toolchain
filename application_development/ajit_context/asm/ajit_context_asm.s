.section .text.traphandlers

.align 8
! at entry, %o0 contains the pointer to the context data structure.
.global __ajit_getcontext__
__ajit_getcontext__:
	! Register %o0 is assumed to hold the pointer to the 
	! context data structure.
	!

        ! store the globals..
	std %g0, [%o0 + 64]
	std %g2, [%o0 + 72]
	std %g4, [%o0 + 80]
	std %g6, [%o0 + 88]

	rd %psr, %g7
	st %g7, [%o0 + 32]

	rd %wim, %g7
	st %g7, [%o0+ 36]

	rd %tbr, %g7
	st %g7, [%o0 + 40]
	
	rd %y,  %g7
	st %g7, [%o0+ 44]

	st %fsr, [%o0 + 48]



	! use globals for temp work from now on.
	mov %o0, %g7
	add %o0, 96, %g1


	! set window to 0.
	rd %psr, %g3
        set 0xffffffe0, %g2
	and %g3, %g2, %g2
	mov %g2, %psr

	! clear the wim
	mov %g0, %wim

	! Save all windows into the context data structure.
	mov 8, %g4
save_window:
	std %o0, [%g1]
	std %o2, [%g1 + 8]
	std %o4, [%g1 + 16]
	std %o6, [%g1 + 24]
	std %l0, [%g1 + 32]
	std %l2, [%g1 + 40]
	std %l4, [%g1 + 48]
	std %l6, [%g1 + 56]
	add %g1, 64, %g1
	restore 
	subcc %g4, 0x1, %g4
	bnz save_window
	nop

	! store FP regs into the context data structure.
save_fp:
	std %f0, [%g1]
	std %f2, [%g1 + 8]
	std %f4, [%g1 + 16]
	std %f6, [%g1 + 24]
	std %f8, [%g1 + 32]
	std %f10, [%g1 + 40]
	std %f12, [%g1 + 48]
	std %f14, [%g1 + 56]
	std %f16, [%g1 + 64]
	std %f18, [%g1 + 72]
	std %f20, [%g1 + 80]
	std %f22, [%g1 + 88]
	std %f24, [%g1 + 96]
	std %f26, [%g1 + 104]
	std %f28, [%g1 + 112]
	std %f30, [%g1 + 120]

	! get back the psr.. points to window T
	ld [%g7 + 32], %g2
	mov %g2, %psr
	
	! get back the wim
	ld [%g7 + 36], %g2
	mov %g2, %wim

	! get the globals back.
	ldd [%g7 + 64], %g0
	ldd [%g7 + 72], %g2
	ldd [%g7 + 80], %g4
	ldd [%g7 + 88], %g6


	! Thats it...
	retl
	nop


!
! %o0 contains the address to the context data structure.
! %o7 contains the return pointer.
!
!  This function is passed a context data structure pointer
!  in register %o0.   The entire machine state is read from
!  this into the registers, and the thing runs...
!
.global __ajit_setcontext__
__ajit_setcontext__:

	! Use globals...
	mov %o0, %g1
	mov %o0, %g7

	!
	! if the function to be called is NULL,
	! and if the link context is NULL, then
	! return -1.
	!

	!
	! Register %o0 holds the pointer to the 
	! context data structure, but it has been saved into 
	! g1 and g7.
	!

	!
	! get the psr and other status registers
	!
	ld [%g1 + 32], %g2
	mov %g2, %psr  ! this will change o0 but we are using globals.
	ld [%g1+ 36], %g2
	mov %g2, %wim
	ld [%g1+ 40], %g2
	mov %g2, %tbr
	ld [%g1+ 44], %g2
	mov %g2, %y
	ld [%g1+ 48], %fsr

	! use globals for temp work from now on.
	add %g1, 96, %g1

	! get the window registers.
        ! set the window pointer in the
	! psr to 0.
	mov  %psr, %g2
        andn %g2, 0x7, %g2
	mov  %g2, %psr

	! clear the wim
	mov %g0, %wim

	mov 8, %g2

restore_window:
	ldd [%g1], %o0
	ldd [%g1 + 8], %o2
	ldd [%g1 + 16], %o4
	ldd [%g1 + 24], %o6
	ldd [%g1 + 32], %l0
	ldd [%g1 + 40], %l2
	ldd [%g1 + 48], %l4
	ldd [%g1 + 56], %l6
	add %g1, 64, %g1
	restore 
	subcc %g2, 1, %g2
	bnz restore_window
	nop

restore_fp:
	ldd [%g1],       %f0
	ldd [%g1 + 8],   %f2
	ldd [%g1 + 16],  %f4
	ldd [%g1 + 24],  %f6
	ldd [%g1 + 32],  %f8
	ldd [%g1 + 40],  %f10
	ldd [%g1 + 48],  %f12
	ldd [%g1 + 56],  %f14
	ldd [%g1 + 64],  %f16
	ldd [%g1 + 72],  %f18
	ldd [%g1 + 80],  %f20
	ldd [%g1 + 88],  %f22
	ldd [%g1 + 96],  %f24
	ldd [%g1 + 104], %f26
	ldd [%g1 + 112], %f28
	ldd [%g1 + 120], %f30


	! get back the psr
	ld [%g7 + 32], %g2
	mov %g2, %psr
	
	! get back the wim
	ld [%g7 + 36], %g2
	mov %g2, %wim


	! store g7 in l3..
	mov %g7, %l4

	! get back the globals..
	ldd [%g7+ 64], %g0
	ldd [%g7+ 72], %g2
	ldd [%g7+ 80], %g4
	ldd [%g7+ 88], %g6 

all_regs_restored:

	! l4 is the context pointer
	ld [%l4], %l5        ! function to be called.
	ld [%l4 + 4], %o0    ! argument for function.
	

	! will call func if function pointer
	! is not null.
	subcc %l5, 0, %l5

	! switch to link context...
	bz,a  switch_to_link_context
	nop


	!
	! call the link function...
	!
	call %l5
	nop




switch_to_link_context:

	ld [%l4 + 8], %o0   ! link context.

	! link context is in l6
	subcc %o0, 0, %o0

	bz  skip_to_return
	nop


	! setcontext to o0
	call __ajit_setcontext__
	nop


skip_to_return:
	mov -1,  %o0
	retl
	nop	

! o0 contains old-context, o1 new-context.
! o7 as usual, contains the caller.
! called from window T
.global __ajit_swapcontext__
__ajit_swapcontext__:
	mov %o1, %o2
	mov %o7, %o3

	!
	! get the context. %i0 contains
	! the source context pointer.
	!
	call __ajit_getcontext__
	nop

	!
	! setcontext should return to this
	! place..
	!
	mov %o3, %o1
	call __ajit_set_context_return_pointer__
	nop

	! now move original o1 to o0 and call
	! setcontext
	mov %o2, %o0
	call __ajit_setcontext__
	nop


return_from_swap_context:
	retl
	nop

	ta 0
	
	


