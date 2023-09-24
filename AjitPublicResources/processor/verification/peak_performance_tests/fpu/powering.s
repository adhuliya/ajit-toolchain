
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
	set data_S,  %o2

	ldd [%o0], %f0
	ldd [%o1], %f2
	ldd [%o2], %f4

label1:


	fmuld %f0, %f4, %f0
	fcmpd %f0, %f2
	fbl label1
	nop

	ta 0	

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	.align 8
	ZERO: .double 0
	data_R0: .double 0d1.0
	data_R2: .double 0d1024.0
	data_S:  .double 0d2.0

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
