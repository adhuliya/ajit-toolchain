;;
;; Sample message passing stack code.
;;
(define stack
  (let ((stk '()))
    (lambda (msg)
      (case msg
	((empty?)    (lambda ()  (null? stk)))
	((push!)     (lambda (x) (set! stk (cons x stk))))
	((pop!)      (lambda ()  (if (null? stk)
				     (error "Stack empty")
				     (let ((x (car stk)))
				       (begin
					 (set! stk (cdr stk))
					 x)
				       ))))
	((top)       (lambda ()  (if (null? stk)
				     (error "Stack empty")
				     (car stk))))
	(else        (error "stack: invalid message" msg)))
      )))
