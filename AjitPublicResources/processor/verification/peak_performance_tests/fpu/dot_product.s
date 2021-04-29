
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
		

	! 8 iterations.
	mov 8, %g1

	set data_R0, %o0
	set data_R2, %o1
	set data_R4, %o2
	set data_R6, %o3

	set data_R8, %o4
	set data_R10, %o5
	set data_R12, %o6
	set data_R14, %o7
	
	set data_R16, %i0
	set data_R18, %i1
	set data_R20, %i2
	set data_R22, %i3

	set data_R24, %i4
	set data_R26, %i5
	set data_R28, %i6
	set data_R30, %i7

	set data_ACC, %l0

label1:

	ldd [%o0], %f0
	ldd [%o1], %f2
	ldd [%o2], %f4
	ldd [%o3], %f6

	ldd [%o4], %f8
	ldd [%o5], %f10
	ldd [%o6], %f12
	ldd [%o7], %f14
	
	ldd [%i0], %f16
	ldd [%i1], %f18
	ldd [%i2], %f20
	ldd [%i3], %f22

	ldd [%i4], %f24
	ldd [%i5], %f26
	ldd [%i6], %f28
	ldd [%i7], %f30



	fmuls %f0, %f1,   %f0	
	fmuls %f2, %f3,   %f1	
	fmuls %f4, %f5,   %f2	
	fmuls %f6, %f7,   %f3	
	fmuls %f8, %f9,   %f4	
	fmuls %f10, %f11, %f5	
	fmuls %f12, %f13, %f6	
	fmuls %f14, %f15, %f7	
	fmuls %f16, %f17, %f8	
	fmuls %f18, %f19, %f9	
	fmuls %f20, %f21, %f10	
	fmuls %f22, %f23, %f11	
	fmuls %f24, %f25, %f12	
	fmuls %f26, %f27, %f13	
	fmuls %f28, %f29, %f14	
	fmuls %f30, %f31, %f15	
	fadds %f0, %f1, %f0
	fadds %f2, %f3, %f1
	fadds %f4, %f5, %f2
	fadds %f6, %f7, %f3
	fadds %f8, %f9, %f4
	fadds %f10, %f11, %f5
	fadds %f12, %f13, %f6
	fadds %f14, %f15, %f7
	fadds %f0, %f1, %f0
	fadds %f2, %f3, %f1
	fadds %f4, %f5, %f2
	fadds %f6, %f7, %f3
	fadds %f0, %f1, %f0
	fadds %f2, %f3, %f1
	ld    [%l0], %f2
	fadds %f0, %f1, %f0
	fadds %f0, %f2, %f0
	st    %f0, [%l0]

	subcc %g1, 0x1, %g1	
	bnz label1
	nop

	ta 0	

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	.align 8
	ZERO: .double 0
	data_R0: .single 0r1.0
	data_R1: .single 0r1.0
	data_R2: .single 0r1.0
	data_R3: .single 0r1.0
	data_R4: .single 0r1.0
	data_R5: .single 0r1.0
	data_R6: .single 0r1.0
	data_R7: .single 0r1.0

	data_R8:  .single 0r1.0
	data_R9: .single 0r1.0
	data_R10: .single 0r1.0
	data_R11: .single 0r1.0
	data_R12: .single 0r1.0
	data_R13: .single 0r1.0
	data_R14: .single 0r1.0
	data_R15: .single 0r1.0
	
	data_R16:  .single 0r1.0
	data_R17: .single 0r1.0
	data_R18: .single 0r1.0
	data_R19: .single 0r1.0
	data_R20: .single 0r1.0
	data_R21: .single 0r1.0
	data_R22: .single 0r1.0
	data_R23: .single 0r1.0

	data_R24:  .single 0r1.0
	data_R25: .single 0r1.0
	data_R26: .single 0r1.0
	data_R27: .single 0r1.0
	data_R28: .single 0r1.0
	data_R29: .single 0r1.0
	data_R30: .single 0r1.0
	data_R31: .single 0r1.0

	data_ACC: .single 0r0.0				! 0x0

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
