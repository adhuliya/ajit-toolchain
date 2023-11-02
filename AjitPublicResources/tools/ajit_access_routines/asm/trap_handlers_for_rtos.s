/* reference 					*/
/* http://ieng9.ucsd.edu/~cs30x/sparcstack.html */

!
! A save instruction caused a window-overflow-trap.
! Window-id      1   2   3
! Symbol         N   T   W
! From Window W we wanted to move to window T.  T
! was invalid... Trap!  Trap-handler puts us in  window T.
! 
! We will save window N, N becomes the new trap window
! and T becomes available to reexecute the save.
!  
.section .text.traphandlers
window_overflow_trap_handler:


	! when we enter the trap handler, we are in window T
	! Note that T may not have a stack...

        /* rotate WIM one bit right, we have 8 windows */
        mov %wim,%l3
        sll %l3,7,%l4
        srl %l3,1,%l3
        or  %l3,%l4,%l3
        and %l3,0xff,%l3

        /* disable WIM traps */
        mov %g0,%wim
        nop; nop; nop

	/*
        /* move to window N (this will not trap, since wim=0), .. */
	/* Note: o6 in this window will provide a stack pointer   */
	/*  which we assume to be valid                           */
	/*   (note: in linux kernel, validity of sp is also checked) */
        save

        /* dump registers to stack (note: use sp in N) */
        std %l0, [%sp +  0]
        std %l2, [%sp +  8]
        std %l4, [%sp + 16]
        std %l6, [%sp + 24]
        std %i0, [%sp + 32]
        std %i2, [%sp + 40]
        std %i4, [%sp + 48]
        std %i6, [%sp + 56]

        /* back to where we should be     */
	/* go back to the window T from which the save had trapped */
        restore

        /* set new value of window invalid mask       */
	/* new value of WIM.  N is marked invalid     */
        mov %l3,%wim
        nop; nop; nop

        /* trap handler done, reexecute the save which trapped.  This time
	/* window T is available.. no trap.   */
        jmp %l1

	/* Note rett does a restore, puts us back in W */
        rett %l2

!
! window underflow trap handler
!   From window W-1 we did a restore and we find that window
!   W is unavailable.. trap handler puts us in window W-2.
!
!
window_underflow_trap_handler:

	! current window = W-2

        /* rotate WIM on bit LEFT, we have 8 windows */ 
	/* This marks window W+1 as unavailable      */
        mov %wim,%l3
        srl %l3,7,%l4
        sll %l3,1,%l3
        or  %l3,%l4,%l3
        and %l3,0xff,%l3

        /* disable WIM traps */
        mov %g0,%wim
        nop; nop; nop

        /* get to correct window, ie window W */
        restore 	! move to window W-1
        restore		! move to window W

        /* recovers locals and ins of W   */
        ldd [%sp +  0], %l0
        ldd [%sp +  8], %l2
        ldd [%sp + 16], %l4
        ldd [%sp + 24], %l6
        ldd [%sp + 32], %i0
        ldd [%sp + 40], %i2
        ldd [%sp + 48], %i4
        ldd [%sp + 56], %i6

        /* go to window W-2 ...*/
        save		! move to W-1
        save		! move to W-2

        /* set new value of wim (W+1 is marked invalid) */
        mov %l3,%wim
        nop; nop; nop

        /* go home */
        jmp %l1
	/* back in W-1, retry with W valid.*/
        rett %l2

.section .text.traptablebase
	.align 4096
.global trap_table_base;
trap_table_base:
hardware_trap_table_base:
HW_trap_0x00: ta 0; nop; nop; nop;
HW_trap_0x01: ta 0; nop; nop; nop; ! instruction access exception
HW_trap_0x02: ta 0; nop; nop; nop; ! illegal instruction
HW_trap_0x03: ta 0; nop; nop; nop; ! privileged instruction 
HW_trap_0x04: ta 0; nop; nop; nop; ! fp unit disabled.
HW_trap_0x05: ! window overflow trap
	ba window_overflow_trap_handler; nop; nop; nop;
HW_trap_0x06: ! window underflow trap
	ba window_underflow_trap_handler; nop; nop; nop;
