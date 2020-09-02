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
	/* new value of WIM.  (W+1) is marked invalid */
        mov %l3,%wim
        nop; nop; nop

        /* trap handler done, reexecute the save which trapped.  This time
	/* window W is available.. no trap.   */
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
        
        /* rotate WIM on bit LEFT, we have 8 windows */ 
        mov %wim,%l3
        srl %l3,7,%l4
        sll %l3,1,%l3
        or  %l3,%l4,%l3
        and %l3,0xff,%l3

        /* disable WIM traps */
        mov %g0,%wim
        nop; nop; nop

        /* get to correct window, ie window W */
        restore 	
        restore	

        /* recovers locals and ins of W   */
        ldd [%sp +  0], %l0
        ldd [%sp +  8], %l2
        ldd [%sp + 16], %l4
        ldd [%sp + 24], %l6
        ldd [%sp + 32], %i0
        ldd [%sp + 40], %i2
        ldd [%sp + 48], %i4
        ldd [%sp + 56], %i6

        /* go to window W-2 */
        save
        save

        /* set new value of window */
        mov %l3,%wim
        nop; nop; nop

        /* go home */
        jmp %l1
	/* back in W-1, retry with W valid.*/
        rett %l2
	nop

/* save psr, tbr, wim, l0 into g4, g5, g6, g7 respectively  */
record_trap_debug_status:
        rd %psr,  %g4 
        rd %tbr,  %g5
        rd %wim,  %g6
        mov %o7,  %g7 /* pc */
        retl
        nop


.section .text.traptablebase
	.align 4096
.global trap_table_base;
/* for all traps other than window-overflow/underflow */
/* we are putting the processor in error mode.        */
/* the routine record_trap_debug_status saves some    */
/* info about the trap into g4-g7                     */
trap_table_base:
hardware_trap_table_base:
HW_trap_0x00: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x01: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x02: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x03: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x04: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x05: ! window overflow trap
	ba window_overflow_trap_handler; nop; nop; nop;
HW_trap_0x06: ! window underflow trap
	ba window_underflow_trap_handler; nop; nop; nop;
HW_trap_0x07: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x08: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x09: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x0a: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x0b: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x0c: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x0d: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x0e: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x0f: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x10: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x11: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x12: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x13: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x14: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x15: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x16: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x17: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x18: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x19: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x1a: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x1b: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x1c: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x1d: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x1e: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x1f: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x20: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x21: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x22: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x23: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x24: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x25: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x26: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x27: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x28: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x29: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x2a: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x2b: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x2c: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x2d: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x2e: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x2f: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x30: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x31: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x32: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x33: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x34: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x35: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x36: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x37: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x38: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x39: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x3a: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x3b: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x3c: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x3d: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x3e: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x3f: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x40: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x41: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x42: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x43: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x44: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x45: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x46: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x47: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x48: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x49: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x4a: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x4b: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x4c: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x4d: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x4e: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x4f: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x50: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x51: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x52: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x53: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x54: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x55: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x56: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x57: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x58: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x59: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x5a: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x5b: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x5c: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x5d: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x5e: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x5f: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x60: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x61: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x62: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x63: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x64: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x65: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x66: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x67: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x68: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x69: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x6a: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x6b: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x6c: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x6d: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x6e: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x6f: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x70: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x71: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x72: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x73: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x74: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x75: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x76: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x77: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x78: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x79: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x7a: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x7b: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x7c: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x7d: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x7e: call record_trap_debug_status; nop; ta 0; nop;
HW_trap_0x7f: call record_trap_debug_status; nop; ta 0; nop;

software_trap_table_base:

SW_trap_0x80: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x81: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x82: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x83: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x84: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x85: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x86: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x87: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x88: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x89: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x8a: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x8b: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x8c: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x8d: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x8e: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x8f: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x90: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x91: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x92: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x93: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x94: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x95: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x96: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x97: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x98: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x99: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x9a: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x9b: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x9c: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x9d: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x9e: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0x9f: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xa0: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xa1: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xa2: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xa3: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xa4: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xa5: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xa6: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xa7: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xa8: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xa9: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xaa: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xab: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xac: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xad: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xae: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xaf: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xb0: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xb1: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xb2: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xb3: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xb4: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xb5: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xb6: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xb7: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xb8: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xb9: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xba: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xbb: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xbc: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xbd: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xbe: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xbf: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xc0: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xc1: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xc2: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xc3: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xc4: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xc5: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xc6: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xc7: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xc8: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xc9: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xca: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xcb: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xcc: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xcd: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xce: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xcf: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xd0: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xd1: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xd2: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xd3: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xd4: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xd5: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xd6: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xd7: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xd8: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xd9: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xda: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xdb: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xdc: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xdd: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xde: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xdf: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xe0: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xe1: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xe2: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xe3: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xe4: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xe5: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xe6: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xe7: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xe8: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xe9: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xea: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xeb: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xec: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xed: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xee: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xef: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xf0: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xf1: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xf2: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xf3: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xf4: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xf5: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xf6: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xf7: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xf8: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xf9: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xfa: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xfb: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xfc: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xfd: call record_trap_debug_status; nop; ta 0; nop;
SW_trap_0xfe: call record_trap_debug_status; nop; ta 0; nop;

nop
nop

