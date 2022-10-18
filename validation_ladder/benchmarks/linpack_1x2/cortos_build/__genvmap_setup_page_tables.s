.section .text.pagetablesetup
.global page_table_setup
page_table_setup:
   set PAGE_TABLE_BASE, %g1
   !PTD: context=0, index=0, level=0, child_p_addr=0xd00, p_addr=0x1000
   ! *(PAGE_TABLE_BASE + 0x1000) = ptd(PAGE_TABLE_BASE + 0xc00)
   ! make PTD from 0xd00
   set 0xc00, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x1000, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTD: context=0, index=64, level=1, child_p_addr=0x0, p_addr=0xd00
   ! *(PAGE_TABLE_BASE + 0xd00) = ptd(PAGE_TABLE_BASE + 0x0)
   ! make PTD from 0x0
   set 0x0, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0xd00, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=0, level=2,  ppnr=0x40000000, p_addr=0x0, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x0) = 0x400008a (pte)
   set 0x400008a, %g2
   set 0x0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=1, level=2,  ppnr=0x40040000, p_addr=0x4, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x4) = 0x400408a (pte)
   set 0x400408a, %g2
   set 0x4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=2, level=2,  ppnr=0x40080000, p_addr=0x8, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x8) = 0x400808a (pte)
   set 0x400808a, %g2
   set 0x8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=3, level=2,  ppnr=0x400c0000, p_addr=0xc, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0xc) = 0x400c08a (pte)
   set 0x400c08a, %g2
   set 0xc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=4, level=2,  ppnr=0x40100000, p_addr=0x10, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x10) = 0x401008a (pte)
   set 0x401008a, %g2
   set 0x10, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=5, level=2,  ppnr=0x40140000, p_addr=0x14, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x14) = 0x401408a (pte)
   set 0x401408a, %g2
   set 0x14, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=6, level=2,  ppnr=0x40180000, p_addr=0x18, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x18) = 0x401808a (pte)
   set 0x401808a, %g2
   set 0x18, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=7, level=2,  ppnr=0x401c0000, p_addr=0x1c, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x1c) = 0x401c08a (pte)
   set 0x401c08a, %g2
   set 0x1c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=8, level=2,  ppnr=0x40200000, p_addr=0x20, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x20) = 0x402008a (pte)
   set 0x402008a, %g2
   set 0x20, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=9, level=2,  ppnr=0x40240000, p_addr=0x24, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x24) = 0x402408a (pte)
   set 0x402408a, %g2
   set 0x24, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=10, level=2,  ppnr=0x40280000, p_addr=0x28, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x28) = 0x402808a (pte)
   set 0x402808a, %g2
   set 0x28, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=11, level=2,  ppnr=0x402c0000, p_addr=0x2c, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x2c) = 0x402c08a (pte)
   set 0x402c08a, %g2
   set 0x2c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=12, level=2,  ppnr=0x40300000, p_addr=0x30, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x30) = 0x403008a (pte)
   set 0x403008a, %g2
   set 0x30, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=13, level=2,  ppnr=0x40340000, p_addr=0x34, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x34) = 0x403408a (pte)
   set 0x403408a, %g2
   set 0x34, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=14, level=2,  ppnr=0x40380000, p_addr=0x38, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x38) = 0x403808a (pte)
   set 0x403808a, %g2
   set 0x38, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=15, level=2,  ppnr=0x403c0000, p_addr=0x3c, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x3c) = 0x403c08a (pte)
   set 0x403c08a, %g2
   set 0x3c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=16, level=2,  ppnr=0x40400000, p_addr=0x40, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x40) = 0x404008a (pte)
   set 0x404008a, %g2
   set 0x40, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=17, level=2,  ppnr=0x40440000, p_addr=0x44, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x44) = 0x404408a (pte)
   set 0x404408a, %g2
   set 0x44, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=18, level=2,  ppnr=0x40480000, p_addr=0x48, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x48) = 0x404808a (pte)
   set 0x404808a, %g2
   set 0x48, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=19, level=2,  ppnr=0x404c0000, p_addr=0x4c, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x4c) = 0x404c08a (pte)
   set 0x404c08a, %g2
   set 0x4c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=20, level=2,  ppnr=0x40500000, p_addr=0x50, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x50) = 0x405008a (pte)
   set 0x405008a, %g2
   set 0x50, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=21, level=2,  ppnr=0x40540000, p_addr=0x54, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x54) = 0x405408a (pte)
   set 0x405408a, %g2
   set 0x54, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=22, level=2,  ppnr=0x40580000, p_addr=0x58, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x58) = 0x405808a (pte)
   set 0x405808a, %g2
   set 0x58, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=23, level=2,  ppnr=0x405c0000, p_addr=0x5c, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x5c) = 0x405c08a (pte)
   set 0x405c08a, %g2
   set 0x5c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=24, level=2,  ppnr=0x40600000, p_addr=0x60, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x60) = 0x406008a (pte)
   set 0x406008a, %g2
   set 0x60, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=25, level=2,  ppnr=0x40640000, p_addr=0x64, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x64) = 0x406408a (pte)
   set 0x406408a, %g2
   set 0x64, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=26, level=2,  ppnr=0x40680000, p_addr=0x68, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x68) = 0x406808a (pte)
   set 0x406808a, %g2
   set 0x68, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=27, level=2,  ppnr=0x406c0000, p_addr=0x6c, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x6c) = 0x406c08a (pte)
   set 0x406c08a, %g2
   set 0x6c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=28, level=2,  ppnr=0x40700000, p_addr=0x70, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x70) = 0x407008a (pte)
   set 0x407008a, %g2
   set 0x70, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=29, level=2,  ppnr=0x40740000, p_addr=0x74, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x74) = 0x407408a (pte)
   set 0x407408a, %g2
   set 0x74, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=30, level=2,  ppnr=0x40780000, p_addr=0x78, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x78) = 0x407808a (pte)
   set 0x407808a, %g2
   set 0x78, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=31, level=2,  ppnr=0x407c0000, p_addr=0x7c, cacheable=0x1, acc=0x2
   ! *(PAGE_TABLE_BASE + 0x7c) = 0x407c08a (pte)
   set 0x407c08a, %g2
   set 0x7c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=32, level=2,  ppnr=0x40800000, p_addr=0x80, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x80) = 0x408008e (pte)
   set 0x408008e, %g2
   set 0x80, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=33, level=2,  ppnr=0x40840000, p_addr=0x84, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x84) = 0x408408e (pte)
   set 0x408408e, %g2
   set 0x84, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=34, level=2,  ppnr=0x40880000, p_addr=0x88, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x88) = 0x408808e (pte)
   set 0x408808e, %g2
   set 0x88, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=35, level=2,  ppnr=0x408c0000, p_addr=0x8c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x8c) = 0x408c08e (pte)
   set 0x408c08e, %g2
   set 0x8c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=36, level=2,  ppnr=0x40900000, p_addr=0x90, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x90) = 0x409008e (pte)
   set 0x409008e, %g2
   set 0x90, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=37, level=2,  ppnr=0x40940000, p_addr=0x94, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x94) = 0x409408e (pte)
   set 0x409408e, %g2
   set 0x94, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=38, level=2,  ppnr=0x40980000, p_addr=0x98, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x98) = 0x409808e (pte)
   set 0x409808e, %g2
   set 0x98, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=39, level=2,  ppnr=0x409c0000, p_addr=0x9c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x9c) = 0x409c08e (pte)
   set 0x409c08e, %g2
   set 0x9c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=40, level=2,  ppnr=0x40a00000, p_addr=0xa0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xa0) = 0x40a008e (pte)
   set 0x40a008e, %g2
   set 0xa0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=41, level=2,  ppnr=0x40a40000, p_addr=0xa4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xa4) = 0x40a408e (pte)
   set 0x40a408e, %g2
   set 0xa4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=42, level=2,  ppnr=0x40a80000, p_addr=0xa8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xa8) = 0x40a808e (pte)
   set 0x40a808e, %g2
   set 0xa8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=43, level=2,  ppnr=0x40ac0000, p_addr=0xac, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xac) = 0x40ac08e (pte)
   set 0x40ac08e, %g2
   set 0xac, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=44, level=2,  ppnr=0x40b00000, p_addr=0xb0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xb0) = 0x40b008e (pte)
   set 0x40b008e, %g2
   set 0xb0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=45, level=2,  ppnr=0x40b40000, p_addr=0xb4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xb4) = 0x40b408e (pte)
   set 0x40b408e, %g2
   set 0xb4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=46, level=2,  ppnr=0x40b80000, p_addr=0xb8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xb8) = 0x40b808e (pte)
   set 0x40b808e, %g2
   set 0xb8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=47, level=2,  ppnr=0x40bc0000, p_addr=0xbc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xbc) = 0x40bc08e (pte)
   set 0x40bc08e, %g2
   set 0xbc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=48, level=2,  ppnr=0x40c00000, p_addr=0xc0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xc0) = 0x40c008e (pte)
   set 0x40c008e, %g2
   set 0xc0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=49, level=2,  ppnr=0x40c40000, p_addr=0xc4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xc4) = 0x40c408e (pte)
   set 0x40c408e, %g2
   set 0xc4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=50, level=2,  ppnr=0x40c80000, p_addr=0xc8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xc8) = 0x40c808e (pte)
   set 0x40c808e, %g2
   set 0xc8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=51, level=2,  ppnr=0x40cc0000, p_addr=0xcc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xcc) = 0x40cc08e (pte)
   set 0x40cc08e, %g2
   set 0xcc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=52, level=2,  ppnr=0x40d00000, p_addr=0xd0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xd0) = 0x40d008e (pte)
   set 0x40d008e, %g2
   set 0xd0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=53, level=2,  ppnr=0x40d40000, p_addr=0xd4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xd4) = 0x40d408e (pte)
   set 0x40d408e, %g2
   set 0xd4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=54, level=2,  ppnr=0x40d80000, p_addr=0xd8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xd8) = 0x40d808e (pte)
   set 0x40d808e, %g2
   set 0xd8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=55, level=2,  ppnr=0x40dc0000, p_addr=0xdc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xdc) = 0x40dc08e (pte)
   set 0x40dc08e, %g2
   set 0xdc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=56, level=2,  ppnr=0x40e00000, p_addr=0xe0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xe0) = 0x40e008e (pte)
   set 0x40e008e, %g2
   set 0xe0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=57, level=2,  ppnr=0x40e40000, p_addr=0xe4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xe4) = 0x40e408e (pte)
   set 0x40e408e, %g2
   set 0xe4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=58, level=2,  ppnr=0x40e80000, p_addr=0xe8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xe8) = 0x40e808e (pte)
   set 0x40e808e, %g2
   set 0xe8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=59, level=2,  ppnr=0x40ec0000, p_addr=0xec, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xec) = 0x40ec08e (pte)
   set 0x40ec08e, %g2
   set 0xec, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=60, level=2,  ppnr=0x40f00000, p_addr=0xf0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xf0) = 0x40f008e (pte)
   set 0x40f008e, %g2
   set 0xf0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=61, level=2,  ppnr=0x40f40000, p_addr=0xf4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xf4) = 0x40f408e (pte)
   set 0x40f408e, %g2
   set 0xf4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=62, level=2,  ppnr=0x40f80000, p_addr=0xf8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xf8) = 0x40f808e (pte)
   set 0x40f808e, %g2
   set 0xf8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=63, level=2,  ppnr=0x40fc0000, p_addr=0xfc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xfc) = 0x40fc08e (pte)
   set 0x40fc08e, %g2
   set 0xfc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=65, level=1,  ppnr=0x41000000, p_addr=0xd04, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xd04) = 0x410008e (pte)
   set 0x410008e, %g2
   set 0xd04, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTD: context=0, index=66, level=1, child_p_addr=0x100, p_addr=0xd08
   ! *(PAGE_TABLE_BASE + 0xd08) = ptd(PAGE_TABLE_BASE + 0x100)
   ! make PTD from 0x100
   set 0x100, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0xd08, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=0, level=2,  ppnr=0x42000000, p_addr=0x100, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x100) = 0x420008e (pte)
   set 0x420008e, %g2
   set 0x100, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=1, level=2,  ppnr=0x42040000, p_addr=0x104, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x104) = 0x420408e (pte)
   set 0x420408e, %g2
   set 0x104, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=2, level=2,  ppnr=0x42080000, p_addr=0x108, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x108) = 0x420808e (pte)
   set 0x420808e, %g2
   set 0x108, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=3, level=2,  ppnr=0x420c0000, p_addr=0x10c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x10c) = 0x420c08e (pte)
   set 0x420c08e, %g2
   set 0x10c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=4, level=2,  ppnr=0x42100000, p_addr=0x110, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x110) = 0x421008e (pte)
   set 0x421008e, %g2
   set 0x110, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=5, level=2,  ppnr=0x42140000, p_addr=0x114, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x114) = 0x421408e (pte)
   set 0x421408e, %g2
   set 0x114, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=6, level=2,  ppnr=0x42180000, p_addr=0x118, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x118) = 0x421808e (pte)
   set 0x421808e, %g2
   set 0x118, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=7, level=2,  ppnr=0x421c0000, p_addr=0x11c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x11c) = 0x421c08e (pte)
   set 0x421c08e, %g2
   set 0x11c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=8, level=2,  ppnr=0x42200000, p_addr=0x120, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x120) = 0x422008e (pte)
   set 0x422008e, %g2
   set 0x120, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=9, level=2,  ppnr=0x42240000, p_addr=0x124, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x124) = 0x422408e (pte)
   set 0x422408e, %g2
   set 0x124, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=10, level=2,  ppnr=0x42280000, p_addr=0x128, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x128) = 0x422808e (pte)
   set 0x422808e, %g2
   set 0x128, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=11, level=2,  ppnr=0x422c0000, p_addr=0x12c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x12c) = 0x422c08e (pte)
   set 0x422c08e, %g2
   set 0x12c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=12, level=2,  ppnr=0x42300000, p_addr=0x130, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x130) = 0x423008e (pte)
   set 0x423008e, %g2
   set 0x130, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=13, level=2,  ppnr=0x42340000, p_addr=0x134, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x134) = 0x423408e (pte)
   set 0x423408e, %g2
   set 0x134, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=14, level=2,  ppnr=0x42380000, p_addr=0x138, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x138) = 0x423808e (pte)
   set 0x423808e, %g2
   set 0x138, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=15, level=2,  ppnr=0x423c0000, p_addr=0x13c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x13c) = 0x423c08e (pte)
   set 0x423c08e, %g2
   set 0x13c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=16, level=2,  ppnr=0x42400000, p_addr=0x140, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x140) = 0x424008e (pte)
   set 0x424008e, %g2
   set 0x140, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=17, level=2,  ppnr=0x42440000, p_addr=0x144, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x144) = 0x424408e (pte)
   set 0x424408e, %g2
   set 0x144, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=18, level=2,  ppnr=0x42480000, p_addr=0x148, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x148) = 0x424808e (pte)
   set 0x424808e, %g2
   set 0x148, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=19, level=2,  ppnr=0x424c0000, p_addr=0x14c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x14c) = 0x424c08e (pte)
   set 0x424c08e, %g2
   set 0x14c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=20, level=2,  ppnr=0x42500000, p_addr=0x150, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x150) = 0x425008e (pte)
   set 0x425008e, %g2
   set 0x150, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=21, level=2,  ppnr=0x42540000, p_addr=0x154, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x154) = 0x425408e (pte)
   set 0x425408e, %g2
   set 0x154, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=22, level=2,  ppnr=0x42580000, p_addr=0x158, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x158) = 0x425808e (pte)
   set 0x425808e, %g2
   set 0x158, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=23, level=2,  ppnr=0x425c0000, p_addr=0x15c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x15c) = 0x425c08e (pte)
   set 0x425c08e, %g2
   set 0x15c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=24, level=2,  ppnr=0x42600000, p_addr=0x160, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x160) = 0x426008e (pte)
   set 0x426008e, %g2
   set 0x160, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=25, level=2,  ppnr=0x42640000, p_addr=0x164, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x164) = 0x426408e (pte)
   set 0x426408e, %g2
   set 0x164, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=26, level=2,  ppnr=0x42680000, p_addr=0x168, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x168) = 0x426808e (pte)
   set 0x426808e, %g2
   set 0x168, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=27, level=2,  ppnr=0x426c0000, p_addr=0x16c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x16c) = 0x426c08e (pte)
   set 0x426c08e, %g2
   set 0x16c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=28, level=2,  ppnr=0x42700000, p_addr=0x170, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x170) = 0x427008e (pte)
   set 0x427008e, %g2
   set 0x170, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=29, level=2,  ppnr=0x42740000, p_addr=0x174, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x174) = 0x427408e (pte)
   set 0x427408e, %g2
   set 0x174, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=30, level=2,  ppnr=0x42780000, p_addr=0x178, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x178) = 0x427808e (pte)
   set 0x427808e, %g2
   set 0x178, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=31, level=2,  ppnr=0x427c0000, p_addr=0x17c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x17c) = 0x427c08e (pte)
   set 0x427c08e, %g2
   set 0x17c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=32, level=2,  ppnr=0x42800000, p_addr=0x180, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x180) = 0x428008e (pte)
   set 0x428008e, %g2
   set 0x180, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=33, level=2,  ppnr=0x42840000, p_addr=0x184, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x184) = 0x428408e (pte)
   set 0x428408e, %g2
   set 0x184, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=34, level=2,  ppnr=0x42880000, p_addr=0x188, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x188) = 0x428808e (pte)
   set 0x428808e, %g2
   set 0x188, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=35, level=2,  ppnr=0x428c0000, p_addr=0x18c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x18c) = 0x428c08e (pte)
   set 0x428c08e, %g2
   set 0x18c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=36, level=2,  ppnr=0x42900000, p_addr=0x190, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x190) = 0x429008e (pte)
   set 0x429008e, %g2
   set 0x190, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=37, level=2,  ppnr=0x42940000, p_addr=0x194, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x194) = 0x429408e (pte)
   set 0x429408e, %g2
   set 0x194, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=38, level=2,  ppnr=0x42980000, p_addr=0x198, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x198) = 0x429808e (pte)
   set 0x429808e, %g2
   set 0x198, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=39, level=2,  ppnr=0x429c0000, p_addr=0x19c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x19c) = 0x429c08e (pte)
   set 0x429c08e, %g2
   set 0x19c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=40, level=2,  ppnr=0x42a00000, p_addr=0x1a0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1a0) = 0x42a008e (pte)
   set 0x42a008e, %g2
   set 0x1a0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=41, level=2,  ppnr=0x42a40000, p_addr=0x1a4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1a4) = 0x42a408e (pte)
   set 0x42a408e, %g2
   set 0x1a4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=42, level=2,  ppnr=0x42a80000, p_addr=0x1a8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1a8) = 0x42a808e (pte)
   set 0x42a808e, %g2
   set 0x1a8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=43, level=2,  ppnr=0x42ac0000, p_addr=0x1ac, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1ac) = 0x42ac08e (pte)
   set 0x42ac08e, %g2
   set 0x1ac, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=44, level=2,  ppnr=0x42b00000, p_addr=0x1b0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1b0) = 0x42b008e (pte)
   set 0x42b008e, %g2
   set 0x1b0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=45, level=2,  ppnr=0x42b40000, p_addr=0x1b4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1b4) = 0x42b408e (pte)
   set 0x42b408e, %g2
   set 0x1b4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=46, level=2,  ppnr=0x42b80000, p_addr=0x1b8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1b8) = 0x42b808e (pte)
   set 0x42b808e, %g2
   set 0x1b8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=47, level=2,  ppnr=0x42bc0000, p_addr=0x1bc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1bc) = 0x42bc08e (pte)
   set 0x42bc08e, %g2
   set 0x1bc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=48, level=2,  ppnr=0x42c00000, p_addr=0x1c0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1c0) = 0x42c008e (pte)
   set 0x42c008e, %g2
   set 0x1c0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=49, level=2,  ppnr=0x42c40000, p_addr=0x1c4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1c4) = 0x42c408e (pte)
   set 0x42c408e, %g2
   set 0x1c4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=50, level=2,  ppnr=0x42c80000, p_addr=0x1c8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1c8) = 0x42c808e (pte)
   set 0x42c808e, %g2
   set 0x1c8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=51, level=2,  ppnr=0x42cc0000, p_addr=0x1cc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1cc) = 0x42cc08e (pte)
   set 0x42cc08e, %g2
   set 0x1cc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=52, level=2,  ppnr=0x42d00000, p_addr=0x1d0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1d0) = 0x42d008e (pte)
   set 0x42d008e, %g2
   set 0x1d0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=53, level=2,  ppnr=0x42d40000, p_addr=0x1d4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1d4) = 0x42d408e (pte)
   set 0x42d408e, %g2
   set 0x1d4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=54, level=2,  ppnr=0x42d80000, p_addr=0x1d8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1d8) = 0x42d808e (pte)
   set 0x42d808e, %g2
   set 0x1d8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=55, level=2,  ppnr=0x42dc0000, p_addr=0x1dc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1dc) = 0x42dc08e (pte)
   set 0x42dc08e, %g2
   set 0x1dc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=56, level=2,  ppnr=0x42e00000, p_addr=0x1e0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1e0) = 0x42e008e (pte)
   set 0x42e008e, %g2
   set 0x1e0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=57, level=2,  ppnr=0x42e40000, p_addr=0x1e4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1e4) = 0x42e408e (pte)
   set 0x42e408e, %g2
   set 0x1e4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=58, level=2,  ppnr=0x42e80000, p_addr=0x1e8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1e8) = 0x42e808e (pte)
   set 0x42e808e, %g2
   set 0x1e8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=59, level=2,  ppnr=0x42ec0000, p_addr=0x1ec, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1ec) = 0x42ec08e (pte)
   set 0x42ec08e, %g2
   set 0x1ec, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=60, level=2,  ppnr=0x42f00000, p_addr=0x1f0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1f0) = 0x42f008e (pte)
   set 0x42f008e, %g2
   set 0x1f0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=61, level=2,  ppnr=0x42f40000, p_addr=0x1f4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1f4) = 0x42f408e (pte)
   set 0x42f408e, %g2
   set 0x1f4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=62, level=2,  ppnr=0x42f80000, p_addr=0x1f8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1f8) = 0x42f808e (pte)
   set 0x42f808e, %g2
   set 0x1f8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=63, level=2,  ppnr=0x42fc0000, p_addr=0x1fc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x1fc) = 0x42fc08e (pte)
   set 0x42fc08e, %g2
   set 0x1fc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTD: context=0, index=67, level=1, child_p_addr=0x300, p_addr=0xd0c
   ! *(PAGE_TABLE_BASE + 0xd0c) = ptd(PAGE_TABLE_BASE + 0x300)
   ! make PTD from 0x300
   set 0x300, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0xd0c, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=0, level=2,  ppnr=0x43000000, p_addr=0x300, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x300) = 0x430008e (pte)
   set 0x430008e, %g2
   set 0x300, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=1, level=2,  ppnr=0x43040000, p_addr=0x304, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x304) = 0x430408e (pte)
   set 0x430408e, %g2
   set 0x304, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=2, level=2,  ppnr=0x43080000, p_addr=0x308, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x308) = 0x430808e (pte)
   set 0x430808e, %g2
   set 0x308, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=3, level=2,  ppnr=0x430c0000, p_addr=0x30c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x30c) = 0x430c08e (pte)
   set 0x430c08e, %g2
   set 0x30c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=4, level=2,  ppnr=0x43100000, p_addr=0x310, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x310) = 0x431008e (pte)
   set 0x431008e, %g2
   set 0x310, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=5, level=2,  ppnr=0x43140000, p_addr=0x314, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x314) = 0x431408e (pte)
   set 0x431408e, %g2
   set 0x314, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=6, level=2,  ppnr=0x43180000, p_addr=0x318, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x318) = 0x431808e (pte)
   set 0x431808e, %g2
   set 0x318, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=7, level=2,  ppnr=0x431c0000, p_addr=0x31c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x31c) = 0x431c08e (pte)
   set 0x431c08e, %g2
   set 0x31c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=8, level=2,  ppnr=0x43200000, p_addr=0x320, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x320) = 0x432008e (pte)
   set 0x432008e, %g2
   set 0x320, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=9, level=2,  ppnr=0x43240000, p_addr=0x324, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x324) = 0x432408e (pte)
   set 0x432408e, %g2
   set 0x324, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=10, level=2,  ppnr=0x43280000, p_addr=0x328, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x328) = 0x432808e (pte)
   set 0x432808e, %g2
   set 0x328, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=11, level=2,  ppnr=0x432c0000, p_addr=0x32c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x32c) = 0x432c08e (pte)
   set 0x432c08e, %g2
   set 0x32c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=12, level=2,  ppnr=0x43300000, p_addr=0x330, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x330) = 0x433008e (pte)
   set 0x433008e, %g2
   set 0x330, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=13, level=2,  ppnr=0x43340000, p_addr=0x334, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x334) = 0x433408e (pte)
   set 0x433408e, %g2
   set 0x334, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=14, level=2,  ppnr=0x43380000, p_addr=0x338, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x338) = 0x433808e (pte)
   set 0x433808e, %g2
   set 0x338, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=15, level=2,  ppnr=0x433c0000, p_addr=0x33c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x33c) = 0x433c08e (pte)
   set 0x433c08e, %g2
   set 0x33c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=16, level=2,  ppnr=0x43400000, p_addr=0x340, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x340) = 0x434008e (pte)
   set 0x434008e, %g2
   set 0x340, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=17, level=2,  ppnr=0x43440000, p_addr=0x344, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x344) = 0x434408e (pte)
   set 0x434408e, %g2
   set 0x344, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=18, level=2,  ppnr=0x43480000, p_addr=0x348, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x348) = 0x434808e (pte)
   set 0x434808e, %g2
   set 0x348, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=19, level=2,  ppnr=0x434c0000, p_addr=0x34c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x34c) = 0x434c08e (pte)
   set 0x434c08e, %g2
   set 0x34c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTD: context=0, index=20, level=2, child_p_addr=0x200, p_addr=0x350
   ! *(PAGE_TABLE_BASE + 0x350) = ptd(PAGE_TABLE_BASE + 0x200)
   ! make PTD from 0x200
   set 0x200, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x350, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=0, level=3,  ppnr=0x43500000, p_addr=0x200, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x200) = 0x435008e (pte)
   set 0x435008e, %g2
   set 0x200, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=1, level=3,  ppnr=0x43501000, p_addr=0x204, cacheable=0x0, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x204) = 0x435010e (pte)
   set 0x435010e, %g2
   set 0x204, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=2, level=3,  ppnr=0x43502000, p_addr=0x208, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x208) = 0x435028e (pte)
   set 0x435028e, %g2
   set 0x208, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=3, level=3,  ppnr=0x43503000, p_addr=0x20c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x20c) = 0x435038e (pte)
   set 0x435038e, %g2
   set 0x20c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=4, level=3,  ppnr=0x43504000, p_addr=0x210, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x210) = 0x435048e (pte)
   set 0x435048e, %g2
   set 0x210, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=5, level=3,  ppnr=0x43505000, p_addr=0x214, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x214) = 0x435058e (pte)
   set 0x435058e, %g2
   set 0x214, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=6, level=3,  ppnr=0x43506000, p_addr=0x218, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x218) = 0x435068e (pte)
   set 0x435068e, %g2
   set 0x218, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=7, level=3,  ppnr=0x43507000, p_addr=0x21c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x21c) = 0x435078e (pte)
   set 0x435078e, %g2
   set 0x21c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=8, level=3,  ppnr=0x43508000, p_addr=0x220, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x220) = 0x435088e (pte)
   set 0x435088e, %g2
   set 0x220, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=9, level=3,  ppnr=0x43509000, p_addr=0x224, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x224) = 0x435098e (pte)
   set 0x435098e, %g2
   set 0x224, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=10, level=3,  ppnr=0x4350a000, p_addr=0x228, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x228) = 0x4350a8e (pte)
   set 0x4350a8e, %g2
   set 0x228, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=11, level=3,  ppnr=0x4350b000, p_addr=0x22c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x22c) = 0x4350b8e (pte)
   set 0x4350b8e, %g2
   set 0x22c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=12, level=3,  ppnr=0x4350c000, p_addr=0x230, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x230) = 0x4350c8e (pte)
   set 0x4350c8e, %g2
   set 0x230, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=13, level=3,  ppnr=0x4350d000, p_addr=0x234, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x234) = 0x4350d8e (pte)
   set 0x4350d8e, %g2
   set 0x234, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=14, level=3,  ppnr=0x4350e000, p_addr=0x238, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x238) = 0x4350e8e (pte)
   set 0x4350e8e, %g2
   set 0x238, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=15, level=3,  ppnr=0x4350f000, p_addr=0x23c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x23c) = 0x4350f8e (pte)
   set 0x4350f8e, %g2
   set 0x23c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=16, level=3,  ppnr=0x43510000, p_addr=0x240, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x240) = 0x435108e (pte)
   set 0x435108e, %g2
   set 0x240, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=17, level=3,  ppnr=0x43511000, p_addr=0x244, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x244) = 0x435118e (pte)
   set 0x435118e, %g2
   set 0x244, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=18, level=3,  ppnr=0x43512000, p_addr=0x248, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x248) = 0x435128e (pte)
   set 0x435128e, %g2
   set 0x248, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=19, level=3,  ppnr=0x43513000, p_addr=0x24c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x24c) = 0x435138e (pte)
   set 0x435138e, %g2
   set 0x24c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=20, level=3,  ppnr=0x43514000, p_addr=0x250, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x250) = 0x435148e (pte)
   set 0x435148e, %g2
   set 0x250, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=21, level=3,  ppnr=0x43515000, p_addr=0x254, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x254) = 0x435158e (pte)
   set 0x435158e, %g2
   set 0x254, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=22, level=3,  ppnr=0x43516000, p_addr=0x258, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x258) = 0x435168e (pte)
   set 0x435168e, %g2
   set 0x258, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=23, level=3,  ppnr=0x43517000, p_addr=0x25c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x25c) = 0x435178e (pte)
   set 0x435178e, %g2
   set 0x25c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=24, level=3,  ppnr=0x43518000, p_addr=0x260, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x260) = 0x435188e (pte)
   set 0x435188e, %g2
   set 0x260, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=25, level=3,  ppnr=0x43519000, p_addr=0x264, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x264) = 0x435198e (pte)
   set 0x435198e, %g2
   set 0x264, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=26, level=3,  ppnr=0x4351a000, p_addr=0x268, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x268) = 0x4351a8e (pte)
   set 0x4351a8e, %g2
   set 0x268, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=27, level=3,  ppnr=0x4351b000, p_addr=0x26c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x26c) = 0x4351b8e (pte)
   set 0x4351b8e, %g2
   set 0x26c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=28, level=3,  ppnr=0x4351c000, p_addr=0x270, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x270) = 0x4351c8e (pte)
   set 0x4351c8e, %g2
   set 0x270, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=29, level=3,  ppnr=0x4351d000, p_addr=0x274, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x274) = 0x4351d8e (pte)
   set 0x4351d8e, %g2
   set 0x274, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=30, level=3,  ppnr=0x4351e000, p_addr=0x278, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x278) = 0x4351e8e (pte)
   set 0x4351e8e, %g2
   set 0x278, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=31, level=3,  ppnr=0x4351f000, p_addr=0x27c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x27c) = 0x4351f8e (pte)
   set 0x4351f8e, %g2
   set 0x27c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=32, level=3,  ppnr=0x43520000, p_addr=0x280, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x280) = 0x435208e (pte)
   set 0x435208e, %g2
   set 0x280, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=33, level=3,  ppnr=0x43521000, p_addr=0x284, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x284) = 0x435218e (pte)
   set 0x435218e, %g2
   set 0x284, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=34, level=3,  ppnr=0x43522000, p_addr=0x288, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x288) = 0x435228e (pte)
   set 0x435228e, %g2
   set 0x288, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=35, level=3,  ppnr=0x43523000, p_addr=0x28c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x28c) = 0x435238e (pte)
   set 0x435238e, %g2
   set 0x28c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=36, level=3,  ppnr=0x43524000, p_addr=0x290, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x290) = 0x435248e (pte)
   set 0x435248e, %g2
   set 0x290, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=37, level=3,  ppnr=0x43525000, p_addr=0x294, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x294) = 0x435258e (pte)
   set 0x435258e, %g2
   set 0x294, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=38, level=3,  ppnr=0x43526000, p_addr=0x298, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x298) = 0x435268e (pte)
   set 0x435268e, %g2
   set 0x298, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=39, level=3,  ppnr=0x43527000, p_addr=0x29c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x29c) = 0x435278e (pte)
   set 0x435278e, %g2
   set 0x29c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=40, level=3,  ppnr=0x43528000, p_addr=0x2a0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2a0) = 0x435288e (pte)
   set 0x435288e, %g2
   set 0x2a0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=41, level=3,  ppnr=0x43529000, p_addr=0x2a4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2a4) = 0x435298e (pte)
   set 0x435298e, %g2
   set 0x2a4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=42, level=3,  ppnr=0x4352a000, p_addr=0x2a8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2a8) = 0x4352a8e (pte)
   set 0x4352a8e, %g2
   set 0x2a8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=43, level=3,  ppnr=0x4352b000, p_addr=0x2ac, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2ac) = 0x4352b8e (pte)
   set 0x4352b8e, %g2
   set 0x2ac, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=44, level=3,  ppnr=0x4352c000, p_addr=0x2b0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2b0) = 0x4352c8e (pte)
   set 0x4352c8e, %g2
   set 0x2b0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=45, level=3,  ppnr=0x4352d000, p_addr=0x2b4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2b4) = 0x4352d8e (pte)
   set 0x4352d8e, %g2
   set 0x2b4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=46, level=3,  ppnr=0x4352e000, p_addr=0x2b8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2b8) = 0x4352e8e (pte)
   set 0x4352e8e, %g2
   set 0x2b8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=47, level=3,  ppnr=0x4352f000, p_addr=0x2bc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2bc) = 0x4352f8e (pte)
   set 0x4352f8e, %g2
   set 0x2bc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=48, level=3,  ppnr=0x43530000, p_addr=0x2c0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2c0) = 0x435308e (pte)
   set 0x435308e, %g2
   set 0x2c0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=49, level=3,  ppnr=0x43531000, p_addr=0x2c4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2c4) = 0x435318e (pte)
   set 0x435318e, %g2
   set 0x2c4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=50, level=3,  ppnr=0x43532000, p_addr=0x2c8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2c8) = 0x435328e (pte)
   set 0x435328e, %g2
   set 0x2c8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=51, level=3,  ppnr=0x43533000, p_addr=0x2cc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2cc) = 0x435338e (pte)
   set 0x435338e, %g2
   set 0x2cc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=52, level=3,  ppnr=0x43534000, p_addr=0x2d0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2d0) = 0x435348e (pte)
   set 0x435348e, %g2
   set 0x2d0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=53, level=3,  ppnr=0x43535000, p_addr=0x2d4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2d4) = 0x435358e (pte)
   set 0x435358e, %g2
   set 0x2d4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=54, level=3,  ppnr=0x43536000, p_addr=0x2d8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2d8) = 0x435368e (pte)
   set 0x435368e, %g2
   set 0x2d8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=55, level=3,  ppnr=0x43537000, p_addr=0x2dc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2dc) = 0x435378e (pte)
   set 0x435378e, %g2
   set 0x2dc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=56, level=3,  ppnr=0x43538000, p_addr=0x2e0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2e0) = 0x435388e (pte)
   set 0x435388e, %g2
   set 0x2e0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=57, level=3,  ppnr=0x43539000, p_addr=0x2e4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2e4) = 0x435398e (pte)
   set 0x435398e, %g2
   set 0x2e4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=58, level=3,  ppnr=0x4353a000, p_addr=0x2e8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2e8) = 0x4353a8e (pte)
   set 0x4353a8e, %g2
   set 0x2e8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=59, level=3,  ppnr=0x4353b000, p_addr=0x2ec, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2ec) = 0x4353b8e (pte)
   set 0x4353b8e, %g2
   set 0x2ec, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=60, level=3,  ppnr=0x4353c000, p_addr=0x2f0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2f0) = 0x4353c8e (pte)
   set 0x4353c8e, %g2
   set 0x2f0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=61, level=3,  ppnr=0x4353d000, p_addr=0x2f4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2f4) = 0x4353d8e (pte)
   set 0x4353d8e, %g2
   set 0x2f4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=62, level=3,  ppnr=0x4353e000, p_addr=0x2f8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2f8) = 0x4353e8e (pte)
   set 0x4353e8e, %g2
   set 0x2f8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=63, level=3,  ppnr=0x4353f000, p_addr=0x2fc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x2fc) = 0x4353f8e (pte)
   set 0x4353f8e, %g2
   set 0x2fc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=21, level=2,  ppnr=0x43540000, p_addr=0x354, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x354) = 0x435408e (pte)
   set 0x435408e, %g2
   set 0x354, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=22, level=2,  ppnr=0x43580000, p_addr=0x358, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x358) = 0x435808e (pte)
   set 0x435808e, %g2
   set 0x358, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=23, level=2,  ppnr=0x435c0000, p_addr=0x35c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x35c) = 0x435c08e (pte)
   set 0x435c08e, %g2
   set 0x35c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=24, level=2,  ppnr=0x43600000, p_addr=0x360, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x360) = 0x436008e (pte)
   set 0x436008e, %g2
   set 0x360, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=25, level=2,  ppnr=0x43640000, p_addr=0x364, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x364) = 0x436408e (pte)
   set 0x436408e, %g2
   set 0x364, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=26, level=2,  ppnr=0x43680000, p_addr=0x368, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x368) = 0x436808e (pte)
   set 0x436808e, %g2
   set 0x368, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=27, level=2,  ppnr=0x436c0000, p_addr=0x36c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x36c) = 0x436c08e (pte)
   set 0x436c08e, %g2
   set 0x36c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=28, level=2,  ppnr=0x43700000, p_addr=0x370, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x370) = 0x437008e (pte)
   set 0x437008e, %g2
   set 0x370, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=29, level=2,  ppnr=0x43740000, p_addr=0x374, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x374) = 0x437408e (pte)
   set 0x437408e, %g2
   set 0x374, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=30, level=2,  ppnr=0x43780000, p_addr=0x378, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x378) = 0x437808e (pte)
   set 0x437808e, %g2
   set 0x378, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=31, level=2,  ppnr=0x437c0000, p_addr=0x37c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x37c) = 0x437c08e (pte)
   set 0x437c08e, %g2
   set 0x37c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=32, level=2,  ppnr=0x43800000, p_addr=0x380, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x380) = 0x438008e (pte)
   set 0x438008e, %g2
   set 0x380, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=33, level=2,  ppnr=0x43840000, p_addr=0x384, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x384) = 0x438408e (pte)
   set 0x438408e, %g2
   set 0x384, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=34, level=2,  ppnr=0x43880000, p_addr=0x388, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x388) = 0x438808e (pte)
   set 0x438808e, %g2
   set 0x388, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=35, level=2,  ppnr=0x438c0000, p_addr=0x38c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x38c) = 0x438c08e (pte)
   set 0x438c08e, %g2
   set 0x38c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=36, level=2,  ppnr=0x43900000, p_addr=0x390, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x390) = 0x439008e (pte)
   set 0x439008e, %g2
   set 0x390, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=37, level=2,  ppnr=0x43940000, p_addr=0x394, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x394) = 0x439408e (pte)
   set 0x439408e, %g2
   set 0x394, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=38, level=2,  ppnr=0x43980000, p_addr=0x398, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x398) = 0x439808e (pte)
   set 0x439808e, %g2
   set 0x398, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=39, level=2,  ppnr=0x439c0000, p_addr=0x39c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x39c) = 0x439c08e (pte)
   set 0x439c08e, %g2
   set 0x39c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=40, level=2,  ppnr=0x43a00000, p_addr=0x3a0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3a0) = 0x43a008e (pte)
   set 0x43a008e, %g2
   set 0x3a0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=41, level=2,  ppnr=0x43a40000, p_addr=0x3a4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3a4) = 0x43a408e (pte)
   set 0x43a408e, %g2
   set 0x3a4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=42, level=2,  ppnr=0x43a80000, p_addr=0x3a8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3a8) = 0x43a808e (pte)
   set 0x43a808e, %g2
   set 0x3a8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=43, level=2,  ppnr=0x43ac0000, p_addr=0x3ac, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3ac) = 0x43ac08e (pte)
   set 0x43ac08e, %g2
   set 0x3ac, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=44, level=2,  ppnr=0x43b00000, p_addr=0x3b0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3b0) = 0x43b008e (pte)
   set 0x43b008e, %g2
   set 0x3b0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=45, level=2,  ppnr=0x43b40000, p_addr=0x3b4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3b4) = 0x43b408e (pte)
   set 0x43b408e, %g2
   set 0x3b4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=46, level=2,  ppnr=0x43b80000, p_addr=0x3b8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3b8) = 0x43b808e (pte)
   set 0x43b808e, %g2
   set 0x3b8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=47, level=2,  ppnr=0x43bc0000, p_addr=0x3bc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3bc) = 0x43bc08e (pte)
   set 0x43bc08e, %g2
   set 0x3bc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=48, level=2,  ppnr=0x43c00000, p_addr=0x3c0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3c0) = 0x43c008e (pte)
   set 0x43c008e, %g2
   set 0x3c0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=49, level=2,  ppnr=0x43c40000, p_addr=0x3c4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3c4) = 0x43c408e (pte)
   set 0x43c408e, %g2
   set 0x3c4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=50, level=2,  ppnr=0x43c80000, p_addr=0x3c8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3c8) = 0x43c808e (pte)
   set 0x43c808e, %g2
   set 0x3c8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=51, level=2,  ppnr=0x43cc0000, p_addr=0x3cc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3cc) = 0x43cc08e (pte)
   set 0x43cc08e, %g2
   set 0x3cc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=52, level=2,  ppnr=0x43d00000, p_addr=0x3d0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3d0) = 0x43d008e (pte)
   set 0x43d008e, %g2
   set 0x3d0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=53, level=2,  ppnr=0x43d40000, p_addr=0x3d4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3d4) = 0x43d408e (pte)
   set 0x43d408e, %g2
   set 0x3d4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=54, level=2,  ppnr=0x43d80000, p_addr=0x3d8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3d8) = 0x43d808e (pte)
   set 0x43d808e, %g2
   set 0x3d8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=55, level=2,  ppnr=0x43dc0000, p_addr=0x3dc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3dc) = 0x43dc08e (pte)
   set 0x43dc08e, %g2
   set 0x3dc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=56, level=2,  ppnr=0x43e00000, p_addr=0x3e0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3e0) = 0x43e008e (pte)
   set 0x43e008e, %g2
   set 0x3e0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=57, level=2,  ppnr=0x43e40000, p_addr=0x3e4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3e4) = 0x43e408e (pte)
   set 0x43e408e, %g2
   set 0x3e4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=58, level=2,  ppnr=0x43e80000, p_addr=0x3e8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3e8) = 0x43e808e (pte)
   set 0x43e808e, %g2
   set 0x3e8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=59, level=2,  ppnr=0x43ec0000, p_addr=0x3ec, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3ec) = 0x43ec08e (pte)
   set 0x43ec08e, %g2
   set 0x3ec, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=60, level=2,  ppnr=0x43f00000, p_addr=0x3f0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3f0) = 0x43f008e (pte)
   set 0x43f008e, %g2
   set 0x3f0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=61, level=2,  ppnr=0x43f40000, p_addr=0x3f4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3f4) = 0x43f408e (pte)
   set 0x43f408e, %g2
   set 0x3f4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=62, level=2,  ppnr=0x43f80000, p_addr=0x3f8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3f8) = 0x43f808e (pte)
   set 0x43f808e, %g2
   set 0x3f8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=63, level=2,  ppnr=0x43fc0000, p_addr=0x3fc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x3fc) = 0x43fc08e (pte)
   set 0x43fc08e, %g2
   set 0x3fc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=68, level=1,  ppnr=0x44000000, p_addr=0xd10, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xd10) = 0x440008e (pte)
   set 0x440008e, %g2
   set 0xd10, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=69, level=1,  ppnr=0x45000000, p_addr=0xd14, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xd14) = 0x450008e (pte)
   set 0x450008e, %g2
   set 0xd14, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTD: context=0, index=70, level=1, child_p_addr=0x500, p_addr=0xd18
   ! *(PAGE_TABLE_BASE + 0xd18) = ptd(PAGE_TABLE_BASE + 0x500)
   ! make PTD from 0x500
   set 0x500, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0xd18, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=0, level=2,  ppnr=0x46000000, p_addr=0x500, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x500) = 0x460008e (pte)
   set 0x460008e, %g2
   set 0x500, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=1, level=2,  ppnr=0x46040000, p_addr=0x504, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x504) = 0x460408e (pte)
   set 0x460408e, %g2
   set 0x504, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=2, level=2,  ppnr=0x46080000, p_addr=0x508, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x508) = 0x460808e (pte)
   set 0x460808e, %g2
   set 0x508, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=3, level=2,  ppnr=0x460c0000, p_addr=0x50c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x50c) = 0x460c08e (pte)
   set 0x460c08e, %g2
   set 0x50c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=4, level=2,  ppnr=0x46100000, p_addr=0x510, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x510) = 0x461008e (pte)
   set 0x461008e, %g2
   set 0x510, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=5, level=2,  ppnr=0x46140000, p_addr=0x514, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x514) = 0x461408e (pte)
   set 0x461408e, %g2
   set 0x514, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=6, level=2,  ppnr=0x46180000, p_addr=0x518, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x518) = 0x461808e (pte)
   set 0x461808e, %g2
   set 0x518, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=7, level=2,  ppnr=0x461c0000, p_addr=0x51c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x51c) = 0x461c08e (pte)
   set 0x461c08e, %g2
   set 0x51c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=8, level=2,  ppnr=0x46200000, p_addr=0x520, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x520) = 0x462008e (pte)
   set 0x462008e, %g2
   set 0x520, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=9, level=2,  ppnr=0x46240000, p_addr=0x524, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x524) = 0x462408e (pte)
   set 0x462408e, %g2
   set 0x524, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=10, level=2,  ppnr=0x46280000, p_addr=0x528, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x528) = 0x462808e (pte)
   set 0x462808e, %g2
   set 0x528, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=11, level=2,  ppnr=0x462c0000, p_addr=0x52c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x52c) = 0x462c08e (pte)
   set 0x462c08e, %g2
   set 0x52c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=12, level=2,  ppnr=0x46300000, p_addr=0x530, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x530) = 0x463008e (pte)
   set 0x463008e, %g2
   set 0x530, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=13, level=2,  ppnr=0x46340000, p_addr=0x534, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x534) = 0x463408e (pte)
   set 0x463408e, %g2
   set 0x534, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=14, level=2,  ppnr=0x46380000, p_addr=0x538, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x538) = 0x463808e (pte)
   set 0x463808e, %g2
   set 0x538, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=15, level=2,  ppnr=0x463c0000, p_addr=0x53c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x53c) = 0x463c08e (pte)
   set 0x463c08e, %g2
   set 0x53c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=16, level=2,  ppnr=0x46400000, p_addr=0x540, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x540) = 0x464008e (pte)
   set 0x464008e, %g2
   set 0x540, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=17, level=2,  ppnr=0x46440000, p_addr=0x544, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x544) = 0x464408e (pte)
   set 0x464408e, %g2
   set 0x544, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=18, level=2,  ppnr=0x46480000, p_addr=0x548, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x548) = 0x464808e (pte)
   set 0x464808e, %g2
   set 0x548, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=19, level=2,  ppnr=0x464c0000, p_addr=0x54c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x54c) = 0x464c08e (pte)
   set 0x464c08e, %g2
   set 0x54c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=20, level=2,  ppnr=0x46500000, p_addr=0x550, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x550) = 0x465008e (pte)
   set 0x465008e, %g2
   set 0x550, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=21, level=2,  ppnr=0x46540000, p_addr=0x554, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x554) = 0x465408e (pte)
   set 0x465408e, %g2
   set 0x554, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=22, level=2,  ppnr=0x46580000, p_addr=0x558, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x558) = 0x465808e (pte)
   set 0x465808e, %g2
   set 0x558, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTD: context=0, index=23, level=2, child_p_addr=0x400, p_addr=0x55c
   ! *(PAGE_TABLE_BASE + 0x55c) = ptd(PAGE_TABLE_BASE + 0x400)
   ! make PTD from 0x400
   set 0x400, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x55c, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=0, level=3,  ppnr=0x465c0000, p_addr=0x400, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x400) = 0x465c08e (pte)
   set 0x465c08e, %g2
   set 0x400, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=1, level=3,  ppnr=0x465c1000, p_addr=0x404, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x404) = 0x465c18e (pte)
   set 0x465c18e, %g2
   set 0x404, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=2, level=3,  ppnr=0x465c2000, p_addr=0x408, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x408) = 0x465c28e (pte)
   set 0x465c28e, %g2
   set 0x408, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=3, level=3,  ppnr=0x465c3000, p_addr=0x40c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x40c) = 0x465c38e (pte)
   set 0x465c38e, %g2
   set 0x40c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=4, level=3,  ppnr=0x465c4000, p_addr=0x410, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x410) = 0x465c48e (pte)
   set 0x465c48e, %g2
   set 0x410, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=5, level=3,  ppnr=0x465c5000, p_addr=0x414, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x414) = 0x465c58e (pte)
   set 0x465c58e, %g2
   set 0x414, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=6, level=3,  ppnr=0x465c6000, p_addr=0x418, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x418) = 0x465c68e (pte)
   set 0x465c68e, %g2
   set 0x418, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=7, level=3,  ppnr=0x465c7000, p_addr=0x41c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x41c) = 0x465c78e (pte)
   set 0x465c78e, %g2
   set 0x41c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=8, level=3,  ppnr=0x465c8000, p_addr=0x420, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x420) = 0x465c88e (pte)
   set 0x465c88e, %g2
   set 0x420, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=9, level=3,  ppnr=0x465c9000, p_addr=0x424, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x424) = 0x465c98e (pte)
   set 0x465c98e, %g2
   set 0x424, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=10, level=3,  ppnr=0x465ca000, p_addr=0x428, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x428) = 0x465ca8e (pte)
   set 0x465ca8e, %g2
   set 0x428, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=11, level=3,  ppnr=0x465cb000, p_addr=0x42c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x42c) = 0x465cb8e (pte)
   set 0x465cb8e, %g2
   set 0x42c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=12, level=3,  ppnr=0x465cc000, p_addr=0x430, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x430) = 0x465cc8e (pte)
   set 0x465cc8e, %g2
   set 0x430, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=13, level=3,  ppnr=0x465cd000, p_addr=0x434, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x434) = 0x465cd8e (pte)
   set 0x465cd8e, %g2
   set 0x434, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=14, level=3,  ppnr=0x465ce000, p_addr=0x438, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x438) = 0x465ce8e (pte)
   set 0x465ce8e, %g2
   set 0x438, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=15, level=3,  ppnr=0x465cf000, p_addr=0x43c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x43c) = 0x465cf8e (pte)
   set 0x465cf8e, %g2
   set 0x43c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=16, level=3,  ppnr=0x465d0000, p_addr=0x440, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x440) = 0x465d08e (pte)
   set 0x465d08e, %g2
   set 0x440, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=17, level=3,  ppnr=0x465d1000, p_addr=0x444, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x444) = 0x465d18e (pte)
   set 0x465d18e, %g2
   set 0x444, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=18, level=3,  ppnr=0x465d2000, p_addr=0x448, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x448) = 0x465d28e (pte)
   set 0x465d28e, %g2
   set 0x448, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=19, level=3,  ppnr=0x465d3000, p_addr=0x44c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x44c) = 0x465d38e (pte)
   set 0x465d38e, %g2
   set 0x44c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=20, level=3,  ppnr=0x465d4000, p_addr=0x450, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x450) = 0x465d48e (pte)
   set 0x465d48e, %g2
   set 0x450, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=21, level=3,  ppnr=0x465d5000, p_addr=0x454, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x454) = 0x465d58e (pte)
   set 0x465d58e, %g2
   set 0x454, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=22, level=3,  ppnr=0x465d6000, p_addr=0x458, cacheable=0x1, acc=0x4
   ! *(PAGE_TABLE_BASE + 0x458) = 0x465d692 (pte)
   set 0x465d692, %g2
   set 0x458, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=23, level=3,  ppnr=0x465d7000, p_addr=0x45c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x45c) = 0x465d78e (pte)
   set 0x465d78e, %g2
   set 0x45c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=24, level=3,  ppnr=0x465d8000, p_addr=0x460, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x460) = 0x465d88e (pte)
   set 0x465d88e, %g2
   set 0x460, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=25, level=3,  ppnr=0x465d9000, p_addr=0x464, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x464) = 0x465d98e (pte)
   set 0x465d98e, %g2
   set 0x464, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=26, level=3,  ppnr=0x465da000, p_addr=0x468, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x468) = 0x465da8e (pte)
   set 0x465da8e, %g2
   set 0x468, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=27, level=3,  ppnr=0x465db000, p_addr=0x46c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x46c) = 0x465db8e (pte)
   set 0x465db8e, %g2
   set 0x46c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=28, level=3,  ppnr=0x465dc000, p_addr=0x470, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x470) = 0x465dc8e (pte)
   set 0x465dc8e, %g2
   set 0x470, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=29, level=3,  ppnr=0x465dd000, p_addr=0x474, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x474) = 0x465dd8e (pte)
   set 0x465dd8e, %g2
   set 0x474, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=30, level=3,  ppnr=0x465de000, p_addr=0x478, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x478) = 0x465de8e (pte)
   set 0x465de8e, %g2
   set 0x478, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=31, level=3,  ppnr=0x465df000, p_addr=0x47c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x47c) = 0x465df8e (pte)
   set 0x465df8e, %g2
   set 0x47c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=32, level=3,  ppnr=0x465e0000, p_addr=0x480, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x480) = 0x465e08e (pte)
   set 0x465e08e, %g2
   set 0x480, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=33, level=3,  ppnr=0x465e1000, p_addr=0x484, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x484) = 0x465e18e (pte)
   set 0x465e18e, %g2
   set 0x484, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=34, level=3,  ppnr=0x465e2000, p_addr=0x488, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x488) = 0x465e28e (pte)
   set 0x465e28e, %g2
   set 0x488, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=35, level=3,  ppnr=0x465e3000, p_addr=0x48c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x48c) = 0x465e38e (pte)
   set 0x465e38e, %g2
   set 0x48c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=36, level=3,  ppnr=0x465e4000, p_addr=0x490, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x490) = 0x465e48e (pte)
   set 0x465e48e, %g2
   set 0x490, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=37, level=3,  ppnr=0x465e5000, p_addr=0x494, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x494) = 0x465e58e (pte)
   set 0x465e58e, %g2
   set 0x494, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=38, level=3,  ppnr=0x465e6000, p_addr=0x498, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x498) = 0x465e68e (pte)
   set 0x465e68e, %g2
   set 0x498, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=39, level=3,  ppnr=0x465e7000, p_addr=0x49c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x49c) = 0x465e78e (pte)
   set 0x465e78e, %g2
   set 0x49c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=40, level=3,  ppnr=0x465e8000, p_addr=0x4a0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4a0) = 0x465e88e (pte)
   set 0x465e88e, %g2
   set 0x4a0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=41, level=3,  ppnr=0x465e9000, p_addr=0x4a4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4a4) = 0x465e98e (pte)
   set 0x465e98e, %g2
   set 0x4a4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=42, level=3,  ppnr=0x465ea000, p_addr=0x4a8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4a8) = 0x465ea8e (pte)
   set 0x465ea8e, %g2
   set 0x4a8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=43, level=3,  ppnr=0x465eb000, p_addr=0x4ac, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4ac) = 0x465eb8e (pte)
   set 0x465eb8e, %g2
   set 0x4ac, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=44, level=3,  ppnr=0x465ec000, p_addr=0x4b0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4b0) = 0x465ec8e (pte)
   set 0x465ec8e, %g2
   set 0x4b0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=45, level=3,  ppnr=0x465ed000, p_addr=0x4b4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4b4) = 0x465ed8e (pte)
   set 0x465ed8e, %g2
   set 0x4b4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=46, level=3,  ppnr=0x465ee000, p_addr=0x4b8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4b8) = 0x465ee8e (pte)
   set 0x465ee8e, %g2
   set 0x4b8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=47, level=3,  ppnr=0x465ef000, p_addr=0x4bc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4bc) = 0x465ef8e (pte)
   set 0x465ef8e, %g2
   set 0x4bc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=48, level=3,  ppnr=0x465f0000, p_addr=0x4c0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4c0) = 0x465f08e (pte)
   set 0x465f08e, %g2
   set 0x4c0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=49, level=3,  ppnr=0x465f1000, p_addr=0x4c4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4c4) = 0x465f18e (pte)
   set 0x465f18e, %g2
   set 0x4c4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=50, level=3,  ppnr=0x465f2000, p_addr=0x4c8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4c8) = 0x465f28e (pte)
   set 0x465f28e, %g2
   set 0x4c8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=51, level=3,  ppnr=0x465f3000, p_addr=0x4cc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4cc) = 0x465f38e (pte)
   set 0x465f38e, %g2
   set 0x4cc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=52, level=3,  ppnr=0x465f4000, p_addr=0x4d0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4d0) = 0x465f48e (pte)
   set 0x465f48e, %g2
   set 0x4d0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=53, level=3,  ppnr=0x465f5000, p_addr=0x4d4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4d4) = 0x465f58e (pte)
   set 0x465f58e, %g2
   set 0x4d4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=54, level=3,  ppnr=0x465f6000, p_addr=0x4d8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4d8) = 0x465f68e (pte)
   set 0x465f68e, %g2
   set 0x4d8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=55, level=3,  ppnr=0x465f7000, p_addr=0x4dc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4dc) = 0x465f78e (pte)
   set 0x465f78e, %g2
   set 0x4dc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=56, level=3,  ppnr=0x465f8000, p_addr=0x4e0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4e0) = 0x465f88e (pte)
   set 0x465f88e, %g2
   set 0x4e0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=57, level=3,  ppnr=0x465f9000, p_addr=0x4e4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4e4) = 0x465f98e (pte)
   set 0x465f98e, %g2
   set 0x4e4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=58, level=3,  ppnr=0x465fa000, p_addr=0x4e8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4e8) = 0x465fa8e (pte)
   set 0x465fa8e, %g2
   set 0x4e8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=59, level=3,  ppnr=0x465fb000, p_addr=0x4ec, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4ec) = 0x465fb8e (pte)
   set 0x465fb8e, %g2
   set 0x4ec, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=60, level=3,  ppnr=0x465fc000, p_addr=0x4f0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4f0) = 0x465fc8e (pte)
   set 0x465fc8e, %g2
   set 0x4f0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=61, level=3,  ppnr=0x465fd000, p_addr=0x4f4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4f4) = 0x465fd8e (pte)
   set 0x465fd8e, %g2
   set 0x4f4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=62, level=3,  ppnr=0x465fe000, p_addr=0x4f8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4f8) = 0x465fe8e (pte)
   set 0x465fe8e, %g2
   set 0x4f8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=63, level=3,  ppnr=0x465ff000, p_addr=0x4fc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x4fc) = 0x465ff8e (pte)
   set 0x465ff8e, %g2
   set 0x4fc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=24, level=2,  ppnr=0x46600000, p_addr=0x560, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x560) = 0x466008e (pte)
   set 0x466008e, %g2
   set 0x560, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=25, level=2,  ppnr=0x46640000, p_addr=0x564, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x564) = 0x466408e (pte)
   set 0x466408e, %g2
   set 0x564, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=26, level=2,  ppnr=0x46680000, p_addr=0x568, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x568) = 0x466808e (pte)
   set 0x466808e, %g2
   set 0x568, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=27, level=2,  ppnr=0x466c0000, p_addr=0x56c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x56c) = 0x466c08e (pte)
   set 0x466c08e, %g2
   set 0x56c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=28, level=2,  ppnr=0x46700000, p_addr=0x570, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x570) = 0x467008e (pte)
   set 0x467008e, %g2
   set 0x570, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=29, level=2,  ppnr=0x46740000, p_addr=0x574, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x574) = 0x467408e (pte)
   set 0x467408e, %g2
   set 0x574, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=30, level=2,  ppnr=0x46780000, p_addr=0x578, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x578) = 0x467808e (pte)
   set 0x467808e, %g2
   set 0x578, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=31, level=2,  ppnr=0x467c0000, p_addr=0x57c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x57c) = 0x467c08e (pte)
   set 0x467c08e, %g2
   set 0x57c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=32, level=2,  ppnr=0x46800000, p_addr=0x580, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x580) = 0x468008e (pte)
   set 0x468008e, %g2
   set 0x580, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=33, level=2,  ppnr=0x46840000, p_addr=0x584, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x584) = 0x468408e (pte)
   set 0x468408e, %g2
   set 0x584, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=34, level=2,  ppnr=0x46880000, p_addr=0x588, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x588) = 0x468808e (pte)
   set 0x468808e, %g2
   set 0x588, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=35, level=2,  ppnr=0x468c0000, p_addr=0x58c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x58c) = 0x468c08e (pte)
   set 0x468c08e, %g2
   set 0x58c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=36, level=2,  ppnr=0x46900000, p_addr=0x590, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x590) = 0x469008e (pte)
   set 0x469008e, %g2
   set 0x590, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=37, level=2,  ppnr=0x46940000, p_addr=0x594, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x594) = 0x469408e (pte)
   set 0x469408e, %g2
   set 0x594, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=38, level=2,  ppnr=0x46980000, p_addr=0x598, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x598) = 0x469808e (pte)
   set 0x469808e, %g2
   set 0x598, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=39, level=2,  ppnr=0x469c0000, p_addr=0x59c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x59c) = 0x469c08e (pte)
   set 0x469c08e, %g2
   set 0x59c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=40, level=2,  ppnr=0x46a00000, p_addr=0x5a0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5a0) = 0x46a008e (pte)
   set 0x46a008e, %g2
   set 0x5a0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=41, level=2,  ppnr=0x46a40000, p_addr=0x5a4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5a4) = 0x46a408e (pte)
   set 0x46a408e, %g2
   set 0x5a4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=42, level=2,  ppnr=0x46a80000, p_addr=0x5a8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5a8) = 0x46a808e (pte)
   set 0x46a808e, %g2
   set 0x5a8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=43, level=2,  ppnr=0x46ac0000, p_addr=0x5ac, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5ac) = 0x46ac08e (pte)
   set 0x46ac08e, %g2
   set 0x5ac, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=44, level=2,  ppnr=0x46b00000, p_addr=0x5b0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5b0) = 0x46b008e (pte)
   set 0x46b008e, %g2
   set 0x5b0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=45, level=2,  ppnr=0x46b40000, p_addr=0x5b4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5b4) = 0x46b408e (pte)
   set 0x46b408e, %g2
   set 0x5b4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=46, level=2,  ppnr=0x46b80000, p_addr=0x5b8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5b8) = 0x46b808e (pte)
   set 0x46b808e, %g2
   set 0x5b8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=47, level=2,  ppnr=0x46bc0000, p_addr=0x5bc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5bc) = 0x46bc08e (pte)
   set 0x46bc08e, %g2
   set 0x5bc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=48, level=2,  ppnr=0x46c00000, p_addr=0x5c0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5c0) = 0x46c008e (pte)
   set 0x46c008e, %g2
   set 0x5c0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=49, level=2,  ppnr=0x46c40000, p_addr=0x5c4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5c4) = 0x46c408e (pte)
   set 0x46c408e, %g2
   set 0x5c4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=50, level=2,  ppnr=0x46c80000, p_addr=0x5c8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5c8) = 0x46c808e (pte)
   set 0x46c808e, %g2
   set 0x5c8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=51, level=2,  ppnr=0x46cc0000, p_addr=0x5cc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5cc) = 0x46cc08e (pte)
   set 0x46cc08e, %g2
   set 0x5cc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=52, level=2,  ppnr=0x46d00000, p_addr=0x5d0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5d0) = 0x46d008e (pte)
   set 0x46d008e, %g2
   set 0x5d0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=53, level=2,  ppnr=0x46d40000, p_addr=0x5d4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5d4) = 0x46d408e (pte)
   set 0x46d408e, %g2
   set 0x5d4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=54, level=2,  ppnr=0x46d80000, p_addr=0x5d8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5d8) = 0x46d808e (pte)
   set 0x46d808e, %g2
   set 0x5d8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=55, level=2,  ppnr=0x46dc0000, p_addr=0x5dc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5dc) = 0x46dc08e (pte)
   set 0x46dc08e, %g2
   set 0x5dc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=56, level=2,  ppnr=0x46e00000, p_addr=0x5e0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5e0) = 0x46e008e (pte)
   set 0x46e008e, %g2
   set 0x5e0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=57, level=2,  ppnr=0x46e40000, p_addr=0x5e4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5e4) = 0x46e408e (pte)
   set 0x46e408e, %g2
   set 0x5e4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=58, level=2,  ppnr=0x46e80000, p_addr=0x5e8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5e8) = 0x46e808e (pte)
   set 0x46e808e, %g2
   set 0x5e8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=59, level=2,  ppnr=0x46ec0000, p_addr=0x5ec, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5ec) = 0x46ec08e (pte)
   set 0x46ec08e, %g2
   set 0x5ec, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=60, level=2,  ppnr=0x46f00000, p_addr=0x5f0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5f0) = 0x46f008e (pte)
   set 0x46f008e, %g2
   set 0x5f0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=61, level=2,  ppnr=0x46f40000, p_addr=0x5f4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5f4) = 0x46f408e (pte)
   set 0x46f408e, %g2
   set 0x5f4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=62, level=2,  ppnr=0x46f80000, p_addr=0x5f8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5f8) = 0x46f808e (pte)
   set 0x46f808e, %g2
   set 0x5f8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=63, level=2,  ppnr=0x46fc0000, p_addr=0x5fc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x5fc) = 0x46fc08e (pte)
   set 0x46fc08e, %g2
   set 0x5fc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=71, level=1,  ppnr=0x47000000, p_addr=0xd1c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xd1c) = 0x470008e (pte)
   set 0x470008e, %g2
   set 0xd1c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTD: context=0, index=72, level=1, child_p_addr=0x700, p_addr=0xd20
   ! *(PAGE_TABLE_BASE + 0xd20) = ptd(PAGE_TABLE_BASE + 0x700)
   ! make PTD from 0x700
   set 0x700, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0xd20, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=0, level=2,  ppnr=0x48000000, p_addr=0x700, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x700) = 0x480008e (pte)
   set 0x480008e, %g2
   set 0x700, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=1, level=2,  ppnr=0x48040000, p_addr=0x704, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x704) = 0x480408e (pte)
   set 0x480408e, %g2
   set 0x704, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=2, level=2,  ppnr=0x48080000, p_addr=0x708, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x708) = 0x480808e (pte)
   set 0x480808e, %g2
   set 0x708, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=3, level=2,  ppnr=0x480c0000, p_addr=0x70c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x70c) = 0x480c08e (pte)
   set 0x480c08e, %g2
   set 0x70c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=4, level=2,  ppnr=0x48100000, p_addr=0x710, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x710) = 0x481008e (pte)
   set 0x481008e, %g2
   set 0x710, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=5, level=2,  ppnr=0x48140000, p_addr=0x714, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x714) = 0x481408e (pte)
   set 0x481408e, %g2
   set 0x714, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=6, level=2,  ppnr=0x48180000, p_addr=0x718, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x718) = 0x481808e (pte)
   set 0x481808e, %g2
   set 0x718, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=7, level=2,  ppnr=0x481c0000, p_addr=0x71c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x71c) = 0x481c08e (pte)
   set 0x481c08e, %g2
   set 0x71c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=8, level=2,  ppnr=0x48200000, p_addr=0x720, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x720) = 0x482008e (pte)
   set 0x482008e, %g2
   set 0x720, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=9, level=2,  ppnr=0x48240000, p_addr=0x724, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x724) = 0x482408e (pte)
   set 0x482408e, %g2
   set 0x724, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=10, level=2,  ppnr=0x48280000, p_addr=0x728, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x728) = 0x482808e (pte)
   set 0x482808e, %g2
   set 0x728, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=11, level=2,  ppnr=0x482c0000, p_addr=0x72c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x72c) = 0x482c08e (pte)
   set 0x482c08e, %g2
   set 0x72c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=12, level=2,  ppnr=0x48300000, p_addr=0x730, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x730) = 0x483008e (pte)
   set 0x483008e, %g2
   set 0x730, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=13, level=2,  ppnr=0x48340000, p_addr=0x734, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x734) = 0x483408e (pte)
   set 0x483408e, %g2
   set 0x734, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=14, level=2,  ppnr=0x48380000, p_addr=0x738, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x738) = 0x483808e (pte)
   set 0x483808e, %g2
   set 0x738, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=15, level=2,  ppnr=0x483c0000, p_addr=0x73c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x73c) = 0x483c08e (pte)
   set 0x483c08e, %g2
   set 0x73c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=16, level=2,  ppnr=0x48400000, p_addr=0x740, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x740) = 0x484008e (pte)
   set 0x484008e, %g2
   set 0x740, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=17, level=2,  ppnr=0x48440000, p_addr=0x744, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x744) = 0x484408e (pte)
   set 0x484408e, %g2
   set 0x744, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=18, level=2,  ppnr=0x48480000, p_addr=0x748, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x748) = 0x484808e (pte)
   set 0x484808e, %g2
   set 0x748, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=19, level=2,  ppnr=0x484c0000, p_addr=0x74c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x74c) = 0x484c08e (pte)
   set 0x484c08e, %g2
   set 0x74c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=20, level=2,  ppnr=0x48500000, p_addr=0x750, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x750) = 0x485008e (pte)
   set 0x485008e, %g2
   set 0x750, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=21, level=2,  ppnr=0x48540000, p_addr=0x754, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x754) = 0x485408e (pte)
   set 0x485408e, %g2
   set 0x754, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=22, level=2,  ppnr=0x48580000, p_addr=0x758, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x758) = 0x485808e (pte)
   set 0x485808e, %g2
   set 0x758, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTD: context=0, index=23, level=2, child_p_addr=0x600, p_addr=0x75c
   ! *(PAGE_TABLE_BASE + 0x75c) = ptd(PAGE_TABLE_BASE + 0x600)
   ! make PTD from 0x600
   set 0x600, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x75c, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=0, level=3,  ppnr=0x485c0000, p_addr=0x600, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x600) = 0x485c08e (pte)
   set 0x485c08e, %g2
   set 0x600, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=1, level=3,  ppnr=0x485c1000, p_addr=0x604, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x604) = 0x485c18e (pte)
   set 0x485c18e, %g2
   set 0x604, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=2, level=3,  ppnr=0x485c2000, p_addr=0x608, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x608) = 0x485c28e (pte)
   set 0x485c28e, %g2
   set 0x608, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=3, level=3,  ppnr=0x485c3000, p_addr=0x60c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x60c) = 0x485c38e (pte)
   set 0x485c38e, %g2
   set 0x60c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=4, level=3,  ppnr=0x485c4000, p_addr=0x610, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x610) = 0x485c48e (pte)
   set 0x485c48e, %g2
   set 0x610, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=5, level=3,  ppnr=0x485c5000, p_addr=0x614, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x614) = 0x485c58e (pte)
   set 0x485c58e, %g2
   set 0x614, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=6, level=3,  ppnr=0x485c6000, p_addr=0x618, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x618) = 0x485c68e (pte)
   set 0x485c68e, %g2
   set 0x618, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=7, level=3,  ppnr=0x485c7000, p_addr=0x61c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x61c) = 0x485c78e (pte)
   set 0x485c78e, %g2
   set 0x61c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=8, level=3,  ppnr=0x485c8000, p_addr=0x620, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x620) = 0x485c88e (pte)
   set 0x485c88e, %g2
   set 0x620, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=9, level=3,  ppnr=0x485c9000, p_addr=0x624, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x624) = 0x485c98e (pte)
   set 0x485c98e, %g2
   set 0x624, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=10, level=3,  ppnr=0x485ca000, p_addr=0x628, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x628) = 0x485ca8e (pte)
   set 0x485ca8e, %g2
   set 0x628, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=11, level=3,  ppnr=0x485cb000, p_addr=0x62c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x62c) = 0x485cb8e (pte)
   set 0x485cb8e, %g2
   set 0x62c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=12, level=3,  ppnr=0x485cc000, p_addr=0x630, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x630) = 0x485cc8e (pte)
   set 0x485cc8e, %g2
   set 0x630, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=13, level=3,  ppnr=0x485cd000, p_addr=0x634, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x634) = 0x485cd8e (pte)
   set 0x485cd8e, %g2
   set 0x634, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=14, level=3,  ppnr=0x485ce000, p_addr=0x638, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x638) = 0x485ce8e (pte)
   set 0x485ce8e, %g2
   set 0x638, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=15, level=3,  ppnr=0x485cf000, p_addr=0x63c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x63c) = 0x485cf8e (pte)
   set 0x485cf8e, %g2
   set 0x63c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=16, level=3,  ppnr=0x485d0000, p_addr=0x640, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x640) = 0x485d08e (pte)
   set 0x485d08e, %g2
   set 0x640, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=17, level=3,  ppnr=0x485d1000, p_addr=0x644, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x644) = 0x485d18e (pte)
   set 0x485d18e, %g2
   set 0x644, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=18, level=3,  ppnr=0x485d2000, p_addr=0x648, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x648) = 0x485d28e (pte)
   set 0x485d28e, %g2
   set 0x648, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=19, level=3,  ppnr=0x485d3000, p_addr=0x64c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x64c) = 0x485d38e (pte)
   set 0x485d38e, %g2
   set 0x64c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=20, level=3,  ppnr=0x485d4000, p_addr=0x650, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x650) = 0x485d48e (pte)
   set 0x485d48e, %g2
   set 0x650, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=21, level=3,  ppnr=0x485d5000, p_addr=0x654, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x654) = 0x485d58e (pte)
   set 0x485d58e, %g2
   set 0x654, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=22, level=3,  ppnr=0x485d6000, p_addr=0x658, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x658) = 0x485d68e (pte)
   set 0x485d68e, %g2
   set 0x658, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=23, level=3,  ppnr=0x485d7000, p_addr=0x65c, cacheable=0x1, acc=0x4
   ! *(PAGE_TABLE_BASE + 0x65c) = 0x485d792 (pte)
   set 0x485d792, %g2
   set 0x65c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=24, level=3,  ppnr=0x485d8000, p_addr=0x660, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x660) = 0x485d88e (pte)
   set 0x485d88e, %g2
   set 0x660, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=25, level=3,  ppnr=0x485d9000, p_addr=0x664, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x664) = 0x485d98e (pte)
   set 0x485d98e, %g2
   set 0x664, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=26, level=3,  ppnr=0x485da000, p_addr=0x668, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x668) = 0x485da8e (pte)
   set 0x485da8e, %g2
   set 0x668, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=27, level=3,  ppnr=0x485db000, p_addr=0x66c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x66c) = 0x485db8e (pte)
   set 0x485db8e, %g2
   set 0x66c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=28, level=3,  ppnr=0x485dc000, p_addr=0x670, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x670) = 0x485dc8e (pte)
   set 0x485dc8e, %g2
   set 0x670, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=29, level=3,  ppnr=0x485dd000, p_addr=0x674, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x674) = 0x485dd8e (pte)
   set 0x485dd8e, %g2
   set 0x674, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=30, level=3,  ppnr=0x485de000, p_addr=0x678, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x678) = 0x485de8e (pte)
   set 0x485de8e, %g2
   set 0x678, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=31, level=3,  ppnr=0x485df000, p_addr=0x67c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x67c) = 0x485df8e (pte)
   set 0x485df8e, %g2
   set 0x67c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=32, level=3,  ppnr=0x485e0000, p_addr=0x680, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x680) = 0x485e08e (pte)
   set 0x485e08e, %g2
   set 0x680, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=33, level=3,  ppnr=0x485e1000, p_addr=0x684, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x684) = 0x485e18e (pte)
   set 0x485e18e, %g2
   set 0x684, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=34, level=3,  ppnr=0x485e2000, p_addr=0x688, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x688) = 0x485e28e (pte)
   set 0x485e28e, %g2
   set 0x688, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=35, level=3,  ppnr=0x485e3000, p_addr=0x68c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x68c) = 0x485e38e (pte)
   set 0x485e38e, %g2
   set 0x68c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=36, level=3,  ppnr=0x485e4000, p_addr=0x690, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x690) = 0x485e48e (pte)
   set 0x485e48e, %g2
   set 0x690, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=37, level=3,  ppnr=0x485e5000, p_addr=0x694, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x694) = 0x485e58e (pte)
   set 0x485e58e, %g2
   set 0x694, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=38, level=3,  ppnr=0x485e6000, p_addr=0x698, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x698) = 0x485e68e (pte)
   set 0x485e68e, %g2
   set 0x698, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=39, level=3,  ppnr=0x485e7000, p_addr=0x69c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x69c) = 0x485e78e (pte)
   set 0x485e78e, %g2
   set 0x69c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=40, level=3,  ppnr=0x485e8000, p_addr=0x6a0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6a0) = 0x485e88e (pte)
   set 0x485e88e, %g2
   set 0x6a0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=41, level=3,  ppnr=0x485e9000, p_addr=0x6a4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6a4) = 0x485e98e (pte)
   set 0x485e98e, %g2
   set 0x6a4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=42, level=3,  ppnr=0x485ea000, p_addr=0x6a8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6a8) = 0x485ea8e (pte)
   set 0x485ea8e, %g2
   set 0x6a8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=43, level=3,  ppnr=0x485eb000, p_addr=0x6ac, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6ac) = 0x485eb8e (pte)
   set 0x485eb8e, %g2
   set 0x6ac, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=44, level=3,  ppnr=0x485ec000, p_addr=0x6b0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6b0) = 0x485ec8e (pte)
   set 0x485ec8e, %g2
   set 0x6b0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=45, level=3,  ppnr=0x485ed000, p_addr=0x6b4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6b4) = 0x485ed8e (pte)
   set 0x485ed8e, %g2
   set 0x6b4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=46, level=3,  ppnr=0x485ee000, p_addr=0x6b8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6b8) = 0x485ee8e (pte)
   set 0x485ee8e, %g2
   set 0x6b8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=47, level=3,  ppnr=0x485ef000, p_addr=0x6bc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6bc) = 0x485ef8e (pte)
   set 0x485ef8e, %g2
   set 0x6bc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=48, level=3,  ppnr=0x485f0000, p_addr=0x6c0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6c0) = 0x485f08e (pte)
   set 0x485f08e, %g2
   set 0x6c0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=49, level=3,  ppnr=0x485f1000, p_addr=0x6c4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6c4) = 0x485f18e (pte)
   set 0x485f18e, %g2
   set 0x6c4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=50, level=3,  ppnr=0x485f2000, p_addr=0x6c8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6c8) = 0x485f28e (pte)
   set 0x485f28e, %g2
   set 0x6c8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=51, level=3,  ppnr=0x485f3000, p_addr=0x6cc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6cc) = 0x485f38e (pte)
   set 0x485f38e, %g2
   set 0x6cc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=52, level=3,  ppnr=0x485f4000, p_addr=0x6d0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6d0) = 0x485f48e (pte)
   set 0x485f48e, %g2
   set 0x6d0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=53, level=3,  ppnr=0x485f5000, p_addr=0x6d4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6d4) = 0x485f58e (pte)
   set 0x485f58e, %g2
   set 0x6d4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=54, level=3,  ppnr=0x485f6000, p_addr=0x6d8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6d8) = 0x485f68e (pte)
   set 0x485f68e, %g2
   set 0x6d8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=55, level=3,  ppnr=0x485f7000, p_addr=0x6dc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6dc) = 0x485f78e (pte)
   set 0x485f78e, %g2
   set 0x6dc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=56, level=3,  ppnr=0x485f8000, p_addr=0x6e0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6e0) = 0x485f88e (pte)
   set 0x485f88e, %g2
   set 0x6e0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=57, level=3,  ppnr=0x485f9000, p_addr=0x6e4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6e4) = 0x485f98e (pte)
   set 0x485f98e, %g2
   set 0x6e4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=58, level=3,  ppnr=0x485fa000, p_addr=0x6e8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6e8) = 0x485fa8e (pte)
   set 0x485fa8e, %g2
   set 0x6e8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=59, level=3,  ppnr=0x485fb000, p_addr=0x6ec, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6ec) = 0x485fb8e (pte)
   set 0x485fb8e, %g2
   set 0x6ec, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=60, level=3,  ppnr=0x485fc000, p_addr=0x6f0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6f0) = 0x485fc8e (pte)
   set 0x485fc8e, %g2
   set 0x6f0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=61, level=3,  ppnr=0x485fd000, p_addr=0x6f4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6f4) = 0x485fd8e (pte)
   set 0x485fd8e, %g2
   set 0x6f4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=62, level=3,  ppnr=0x485fe000, p_addr=0x6f8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6f8) = 0x485fe8e (pte)
   set 0x485fe8e, %g2
   set 0x6f8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=63, level=3,  ppnr=0x485ff000, p_addr=0x6fc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x6fc) = 0x485ff8e (pte)
   set 0x485ff8e, %g2
   set 0x6fc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=24, level=2,  ppnr=0x48600000, p_addr=0x760, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x760) = 0x486008e (pte)
   set 0x486008e, %g2
   set 0x760, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=25, level=2,  ppnr=0x48640000, p_addr=0x764, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x764) = 0x486408e (pte)
   set 0x486408e, %g2
   set 0x764, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=26, level=2,  ppnr=0x48680000, p_addr=0x768, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x768) = 0x486808e (pte)
   set 0x486808e, %g2
   set 0x768, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=27, level=2,  ppnr=0x486c0000, p_addr=0x76c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x76c) = 0x486c08e (pte)
   set 0x486c08e, %g2
   set 0x76c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=28, level=2,  ppnr=0x48700000, p_addr=0x770, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x770) = 0x487008e (pte)
   set 0x487008e, %g2
   set 0x770, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=29, level=2,  ppnr=0x48740000, p_addr=0x774, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x774) = 0x487408e (pte)
   set 0x487408e, %g2
   set 0x774, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=30, level=2,  ppnr=0x48780000, p_addr=0x778, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x778) = 0x487808e (pte)
   set 0x487808e, %g2
   set 0x778, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=31, level=2,  ppnr=0x487c0000, p_addr=0x77c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x77c) = 0x487c08e (pte)
   set 0x487c08e, %g2
   set 0x77c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=32, level=2,  ppnr=0x48800000, p_addr=0x780, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x780) = 0x488008e (pte)
   set 0x488008e, %g2
   set 0x780, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=33, level=2,  ppnr=0x48840000, p_addr=0x784, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x784) = 0x488408e (pte)
   set 0x488408e, %g2
   set 0x784, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=34, level=2,  ppnr=0x48880000, p_addr=0x788, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x788) = 0x488808e (pte)
   set 0x488808e, %g2
   set 0x788, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=35, level=2,  ppnr=0x488c0000, p_addr=0x78c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x78c) = 0x488c08e (pte)
   set 0x488c08e, %g2
   set 0x78c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=36, level=2,  ppnr=0x48900000, p_addr=0x790, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x790) = 0x489008e (pte)
   set 0x489008e, %g2
   set 0x790, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=37, level=2,  ppnr=0x48940000, p_addr=0x794, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x794) = 0x489408e (pte)
   set 0x489408e, %g2
   set 0x794, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=38, level=2,  ppnr=0x48980000, p_addr=0x798, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x798) = 0x489808e (pte)
   set 0x489808e, %g2
   set 0x798, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=39, level=2,  ppnr=0x489c0000, p_addr=0x79c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x79c) = 0x489c08e (pte)
   set 0x489c08e, %g2
   set 0x79c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=40, level=2,  ppnr=0x48a00000, p_addr=0x7a0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7a0) = 0x48a008e (pte)
   set 0x48a008e, %g2
   set 0x7a0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=41, level=2,  ppnr=0x48a40000, p_addr=0x7a4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7a4) = 0x48a408e (pte)
   set 0x48a408e, %g2
   set 0x7a4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=42, level=2,  ppnr=0x48a80000, p_addr=0x7a8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7a8) = 0x48a808e (pte)
   set 0x48a808e, %g2
   set 0x7a8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=43, level=2,  ppnr=0x48ac0000, p_addr=0x7ac, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7ac) = 0x48ac08e (pte)
   set 0x48ac08e, %g2
   set 0x7ac, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=44, level=2,  ppnr=0x48b00000, p_addr=0x7b0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7b0) = 0x48b008e (pte)
   set 0x48b008e, %g2
   set 0x7b0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=45, level=2,  ppnr=0x48b40000, p_addr=0x7b4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7b4) = 0x48b408e (pte)
   set 0x48b408e, %g2
   set 0x7b4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=46, level=2,  ppnr=0x48b80000, p_addr=0x7b8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7b8) = 0x48b808e (pte)
   set 0x48b808e, %g2
   set 0x7b8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=47, level=2,  ppnr=0x48bc0000, p_addr=0x7bc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7bc) = 0x48bc08e (pte)
   set 0x48bc08e, %g2
   set 0x7bc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=48, level=2,  ppnr=0x48c00000, p_addr=0x7c0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7c0) = 0x48c008e (pte)
   set 0x48c008e, %g2
   set 0x7c0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=49, level=2,  ppnr=0x48c40000, p_addr=0x7c4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7c4) = 0x48c408e (pte)
   set 0x48c408e, %g2
   set 0x7c4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=50, level=2,  ppnr=0x48c80000, p_addr=0x7c8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7c8) = 0x48c808e (pte)
   set 0x48c808e, %g2
   set 0x7c8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=51, level=2,  ppnr=0x48cc0000, p_addr=0x7cc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7cc) = 0x48cc08e (pte)
   set 0x48cc08e, %g2
   set 0x7cc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=52, level=2,  ppnr=0x48d00000, p_addr=0x7d0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7d0) = 0x48d008e (pte)
   set 0x48d008e, %g2
   set 0x7d0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=53, level=2,  ppnr=0x48d40000, p_addr=0x7d4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7d4) = 0x48d408e (pte)
   set 0x48d408e, %g2
   set 0x7d4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=54, level=2,  ppnr=0x48d80000, p_addr=0x7d8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7d8) = 0x48d808e (pte)
   set 0x48d808e, %g2
   set 0x7d8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=55, level=2,  ppnr=0x48dc0000, p_addr=0x7dc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7dc) = 0x48dc08e (pte)
   set 0x48dc08e, %g2
   set 0x7dc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=56, level=2,  ppnr=0x48e00000, p_addr=0x7e0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7e0) = 0x48e008e (pte)
   set 0x48e008e, %g2
   set 0x7e0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=57, level=2,  ppnr=0x48e40000, p_addr=0x7e4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7e4) = 0x48e408e (pte)
   set 0x48e408e, %g2
   set 0x7e4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=58, level=2,  ppnr=0x48e80000, p_addr=0x7e8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7e8) = 0x48e808e (pte)
   set 0x48e808e, %g2
   set 0x7e8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=59, level=2,  ppnr=0x48ec0000, p_addr=0x7ec, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7ec) = 0x48ec08e (pte)
   set 0x48ec08e, %g2
   set 0x7ec, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=60, level=2,  ppnr=0x48f00000, p_addr=0x7f0, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7f0) = 0x48f008e (pte)
   set 0x48f008e, %g2
   set 0x7f0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=61, level=2,  ppnr=0x48f40000, p_addr=0x7f4, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7f4) = 0x48f408e (pte)
   set 0x48f408e, %g2
   set 0x7f4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=62, level=2,  ppnr=0x48f80000, p_addr=0x7f8, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7f8) = 0x48f808e (pte)
   set 0x48f808e, %g2
   set 0x7f8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=63, level=2,  ppnr=0x48fc0000, p_addr=0x7fc, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x7fc) = 0x48fc08e (pte)
   set 0x48fc08e, %g2
   set 0x7fc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=73, level=1,  ppnr=0x49000000, p_addr=0xd24, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0xd24) = 0x490008e (pte)
   set 0x490008e, %g2
   set 0xd24, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTD: context=0, index=74, level=1, child_p_addr=0x900, p_addr=0xd28
   ! *(PAGE_TABLE_BASE + 0xd28) = ptd(PAGE_TABLE_BASE + 0x900)
   ! make PTD from 0x900
   set 0x900, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0xd28, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=0, level=2,  ppnr=0x4a000000, p_addr=0x900, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x900) = 0x4a0008e (pte)
   set 0x4a0008e, %g2
   set 0x900, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=1, level=2,  ppnr=0x4a040000, p_addr=0x904, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x904) = 0x4a0408e (pte)
   set 0x4a0408e, %g2
   set 0x904, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=2, level=2,  ppnr=0x4a080000, p_addr=0x908, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x908) = 0x4a0808e (pte)
   set 0x4a0808e, %g2
   set 0x908, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=3, level=2,  ppnr=0x4a0c0000, p_addr=0x90c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x90c) = 0x4a0c08e (pte)
   set 0x4a0c08e, %g2
   set 0x90c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=4, level=2,  ppnr=0x4a100000, p_addr=0x910, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x910) = 0x4a1008e (pte)
   set 0x4a1008e, %g2
   set 0x910, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=5, level=2,  ppnr=0x4a140000, p_addr=0x914, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x914) = 0x4a1408e (pte)
   set 0x4a1408e, %g2
   set 0x914, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=6, level=2,  ppnr=0x4a180000, p_addr=0x918, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x918) = 0x4a1808e (pte)
   set 0x4a1808e, %g2
   set 0x918, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=7, level=2,  ppnr=0x4a1c0000, p_addr=0x91c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x91c) = 0x4a1c08e (pte)
   set 0x4a1c08e, %g2
   set 0x91c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=8, level=2,  ppnr=0x4a200000, p_addr=0x920, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x920) = 0x4a2008e (pte)
   set 0x4a2008e, %g2
   set 0x920, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=9, level=2,  ppnr=0x4a240000, p_addr=0x924, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x924) = 0x4a2408e (pte)
   set 0x4a2408e, %g2
   set 0x924, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=10, level=2,  ppnr=0x4a280000, p_addr=0x928, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x928) = 0x4a2808e (pte)
   set 0x4a2808e, %g2
   set 0x928, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=11, level=2,  ppnr=0x4a2c0000, p_addr=0x92c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x92c) = 0x4a2c08e (pte)
   set 0x4a2c08e, %g2
   set 0x92c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=12, level=2,  ppnr=0x4a300000, p_addr=0x930, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x930) = 0x4a3008e (pte)
   set 0x4a3008e, %g2
   set 0x930, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=13, level=2,  ppnr=0x4a340000, p_addr=0x934, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x934) = 0x4a3408e (pte)
   set 0x4a3408e, %g2
   set 0x934, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=14, level=2,  ppnr=0x4a380000, p_addr=0x938, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x938) = 0x4a3808e (pte)
   set 0x4a3808e, %g2
   set 0x938, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=15, level=2,  ppnr=0x4a3c0000, p_addr=0x93c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x93c) = 0x4a3c08e (pte)
   set 0x4a3c08e, %g2
   set 0x93c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=16, level=2,  ppnr=0x4a400000, p_addr=0x940, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x940) = 0x4a4008e (pte)
   set 0x4a4008e, %g2
   set 0x940, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=17, level=2,  ppnr=0x4a440000, p_addr=0x944, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x944) = 0x4a4408e (pte)
   set 0x4a4408e, %g2
   set 0x944, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=18, level=2,  ppnr=0x4a480000, p_addr=0x948, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x948) = 0x4a4808e (pte)
   set 0x4a4808e, %g2
   set 0x948, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=19, level=2,  ppnr=0x4a4c0000, p_addr=0x94c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x94c) = 0x4a4c08e (pte)
   set 0x4a4c08e, %g2
   set 0x94c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=20, level=2,  ppnr=0x4a500000, p_addr=0x950, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x950) = 0x4a5008e (pte)
   set 0x4a5008e, %g2
   set 0x950, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=21, level=2,  ppnr=0x4a540000, p_addr=0x954, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x954) = 0x4a5408e (pte)
   set 0x4a5408e, %g2
   set 0x954, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=22, level=2,  ppnr=0x4a580000, p_addr=0x958, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x958) = 0x4a5808e (pte)
   set 0x4a5808e, %g2
   set 0x958, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTD: context=0, index=23, level=2, child_p_addr=0x800, p_addr=0x95c
   ! *(PAGE_TABLE_BASE + 0x95c) = ptd(PAGE_TABLE_BASE + 0x800)
   ! make PTD from 0x800
   set 0x800, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0x95c, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=0, level=3,  ppnr=0x4a5c0000, p_addr=0x800, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x800) = 0x4a5c08e (pte)
   set 0x4a5c08e, %g2
   set 0x800, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=1, level=3,  ppnr=0x4a5c1000, p_addr=0x804, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x804) = 0x4a5c18e (pte)
   set 0x4a5c18e, %g2
   set 0x804, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=2, level=3,  ppnr=0x4a5c2000, p_addr=0x808, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x808) = 0x4a5c28e (pte)
   set 0x4a5c28e, %g2
   set 0x808, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=3, level=3,  ppnr=0x4a5c3000, p_addr=0x80c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x80c) = 0x4a5c38e (pte)
   set 0x4a5c38e, %g2
   set 0x80c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=4, level=3,  ppnr=0x4a5c4000, p_addr=0x810, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x810) = 0x4a5c48e (pte)
   set 0x4a5c48e, %g2
   set 0x810, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=5, level=3,  ppnr=0x4a5c5000, p_addr=0x814, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x814) = 0x4a5c58e (pte)
   set 0x4a5c58e, %g2
   set 0x814, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=6, level=3,  ppnr=0x4a5c6000, p_addr=0x818, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x818) = 0x4a5c68e (pte)
   set 0x4a5c68e, %g2
   set 0x818, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=7, level=3,  ppnr=0x4a5c7000, p_addr=0x81c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x81c) = 0x4a5c78e (pte)
   set 0x4a5c78e, %g2
   set 0x81c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=8, level=3,  ppnr=0x4a5c8000, p_addr=0x820, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x820) = 0x4a5c88e (pte)
   set 0x4a5c88e, %g2
   set 0x820, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=9, level=3,  ppnr=0x4a5c9000, p_addr=0x824, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x824) = 0x4a5c98e (pte)
   set 0x4a5c98e, %g2
   set 0x824, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=10, level=3,  ppnr=0x4a5ca000, p_addr=0x828, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x828) = 0x4a5ca8e (pte)
   set 0x4a5ca8e, %g2
   set 0x828, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=11, level=3,  ppnr=0x4a5cb000, p_addr=0x82c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x82c) = 0x4a5cb8e (pte)
   set 0x4a5cb8e, %g2
   set 0x82c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=12, level=3,  ppnr=0x4a5cc000, p_addr=0x830, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x830) = 0x4a5cc8e (pte)
   set 0x4a5cc8e, %g2
   set 0x830, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=13, level=3,  ppnr=0x4a5cd000, p_addr=0x834, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x834) = 0x4a5cd8e (pte)
   set 0x4a5cd8e, %g2
   set 0x834, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=14, level=3,  ppnr=0x4a5ce000, p_addr=0x838, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x838) = 0x4a5ce8e (pte)
   set 0x4a5ce8e, %g2
   set 0x838, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=15, level=3,  ppnr=0x4a5cf000, p_addr=0x83c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x83c) = 0x4a5cf8e (pte)
   set 0x4a5cf8e, %g2
   set 0x83c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=16, level=3,  ppnr=0x4a5d0000, p_addr=0x840, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x840) = 0x4a5d08e (pte)
   set 0x4a5d08e, %g2
   set 0x840, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=17, level=3,  ppnr=0x4a5d1000, p_addr=0x844, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x844) = 0x4a5d18e (pte)
   set 0x4a5d18e, %g2
   set 0x844, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=18, level=3,  ppnr=0x4a5d2000, p_addr=0x848, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x848) = 0x4a5d28e (pte)
   set 0x4a5d28e, %g2
   set 0x848, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=19, level=3,  ppnr=0x4a5d3000, p_addr=0x84c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x84c) = 0x4a5d38e (pte)
   set 0x4a5d38e, %g2
   set 0x84c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=20, level=3,  ppnr=0x4a5d4000, p_addr=0x850, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x850) = 0x4a5d48e (pte)
   set 0x4a5d48e, %g2
   set 0x850, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=21, level=3,  ppnr=0x4a5d5000, p_addr=0x854, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x854) = 0x4a5d58e (pte)
   set 0x4a5d58e, %g2
   set 0x854, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=22, level=3,  ppnr=0x4a5d6000, p_addr=0x858, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x858) = 0x4a5d68e (pte)
   set 0x4a5d68e, %g2
   set 0x858, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=23, level=3,  ppnr=0x4a5d7000, p_addr=0x85c, cacheable=0x1, acc=0x3
   ! *(PAGE_TABLE_BASE + 0x85c) = 0x4a5d78e (pte)
   set 0x4a5d78e, %g2
   set 0x85c, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=24, level=3,  ppnr=0x4a5d8000, p_addr=0x860, cacheable=0x1, acc=0x4
   ! *(PAGE_TABLE_BASE + 0x860) = 0x4a5d892 (pte)
   set 0x4a5d892, %g2
   set 0x860, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTD: context=0, index=255, level=1, child_p_addr=0xbfc, p_addr=0xffc
   ! *(PAGE_TABLE_BASE + 0xffc) = ptd(PAGE_TABLE_BASE + 0xb00)
   ! make PTD from 0xbfc
   set 0xb00, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0xffc, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTD: context=0, index=63, level=2, child_p_addr=0xac0, p_addr=0xbfc
   ! *(PAGE_TABLE_BASE + 0xbfc) = ptd(PAGE_TABLE_BASE + 0xa00)
   ! make PTD from 0xac0
   set 0xa00, %g4
   add %g1, %g4, %g4
   srl %g4, 0x4, %g4
   or  %g4, 0x1, %g4
   ! g4 contains PTD 
   set 0xbfc, %g5
   add %g5, %g1, %g3
   st %g4, [%g3]
   ! g4 stored into [g3] 
   !PTE: context=0, index=48, level=3,  ppnr=0xffff0000, p_addr=0xac0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xac0) = 0xffff016 (pte)
   set 0xffff016, %g2
   set 0xac0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=49, level=3,  ppnr=0xffff1000, p_addr=0xac4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xac4) = 0xffff116 (pte)
   set 0xffff116, %g2
   set 0xac4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=50, level=3,  ppnr=0xffff2000, p_addr=0xac8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xac8) = 0xffff216 (pte)
   set 0xffff216, %g2
   set 0xac8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=51, level=3,  ppnr=0xffff3000, p_addr=0xacc, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xacc) = 0xffff316 (pte)
   set 0xffff316, %g2
   set 0xacc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=52, level=3,  ppnr=0xffff4000, p_addr=0xad0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xad0) = 0xffff416 (pte)
   set 0xffff416, %g2
   set 0xad0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=53, level=3,  ppnr=0xffff5000, p_addr=0xad4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xad4) = 0xffff516 (pte)
   set 0xffff516, %g2
   set 0xad4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=54, level=3,  ppnr=0xffff6000, p_addr=0xad8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xad8) = 0xffff616 (pte)
   set 0xffff616, %g2
   set 0xad8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=55, level=3,  ppnr=0xffff7000, p_addr=0xadc, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xadc) = 0xffff716 (pte)
   set 0xffff716, %g2
   set 0xadc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=56, level=3,  ppnr=0xffff8000, p_addr=0xae0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xae0) = 0xffff816 (pte)
   set 0xffff816, %g2
   set 0xae0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=57, level=3,  ppnr=0xffff9000, p_addr=0xae4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xae4) = 0xffff916 (pte)
   set 0xffff916, %g2
   set 0xae4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=58, level=3,  ppnr=0xffffa000, p_addr=0xae8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xae8) = 0xffffa16 (pte)
   set 0xffffa16, %g2
   set 0xae8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=59, level=3,  ppnr=0xffffb000, p_addr=0xaec, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xaec) = 0xffffb16 (pte)
   set 0xffffb16, %g2
   set 0xaec, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=60, level=3,  ppnr=0xffffc000, p_addr=0xaf0, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xaf0) = 0xffffc16 (pte)
   set 0xffffc16, %g2
   set 0xaf0, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=61, level=3,  ppnr=0xffffd000, p_addr=0xaf4, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xaf4) = 0xffffd16 (pte)
   set 0xffffd16, %g2
   set 0xaf4, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=62, level=3,  ppnr=0xffffe000, p_addr=0xaf8, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xaf8) = 0xffffe16 (pte)
   set 0xffffe16, %g2
   set 0xaf8, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   !PTE: context=0, index=63, level=3,  ppnr=0xfffff000, p_addr=0xafc, cacheable=0x0, acc=0x5
   ! *(PAGE_TABLE_BASE + 0xafc) = 0xfffff16 (pte)
   set 0xfffff16, %g2
   set 0xafc, %g5
   add %g5, %g1, %g3
   st %g2, [%g3]
   retl;
   nop;
! done: page_table_setup
! start: set context-table-pointer = PAGE_TABLE_BASE + 0x1000
.global set_context_table_pointer
set_context_table_pointer:
   set PAGE_TABLE_BASE, %g1
   set 0x1000, %g5
   add %g5, %g1, %g2
   srl  %g2, 0x4, %g2
   or  %g2, 0x1, %g2
   set 0x100, %g3
   sta %g2, [%g3] 0x4
   retl;
   nop;
! done: set  context-table-pointer
.align 1024
PAGE_TABLE_BASE: .skip 5120
