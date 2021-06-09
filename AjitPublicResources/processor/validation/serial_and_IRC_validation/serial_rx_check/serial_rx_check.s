    ! enable interrupts.
    mov 0x0, %sp
    mov 0xE0, %l0  
    wr %l0, %psr 
    mov 0xa, %o0
    !sll %o0, 0x18, %o0
 
    ! trap table
    set   trap_table_base, %l0
    wr        %l0, 0x0, %tbr   
    ! start the test..
    sethi  %hi(0xffff3000), %g1
    ! enable tx, rx, rx-int on serial.
    or  %g1, 0x200, %g1
    or  %g1, 0x10,  %g4  ! g4 points to tx-buffer.
    or  %g1, 0x20,  %g5  ! g5 points to rx-buffer
    or  %g0, 0x3,   %g2	 ! 
    sta %g2, [%g1] 0x20  ! enable rx,tx
    lda [%g1] 0x20, %g3  ! g3 should contain 0x3 
    
    !
spinloop:
    lduba [%g5] 0x20, %g3  ! read the rx buffer.
    orcc  %g0, %g3, %g3    ! check for null byte.
    bnz,a  checkret
    stuba %g3, [%g4] 0x20  ! store into tx buffer.
checkret:
    subcc %g3, %o0 , %g6
    bnz spinloop
    nop
    ta 0

