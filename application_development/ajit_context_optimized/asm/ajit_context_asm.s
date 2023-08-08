.section .text.traphandlers

.align 8
!
! at entry, %o0 contains the pointer to the context data structure.
!           %o7 contains the caller pointer...
! Note:  getcontext can be executed in user mode!
!
.global __ajit_getcontext__
__ajit_getcontext__:

	!
	! Register %o0 now holds the pointer to the 
	! context data structure.
	!

        ! store the globals..
	std %g0, [%o0 + 64]
	std %g2, [%o0 + 72]
	std %g4, [%o0 + 80]
	std %g6, [%o0 + 88]

	! store the outs.


	! save the y register and the fsr
	mov %y, %g1
	st %g1,  [%o0 + 32]
	st %fsr, [%o0 + 36]

	! store the locals and the outs
	std %l0, [%o0 + 96]
	std %l2, [%o0 + 104]
	std %l4, [%o0 + 112]
	std %l6, [%o0 + 120]

	mov %o0, %g2
	mov %o7, %g3

	std %i0, [%o0 + 128]
	std %i2, [%o0 + 136]
	std %i4, [%o0 + 144]
	std %i6, [%o0 + 152]

	std %o2, [%o0 + 168]
	std %o4, [%o0 + 176]
	std %o6, [%o0 + 184]
	std %o0, [%o0 + 160]
	
	


	! save FP? check if bit is set.	
        mov %psr, %g1
	srl %g1, 0xc, %g1
	andcc %g1, 0x1, %g1

	bz continue_after_saving_fp
	nop

        ! save floating point registers to stack, if FP is enabled
	std %f0,  [%g2 + 192]
	std %f2,  [%g2 + 200]
	std %f4,  [%g2 + 208]
	std %f6,  [%g2 + 216]
	std %f8,  [%g2 + 224]
	std %f10, [%g2 + 232]
	std %f12, [%g2 + 240]
	std %f14, [%g2 + 248]
	std %f16, [%g2 + 256]
	std %f18, [%g2 + 264]
	std %f20, [%g2 + 272]
	std %f22, [%g2 + 280]
	std %f24, [%g2 + 288]
	std %f26, [%g2 + 296]
	std %f28, [%g2 + 304]
	std %f30, [%g2 + 312]

continue_after_saving_fp:

	! recover the remaining globals..
	ld  [%g2 + 68], %g1
	ldd [%g2 + 72], %g2

	! return 0
	! mov %g0, %o0

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
! Note: setcontext can be executed only in supervisor mode.
!
.global __ajit_setcontext__
__ajit_setcontext__:

	! uses g1, g2, g3 
	ba save_all_valid_windows_to_stack
	nop

done_saving_all_windows_to_stack:


	! o0 contains the context, o7 the return address.
	! Save the context pointer.
	mov %o0, %g2
	
	! save the return address for this call.
	mov %o7, %g3

	!
	! if the function to be called is NULL,
	! and if the link context is NULL, then
	! return -1.
	!

	!
	! Register %o0 holds the pointer to the 
	! context data structure, but it has been saved into 
	! g2.
	!

	!
	! get the y register and the fsr
	!
	ld [%g2+ 32], %g1
	mov %g1, %y
	ld [%g2 + 36], %fsr

	! get the locals and outs from the context.
	! includes the stack pointer!
	ldd [%g2 + 96],  %l0
	ldd [%g2 + 104], %l2
	ldd [%g2 + 112], %l4
	ldd [%g2 + 120], %l6

	ldd [%g2 + 128],  %i0
	ldd [%g2 + 136],  %i2
	ldd [%g2 + 144],  %i4
	ldd [%g2 + 152],  %i6

	ldd [%g2 + 160],  %o0
	ldd [%g2 + 168],  %o2
	ldd [%g2 + 176],  %o4
	ldd [%g2 + 184],  %o6

	! FP enabled?
	rd   %psr, %g1
	srl   %g1, 0xc, %g1
	andcc %g1, 0x1, %g1

	bz continue_after_loading_fp
	nop

        ! load floating point registers to stack, if FP is enabled
	ldd [%g2 + 192], %f0
	ldd [%g2 + 200], %f2
	ldd [%g2 + 208], %f4
	ldd [%g2 + 216], %f6
	ldd [%g2 + 224], %f8
	ldd [%g2 + 232], %f10
	ldd [%g2 + 240], %f12
	ldd [%g2 + 248], %f14
	ldd [%g2 + 256], %f16
	ldd [%g2 + 264], %f18
	ldd [%g2 + 272], %f20
	ldd [%g2 + 280], %f22
	ldd [%g2 + 288], %f24
	ldd [%g2 + 296], %f26
	ldd [%g2 + 304], %f28
	ldd [%g2 + 312], %f30

