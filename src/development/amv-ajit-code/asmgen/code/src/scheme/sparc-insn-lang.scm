;;
;; SPARC V8 + AJIT Description.
;;
;; References: The SPArc V8 manual + AJIT documents.

;;
;; We mainly implement  the SPARC V8, with AJIT  as "extensions".  The
;; variables and functions for AJIT will be explicitly marked with the
;; "AJIT" prefix or suffix string.   There is no separate mechanism to
;; "extend".

;; We  design this  following  the  SPARC V8  manual  layout.  As  the
;; chapters are read, their relevant content is included here.

;; Chapter 2: Overview
(define sparc-processor
  '(units '('(integer-unit '(to-be-defined-attributes-like-registers-etc))
	    '(floating-point-unit '(to-be-defined-attributes-like-registers-etc))
	    '(coprocessor-unit    '(('optional . #t) '(to-be-defined-attributes-like-registers-etc)))
	    )
	  )
  '(execution-modes '('supervisor 'user))
  )
