/* 
 * NOTES:
 *
 * A bit pattern is characterised by:
 *
 * 1. Type -- instruction or data (ignore "data" :-) ).
 * 1.1 Sub types -- If instruction, then which type? (e.g. arith, logic etc.)
 *                  If data, then which type? (e.g. int, float etc.)
 * 2. Size -- 8 bit, 16 bit, ...
 * 3. Alignment -- 8 bit, 16 bit, ...
 * 4. Ordering -- Little or Big Endian.
 * 5. Layout -- which bits represent what
 * 5.1  Region -- Start and End
 * 5.2  Meaning -- what is being represented (depends on code or data).
 */

#define  MAX_MNEMONIC_LENGTH      42
#define  MAX_REGION_NAME          1024
#define  MAX_INSNS                4096
#define  MAX_LAYOUT               128 /* max 128 bit data type, 1 Quad word */

typedef enum region_meanings {
  AJIT_SPARC_INSN_FORMAT = 0,
  AJIT_SPARC_DESTINATION_REGISTER,
  AJIT_SPARC_SOURCE_REGISTER_ONE,
  AJIT_SPARC_SOURCE_REGISTER_TWO,
  AJIT_OP_FORMAT_ONE,
  AJIT_OP_FORMAT_TWO,
  AJIT_OP_FORMAT_THREE,
  AJIT_ANNUL_BIT,
  AJIT_CONDITION_CODE_MASK,
  AJIT_IMMEDIATE_22,
  AJIT_DISPLACEMENT_22,
  AJIT_DISPLACEMENT_30,
  AJIT_BIT_I,
  AJIT_ASI,			/* address space identifier */
  AJIT_SIMM_13,			/* Signed Immediate. Depends on AJIT_BIT_I. */
  AJIT_OPF,			/* Floating point op, or CoProcessor op. */
  ALL_AJIT_SPARC_REGION_MEANINGS,
} AJIT_REGION_MEANING;

typedef enum align {
  ALIGN_BYTE = 0,		/*  1 Byte */
  ALIGN_HALF_WORD,		/*  2 Bytes, 1 Half word */
  ALIGN_WORD,			/*  4 Bytes, 2 Half words, 1 Word */
  ALIGN_DOUBLE_WORD,		/*  8 Bytes, 4 Half words, 2 Words, 1 Double word */
  ALIGN_QUAD_WORD,		/* 16 Bytes, 8 Half words, 4 Words, 2 Double words, 1 Quada word */
} ALIGNMENT;

typedef enum bit_order {
  AJIT_LITTLE = 0,
  AJIT_BIG,			/* SPARC is BIG Endian */
} AJIT_ORDERING;
  
typedef enum insn_group {	   /* SPARC V8 has 6 categories.  AJIT
				      defines few more */
  AJIT_SPARC_LOAD_STORE = 0,	   /* SPARC V8: Category 1. */
  AJIT_SPARC_INTEGER_ARITHMETIC,   /* SPARC V8: Category 2. */
  AJIT_SPARC_CONTROL_TRANSFER,	   /* SPARC V8: Category 3. */
  AJIT_SPARC_RW_CONTROL_REGISTER,  /* SPARC V8: Category 4. */
  AJIT_SPARC_FLOAT_PT_OP,	   /* SPARC V8: Category 5. */
  AJIT_SPARC_COPROC_OP,	           /* SPARC V8: Category 6. */
  AJIT_ADD_SUB,		           /* AJIT Category 1. */
  AJIT_SHIFT,		           /* AJIT Category 2. */
  AJIT_MUL_DIV,		           /* AJIT Category 3. */
  AJIT_64BIT_LOGICAL,	           /* AJIT Category 4. */
  AJIT_SIMD_I,		           /* AJIT Category 5. */
  AJIT_SIMD_II,		           /* AJIT Category 6. */
  AJIT_SIMD_FLOAT,	           /* AJIT Category 7. */
  ALL_AJIT_INSN_GROUPS,		/* This must  be last. It  denotes the
				   number of groups. */
} AJIT_INSN_SUBTYPE;

typedef enum bit_field_type {	/* Gleaned from  SPARC V8 architecture
				   manual. */
  AJIT_USED = 0,		/* Used but ignored, e.g. op code bits */
  AJIT_REGISTER,		/* Specify some registers */
  AJIT_OPCODE,			/* Used to build the op code */
  AJIT_UNUSED,
  ALL_AJIT_BIT_FIELD_TYPES,
} AJIT_BIT_FIELD_TYPE;		/* Not very useful as details are required. */
  
typedef struct region {
  char               region_name [MAX_REGION_NAME];
  int                start;	/* Always non-negative. */
  int                end;	/* Always non-negative, and never less than "start". */
  int                length;	/* Computed from above two. Always non-negative. */
} AJIT_BIT_REGION_SPEC;

typedef struct layout {
  AJIT_BIT_REGION_SPEC region;
  AJIT_REGION_MEANING  meaning;
} AJIT_INSN_LAYOUT;

typedef struct ajit_insn {
  char               mnemonic [MAX_MNEMONIC_LENGTH]; /* The mnemonic string */
  AJIT_INSN_SUBTYPE  subtype;			     /* Arithmetic, Logic, ... etc. */
  int                num_bits;			     /* 32 or 64 */
  ALIGNMENT          align;			     /* Always BIG for SPARC & AJIT */
  AJIT_ORDERING      order;			     /* Little or big endian */
  AJIT_INSN_LAYOUT   layout[MAX_LAYOUT];	     /* An array of layout details */
} AJIT_INSN;

