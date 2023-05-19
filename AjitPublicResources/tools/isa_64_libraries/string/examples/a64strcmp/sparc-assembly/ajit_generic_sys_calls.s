	.file	"ajit_generic_sys_calls.c"
	.section	".text"
.Ltext0:
	.cfi_sections	.debug_frame
	.align 4
	.global ajit_sys_get_core_and_thread_id
	.type	ajit_sys_get_core_and_thread_id, #function
	.proc	020
ajit_sys_get_core_and_thread_id:
.LFB0:
	.file 1 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_generic_sys_calls.c"
	.loc 1 11 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI0:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	.loc 1 13 0
	mov	29, %o0
	call	ajit_sys_read_asr, 0
	 nop
	st	%o0, [%fp-4]
	.loc 1 15 0
	ld	[%fp-4], %g1
	srl	%g1, 8, %g1
	mov	%g1, %g2
	ld	[%fp+68], %g1
	stb	%g2, [%g1]
	.loc 1 16 0
	ld	[%fp-4], %g1
	mov	%g1, %g2
	ld	[%fp+72], %g1
	stb	%g2, [%g1]
	.loc 1 17 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE0:
	.size	ajit_sys_get_core_and_thread_id, .-ajit_sys_get_core_and_thread_id
	.align 4
	.global ajit_sys_get_clock_time
	.type	ajit_sys_get_clock_time, #function
	.proc	017
ajit_sys_get_clock_time:
.LFB1:
	.loc 1 20 0
	.cfi_startproc
	save	%sp, -112, %sp
.LCFI1:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 21 0
	mov	30, %o0
	call	ajit_sys_read_asr, 0
	 nop
	st	%o0, [%fp-4]
	.loc 1 22 0
	mov	31, %o0
	call	ajit_sys_read_asr, 0
	 nop
	st	%o0, [%fp-8]
	.loc 1 23 0
	ld	[%fp-8], %g1
	mov	0, %g2
	mov	%g1, %g3
	std	%g2, [%fp-16]
	.loc 1 24 0
	ld	[%fp-12], %g1
	sll	%g1, 0, %g1
	st	%g1, [%fp-16]
	st	%g0, [%fp-12]
	.loc 1 25 0
	ld	[%fp-4], %g1
	mov	0, %g2
	mov	%g1, %g3
	ldd	[%fp-16], %i4
	or	%i4, %g2, %g2
	or	%i5, %g3, %g3
	std	%g2, [%fp-16]
	.loc 1 26 0
	ldd	[%fp-16], %g2
	.loc 1 27 0
	mov	%g2, %i0
	mov	%g3, %i1
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE1:
	.size	ajit_sys_get_clock_time, .-ajit_sys_get_clock_time
	.align 4
	.global ajit_sys_sleep
	.type	ajit_sys_sleep, #function
	.proc	020
ajit_sys_sleep:
.LFB2:
	.loc 1 30 0
	.cfi_startproc
	save	%sp, -112, %sp
.LCFI2:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	.loc 1 31 0
	call	ajit_sys_get_clock_time, 0
	 nop
	std	%o0, [%fp-8]
	.loc 1 32 0
	ld	[%fp+68], %g1
	mov	0, %i2
	mov	%g1, %i3
	ldd	[%fp-8], %i4
	addcc	%i3, %i5, %g3
	addx	%i2, %i4, %g2
	std	%g2, [%fp-16]
	.loc 1 34 0
	b	.L5
	 nop
.L6:
	.loc 1 36 0
	call	ajit_sys_get_clock_time, 0
	 nop
	std	%o0, [%fp-8]
.L5:
	.loc 1 34 0 discriminator 1
	ld	[%fp-16], %g2
	ld	[%fp-8], %g1
	cmp	%g2, %g1
	bgu	.L6
	 nop
	ld	[%fp-16], %g2
	ld	[%fp-8], %g1
	cmp	%g2, %g1
	bne	.L9
	 nop
	ld	[%fp-12], %g2
	ld	[%fp-4], %g1
	cmp	%g2, %g1
	bgu	.L6
	 nop
.L9:
	.loc 1 38 0
	nop
.L4:
	.loc 1 39 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE2:
	.size	ajit_sys_sleep, .-ajit_sys_sleep
