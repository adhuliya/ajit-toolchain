.section ".text"
.align 4
.global add
.type add, #function
add:
	save %sp, -80, %sp
	add %i0, %i1, %g1  !input is in io and io of callee, and in o0 and o1 of caller.
	mov %g1, %i0	   !ouput is stored in i0 of callee, calleer finds it as i0 of its register window.		
	restore
	retl
	nop
