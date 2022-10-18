	.file	"score_board.c"
	.section	".text"
	.align 4
	.global initChannel
	.type	initChannel, #function
	.proc	020
initChannel:
	mov	1, %g1
	st	%g0, [%o0+4]
	st	%g0, [%o0+76]
	jmp	%o7+8
	 st	%g1, [%o0+148]
	.size	initChannel, .-initChannel
	.align 4
	.global checkChannelStatus
	.type	checkChannelStatus, #function
	.proc	016
checkChannelStatus:
	ld	[%o0+4], %g1
	subcc	%g0, %g1, %g0
	subx	%g0, -1, %g1
	st	%g1, [%o1]
	ld	[%o0+4], %g1
	cmp	%g1, 0
	be	.L3
	 mov	0, %g2
	ld	[%o0+76], %g2
	xor	%g1, %g2, %g1
	subcc	%g0, %g1, %g0
	subx	%g0, -1, %g2
.L3:
	st	%g2, [%o2]
	ld	[%o0+4], %g2
	cmp	%g2, 0
	be	.L4
	 mov	0, %g1
	ld	[%o0+76], %g1
	xor	%g2, %g1, %g2
	subcc	%g0, %g2, %g0
	addx	%g0, 0, %g1
.L4:
	jmp	%o7+8
	 st	%g1, [%o3]
	.size	checkChannelStatus, .-checkChannelStatus
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.asciz	"DEBUG"
	.align 8
.LC1:
	.asciz	"../score_board.c"
	.align 8
.LC2:
	.asciz	"waitOnChannelResponse: returned... response_id=%d.\n"
	.align 8
.LC3:
	.asciz	" 0x%x "
	.section	".text"
	.align 4
	.global responseReadyInChannel
	.type	responseReadyInChannel, #function
	.proc	016
responseReadyInChannel:
	save	%sp, -96, %sp
	ld	[%i1+4], %g1
	cmp	%i0, %g1
	be	.L15
	 mov	%i0, %g2
	ld	[%i1+76], %g3
	cmp	%g1, %g3
	be	.L19
	 mov	0, %i0
	jmp	%i7+8
	 restore
.L19:
	st	%g1, [%g2]
	sethi	%hi(.LC0), %l0
	sethi	%hi(.LC1), %i0
	or	%l0, %lo(.LC0), %o0
	or	%i0, %lo(.LC1), %o1
	sethi	%hi(__func__.2585), %i2
	mov	37, %o3
	or	%i2, %lo(__func__.2585), %o2
	ld	[%i1+76], %o5
	sethi	%hi(.LC2), %o4
	call	__cortos_log_printf, 0
	 or	%o4, %lo(.LC2), %o4
	ld	[%i1+80], %g1
	mov	%i1, %i5
	cmp	%g1, 0
	be	.L14
	 mov	0, %i4
	sethi	%hi(.LC3), %i3
	or	%l0, %lo(.LC0), %l0
	or	%i0, %lo(.LC1), %i0
	or	%i2, %lo(__func__.2585), %i2
	or	%i3, %lo(.LC3), %i3
.L17:
	ld	[%i5+84], %o5
	mov	%l0, %o0
	mov	%i0, %o1
	mov	%i2, %o2
	mov	40, %o3
	call	__cortos_log_printf, 0
	 mov	%i3, %o4
	add	%i4, 1, %i4
	ld	[%i1+80], %g1
	cmp	%i4, %g1
	blu	.L17
	 add	%i5, 4, %i5
.L14:
	jmp	%i7+8
	 restore %g0, 1, %o0
.L15:
	jmp	%i7+8
	 restore %g0, 0, %o0
	.size	responseReadyInChannel, .-responseReadyInChannel
	.align 4
	.global registerResponseToChannel
	.type	registerResponseToChannel, #function
	.proc	020
registerResponseToChannel:
	ld	[%o0+76], %g1
	addcc	%g1, 1, %g1
	be,a	.L23
	 mov	1, %g1
.L23:
	jmp	%o7+8
	 st	%g1, [%o0+76]
	.size	registerResponseToChannel, .-registerResponseToChannel
	.align 4
	.global registerRequestToChannel
	.type	registerRequestToChannel, #function
	.proc	020
