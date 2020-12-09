;;
;; INSN Language
;;
;; (define old-output-port (current-output-port))
;; (define current-output-port (lambda () (open-output-file "insn.log")))
(load "insn-lang.scm")

;;
;; Simple structure: The grammar is
;;
;; attribute : '(' symbol value ')'
;; structure : () | '(' attribute structure ')'
;; symbol : variable
;; value  : datum | structure
;; datum  : string | number | enumerated | expression
;;

;; insn : () | '(' attribute insn ')'    ; List of attributes
;; attribute : '(' symbol value ')'
;; value : string | integer | enumerated | list

;; Given a description of ONE insn, get the components.
;; This is a generic low level extractor. The individual selectors are
;; separately defined.

;; Flattens nested lists
(define flatten
  (lambda (l)
    (if (null? l) l
	(append (car l)
		(flatten (cdr l))
		))))

(define amv-reverse
  (lambda (l)
    (append (reverse (cdr l)) (list (car l)))))


(define get
  (lambda (insn-data info-symbol)
    (if (null? insn-data)
	insn-data
	(let ((info     (car insn-data))
	      (rest     (cdr insn-data)))
	  (if (and (list? info) (= (length info) 2))
	      (let ((sym   (car  info))
		    (val   (cadr info)))
		(if (eqv? sym info-symbol)
		    val
		    (get rest info-symbol))
		)
	      #f
	      )
	  ))
    ))

