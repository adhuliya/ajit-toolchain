
.text
.global main

main:
start: 
        save %sp,-80,%sp    !save memory to store input values
        set 0xfffffffc,%g3   !double-word aligned for std
        and %fp, %g3,%fp

        set 0x400ccccc, %l0 !set value in a register  (value is 2.2)
        st %l0, [%fp + -4]  !put in memory
        ld [%fp + -4],%f0   !first input in f0 from memory
        fmovs %f0,%f1       

        set 0x3f8ccccc, %l1 !set value in a register  (value is 1.1)
        st %l1, [%fp + -4]  !put in memory
        ld [%fp + -4],%f2   !second input in f0 from memory
	fmovs %f2,%f3
 
        vfsub32 %f0,%f2,%f4   !result should be 1.1
	set 0x40664066, %l0 !set value in a register  (value is 2.2)
        st %l0, [%fp + -4]  !put in memory
        ld [%fp + -4],%f0   !first input in f0 from memory
        fmovs %f0,%f1

        set 0x3c663c66, %l1 !set value in a register  (value is 1.1)
        st %l1, [%fp + -4]  !put in memory
        ld [%fp + -4],%f2   !second input in f0 from memory
        fmovs %f2,%f3



	vfsub16 %f0,%f2,%f6
        restore

 
end:	ta 0
