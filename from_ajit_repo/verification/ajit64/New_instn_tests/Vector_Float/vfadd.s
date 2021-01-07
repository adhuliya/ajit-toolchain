
.text
.global main

main:
start: 
        save %sp,-96,%sp    !save memory to store input values
	set 0xfffffffc,%g3   !double-word aligned for std
        and %fp, %g3,%fp
        set 0x3c663c66, %l0 !set value in a register  (value is 1.1)
        st %l0, [%fp + -4]  !put in memory
        ld [%fp + -4],%f0   !first input in f0 from memory
        fmovs %f0,%f1       !give values in all registers
	fmovs %f1,%f2
        fmovs %f1,%f3       
        vfadd16 %f0,%f2,%f4   !result should be 2.2

        set 0x3f8ccccc, %l0 !set value in a register  (value is 1.1)
        st %l0, [%fp + -4]  !put in memory
        ld [%fp + -4],%f0   !first input in f0 from memory
        fmovs %f0,%f2       !give values in all registers
        fmovs %f2,%f1
        fmovs %f1,%f3
	vfadd32 %f0,%f2,%f6   !result should be 2.2


	restore
 
end:	ta 0
