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

	!
	! save the window of the caller
	! of getcontext.  This is because
	! getcontext returns multiple times,
	! and the window registers need to
	! be preserved across these returns!
	!
	! looks like gcc has a hack for this
	! for the "true getcontext", but this
	! is not available to us.
	!
	std %l0, [%o0 + 64 ]
	std %l2, [%o0 + 72]
	std %l4, [%o0 + 80]
	std %l6, [%o0 + 88]

	std %i0, [%o0 + 96]
	std %i2, [%o0 + 104]
	std %i4, [%o0 + 112]
	std %i6, [%o0 + 120]

	save %sp, -96, %sp

	! stack pointer to be saved, default value
	mov %sp, %o2

	st %i7, [%i0]      ! return PC

	subcc %i1, 0x0, %i1
	bz set_sp_from_window
	nop

	! forced value of stack pointer.
	mov %i1, %o2

set_sp_from_window:
        st %o2, [%i0 + 4] ! stack-pointer.
	st %fp, [%i0 + 28] ! fp

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
	mov %o7, %g7

	call __ajit_context_save_all_windows_and_set_wim__
	nop

	mov %g7, %i7

leave_supervisor_region:

	! now in window W-1
	!  Window W-1 will keep stack of the
	!  context.
	!  get the stack pointer, but keep
	!  it in o0
	ld [%i0 + 4], %o0



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
	ldd [%o0],      %l0
	ldd [%o0 + 8],  %l2
	ldd [%o0 + 16], %l4
	ldd [%o0 + 24], %l6

	! get back all input regs except for i0
	! note that the saved i0 should be the same 
	! as the context pointer..
        ld  [%o0 + 36],  %i1
	ldd [%o0 + 40],  %i2
	ldd [%o0 + 48],  %i4
	ldd [%o0 + 56],  %i6

	! get back the frame pointer.
	ld [%i0 + 28], %fp

	! now update the stack pointer.
	! (after the current window has its registers)
	mov %o0, %sp

	! read func
	ld [%i0 + 16], %o0
	subcc %o0, %g0, %o0

	bz  __to_link_context__
	nop

	! in window W-1.. correct stack !
	! restore
	! save
	! in new stack area.


	ld [%i0 + 16], %o2
	ld [%i0 + 20], %o0

	call %o2
	nop
	

__to_link_context__:

	! link context?
	ld [%i0 + 24], %o2
	subcc %o2, 0x0, %o2
	
	bz __return_from_setcontext__
	nop

	! set context to link_context.
	call __ajit_setcontext__
	mov %o2, %o0

__return_from_setcontext__:
	! in window W-1

	! return pc..
	ld [%i0], %i7
	add %i7, 8, %i7

	restore

	! the window registers in
	! the caller (of getcontext)
	! may have been modified.
	! recover them from the
	! stored values in context 
	ldd [%o0 + 64 ], %l0
	ldd [%o0 + 72],  %l2
	ldd [%o0 + 80],  %l4
	ldd [%o0 + 88],  %l6

	ldd [%o0 + 96],  %i0
	ldd [%o0 + 104], %i2
	ldd [%o0 + 112], %i4
	ldd [%o0 + 120], %i6

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

	mov %wim, %g2

	mov 0x0, %wim
	mov 0x8, %g3

save_one_window:

	! if stack pointer is 0, skip save.
	subcc %sp, 0, %g0

	bz skip_this_window
	nop

	! check if window is valid
	! and needs to be saved.
	mov %psr, %g1
	and %g1, 7, %g1

	! valid window?
	srl %g2, %g1, %g4
	orcc %g4, 0, %g4

	! if window is marked invalid, skip save.
	bnz skip_this_window
	nop


	std %l0, [%sp]
	std %l2, [%sp+8]
	std %l4, [%sp+16]
	std %l6, [%sp+24]

	std %i0, [%sp+32]
	std %i2, [%sp+40]
	std %i4, [%sp+48]
	std %i6, [%sp+56]

	mov %g0, %sp

skip_this_window:

	! for g3 in 8,7,6,...,2
	! jump to save_one_window..
	! for g3 = 1, an additional 
	! save.
	subcc %g3, 0x1, %g3

	! loop back 7 times.
	bnz save_one_window
	! there will be 8 saves.
	save


	! back in the window where
	! you started.

done_saving_windows:

	mov %g0, %sp

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

! enter  this routine in window W
.global __ajit_context_save_all_windows_and_set_wim__
__ajit_context_save_all_windows_and_set_wim__:
	mov %o7, %g6

	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	! before setting the context, save            !
	! all the active register windows.            !
	!					      !
	! This needs supervisor permissions!          !
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	call __ajit_context_save_all_windows__
	nop

	save

	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!   Set window W as invalid		      !
	! This needs supervisor permissions!          !
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	call set_wim_to_previous_window
	nop

	mov %g7, %i7
	jmpl %g6 + 8, %g0
	nop

	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	! end supervisor permission region..          !
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
