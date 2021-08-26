.global dotP
dotP:
	save

	set 0x50000, %l3
	set 0x51000, %l4
	set 0x52000, %l6	


	ldd  [%l3], %f0
	ldd  [%l4], %f2
	ldd  [%l3 + 8], %f4
	ldd  [%l4 + 8], %f6
	ldd  [%l3 + 16], %f8
	ldd  [%l4 + 16], %f10
	ldd  [%l3 + 24], %f12
	ldd  [%l4 + 24], %f14
	ldd  [%l3 + 32], %f16
	ldd  [%l4 + 32], %f18
	ldd  [%l3 + 40], %f20
	ldd  [%l4 + 40], %f22
	ldd  [%l3 + 48], %f24
	ldd  [%l4 + 48], %f26
	ldd  [%l3 + 56], %f28
	ldd  [%l4 + 56], %f30

	! vector multiply.
	vfmul32 %f0, %f2, %f0
	vfmul32 %f4, %f6, %f4
	vfmul32 %f8, %f10, %f8
	vfmul32 %f12, %f14, %f12
	vfmul32 %f16, %f18, %f16
	vfmul32 %f20, %f22, %f20
	vfmul32 %f24, %f26, %f24
	vfmul32 %f28, %f30, %f28

	! reduce
	vfadd32 %f0, %f4,   %f0
	vfadd32 %f8, %f12,  %f2
	vfadd32 %f16, %f20, %f4
	vfadd32 %f24, %f28, %f6


	vfadd32 %f0, %f2, %f8
	vfadd32 %f4, %f6, %f10

	vfadd32 %f8, %f10, %f0

	fadds %f0, %f1, %f2

	st %f2, [%l6]

	restore 
	retl
	nop



	
	
