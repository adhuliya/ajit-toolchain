;;
;; Layout of SPARC V8 instructions.
;;

(define bit-region-meanings-list
  '(
    SPARC_INSN_FORMAT
    SPARC_DESTINATION_REGISTER
    SPARC_SOURCE_REGISTER_ONE
    SPARC_SOURCE_REGISTER_TWO
    SPARC_OP_FORMAT_ONE
    SPARC_OP_FORMAT_TWO
    SPARC_OP_FORMAT_THREE
    SPARC_ANNUL_BIT
    SPARC_CONDITION_CODE_MASK
    SPARC_IMMEDIATE_22
    SPARC_DISPLACEMENT_22
    SPARC_DISPLACEMENT_30
    SPARC_BIT_I		;; ALU second operand selector.
    SPARC_ASI		;; address space identifier.
    SPARC_SIMM_13	;; Signed Immediate. Depends on SPARC_BIT_I.
    SPARC_OPF		;; Floating point op, or CoProcessor op.
    SPARC_UNUSED	;; Region is unused
    SPARC_RESERVED
    SPARC_IGNORED
    ALL_SPARC_REGION_MEANINGS
    ))

(define alignment-types
  '(
    ALIGN_BYTE		;;  1 Byte
    ALIGN_HALF_WORD	;;  2 Bytes, 1 Half word
    ALIGN_WORD		;;  4 Bytes, 2 Half words, 1 Word
    ALIGN_DOUBLE_WORD	;;  8 Bytes, 4 Half words, 2 Words, 1 Double word
    ALIGN_QUAD_WORD	;; 16 Bytes, 8 Half words, 4 Words, 2 Double words, 1 Quada word
    ))

(define insn-subtype
  '(
    SPARC_LOAD_STORE		;; SPARC V8: Category 1.
    SPARC_INTEGER_ARITHMETIC	;; SPARC V8: Category 2.
    SPARC_CONTROL_TRANSFER	;; SPARC V8: Category 3.
    SPARC_RW_CONTROL_REGISTER	;; SPARC V8: Category 4.
    SPARC_FLOAT_PT_OP		;; SPARC V8: Category 5.
    SPARC_COPROC_OP		;; SPARC V8: Category 6.
    AJIT_ADD_SUB		;; AJIT Category 1.
    AJIT_SHIFT		        ;; AJIT Category 2.
    AJIT_MUL_DIV		;; AJIT Category 3.
    AJIT_64BIT_LOGICAL		;; AJIT Category 4.
    AJIT_SIMD_I		        ;; AJIT Category 5.
    AJIT_SIMD_II		;; AJIT Category 6.
    AJIT_SIMD_FLOAT		;; AJIT Category 7.
    ALL_AJIT_INSN_GROUPS		;; This must  be last. It  denotes the number of groups.
    ))

(define bit-field-type
  '(
    USED		;; Used and not ignored; these mean something
    REGISTER		;; Specify some registers
    OPCODE		;; Used to build the op code
    RESERVED		;; Unused but reserved
    IGNORED		;; Used but ignored, e.g. op code bits
    LOCATION		;; Used to specify primary memory location
    VALUE		;; Explicit number, e.g. immediate operands
    UNUSED
    ALL_AJIT_BIT_FIELD_TYPES
    ))

(define value-representation
  '(BINARY
    OCTAL
    DECIMAL
    HEXADECIMAL
    ))



