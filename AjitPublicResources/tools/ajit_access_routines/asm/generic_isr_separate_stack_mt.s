! An improved generic isr model for the case when an interrupt handler
! does a lot of user-level work.
! Stack for ISR.
.section .data.traphandlers
! 4KB for now, configurable later.
.global generic_isr_stack_buffer
.align 8
generic_isr_stack_buffer
.skip 4096

!
! There was an interrupt in window W, we move to trap window T
! Trap window T is either valid or invalid..  If it is valid,
! then we can give it a stack..  
!
! If T is invalid, then we make it valid as follows:
!    make T-1 invalid by saving its registers to stack.
!         and adjusting wim
!    make T valid
! endif 
!    Give T a stack relative to that in W.
!    save T state into W. 
!    deepen the stack in T.
!    call the ajit generic interrupt handler from T.
!    on return, make window T+1 available to 
!           rett into.. using a restore/save combination.
!    recover the critical information stored on stack in T
!    jmpl/rett into T+1 and go on.
!
!  ASSUMPTIONS
!    l0 contains PSR
!    l3 contains TBR
!
.section .text.traphandlers
.align 8
.global generic_vectored_isr
generic_vectored_isr:
   !
   ! check if T is valid.
   !
   rd %wim, %l4
   srl %l4, %l0, %l4
   cmp %l4, 0x1

   bne continue_with_valid_T
   nop

handle_invalid_T:

   ! window T-1 will be made invalid...
   mov %wim,%l3
   sll %l3,7,%l4
   srl %l3,1,%l3
   or  %l3,%l4,%l3
   and %l3,0xff,%l3

   ! wim = 0.
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

   ! Give window T a stack..
   sub %fp, 128, %sp


   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   ! save state in stack of window T.
   ! Step 0
   !    Save the PSR (for the flags!)
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   !
   !   Store globals ins psr l1 l2 in stack of T.
   !   Will be recovered later.
   !
   st  %l0, [%sp + 64]            ! Save PSR
   st  %g1, [%sp + 68]
   std %g2, [%sp + 72]
   std %g4, [%sp + 80]
   std %g6, [%sp + 88]
   ! for rett
   st  %l1, [%sp + 96]
   st  %l2, [%sp + 100]
   ! y carries state.
   mov %y, %l7
   st  %l7,  [%sp + 104]

   ! floating point state is not saved here,
   ! but should be managed in the C handler.


   !
   !   enable traps, but set proc-ilvl=15
   !   so that non NMI interrupt will be blocked.
   !   This prevents a non NMI interrupt from interrupting
   !   the interrupt handler.
   !
   or %l0, 0x20, %l7       ! ET=1
   or %l7, 0xf00, %l7      ! [11:8] = 0xf
   wr %l7, %psr            ! write to PSR

   !
   ! switch to isr stack.
   !    In this window, a minimal stack..
   !
   mov %sp, %fp
   set generic_isr_stack_buffer, %sp
   set 4096, %l7
   add %sp, %l7, %sp
   sub %sp, 64, %sp

   !  call the interrupt handler.. free to
   !  do whatever it wants... return should
   !  bring it home to this window..
   rd %tbr, %o0

   ! This is a  C routine with one argument
   ! namely, the TBR value.
   !
   ! It will run in window T-1....
   !    which may be invalid.. 
   !    Thus, the ET=1 above.
   !
   ! 
   call ajit_generic_interrupt_handler
   nop

   !
   ! You have come back from the actual handler..
   ! Interrupts are still disabled... 
   ! Traps are enabled...  
   ! Get back the original stack.
   mov %fp, %sp
   add %fp, 128, %fp
   
   !   get back the psr and global registers,in regs,y
   ld [%sp + 64],   %l3  ! the original psr
   ld  [%sp + 68],  %g1
   ldd [%sp + 72],  %g2
   ldd [%sp + 80],  %g4
   ldd [%sp + 88],  %g6
   ld  [%sp + 96],  %l1
   ld  [%sp + 100], %l2
   ld  [%sp + 104], %l7
   ! recover y.
   mov %l7, %y

   !  make window T+1 available for RETT!
   !  Note that traps are enabled, you can
   !  restore..
   restore

   ! back in T.
   save
 
   ! original psr, disable traps..
   wr %l3, %psr

recover_and_leave:

jmpl_and_return:

   !   go home.. guaranteed that the
   !   return window is valid 
   jmpl %r17, %r0
   rett %r18

   nop
