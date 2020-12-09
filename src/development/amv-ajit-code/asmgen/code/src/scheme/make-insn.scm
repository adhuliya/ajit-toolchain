;;
;; Sparc V8 insns (Appendix B of Sparc V8 manual).
;; AJIT additions a little later.
;;

;; This is just a database of Sparc V8 instructions.  We use the style
;; as described in the manual. Thus:
;;

;; A.     Instructions  are grouped  into  6 major  "sections" and  34
;;        minor "sections".
;; B.     Each section has five subsections of description
;; B.1    A table of opcodes
;; B.2    Illustration of applicable formats
;; B.3    Suggested ASM syntax
;; B.4    Descriptions of: (a) Salient features, (b) restrictions, (c)
;;        traps.
;; B.5    A list of traps that can occur.
;; C.     All instructions are 32 bits.
;; D.     Three *major* formats
;; D.1    Format 1:
;;        CALL instruction
;;        insn[30:31] : op = 1, insn[0:29] : 30 bit displacement.
;;        (All  addresses  are  word   aligned,  hence  only  the  most
;;        significant 30  bits contain  the address  information.  The
;;        processor left shifts the argument by 2.)
;; D.2    Format 2:
;;        SETHI and Branches
;;        insn[30:31] : op = 0,
;;        Format 2a:
;;           insn[25:29]  :  rd,  insn[22:24]   :  op2,  insn[0:21]  :
;;           immediate 22
;;        Format 2b:
;;           insn[29:29] :  a, insn[25:28]  : cond,  insn[22:24]: op2,
;;           insn[0:21] : displacement 22
;; D.3    Format 3:
;;        All remaining ones
;;        insn[30:31] :  op = 2 or  3 (10b or 11b),  insn[25:29] : rd,
;;        insn[19:24] : op3, insn[14:18] : rs1
;;        Format 2a:
;;           insn[13:13] : i = 0, insn[05:12] : asi, insn[0:4] : rs2
;;        Format 2b:
;;           insn[13:13] : i = 1, insn[0:12] : signed immediate 13
;;        Format 2c:
;;           insn[05:13] : opf, insn[0:4] : rs1

;;
;; Basic architecture: Dispatch on the value of "op" field
;;

