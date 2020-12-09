;; Define the basic symbol-value binding
(define make-sym
  (lambda ()
    (let ((b (cons '__undefined '__no-value))) ; the binding we will remember
      (lambda (msg)
	(define inp-check
	  (lambda (p) (and (pair? p)
			   (symbol? (car p))
			   (not (eq? (car p) '__undefined))
			   )))
	(cond ((eq? msg 'set)           (lambda (p) (begin (set! b p)  b)))
	      ((eq? msg 'get)           (lambda () b))
	      ((eq? msg 'check)         (lambda () (inp-check b)))
	      ((eq? msg 'get-symbol)    (lambda () (car b)))
	      ((eq? msg 'get-value)     (lambda () (cdr b)))
	      ((eq? msg 'update-symbol) (lambda (s) (and (symbol? s)
							 (set-car! b s)
							 s)))
	      ((eq? msg 'update-value)  (lambda (v) (set-cdr! b v)))
	      ((eq? msg 'print-self)    (lambda ()
					  (if (inp-check b)
					      (begin
						(display "(")
						(display "Symbol: ")
						(display (car b))
						(display " . Value: ")
						(display (cdr b))
						(display ")")
						(newline))
					      (begin
						(display "UNDEFINED: ")
						(display "(")
						(display "Symbol: ")
						(display (car b))
						(display " . Value: ")
						(display (cdr b))
						(display ")")
						(newline))
					      )))
	      (else (error "Wrong message: " msg)))
	)
      )
    )
  )


;; Test each message
   ;; tests :: (define s make-sym)
   ;; tests :: ((s 'set) (cons 'a 1))
   ;; tests :: ;; $1 = (a . 1)
   ;; tests :: ((s 'print-self))
   ;; tests :: ;; (Symbol: a Value: 1)
   ;; tests :: ((s 'get-symbol))
   ;; tests :: ;; $2 = a
   ;; tests :: ((s 'get-value))
   ;; tests :: ;; $3 = 1
   ;; tests :: ((s 'check))
   ;; tests :: ;; $4 = #t
   ;; tests :: ((s 'update-symbol) 'b)
   ;; tests :: ;; $5 = b
   ;; tests :: ((s 'check))
   ;; tests :: ;; $6 = #t
   ;; tests :: ((s 'print-self))
   ;; tests :: ;; (Symbol: b Value: 1)
   ;; tests :: ((s 'update-value) 2)
   ;; tests :: ((s 'print-self))
   ;; tests :: ;; (Symbol: b Value: 2)
   ;; tests :: ((s 'get-value))
   ;; tests :: ;; $7 = 2
   ;; tests :: ((s 'update-value) (list 1 2))
   ;; tests :: ((s 'print-self))
   ;; tests :: ;; (Symbol: b Value: (1 2))
   ;; tests :: ((s 'get-value))