registerRequestToChannel:
	ld	[%o0+4], %g1
	addcc	%g1, 1, %g1
	be,a	.L26
	 mov	1, %g1
.L26:
	jmp	%o7+8
	 st	%g1, [%o0+4]
	.size	registerRequestToChannel, .-registerRequestToChannel
	.align 4
	.global isChannelFree
	.type	isChannelFree, #function
	.proc	016
isChannelFree:
	ld	[%o0+4], %g1
	cmp	%g1, 0
	bne,a	.L35
	 ld	[%o0+76], %g2
	subcc	%g0, %g1, %g0
.L36:
	jmp	%o7+8
	 subx	%g0, -1, %o0
.L35:
	cmp	%g1, %g2
	bne	.L36
	 subcc	%g0, %g1, %g0
	jmp	%o7+8
	 mov	1, %o0
	.size	isChannelFree, .-isChannelFree
	.align 4
	.global channelHasPendingJob
	.type	channelHasPendingJob, #function
	.proc	016
channelHasPendingJob:
	ld	[%o0+4], %g2
	cmp	%g2, 0
	be	.L38
	 mov	0, %g1
	ld	[%o0+76], %g1
	xor	%g2, %g1, %g2
	subcc	%g0, %g2, %g0
	addx	%g0, 0, %g1
.L38:
	jmp	%o7+8
	 mov	%g1, %o0
	.size	channelHasPendingJob, .-channelHasPendingJob
	.align 4
	.global initScoreboard
	.type	initScoreboard, #function
	.proc	020
initScoreboard:
	add	%o0, 12, %o0
	mov	256, %g1
.L42:
	st	%g0, [%o0]
	st	%g0, [%o0+72]
	addcc	%g1, -1, %g1
	bne	.L42
	 add	%o0, 152, %o0
	jmp	%o7+8
	 nop
	.size	initScoreboard, .-initScoreboard
	.align 4
	.global channelId
	.type	channelId, #function
	.proc	016
channelId:
	ld	[%o0+4], %g1
	ld	[%o0], %g2
	smul	%o1, %g1, %o1
	add	%o2, %o1, %o2
	smul	%o2, %g2, %g2
	add	%g2, %o3, %o3
	smul	%o3, %g1, %o0
	jmp	%o7+8
	 add	%o0, %o4, %o0
	.size	channelId, .-channelId
	.align 4
	.global checkScoreboardSlotStatus
	.type	checkScoreboardSlotStatus, #function
	.proc	016
checkScoreboardSlotStatus:
	ld	[%o0+4], %g1
	ld	[%o0], %g2
	smul	%o1, %g1, %o1
	add	%o1, %o2, %o2
	smul	%o2, %g2, %g2
	add	%g2, %o3, %o3
	smul	%o3, %g1, %g1
	add	%g1, %o4, %o4
	smul	%o4, 152, %g1
	add	%g1, 8, %g1
	add	%o0, %g1, %o0
	ld	[%o0+4], %g1
	subcc	%g0, %g1, %g0
	subx	%g0, -1, %g1
	st	%g1, [%o5]
	ld	[%o0+4], %g2
	cmp	%g2, 0
	be	.L46
	 mov	0, %g1
	ld	[%o0+76], %g1
	xor	%g2, %g1, %g2
	subcc	%g0, %g2, %g0
	subx	%g0, -1, %g1
.L46:
	ld	[%sp+92], %g2
	st	%g1, [%g2]
	ld	[%o0+4], %g2
	cmp	%g2, 0
	be	.L47
	 mov	0, %g1
	ld	[%o0+76], %g1
	xor	%g2, %g1, %g2
	subcc	%g0, %g2, %g0
	addx	%g0, 0, %g1
.L47:
	ld	[%sp+96], %g2
	mov	0, %o0
	jmp	%o7+8
	 st	%g1, [%g2]
	.size	checkScoreboardSlotStatus, .-checkScoreboardSlotStatus
	.align 4
	.global isScoreboardSlotFree
	.type	isScoreboardSlotFree, #function
	.proc	016