HW_trap_0x07: ta 0; nop; nop; nop; ! unaligned access exception
HW_trap_0x08: ta 0; nop; nop; nop; ! floating point exception.
HW_trap_0x09: ta 0; nop; nop; nop; ! data access exception.
HW_trap_0x0a: ta 0; nop; nop; nop; ! tagged overflow fault.
HW_trap_0x0b: ta 0; nop; nop; nop; 
HW_trap_0x0c: ta 0; nop; nop; nop; 
HW_trap_0x0d: ta 0; nop; nop; nop;
HW_trap_0x0e: ta 0; nop; nop; nop;
HW_trap_0x0f: ta 0; nop; nop; nop;
HW_trap_0x10: ta 0; nop; nop; nop;
# interrupt handlers start here.
HW_trap_0x11: 
	rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_isr; nop; 
HW_trap_0x12: 
	rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_isr; nop; 
HW_trap_0x13: 
	rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_isr; nop; 
HW_trap_0x14: 
	rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_isr; nop; 
HW_trap_0x15: 
	rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_isr; nop; 
HW_trap_0x16: 
	rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_isr; nop; 
HW_trap_0x17: 
	rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_isr; nop; 
HW_trap_0x18: 
	rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_isr; nop; 
HW_trap_0x19: 
	rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_isr; nop; 
# timer.
HW_trap_0x1a: 
	rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_isr; nop; 
HW_trap_0x1b: 
	rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_isr; nop; 
# serial
HW_trap_0x1c: 
	rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_isr; nop; 
# external
HW_trap_0x1d: 
	rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_isr; nop; 
HW_trap_0x1e: 
	rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_isr; nop; 
HW_trap_0x1f: 
	rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_isr; nop; 
