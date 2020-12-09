(TeX-add-style-hook
 "binutils"
 (lambda ()
   (TeX-run-style-hooks
    "../src/add-sub-insn-extns"
    "../src/shift-insn-extns"
    "../src/mul-div-insn-extns"
    "../src/64-bit-logical-insn-extns"
    "../src/int-unit-extns-summary")
   (LaTeX-add-labels
    "chap:amv:work"
    "sec:binutils:support"
    "sec:integer-unit-extns:arith-logic-insns:impl"
    "sec:integer-unit-extns:simd-instructions:impl"
    "sec:integer-unit-extns:simd-instructions:2:impl"
    "sec:vector-floating-point-instructions:impl"
    "sec:cswap-instructions:impl"))
 :latex)

