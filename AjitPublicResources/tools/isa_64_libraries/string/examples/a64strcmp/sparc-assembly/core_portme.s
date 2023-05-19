	.file	"core_portme.c"
	.section	".text"
.Ltext0:
	.cfi_sections	.debug_frame
	.align 4
	.global ajit_serial_init
	.type	ajit_serial_init, #function
	.proc	020
ajit_serial_init:
.LFB0:
	.file 1 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/minimal_printf_timer/src/core_portme.c"
	.loc 1 6 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI0:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 7 0
	mov	1, %o0
	mov	0, %o1
	mov	0, %o2
	call	__ajit_serial_configure_via_bypass__, 0
	 nop
	.loc 1 8 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE0:
	.size	ajit_serial_init, .-ajit_serial_init
	.align 4
	.global ajit_barebones_clock
	.type	ajit_barebones_clock, #function
	.proc	016
ajit_barebones_clock:
.LFB1:
	.loc 1 10 0
	.cfi_startproc
	save	%sp, -112, %sp
.LCFI1:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 11 0
	call	__ajit_read_cycle_count_register_high__, 0
	 nop
	st	%o0, [%fp-4]
	.loc 1 12 0
	call	__ajit_read_cycle_count_register_low__, 0
	 nop
	st	%o0, [%fp-8]
	.loc 1 15 0
	ld	[%fp-4], %g1
	sll	%g1, 24, %g2
	ld	[%fp-8], %g1
	srl	%g1, 8, %g1
	or	%g2, %g1, %g1
	st	%g1, [%fp-12]
	.loc 1 17 0
	ld	[%fp-12], %g1
	.loc 1 18 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE1:
	.size	ajit_barebones_clock, .-ajit_barebones_clock
.Letext0:
	.file 2 "/home/ajit4/ajit-toolchain/build/buildroot-2014.08/output/host/usr/lib/gcc/sparc-buildroot-linux-uclibc/4.7.4/include/stdint-gcc.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.uaword	0xba
	.uahalf	0x2
	.uaword	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.uaword	.LASF10
	.byte	0x1
	.uaword	.LASF11
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
	.uaword	.LASF12
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
	.uleb128 0x5
	.byte	0x1
	.uaword	.LASF13
	.byte	0x1
	.byte	0x5
	.uaword	.LFB0
	.uaword	.LFE0
	.uaword	.LLST0
	.byte	0x1
	.uleb128 0x6
	.byte	0x1
	.uaword	.LASF14
	.byte	0x1
	.byte	0xa
	.uaword	0x4b
	.uaword	.LFB1
	.uaword	.LFE1
	.uaword	.LLST1
	.byte	0x1
	.uleb128 0x7
	.uaword	.LASF7
	.byte	0x1
	.byte	0xb
	.uaword	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0x7
	.uaword	.LASF8
	.byte	0x1
	.byte	0xc
	.uaword	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0x7
	.uaword	.LASF9
	.byte	0x1
	.byte	0xf
	.uaword	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
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
	.byte	0
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
	.uleb128 0x2116
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x6
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x7
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
.LASF3:
	.asciz	"unsigned char"
.LASF4:
	.asciz	"short unsigned int"
.LASF9:
	.asciz	"rval"
.LASF7:
	.asciz	"tick_h"
.LASF8:
	.asciz	"tick_l"
.LASF5:
	.asciz	"unsigned int"
.LASF14:
	.asciz	"ajit_barebones_clock"
.LASF6:
	.asciz	"long long unsigned int"
.LASF13:
	.asciz	"ajit_serial_init"
.LASF2:
	.asciz	"long long int"
.LASF10:
	.asciz	"GNU C 4.7.4"
.LASF1:
	.asciz	"short int"
.LASF12:
	.asciz	"uint32_t"
.LASF0:
	.asciz	"signed char"
.LASF11:
	.asciz	"/home/ajit4/ajit-toolchain/AjitPublicResources/tools/minimal_printf_timer/src/core_portme.c"
	.ident	"GCC: (Buildroot 2014.08-ga2bdb80-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
