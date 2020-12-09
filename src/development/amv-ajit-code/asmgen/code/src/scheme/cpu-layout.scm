;;
;; Layout of the SPARC V8 CPU
;;

(define register-types
  '('('description-type BIT_FLAG)
    '(SPARC_GENERAL_PURPOSE
      SPARC_DATA_REGISTER
      SPARC_CONTROL_REGISTER
      SPARC_STATUS_REGISTER
      ALL_SPARC_REGISTER_TYPES
      )
    ))

(define register-file			;; Anshuman's GOLI
  '((('class 'global)
      ('range-min 0)
      ('range-max 7)
      )
    (('class 'input)
      ('range-min 8)
      ('range-max 15)
      )
    (('class 'local)
      ('range-min 16)
      ('range-max 23)
      )
    (('class 'output)
      ('range-min 24)
      ('range-max 31)
      )
    ))

(define bit-order
  '(
    LITTLE_ENDIAN
    BIG_ENDIAN		;; SPARC is BIG Endian
    ))