.align 4096;
trap_table_base:
HW_trap_0x00: mov 0x00, %g7; restore; ta 0; nop;
HW_trap_0x01: mov 0x01, %g7; restore; ta 0; nop;
HW_trap_0x02: mov 0x02, %g7; restore; ta 0; nop;
HW_trap_0x03: mov 0x03, %g7; restore; ta 0; nop;
HW_trap_0x04: mov 0x04, %g7; restore; ta 0; nop;
HW_trap_0x05: mov 0x05, %g7; restore; ta 0; nop;
HW_trap_0x06: mov 0x06, %g7; restore; ta 0; nop;
HW_trap_0x07: mov 0x07, %g7; restore; ta 0; nop;
HW_trap_0x08: mov 0x08, %g7; restore; ta 0; nop;
HW_trap_0x09: mov 0x09, %g7; restore; ta 0; nop;
HW_trap_0x0a: mov 0x0a, %g7; restore; ta 0; nop;
HW_trap_0x0b: mov 0x0b, %g7; restore; ta 0; nop;
HW_trap_0x0c: mov 0x0c, %g7; restore; ta 0; nop;
HW_trap_0x0d: mov 0x0d, %g7; restore; ta 0; nop;
HW_trap_0x0e: mov 0x0e, %g7; restore; ta 0; nop;
HW_trap_0x0f: mov 0x0f, %g7; restore; ta 0; nop;
HW_trap_0x10: mov 0x10, %g7; restore; ta 0; nop;
HW_trap_0x11: mov 0x11, %g7; restore; ta 0; nop;
HW_trap_0x12: mov 0x12, %g7; restore; ta 0; nop;
HW_trap_0x13: mov 0x13, %g7; restore; ta 0; nop;
HW_trap_0x14: mov 0x14, %g7; restore; ta 0; nop;
HW_trap_0x15: mov 0x15, %g7; restore; ta 0; nop;
HW_trap_0x16: mov 0x16, %g7; restore; ta 0; nop;
HW_trap_0x17: mov 0x17, %g7; restore; ta 0; nop;
HW_trap_0x18: mov 0x18, %g7; restore; ta 0; nop;
HW_trap_0x19: mov 0x19, %g7; restore; ta 0; nop;
HW_trap_0x1a: mov 0x20, %g7; restore; ta 0; nop;
HW_trap_0x1b: mov 0x1b, %g7; restore; ta 0; nop;
HW_trap_0x1c: mov 0x1c, %g7; restore; ta 0; nop;
HW_trap_0x1d: mov 0x1d, %g7; restore; ta 0; nop;
HW_trap_0x1e: mov 0x1e, %g7; restore; ta 0; nop;
HW_trap_0x1f: mov 0x1f, %g7; restore; ta 0; nop;
HW_trap_0x20: mov 0x20, %g7; restore; ta 0; nop;
HW_trap_0x21: mov 0x21, %g7; restore; ta 0; nop;
HW_trap_0x22: mov 0x22, %g7; restore; ta 0; nop;
HW_trap_0x23: mov 0x23, %g7; restore; ta 0; nop;
HW_trap_0x24: mov 0x24, %g7; restore; ta 0; nop;
HW_trap_0x25: mov 0x25, %g7; restore; ta 0; nop;
HW_trap_0x26: mov 0x26, %g7; restore; ta 0; nop;
HW_trap_0x27: mov 0x27, %g7; restore; ta 0; nop;
HW_trap_0x28: mov 0x28, %g7; restore; ta 0; nop;
HW_trap_0x29: mov 0x29, %g7; restore; ta 0; nop;
HW_trap_0x2a: mov 0x2a, %g7; restore; ta 0; nop;
HW_trap_0x2b: mov 0x2b, %g7; restore; ta 0; nop;
HW_trap_0x2c: mov 0x2c, %g7; restore; ta 0; nop;
HW_trap_0x2d: mov 0x2d, %g7; restore; ta 0; nop;
HW_trap_0x2e: mov 0x2e, %g7; restore; ta 0; nop;
HW_trap_0x2f: mov 0x2f, %g7; restore; ta 0; nop;
HW_trap_0x30: mov 0x30, %g7; restore; ta 0; nop;
HW_trap_0x31: mov 0x31, %g7; restore; ta 0; nop;
HW_trap_0x32: mov 0x32, %g7; restore; ta 0; nop;
HW_trap_0x33: mov 0x33, %g7; restore; ta 0; nop;
HW_trap_0x34: mov 0x34, %g7; restore; ta 0; nop;
HW_trap_0x35: mov 0x35, %g7; restore; ta 0; nop;
HW_trap_0x36: mov 0x36, %g7; restore; ta 0; nop;
HW_trap_0x37: mov 0x37, %g7; restore; ta 0; nop;
HW_trap_0x38: mov 0x38, %g7; restore; ta 0; nop;
HW_trap_0x39: mov 0x39, %g7; restore; ta 0; nop;
HW_trap_0x3a: mov 0x3a, %g7; restore; ta 0; nop;
HW_trap_0x3b: mov 0x3b, %g7; restore; ta 0; nop;
HW_trap_0x3c: mov 0x3c, %g7; restore; ta 0; nop;
HW_trap_0x3d: mov 0x3d, %g7; restore; ta 0; nop;
HW_trap_0x3e: mov 0x3e, %g7; restore; ta 0; nop;
HW_trap_0x3f: mov 0x3f, %g7; restore; ta 0; nop;
HW_trap_0x40: mov 0x40, %g7; restore; ta 0; nop;
HW_trap_0x41: mov 0x41, %g7; restore; ta 0; nop;
HW_trap_0x42: mov 0x42, %g7; restore; ta 0; nop;
HW_trap_0x43: mov 0x43, %g7; restore; ta 0; nop;
HW_trap_0x44: mov 0x44, %g7; restore; ta 0; nop;
HW_trap_0x45: mov 0x45, %g7; restore; ta 0; nop;
HW_trap_0x46: mov 0x46, %g7; restore; ta 0; nop;
HW_trap_0x47: mov 0x47, %g7; restore; ta 0; nop;
HW_trap_0x48: mov 0x48, %g7; restore; ta 0; nop;
HW_trap_0x49: mov 0x49, %g7; restore; ta 0; nop;
HW_trap_0x4a: mov 0x4a, %g7; restore; ta 0; nop;
HW_trap_0x4b: mov 0x4b, %g7; restore; ta 0; nop;
HW_trap_0x4c: mov 0x4c, %g7; restore; ta 0; nop;
HW_trap_0x4d: mov 0x4d, %g7; restore; ta 0; nop;
HW_trap_0x4e: mov 0x4e, %g7; restore; ta 0; nop;
HW_trap_0x4f: mov 0x4f, %g7; restore; ta 0; nop;
HW_trap_0x50: mov 0x50, %g7; restore; ta 0; nop;
HW_trap_0x51: mov 0x51, %g7; restore; ta 0; nop;
HW_trap_0x52: mov 0x52, %g7; restore; ta 0; nop;
HW_trap_0x53: mov 0x53, %g7; restore; ta 0; nop;
HW_trap_0x54: mov 0x54, %g7; restore; ta 0; nop;
HW_trap_0x55: mov 0x55, %g7; restore; ta 0; nop;
HW_trap_0x56: mov 0x56, %g7; restore; ta 0; nop;
HW_trap_0x57: mov 0x57, %g7; restore; ta 0; nop;
HW_trap_0x58: mov 0x58, %g7; restore; ta 0; nop;
HW_trap_0x59: mov 0x59, %g7; restore; ta 0; nop;
HW_trap_0x5a: mov 0x5a, %g7; restore; ta 0; nop;
HW_trap_0x5b: mov 0x5b, %g7; restore; ta 0; nop;
HW_trap_0x5c: mov 0x5c, %g7; restore; ta 0; nop;
HW_trap_0x5d: mov 0x5d, %g7; restore; ta 0; nop;
HW_trap_0x5e: mov 0x5e, %g7; restore; ta 0; nop;
HW_trap_0x5f: mov 0x5f, %g7; restore; ta 0; nop;
HW_trap_0x60: mov 0x60, %g7; restore; ta 0; nop;
HW_trap_0x61: mov 0x61, %g7; restore; ta 0; nop;
HW_trap_0x62: mov 0x62, %g7; restore; ta 0; nop;
HW_trap_0x63: mov 0x63, %g7; restore; ta 0; nop;
HW_trap_0x64: mov 0x64, %g7; restore; ta 0; nop;
HW_trap_0x65: mov 0x65, %g7; restore; ta 0; nop;
HW_trap_0x66: mov 0x66, %g7; restore; ta 0; nop;
HW_trap_0x67: mov 0x67, %g7; restore; ta 0; nop;
HW_trap_0x68: mov 0x68, %g7; restore; ta 0; nop;
HW_trap_0x69: mov 0x69, %g7; restore; ta 0; nop;
HW_trap_0x6a: mov 0x6a, %g7; restore; ta 0; nop;
HW_trap_0x6b: mov 0x6b, %g7; restore; ta 0; nop;
HW_trap_0x6c: mov 0x6c, %g7; restore; ta 0; nop;
HW_trap_0x6d: mov 0x6d, %g7; restore; ta 0; nop;
HW_trap_0x6e: mov 0x6e, %g7; restore; ta 0; nop;
HW_trap_0x6f: mov 0x6f, %g7; restore; ta 0; nop;
HW_trap_0x70: mov 0x70, %g7; restore; ta 0; nop;
HW_trap_0x71: mov 0x71, %g7; restore; ta 0; nop;
HW_trap_0x72: mov 0x72, %g7; restore; ta 0; nop;
HW_trap_0x73: mov 0x73, %g7; restore; ta 0; nop;
HW_trap_0x74: mov 0x74, %g7; restore; ta 0; nop;
HW_trap_0x75: mov 0x75, %g7; restore; ta 0; nop;
HW_trap_0x76: mov 0x76, %g7; restore; ta 0; nop;
HW_trap_0x77: mov 0x77, %g7; restore; ta 0; nop;
HW_trap_0x78: mov 0x78, %g7; restore; ta 0; nop;
HW_trap_0x79: mov 0x79, %g7; restore; ta 0; nop;
HW_trap_0x7a: mov 0x7a, %g7; restore; ta 0; nop;
HW_trap_0x7b: mov 0x7b, %g7; restore; ta 0; nop;
HW_trap_0x7c: mov 0x7c, %g7; restore; ta 0; nop;
HW_trap_0x7d: mov 0x7d, %g7; restore; ta 0; nop;
HW_trap_0x7e: mov 0x7e, %g7; restore; ta 0; nop;
HW_trap_0x7f: mov 0x7f, %g7; restore; ta 0; nop;
software_trap_table_base:
SW_trap_0x80: mov 0x80, %g7; restore; ta 0; nop;
SW_trap_0x81: mov 0x81, %g7; restore; ta 0; nop;
SW_trap_0x82: mov 0x81, %g7; restore; ta 0; nop;
SW_trap_0x83: mov 0x83, %g7; restore; ta 0; nop;
SW_trap_0x84: mov 0x84, %g7; restore; ta 0; nop;
SW_trap_0x85: mov 0x85, %g7; restore; ta 0; nop;
SW_trap_0x86: mov 0x86, %g7; restore; ta 0; nop;
SW_trap_0x87: mov 0x87, %g7; restore; ta 0; nop;
SW_trap_0x88: mov 0x88, %g7; restore; ta 0; nop;
SW_trap_0x89: mov 0x89, %g7; restore; ta 0; nop;
SW_trap_0x8a: mov 0x8a, %g7; restore; ta 0; nop;
SW_trap_0x8b: mov 0x8b, %g7; restore; ta 0; nop;
SW_trap_0x8c: mov 0x8c, %g7; restore; ta 0; nop;
SW_trap_0x8d: mov 0x8d, %g7; restore; ta 0; nop;
SW_trap_0x8e: mov 0x8e, %g7; restore; ta 0; nop;
SW_trap_0x8f: mov 0x8f, %g7; restore; ta 0; nop;
SW_trap_0x90: mov 0x90, %g7; restore; ta 0; nop;
SW_trap_0x91: mov 0x91, %g7; restore; ta 0; nop;
SW_trap_0x92: mov 0x92, %g7; restore; ta 0; nop;
SW_trap_0x93: mov 0x93, %g7; restore; ta 0; nop;
SW_trap_0x94: mov 0x94, %g7; restore; ta 0; nop;
SW_trap_0x95: mov 0x95, %g7; restore; ta 0; nop;
SW_trap_0x96: mov 0x96, %g7; restore; ta 0; nop;
SW_trap_0x97: mov 0x97, %g7; restore; ta 0; nop;
SW_trap_0x98: mov 0x98, %g7; restore; ta 0; nop;
SW_trap_0x99: mov 0x99, %g7; restore; ta 0; nop;
SW_trap_0x9a: mov 0x9a, %g7; restore; ta 0; nop;
SW_trap_0x9b: mov 0x9b, %g7; restore; ta 0; nop;
SW_trap_0x9c: mov 0x9c, %g7; restore; ta 0; nop;
SW_trap_0x9d: mov 0x9d, %g7; restore; ta 0; nop;
SW_trap_0x9e: mov 0x9e, %g7; restore; ta 0; nop;
SW_trap_0x9f: mov 0x9f, %g7; restore; ta 0; nop;
SW_trap_0xa0: mov 0xa0, %g7; restore; ta 0; nop;
SW_trap_0xa1: mov 0xa1, %g7; restore; ta 0; nop;
SW_trap_0xa2: mov 0xa2, %g7; restore; ta 0; nop;
SW_trap_0xa3: mov 0xa3, %g7; restore; ta 0; nop;
SW_trap_0xa4: mov 0xa4, %g7; restore; ta 0; nop;
SW_trap_0xa5: mov 0xa5, %g7; restore; ta 0; nop;
SW_trap_0xa6: mov 0xa6, %g7; restore; ta 0; nop;
SW_trap_0xa7: mov 0xa7, %g7; restore; ta 0; nop;
SW_trap_0xa8: mov 0xa8, %g7; restore; ta 0; nop;
SW_trap_0xa9: mov 0xa9, %g7; restore; ta 0; nop;
SW_trap_0xaa: mov 0xaa, %g7; restore; ta 0; nop;
SW_trap_0xab: mov 0xab, %g7; restore; ta 0; nop;
SW_trap_0xac: mov 0xac, %g7; restore; ta 0; nop;
SW_trap_0xad: mov 0xad, %g7; restore; ta 0; nop;
SW_trap_0xae: mov 0xae, %g7; restore; ta 0; nop;
SW_trap_0xaf: mov 0xaf, %g7; restore; ta 0; nop;
SW_trap_0xb0: mov 0xb0, %g7; restore; ta 0; nop;
SW_trap_0xb1: mov 0xb1, %g7; restore; ta 0; nop;
SW_trap_0xb2: mov 0xb2, %g7; restore; ta 0; nop;
SW_trap_0xb3: mov 0xb3, %g7; restore; ta 0; nop;
SW_trap_0xb4: mov 0xb4, %g7; restore; ta 0; nop;
SW_trap_0xb5: mov 0xb5, %g7; restore; ta 0; nop;
SW_trap_0xb6: mov 0xb6, %g7; restore; ta 0; nop;
SW_trap_0xb7: mov 0xb7, %g7; restore; ta 0; nop;
SW_trap_0xb8: mov 0xb8, %g7; restore; ta 0; nop;
SW_trap_0xb9: mov 0xb9, %g7; restore; ta 0; nop;
SW_trap_0xba: mov 0xba, %g7; restore; ta 0; nop;
SW_trap_0xbb: mov 0xbb, %g7; restore; ta 0; nop;
SW_trap_0xbc: mov 0xbc, %g7; restore; ta 0; nop;
SW_trap_0xbd: mov 0xbd, %g7; restore; ta 0; nop;
SW_trap_0xbe: mov 0xbe, %g7; restore; ta 0; nop;
SW_trap_0xbf: mov 0xbf, %g7; restore; ta 0; nop;
SW_trap_0xc0: mov 0xc0, %g7; restore; ta 0; nop;
SW_trap_0xc1: mov 0xc1, %g7; restore; ta 0; nop;
SW_trap_0xc2: mov 0xc2, %g7; restore; ta 0; nop;
SW_trap_0xc3: mov 0xc3, %g7; restore; ta 0; nop;
SW_trap_0xc4: mov 0xc4, %g7; restore; ta 0; nop;
SW_trap_0xc5: mov 0xc5, %g7; restore; ta 0; nop;
SW_trap_0xc6: mov 0xc6, %g7; restore; ta 0; nop;
SW_trap_0xc7: mov 0xc7, %g7; restore; ta 0; nop;
SW_trap_0xc8: mov 0xc8, %g7; restore; ta 0; nop;
SW_trap_0xc9: mov 0xc9, %g7; restore; ta 0; nop;
SW_trap_0xca: mov 0xca, %g7; restore; ta 0; nop;
SW_trap_0xcb: mov 0xcb, %g7; restore; ta 0; nop;
SW_trap_0xcc: mov 0xcc, %g7; restore; ta 0; nop;
SW_trap_0xcd: mov 0xcd, %g7; restore; ta 0; nop;
SW_trap_0xce: mov 0xce, %g7; restore; ta 0; nop;
SW_trap_0xcf: mov 0xcf, %g7; restore; ta 0; nop;
SW_trap_0xd0: mov 0xd0, %g7; restore; ta 0; nop;
SW_trap_0xd1: mov 0xd1, %g7; restore; ta 0; nop;
SW_trap_0xd2: mov 0xd2, %g7; restore; ta 0; nop;
SW_trap_0xd3: mov 0xd3, %g7; restore; ta 0; nop;
SW_trap_0xd4: mov 0xd4, %g7; restore; ta 0; nop;
SW_trap_0xd5: mov 0xd5, %g7; restore; ta 0; nop;
SW_trap_0xd6: mov 0xd6, %g7; restore; ta 0; nop;
SW_trap_0xd7: mov 0xd7, %g7; restore; ta 0; nop;
SW_trap_0xd8: mov 0xd8, %g7; restore; ta 0; nop;
SW_trap_0xd9: mov 0xd9, %g7; restore; ta 0; nop;
SW_trap_0xda: mov 0xda, %g7; restore; ta 0; nop;
SW_trap_0xdb: mov 0xdb, %g7; restore; ta 0; nop;
SW_trap_0xdc: mov 0xdc, %g7; restore; ta 0; nop;
SW_trap_0xdd: mov 0xdd, %g7; restore; ta 0; nop;
SW_trap_0xde: mov 0xde, %g7; restore; ta 0; nop;
SW_trap_0xdf: mov 0xdf, %g7; restore; ta 0; nop;
SW_trap_0xe0: mov 0xe0, %g7; restore; ta 0; nop;
SW_trap_0xe1: mov 0xe1, %g7; restore; ta 0; nop;
SW_trap_0xe2: mov 0xe2, %g7; restore; ta 0; nop;
SW_trap_0xe3: mov 0xe3, %g7; restore; ta 0; nop;
SW_trap_0xe4: mov 0xe4, %g7; restore; ta 0; nop;
SW_trap_0xe5: mov 0xe5, %g7; restore; ta 0; nop;
SW_trap_0xe6: mov 0xe6, %g7; restore; ta 0; nop;
SW_trap_0xe7: mov 0xe7, %g7; restore; ta 0; nop;
SW_trap_0xe8: mov 0xe8, %g7; restore; ta 0; nop;
SW_trap_0xe9: mov 0xe9, %g7; restore; ta 0; nop;
SW_trap_0xea: mov 0xea, %g7; restore; ta 0; nop;
SW_trap_0xeb: mov 0xeb, %g7; restore; ta 0; nop;
SW_trap_0xec: mov 0xec, %g7; restore; ta 0; nop;
SW_trap_0xed: mov 0xed, %g7; restore; ta 0; nop;
SW_trap_0xee: mov 0xee, %g7; restore; ta 0; nop;
SW_trap_0xef: mov 0xef, %g7; restore; ta 0; nop;
SW_trap_0xf0: mov 0xf0, %g7; restore; ta 0; nop;
SW_trap_0xf1: mov 0xf1, %g7; restore; ta 0; nop;
SW_trap_0xf2: mov 0xf2, %g7; restore; ta 0; nop;
SW_trap_0xf3: mov 0xf3, %g7; restore; ta 0; nop;
SW_trap_0xf4: mov 0xf4, %g7; restore; ta 0; nop;
SW_trap_0xf5: mov 0xf5, %g7; restore; ta 0; nop;
SW_trap_0xf6: mov 0xf6, %g7; restore; ta 0; nop;
SW_trap_0xf7: mov 0xf7, %g7; restore; ta 0; nop;
SW_trap_0xf8: mov 0xf8, %g7; restore; ta 0; nop;
SW_trap_0xf9: mov 0xf9, %g7; restore; ta 0; nop;
SW_trap_0xfa: mov 0xfa, %g7; restore; ta 0; nop;
SW_trap_0xfb: mov 0xfb, %g7; restore; ta 0; nop;
SW_trap_0xfc: mov 0xfc, %g7; restore; ta 0; nop;
SW_trap_0xfd: mov 0xfd, %g7; restore; ta 0; nop;
SW_trap_0xfe: mov 0xfe, %g7; restore; ta 0; nop;
