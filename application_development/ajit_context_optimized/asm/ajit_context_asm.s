.section .text.traphandlers

.align 8
!
! at entry, %o0 contains the pointer to the context data structure.
!           %o1 contains the stack pointer to be used..
!                  (if null, the stack pointer is sampled)
!           %o7 contains the caller pointer...
! Note:  getcontext can be executed in user mode!
!
.global __ajit_getcontext__
__ajit_getcontext__:

	save %sp, -96, %sp

	! stack pointer to be saved, default value
	mov %sp, %o2

	st %i7, [%i0]     ! return PC

	subcc %i1, 0x0, %i1
	bz set_sp_from_window
	nop

	! forced value of stack pointer.
	mov %i1, %o2

set_sp_from_window:
        st %o2, [%i0 + 4] ! stack-pointer.

	! save the globals into the
	! context
	std %g0, [%i0 + 32]
	std %g2, [%i0 + 40]
	std %g4, [%i0 + 48]
	std %g6, [%i0 + 56]

	! stores ins and  locals to stack
	! now use globals until the end
	std %l0, [%o2]
	std %l2, [%o2 + 8]
	std %l4, [%o2 + 16]
	std %l6, [%o2 + 24]

	std %i0, [%o2 + 32]
	std %i2, [%o2 + 40]
	std %i4, [%o2 + 48]
	std %i6, [%o2 + 56]
	
	! save the y register and the fsr
	mov %y, %g1
	st %g1,  [%i0 + 8]  ! y
	st %fsr, [%i0 + 12] ! fsr

	! recover the globals..
	ldd  [%i0 + 32], %g0
	ldd  [%i0 + 40], %g2

	ret
	restore 
	nop


!
! %o0 contains the address to the context data structure.
! %o7 contains the return pointer.
!
!  This function is passed a context data structure pointer
!  in register %o0.   The entire machine state is read from
!  this into the registers, and the thing runs...
!
!
.global __ajit_setcontext__
__ajit_setcontext__:
	! Entered in window W

	!
	! before setting the context, save
	! all the active register windows.
	!
	call __ajit_context_save_all_windows__
	nop

	save
	! now in window W-1

	!  Window W-1 will keep stack of the
	!  context.
	!  get the stack pointer
	ld [%i0 + 4], %sp

	! clobbers o7, ok.
	call set_wim_to_previous_window
	nop



move_on:
	! recover the window from the context.

	!
	! get the y register and the fsr
	!
	ld [%i0+ 8], %g1
	mov %g1, %y
	ld [%i0 + 12], %fsr


	! get the globals back from the context.
	ldd [%i0 + 32], %g0
	ldd [%i0 + 40], %g2
	ldd [%i0 + 48], %g4
	ldd [%i0 + 56], %g6
	

	! get the locals and ins from the stack..
	ldd [%sp],      %l0
	ldd [%sp + 8],  %l2
	ldd [%sp + 16], %l4
	ldd [%sp + 24], %l6

	! get back all input regs including i0
	! note that i0 will be the same as when
	! getcontext was called..
        ld  [%sp + 36],  %i1
	ldd [%sp + 40],  %i2
	ldd [%sp + 48],  %i4
	ldd [%sp + 56],  %i6

	! read func
	ld [%i0 + 16], %o0
	subcc %o0, %g0, %o0

	bz  __return_from_setcontext__
	nop

	! in window W-1.. correct stack !
	restore

	save
	! in new stack area.


	ld [%i0 + 16], %o2
	ld [%i0 + 20], %o0

	call %o2
	nop
	

	! should never return.
	!ta 0


__return_from_setcontext__:
	! in window W-1

	! return pc..
	ld [%i0], %i7
	add %i7, 8, %i7
	
	restore
	jmpl %o7, %g0

	nop

! o0 = source context
! o1 = source stack
! o2 = destination context
.global __ajit_swapcontext__
__ajit_swapcontext__:

	mov %o7, %o5

	! o0, o1 is used here.. but o7
	! is clobbered.
	call __ajit_getcontext__ 
	nop

	st %o5, [%o0]


	mov %o2, %o0
	call __ajit_setcontext__
	nop

	ta 0

	
!
! g1 contains the PSR
!
.global __ajit_context_save_all_windows__
__ajit_context_save_all_windows__:
        ! g1 will hold the current window.
	mov %psr, %g1
	and %g1, 7, %g1

	mov %wim, %g2
	mov 0x0, %wim
	mov 0x8, %g3

save_one_window:
	subcc %sp, 0, %g0

	bz skip_this_window
	nop

	std %l0, [%sp]
	std %l2, [%sp+8]
	std %l4, [%sp+16]
	std %l6, [%sp+24]

	std %i0, [%sp+32]
	std %i2, [%sp+40]
	std %i4, [%sp+48]
	std %i6, [%sp+56]

skip_this_window:

	subcc %g3, 0x1, %g3

	bnz save_one_window
	save

done_saving_windows:

	retl 
	nop


	



!
! uses g1, g2, g3.
!
.global set_wim_to_previous_window
set_wim_to_previous_window:
	!
	! now the wim.. mark
	! current window + 1 as 
	! invalid.
	!
	mov %psr, %g1
	and %g1, 0x7, %g1

	add %g1, 0x1, %g1
	and %g1, 0x7, %g1

	mov 0x1, %g2
	sll %g2, %g1, %g2

	mov %g2, %wim

	retl
	nop

