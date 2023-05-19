.section .text.pagetablesetup
.global page_table_setup
page_table_setup:
   set PAGE_TABLE_BASE, %g1
   !PTD: context=0, index=0, level=0, child_p_addr=0x400, p_addr=0x800
   ! *(PAGE_TABLE_BASE + 0x800) = ptd(PAGE_TABLE_BASE + 0x400)
   ! make PTD from 0x400
   set 0x400, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x800, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=0, level=1,  ppnr=0x0, p_addr=0x400, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x400) = 0x8e (pte)
   set 0x8e, %g2
   set 0x400, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTD: context=0, index=255, level=1, child_p_addr=0x1fc, p_addr=0x7fc
   ! *(PAGE_TABLE_BASE + 0x7fc) = ptd(PAGE_TABLE_BASE + 0x100)
   ! make PTD from 0x1fc
   set 0x100, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x7fc, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTD: context=0, index=63, level=2, child_p_addr=0xcc, p_addr=0x1fc
   ! *(PAGE_TABLE_BASE + 0x1fc) = ptd(PAGE_TABLE_BASE + 0x0)
   ! make PTD from 0xcc
   set 0x0, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x1fc, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=51, level=3,  ppnr=0xffff3000, p_addr=0xcc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xcc) = 0xffff38e (pte)
   set 0xffff38e, %g2
   set 0xcc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=52, level=3,  ppnr=0xffff4000, p_addr=0xd0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xd0) = 0xffff48e (pte)
   set 0xffff48e, %g2
   set 0xd0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=63, level=3,  ppnr=0xff000, p_addr=0xfc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xfc) = 0xff8e (pte)
   set 0xff8e, %g2
   set 0xfc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=62, level=3,  ppnr=0xff000, p_addr=0xf8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xf8) = 0xff8e (pte)
   set 0xff8e, %g2
   set 0xf8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   retl;
   nop;
! done: page_table_setup
! start: set context-table-pointer = PAGE_TABLE_BASE + 0x800
.global set_context_table_pointer
set_context_table_pointer:
   set PAGE_TABLE_BASE, %g1
   set 0x800, %g5
   add %g5, %g1, %g2
   srl  %g2, 0x4, %g2
   or  %g2, 0x1, %g2
   set 0x100, %g3
   sta %g2, [%g3] 0x4
   retl;
   nop;
! done: set  context-table-pointer
.align 1024
PAGE_TABLE_BASE: .skip 3072