;; stors (SelecTORS)
(define get-insn-mnemonic
   (lambda (insn) (get insn 'mnemonic)))

(define get-insn-insn-subtype
   (lambda (insn) (get insn 'insn-subtype)))

(define get-insn-alignment-type
   (lambda (insn) (get insn 'alignment-type)))

(define get-insn-length-in-bits 
   (lambda (insn) (get insn 'length-in-bits )))

(define get-insn-format-type
   (lambda (insn) (get insn 'format-type)))

(define get-insn-bit-order
   (lambda (insn) (get insn 'bit-order)))

(define get-insn-opcode-layout
   (lambda (insn) (get insn 'opcode-layout)))

(define get-number-of-all-regions-in-insn
  (lambda (insn) (length (get-insn-opcode-layout insn))))

(define get-number-of-given-region-type-in-insn
  (lambda (insn type)
    (let ((num-regions   (get-number-of-all-regions-in-insn insn))
	  (regions-list  (get-insn-opcode-layout            insn)))
      (define process-regions-list
	(lambda (rl)
	  (if (null? rl)
	      0
	      (let ((curr-region   (car rl))
		    (rest-region   (cdr rl))
		    )
		(+ (if (eq? (car curr-region) type) 1 0)
		   (process-regions-list rest-region)))
	      )))
      (process-regions-list regions-list))))

(define get-number-of-unions-in-insn
  (lambda (insn)
    (get-number-of-given-region-type-in-insn insn 'union)))

(define get-number-of-regions-in-insn
  (lambda (insn)
    (get-number-of-given-region-type-in-insn insn 'region)))

(define get-list-of-given-region-type-in-insn
  (lambda (insn type)
    (let ((num-regions   (get-number-of-all-regions-in-insn insn))
	  (regions-list  (get-insn-opcode-layout            insn)))
      (define process-regions-list
	(lambda (rl)
	  (if (null? rl)
	      rl
	      (let ((curr-region   (car rl))
		    (rest-region   (cdr rl))
		    )
		(if (eq? (car curr-region) type)
		    (cons curr-region 
			  (process-regions-list rest-region))
		    (process-regions-list rest-region))
	      ))))
      (process-regions-list regions-list)
      )))

(define get-list-of-unions-in-insn
  (lambda (insn)
    (get-list-of-given-region-type-in-insn insn 'union)))

(define get-list-of-regions-in-insn
  (lambda (insn)
    (get-list-of-given-region-type-in-insn insn 'region)))

(define get-list-of-regions-in-union
  (lambda (u) (cadar u)))

;;
;; Return a list of pairs, each pair given as: (binary digit . location).
;; 
    (define get-val-of
      (lambda (region-details-list sym)
	(if (null? region-details-list)
	    '()
	    (let* ((bind    (car  region-details-list))
		   (rest    (cdr region-details-list))
		   (the-sym (car  bind))
		   (the-val (cadr bind))
		   )
	      (if (eq? the-sym sym)
	      	  the-val
	      	  (get-val-of rest sym))))))

    (define get-list-of-binary-digit-and-location-pairs
      (lambda (value start end)
	(if (> start end) '()
	    (let* ((least-digit   (if (number? value)
				      (remainder value 2)
				      'X))
		   (next-value    (if (number? value)
				      (quotient  value 2)
				      'X))
		   )
	      (cons (cons least-digit start)
		    (get-list-of-binary-digit-and-location-pairs
		     next-value
		     (+ start 1)
		     end)
		    )
	      )				; end let
	    )
	)
      )

;;
;; A union describes the same set of bits organized in different ways.
;; An organization  is a set of  one or more regions.   We expand each
;; organization into a list of bit patterns.  A bit pattern of a union
;; is a list of bit patterns of each organization.
;; 
(define get-bit-pattern-lists-of-all-unions
  (lambda (lou)
    (if (null? lou) '()
	(let* ((curr-union       (car    lou))
	       (curr-union-list  (cadr   curr-union))
	       (bpcul            (get-bit-pattern-lists-of-one-union   curr-union-list))
	       (rest-unions      (cdr    lou)))
	  (begin
	    (pp "=== Current union is: ")
	    (pp curr-union)
	    (newline)
	    (pp "=== Current union list is: ")
	    (pp curr-union-list)
	    (newline)
	    (pp "=== Bit pattern of current union list is: ")
	    (pp bpcul)
	    (newline)
	    (pp "=== Continuing to get the bit pattern of rest of the union list ... ")
	    (pp rest-unions)
	    (newline)
	    (pp "====")
	    (newline)
	    (cons bpcul
		  (get-bit-pattern-lists-of-all-unions  rest-unions))
	  )
	  ))))

;; Return a list of bit patterns of union for each organization.
(define get-bit-pattern-lists-of-one-union
  (lambda (loriu)
    (if (null? loriu) '()
	(begin
	  (pp "Given union is: ")
	  (pp loriu)
	  (newline)
	  (let* ((curr-region  (car  loriu))
		 (rest-region  (cdr  loriu))
		 (cr-bits      (flatten
				(reverse
				 (get-bit-pattern-list-of-a-region
				  curr-region)))))
	    (begin
	      (pp "Current region is: ")
	      (pp curr-region)
	      (newline)
	      (pp "Rest of the regions are: ")
	      (pp rest-region)
	      (newline)
	      (pp "Bits of current region are: ")
	      (pp cr-bits)
	      (newline)
	      (cons cr-bits
		    (get-bit-pattern-lists-of-one-union  rest-region)
		    ))
	    )
	  )
	)))

(define get-bit-pattern-list-of-a-region
  (lambda (r)
    (if (null? r) r
        (let* ((a-region (car  r))
	       (rest     (cdr  r))
	       (attribs  (cadr a-region))
               (name     (get-val-of attribs 'name))
               (start    (get-val-of attribs 'start))
               (end      (get-val-of attribs 'end))
               (meaning  (get-val-of attribs 'meaning))
               (val-det  (get-val-of attribs 'setup))
               (the-val  (get-val-of val-det 'value))
	       (the-rep  (get-val-of val-det 'value-representation))
	       (the-typ  (get-val-of val-det 'value-type))
	       )
	  (cons (get-list-of-binary-digit-and-location-pairs
		 the-val
		 start
		 end)
		(get-bit-pattern-list-of-a-region rest)
	   )
	  )
     )))

(define	rlst  (get-insn-opcode-layout               insn-description))
(define lor   (get-list-of-regions-in-insn          insn-description))
(define lou   (get-list-of-unions-in-insn           insn-description))
(define xlst  (get-bit-pattern-list-of-a-region     lor))
(define ulst  (get-bit-pattern-lists-of-all-unions  lou))

;; (define get-insn-bit-pattern
;;   (lambda (insn)
;;     (let ((layout    (get-insn-opcode-layout  insn)))
;;       (if (null? layout)
;; 	  '()
;; 	  (let* ((curr-comp   (car layout))
;; 		 (rest-comp   (cdr layout))
;; 		 )
;; 	   )
;; 	  )
;;        )
;;     ))

;; (close-output-port (current-output-port))
;; (define current-output-port old-output-port)
