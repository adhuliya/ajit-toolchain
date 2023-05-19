	.file	"ajit_mt_sw_traps.c"
	.section	".text"
.Ltext0:
	.cfi_sections	.debug_frame
	.common	ajit_global_sw_trap_handlers,64,4
	.align 4
	.global ajit_initialize_sw_trap_handlers_to_null
	.type	ajit_initialize_sw_trap_handlers_to_null, #function
	.proc	020
ajit_initialize_sw_trap_handlers_to_null:
.LFB0:
	.file 1 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_mt_sw_traps.c"
	.loc 1 10 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI0:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 12 0
	st	%g0, [%fp-4]
	b	.L2
	 nop
.L3:
	.loc 1 13 0 discriminator 2
	sethi	%hi(ajit_global_sw_trap_handlers), %g1
	or	%g1, %lo(ajit_global_sw_trap_handlers), %g2
	ld	[%fp-4], %g1
	sll	%g1, 2, %g1
	st	%g0, [%g2+%g1]
	.loc 1 12 0 discriminator 2
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-4]
.L2:
	.loc 1 12 0 is_stmt 0 discriminator 1
	ld	[%fp-4], %g1
	cmp	%g1, 15
	ble	.L3
	 nop
	.loc 1 14 0 is_stmt 1
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE0:
	.size	ajit_initialize_sw_trap_handlers_to_null, .-ajit_initialize_sw_trap_handlers_to_null
	.align 4
	.global ajit_set_sw_trap_handler
	.type	ajit_set_sw_trap_handler, #function
	.proc	020
ajit_set_sw_trap_handler:
.LFB1:
	.loc 1 17 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI1:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	.loc 1 18 0
	ld	[%fp+68], %g1
	cmp	%g1, 15
	bgu	.L4
	 nop
	.loc 1 19 0
	sethi	%hi(ajit_global_sw_trap_handlers), %g1
	or	%g1, %lo(ajit_global_sw_trap_handlers), %g2
	ld	[%fp+68], %g1
	sll	%g1, 2, %g1
	ld	[%fp+72], %g3
	st	%g3, [%g2+%g1]
.L4:
	.loc 1 21 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE1:
	.size	ajit_set_sw_trap_handler, .-ajit_set_sw_trap_handler
	.align 4
	.global ajit_generic_sw_trap_handler
	.type	ajit_generic_sw_trap_handler, #function
	.proc	020
ajit_generic_sw_trap_handler:
.LFB2:
	.loc 1 24 0
	.cfi_startproc
	save	%sp, -112, %sp
.LCFI2:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	.loc 1 25 0
	st	%g0, [%fp-4]
	.loc 1 26 0
	ld	[%fp+68], %g1
	srl	%g1, 4, %g1
	and	%g1, 255, %g1
	add	%g1, -128, %g1
	st	%g1, [%fp-8]
	.loc 1 27 0
	ld	[%fp-8], %g1
	cmp	%g1, 15
	bgu	.L7
	 nop
.LBB2:
	.loc 1 29 0
	sethi	%hi(ajit_global_sw_trap_handlers), %g1
	or	%g1, %lo(ajit_global_sw_trap_handlers), %g2
	ld	[%fp-8], %g1
	sll	%g1, 2, %g1
	ld	[%g2+%g1], %g1
	st	%g1, [%fp-12]
	.loc 1 30 0
	ld	[%fp-12], %g1
	cmp	%g1, 0
	be	.L8
	 nop
	.loc 1 32 0
	ld	[%fp-12], %g1
	ld	[%fp+72], %o0
	ld	[%fp+76], %o1
	ld	[%fp+80], %o2
	call	%g1, 0
	 nop
	b	.L9
	 nop
.L8:
	.loc 1 36 0
	mov	1, %g1
	st	%g1, [%fp-4]
	b	.L9
	 nop
.L7:
.LBE2:
	.loc 1 40 0
	mov	1, %g1
	st	%g1, [%fp-4]
.L9:
	.loc 1 43 0
	ld	[%fp-4], %g1
	cmp	%g1, 0
	be	.L6
	 nop
	.loc 1 45 0
#APP
! 45 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_mt_sw_traps.c" 1
	ta 0;
! 0 "" 2
#NO_APP
.L6:
	.loc 1 47 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE2:
	.size	ajit_generic_sw_trap_handler, .-ajit_generic_sw_trap_handler
