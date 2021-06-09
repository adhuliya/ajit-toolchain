.section .text.ajitstart
.global _start;
_start:
	! stack..
	set 0xfff01ff8, %sp
        set 0xfff01f00, %fp

	set 0x1,%l0
	wr %l0, 0x0, %wim

	set trap_table_base,%l0
	wr %l0,0x0,%tbr

	call page_table_setup
	nop

	call set_context_table_pointer
	nop

	set 0x10E7,%l0
	wr %l0,%psr

	set 0x1,%o0
	sta %o0,[%g0] 0x4

	call main
	nop
	ta 0
