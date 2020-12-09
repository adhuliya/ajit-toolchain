;; 
;; SPARC v8 (+ AJIT) Opcode pattern descriptions.
;; 

;; Define the basic symbol-value binding
(define make-sym
  (let ((b  '()))			; the binding we will remember
    (lambda (msg)
      (define inp-check
	(lambda (p) (and (list?   p)
			 (eq? (length p) 2)
			 (symbol? (car p)))))
      (cond ((eq? msg 'set)           (lambda (p) (begin (set! b p)  b)))
	    ((eq? msg 'get)           (lambda () b))
	    ((eq? msg 'check)         (lambda () (inp-check b)))
	    ((eq? msg 'get-symbol)    (lambda () (car b)))
	    ((eq? msg 'get-value)     (lambda () (cadr b)))
	    ((eq? msg 'update-symbol) (lambda (s) (and (symbol? s)
						       (set-car! b s)
						       s)))
	    ((eq? msg 'update-value)  (lambda (v) (set-cdr! b v)))
	    ((eq? msg 'print-self)    (lambda ()
					(begin
					  (display "(")
					  (display "Symbol: ")
					  (display (car b))
					  (display " Value: ")
					  (display (cadr b))
					  (display ")")
					  (newline)
					  )))
	    (else (error "Wrong message: " msg)))
      )
    )
  )