.Letext0:
	.file 2 "/home/ajit4/ajit-toolchain/build/buildroot-2014.08/output/host/usr/lib/gcc/sparc-buildroot-linux-uclibc/4.7.4/include/stdint-gcc.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.uaword	0x16a
	.uahalf	0x2
	.uaword	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.uaword	.LASF23
	.byte	0x1
	.uaword	.LASF24
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
	.uleb128 0x4
	.uaword	.LASF5
	.byte	0x2
	.byte	0x2e
	.uaword	0x48
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.uaword	.LASF3
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.uaword	.LASF4
	.uleb128 0x4
	.uaword	.LASF6
	.byte	0x2
	.byte	0x34
	.uaword	0x61
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF7
	.uleb128 0x4
	.uaword	.LASF8
	.byte	0x2
	.byte	0x37
	.uaword	0x73
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.uaword	.LASF9
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF10
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.uaword	.LASF11
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF12
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.uaword	.LASF13
	.uleb128 0x5
	.byte	0x1
	.uaword	.LASF16
	.byte	0x1
	.byte	0xa
	.byte	0x1
	.uaword	.LFB0
	.uaword	.LFE0
	.uaword	.LLST0
	.byte	0x1
	.uaword	0xdd
	.uleb128 0x6
	.uaword	.LASF14
	.byte	0x1
	.byte	0xa
	.uaword	0xdd
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x6
	.uaword	.LASF15
	.byte	0x1
	.byte	0xa
	.uaword	0xdd
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0x7
	.uaword	.LASF18
	.byte	0x1
	.byte	0xd
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.uaword	0x3d
	.uleb128 0x9
	.byte	0x1
	.uaword	.LASF17
	.byte	0x1
	.byte	0x13
	.uaword	0x68
	.uaword	.LFB1
	.uaword	.LFE1
	.uaword	.LLST1
	.byte	0x1
	.uaword	0x12b
	.uleb128 0xa
	.asciz	"v_l"
	.byte	0x1
	.byte	0x15
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0xa
	.asciz	"v_h"
	.byte	0x1
	.byte	0x16
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0x7
	.uaword	.LASF19
	.byte	0x1
	.byte	0x17
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0xb
	.byte	0x1
	.uaword	.LASF25
	.byte	0x1
	.byte	0x1d
	.byte	0x1
	.uaword	.LFB2
	.uaword	.LFE2
	.uaword	.LLST2
	.byte	0x1
	.uleb128 0x6
	.uaword	.LASF20
	.byte	0x1
	.byte	0x1d
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x7
	.uaword	.LASF21
	.byte	0x1
	.byte	0x1f
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0x7
	.uaword	.LASF22
	.byte	0x1
	.byte	0x20
	.uaword	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -16
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
	.uleb128 0x6
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
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0xb
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
.LASF7:
	.asciz	"unsigned int"
.LASF21:
	.asciz	"curr_time"
.LASF17:
	.asciz	"ajit_sys_get_clock_time"
.LASF24:
	.asciz	"/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_generic_sys_calls.c"
.LASF23:
	.asciz	"GNU C 4.7.4"
.LASF10:
	.asciz	"long unsigned int"
.LASF9:
	.asciz	"long long unsigned int"
.LASF8:
	.asciz	"uint64_t"
.LASF5:
	.asciz	"uint8_t"
.LASF3:
	.asciz	"unsigned char"
.LASF13:
	.asciz	"char"
.LASF6:
	.asciz	"uint32_t"
.LASF11:
	.asciz	"long int"
.LASF19:
	.asciz	"ret_val"
.LASF18:
	.asciz	"rval"
.LASF4:
	.asciz	"short unsigned int"
.LASF0:
	.asciz	"signed char"
.LASF25:
	.asciz	"ajit_sys_sleep"
.LASF16:
	.asciz	"ajit_sys_get_core_and_thread_id"
.LASF14:
	.asciz	"core_id"
.LASF20:
	.asciz	"clock_cycles"
.LASF1:
	.asciz	"short int"
.LASF22:
	.asciz	"end_time"
.LASF15:
	.asciz	"thread_id"
.LASF12:
	.asciz	"sizetype"
	.ident	"GCC: (Buildroot 2014.08-ga2bdb80-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
