
.global main
main:
_start:
	set 0x100, %o0
	sta %o0, [%g0] 0x4      ! set the default cacheable bit in the mmu to 1. mmu stays disabled.

	!!! clear all FPU registers
	set ZERO, %l0; ldd [%l0], %f0

	! Initialize PSR, enable traps.
	! set PSR with ET=1 PS=1 S=1 and EF=1 all other fields=0
	set 0x10e0, %l0
	wr %l0, %psr

	!store base of trap table in TBR register
	set	trap_table_base, %l0
	wr	%l0, 0x0, %tbr
		

	set data_R0, %o0
	ldd [%o0], %f0
	set data_R2, %o1
	ldd [%o1], %f2
	set data_R4, %o2
	ldd [%o2], %f4
	set data_R6, %o3
	ldd [%o3], %f6

	set data_R8, %o4
	ldd [%o4], %f8
	set data_R10, %o5
	ldd [%o5], %f10
	set data_R12, %o6
	ldd [%o6], %f12
	set data_R14, %o7
	ldd [%o7], %f14
	
	set data_R16, %i0
	ldd [%i0], %f16
	set data_R18, %i1
	ldd [%i1], %f18
	set data_R20, %i2
	ldd [%i2], %f20
	set data_R22, %i3
	ldd [%i3], %f22

	set data_R24, %i4
	ldd [%i4], %f24
	set data_R26, %i5
	ldd [%i5], %f26
	set data_R28, %i6
	ldd [%i6], %f28
	set data_R30, %i7
	ldd [%i7], %f30

	! 8 iterations.
	mov 8, %g1

label1:
	fadds %f0, %f1, %f0	
	fmuls %f1, %f2, %f1	
	fadds %f2, %f3, %f2	
	fmuls %f3, %f4, %f3
	fadds %f4, %f5, %f4
	fmuls %f5, %f6, %f5	
	fadds %f6, %f7, %f6	
	fmuls %f7, %f8, %f7
	fadds %f8, %f9, %f8
	fmuls %f9, %f10, %f9	
	fadds %f10, %f11, %f10	
	fmuls %f11, %f12, %f11
	fadds %f12, %f13, %f12
	fmuls %f13, %f14, %f13	
	fadds %f14, %f15, %f14	
	fmuls %f15, %f16, %f15
	fadds %f16, %f17, %f16	
	fmuls %f17, %f18, %f17	
	fadds %f18, %f19, %f18	
	fmuls %f19, %f20, %f19
	fadds %f20, %f21, %f20
	fmuls %f21, %f22, %f21	
	fadds %f22, %f23, %f22	
	fmuls %f23, %f24, %f23
	fadds %f24, %f25, %f24
	fmuls %f25, %f26, %f25	
	fadds %f26, %f27, %f26	
	fmuls %f27, %f28, %f27
	fadds %f28, %f29, %f28
	fmuls %f29, %f30, %f29	
	fadds %f30, %f31, %f30	
	fmuls %f31, %f31, %f31

	subcc %g1, 0x1, %g1	
	bnz label1
	nop

	ta 0	

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	.align 8
	ZERO: .double 0
	data_R0: .single 0r4.2				! 0x40866666
	data_R1: .single 0r5.2				! 0x40a66666
	data_R2: .single 0r6.2				! 0x40c66666
	data_R3: .single 0r7.2				! 0x40e66666
	data_R4: .single 0r8.2				! 0x41033333
	data_R5: .single 0r9.2				! 0x41133333
	data_R6: .single 0r10.2				! 0x41233333
	data_R7: .single 0r11.2				! 0x41333333

	data_R8:  .single 0r12.2			! 0x41433333
	data_R9: .single 0r13.2				! 0x41533333
	data_R10: .single 0r14.2			! 0x41633333
	data_R11: .single 0r15.2			! 0x41733333
	data_R12: .single 0r16.2			! 0x4181999a
	data_R13: .single 0r17.2			! 0x4189999a
	data_R14: .single 0r18.2			! 0x4191999a
	data_R15: .single 0r19.2			! 0x4199999a
	
	data_R16:  .single 0r12.2			! 0x41433333
	data_R17: .single 0r13.2			! 0x41533333
	data_R18: .single 0r14.2			! 0x41633333
	data_R19: .single 0r15.2			! 0x41733333
	data_R20: .single 0r16.2			! 0x4181999a
	data_R21: .single 0r17.2			! 0x4189999a
	data_R22: .single 0r18.2			! 0x4191999a
	data_R23: .single 0r19.2			! 0x4199999a

	data_R24:  .single 0r12.2			! 0x41433333
	data_R25: .single 0r13.2			! 0x41533333
	data_R26: .single 0r14.2			! 0x41633333
	data_R27: .single 0r15.2			! 0x41733333
	data_R28: .single 0r16.2			! 0x4181999a
	data_R29: .single 0r17.2			! 0x4189999a
	data_R30: .single 0r18.2			! 0x4191999a
	data_R31: .single 0r19.2			! 0x4199999a

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	!====================================
	! TRAP TABLE
	!====================================
	!NOTE: the trap table has to be aligned on 2^12 = 4096 bytes
	!because wr tbr instruction copies bits 
	!31:12 of the result only into tbr register
	
	.align 4096

trap_table_base:
	! The trap handler for each trap does the following:
	!	- store the trap number in g1
	!	- do a restore operation so that we  
	!	  go back to the original window 
	!	- ta 0 (cause a trap in trap to go into ERROR mode)

hardware_trap_table_base:

HW_trap_0x00: mov 0x00, %g1; restore; ta 0; nop
HW_trap_0x01: mov 0x01, %g1; restore; ta 0; nop
HW_trap_0x02: mov 0x02, %g1; restore; ta 0; nop
HW_trap_0x03: mov 0x03, %g1; restore; ta 0; nop
HW_trap_0x04: mov 0x04, %g1; restore; ta 0; nop
HW_trap_0x05: mov 0x05, %g1; restore; ta 0; nop
HW_trap_0x06: mov 0x06, %g1; restore; ta 0; nop
HW_trap_0x07: mov 0x07, %g1; restore; ta 0; nop
HW_trap_0x08: inc %g2; ta 0; nop; nop      !FP exception

software_trap_table_base:
SW_trap_0x80: mov 0x80, %g1; restore; ta 0; nop
SW_trap_0x81: mov 0x81, %g1; restore; ta 0; nop
