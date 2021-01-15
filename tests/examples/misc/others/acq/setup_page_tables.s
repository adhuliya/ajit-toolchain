.global page_table_setup
page_table_setup:
   set PAGE_TABLE_BASE, %g1
   !PTD: index=0, level=0, child_p_addr=0x400, p_addr=0x800
   ! *(PAGE_TABLE_BASE + 0x800) = ptd(PAGE_TABLE_BASE + 0x400)
   ! make PTD from 0x400
   set 0x400, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   add 0x800, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: index=0, level=1,  ppnr=0x0, p_addr=0x400
   ! *(PAGE_TABLE_BASE + 0x400) = 0x8e (pte)
   set 0x8e, %g2
   add 0x400, %g1, %g3
   st %g2, [%g3]
   !PTD: index=64, level=1, child_p_addr=0x0, p_addr=0x500
   ! *(PAGE_TABLE_BASE + 0x500) = ptd(PAGE_TABLE_BASE + 0x0)
   ! make PTD from 0x0
   set 0x0, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   add 0x500, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: index=0, level=2,  ppnr=0x80000, p_addr=0x0
   ! *(PAGE_TABLE_BASE + 0x0) = 0x808e (pte)
   set 0x808e, %g2
   add 0x0, %g1, %g3
   st %g2, [%g3]
   !PTD: index=255, level=1, child_p_addr=0x2fc, p_addr=0x7fc
   ! *(PAGE_TABLE_BASE + 0x7fc) = ptd(PAGE_TABLE_BASE + 0x200)
   ! make PTD from 0x2fc
   set 0x200, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   add 0x7fc, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTD: index=63, level=2, child_p_addr=0x1fc, p_addr=0x2fc
   ! *(PAGE_TABLE_BASE + 0x2fc) = ptd(PAGE_TABLE_BASE + 0x100)
   ! make PTD from 0x1fc
   set 0x100, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   add 0x2fc, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: index=63, level=3,  ppnr=0xff000, p_addr=0x1fc
   ! *(PAGE_TABLE_BASE + 0x1fc) = 0xff8e (pte)
   set 0xff8e, %g2
   add 0x1fc, %g1, %g3
   st %g2, [%g3]
   !PTD: index=255, level=1, child_p_addr=0x2fc, p_addr=0x7fc
   ! *(PAGE_TABLE_BASE + 0x7fc) = ptd(PAGE_TABLE_BASE + 0x200)
   ! make PTD from 0x2fc
   set 0x200, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   add 0x7fc, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTD: index=63, level=2, child_p_addr=0x1fc, p_addr=0x2fc
   ! *(PAGE_TABLE_BASE + 0x2fc) = ptd(PAGE_TABLE_BASE + 0x100)
   ! make PTD from 0x1fc
   set 0x100, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   add 0x2fc, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: index=63, level=3,  ppnr=0xff000, p_addr=0x1fc
   ! *(PAGE_TABLE_BASE + 0x1fc) = 0xff8e (pte)
   set 0xff8e, %g2
   add 0x1fc, %g1, %g3
   st %g2, [%g3]
! start: set context-table-pointer = PAGE_TABLE_BASE + 0x800
   add 0x800, %g1, %g2
   srl  %g2, 0x4, %g2
   or  %g2, 0x1, %g2
   set 0x100, %g3
   sta %g2, [%g3] 0x4
! done: set  context-table-pointer
   retl;
   nop;
.align 1024
PAGE_TABLE_BASE: .skip 3072