# unhandled traps..
HW_trap_0x20: ta 0; nop; nop; nop;
HW_trap_0x21: ta 0; nop; nop; nop;
HW_trap_0x22: ta 0; nop; nop; nop;
HW_trap_0x23: ta 0; nop; nop; nop;
HW_trap_0x24: ta 0; nop; nop; nop; ! coprocessor disabled.
HW_trap_0x25: ta 0; nop; nop; nop;
HW_trap_0x26: ta 0; nop; nop; nop;
HW_trap_0x27: ta 0; nop; nop; nop;
HW_trap_0x28: ta 0; nop; nop; nop;
HW_trap_0x29: ta 0; nop; nop; nop;
HW_trap_0x2a: ta 0; nop; nop; nop; ! integer divide-by-zero.
HW_trap_0x2b: ta 0; nop; nop; nop;
HW_trap_0x2c: ta 0; nop; nop; nop;
HW_trap_0x2d: ta 0; nop; nop; nop;
HW_trap_0x2e: ta 0; nop; nop; nop;
HW_trap_0x2f: ta 0; nop; nop; nop;
HW_trap_0x30: ta 0; nop; nop; nop;
HW_trap_0x31: ta 0; nop; nop; nop;
HW_trap_0x32: ta 0; nop; nop; nop;
HW_trap_0x33: ta 0; nop; nop; nop;
HW_trap_0x34: ta 0; nop; nop; nop;
HW_trap_0x35: ta 0; nop; nop; nop;
HW_trap_0x36: ta 0; nop; nop; nop;
HW_trap_0x37: ta 0; nop; nop; nop;
HW_trap_0x38: ta 0; nop; nop; nop;
HW_trap_0x39: ta 0; nop; nop; nop;
HW_trap_0x3a: ta 0; nop; nop; nop;
HW_trap_0x3b: ta 0; nop; nop; nop;
HW_trap_0x3c: ta 0; nop; nop; nop;
HW_trap_0x3d: ta 0; nop; nop; nop;
HW_trap_0x3e: ta 0; nop; nop; nop;
HW_trap_0x3f: ta 0; nop; nop; nop;
HW_trap_0x40: ta 0; nop; nop; nop;
HW_trap_0x41: ta 0; nop; nop; nop;
HW_trap_0x42: ta 0; nop; nop; nop;
HW_trap_0x43: ta 0; nop; nop; nop;
HW_trap_0x44: ta 0; nop; nop; nop;
HW_trap_0x45: ta 0; nop; nop; nop;
HW_trap_0x46: ta 0; nop; nop; nop;
HW_trap_0x47: ta 0; nop; nop; nop;
HW_trap_0x48: ta 0; nop; nop; nop;
HW_trap_0x49: ta 0; nop; nop; nop;
HW_trap_0x4a: ta 0; nop; nop; nop;
HW_trap_0x4b: ta 0; nop; nop; nop;
HW_trap_0x4c: ta 0; nop; nop; nop;
HW_trap_0x4d: ta 0; nop; nop; nop;
HW_trap_0x4e: ta 0; nop; nop; nop;
HW_trap_0x4f: ta 0; nop; nop; nop;
HW_trap_0x50: ta 0; nop; nop; nop;
HW_trap_0x51: ta 0; nop; nop; nop;
HW_trap_0x52: ta 0; nop; nop; nop;
HW_trap_0x53: ta 0; nop; nop; nop;
HW_trap_0x54: ta 0; nop; nop; nop;
HW_trap_0x55: ta 0; nop; nop; nop;
HW_trap_0x56: ta 0; nop; nop; nop;
HW_trap_0x57: ta 0; nop; nop; nop;
HW_trap_0x58: ta 0; nop; nop; nop;
HW_trap_0x59: ta 0; nop; nop; nop;
HW_trap_0x5a: ta 0; nop; nop; nop;
HW_trap_0x5b: ta 0; nop; nop; nop;
HW_trap_0x5c: ta 0; nop; nop; nop;
HW_trap_0x5d: ta 0; nop; nop; nop;
HW_trap_0x5e: ta 0; nop; nop; nop;
HW_trap_0x5f: ta 0; nop; nop; nop;
HW_trap_0x60: ta 0; nop; nop; nop;
HW_trap_0x61: ta 0; nop; nop; nop;
HW_trap_0x62: ta 0; nop; nop; nop;
HW_trap_0x63: ta 0; nop; nop; nop;
HW_trap_0x64: ta 0; nop; nop; nop;
HW_trap_0x65: ta 0; nop; nop; nop;
HW_trap_0x66: ta 0; nop; nop; nop;
HW_trap_0x67: ta 0; nop; nop; nop;
HW_trap_0x68: ta 0; nop; nop; nop;
HW_trap_0x69: ta 0; nop; nop; nop;
HW_trap_0x6a: ta 0; nop; nop; nop;
HW_trap_0x6b: ta 0; nop; nop; nop;
HW_trap_0x6c: ta 0; nop; nop; nop;
HW_trap_0x6d: ta 0; nop; nop; nop;
HW_trap_0x6e: ta 0; nop; nop; nop;
HW_trap_0x6f: ta 0; nop; nop; nop;
HW_trap_0x70: ta 0; nop; nop; nop;
HW_trap_0x71: ta 0; nop; nop; nop;
HW_trap_0x72: ta 0; nop; nop; nop;
HW_trap_0x73: ta 0; nop; nop; nop;
HW_trap_0x74: ta 0; nop; nop; nop;
HW_trap_0x75: ta 0; nop; nop; nop;
HW_trap_0x76: ta 0; nop; nop; nop;
HW_trap_0x77: ta 0; nop; nop; nop;
HW_trap_0x78: ta 0; nop; nop; nop;
HW_trap_0x79: ta 0; nop; nop; nop;
HW_trap_0x7a: ta 0; nop; nop; nop;
HW_trap_0x7b: ta 0; nop; nop; nop;
HW_trap_0x7c: ta 0; nop; nop; nop;
HW_trap_0x7d: ta 0; nop; nop; nop;
HW_trap_0x7e: ta 0; nop; nop; nop;
HW_trap_0x7f: ta 0; nop; nop; nop;

