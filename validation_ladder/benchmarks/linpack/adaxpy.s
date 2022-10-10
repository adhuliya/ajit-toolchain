.global adaxpy
adaxpy:
.type adaxpy #function
_start:
        save %sp,-120,%sp
        
        !i0 has N - number of elements in dx and dy
        !i1 has multiplier for dx (da)
	!i2 has second part of double precision for da
        !i3 has initial address of dx
	!i4 has incx
        !i5 has initial address of dy
        !fp +92 has incy


	!check if n or da are zero
	cmp %i0,0
	ble exit
	mov %g0,%g1
	std %g0, [%fp + -24]
	ldd [%fp + -24], %f0 
	st %i1, [%fp + -24]
	st %i2, [%fp + -20]  !da at fp-24
	ldd [%fp + -24], %f4  !da in f4,f5
	fcmpd %f0,%f4
	fbe exit

	!check if incx and incy are equal to 1
	!we assume it is 1 and exit if not TODO:add code for unequal incremments
	mov 1,%g1
	cmp %i4,%g1
	bne exit
	ld [%fp + 92],%g2
	cmp %g2,%g1
	bne exit

	!do n%4
	andcc %i0,0x3,%g1 !g1 has m
	be label2
	sub %i0,%g1,%i0 	!i0 should now be a multiple of 4

	
	
label1:	ldd [%i3], %f0
        ldd [%i5], %f2
        fmuld %f4,%f0,%f0
        faddd %f2,%f0,%f2
	std %f8, [%i5]
	add %i3,8,%i3
	subcc %g1,1,%g1
	bne label1 
	add %i5,8,%i5

		
	! check if i0 is less than 4
	cmp %i0,4
	bl exit
	nop
	

	
label2:	ldd [%i3], %f0
	ldd [%i5], %f2
	fmuld %f4,%f0,%f0
	faddd %f2,%f0,%f2
	std %f2, [%i5]
        ldd [%i3 + 8], %f0
        ldd [%i5 + 8], %f2
        fmuld %f4,%f0,%f0
        faddd %f2,%f0,%f2
        std %f2, [%i5 +8]
        ldd [%i3 + 16], %f0
        ldd [%i5 + 16], %f2
        fmuld %f4,%f0,%f0
        faddd %f2,%f0,%f2
        std %f2, [%i5 +16]
        ldd [%i3 + 24], %f0
        ldd [%i5 + 24], %f2
        fmuld %f4,%f0,%f0
        faddd %f2,%f0,%f2
        std %f2, [%i5 +24]
	add %i3,32,%i3
	subcc %i0,4,%i0
	bne label2
	add %i5,32,%i5

exit:  restore
       retl
       nop

