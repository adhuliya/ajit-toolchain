;; Define a mnemonic
;; 
;; Uses the ability to define and manipulate bindings from "make-sym.scm".

(define make-mnemonic
  (lambda ()
    (let  ((m-sym (make-sym)))
      (lambda (m)
	(define check-mnemonic
	  (lambda ()
	    (and ((m-sym 'check))
		 (eq? 'mnemonic ((m-sym 'get-symbol))))
	    ))
	(cond  ((eq? m 'mnemonic-init)       (lambda ()
					       ((m-sym 'set) (cons 'mnemonic '()))))
	       ((eq? m 'mnemonic-set)  	     (lambda (p)
					       ((m-sym 'update-value)
						(if (and (string? p) check-mnemonic) p '()))))
	       ((eq? m 'mnemonic-get)  	     (lambda () ((m-sym 'get))))
	       ((eq? m 'mnemonic-get-insn)   (lambda () ((m-sym 'get-value))))
	       ((eq? m 'mnemonic-check)      (lambda () (check-mnemonic)))
	       ((eq? m 'mnemonic-print-self) (lambda () (begin
							  (display "MNEMONIC: ")
							  ((m-sym 'print-self))
							  )))
	       (else (error "MNEMONIC: Unknown message - " m)))
	))))


;; Define a (sample) list of mnemonics
(define mnemonics-string-data
  '("ADDD"     "ADDDCC" 	; Add
    ))

;; (define mnemonics-string-data
;;   '("ADDD"     "ADDDCC"    "SUBD"      "SUBDCC" 	; Add and subtract
;;     "SLLD"     "SRLD"      "SRAD"	         	; Shift
;;     "UMULD"    "UMULDCC"   "SMULD"     "SMULDCC"
;;     "UDIVD"    "UDIVDCC"   "SDIVD"     "SDIVDCC"	; Mulitply and divide
;;     "ORD"      "ORDCC"     "ORDN"      "ORDNCC"
;;     "XORDCC"   "XNORD"     "XNORDCC"
;;     "ANDD"     "ANDDCC"    "ANDDNCC"            	; 64 bit logical
;;     "VADDD8"   "VADDD16"   "VADDD32"
;;     "VSUBD8"   "VSUBD16"   "VSUBD32"
;;     "VUMULD8"  "VUMULD16"  "VUMULD32"
;;     "VSMULD8"  "VSMULD16"  "VSMULD32"           	; SIMD I
;;     "ORDBYTER" "ANDDBYTER" "XORDBYTER" "ZBYTEDPOS"	; SIMD II
;;     "VFADD"    "VFSUB"     "VFMUL"     "VFDIV"
;;     "VFSQRT"                                            ; SIMD Floating point
;;     ))

;; Build a manipulatable list.  No error handling at the moment.
(define make-mnemonics-list
  (lambda (l)
    (define set-mnemonic
      (lambda (s)
	(if (string? s)
	    (let* ((m  (make-mnemonic))
		   (mi ((m 'mnemonic-init)))
		   (ms ((m 'mnemonic-set) s))
		   )
	      ((m 'mnemonic-get)))
	    'NULL)))

    (if (null? l)
	l
	(cons
	 (set-mnemonic (car l))
	 (make-mnemonics-list (cdr l))))))

(define ml (make-mnemonics-list mnemonics-string-data))

