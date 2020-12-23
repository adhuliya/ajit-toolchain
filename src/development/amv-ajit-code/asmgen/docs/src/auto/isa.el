(TeX-add-style-hook
 "isa"
 (lambda ()
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "../src/isa-v2-details"
    "../src/binutils"
    "../src/sisad"
    "../src/packaging"
    "book"
    "bk10"
    "epsf"
    "pstricks"
    "enumitem"
    "fullpage"
    "hyperref")
   (TeX-add-symbols
    "note"
    "attention")
   (LaTeX-add-labels
    "chap:from:mpd:at:iitb"
    "sec:Overview"
    "sec:changes:wrt:v1"
    "sec:insn:modified"
    "sec:asr:mappings"
    "sec:isa:extns"
    "sec:isa:v2"))
 :latex)

