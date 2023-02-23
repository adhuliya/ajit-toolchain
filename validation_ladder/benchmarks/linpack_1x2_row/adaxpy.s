.global adaxpy
adaxpy:
.type adaxpy #function
_start:
        save %sp,-196,%sp
        
        !i0 has N - number of elements in dx and dy
        !i1 has multiplier for dx (da)
	!i2 has second part of double precision for da
        !i3 has initial address of dx
	!i4 has dy


	!check if n or da are zero
	cmp %i0,0
	ble exit
	mov %g0,%g1
	std %g0, [%fp + -24]
	ldd [%fp + -24], %f8
	st %i1, [%fp + -24]
	st %i2, [%fp + -20]  !da at fp-24
	ldd [%fp + -24], %f12  !da in f4,f5
	fcmpd %f8,%f12
	fbe exit 
	nop




th_chk: rd %asr29, %l1
	set 0x50520000, %l2
	cmp %l1,%l2
	bz th0
	andcc %i0,0x3,%g1          !!%g1 has m

th1add: sub %i0,%g1,%i0         !i0 should now be a multiple of 4
	add %g1,1,%g1
	sll %g1,3,%g2                !!!start adress of tth1 = 8*g1, using shift operator
	add %g2,%i3,%i3
	ba check		     !!!exit if less than 
	add %g2,%i5,%i5
	
        !do n%4
th0:   	be check        	! andcc %i0,0x3,%g1
	sub %i0,%g1,%i0         !i0 should now be a multiple of 4
                                !check if less than 4 - exit for th1
      

	
label1:	ldd [%i3], %f8
        ldd [%i5], %f10
	add %i3,8,%i3
        fmuld %f12,%f8,%f8
        faddd %f10,%f8,%f10
	subcc %g1,1,%g1
	std %f10, [%i5]
	bne label1 
	add %i5,8,%i5

	! check if i0 is less than 4
check:	cmp %i0,4
	bl exit
	nop
	
label2:	ldd [%i3], %f8
	ldd [%i5], %f10
	ldd [%i3 + 16], %f14
        ldd [%i5 + 16], %f16
	fmuld %f12,%f8,%f8
        fmuld %f12,%f14,%f14
	add %i3,32,%i3
!	ldd [%i3 + 16], %f18
	faddd %f10,%f8,%f10
        faddd %f16,%f14,%f16
!	ldd [%i5 + 16], %f20
	subcc %i0,4,%i0
	std %f10, [%i5]
	std %f16, [%i5 +16]
!        ldd [%i3 + 24], %f24
!        ldd [%i5 + 24], %f26
!	fmuld %f12,%f18,%f18
!        fmuld %f12,%f24,%f24
!	add %i3,32,%i3
!	faddd %f20,%f18,%f20
!        faddd %f26,%f24,%f26
!	subcc %i0,4,%i0
!	std %f20, [%i5 +16]
!       std %f26, [%i5 +24]
	bnz label2
	add %i5,32,%i5
	
exit:  
       restore
       retl
       nop

