	.file	"main.c"
	.section	".text"
.Ltext0:
	.cfi_sections	.debug_frame
	.common	b,4,4
	.section	".rodata"
	.align 8
.LC0:
	.long	1075838976
	.long	0
	.align 8
.LC1:
	.long	1079574528
	.long	0
	.section	".text"
	.align 4
	.global main
	.type	main, #function
	.proc	020
main:
.LFB0:
	.file 1 "main.c"
	.loc 1 5 0
	.cfi_startproc
	save	%sp, -112, %sp
.LCFI0:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 7 0
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %g1
	ldd	[%g1], %f8
	std	%f8, [%fp-8]
	ldd	[%fp-8], %o0
	call	asinh, 0
	 nop
	fmovs	%f0, %f10
	fmovs	%f1, %f11
	sethi	%hi(.LC1), %g1
	or	%g1, %lo(.LC1), %g1
	ldd	[%g1], %f8
	fmuld	%f10, %f8, %f8
	fdtoi	%f8, %f10
	st	%f10, [%fp-12]
	ld	[%fp-12], %g2
	sethi	%hi(b), %g1
	or	%g1, %lo(b), %g1
	st	%g2, [%g1]
	.loc 1 9 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE0:
	.size	main, .-main
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.uaword	0xa9
	.uahalf	0x2
	.uaword	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.uaword	.LASF13
	.byte	0x1
	.uaword	.LASF14
	.uaword	.LASF15
	.uaword	.Ltext0
	.uaword	.Letext0
	.uaword	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.uaword	.LASF0
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.uaword	.LASF1
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.asciz	"int"
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.uaword	.LASF2
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF3
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.uaword	.LASF4
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.uaword	.LASF5
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF6
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.uaword	.LASF7
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.uaword	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.uaword	.LASF9
	.uleb128 0x2
	.byte	0x8
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
	.uleb128 0x4
	.byte	0x1
	.uaword	.LASF16
	.byte	0x1
	.byte	0x5
	.uaword	.LFB0
	.uaword	.LFE0
	.uaword	.LLST0
	.byte	0x1
	.uleb128 0x5
	.asciz	"b"
	.byte	0x1
	.byte	0x4
	.uaword	0x33
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.uaword	b
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
	.uleb128 0x1b
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
	.uleb128 0x5
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
.LASF9:
	.asciz	"long long int"
.LASF3:
	.asciz	"unsigned int"
.LASF14:
	.asciz	"main.c"
.LASF13:
	.asciz	"GNU C 4.7.4"
.LASF6:
	.asciz	"long unsigned int"
.LASF10:
	.asciz	"long long unsigned int"
.LASF2:
	.asciz	"char"
.LASF15:
	.asciz	"/home/anshuman/glibc_tests/asinh"
.LASF4:
	.asciz	"unsigned char"
.LASF16:
	.asciz	"main"
.LASF11:
	.asciz	"long int"
.LASF1:
	.asciz	"double"
.LASF5:
	.asciz	"short unsigned int"
.LASF7:
	.asciz	"signed char"
.LASF0:
	.asciz	"float"
.LASF8:
	.asciz	"short int"
.LASF12:
	.asciz	"sizetype"
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
