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
	call copy_program_image_u64
	nop

	! jump to code.
	call 0x40000000
	nop

	ta 0

!
! This is a small subroutine which copies
! memory bytes from one region to another.
!
! g3 contains starting source address aligned on 
! double word boundary, g4 contains  number of bytes 
!  (must be > 0, and a multiple of 8) to be copied,
! g5 contains the starting destination addres,
! aligned on double word boundary
!
.global _copy_segment_u64;
_copy_segment_u64:
        ldd [%g3], %l4
	std %l4, [%g5]
	add  %g3,8, %g3
	add  %g5,8, %g5
        subcc %g4, 8, %g4
        bnz _copy_segment_u64
        nop
        retl 
        nop
	