isScoreboardSlotFree:
	ld	[%o0+4], %g1
	ld	[%o0], %g2
	smul	%o1, %g1, %o1
	add	%o1, %o2, %o2
	smul	%o2, %g2, %g2
	add	%g2, %o3, %o3
	smul	%o3, %g1, %g1
	add	%g1, %o4, %o4
	smul	%o4, 152, %g1
	add	%g1, 8, %g1
	add	%o0, %g1, %o0
	ld	[%o0+4], %g1
	cmp	%g1, 0
	bne,a	.L59
	 ld	[%o0+76], %g2
	subcc	%g0, %g1, %g0
.L60:
	jmp	%o7+8
	 subx	%g0, -1, %o0
.L59:
	cmp	%g1, %g2
	bne	.L60
	 subcc	%g0, %g1, %g0
	jmp	%o7+8
	 mov	1, %o0
	.size	isScoreboardSlotFree, .-isScoreboardSlotFree
	.align 4
	.global jobPendingInScoreboardSlot
	.type	jobPendingInScoreboardSlot, #function
	.proc	016
jobPendingInScoreboardSlot:
	mov	%o0, %g1
	ld	[%g1+4], %g2
	ld	[%g1], %g3
	smul	%o1, %g2, %o1
	add	%o1, %o2, %o2
	smul	%o2, %g3, %g3
	add	%g3, %o3, %o3
	smul	%o3, %g2, %g2
	add	%g2, %o4, %o4
	smul	%o4, 152, %g2
	add	%g2, 8, %g2
	add	%g1, %g2, %g1
	ld	[%g1+4], %g2
	cmp	%g2, 0
	be	.L65
	 mov	0, %o0
	ld	[%g1+76], %g1
	xor	%g2, %g1, %g2
	subcc	%g0, %g2, %g0
	addx	%g0, 0, %o0
.L65:
	jmp	%o7+8
	 nop
	.size	jobPendingInScoreboardSlot, .-jobPendingInScoreboardSlot
	.align 4
	.global selectScoreboardWorker
	.type	selectScoreboardWorker, #function
	.proc	016
selectScoreboardWorker:
	save	%sp, -96, %sp
	st	%i4, [%fp+84]
	ld	[%i0+4], %l5
	cmp	%l5, 0
	be	.L75
	 mov	%i0, %l1
	add	%l5, 1, %l7
	add	%i2, 1, %l3
	add	%l5, -1, %l6
	add	%l7, %i2, %l7
	cmp	%i3, 0
.L82:
	bne	.L68
	 and	%l6, %l3, %l0
	ld	[%l1], %l4
	cmp	%l4, 0
	be	.L70
	 add	%l4, 1, %l2
	add	%i1, 1, %i5
	add	%l4, -1, %i0
	b	.L73
	 add	%l2, %i1, %l2
.L80:
	cmp	%i5, %l2
	be,a	.L81
	 add	%l3, 1, %l3
.L73:
	and	%i5, %i0, %i4
	mov	%l1, %o0
	mov	%i1, %o1
	mov	%i2, %o2
	mov	%i4, %o3
	call	isScoreboardSlotFree, 0
	 mov	%l0, %o4
	cmp	%o0, 0
	be,a	.L80
	 add	%i5, 1, %i5
	smul	%i1, %l5, %i1
	mov	%i4, %g1
	add	%i1, %i2, %i2
	smul	%l4, %i2, %l4
	add	%l4, %g1, %g1
	smul	%g1, %l5, %l5
	ld	[%fp+84], %g1
	add	%l5, %l0, %l0
	smul	%l0, 152, %l0
	add	%l0, 8, %l0
	add	%l1, %l0, %l1
	st	%l1, [%g1]
	jmp	%i7+8
	 restore %g0, 0, %o0
.L70:
	add	%l3, 1, %l3
.L81:
	cmp	%l3, %l7
	bne	.L82
	 cmp	%i3, 0
.L75:
	jmp	%i7+8
	 restore %g0, 1, %o0
