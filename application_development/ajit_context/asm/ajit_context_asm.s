.section .text.traphandlers
.align 8
! at entry, %o0 contains the pointer to the context data structure.
.global __ajit_getcontext__
__ajit_getcontext__:
	!
	! This function was called from window T, move to window T-1.
        !	
	save %sp, -256, %sp

	!
	! Register %i0 is assumed to hold the pointer to the 
	! thread data structure.
	!
	rd %psr, %l6
	st %l6, [%i0]

	rd %wim, %l6
	st %l6, [%i0+4]

	rd %tbr, %l6
	st %l6, [%i0+8]
	
	rd %y,  %l6
	st %l6, [%i0+12]

	st %fsr, [%i0 + 16]

        ! store the globals..
	std %g0, [%i0 + 32]
	std %g2, [%i0 + 40]
	std %g4, [%i0 + 48]
	std %g6, [%i0 + 56]


	! use globals for temp work from now on.
	mov %i0, %g7
	add %i0, 64, %g1

	! set window to 0.
	rd %psr, %g3
        set 0xffffffe0, %g2
	and %g3, %g2, %g2
	mov %g2, %psr

	! clear the wim
	mov %g0, %wim

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

	! store FP regs into R state.
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

	! get back the psr
	ld [%g7], %g2
	mov %g2, %psr
	
	! get back the wim
	ld [%g7 + 4], %g2
	mov %g2, %wim

	! get the globals back.
	ldd [%g7 + 32], %g0
	ldd [%g7 + 40], %g2
	ldd [%g7 + 48], %g4
	ldd [%g7 + 56], %g6

	! Thats it...
	ret
	restore
	nop

.global __ajit_setcontext__
__ajit_setcontext__:
	!
	! This function was called from window T, move to window T-1.
        !	
	save %sp, -256, %sp

	! i0 could get clobbered..
	! we keep it in g1, and g7
	mov %i0, %g1
	mov %i0, %g7

	!
	! Register %i0 is assumed to hold the pointer to the 
	! thread data structure.
	!
	! get the psr and other status registers
	!
	ld [%g1], %g2
	mov %g2, %psr
	ld [%g1+4], %g2
	mov %g2, %wim
	ld [%g1+8], %g2
	mov %g2, %tbr
	ld [%g1+12], %g2
	mov %g2, %y
	ld [%g1+16], %fsr

	! use globals for temp work from now on.
	add %g1, 64, %g1

	! get the window registers.
	mov %psr, %g2
        set 0xffffffe0, %g3
	and %g2, %g3, %g3
	mov %g3, %psr

	! clear the wim
	mov %g0, %wim

	mov 8, %g4
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
	subcc %g4, 1, %g4
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
	ld [%g7], %g2
	mov %g2, %psr
	
	! get back the wim
	ld [%g7 + 4], %g2
	mov %g2, %wim

	! now get back the globals..
	ldd [%g7], %g0
	ldd [%g7+8], %g2
	ldd [%g7+16], %g4
	ldd [%g7+24], %g6

	ret
	restore
	nop	

! o0 contains context pointer
! o1 contains the function which needs
!    to be called.
! o2 contains the argument...
!
! Start in window T
.global __ajit_makecontext__
__ajit_makecontext__:
	!
        ! Need to save the return pointer somewhere.
	!
	st %o7, [%o0 + 24]

	! ajit_getcontext will save window T-1
        call __ajit_getcontext__
	nop

	! get back the return pointer
	ld [%o0 + 24], %o7

	! back in window T

	!
	! now we need to update register
	! i7 from window T-1 in the context data structure.
	! (ie o7 from window T)
	!

	!
	! o0 contains the context pointer, in window T
	! o7 contains the return pointer,  in window T
	!
patch_return_location:
	save

	! now in T-1
	! i0 contains the context pointer.
	! i7 contains the return pointer.

	! calculate the offset for window
	! T in the context data structure.
	!
	mov %psr, %l3
	and 0x7, %l3, %l3
	add %l3, 0x1, %l3
	and 0x7, %l3, %l3

	! l3 contains the window pointer T

	! offset for register window T in
	! context data structure.
	umul %l3, 64, %l3
	add  %l3, 64, %l3
	add  %l3, %i0, %l3

	! update o7 in window T in
	! context data structure.
	st %i7, [%l3 + 28]
	restore

	! back in T, with patched 
	! return location.
	subcc %o1, 0x0, %o1
	bz return_from_makecontext
	nop

	!
	! From window T, call the target.
	!
	mov %o2, %o0
	call %o1 
	nop

return_from_makecontext:
        ! return from window T
	ret
	nop
	
