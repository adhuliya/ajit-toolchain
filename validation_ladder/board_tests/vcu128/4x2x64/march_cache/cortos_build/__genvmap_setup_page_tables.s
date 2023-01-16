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
   !PTD: context=0, index=0, level=1, child_p_addr=0x200, p_addr=0x400
   ! *(PAGE_TABLE_BASE + 0x400) = ptd(PAGE_TABLE_BASE + 0x200)
   ! make PTD from 0x200
   set 0x200, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x400, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTD: context=0, index=0, level=2, child_p_addr=0x0, p_addr=0x200
   ! *(PAGE_TABLE_BASE + 0x200) = ptd(PAGE_TABLE_BASE + 0x0)
   ! make PTD from 0x0
   set 0x0, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x200, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=0, level=3,  ppnr=0x0, p_addr=0x0, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x0) = 0x8a (pte)
   set 0x8a, %g2
   set 0x0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=1, level=3,  ppnr=0x1000, p_addr=0x4, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x4) = 0x18a (pte)
   set 0x18a, %g2
   set 0x4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=2, level=3,  ppnr=0x2000, p_addr=0x8, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x8) = 0x28a (pte)
   set 0x28a, %g2
   set 0x8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=3, level=3,  ppnr=0x3000, p_addr=0xc, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0xc) = 0x38a (pte)
   set 0x38a, %g2
   set 0xc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=4, level=3,  ppnr=0x4000, p_addr=0x10, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x10) = 0x48a (pte)
   set 0x48a, %g2
   set 0x10, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=5, level=3,  ppnr=0x5000, p_addr=0x14, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x14) = 0x58a (pte)
   set 0x58a, %g2
   set 0x14, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=6, level=3,  ppnr=0x6000, p_addr=0x18, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x18) = 0x68a (pte)
   set 0x68a, %g2
   set 0x18, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=7, level=3,  ppnr=0x7000, p_addr=0x1c, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x1c) = 0x78a (pte)
   set 0x78a, %g2
   set 0x1c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=8, level=3,  ppnr=0x8000, p_addr=0x20, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x20) = 0x88a (pte)
   set 0x88a, %g2
   set 0x20, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=9, level=3,  ppnr=0x9000, p_addr=0x24, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x24) = 0x98a (pte)
   set 0x98a, %g2
   set 0x24, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=10, level=3,  ppnr=0xa000, p_addr=0x28, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x28) = 0xa8a (pte)
   set 0xa8a, %g2
   set 0x28, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=11, level=3,  ppnr=0xb000, p_addr=0x2c, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x2c) = 0xb8a (pte)
   set 0xb8a, %g2
   set 0x2c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=12, level=3,  ppnr=0xc000, p_addr=0x30, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x30) = 0xc8a (pte)
   set 0xc8a, %g2
   set 0x30, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=13, level=3,  ppnr=0xd000, p_addr=0x34, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x34) = 0xd8a (pte)
   set 0xd8a, %g2
   set 0x34, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=14, level=3,  ppnr=0xe000, p_addr=0x38, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x38) = 0xe8a (pte)
   set 0xe8a, %g2
   set 0x38, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=15, level=3,  ppnr=0xf000, p_addr=0x3c, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x3c) = 0xf8a (pte)
   set 0xf8a, %g2
   set 0x3c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=16, level=3,  ppnr=0x10000, p_addr=0x40, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x40) = 0x108e (pte)
   set 0x108e, %g2
   set 0x40, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=17, level=3,  ppnr=0x11000, p_addr=0x44, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x44) = 0x118e (pte)
   set 0x118e, %g2
   set 0x44, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=18, level=3,  ppnr=0x12000, p_addr=0x48, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x48) = 0x128e (pte)
   set 0x128e, %g2
   set 0x48, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=19, level=3,  ppnr=0x13000, p_addr=0x4c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4c) = 0x138e (pte)
   set 0x138e, %g2
   set 0x4c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=20, level=3,  ppnr=0x14000, p_addr=0x50, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x50) = 0x148e (pte)
   set 0x148e, %g2
   set 0x50, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=21, level=3,  ppnr=0x15000, p_addr=0x54, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x54) = 0x158e (pte)
   set 0x158e, %g2
   set 0x54, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=22, level=3,  ppnr=0x16000, p_addr=0x58, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x58) = 0x168e (pte)
   set 0x168e, %g2
   set 0x58, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=23, level=3,  ppnr=0x17000, p_addr=0x5c, cacheable=0x0, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5c) = 0x170e (pte)
   set 0x170e, %g2
   set 0x5c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=24, level=3,  ppnr=0x18000, p_addr=0x60, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x60) = 0x188e (pte)
   set 0x188e, %g2
   set 0x60, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=25, level=3,  ppnr=0x19000, p_addr=0x64, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x64) = 0x198e (pte)
   set 0x198e, %g2
   set 0x64, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=26, level=3,  ppnr=0x1a000, p_addr=0x68, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x68) = 0x1a8e (pte)
   set 0x1a8e, %g2
   set 0x68, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=27, level=3,  ppnr=0x1b000, p_addr=0x6c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6c) = 0x1b8e (pte)
   set 0x1b8e, %g2
   set 0x6c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=28, level=3,  ppnr=0x1c000, p_addr=0x70, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x70) = 0x1c8e (pte)
   set 0x1c8e, %g2
   set 0x70, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=29, level=3,  ppnr=0x1d000, p_addr=0x74, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x74) = 0x1d8e (pte)
   set 0x1d8e, %g2
   set 0x74, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=30, level=3,  ppnr=0x1e000, p_addr=0x78, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x78) = 0x1e8e (pte)
   set 0x1e8e, %g2
   set 0x78, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=31, level=3,  ppnr=0x1f000, p_addr=0x7c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7c) = 0x1f8e (pte)
   set 0x1f8e, %g2
   set 0x7c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=32, level=3,  ppnr=0x20000, p_addr=0x80, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x80) = 0x208e (pte)
   set 0x208e, %g2
   set 0x80, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=33, level=3,  ppnr=0x21000, p_addr=0x84, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x84) = 0x218e (pte)
   set 0x218e, %g2
   set 0x84, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=34, level=3,  ppnr=0x22000, p_addr=0x88, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x88) = 0x228e (pte)
   set 0x228e, %g2
   set 0x88, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=35, level=3,  ppnr=0x23000, p_addr=0x8c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x8c) = 0x238e (pte)
   set 0x238e, %g2
   set 0x8c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=36, level=3,  ppnr=0x24000, p_addr=0x90, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x90) = 0x248e (pte)
   set 0x248e, %g2
   set 0x90, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=37, level=3,  ppnr=0x25000, p_addr=0x94, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x94) = 0x258e (pte)
   set 0x258e, %g2
   set 0x94, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=38, level=3,  ppnr=0x26000, p_addr=0x98, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x98) = 0x268e (pte)
   set 0x268e, %g2
   set 0x98, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=39, level=3,  ppnr=0x27000, p_addr=0x9c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x9c) = 0x278e (pte)
   set 0x278e, %g2
   set 0x9c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=40, level=3,  ppnr=0x28000, p_addr=0xa0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xa0) = 0x288e (pte)
   set 0x288e, %g2
   set 0xa0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=41, level=3,  ppnr=0x29000, p_addr=0xa4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xa4) = 0x298e (pte)
   set 0x298e, %g2
   set 0xa4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=42, level=3,  ppnr=0x2a000, p_addr=0xa8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xa8) = 0x2a8e (pte)
   set 0x2a8e, %g2
   set 0xa8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=43, level=3,  ppnr=0x2b000, p_addr=0xac, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xac) = 0x2b8e (pte)
   set 0x2b8e, %g2
   set 0xac, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=44, level=3,  ppnr=0x2c000, p_addr=0xb0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xb0) = 0x2c8e (pte)
   set 0x2c8e, %g2
   set 0xb0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=45, level=3,  ppnr=0x2d000, p_addr=0xb4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xb4) = 0x2d8e (pte)
   set 0x2d8e, %g2
   set 0xb4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=46, level=3,  ppnr=0x2e000, p_addr=0xb8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xb8) = 0x2e8e (pte)
   set 0x2e8e, %g2
   set 0xb8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=47, level=3,  ppnr=0x2f000, p_addr=0xbc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xbc) = 0x2f8e (pte)
   set 0x2f8e, %g2
   set 0xbc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=48, level=3,  ppnr=0x30000, p_addr=0xc0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xc0) = 0x308e (pte)
   set 0x308e, %g2
   set 0xc0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=49, level=3,  ppnr=0x31000, p_addr=0xc4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xc4) = 0x318e (pte)
   set 0x318e, %g2
   set 0xc4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=50, level=3,  ppnr=0x32000, p_addr=0xc8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xc8) = 0x328e (pte)
   set 0x328e, %g2
   set 0xc8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=51, level=3,  ppnr=0x33000, p_addr=0xcc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xcc) = 0x338e (pte)
   set 0x338e, %g2
   set 0xcc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=52, level=3,  ppnr=0x34000, p_addr=0xd0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xd0) = 0x348e (pte)
   set 0x348e, %g2
   set 0xd0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=53, level=3,  ppnr=0x35000, p_addr=0xd4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xd4) = 0x358e (pte)
   set 0x358e, %g2
   set 0xd4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=54, level=3,  ppnr=0x36000, p_addr=0xd8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xd8) = 0x368e (pte)
   set 0x368e, %g2
   set 0xd8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=55, level=3,  ppnr=0x37000, p_addr=0xdc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xdc) = 0x378e (pte)
   set 0x378e, %g2
   set 0xdc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=56, level=3,  ppnr=0x38000, p_addr=0xe0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xe0) = 0x388e (pte)
   set 0x388e, %g2
   set 0xe0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=57, level=3,  ppnr=0x39000, p_addr=0xe4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xe4) = 0x398e (pte)
   set 0x398e, %g2
   set 0xe4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=58, level=3,  ppnr=0x3a000, p_addr=0xe8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xe8) = 0x3a8e (pte)
   set 0x3a8e, %g2
   set 0xe8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=59, level=3,  ppnr=0x3b000, p_addr=0xec, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xec) = 0x3b8e (pte)
   set 0x3b8e, %g2
   set 0xec, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=60, level=3,  ppnr=0x3c000, p_addr=0xf0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xf0) = 0x3c8e (pte)
   set 0x3c8e, %g2
   set 0xf0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=61, level=3,  ppnr=0x3d000, p_addr=0xf4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xf4) = 0x3d8e (pte)
   set 0x3d8e, %g2
   set 0xf4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=62, level=3,  ppnr=0x3e000, p_addr=0xf8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xf8) = 0x3e8e (pte)
   set 0x3e8e, %g2
   set 0xf8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=63, level=3,  ppnr=0x3f000, p_addr=0xfc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xfc) = 0x3f8e (pte)
   set 0x3f8e, %g2
   set 0xfc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=1, level=2,  ppnr=0x40000, p_addr=0x204, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x204) = 0x408e (pte)
   set 0x408e, %g2
   set 0x204, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=2, level=2,  ppnr=0x80000, p_addr=0x208, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x208) = 0x808e (pte)
   set 0x808e, %g2
   set 0x208, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=3, level=2,  ppnr=0xc0000, p_addr=0x20c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x20c) = 0xc08e (pte)
   set 0xc08e, %g2
   set 0x20c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTD: context=0, index=4, level=2, child_p_addr=0x100, p_addr=0x210
   ! *(PAGE_TABLE_BASE + 0x210) = ptd(PAGE_TABLE_BASE + 0x100)
   ! make PTD from 0x100
   set 0x100, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x210, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=0, level=3,  ppnr=0x100000, p_addr=0x100, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x100) = 0x1008e (pte)
   set 0x1008e, %g2
   set 0x100, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=1, level=3,  ppnr=0x101000, p_addr=0x104, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x104) = 0x1018e (pte)
   set 0x1018e, %g2
   set 0x104, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=2, level=3,  ppnr=0x102000, p_addr=0x108, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x108) = 0x1028e (pte)
   set 0x1028e, %g2
   set 0x108, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=3, level=3,  ppnr=0x103000, p_addr=0x10c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x10c) = 0x1038e (pte)
   set 0x1038e, %g2
   set 0x10c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=4, level=3,  ppnr=0x104000, p_addr=0x110, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x110) = 0x1048e (pte)
   set 0x1048e, %g2
   set 0x110, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=5, level=3,  ppnr=0x105000, p_addr=0x114, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x114) = 0x1058e (pte)
   set 0x1058e, %g2
   set 0x114, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=6, level=3,  ppnr=0x106000, p_addr=0x118, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x118) = 0x1068e (pte)
   set 0x1068e, %g2
   set 0x118, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=7, level=3,  ppnr=0x107000, p_addr=0x11c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x11c) = 0x1078e (pte)
   set 0x1078e, %g2
   set 0x11c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=8, level=3,  ppnr=0x108000, p_addr=0x120, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x120) = 0x1088e (pte)
   set 0x1088e, %g2
   set 0x120, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=9, level=3,  ppnr=0x109000, p_addr=0x124, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x124) = 0x1098e (pte)
   set 0x1098e, %g2
   set 0x124, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=10, level=3,  ppnr=0x10a000, p_addr=0x128, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x128) = 0x10a8e (pte)
   set 0x10a8e, %g2
   set 0x128, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=11, level=3,  ppnr=0x10b000, p_addr=0x12c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x12c) = 0x10b8e (pte)
   set 0x10b8e, %g2
   set 0x12c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=12, level=3,  ppnr=0x10c000, p_addr=0x130, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x130) = 0x10c8e (pte)
   set 0x10c8e, %g2
   set 0x130, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=13, level=3,  ppnr=0x10d000, p_addr=0x134, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x134) = 0x10d8e (pte)
   set 0x10d8e, %g2
   set 0x134, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=14, level=3,  ppnr=0x10e000, p_addr=0x138, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x138) = 0x10e8e (pte)
   set 0x10e8e, %g2
   set 0x138, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=15, level=3,  ppnr=0x10f000, p_addr=0x13c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x13c) = 0x10f8e (pte)
   set 0x10f8e, %g2
   set 0x13c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=16, level=3,  ppnr=0x110000, p_addr=0x140, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x140) = 0x1108e (pte)
   set 0x1108e, %g2
   set 0x140, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=17, level=3,  ppnr=0x111000, p_addr=0x144, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x144) = 0x1118e (pte)
   set 0x1118e, %g2
   set 0x144, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=18, level=3,  ppnr=0x112000, p_addr=0x148, cacheable=0x1, acc=0x4
   ! *(PAGE_TABLE_BASE + 0x148) = 0x11292 (pte)
   set 0x11292, %g2
   set 0x148, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=19, level=3,  ppnr=0x113000, p_addr=0x14c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x14c) = 0x1138e (pte)
   set 0x1138e, %g2
   set 0x14c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=20, level=3,  ppnr=0x114000, p_addr=0x150, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x150) = 0x1148e (pte)
   set 0x1148e, %g2
   set 0x150, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=21, level=3,  ppnr=0x115000, p_addr=0x154, cacheable=0x1, acc=0x4
   ! *(PAGE_TABLE_BASE + 0x154) = 0x11592 (pte)
   set 0x11592, %g2
   set 0x154, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=22, level=3,  ppnr=0x116000, p_addr=0x158, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x158) = 0x1168e (pte)
   set 0x1168e, %g2
   set 0x158, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=23, level=3,  ppnr=0x117000, p_addr=0x15c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x15c) = 0x1178e (pte)
   set 0x1178e, %g2
   set 0x15c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=24, level=3,  ppnr=0x118000, p_addr=0x160, cacheable=0x1, acc=0x4
   ! *(PAGE_TABLE_BASE + 0x160) = 0x11892 (pte)
   set 0x11892, %g2
   set 0x160, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=25, level=3,  ppnr=0x119000, p_addr=0x164, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x164) = 0x1198e (pte)
   set 0x1198e, %g2
   set 0x164, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=26, level=3,  ppnr=0x11a000, p_addr=0x168, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x168) = 0x11a8e (pte)
   set 0x11a8e, %g2
   set 0x168, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=27, level=3,  ppnr=0x11b000, p_addr=0x16c, cacheable=0x1, acc=0x4
   ! *(PAGE_TABLE_BASE + 0x16c) = 0x11b92 (pte)
   set 0x11b92, %g2
   set 0x16c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=28, level=3,  ppnr=0x11c000, p_addr=0x170, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x170) = 0x11c8e (pte)
   set 0x11c8e, %g2
   set 0x170, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=29, level=3,  ppnr=0x11d000, p_addr=0x174, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x174) = 0x11d8e (pte)
   set 0x11d8e, %g2
   set 0x174, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=30, level=3,  ppnr=0x11e000, p_addr=0x178, cacheable=0x1, acc=0x4
   ! *(PAGE_TABLE_BASE + 0x178) = 0x11e92 (pte)
   set 0x11e92, %g2
   set 0x178, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=31, level=3,  ppnr=0x11f000, p_addr=0x17c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x17c) = 0x11f8e (pte)
   set 0x11f8e, %g2
   set 0x17c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=32, level=3,  ppnr=0x120000, p_addr=0x180, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x180) = 0x1208e (pte)
   set 0x1208e, %g2
   set 0x180, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=33, level=3,  ppnr=0x121000, p_addr=0x184, cacheable=0x1, acc=0x4
   ! *(PAGE_TABLE_BASE + 0x184) = 0x12192 (pte)
   set 0x12192, %g2
   set 0x184, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=34, level=3,  ppnr=0x122000, p_addr=0x188, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x188) = 0x1228e (pte)
   set 0x1228e, %g2
   set 0x188, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=35, level=3,  ppnr=0x123000, p_addr=0x18c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x18c) = 0x1238e (pte)
   set 0x1238e, %g2
   set 0x18c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=36, level=3,  ppnr=0x124000, p_addr=0x190, cacheable=0x1, acc=0x4
   ! *(PAGE_TABLE_BASE + 0x190) = 0x12492 (pte)
   set 0x12492, %g2
   set 0x190, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=37, level=3,  ppnr=0x125000, p_addr=0x194, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x194) = 0x1258e (pte)
   set 0x1258e, %g2
   set 0x194, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=38, level=3,  ppnr=0x126000, p_addr=0x198, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x198) = 0x1268e (pte)
   set 0x1268e, %g2
   set 0x198, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=39, level=3,  ppnr=0x127000, p_addr=0x19c, cacheable=0x1, acc=0x4
   ! *(PAGE_TABLE_BASE + 0x19c) = 0x12792 (pte)
   set 0x12792, %g2
   set 0x19c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=40, level=3,  ppnr=0x128000, p_addr=0x1a0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1a0) = 0x1288e (pte)
   set 0x1288e, %g2
   set 0x1a0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=41, level=3,  ppnr=0x129000, p_addr=0x1a4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1a4) = 0x1298e (pte)
   set 0x1298e, %g2
   set 0x1a4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=42, level=3,  ppnr=0x12a000, p_addr=0x1a8, cacheable=0x1, acc=0x4
   ! *(PAGE_TABLE_BASE + 0x1a8) = 0x12a92 (pte)
   set 0x12a92, %g2
   set 0x1a8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTD: context=0, index=32, level=1, child_p_addr=0x300, p_addr=0x480
   ! *(PAGE_TABLE_BASE + 0x480) = ptd(PAGE_TABLE_BASE + 0x300)
   ! make PTD from 0x300
   set 0x300, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x480, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=0, level=2,  ppnr=0x20000000, p_addr=0x300, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x300) = 0x200008e (pte)
   set 0x200008e, %g2
   set 0x300, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=1, level=2,  ppnr=0x20040000, p_addr=0x304, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x304) = 0x200408e (pte)
   set 0x200408e, %g2
   set 0x304, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=2, level=2,  ppnr=0x20080000, p_addr=0x308, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x308) = 0x200808e (pte)
   set 0x200808e, %g2
   set 0x308, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=3, level=2,  ppnr=0x200c0000, p_addr=0x30c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x30c) = 0x200c08e (pte)
   set 0x200c08e, %g2
   set 0x30c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=4, level=2,  ppnr=0x20100000, p_addr=0x310, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x310) = 0x201008e (pte)
   set 0x201008e, %g2
   set 0x310, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=5, level=2,  ppnr=0x20140000, p_addr=0x314, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x314) = 0x201408e (pte)
   set 0x201408e, %g2
   set 0x314, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=6, level=2,  ppnr=0x20180000, p_addr=0x318, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x318) = 0x201808e (pte)
   set 0x201808e, %g2
   set 0x318, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=7, level=2,  ppnr=0x201c0000, p_addr=0x31c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x31c) = 0x201c08e (pte)
   set 0x201c08e, %g2
   set 0x31c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=128, level=1,  ppnr=0x80000000, p_addr=0x600, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x600) = 0x8000016 (pte)
   set 0x8000016, %g2
   set 0x600, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=129, level=1,  ppnr=0x81000000, p_addr=0x604, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x604) = 0x8100016 (pte)
   set 0x8100016, %g2
   set 0x604, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=130, level=1,  ppnr=0x82000000, p_addr=0x608, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x608) = 0x8200016 (pte)
   set 0x8200016, %g2
   set 0x608, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=131, level=1,  ppnr=0x83000000, p_addr=0x60c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x60c) = 0x8300016 (pte)
   set 0x8300016, %g2
   set 0x60c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=132, level=1,  ppnr=0x84000000, p_addr=0x610, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x610) = 0x8400016 (pte)
   set 0x8400016, %g2
   set 0x610, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=133, level=1,  ppnr=0x85000000, p_addr=0x614, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x614) = 0x8500016 (pte)
   set 0x8500016, %g2
   set 0x614, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=134, level=1,  ppnr=0x86000000, p_addr=0x618, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x618) = 0x8600016 (pte)
   set 0x8600016, %g2
   set 0x618, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=135, level=1,  ppnr=0x87000000, p_addr=0x61c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x61c) = 0x8700016 (pte)
   set 0x8700016, %g2
   set 0x61c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=136, level=1,  ppnr=0x88000000, p_addr=0x620, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x620) = 0x8800016 (pte)
   set 0x8800016, %g2
   set 0x620, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=137, level=1,  ppnr=0x89000000, p_addr=0x624, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x624) = 0x8900016 (pte)
   set 0x8900016, %g2
   set 0x624, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=138, level=1,  ppnr=0x8a000000, p_addr=0x628, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x628) = 0x8a00016 (pte)
   set 0x8a00016, %g2
   set 0x628, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=139, level=1,  ppnr=0x8b000000, p_addr=0x62c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x62c) = 0x8b00016 (pte)
   set 0x8b00016, %g2
   set 0x62c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=140, level=1,  ppnr=0x8c000000, p_addr=0x630, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x630) = 0x8c00016 (pte)
   set 0x8c00016, %g2
   set 0x630, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=141, level=1,  ppnr=0x8d000000, p_addr=0x634, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x634) = 0x8d00016 (pte)
   set 0x8d00016, %g2
   set 0x634, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=142, level=1,  ppnr=0x8e000000, p_addr=0x638, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x638) = 0x8e00016 (pte)
   set 0x8e00016, %g2
   set 0x638, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=143, level=1,  ppnr=0x8f000000, p_addr=0x63c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x63c) = 0x8f00016 (pte)
   set 0x8f00016, %g2
   set 0x63c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=144, level=1,  ppnr=0x90000000, p_addr=0x640, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x640) = 0x9000016 (pte)
   set 0x9000016, %g2
   set 0x640, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=145, level=1,  ppnr=0x91000000, p_addr=0x644, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x644) = 0x9100016 (pte)
   set 0x9100016, %g2
   set 0x644, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=146, level=1,  ppnr=0x92000000, p_addr=0x648, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x648) = 0x9200016 (pte)
   set 0x9200016, %g2
   set 0x648, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=147, level=1,  ppnr=0x93000000, p_addr=0x64c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x64c) = 0x9300016 (pte)
   set 0x9300016, %g2
   set 0x64c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=148, level=1,  ppnr=0x94000000, p_addr=0x650, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x650) = 0x9400016 (pte)
   set 0x9400016, %g2
   set 0x650, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=149, level=1,  ppnr=0x95000000, p_addr=0x654, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x654) = 0x9500016 (pte)
   set 0x9500016, %g2
   set 0x654, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=150, level=1,  ppnr=0x96000000, p_addr=0x658, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x658) = 0x9600016 (pte)
   set 0x9600016, %g2
   set 0x658, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=151, level=1,  ppnr=0x97000000, p_addr=0x65c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x65c) = 0x9700016 (pte)
   set 0x9700016, %g2
   set 0x65c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=152, level=1,  ppnr=0x98000000, p_addr=0x660, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x660) = 0x9800016 (pte)
   set 0x9800016, %g2
   set 0x660, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=153, level=1,  ppnr=0x99000000, p_addr=0x664, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x664) = 0x9900016 (pte)
   set 0x9900016, %g2
   set 0x664, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=154, level=1,  ppnr=0x9a000000, p_addr=0x668, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x668) = 0x9a00016 (pte)
   set 0x9a00016, %g2
   set 0x668, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=155, level=1,  ppnr=0x9b000000, p_addr=0x66c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x66c) = 0x9b00016 (pte)
   set 0x9b00016, %g2
   set 0x66c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=156, level=1,  ppnr=0x9c000000, p_addr=0x670, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x670) = 0x9c00016 (pte)
   set 0x9c00016, %g2
   set 0x670, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=157, level=1,  ppnr=0x9d000000, p_addr=0x674, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x674) = 0x9d00016 (pte)
   set 0x9d00016, %g2
   set 0x674, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=158, level=1,  ppnr=0x9e000000, p_addr=0x678, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x678) = 0x9e00016 (pte)
   set 0x9e00016, %g2
   set 0x678, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=159, level=1,  ppnr=0x9f000000, p_addr=0x67c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x67c) = 0x9f00016 (pte)
   set 0x9f00016, %g2
   set 0x67c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=160, level=1,  ppnr=0xa0000000, p_addr=0x680, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x680) = 0xa000016 (pte)
   set 0xa000016, %g2
   set 0x680, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=161, level=1,  ppnr=0xa1000000, p_addr=0x684, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x684) = 0xa100016 (pte)
   set 0xa100016, %g2
   set 0x684, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=162, level=1,  ppnr=0xa2000000, p_addr=0x688, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x688) = 0xa200016 (pte)
   set 0xa200016, %g2
   set 0x688, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=163, level=1,  ppnr=0xa3000000, p_addr=0x68c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x68c) = 0xa300016 (pte)
   set 0xa300016, %g2
   set 0x68c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=164, level=1,  ppnr=0xa4000000, p_addr=0x690, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x690) = 0xa400016 (pte)
   set 0xa400016, %g2
   set 0x690, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=165, level=1,  ppnr=0xa5000000, p_addr=0x694, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x694) = 0xa500016 (pte)
   set 0xa500016, %g2
   set 0x694, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=166, level=1,  ppnr=0xa6000000, p_addr=0x698, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x698) = 0xa600016 (pte)
   set 0xa600016, %g2
   set 0x698, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=167, level=1,  ppnr=0xa7000000, p_addr=0x69c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x69c) = 0xa700016 (pte)
   set 0xa700016, %g2
   set 0x69c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=168, level=1,  ppnr=0xa8000000, p_addr=0x6a0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6a0) = 0xa800016 (pte)
   set 0xa800016, %g2
   set 0x6a0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=169, level=1,  ppnr=0xa9000000, p_addr=0x6a4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6a4) = 0xa900016 (pte)
   set 0xa900016, %g2
   set 0x6a4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=170, level=1,  ppnr=0xaa000000, p_addr=0x6a8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6a8) = 0xaa00016 (pte)
   set 0xaa00016, %g2
   set 0x6a8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=171, level=1,  ppnr=0xab000000, p_addr=0x6ac, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6ac) = 0xab00016 (pte)
   set 0xab00016, %g2
   set 0x6ac, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=172, level=1,  ppnr=0xac000000, p_addr=0x6b0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6b0) = 0xac00016 (pte)
   set 0xac00016, %g2
   set 0x6b0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=173, level=1,  ppnr=0xad000000, p_addr=0x6b4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6b4) = 0xad00016 (pte)
   set 0xad00016, %g2
   set 0x6b4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=174, level=1,  ppnr=0xae000000, p_addr=0x6b8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6b8) = 0xae00016 (pte)
   set 0xae00016, %g2
   set 0x6b8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=175, level=1,  ppnr=0xaf000000, p_addr=0x6bc, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6bc) = 0xaf00016 (pte)
   set 0xaf00016, %g2
   set 0x6bc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=176, level=1,  ppnr=0xb0000000, p_addr=0x6c0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6c0) = 0xb000016 (pte)
   set 0xb000016, %g2
   set 0x6c0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=177, level=1,  ppnr=0xb1000000, p_addr=0x6c4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6c4) = 0xb100016 (pte)
   set 0xb100016, %g2
   set 0x6c4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=178, level=1,  ppnr=0xb2000000, p_addr=0x6c8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6c8) = 0xb200016 (pte)
   set 0xb200016, %g2
   set 0x6c8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=179, level=1,  ppnr=0xb3000000, p_addr=0x6cc, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6cc) = 0xb300016 (pte)
   set 0xb300016, %g2
   set 0x6cc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=180, level=1,  ppnr=0xb4000000, p_addr=0x6d0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6d0) = 0xb400016 (pte)
   set 0xb400016, %g2
   set 0x6d0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=181, level=1,  ppnr=0xb5000000, p_addr=0x6d4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6d4) = 0xb500016 (pte)
   set 0xb500016, %g2
   set 0x6d4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=182, level=1,  ppnr=0xb6000000, p_addr=0x6d8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6d8) = 0xb600016 (pte)
   set 0xb600016, %g2
   set 0x6d8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=183, level=1,  ppnr=0xb7000000, p_addr=0x6dc, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6dc) = 0xb700016 (pte)
   set 0xb700016, %g2
   set 0x6dc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=184, level=1,  ppnr=0xb8000000, p_addr=0x6e0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6e0) = 0xb800016 (pte)
   set 0xb800016, %g2
   set 0x6e0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=185, level=1,  ppnr=0xb9000000, p_addr=0x6e4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6e4) = 0xb900016 (pte)
   set 0xb900016, %g2
   set 0x6e4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=186, level=1,  ppnr=0xba000000, p_addr=0x6e8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6e8) = 0xba00016 (pte)
   set 0xba00016, %g2
   set 0x6e8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=187, level=1,  ppnr=0xbb000000, p_addr=0x6ec, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6ec) = 0xbb00016 (pte)
   set 0xbb00016, %g2
   set 0x6ec, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=188, level=1,  ppnr=0xbc000000, p_addr=0x6f0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6f0) = 0xbc00016 (pte)
   set 0xbc00016, %g2
   set 0x6f0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=189, level=1,  ppnr=0xbd000000, p_addr=0x6f4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6f4) = 0xbd00016 (pte)
   set 0xbd00016, %g2
   set 0x6f4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=190, level=1,  ppnr=0xbe000000, p_addr=0x6f8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6f8) = 0xbe00016 (pte)
   set 0xbe00016, %g2
   set 0x6f8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=191, level=1,  ppnr=0xbf000000, p_addr=0x6fc, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x6fc) = 0xbf00016 (pte)
   set 0xbf00016, %g2
   set 0x6fc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=192, level=1,  ppnr=0xc0000000, p_addr=0x700, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x700) = 0xc000016 (pte)
   set 0xc000016, %g2
   set 0x700, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=193, level=1,  ppnr=0xc1000000, p_addr=0x704, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x704) = 0xc100016 (pte)
   set 0xc100016, %g2
   set 0x704, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=194, level=1,  ppnr=0xc2000000, p_addr=0x708, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x708) = 0xc200016 (pte)
   set 0xc200016, %g2
   set 0x708, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=195, level=1,  ppnr=0xc3000000, p_addr=0x70c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x70c) = 0xc300016 (pte)
   set 0xc300016, %g2
   set 0x70c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=196, level=1,  ppnr=0xc4000000, p_addr=0x710, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x710) = 0xc400016 (pte)
   set 0xc400016, %g2
   set 0x710, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=197, level=1,  ppnr=0xc5000000, p_addr=0x714, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x714) = 0xc500016 (pte)
   set 0xc500016, %g2
   set 0x714, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=198, level=1,  ppnr=0xc6000000, p_addr=0x718, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x718) = 0xc600016 (pte)
   set 0xc600016, %g2
   set 0x718, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=199, level=1,  ppnr=0xc7000000, p_addr=0x71c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x71c) = 0xc700016 (pte)
   set 0xc700016, %g2
   set 0x71c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=200, level=1,  ppnr=0xc8000000, p_addr=0x720, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x720) = 0xc800016 (pte)
   set 0xc800016, %g2
   set 0x720, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=201, level=1,  ppnr=0xc9000000, p_addr=0x724, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x724) = 0xc900016 (pte)
   set 0xc900016, %g2
   set 0x724, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=202, level=1,  ppnr=0xca000000, p_addr=0x728, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x728) = 0xca00016 (pte)
   set 0xca00016, %g2
   set 0x728, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=203, level=1,  ppnr=0xcb000000, p_addr=0x72c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x72c) = 0xcb00016 (pte)
   set 0xcb00016, %g2
   set 0x72c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=204, level=1,  ppnr=0xcc000000, p_addr=0x730, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x730) = 0xcc00016 (pte)
   set 0xcc00016, %g2
   set 0x730, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=205, level=1,  ppnr=0xcd000000, p_addr=0x734, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x734) = 0xcd00016 (pte)
   set 0xcd00016, %g2
   set 0x734, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=206, level=1,  ppnr=0xce000000, p_addr=0x738, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x738) = 0xce00016 (pte)
   set 0xce00016, %g2
   set 0x738, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=207, level=1,  ppnr=0xcf000000, p_addr=0x73c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x73c) = 0xcf00016 (pte)
   set 0xcf00016, %g2
   set 0x73c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=208, level=1,  ppnr=0xd0000000, p_addr=0x740, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x740) = 0xd000016 (pte)
   set 0xd000016, %g2
   set 0x740, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=209, level=1,  ppnr=0xd1000000, p_addr=0x744, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x744) = 0xd100016 (pte)
   set 0xd100016, %g2
   set 0x744, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=210, level=1,  ppnr=0xd2000000, p_addr=0x748, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x748) = 0xd200016 (pte)
   set 0xd200016, %g2
   set 0x748, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=211, level=1,  ppnr=0xd3000000, p_addr=0x74c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x74c) = 0xd300016 (pte)
   set 0xd300016, %g2
   set 0x74c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=212, level=1,  ppnr=0xd4000000, p_addr=0x750, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x750) = 0xd400016 (pte)
   set 0xd400016, %g2
   set 0x750, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=213, level=1,  ppnr=0xd5000000, p_addr=0x754, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x754) = 0xd500016 (pte)
   set 0xd500016, %g2
   set 0x754, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=214, level=1,  ppnr=0xd6000000, p_addr=0x758, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x758) = 0xd600016 (pte)
   set 0xd600016, %g2
   set 0x758, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=215, level=1,  ppnr=0xd7000000, p_addr=0x75c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x75c) = 0xd700016 (pte)
   set 0xd700016, %g2
   set 0x75c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=216, level=1,  ppnr=0xd8000000, p_addr=0x760, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x760) = 0xd800016 (pte)
   set 0xd800016, %g2
   set 0x760, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=217, level=1,  ppnr=0xd9000000, p_addr=0x764, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x764) = 0xd900016 (pte)
   set 0xd900016, %g2
   set 0x764, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=218, level=1,  ppnr=0xda000000, p_addr=0x768, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x768) = 0xda00016 (pte)
   set 0xda00016, %g2
   set 0x768, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=219, level=1,  ppnr=0xdb000000, p_addr=0x76c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x76c) = 0xdb00016 (pte)
   set 0xdb00016, %g2
   set 0x76c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=220, level=1,  ppnr=0xdc000000, p_addr=0x770, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x770) = 0xdc00016 (pte)
   set 0xdc00016, %g2
   set 0x770, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=221, level=1,  ppnr=0xdd000000, p_addr=0x774, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x774) = 0xdd00016 (pte)
   set 0xdd00016, %g2
   set 0x774, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=222, level=1,  ppnr=0xde000000, p_addr=0x778, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x778) = 0xde00016 (pte)
   set 0xde00016, %g2
   set 0x778, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=223, level=1,  ppnr=0xdf000000, p_addr=0x77c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x77c) = 0xdf00016 (pte)
   set 0xdf00016, %g2
   set 0x77c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=224, level=1,  ppnr=0xe0000000, p_addr=0x780, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x780) = 0xe000016 (pte)
   set 0xe000016, %g2
   set 0x780, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=225, level=1,  ppnr=0xe1000000, p_addr=0x784, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x784) = 0xe100016 (pte)
   set 0xe100016, %g2
   set 0x784, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=226, level=1,  ppnr=0xe2000000, p_addr=0x788, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x788) = 0xe200016 (pte)
   set 0xe200016, %g2
   set 0x788, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=227, level=1,  ppnr=0xe3000000, p_addr=0x78c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x78c) = 0xe300016 (pte)
   set 0xe300016, %g2
   set 0x78c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=228, level=1,  ppnr=0xe4000000, p_addr=0x790, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x790) = 0xe400016 (pte)
   set 0xe400016, %g2
   set 0x790, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=229, level=1,  ppnr=0xe5000000, p_addr=0x794, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x794) = 0xe500016 (pte)
   set 0xe500016, %g2
   set 0x794, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=230, level=1,  ppnr=0xe6000000, p_addr=0x798, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x798) = 0xe600016 (pte)
   set 0xe600016, %g2
   set 0x798, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=231, level=1,  ppnr=0xe7000000, p_addr=0x79c, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x79c) = 0xe700016 (pte)
   set 0xe700016, %g2
   set 0x79c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=232, level=1,  ppnr=0xe8000000, p_addr=0x7a0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7a0) = 0xe800016 (pte)
   set 0xe800016, %g2
   set 0x7a0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=233, level=1,  ppnr=0xe9000000, p_addr=0x7a4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7a4) = 0xe900016 (pte)
   set 0xe900016, %g2
   set 0x7a4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=234, level=1,  ppnr=0xea000000, p_addr=0x7a8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7a8) = 0xea00016 (pte)
   set 0xea00016, %g2
   set 0x7a8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=235, level=1,  ppnr=0xeb000000, p_addr=0x7ac, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7ac) = 0xeb00016 (pte)
   set 0xeb00016, %g2
   set 0x7ac, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=236, level=1,  ppnr=0xec000000, p_addr=0x7b0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7b0) = 0xec00016 (pte)
   set 0xec00016, %g2
   set 0x7b0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=237, level=1,  ppnr=0xed000000, p_addr=0x7b4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7b4) = 0xed00016 (pte)
   set 0xed00016, %g2
   set 0x7b4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=238, level=1,  ppnr=0xee000000, p_addr=0x7b8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7b8) = 0xee00016 (pte)
   set 0xee00016, %g2
   set 0x7b8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=239, level=1,  ppnr=0xef000000, p_addr=0x7bc, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7bc) = 0xef00016 (pte)
   set 0xef00016, %g2
   set 0x7bc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=240, level=1,  ppnr=0xf0000000, p_addr=0x7c0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7c0) = 0xf000016 (pte)
   set 0xf000016, %g2
   set 0x7c0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=241, level=1,  ppnr=0xf1000000, p_addr=0x7c4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7c4) = 0xf100016 (pte)
   set 0xf100016, %g2
   set 0x7c4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=242, level=1,  ppnr=0xf2000000, p_addr=0x7c8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7c8) = 0xf200016 (pte)
   set 0xf200016, %g2
   set 0x7c8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=243, level=1,  ppnr=0xf3000000, p_addr=0x7cc, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7cc) = 0xf300016 (pte)
   set 0xf300016, %g2
   set 0x7cc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=244, level=1,  ppnr=0xf4000000, p_addr=0x7d0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7d0) = 0xf400016 (pte)
   set 0xf400016, %g2
   set 0x7d0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=245, level=1,  ppnr=0xf5000000, p_addr=0x7d4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7d4) = 0xf500016 (pte)
   set 0xf500016, %g2
   set 0x7d4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=246, level=1,  ppnr=0xf6000000, p_addr=0x7d8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7d8) = 0xf600016 (pte)
   set 0xf600016, %g2
   set 0x7d8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=247, level=1,  ppnr=0xf7000000, p_addr=0x7dc, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7dc) = 0xf700016 (pte)
   set 0xf700016, %g2
   set 0x7dc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=248, level=1,  ppnr=0xf8000000, p_addr=0x7e0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7e0) = 0xf800016 (pte)
   set 0xf800016, %g2
   set 0x7e0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=249, level=1,  ppnr=0xf9000000, p_addr=0x7e4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7e4) = 0xf900016 (pte)
   set 0xf900016, %g2
   set 0x7e4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=250, level=1,  ppnr=0xfa000000, p_addr=0x7e8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7e8) = 0xfa00016 (pte)
   set 0xfa00016, %g2
   set 0x7e8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=251, level=1,  ppnr=0xfb000000, p_addr=0x7ec, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7ec) = 0xfb00016 (pte)
   set 0xfb00016, %g2
   set 0x7ec, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=252, level=1,  ppnr=0xfc000000, p_addr=0x7f0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7f0) = 0xfc00016 (pte)
   set 0xfc00016, %g2
   set 0x7f0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=253, level=1,  ppnr=0xfd000000, p_addr=0x7f4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7f4) = 0xfd00016 (pte)
   set 0xfd00016, %g2
   set 0x7f4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=254, level=1,  ppnr=0xfe000000, p_addr=0x7f8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7f8) = 0xfe00016 (pte)
   set 0xfe00016, %g2
   set 0x7f8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=255, level=1,  ppnr=0xff000000, p_addr=0x7fc, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0x7fc) = 0xff00016 (pte)
   set 0xff00016, %g2
   set 0x7fc, %g5
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
