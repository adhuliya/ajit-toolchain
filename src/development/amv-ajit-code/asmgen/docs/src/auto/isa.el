(TeX-add-style-hook
 "isa"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("hyperref" "colorlinks=true" "citecolor=brown" "pagebackref=true" "backref=true" "hyperfigures=true" "hyperfootnotes=true" "hyperindex=true")))
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "../src/binutils"
    "../src/sisad"
    "book"
    "bk10"
    "fullpage"
    "hyperref")
   (LaTeX-add-labels
    "chap:from:mpd:at:iitb"
    "sec:Overview"
    "sec:isa:extns"
    "sec:integer-unit-extns:arith-logic-insns"
    "tab:arith:insns"
    "tab:shift:insns"
    "tab:muldiv:insns"
    "tab:64bit:logical:insns"
    "sec:integer-unit-extns:simd-instructions"
    "tab:simd:insns"
    "sec:integer-unit-extns:simd-instructions:2"
    "tab:simd:2:insns"
    "sec:vector-floating-point-instructions"
    "tab:simd:float:ops"
    "sec:cswap-instructions"
    "tab:cswap:insns"))
 :latex)

