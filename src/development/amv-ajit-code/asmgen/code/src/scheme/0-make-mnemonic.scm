;; Define mnemonics
(define mnemonic
  (let* ((m-sym make-sym)
	 (mnem  ((m-sym 'set) (cons 'mnemonic '())))
	 )
    (lambda (m)
      (define check-mnemonic
	(lambda ()
	  (and ((mnem 'check))
	       (eq? 'mnemonic ((mnem 'get-symbol))))
	       ))
      (cond  ((eq? m 'mnemonic-check)        (check-mnemonic))
	     ((eq? m 'mnemonic-print-self)
	      (display mnem)
	       )
      	     ;; ((eq? m 'set)   (lambda (s) (if (check-mnemonic s) ((set! m
	     (else (error "MNEMONIC: Unknown message - " m)))
      )))
