.section .text.pagetablesetup
.global page_table_setup
page_table_setup:
   set PAGE_TABLE_BASE, %g1
   !PTD: context=0, index=0, level=0, child_p_addr=0x500, p_addr=0x800
   ! *(PAGE_TABLE_BASE + 0x800) = ptd(PAGE_TABLE_BASE + 0x400)
   ! make PTD from 0x500
   set 0x400, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x800, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTD: context=0, index=64, level=1, child_p_addr=0x100, p_addr=0x500
   ! *(PAGE_TABLE_BASE + 0x500) = ptd(PAGE_TABLE_BASE + 0x100)
   ! make PTD from 0x100
   set 0x100, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x500, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTD: context=0, index=0, level=2, child_p_addr=0x0, p_addr=0x100
   ! *(PAGE_TABLE_BASE + 0x100) = ptd(PAGE_TABLE_BASE + 0x0)
   ! make PTD from 0x0
   set 0x0, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x100, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=0, level=3,  ppnr=0x40000000, p_addr=0x0, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x0) = 0x400008a (pte)
   set 0x400008a, %g2
   set 0x0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=1, level=3,  ppnr=0x40001000, p_addr=0x4, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x4) = 0x400018a (pte)
   set 0x400018a, %g2
   set 0x4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=2, level=3,  ppnr=0x40002000, p_addr=0x8, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x8) = 0x400028a (pte)
   set 0x400028a, %g2
   set 0x8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=3, level=3,  ppnr=0x40003000, p_addr=0xc, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0xc) = 0x400038a (pte)
   set 0x400038a, %g2
   set 0xc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=4, level=3,  ppnr=0x40004000, p_addr=0x10, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x10) = 0x400048a (pte)
   set 0x400048a, %g2
   set 0x10, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=5, level=3,  ppnr=0x40005000, p_addr=0x14, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x14) = 0x400058a (pte)
   set 0x400058a, %g2
   set 0x14, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=6, level=3,  ppnr=0x40006000, p_addr=0x18, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x18) = 0x400068a (pte)
   set 0x400068a, %g2
   set 0x18, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=7, level=3,  ppnr=0x40007000, p_addr=0x1c, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x1c) = 0x400078a (pte)
   set 0x400078a, %g2
   set 0x1c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=8, level=3,  ppnr=0x40008000, p_addr=0x20, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x20) = 0x400088a (pte)
   set 0x400088a, %g2
   set 0x20, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=9, level=3,  ppnr=0x40009000, p_addr=0x24, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x24) = 0x400098a (pte)
   set 0x400098a, %g2
   set 0x24, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=10, level=3,  ppnr=0x4000a000, p_addr=0x28, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x28) = 0x4000a8a (pte)
   set 0x4000a8a, %g2
   set 0x28, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=11, level=3,  ppnr=0x4000b000, p_addr=0x2c, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x2c) = 0x4000b8a (pte)
   set 0x4000b8a, %g2
   set 0x2c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=12, level=3,  ppnr=0x4000c000, p_addr=0x30, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x30) = 0x4000c8a (pte)
   set 0x4000c8a, %g2
   set 0x30, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=13, level=3,  ppnr=0x4000d000, p_addr=0x34, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x34) = 0x4000d8a (pte)
   set 0x4000d8a, %g2
   set 0x34, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=14, level=3,  ppnr=0x4000e000, p_addr=0x38, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x38) = 0x4000e8a (pte)
   set 0x4000e8a, %g2
   set 0x38, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=15, level=3,  ppnr=0x4000f000, p_addr=0x3c, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x3c) = 0x4000f8a (pte)
   set 0x4000f8a, %g2
   set 0x3c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=16, level=3,  ppnr=0x40010000, p_addr=0x40, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x40) = 0x400108a (pte)
   set 0x400108a, %g2
   set 0x40, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=17, level=3,  ppnr=0x40011000, p_addr=0x44, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x44) = 0x400118e (pte)
   set 0x400118e, %g2
   set 0x44, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=18, level=3,  ppnr=0x40012000, p_addr=0x48, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x48) = 0x400128e (pte)
   set 0x400128e, %g2
   set 0x48, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=19, level=3,  ppnr=0x40013000, p_addr=0x4c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4c) = 0x400138e (pte)
   set 0x400138e, %g2
   set 0x4c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=20, level=3,  ppnr=0x40014000, p_addr=0x50, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x50) = 0x400148e (pte)
   set 0x400148e, %g2
   set 0x50, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=21, level=3,  ppnr=0x40015000, p_addr=0x54, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x54) = 0x400158e (pte)
   set 0x400158e, %g2
   set 0x54, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=22, level=3,  ppnr=0x40016000, p_addr=0x58, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x58) = 0x400168e (pte)
   set 0x400168e, %g2
   set 0x58, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=23, level=3,  ppnr=0x40017000, p_addr=0x5c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5c) = 0x400178e (pte)
   set 0x400178e, %g2
   set 0x5c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=24, level=3,  ppnr=0x40018000, p_addr=0x60, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x60) = 0x400188e (pte)
   set 0x400188e, %g2
   set 0x60, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=25, level=3,  ppnr=0x40019000, p_addr=0x64, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x64) = 0x400198e (pte)
   set 0x400198e, %g2
   set 0x64, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=26, level=3,  ppnr=0x4001a000, p_addr=0x68, cacheable=0x0, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x68) = 0x4001a0e (pte)
   set 0x4001a0e, %g2
   set 0x68, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=27, level=3,  ppnr=0x4001b000, p_addr=0x6c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6c) = 0x4001b8e (pte)
   set 0x4001b8e, %g2
   set 0x6c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=28, level=3,  ppnr=0x4001c000, p_addr=0x70, cacheable=0x1, acc=0x4
   ! *(PAGE_TABLE_BASE + 0x70) = 0x4001c92 (pte)
   set 0x4001c92, %g2
   set 0x70, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=29, level=3,  ppnr=0x4001d000, p_addr=0x74, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x74) = 0x4001d8e (pte)
   set 0x4001d8e, %g2
   set 0x74, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=30, level=3,  ppnr=0x4001e000, p_addr=0x78, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x78) = 0x4001e8e (pte)
   set 0x4001e8e, %g2
   set 0x78, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=31, level=3,  ppnr=0x4001f000, p_addr=0x7c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7c) = 0x4001f8e (pte)
   set 0x4001f8e, %g2
   set 0x7c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=32, level=3,  ppnr=0x40020000, p_addr=0x80, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x80) = 0x400208e (pte)
   set 0x400208e, %g2
   set 0x80, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=33, level=3,  ppnr=0x40021000, p_addr=0x84, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x84) = 0x400218e (pte)
   set 0x400218e, %g2
   set 0x84, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=34, level=3,  ppnr=0x40022000, p_addr=0x88, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x88) = 0x400228e (pte)
   set 0x400228e, %g2
   set 0x88, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=35, level=3,  ppnr=0x40023000, p_addr=0x8c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x8c) = 0x400238e (pte)
   set 0x400238e, %g2
   set 0x8c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=36, level=3,  ppnr=0x40024000, p_addr=0x90, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x90) = 0x400248e (pte)
   set 0x400248e, %g2
   set 0x90, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=37, level=3,  ppnr=0x40025000, p_addr=0x94, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x94) = 0x400258e (pte)
   set 0x400258e, %g2
   set 0x94, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=38, level=3,  ppnr=0x40026000, p_addr=0x98, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x98) = 0x400268e (pte)
   set 0x400268e, %g2
   set 0x98, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=39, level=3,  ppnr=0x40027000, p_addr=0x9c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x9c) = 0x400278e (pte)
   set 0x400278e, %g2
   set 0x9c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=40, level=3,  ppnr=0x40028000, p_addr=0xa0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xa0) = 0x400288e (pte)
   set 0x400288e, %g2
   set 0xa0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=41, level=3,  ppnr=0x40029000, p_addr=0xa4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xa4) = 0x400298e (pte)
   set 0x400298e, %g2
   set 0xa4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=42, level=3,  ppnr=0x4002a000, p_addr=0xa8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xa8) = 0x4002a8e (pte)
   set 0x4002a8e, %g2
   set 0xa8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=43, level=3,  ppnr=0x4002b000, p_addr=0xac, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xac) = 0x4002b8e (pte)
   set 0x4002b8e, %g2
   set 0xac, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=44, level=3,  ppnr=0x4002c000, p_addr=0xb0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xb0) = 0x4002c8e (pte)
   set 0x4002c8e, %g2
   set 0xb0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=45, level=3,  ppnr=0x4002d000, p_addr=0xb4, cacheable=0x1, acc=0x4
   ! *(PAGE_TABLE_BASE + 0xb4) = 0x4002d92 (pte)
   set 0x4002d92, %g2
   set 0xb4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=46, level=3,  ppnr=0x4002e000, p_addr=0xb8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xb8) = 0x4002e8e (pte)
   set 0x4002e8e, %g2
   set 0xb8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=47, level=3,  ppnr=0x4002f000, p_addr=0xbc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xbc) = 0x4002f8e (pte)
   set 0x4002f8e, %g2
   set 0xbc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=48, level=3,  ppnr=0x40030000, p_addr=0xc0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xc0) = 0x400308e (pte)
   set 0x400308e, %g2
   set 0xc0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=49, level=3,  ppnr=0x40031000, p_addr=0xc4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xc4) = 0x400318e (pte)
   set 0x400318e, %g2
   set 0xc4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=50, level=3,  ppnr=0x40032000, p_addr=0xc8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xc8) = 0x400328e (pte)
   set 0x400328e, %g2
   set 0xc8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=51, level=3,  ppnr=0x40033000, p_addr=0xcc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xcc) = 0x400338e (pte)
   set 0x400338e, %g2
   set 0xcc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=52, level=3,  ppnr=0x40034000, p_addr=0xd0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xd0) = 0x400348e (pte)
   set 0x400348e, %g2
   set 0xd0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=53, level=3,  ppnr=0x40035000, p_addr=0xd4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xd4) = 0x400358e (pte)
   set 0x400358e, %g2
   set 0xd4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=54, level=3,  ppnr=0x40036000, p_addr=0xd8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xd8) = 0x400368e (pte)
   set 0x400368e, %g2
   set 0xd8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=55, level=3,  ppnr=0x40037000, p_addr=0xdc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xdc) = 0x400378e (pte)
   set 0x400378e, %g2
   set 0xdc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=56, level=3,  ppnr=0x40038000, p_addr=0xe0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xe0) = 0x400388e (pte)
   set 0x400388e, %g2
   set 0xe0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=57, level=3,  ppnr=0x40039000, p_addr=0xe4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xe4) = 0x400398e (pte)
   set 0x400398e, %g2
   set 0xe4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=58, level=3,  ppnr=0x4003a000, p_addr=0xe8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xe8) = 0x4003a8e (pte)
   set 0x4003a8e, %g2
   set 0xe8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=59, level=3,  ppnr=0x4003b000, p_addr=0xec, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xec) = 0x4003b8e (pte)
   set 0x4003b8e, %g2
   set 0xec, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=60, level=3,  ppnr=0x4003c000, p_addr=0xf0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xf0) = 0x4003c8e (pte)
   set 0x4003c8e, %g2
   set 0xf0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=61, level=3,  ppnr=0x4003d000, p_addr=0xf4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xf4) = 0x4003d8e (pte)
   set 0x4003d8e, %g2
   set 0xf4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=62, level=3,  ppnr=0x4003e000, p_addr=0xf8, cacheable=0x1, acc=0x4
   ! *(PAGE_TABLE_BASE + 0xf8) = 0x4003e92 (pte)
   set 0x4003e92, %g2
   set 0xf8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTD: context=0, index=255, level=1, child_p_addr=0x3fc, p_addr=0x7fc
   ! *(PAGE_TABLE_BASE + 0x7fc) = ptd(PAGE_TABLE_BASE + 0x300)
   ! make PTD from 0x3fc
   set 0x300, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x7fc, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTD: context=0, index=63, level=2, child_p_addr=0x2c0, p_addr=0x3fc
   ! *(PAGE_TABLE_BASE + 0x3fc) = ptd(PAGE_TABLE_BASE + 0x200)
   ! make PTD from 0x2c0
   set 0x200, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x3fc, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=48, level=3,  ppnr=0xffff0000, p_addr=0x2c0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2c0) = 0xffff016 (pte)
   set 0xffff016, %g2
   set 0x2c0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=49, level=3,  ppnr=0xffff1000, p_addr=0x2c4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2c4) = 0xffff116 (pte)
   set 0xffff116, %g2
   set 0x2c4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=50, level=3,  ppnr=0xffff2000, p_addr=0x2c8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2c8) = 0xffff216 (pte)
   set 0xffff216, %g2
   set 0x2c8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=51, level=3,  ppnr=0xffff3000, p_addr=0x2cc, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2cc) = 0xffff316 (pte)
   set 0xffff316, %g2
   set 0x2cc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=52, level=3,  ppnr=0xffff4000, p_addr=0x2d0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2d0) = 0xffff416 (pte)
   set 0xffff416, %g2
   set 0x2d0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=53, level=3,  ppnr=0xffff5000, p_addr=0x2d4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2d4) = 0xffff516 (pte)
   set 0xffff516, %g2
   set 0x2d4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=54, level=3,  ppnr=0xffff6000, p_addr=0x2d8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2d8) = 0xffff616 (pte)
   set 0xffff616, %g2
   set 0x2d8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=55, level=3,  ppnr=0xffff7000, p_addr=0x2dc, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2dc) = 0xffff716 (pte)
   set 0xffff716, %g2
   set 0x2dc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=56, level=3,  ppnr=0xffff8000, p_addr=0x2e0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2e0) = 0xffff816 (pte)
   set 0xffff816, %g2
   set 0x2e0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=57, level=3,  ppnr=0xffff9000, p_addr=0x2e4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2e4) = 0xffff916 (pte)
   set 0xffff916, %g2
   set 0x2e4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=58, level=3,  ppnr=0xffffa000, p_addr=0x2e8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2e8) = 0xffffa16 (pte)
   set 0xffffa16, %g2
   set 0x2e8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=59, level=3,  ppnr=0xffffb000, p_addr=0x2ec, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2ec) = 0xffffb16 (pte)
   set 0xffffb16, %g2
   set 0x2ec, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=60, level=3,  ppnr=0xffffc000, p_addr=0x2f0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2f0) = 0xffffc16 (pte)
   set 0xffffc16, %g2
   set 0x2f0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=61, level=3,  ppnr=0xffffd000, p_addr=0x2f4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2f4) = 0xffffd16 (pte)
   set 0xffffd16, %g2
   set 0x2f4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=62, level=3,  ppnr=0xffffe000, p_addr=0x2f8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2f8) = 0xffffe16 (pte)
   set 0xffffe16, %g2
   set 0x2f8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=63, level=3,  ppnr=0xfffff000, p_addr=0x2fc, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x2fc) = 0xfffff16 (pte)
   set 0xfffff16, %g2
   set 0x2fc, %g5
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
