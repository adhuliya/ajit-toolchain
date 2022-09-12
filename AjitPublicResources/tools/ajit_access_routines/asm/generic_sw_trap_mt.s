! A generic software trap model, similar to the generic isr model.
!
! When you get here, you are in the trap window T
! which may or may not be an available window.  Our first
! job is to make T an available window, by executing a
! restore/save combination.  Save the globals. 
! And then work from T. Need to be careful while 
! RETT-ing by making window T+1 valid before RETT.
!
!
!  psr, tbr are as received in the trap table.
!  traps are disabled.
!
!  Note: T is is trap handler window and may be invalid!
!
!  ASSUMPTIONS
!    In window T+1, 
!       i0,i1,i2 contain 3 args which are to be passed
!       to the software trap handler.
!
.section .text.traphandlers
.global generic_vectored_sw_trap
generic_vectored_sw_trap:
   !
   ! check if T is valid.
   !
   rd %wim, %l4
   srl %l4, %l0, %l4
   cmp %l4, 0x1

   bne continue_with_valid_T
   nop

handle_invalid_T:
   ! window T-1 will be made invalid... build the wim.
   mov %wim,%l3
   sll %l3,7,%l4
   srl %l3,1,%l3
   or  %l3,%l4,%l3
   and %l3,0xff,%l3

   ! wim = 0... no traps in save/restore.
   mov %g0,%wim

   ! T is invalid.. go to T-1 and
   ! make it valid.
   save

   !
   !  save registers in T-1 to stack.
   !
   std %l0, [%sp +  0]
   std %l2, [%sp +  8]
   std %l4, [%sp + 16]
   std %l6, [%sp + 24]
   std %i0, [%sp + 32]
   std %i2, [%sp + 40]
   std %i4, [%sp + 48]
   std %i6, [%sp + 56]

   ! back in T.
   restore

   ! WIM says T-1 is invalid, but T is valid.
   mov %l3, %wim

continue_with_valid_T:

   ! stack for T
   sub %fp, 96, %sp


   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   ! save state in stack of window T.
   ! Step 0
   !    Save the PSR (for the flags!)
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   !
   !   Store globals ins psr l1 l2 in stack of T.
   !   Will be recovered later.
   !
   st  %l0, [%sp]            ! Save PSR
   st  %g1, [%sp + 4]
   std %g2, [%sp + 8]
   std %g4, [%sp + 16]
   std %g6, [%sp + 24]
   ! for rett
   st  %l1, [%sp + 32]
   st  %l2, [%sp + 36]
   ! y carries state.
   mov %y, %l7
   st  %l7,  [%sp + 40]


   ! floating point state is not saved here,
   ! but should be managed in the C handler.

   ! increase the stack further.. 
   ! for window overflow traps..
   sub %sp, 96, %sp

   !
   !   enable traps, but set proc-ilvl=15
   !   so that non NMI interrupt will be blocked.
   !   This prevents a non NMI interrupt from interrupting
   !   the trap handler.
   !
   or %l0, 0x20, %l7       ! ET=1
   or %l7, 0xf00, %l7     ! [11:8] = 0xf
   wr %l7, %psr           ! write to PSR

   ! Step 6
   !  call the ajit sw trap handler.. free to
   !  do whatever it wants... return should
   !  bring it home to this window..
   rd %tbr, %o0

   ! back up to window T+1, and copy i0,i1,i2 to 
   ! o0, o1, o2 in T+1.
   restore
   mov %i0, %o0
   mov %i1, %o1
   mov %i2, %o2

   ! back into window T, copy i0,i1,i2 to o1,o2,o3
   save 
   mov %i0, %o1
   mov %i1, %o2
   mov %i2, %o3

   !
   ! This is a  C routine with four arguments
   ! namely, the TBR value, and 3 uint32_t values.
   !
   ! It will run in window T-1....
   !    which may be invalid.. 
   !    Thus, the ET=1 above.
   !
   ! 
   call ajit_generic_sw_trap_handler
   nop

   !
   ! You have come back from the actual handler..
   ! Interrupts are still disabled... 

   ! But traps are enabled...  
   !  make window T+1 available for RETT!
   restore

   ! back in T.
   save

recover_and_leave:
   !
   !   recover psr, globals and other state saved in
   !   T's stack frame.
   !
   add %sp, 96, %sp

   !   get back the psr and global registers,in regs,y
   ld [%sp],  %l7  
   wr %l7, %psr
   ld  [%sp + 4],  %g1
   ldd [%sp + 8],  %g2
   ldd [%sp + 16], %g4
   ldd [%sp + 24], %g6
   ld  [%sp + 32], %l1
   ld  [%sp + 36], %l2
   ld  [%sp + 40], %l7


   ! recover y
   mov %l7, %y

jmpl_and_return:

   !   go home.. to the next instruction.
   jmpl %r18, %r0
   rett %r18 + 4

   nop
