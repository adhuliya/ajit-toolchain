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

;; Simple tests
(display "EXECUTING: (define m (make-mnemonic))")
(define m (make-mnemonic))
(newline)
(display "EXECUTING: ((m 'mnemonic-print-self))")
(newline)
((m 'mnemonic-print-self))
(display "EXECUTING: ((m 'mnemonic-init))")
((m 'mnemonic-init))
(newline)
(display "EXECUTING: ((m 'mnemonic-print-self))")
(newline)
((m 'mnemonic-print-self))
(display "EXECUTING: ((m 'mnemonic-set) \"ADDD\")")
((m 'mnemonic-set) "ADDD")
(newline)
(display "EXECUTING: ((m 'mnemonic-print-self))")
(newline)
((m 'mnemonic-print-self))
(display "EXECUTING: ((m 'mnemonic-check))")
((m 'mnemonic-check))
(newline)
(display "EXECUTING: ((m 'mnemonic-print-self))")
(newline)
((m 'mnemonic-print-self))
(display "EXECUTING: ((m 'mnemonic-get))")
(newline)
(display ((m 'mnemonic-get)))
(newline)
(display "EXECUTING: ((m 'mnemonic-print-self))")
(newline)
((m 'mnemonic-print-self))
(display "EXECUTING: ((m 'mnemonic-get-insn))")
(newline)
(display ((m 'mnemonic-get-insn)))
(newline)
(display "DONE.")
(newline)

;; Define a list of mnemonics
;; (define l
;;   '("ADDD"     "ADDDCC"    "SUBD"      "SUBDCC" 	; Add and subtract
;;     ))

(define mnemonics-string-data
  '("ADDD"     "ADDDCC"    "SUBD"      "SUBDCC" 	; Add and subtract
    "SLLD"     "SRLD"      "SRAD"	         	; Shift
    "UMULD"    "UMULDCC"   "SMULD"     "SMULDCC"
    "UDIVD"    "UDIVDCC"   "SDIVD"     "SDIVDCC"	; Mulitply and divide
    "ORD"      "ORDCC"     "ORDN"      "ORDNCC"
    "XORDCC"   "XNORD"     "XNORDCC"
    "ANDD"     "ANDDCC"    "ANDDNCC"            	; 64 bit logical
    "VADDD8"   "VADDD16"   "VADDD32"
    "VSUBD8"   "VSUBD16"   "VSUBD32"
    "VUMULD8"  "VUMULD16"  "VUMULD32"
    "VSMULD8"  "VSMULD16"  "VSMULD32"           	; SIMD I
    "ORDBYTER" "ANDDBYTER" "XORDBYTER" "ZBYTEDPOS"	; SIMD II
    "VFADD"    "VFSUB"     "VFMUL"     "VFDIV"
    "VFSQRT"                                            ; SIMD Floating point
    ))

    ;; (define set-mnemonic
    ;;   (lambda (s)
    ;; 	(if (string? s)
    ;; 	    (let* ((m  (make-mnemonic))
    ;; 		   (mi ((m 'mnemonic-init)))
    ;; 		   (ms ((m 'mnemonic-set) s))
    ;; 		   )
    ;; 	      ((m 'mnemonic-get)))
    ;; 	    'NULL)))

    ;; (define set-mnemonic
    ;;   (lambda (s)
    ;; 	(if (string? s)
    ;; 	    (let ((m (make-mnemonic))
    ;; 		   )
    ;; 	      (begin
    ;; 		((m 'mnemonic-init))
    ;; 		((m 'mnemonic-set) s)
    ;; 		((m 'mnemonic-get))
    ;; 	       ))
    ;; 	    'NULL)))

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