continue_after_loading_fp:
	
	! get back the globals.. except for g2 g3
	ld  [%g2 + 68], %g1
	ldd [%g2+ 80],  %g4
	ldd [%g2+ 88],  %g6 


all_regs_restored:

	! g3 holds the current return pointer.
	! g2 holds the context pointer.

	! save context pointer 
	mov %g2, %l4

	ld [%g2],     %l5        ! function to be called.
	ld [%g2 + 4], %o0        ! argument for function.

	! recover g1, g2, g3 which was used here...
	ld  [%g2+ 68], %g1
	ldd [%g2+ 72], %g2

	! will call func if function pointer
	! is not null.
	subcc %l5, 0, %l5

	! switch to link context...
	bz  switch_to_link_context
	nop


	!
	! call the link function...
	!
	call %l5
	nop


switch_to_link_context:

	ld [%l4 + 8], %o0   ! link context.

	subcc %o0, 0, %o0

	bz  skip_to_return
	nop


	!
	! set context to link...
        !
	call __ajit_setcontext__
	nop

skip_to_return:
	
	!
	! if you get here, it is an error.
 	!

	! recover the window...
	ldd [%l4 + 96],  %l0
	ldd [%l4 + 104], %l2
	ldd [%l4 + 120], %l6

	ldd [%l4 + 128],  %i0
	ldd [%l4 + 136],  %i2
	ldd [%l4 + 144],  %i4
	ldd [%l4 + 152],  %i6

	ldd [%l4 + 160],  %o0
	ldd [%l4 + 168],  %o2
	ldd [%l4 + 176],  %o4
	ldd [%l4 + 184],  %o6

	ldd [%l4 + 112], %l4

	mov -1,  %o0

	retl
	nop	

! o0 contains old-context, o1 new-context.
! o7 as usual, contains the caller.
! called from window T
.global __ajit_swapcontext__
__ajit_swapcontext__:

	! store return pointer into scratch of 
	! old-context
	st %o7, [%o0 + 20]

	call __ajit_getcontext__
	nop

	! get return pointer back 
	ld [%o0 + 20], %o7

	! modify the return pointer of
	! in o0.
	st %o7, [%o0 + 188]

	mov %o1, %o0
	call __ajit_setcontext__
	nop

	retl
	nop


.global save_all_windows_to_stack	
save_all_valid_windows_to_stack:

	mov %g0, %g3

save_window_loop:

	std %l0, [%sp + 0]
	std %l2, [%sp + 8]
	std %l4, [%sp + 16]
	std %l6, [%sp + 24]

	std %i0, [%sp + 32]
	std %i2, [%sp + 40]
	std %i4, [%sp + 48]
	std %i6, [%sp + 56]

	mov %psr, %g1
	mov %wim, %g2

	and %g1, 0x7, %g1
	add %g1, 0x1, %g1
	and %g1, 0x7, %g1

	srl  %g2, %g1, %g2
	andcc %g2, 0x1, %g2

	bnz done_saving_windows
	nop


	restore
	add %g3, 1, %g3

	ba save_window_loop
	nop

done_saving_windows:

	! if %g3 is 0, no need to save
	addcc %g3, %g0, %g3

get_back_to_curr_window_loop:
	
	bz done_restoring_to_current
	nop

	save

	subcc %g3, 0x1, %g3
	nop

	bnz get_back_to_curr_window_loop
	nop

done_restoring_to_current:
	ba done_saving_all_windows_to_stack
	nop

	

	



