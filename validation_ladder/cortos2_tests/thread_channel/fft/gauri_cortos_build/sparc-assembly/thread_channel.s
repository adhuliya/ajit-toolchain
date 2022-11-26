	.file	"thread_channel.c"
	.section	".text"
	.align 4
	.global initChannel
	.type	initChannel, #function
	.proc	020
initChannel:
	mov	1, %g1
	st	%o1, [%o0]
	st	%g0, [%o0+4]
	st	%g0, [%o0+8]
	st	%g0, [%o0+12]
	jmp	%o7+8
	 st	%g1, [%o0+16]
	.size	initChannel, .-initChannel
	.align 4
	.global scheduleChannelJob
	.type	scheduleChannelJob, #function
	.proc	016
scheduleChannelJob:
	ld	[%o0+16], %g2
	mov	%o0, %g1
	cmp	%g2, 1
	be	.L6
	 mov	1, %o0
	jmp	%o7+8
	 nop
.L6:
	ld	[%g1+4], %g2
	add	%g2, 1, %g2
	st	%o1, [%g1+8]
	st	%g2, [%g1+4]
	st	%o2, [%g1+12]
	mov	2, %g2
	mov	0, %o0
	jmp	%o7+8
	 st	%g2, [%g1+16]
	.size	scheduleChannelJob, .-scheduleChannelJob
	.align 4
	.global setChannelResponse
	.type	setChannelResponse, #function
	.proc	016
setChannelResponse:
	ld	[%o0+16], %g2
	mov	%o0, %g1
	cmp	%g2, 3
	be	.L12
	 mov	1, %o0
	jmp	%o7+8
	 nop
.L12:
	mov	4, %g2
	st	%o1, [%g1+12]
	st	%g2, [%g1+16]
	jmp	%o7+8
	 mov	0, %o0
	.size	setChannelResponse, .-setChannelResponse
	.align 4
	.global getChannelResponse
	.type	getChannelResponse, #function
	.proc	016
getChannelResponse:
	ld	[%o0+16], %g2
	mov	%o0, %g1
	cmp	%g2, 4
	be	.L18
	 mov	1, %o0
	jmp	%o7+8
	 nop
.L18:
	ld	[%g1+12], %g2
	st	%g2, [%o1]
	st	%o0, [%g1+16]
	st	%g0, [%g1+8]
	st	%g0, [%g1+12]
	jmp	%o7+8
	 mov	0, %o0
	.size	getChannelResponse, .-getChannelResponse
	.align 4
	.global getChannelJob
	.type	getChannelJob, #function
	.proc	016
getChannelJob:
	ld	[%o0+16], %g2
	mov	%o0, %g1
	cmp	%g2, 2
	be	.L24
	 mov	1, %o0
	jmp	%o7+8
	 nop
.L24:
	ld	[%g1+8], %g2
	st	%g2, [%o1]
	ld	[%g1+12], %g2
	st	%g2, [%o2]
	mov	0, %o0
	mov	3, %g2
	jmp	%o7+8
	 st	%g2, [%g1+16]
	.size	getChannelJob, .-getChannelJob
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
