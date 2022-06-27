.section .text.ajitstart
.global _start;
_start:
	set -256, %sp
	clr %fp

	set 0x1, %l0		! window 0 is marked invalid...  we start at window 7
	wr %l0, 0x0, %wim	!

	! enable traps.
	set 0x10E7, %l0	
	wr %l0, %psr

	! copy to sram..
	call copy_program_image
	nop

	! jump to code.
	ba jump_to_code
	nop

	ta 0

!
! This is a small subroutine which copies
! memory bytes from one region to another.
!
! g3 contains starting source address, g4 contains
! number of bytes (must be > 0) to be copied,
! g5 contains the starting destination addres.
!
.global _copy_segment;
_copy_segment:
        ldub [%g3], %l3
	stub %l3, [%g5]
	add  %g3,1, %g3
	add  %g5,1, %g5
        subcc %g4, 1, %g4
        bnz _copy_segment
        nop
        retl 
        nop
	
