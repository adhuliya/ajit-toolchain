;;
;; Set of checks of an insn (i.e. instruction) description.
;;

(define check-insn
  (lambda (insn)			;; Assume that the insn is a list of attributes
    (if (null? insn) #t			;; identity of conjunction
	(and (check-number-of-bits-ok-p insn)
	     (check-regions-do-not-overlap-p insn)
	     )
	)))

(define check-number-of-bits-ok-p
  (lambda (insn)
    (let* ((len         (get-insn-length-in-bits insn))
	   (regions     (get-insn-opcode-layout  insn))
	   (region-len  (get-region-lengths      regions))
	   )
      (= len region-len)
     )))

(define check-regions-do-not-overlap-p
  (lambda (insn)
    (
     )))

