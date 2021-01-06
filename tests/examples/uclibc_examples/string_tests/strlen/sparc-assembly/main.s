	.file	"main.c"
	.section	".text"
.Ltext0:
	.cfi_sections	.debug_frame
	.common	b,4,4
	.section	".rodata"
	.align 8
.LC0:
	.asciz	"This is a test program."
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
	save	%sp, -104, %sp
.LCFI0:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 6 0
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %g1
	st	%g1, [%fp-4]
	.loc 1 8 0
	ld	[%fp-4], %o0
	call	strlen, 0
	 nop
	mov	%o0, %g1
	mov	%g1, %g2
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
	.uaword	0xb3
	.uahalf	0x2
	.uaword	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.uaword	.LASF11
	.byte	0x1
	.uaword	.LASF12
	.uaword	.LASF13
	.uaword	.Ltext0
	.uaword	.Letext0
	.uaword	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.uaword	.LASF2
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.asciz	"int"
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.uaword	.LASF3
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.uaword	.LASF4
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF5
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.uaword	.LASF6
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.uaword	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.uaword	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.uaword	.LASF9
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.uaword	.LASF10
	.uleb128 0x4
	.byte	0x4
	.uaword	0x41
	.uleb128 0x5
	.byte	0x1
	.uaword	.LASF14
	.byte	0x1
	.byte	0x5
	.uaword	.LFB0
	.uaword	.LFE0
	.uaword	.LLST0
	.byte	0x1
	.uaword	0xa6
	.uleb128 0x6
	.asciz	"s1"
	.byte	0x1
	.byte	0x6
	.uaword	0x79
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x7
	.asciz	"b"
	.byte	0x1
	.byte	0x4
	.uaword	0x3a
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
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
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
	.uleb128 0x2116
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
.LASF8:
	.asciz	"long long int"
.LASF0:
	.asciz	"unsigned int"
.LASF12:
	.asciz	"main.c"
.LASF11:
	.asciz	"GNU C 4.7.4"
.LASF5:
	.asciz	"long unsigned int"
.LASF9:
	.asciz	"long long unsigned int"
.LASF13:
	.asciz	"/home/anshuman/glibc_tests/string_tests/strlen"
.LASF3:
	.asciz	"char"
.LASF4:
	.asciz	"unsigned char"
.LASF14:
	.asciz	"main"
.LASF10:
	.asciz	"long int"
.LASF2:
	.asciz	"short unsigned int"
.LASF6:
	.asciz	"signed char"
.LASF7:
	.asciz	"short int"
.LASF1:
	.asciz	"sizetype"
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
