        .file   "cons-car-cdr.c"
        .global head
        .section        ".bss"
        .align 4
        .type   head, #object
        .size   head, 4
head:
        .skip   4
        .global counter
        .align 4
        .type   counter, #object
        .size   counter, 4
counter:
        .skip   4
        .global lst_len
        .align 4
        .type   lst_len, #object
        .size   lst_len, 4
lst_len:
        .skip   4
        .section        ".rodata"
        .align 8
.LC0:
        .asciz  "List as %d members.\n"
        .align 8
.LC1:
        .asciz  "Element %02d : %d\n"
        .section        ".text"
        .align 4
        .global main
        .type   main, #function
        .proc   04
main:
        adddcc        %g1,              %g2,   %g1
        adddcc        %g2,              %g4,   %g2
        addd          %g1,              %g2,   %g1
        addd          %g2,              %g4,   %g2
        adddreduce16  %g2,              %g1,   %g4
        adddreduce8   %g2,              %g1,   %g4
        anddcc        %g1,              %g2,   %g1
        andd          %g1,              %g2,   %g1
        anddncc       %g1,              %g2,   %g1
        anddn         %g1,              %g2,   %g1
        anddreduce16  %g2,              %g1,   %g4
        anddreduce8   %g2,              %g1,   %g4
        cswapa       [%g2 + 0x0fff]  , %g4
        cswapa       [%g2 + %g1] 0x0A, %g4
        cswap        [%fp + -8]      , %g4
        cswap        [%g2 + 0x0fff]  , %g4
        cswap        [%g2 + %g1] 0x08, %g4
        faddreduce16  %f2,              %f4
        fhtos         %f1,              %f3
        fstoh         %f1,              %f3
        ordcc         %g1,              %g2,   %g1
        ord           %g1,              %g2,   %g1
        ordncc        %g1,              %g2,   %g1
        ordn          %g1,              %g2,   %g1
        ordreduce16   %g2,              %g1,   %g4
        ordreduce8    %g2,              %g1,   %g4
        save          %sp,              -120,  %sp
        sdivdcc       %g1,              %g2,   %g1
        sdivd         %g1,              %g2,   %g1
        slld          %g1,              24,    %g2
        slld          %g1,              %g3,   %g2
        slld          %g2,              2,     %l2
        slld          %g2,              %g4,   %l2
        smuldcc       %g1,              %g2,   %g0
        smuld         %g1,              %g2,   %g0
        smul          %g1,              %g2,   %g0
        srad          %g1,              24,    %g2
        srad          %g1,              %g3,   %g2
        srad          %g2,              2,     %l0
        srad          %g2,              %g4,   %l0
        srld          %g1,              24,    %g2
        srld          %g1,              %g3,   %g2
        srld          %g2,              2,     %g6
        srld          %g2,              %g4,   %g6
        subdcc        %g1,              %g2,   %g1
        subdcc        %g2,              %g4,   %g2
        subd          %g1,              %g2,   %g1
        subd          %g2,              %g4,   %g2
        udivdcc       %g1,              %g2,   %g6
        udivd         %g1,              %g2,   %g1
        udivd         %g1,              %g2,   %g2
        udivd         %g1,              %g2,   %g3
        udivd         %g1,              %g2,   %g4
        udivd         %g1,              %g2,   %g5
        udivd         %g1,              %g2,   %g6
        udivd         %g2,              %g4,   %g2
        umuldcc       %g1,              %g2,   %g0
        umuld         %g1,              %g2,   %g0
        umul          %g1,              %g2,   %g0
        vaddd16       %g1,              %g2,   %g1
        vaddd16       %g2,              %g4,   %g6
        vaddd32       %g1,              %g2,   %g1
        vaddd32       %g2,              %g4,   %g6
        vaddd8        %g1,              %g2,   %g1
        vaddd8        %g2,              %g4,   %g6
        vfadd16       %f2,              %f4,   %f6
        vfadd32       %f2,              %f4,   %f6
        vfmul16       %f2,              %f4,   %f6
        vfmul32       %f2,              %f4,   %f6
        vfsub16       %f2,              %f4,   %f6
        vfsub32       %f2,              %f4,   %f6
        vsmuld16      %g1,              %g2,   %g1
        vsmuld16      %g2,              %g4,   %g6
        vsmuld32      %g1,              %g2,   %g1
        vsmuld32      %g2,              %g4,   %g6
        vsmuld8       %g1,              %g2,   %g1
        vsmuld8       %g2,              %g4,   %g6
        vsubd16       %g1,              %g2,   %g1
        vsubd16       %g2,              %g4,   %g6
        vsubd32       %g1,              %g2,   %g1
        vsubd32       %g2,              %g4,   %g6
        vsubd8        %g1,              %g2,   %g1
        vsubd8        %g2,              %g4,   %g6
        vumuld16      %g1,              %g2,   %g1
        vumuld16      %g2,              %g4,   %g6
        vumuld32      %g1,              %g2,   %g1
        vumuld32      %g2,              %g4,   %g6
        vumuld8       %g1,              %g2,   %g1
        vumuld8       %g2,              %g4,   %g6
        xnordcc       %g1,              %g2,   %g1
        xnord         %g1,              %g2,   %g1
        xordcc        %g1,              %g2,   %g1
        xordreduce16  %g2,              %g1,   %g4
        xordreduce8   %g2,              %g1,   %g4
        zbytedpos     %g2,              255,   %g4
        zbytedpos     %g2,              %g1,   %g4
         nop
        .ident  "GCC: (Buildroot 2014.08) 4.7.4"
        .section        .note.GNU-stack,"",@progbits
