!
! A utility which initializes all stack pointers to 0.
! 
.global clear_stack_pointers
clear_stack_pointers:
	mov %g0, %wim
	mov %g0, %sp
 	save
	mov %g0, %sp
 	save
	mov %g0, %sp
 	save
	mov %g0, %sp
 	save
	mov %g0, %sp
 	save
	mov %g0, %sp
 	save
	mov %g0, %sp
 	save
	mov %g0, %sp
	save

	retl
	nop
