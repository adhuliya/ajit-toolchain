;;
;; INSN Language
;;
(load "cpu-layout.scm")
(load "insn-layout.scm")

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

(define insn-description
  '((mnemonic-class "ADD")
    (insn-subtype SPARC_INTEGER_ARITHMETIC)
    (alignment-type ALIGN_WORD)
    (length-in-bits  32)
    (format-type 2)
    (bit-order BIG)
    ;; Use  expansion  keys to  setup up  a multidimensional  dispatch
    ;; system that will locate  information based on the "coordinates"
    ;; (i.e. specific values of the keys) of each dimension!
    ;;
    ;; For  example, in the  situation below the number  of dimensions
    ;;   are  equal   to  (length   expansion-keys),  i.e.    2.   The
    ;;  SPARC_OP_FORMAT_THREE has  4 (=  (length setup))  coordinates.
    ;; The SPARC_BIT_I has 2  (= (length setup)) coordinates.  We will
    ;;  have a  2 dimensional  table of  4 rows  and 2  columns.  Each
    ;; element  of the table should  be populated by all  the relevant
    ;;  information and  procedures.  For  example, for  a simple  add
    ;;  operation   with  immediate  operands,  a   pair  of  checking
    ;;      predicates       namely      (check-simple-add-p)      and
    ;;  (check-if-second-operand-is-immediate-p)  are   added  to  the
    ;;  element.  These  are to  be used  to build  a chain  of checks
    ;; during assembly.
    (expansion-keys ((SPARC_OP_FORMAT_THREE (setup (((value 00000)
						     (mnemonic "ADD")
						     (check-predicate  check-simple-add-p)
						     (description "Simple add"))
						    ((value 01000)
						     (mnemonic "ADDcc")
						     (check-predicate  check-add-and-set-cc-p)
						     (description "Add and set integer CC"))
						    ((value 00100)
						     (mnemonic "ADDX")
						     (check-predicate  check-add-with-carry-p)
						     (description "Add with carry"))
						    ((value 01100)
						     (mnemonic "ADDXcc")
						     (check-predicate  check-add-with-carry-and-set-cc-p)
						     (description "Add with carry and set integer CC"))))
					    )
		     (SPARC_BIT_I (setup (((value 1)
					   (check-predicate  check-if-second-operand-is-immediate-p)
					   (description "Add immediate"))
					  ((value 0)
					   (check-predicate  check-if-second-operand-is-register-p)
					   (description "Add using RS2"))))
				  )
		     )
		    )
    (opcode-layout ((region ((name "op")
			     (start 30)
			     (end 31)
			     (length (end - start + 1))
			     (meaning SPARC_OP_FORMAT_ONE)
			     (setup ((value 10)
				     (value-representation BINARY)
				     (value-type OPCODE)
				     ))))
		    (region ((name "rd")
			     (start 25)
			     (end 29)
			     (length (end - start + 1))
			     (meaning SPARC_DESTINATION_REGISTER)
			     (setup ((value XXXXX)
				     (value-representation BINARY)
				     (value-type REGISTER)
				     ))))
		    (region ((name "op3")
			     (start 19)
			     (end 24)
			     (length (end - start + 1))
			     (meaning SPARC_OP_FORMAT_THREE)
			     (setup ((value 000000)
				     (value-representation BINARY)
				     (value-type OPCODE)
				     )
				    )))
		    (region ((name "rs1")
			     (start 14)
			     (end 18)
			     (length (end - start + 1))
			     (meaning SPARC_SOURCE_REGISTER_ONE)
			     (setup ((value XXXXX)
				     (value-representation BINARY)
				     (value-type REGISTER)
				     ))))
		    (union		;; Region layout depends on value of "i" bit!
		     (			;; LIST of different layouts of the SAME region
		      (                  ;; Describe layout of SAME region when i = 0
		       (region ((name "i")
				(start 13)
				(end 13)
				(length (end - start + 1))
				(meaning SPARC_BIT_I)
				(setup ((value 0)
					(value-representation BINARY)
					(value-type OPCODE)
					))))
		       (region ((name "unused")
				(start 5)
				(end 12)
				(length (end - start + 1))
				(meaning SPARC_UNUSED)
				(setup ((value 00000000)
					(value-representation BINARY)
					(value-type UNUSED)
					))))
		       (region ((name "rs2")
				(start 0)
				(end 4)
				(length (region-end - region-start + 1))
				(meaning SPARC_SOURCE_REGISTER_TWO)
				(setup ((value XXXXX)
					(value-representation BINARY)
					(value-type REGISTER)
					))))
		       )
		      (                  ;; Describe layout of SAME region when i = 0
		       (region ((name "i")
				(start 13)
				(end 13)
				(length (end - start + 1))
				(meaning SPARC_BIT_I)
				(setup ((value 1)
					(value-representation BINARY)
					(value-type OPCODE)
					))))
		       (region ((name "simm13")
				(start 0)
				(end 12)
				(length (end - start + 1))
				(meaning SPARC_SIMM_13)
				(setup ((value XXXXXXXXXXXXX)
					(value-representation BINARY)
					(value-type VALUE)
					))))
		       )
		      )			;; END LIST of union layouts
		     )			;; END union
		    )			;; END opcode layout
		   )
    ))

			       