.L68:
	mov	%l1, %o0
	mov	%i1, %o1
	mov	%i2, %o2
	mov	%i1, %o3
	call	isScoreboardSlotFree, 0
	 mov	%l0, %o4
	cmp	%o0, 0
	be,a	.L81
	 add	%l3, 1, %l3
	ld	[%l1], %l4
	mov	%i1, %g1
	smul	%i1, %l5, %i1
	add	%i1, %i2, %i2
	smul	%l4, %i2, %l4
	add	%l4, %g1, %g1
	smul	%g1, %l5, %l5
	ld	[%fp+84], %g1
	add	%l5, %l0, %l0
	smul	%l0, 152, %l0
	add	%l0, 8, %l0
	add	%l1, %l0, %l1
	st	%l1, [%g1]
	jmp	%i7+8
	 restore %g0, 0, %o0
	.size	selectScoreboardWorker, .-selectScoreboardWorker
	.align 4
	.global selectScoreboardJob
	.type	selectScoreboardJob, #function
	.proc	016
selectScoreboardJob:
	save	%sp, -96, %sp
	st	%g0, [%i3]
	ld	[%i0], %o5
	cmp	%o5, 0
	be	.L90
	 mov	0, %o7
	ld	[%i0+4], %i5
	smul	%i5, %i5, %o4
	smul	%i1, %i5, %i1
	smul	%o4, %o5, %o4
	add	%i1, %i2, %i1
	smul	%o5, %i5, %i2
.L85:
	mov	%i1, %g1
	cmp	%i5, 0
	be	.L88
	 mov	0, %g4
.L94:
	smul	%g1, 152, %g2
	add	%g2, 8, %g2
	add	%i0, %g2, %g2
	ld	[%g2+4], %g3
	cmp	%g3, 0
	be,a	.L98
	 add	%g4, 1, %g4
	ld	[%g2+76], %i4
	cmp	%g3, %i4
	be,a	.L86
	 add	%g4, 1, %g4
	st	%g2, [%i3]
	jmp	%i7+8
	 restore %g0, 0, %o0
.L86:
.L98:
	cmp	%g4, %i5
	bne	.L94
	 add	%g1, %i2, %g1
.L88:
	add	%o7, 1, %o7
	cmp	%o7, %o5
	bne	.L85
	 add	%i1, %o4, %i1
.L90:
	jmp	%i7+8
	 restore %g0, 1, %o0
	.size	selectScoreboardJob, .-selectScoreboardJob
	.section	.rodata.str1.8
	.align 8
.LC4:
	.asciz	"sidekickServer: registered response %d.\n"
	.align 8
.LC5:
	.asciz	"sidekickServer: job limit %d reached.\n"
	.align 8
.LC6:
	.asciz	"sidekickServer: found job %d.\n"
	.section	".text"
	.align 4
	.global sidekickServer
	.type	sidekickServer, #function
	.proc	020
sidekickServer:
	save	%sp, -104, %sp
	sethi	%hi(.LC1), %i1
	mov	%i0, %i5
	sethi	%hi(__func__.2708), %i2
	sethi	%hi(.LC0), %i0
	subcc	%g0, %i5, %g0
	sethi	%hi(.LC6), %l2
	addx	%g0, 0, %g1
	sethi	%hi(.LC4), %l6
	mov	0, %l7
	st	%g1, [%fp-4]
	or	%i0, %lo(.LC0), %l1
	or	%i1, %lo(.LC1), %l0
	or	%i2, %lo(__func__.2708), %i4
	or	%l2, %lo(.LC6), %l2
	add	%i3, 16, %l5
	add	%i3, 80, %l4
	add	%i3, 84, %l3
	or	%l6, %lo(.LC4), %l6
	ld	[%i3+4], %g1
.L119:
	cmp	%g1, 0
	be	.L118
	 cmp	%l7, %i5
	ld	[%i3+76], %g3
	mov	%l2, %o4
	mov	%g1, %o5
	mov	%l0, %o1
	mov	%i4, %o2
	mov	%l1, %o0
	cmp	%g1, %g3
	be	.L100
	 mov	226, %o3
	call	__cortos_log_printf, 0
	 nop
	ld	[%i3+8], %o0
	mov	%l5, %o1
	mov	%l4, %o2
	add	%o0, -1, %o0
	ld	[%i3+12], %g1
	call	%g1, 0
	 mov	%l3, %o3
	ld	[%i3+76], %o5
	addcc	%o5, 1, %o5
	be,a	.L103
	 mov	1, %o5