software_trap_table_base:
# ta 0 is reserved for halt.
SW_trap_0x80: ta 0; nop; nop; nop;
# ta 1 to 15 for user traps.
# For the moment, we will allow users to use software traps 1-15. 
SW_trap_0x81: rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_sw_trap; nop; 
SW_trap_0x82: rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_sw_trap; nop; 
SW_trap_0x83: rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_sw_trap; nop; 
SW_trap_0x84: rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_sw_trap; nop; 
SW_trap_0x85: rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_sw_trap; nop; 
SW_trap_0x86: rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_sw_trap; nop; 
SW_trap_0x87: rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_sw_trap; nop; 
SW_trap_0x88: rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_sw_trap; nop; 
SW_trap_0x89: rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_sw_trap; nop; 
SW_trap_0x8a: rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_sw_trap; nop; 
SW_trap_0x8b: rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_sw_trap; nop; 
SW_trap_0x8c: rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_sw_trap; nop; 
SW_trap_0x8d: rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_sw_trap; nop; 
SW_trap_0x8e: rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_sw_trap; nop; 
SW_trap_0x8f: rd %psr, %l0; rd %tbr, %l3; ba generic_vectored_sw_trap; nop; 
# ta 16 for privileged asr register reads.
SW_trap_0x90: rd %psr, %l0; rd %tbr, %l3; ba generic_read_asr; nop;
# ta 17 for go to supervisor mode, continue from next instruction.
# NOTE: no return from trap!
SW_trap_0x91: ba generic_sys_go_to_supervisor; nop; nop; nop;
###  not assigned as  yet ###################################################
SW_trap_0x92: ta 0; nop; nop; nop;
SW_trap_0x93: ta 0; nop; nop; nop;
SW_trap_0x94: ta 0; nop; nop; nop;
SW_trap_0x95: ta 0; nop; nop; nop;
SW_trap_0x96: ta 0; nop; nop; nop;
SW_trap_0x97: ta 0; nop; nop; nop;
SW_trap_0x98: ta 0; nop; nop; nop;
SW_trap_0x99: ta 0; nop; nop; nop;
SW_trap_0x9a: ta 0; nop; nop; nop;
SW_trap_0x9b: ta 0; nop; nop; nop;
SW_trap_0x9c: ta 0; nop; nop; nop;
SW_trap_0x9d: ta 0; nop; nop; nop;
SW_trap_0x9e: ta 0; nop; nop; nop;
SW_trap_0x9f: ta 0; nop; nop; nop;
SW_trap_0xa0: ta 0; nop; nop; nop;
SW_trap_0xa1: ta 0; nop; nop; nop;
SW_trap_0xa2: ta 0; nop; nop; nop;
SW_trap_0xa3: ta 0; nop; nop; nop;
SW_trap_0xa4: ta 0; nop; nop; nop;
SW_trap_0xa5: ta 0; nop; nop; nop;
SW_trap_0xa6: ta 0; nop; nop; nop;
SW_trap_0xa7: ta 0; nop; nop; nop;
SW_trap_0xa8: ta 0; nop; nop; nop;
SW_trap_0xa9: ta 0; nop; nop; nop;
SW_trap_0xaa: ta 0; nop; nop; nop;
SW_trap_0xab: ta 0; nop; nop; nop;
SW_trap_0xac: ta 0; nop; nop; nop;
SW_trap_0xad: ta 0; nop; nop; nop;
SW_trap_0xae: ta 0; nop; nop; nop;
SW_trap_0xaf: ta 0; nop; nop; nop;
SW_trap_0xb0: ta 0; nop; nop; nop;
SW_trap_0xb1: ta 0; nop; nop; nop;
SW_trap_0xb2: ta 0; nop; nop; nop;
SW_trap_0xb3: ta 0; nop; nop; nop;
SW_trap_0xb4: ta 0; nop; nop; nop;
SW_trap_0xb5: ta 0; nop; nop; nop;
SW_trap_0xb6: ta 0; nop; nop; nop;
SW_trap_0xb7: ta 0; nop; nop; nop;
SW_trap_0xb8: ta 0; nop; nop; nop;
SW_trap_0xb9: ta 0; nop; nop; nop;
SW_trap_0xba: ta 0; nop; nop; nop;
SW_trap_0xbb: ta 0; nop; nop; nop;
SW_trap_0xbc: ta 0; nop; nop; nop;
SW_trap_0xbd: ta 0; nop; nop; nop;
SW_trap_0xbe: ta 0; nop; nop; nop;
SW_trap_0xbf: ta 0; nop; nop; nop;
SW_trap_0xc0: ta 0; nop; nop; nop;
SW_trap_0xc1: ta 0; nop; nop; nop;
SW_trap_0xc2: ta 0; nop; nop; nop;
SW_trap_0xc3: ta 0; nop; nop; nop;
SW_trap_0xc4: ta 0; nop; nop; nop;
SW_trap_0xc5: ta 0; nop; nop; nop;
SW_trap_0xc6: ta 0; nop; nop; nop;
SW_trap_0xc7: ta 0; nop; nop; nop;
SW_trap_0xc8: ta 0; nop; nop; nop;
SW_trap_0xc9: ta 0; nop; nop; nop;
SW_trap_0xca: ta 0; nop; nop; nop;
SW_trap_0xcb: ta 0; nop; nop; nop;
SW_trap_0xcc: ta 0; nop; nop; nop;
SW_trap_0xcd: ta 0; nop; nop; nop;
SW_trap_0xce: ta 0; nop; nop; nop;
SW_trap_0xcf: ta 0; nop; nop; nop;
SW_trap_0xd0: ta 0; nop; nop; nop;
SW_trap_0xd1: ta 0; nop; nop; nop;
SW_trap_0xd2: ta 0; nop; nop; nop;
SW_trap_0xd3: ta 0; nop; nop; nop;
SW_trap_0xd4: ta 0; nop; nop; nop;
SW_trap_0xd5: ta 0; nop; nop; nop;
SW_trap_0xd6: ta 0; nop; nop; nop;
SW_trap_0xd7: ta 0; nop; nop; nop;
SW_trap_0xd8: ta 0; nop; nop; nop;
SW_trap_0xd9: ta 0; nop; nop; nop;
SW_trap_0xda: ta 0; nop; nop; nop;
SW_trap_0xdb: ta 0; nop; nop; nop;
SW_trap_0xdc: ta 0; nop; nop; nop;
SW_trap_0xdd: ta 0; nop; nop; nop;
SW_trap_0xde: ta 0; nop; nop; nop;
SW_trap_0xdf: ta 0; nop; nop; nop;
SW_trap_0xe0: ta 0; nop; nop; nop;
SW_trap_0xe1: ta 0; nop; nop; nop;
SW_trap_0xe2: ta 0; nop; nop; nop;
SW_trap_0xe3: ta 0; nop; nop; nop;
SW_trap_0xe4: ta 0; nop; nop; nop;
SW_trap_0xe5: ta 0; nop; nop; nop;
SW_trap_0xe6: ta 0; nop; nop; nop;
SW_trap_0xe7: ta 0; nop; nop; nop;
SW_trap_0xe8: ta 0; nop; nop; nop;
SW_trap_0xe9: ta 0; nop; nop; nop;
SW_trap_0xea: ta 0; nop; nop; nop;
SW_trap_0xeb: ta 0; nop; nop; nop;
SW_trap_0xec: ta 0; nop; nop; nop;
SW_trap_0xed: ta 0; nop; nop; nop;
SW_trap_0xee: ta 0; nop; nop; nop;
SW_trap_0xef: ta 0; nop; nop; nop;
SW_trap_0xf0: ta 0; nop; nop; nop;
SW_trap_0xf1: ta 0; nop; nop; nop;
SW_trap_0xf2: ta 0; nop; nop; nop;
SW_trap_0xf3: ta 0; nop; nop; nop;
SW_trap_0xf4: ta 0; nop; nop; nop;
SW_trap_0xf5: ta 0; nop; nop; nop;
SW_trap_0xf6: ta 0; nop; nop; nop;
SW_trap_0xf7: ta 0; nop; nop; nop;
SW_trap_0xf8: ta 0; nop; nop; nop;
SW_trap_0xf9: ta 0; nop; nop; nop;
SW_trap_0xfa: ta 0; nop; nop; nop;
SW_trap_0xfb: ta 0; nop; nop; nop;
SW_trap_0xfc: ta 0; nop; nop; nop;
SW_trap_0xfd: ta 0; nop; nop; nop;
SW_trap_0xfe: ta 0; nop; nop; nop;

nop
nop

