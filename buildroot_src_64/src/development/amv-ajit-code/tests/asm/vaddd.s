.text
.global main
main:
start:

	

	! Set values for a register pair.
	set 0xf008c6f8, %l2
	set 0xf008c6f8, %l3  

	set 0xf000d2fa, %l4
        set 0xf000d2fa, %l5


	! After this,
	!g2 and g3 = e00898f2
	!g4 ans g5 = e00899f2
	!g6 and g7 = e00999f2 

	vaddd8 %l2,%l4,%g2
        vaddd16 %l2,%l4,%g4
        vaddd32 %l2,%l4,%g6

end:	ta 0