.L103:
	st	%o5, [%i3+76]
	mov	%l1, %o0
	mov	%l0, %o1
	mov	%i4, %o2
	mov	234, %o3
	mov	%l6, %o4
	call	__cortos_log_printf, 0
	 add	%l7, 1, %l7
.L100:
	cmp	%l7, %i5
.L118:
	bne,a	.L119
	 ld	[%i3+4], %g1
	ld	[%fp-4], %g1
	cmp	%g1, 0
	be,a	.L119
	 ld	[%i3+4], %g1
	sethi	%hi(.LC5), %i4
	or	%i0, %lo(.LC0), %i0
	or	%i1, %lo(.LC1), %i1
	or	%i2, %lo(__func__.2708), %i2
	mov	240, %i3
	call	__cortos_log_printf, 0
	 restore %i4, %lo(.LC5), %o4
	.size	sidekickServer, .-sidekickServer
	.section	.rodata.str1.8
	.align 8
.LC7:
	.asciz	"sidekickScheduler: job limit %d reached.\n"
	.section	".text"
	.align 4
	.global scoreboardServer
	.type	scoreboardServer, #function
	.proc	020
scoreboardServer:
	save	%sp, -104, %sp
	mov	0, %i5
	subcc	%g0, %i0, %g0
	b	.L134
	 addx	%g0, 0, %i4
.L121:
	be	.L136
	 cmp	%i4, 0
.L134:
	mov	%i1, %o1
.L137:
	mov	%i2, %o2
	add	%fp, -4, %o3
	call	selectScoreboardJob, 0
	 mov	%i3, %o0
	cmp	%o0, 0
	bne	.L121
	 cmp	%i5, %i0
	ld	[%fp-4], %o3
	ld	[%o3+12], %g1
	ld	[%o3+8], %o0
	add	%o3, 12, %o1
	add	%o3, 80, %o2
	call	%g1, 0
	 add	%o3, 84, %o3
	ld	[%fp-4], %g1
	ld	[%g1+76], %g2
	addcc	%g2, 1, %g2
	be,a	.L122
	 mov	1, %g2
.L122:
	add	%i5, 1, %i5
	cmp	%i5, %i0
	bne	.L134
	 st	%g2, [%g1+76]
	cmp	%i4, 0
.L136:
	be	.L137
	 mov	%i1, %o1
	sethi	%hi(.LC0), %o0
	sethi	%hi(.LC1), %o1
	sethi	%hi(__func__.2727), %o2
	or	%o1, %lo(.LC1), %o1
	or	%o2, %lo(__func__.2727), %o2
	mov	265, %o3
	sethi	%hi(.LC7), %o4
	mov	%i0, %o5
	or	%o4, %lo(.LC7), %o4
	call	__cortos_log_printf, 0
	 or	%o0, %lo(.LC0), %o0
	jmp	%i7+8
	 restore
	.size	scoreboardServer, .-scoreboardServer
	.section	.rodata.str1.8
	.align 8
.LC8:
	.asciz	"ERROR"
	.align 8
.LC9:
	.asciz	"scheduleChannelJob:  only CALL_FUNCTION (job_type = 1) jobs supported.\n"
	.section	".text"
	.align 4
	.global scheduleChannelJob
	.type	scheduleChannelJob, #function
	.proc	016
scheduleChannelJob:
	save	%sp, -96, %sp
	cmp	%i0, 1
	be	.L148
	 mov	294, %o3
	sethi	%hi(.LC8), %o0
	sethi	%hi(.LC1), %o1
	or	%o0, %lo(.LC8), %o0
	or	%o1, %lo(.LC1), %o1
	sethi	%hi(__func__.2742), %o2
	sethi	%hi(.LC9), %o4
	or	%o2, %lo(__func__.2742), %o2
	or	%o4, %lo(.LC9), %o4
	call	__cortos_log_printf, 0
	 mov	1, %i0
	jmp	%i7+8
	 restore