.Letext0:
	.file 2 "/home/ajit4/ajit-toolchain/build/buildroot-2014.08/output/host/usr/lib/gcc/sparc-buildroot-linux-uclibc/4.7.4/include/stdint-gcc.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.uaword	0x1a5
	.uahalf	0x2
	.uaword	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.uaword	.LASF20
	.byte	0x1
	.uaword	.LASF21
	.uaword	.Ltext0
	.uaword	.Letext0
	.uaword	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.uaword	.LASF0
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.uaword	.LASF1
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.asciz	"int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.uaword	.LASF2
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.uaword	.LASF3
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.uaword	.LASF4
	.uleb128 0x4
	.uaword	.LASF22
	.byte	0x2
	.byte	0x34
	.uaword	0x56
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.uaword	.LASF6
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF7
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.uaword	.LASF8
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF9
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.uaword	.LASF10
	.uleb128 0x5
	.byte	0x1
	.uaword	.LASF23
	.byte	0x1
	.byte	0x9
	.uaword	.LFB0
	.uaword	.LFE0
	.uaword	.LLST0
	.byte	0x1
	.uaword	0xa6
	.uleb128 0x6
	.asciz	"I"
	.byte	0x1
	.byte	0xb
	.uaword	0x2f
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x7
	.byte	0x1
	.uaword	.LASF12
	.byte	0x1
	.byte	0x10
	.byte	0x1
	.uaword	.LFB1
	.uaword	.LFE1
	.uaword	.LLST1
	.byte	0x1
	.uaword	0xdf
	.uleb128 0x8
	.uaword	.LASF11
	.byte	0x1
	.byte	0x10
	.uaword	0x4b
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x9
	.asciz	"foo"
	.byte	0x1
	.byte	0x10
	.uaword	0xf5
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.byte	0
	.uleb128 0xa
	.byte	0x1
	.uaword	0xf5
	.uleb128 0xb
	.uaword	0x4b
	.uleb128 0xb
	.uaword	0x4b
	.uleb128 0xb
	.uaword	0x4b
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.uaword	0xdf
	.uleb128 0xd
	.byte	0x1
	.uaword	.LASF13
	.byte	0x1
	.byte	0x17
	.byte	0x1
	.uaword	.LFB2
	.uaword	.LFE2
	.uaword	.LLST2
	.byte	0x1
	.uaword	0x186
	.uleb128 0x8
	.uaword	.LASF14
	.byte	0x1
	.byte	0x17
	.uaword	0x4b
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x8
	.uaword	.LASF15
	.byte	0x1
	.byte	0x17
	.uaword	0x4b
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0x8
	.uaword	.LASF16
	.byte	0x1
	.byte	0x17
	.uaword	0x4b
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0x8
	.uaword	.LASF17
	.byte	0x1
	.byte	0x17
	.uaword	0x4b
	.byte	0x3
	.byte	0x91
	.sleb128 80
	.uleb128 0x6
	.asciz	"err"
	.byte	0x1
	.byte	0x19
	.uaword	0x2f
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0xe
	.uaword	.LASF18
	.byte	0x1
	.byte	0x1a
	.uaword	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0xf
	.uaword	.LBB2
	.uaword	.LBE2
	.uleb128 0xe
	.uaword	.LASF19
	.byte	0x1
	.byte	0x1d
	.uaword	0xf5
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.byte	0
	.uleb128 0x10
	.uaword	0xf5
	.uaword	0x196
	.uleb128 0x11
	.uaword	0x72
	.byte	0xf
	.byte	0
	.uleb128 0x12
	.uaword	.LASF24
	.byte	0x1
	.byte	0x7
	.uaword	0x186
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.uaword	ajit_global_sw_trap_handlers
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.uaword	.LFB0-.Ltext0
	.uaword	.LCFI0-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI0-.Ltext0
	.uaword	.LFE0-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST1:
	.uaword	.LFB1-.Ltext0
	.uaword	.LCFI1-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI1-.Ltext0
	.uaword	.LFE1-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST2:
	.uaword	.LFB2-.Ltext0
	.uaword	.LCFI2-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI2-.Ltext0
	.uaword	.LFE2-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
	.section	.debug_aranges,"",@progbits
	.uaword	0x1c
	.uahalf	0x2
	.uaword	.Ldebug_info0
	.byte	0x4
	.byte	0
	.uahalf	0
	.uahalf	0
	.uaword	.Ltext0
	.uaword	.Letext0-.Ltext0
	.uaword	0
	.uaword	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF2:
	.asciz	"long long int"
.LASF5:
	.asciz	"unsigned int"
.LASF3:
	.asciz	"unsigned char"
.LASF20:
	.asciz	"GNU C 4.7.4"
.LASF7:
	.asciz	"long unsigned int"
.LASF6:
	.asciz	"long long unsigned int"
.LASF13:
	.asciz	"ajit_generic_sw_trap_handler"
.LASF14:
	.asciz	"tbr_value"
.LASF10:
	.asciz	"char"
.LASF22:
	.asciz	"uint32_t"
.LASF8:
	.asciz	"long int"
.LASF17:
	.asciz	"arg3"
.LASF11:
	.asciz	"sw_trap_index"
.LASF21:
	.asciz	"/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_mt_sw_traps.c"
.LASF4:
	.asciz	"short unsigned int"
.LASF0:
	.asciz	"signed char"
.LASF19:
	.asciz	"fn_ptr"
.LASF24:
	.asciz	"ajit_global_sw_trap_handlers"
.LASF9:
	.asciz	"sizetype"
.LASF15:
	.asciz	"arg1"
.LASF16:
	.asciz	"arg2"
.LASF1:
	.asciz	"short int"
.LASF23:
	.asciz	"ajit_initialize_sw_trap_handlers_to_null"
.LASF12:
	.asciz	"ajit_set_sw_trap_handler"
.LASF18:
	.asciz	"trap_index"
	.ident	"GCC: (Buildroot 2014.08-ga2bdb80-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
