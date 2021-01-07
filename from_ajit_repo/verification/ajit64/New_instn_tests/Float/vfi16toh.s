
.text
.global main

main:
start: 
 
	save %sp, -80, %sp
	set 0xfffffffc,%g3   !double-word aligned for std
        and %fp, %g3,%fp

        set 0x10001, %l0 !set value in a register  (value is 1.1)
        st %l0, [%fp + -4]  !put in memory
        ld [%fp + -4],%f0   !first input in f0 from memory
        fmovs %f0,%f1       !give values in all registers

	vfi16toh %f0,%f2  !result should be 2.2

	
	restore
 
end:	ta 0