.L148:
	add	%i2, 1, %g1
	st	%i0, [%i4]
	st	%g1, [%i4+8]
	st	%i1, [%i4+12]
	mov	%i4, %g2
	mov	0, %g3
	cmp	%i2, 0
	be	.L143
	 mov	0, %g1
.L146:
	sll	%g3, 2, %g3
	ld	[%i3+%g3], %g3
	st	%g3, [%g2+16]
	add	%g1, 1, %g1
	add	%g2, 4, %g2
	cmp	%g1, %i2
	bne	.L146
	 mov	%g1, %g3
.L143:
	ld	[%i4+4], %g1
	addcc	%g1, 1, %g1
	be,a	.L141
	 mov	1, %g1
.L141:
	st	%g1, [%i4+4]
	jmp	%i7+8
	 restore %g0, 0, %o0
	.size	scheduleChannelJob, .-scheduleChannelJob
	.section	.rodata.str1.8
	.align 8
.LC10:
	.asciz	"scheduleScoreboardJob:  only CALL_FUNCTION (job_type = 1) jobs supported.\n"
	.section	".text"
	.align 4
	.global scheduleScoreboardJob
	.type	scheduleScoreboardJob, #function
	.proc	016
scheduleScoreboardJob:
	save	%sp, -104, %sp
	mov	0, %o3
	mov	%i0, %o1
	st	%g0, [%fp-4]
	ld	[%fp+92], %o0
	mov	%i1, %o2
	add	%fp, -4, %o4
	call	selectScoreboardWorker, 0
	 mov	1, %i0
	cmp	%o0, 0
	bne	.L161
	 cmp	%i2, 1
	be	.L160
	 sethi	%hi(.LC8), %o0
	sethi	%hi(.LC1), %o1
	sethi	%hi(__func__.2758), %o2
	sethi	%hi(.LC10), %o4
	or	%o0, %lo(.LC8), %o0
	or	%o1, %lo(.LC1), %o1
	or	%o2, %lo(__func__.2758), %o2
	mov	327, %o3
	call	__cortos_log_printf, 0
	 or	%o4, %lo(.LC10), %o4
.L161:
	jmp	%i7+8
	 restore
.L160:
	ld	[%fp-4], %g4
	add	%i4, 1, %g1
	st	%i2, [%g4]
	st	%g1, [%g4+8]
	st	%i3, [%g4+12]
	mov	%g4, %g2
	mov	0, %g3
	cmp	%i4, 0
	be	.L155
	 mov	0, %g1
.L158:
	sll	%g3, 2, %g3
	ld	[%i5+%g3], %g3
	st	%g3, [%g2+16]
	add	%g1, 1, %g1
	add	%g2, 4, %g2
	cmp	%g1, %i4
	bne	.L158
	 mov	%g1, %g3
.L155:
	ld	[%g4+4], %g1
	addcc	%g1, 1, %g1
	be,a	.L153
	 mov	1, %g1
.L153:
	st	%g1, [%g4+4]
	jmp	%i7+8
	 restore %g0, 0, %o0
	.size	scheduleScoreboardJob, .-scheduleScoreboardJob
	.section	".rodata"
	.align 8
	.type	__func__.2585, #object
	.size	__func__.2585, 23
__func__.2585:
	.asciz	"responseReadyInChannel"
	.align 8
	.type	__func__.2708, #object
	.size	__func__.2708, 15
__func__.2708:
	.asciz	"sidekickServer"
	.align 8
	.type	__func__.2727, #object
	.size	__func__.2727, 17
__func__.2727:
	.asciz	"scoreboardServer"
	.align 8
	.type	__func__.2742, #object
	.size	__func__.2742, 19
__func__.2742:
	.asciz	"scheduleChannelJob"
	.align 8
	.type	__func__.2758, #object
	.size	__func__.2758, 22
__func__.2758:
	.asciz	"scheduleScoreboardJob"
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
