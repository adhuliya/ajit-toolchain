/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 24 "ldgram.y" /* yacc.c:339  */

/*

 */

#define DONTDECLARE_MALLOC

#include "sysdep.h"
#include "bfd.h"
#include "bfdlink.h"
#include "ld.h"
#include "ldexp.h"
#include "ldver.h"
#include "ldlang.h"
#include "ldfile.h"
#include "ldemul.h"
#include "ldmisc.h"
#include "ldmain.h"
#include "mri.h"
#include "ldctor.h"
#include "ldlex.h"

#ifndef YYDEBUG
#define YYDEBUG 1
#endif

static enum section_type sectype;
static lang_memory_region_type *region;

bfd_boolean ldgram_had_keep = FALSE;
char *ldgram_vers_current_lang = NULL;

#define ERROR_NAME_MAX 20
static char *error_names[ERROR_NAME_MAX];
static int error_index;
#define PUSH_ERROR(x) if (error_index < ERROR_NAME_MAX) error_names[error_index] = x; error_index++;
#define POP_ERROR()   error_index--;

#line 105 "ldgram.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    NAME = 259,
    LNAME = 260,
    PLUSEQ = 261,
    MINUSEQ = 262,
    MULTEQ = 263,
    DIVEQ = 264,
    LSHIFTEQ = 265,
    RSHIFTEQ = 266,
    ANDEQ = 267,
    OREQ = 268,
    OROR = 269,
    ANDAND = 270,
    EQ = 271,
    NE = 272,
    LE = 273,
    GE = 274,
    LSHIFT = 275,
    RSHIFT = 276,
    UNARY = 277,
    END = 278,
    ALIGN_K = 279,
    BLOCK = 280,
    BIND = 281,
    QUAD = 282,
    SQUAD = 283,
    LONG = 284,
    SHORT = 285,
    BYTE = 286,
    SECTIONS = 287,
    PHDRS = 288,
    INSERT_K = 289,
    AFTER = 290,
    BEFORE = 291,
    DATA_SEGMENT_ALIGN = 292,
    DATA_SEGMENT_RELRO_END = 293,
    DATA_SEGMENT_END = 294,
    SORT_BY_NAME = 295,
    SORT_BY_ALIGNMENT = 296,
    SORT_BY_INIT_PRIORITY = 297,
    SIZEOF_HEADERS = 298,
    OUTPUT_FORMAT = 299,
    FORCE_COMMON_ALLOCATION = 300,
    OUTPUT_ARCH = 301,
    INHIBIT_COMMON_ALLOCATION = 302,
    SEGMENT_START = 303,
    INCLUDE = 304,
    MEMORY = 305,
    REGION_ALIAS = 306,
    LD_FEATURE = 307,
    NOLOAD = 308,
    DSECT = 309,
    COPY = 310,
    INFO = 311,
    OVERLAY = 312,
    DEFINED = 313,
    TARGET_K = 314,
    SEARCH_DIR = 315,
    MAP = 316,
    ENTRY = 317,
    NEXT = 318,
    SIZEOF = 319,
    ALIGNOF = 320,
    ADDR = 321,
    LOADADDR = 322,
    MAX_K = 323,
    MIN_K = 324,
    STARTUP = 325,
    HLL = 326,
    SYSLIB = 327,
    FLOAT = 328,
    NOFLOAT = 329,
    NOCROSSREFS = 330,
    ORIGIN = 331,
    FILL = 332,
    LENGTH = 333,
    CREATE_OBJECT_SYMBOLS = 334,
    INPUT = 335,
    GROUP = 336,
    OUTPUT = 337,
    CONSTRUCTORS = 338,
    ALIGNMOD = 339,
    AT = 340,
    SUBALIGN = 341,
    PROVIDE = 342,
    PROVIDE_HIDDEN = 343,
    AS_NEEDED = 344,
    CHIP = 345,
    LIST = 346,
    SECT = 347,
    ABSOLUTE = 348,
    LOAD = 349,
    NEWLINE = 350,
    ENDWORD = 351,
    ORDER = 352,
    NAMEWORD = 353,
    ASSERT_K = 354,
    FORMAT = 355,
    PUBLIC = 356,
    DEFSYMEND = 357,
    BASE = 358,
    ALIAS = 359,
    TRUNCATE = 360,
    REL = 361,
    INPUT_SCRIPT = 362,
    INPUT_MRI_SCRIPT = 363,
    INPUT_DEFSYM = 364,
    CASE = 365,
    EXTERN = 366,
    START = 367,
    VERS_TAG = 368,
    VERS_IDENTIFIER = 369,
    GLOBAL = 370,
    LOCAL = 371,
    VERSIONK = 372,
    INPUT_VERSION_SCRIPT = 373,
    KEEP = 374,
    ONLY_IF_RO = 375,
    ONLY_IF_RW = 376,
    SPECIAL = 377,
    INPUT_SECTION_FLAGS = 378,
    EXCLUDE_FILE = 379,
    CONSTANT = 380,
    INPUT_DYNAMIC_LIST = 381
  };
#endif
/* Tokens.  */
#define INT 258
#define NAME 259
#define LNAME 260
#define PLUSEQ 261
#define MINUSEQ 262
#define MULTEQ 263
#define DIVEQ 264
#define LSHIFTEQ 265
#define RSHIFTEQ 266
#define ANDEQ 267
#define OREQ 268
#define OROR 269
#define ANDAND 270
#define EQ 271
#define NE 272
#define LE 273
#define GE 274
#define LSHIFT 275
#define RSHIFT 276
#define UNARY 277
#define END 278
#define ALIGN_K 279
#define BLOCK 280
#define BIND 281
#define QUAD 282
#define SQUAD 283
#define LONG 284
#define SHORT 285
#define BYTE 286
#define SECTIONS 287
#define PHDRS 288
#define INSERT_K 289
#define AFTER 290
#define BEFORE 291
#define DATA_SEGMENT_ALIGN 292
#define DATA_SEGMENT_RELRO_END 293
#define DATA_SEGMENT_END 294
#define SORT_BY_NAME 295
#define SORT_BY_ALIGNMENT 296
#define SORT_BY_INIT_PRIORITY 297
#define SIZEOF_HEADERS 298
#define OUTPUT_FORMAT 299
#define FORCE_COMMON_ALLOCATION 300
#define OUTPUT_ARCH 301
#define INHIBIT_COMMON_ALLOCATION 302
#define SEGMENT_START 303
#define INCLUDE 304
#define MEMORY 305
#define REGION_ALIAS 306
#define LD_FEATURE 307
#define NOLOAD 308
#define DSECT 309
#define COPY 310
#define INFO 311
#define OVERLAY 312
#define DEFINED 313
#define TARGET_K 314
#define SEARCH_DIR 315
#define MAP 316
#define ENTRY 317
#define NEXT 318
#define SIZEOF 319
#define ALIGNOF 320
#define ADDR 321
#define LOADADDR 322
#define MAX_K 323
#define MIN_K 324
#define STARTUP 325
#define HLL 326
#define SYSLIB 327
#define FLOAT 328
#define NOFLOAT 329
#define NOCROSSREFS 330
#define ORIGIN 331
#define FILL 332
#define LENGTH 333
#define CREATE_OBJECT_SYMBOLS 334
#define INPUT 335
#define GROUP 336
#define OUTPUT 337
#define CONSTRUCTORS 338
#define ALIGNMOD 339
#define AT 340
#define SUBALIGN 341
#define PROVIDE 342
#define PROVIDE_HIDDEN 343
#define AS_NEEDED 344
#define CHIP 345
#define LIST 346
#define SECT 347
#define ABSOLUTE 348
#define LOAD 349
#define NEWLINE 350
#define ENDWORD 351
#define ORDER 352
#define NAMEWORD 353
#define ASSERT_K 354
#define FORMAT 355
#define PUBLIC 356
#define DEFSYMEND 357
#define BASE 358
#define ALIAS 359
#define TRUNCATE 360
#define REL 361
#define INPUT_SCRIPT 362
#define INPUT_MRI_SCRIPT 363
#define INPUT_DEFSYM 364
#define CASE 365
#define EXTERN 366
#define START 367
#define VERS_TAG 368
#define VERS_IDENTIFIER 369
#define GLOBAL 370
#define LOCAL 371
#define VERSIONK 372
#define INPUT_VERSION_SCRIPT 373
#define KEEP 374
#define ONLY_IF_RO 375
#define ONLY_IF_RW 376
#define SPECIAL 377
#define INPUT_SECTION_FLAGS 378
#define EXCLUDE_FILE 379
#define CONSTANT 380
#define INPUT_DYNAMIC_LIST 381

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 62 "ldgram.y" /* yacc.c:355  */

  bfd_vma integer;
  struct big_int
    {
      bfd_vma integer;
      char *str;
    } bigint;
  fill_type *fill;
  char *name;
  const char *cname;
  struct wildcard_spec wildcard;
  struct wildcard_list *wildcard_list;
  struct name_list *name_list;
  struct flag_info_list *flag_info_list;
  struct flag_info *flag_info;
  int token;
  union etree_union *etree;
  struct phdr_info
    {
      bfd_boolean filehdr;
      bfd_boolean phdrs;
      union etree_union *at;
      union etree_union *flags;
    } phdr;
  struct lang_nocrossref *nocrossref;
  struct lang_output_section_phdr_list *section_phdr;
  struct bfd_elf_version_deps *deflist;
  struct bfd_elf_version_expr *versyms;
  struct bfd_elf_version_tree *versnode;

#line 428 "ldgram.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 445 "ldgram.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1901

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  150
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  128
/* YYNRULES -- Number of rules.  */
#define YYNRULES  364
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  787

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   381

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   148,     2,     2,     2,    34,    21,     2,
      37,   145,    32,    30,   143,    31,     2,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    16,   144,
      24,    10,    25,    15,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   146,     2,   147,    20,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,    19,    58,   149,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    11,    12,    13,    14,    17,
      18,    22,    23,    26,    27,    28,    29,    35,    36,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   168,   168,   169,   170,   171,   172,   176,   180,   180,
     190,   190,   203,   204,   208,   209,   210,   213,   216,   217,
     218,   220,   222,   224,   226,   228,   230,   232,   234,   236,
     238,   240,   241,   242,   244,   246,   248,   250,   252,   253,
     255,   254,   258,   260,   264,   265,   266,   270,   272,   276,
     278,   283,   284,   285,   290,   290,   295,   297,   299,   304,
     304,   310,   311,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   328,   330,   332,   335,   337,   339,
     341,   343,   345,   344,   348,   351,   350,   354,   358,   359,
     361,   363,   365,   370,   373,   376,   379,   382,   385,   389,
     388,   393,   392,   397,   396,   403,   407,   408,   409,   413,
     415,   416,   416,   424,   428,   432,   439,   446,   453,   460,
     467,   474,   481,   488,   495,   502,   511,   529,   550,   563,
     572,   583,   592,   603,   612,   621,   625,   634,   638,   646,
     648,   647,   654,   655,   659,   660,   665,   670,   671,   676,
     680,   680,   684,   683,   690,   691,   694,   696,   700,   702,
     704,   706,   708,   713,   720,   722,   726,   728,   730,   732,
     734,   736,   738,   740,   745,   745,   750,   754,   762,   766,
     774,   774,   778,   781,   781,   784,   785,   790,   789,   795,
     794,   801,   809,   817,   818,   822,   823,   827,   829,   834,
     839,   840,   845,   847,   853,   855,   857,   861,   863,   869,
     872,   881,   892,   892,   898,   900,   902,   904,   906,   908,
     911,   913,   915,   917,   919,   921,   923,   925,   927,   929,
     931,   933,   935,   937,   939,   941,   943,   945,   947,   949,
     951,   953,   956,   958,   960,   962,   964,   966,   968,   970,
     972,   974,   976,   978,   987,   989,   991,   993,   995,   997,
     999,  1005,  1006,  1010,  1011,  1015,  1016,  1020,  1021,  1025,
    1026,  1027,  1028,  1031,  1035,  1038,  1044,  1046,  1031,  1053,
    1055,  1057,  1062,  1064,  1052,  1074,  1076,  1074,  1082,  1081,
    1088,  1089,  1090,  1091,  1092,  1096,  1097,  1098,  1102,  1103,
    1108,  1109,  1114,  1115,  1120,  1121,  1126,  1128,  1133,  1136,
    1149,  1153,  1158,  1160,  1151,  1168,  1171,  1173,  1177,  1178,
    1177,  1187,  1232,  1235,  1247,  1256,  1259,  1266,  1266,  1278,
    1279,  1283,  1287,  1296,  1296,  1310,  1310,  1320,  1321,  1325,
    1329,  1333,  1340,  1344,  1352,  1355,  1359,  1363,  1367,  1374,
    1378,  1382,  1386,  1391,  1390,  1404,  1403,  1413,  1417,  1421,
    1425,  1429,  1433,  1439,  1441
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "NAME", "LNAME", "PLUSEQ",
  "MINUSEQ", "MULTEQ", "DIVEQ", "'='", "LSHIFTEQ", "RSHIFTEQ", "ANDEQ",
  "OREQ", "'?'", "':'", "OROR", "ANDAND", "'|'", "'^'", "'&'", "EQ", "NE",
  "'<'", "'>'", "LE", "GE", "LSHIFT", "RSHIFT", "'+'", "'-'", "'*'", "'/'",
  "'%'", "UNARY", "END", "'('", "ALIGN_K", "BLOCK", "BIND", "QUAD",
  "SQUAD", "LONG", "SHORT", "BYTE", "SECTIONS", "PHDRS", "INSERT_K",
  "AFTER", "BEFORE", "DATA_SEGMENT_ALIGN", "DATA_SEGMENT_RELRO_END",
  "DATA_SEGMENT_END", "SORT_BY_NAME", "SORT_BY_ALIGNMENT",
  "SORT_BY_INIT_PRIORITY", "'{'", "'}'", "SIZEOF_HEADERS", "OUTPUT_FORMAT",
  "FORCE_COMMON_ALLOCATION", "OUTPUT_ARCH", "INHIBIT_COMMON_ALLOCATION",
  "SEGMENT_START", "INCLUDE", "MEMORY", "REGION_ALIAS", "LD_FEATURE",
  "NOLOAD", "DSECT", "COPY", "INFO", "OVERLAY", "DEFINED", "TARGET_K",
  "SEARCH_DIR", "MAP", "ENTRY", "NEXT", "SIZEOF", "ALIGNOF", "ADDR",
  "LOADADDR", "MAX_K", "MIN_K", "STARTUP", "HLL", "SYSLIB", "FLOAT",
  "NOFLOAT", "NOCROSSREFS", "ORIGIN", "FILL", "LENGTH",
  "CREATE_OBJECT_SYMBOLS", "INPUT", "GROUP", "OUTPUT", "CONSTRUCTORS",
  "ALIGNMOD", "AT", "SUBALIGN", "PROVIDE", "PROVIDE_HIDDEN", "AS_NEEDED",
  "CHIP", "LIST", "SECT", "ABSOLUTE", "LOAD", "NEWLINE", "ENDWORD",
  "ORDER", "NAMEWORD", "ASSERT_K", "FORMAT", "PUBLIC", "DEFSYMEND", "BASE",
  "ALIAS", "TRUNCATE", "REL", "INPUT_SCRIPT", "INPUT_MRI_SCRIPT",
  "INPUT_DEFSYM", "CASE", "EXTERN", "START", "VERS_TAG", "VERS_IDENTIFIER",
  "GLOBAL", "LOCAL", "VERSIONK", "INPUT_VERSION_SCRIPT", "KEEP",
  "ONLY_IF_RO", "ONLY_IF_RW", "SPECIAL", "INPUT_SECTION_FLAGS",
  "EXCLUDE_FILE", "CONSTANT", "INPUT_DYNAMIC_LIST", "','", "';'", "')'",
  "'['", "']'", "'!'", "'~'", "$accept", "file", "filename", "defsym_expr",
  "$@1", "mri_script_file", "$@2", "mri_script_lines",
  "mri_script_command", "$@3", "ordernamelist", "mri_load_name_list",
  "mri_abs_name_list", "casesymlist", "extern_name_list", "$@4",
  "extern_name_list_body", "script_file", "$@5", "ifile_list", "ifile_p1",
  "$@6", "$@7", "input_list", "@8", "@9", "@10", "sections",
  "sec_or_group_p1", "statement_anywhere", "$@11", "wildcard_name",
  "wildcard_spec", "sect_flag_list", "sect_flags", "exclude_name_list",
  "file_NAME_list", "input_section_spec_no_keep", "input_section_spec",
  "$@12", "statement", "$@13", "$@14", "statement_list",
  "statement_list_opt", "length", "fill_exp", "fill_opt", "assign_op",
  "end", "assignment", "opt_comma", "memory", "memory_spec_list_opt",
  "memory_spec_list", "memory_spec", "$@15", "$@16", "origin_spec",
  "length_spec", "attributes_opt", "attributes_list", "attributes_string",
  "startup", "high_level_library", "high_level_library_NAME_list",
  "low_level_library", "low_level_library_NAME_list",
  "floating_point_support", "nocrossref_list", "mustbe_exp", "$@17", "exp",
  "memspec_at_opt", "opt_at", "opt_align", "opt_subalign",
  "sect_constraint", "section", "$@18", "$@19", "$@20", "$@21", "$@22",
  "$@23", "$@24", "$@25", "$@26", "$@27", "$@28", "$@29", "$@30", "type",
  "atype", "opt_exp_with_type", "opt_exp_without_type", "opt_nocrossrefs",
  "memspec_opt", "phdr_opt", "overlay_section", "$@31", "$@32", "$@33",
  "phdrs", "phdr_list", "phdr", "$@34", "$@35", "phdr_type",
  "phdr_qualifiers", "phdr_val", "dynamic_list_file", "$@36",
  "dynamic_list_nodes", "dynamic_list_node", "dynamic_list_tag",
  "version_script_file", "$@37", "version", "$@38", "vers_nodes",
  "vers_node", "verdep", "vers_tag", "vers_defns", "@39", "@40",
  "opt_semicolon", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
      61,   265,   266,   267,   268,    63,    58,   269,   270,   124,
      94,    38,   271,   272,    60,    62,   273,   274,   275,   276,
      43,    45,    42,    47,    37,   277,   278,    40,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   123,   125,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
     379,   380,   381,    44,    59,    41,    91,    93,    33,   126
};
# endif

#define YYPACT_NINF -687

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-687)))

#define YYTABLE_NINF -336

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     213,  -687,  -687,  -687,  -687,  -687,    60,  -687,  -687,  -687,
    -687,  -687,    42,  -687,   -16,  -687,    37,  -687,   827,  1603,
      78,    65,    47,   -16,  -687,   105,    37,  -687,  1001,    59,
      66,   184,    90,  -687,   103,  -687,   220,   131,   193,   201,
     209,   212,   245,   250,   254,   273,   289,  -687,  -687,   290,
     293,  -687,   294,   298,   304,  -687,   305,  -687,  -687,  -687,
    -687,    98,  -687,  -687,  -687,  -687,  -687,  -687,  -687,   146,
    -687,   340,   220,   342,   674,  -687,   344,   355,   356,  -687,
    -687,   359,   363,   364,   674,   370,   374,   377,  -687,   385,
     277,   674,  -687,   386,  -687,   379,   380,   339,   264,    65,
    -687,  -687,  -687,   349,   276,  -687,  -687,  -687,  -687,  -687,
    -687,  -687,  -687,  -687,  -687,  -687,  -687,  -687,   417,   418,
     419,   423,  -687,  -687,    43,   424,   425,   426,   220,   220,
     427,   220,    14,  -687,   431,    46,   399,   220,   433,   434,
     402,  -687,  -687,  -687,  -687,   383,     1,  -687,    32,  -687,
    -687,   674,   674,   674,   404,   405,   407,   408,   414,  -687,
     416,   420,   421,   428,   429,   435,   436,   444,   445,   446,
     447,   448,   449,   451,   674,   674,  1417,   395,  -687,   312,
    -687,   313,    12,  -687,  -687,   515,  1851,   317,  -687,  -687,
     319,  -687,   459,  -687,  -687,  1851,   411,   105,   105,   320,
     113,   412,   327,   113,  -687,   674,  -687,   267,    35,  -687,
    -687,   -15,   348,  -687,  -687,   220,   437,    -2,  -687,   351,
     352,   357,   358,   360,   366,   367,  -687,  -687,   121,   156,
      18,   368,  -687,  -687,   454,    15,    46,   369,   482,   490,
     674,   371,   -16,   674,   674,  -687,   674,   674,  -687,  -687,
     836,   674,   674,   674,   674,   674,   497,   504,   674,   511,
     513,   516,   517,   674,   674,   518,   519,   674,   674,   520,
    -687,  -687,   674,   674,   674,   674,   674,   674,   674,   674,
     674,   674,   674,   674,   674,   674,   674,   674,   674,   674,
     674,   674,   674,   674,  1851,   522,   524,  -687,   525,   674,
     674,  1851,   129,   526,  -687,    39,  -687,   387,   388,  -687,
    -687,   529,  -687,  -687,  -687,   -70,  -687,  1851,  1001,  -687,
     220,  -687,  -687,  -687,  -687,  -687,  -687,  -687,   531,  -687,
    -687,   902,   500,  -687,  -687,  -687,    43,   535,  -687,  -687,
    -687,  -687,  -687,  -687,  -687,   220,  -687,   220,   431,  -687,
    -687,  -687,  -687,  -687,   503,    48,  -687,    19,  -687,  -687,
    -687,  1437,  -687,   190,  1851,  1851,  1626,  1851,  1851,  -687,
    1030,  1050,  1457,  1477,  1070,   398,   397,  1090,   403,   406,
     410,   413,  1497,  1517,   415,   430,  1110,  1544,   432,  1742,
    1624,  1867,  1010,  1810,  1795,   994,   994,   384,   384,   384,
     384,   226,   226,   240,   240,  -687,  -687,  -687,  1851,  1851,
    1851,  -687,  -687,  -687,  1851,  1851,  -687,  -687,  -687,  -687,
     543,   105,   138,   113,   492,  -687,  -687,   -47,   553,  -687,
     636,   553,   674,   438,  -687,     4,   534,    43,  -687,   440,
    -687,  -687,  -687,    46,  -687,  -687,  -687,   527,  -687,   441,
     442,   555,  -687,  -687,   674,  -687,  -687,   674,   674,  -687,
     674,  -687,  -687,  -687,  -687,  -687,  -687,   674,   674,  -687,
    -687,  -687,   557,  -687,   674,  -687,   457,   547,  -687,  -687,
    -687,   224,   533,  1652,   560,   472,  -687,  -687,  1831,   487,
    -687,  1851,    24,   576,  -687,   578,     2,  -687,   496,   566,
    -687,    31,    46,  -687,  -687,  -687,   458,  1130,  1159,  1179,
    1199,  1219,  1239,   463,  1851,   113,   552,   105,   105,  -687,
    -687,  -687,  -687,  -687,  -687,   466,   674,   242,   597,  -687,
     577,   580,   288,  -687,  -687,   472,   558,   579,   582,  -687,
     475,  -687,  -687,  -687,   611,   480,  -687,  -687,    40,    46,
    -687,  -687,  -687,  -687,  -687,  -687,  -687,  -687,  -687,   481,
     457,  -687,  1259,  -687,   674,   589,   539,  -687,   539,  -687,
     674,    24,   674,   484,  -687,  -687,   537,  -687,    86,   113,
     571,   263,  1288,   674,   605,  -687,  -687,   346,  1308,  -687,
    1328,  -687,  -687,   633,  -687,  -687,  -687,   607,   630,  -687,
    1348,   674,   148,   591,  -687,  -687,    24,  -687,   674,  -687,
    -687,  1368,  -687,  -687,  -687,   592,  -687,  -687,  -687,  1388,
    -687,  -687,  -687,   613,   737,    63,   635,   797,  -687,  -687,
    -687,  -687,  -687,  -687,  -687,   616,   617,   618,   220,   620,
    -687,  -687,  -687,   622,   623,   624,  -687,    83,  -687,   628,
      25,  -687,  -687,  -687,   737,   612,   632,    98,  -687,  -687,
    -687,   235,   347,   114,  -687,  -687,   634,  -687,   668,   114,
    -687,   639,  -687,   -37,    83,   642,    83,   643,  -687,  -687,
    -687,  -687,   625,   656,   646,   647,   540,   649,   545,   654,
     655,   548,   551,   737,   554,  -687,   674,    17,  -687,     9,
    -687,    22,    80,  -687,    83,   177,   -21,    83,   656,   561,
     737,   693,   602,   114,   114,  -687,   114,  -687,   114,   114,
    -687,  -687,   662,  -687,  1564,   562,   563,   705,  -687,   114,
    -687,  -687,  -687,  -687,   178,   602,  -687,   664,  -687,   689,
    -687,   584,   586,    23,   587,   590,  -687,   719,  -687,  -687,
    -687,  -687,  -687,  -687,   720,    76,   594,   595,   114,   598,
     599,   601,    76,  -687,  -687,  -687,   730,  -687,  -687,  -687,
     604,  -687,  -687,    98,  -687,    76,  -687,  -687,   480,  -687,
    -687,   480,  -687,  -687,  -687,   480,  -687
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,    59,    10,     8,   333,   327,     0,     2,    62,     3,
      13,     6,     0,     4,     0,     5,     0,     1,    60,    11,
       0,   344,     0,   334,   337,     0,   328,   329,     0,     0,
       0,     0,     0,    79,     0,    80,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   207,   208,     0,
       0,    82,     0,     0,     0,   111,     0,    72,    61,    64,
      70,     0,    63,    66,    67,    68,    69,    65,    71,     0,
      16,     0,     0,     0,     0,    17,     0,     0,     0,    19,
      46,     0,     0,     0,     0,     0,     0,    51,    54,     0,
       0,     0,   350,   361,   349,   357,   359,     0,     0,   344,
     338,   357,   359,     0,     0,   330,   166,   167,   168,   169,
     212,   170,   171,   172,   173,   212,   108,   316,     0,     0,
       0,     0,     7,    85,   184,     0,     0,     0,     0,     0,
       0,     0,     0,   206,   209,     0,     0,     0,     0,     0,
       0,    54,   175,   174,   110,     0,     0,    40,     0,   240,
     255,     0,     0,     0,     0,     0,     0,     0,     0,   241,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    14,     0,    49,    31,
      47,    32,    18,    33,    23,     0,    36,     0,    37,    52,
      38,    39,     0,    42,    12,     9,     0,     0,     0,     0,
     345,     0,     0,   332,   176,     0,   177,     0,     0,    89,
      90,     0,     0,    62,   187,     0,     0,   181,   186,     0,
       0,     0,     0,     0,     0,     0,   201,   203,   181,   181,
     209,     0,    93,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    13,     0,     0,   218,   214,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     217,   219,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    25,     0,     0,    45,     0,     0,
       0,    22,     0,     0,    56,    55,   355,     0,     0,   339,
     352,   362,   351,   358,   360,     0,   331,   213,   273,   105,
       0,   279,   285,   107,   106,   318,   315,   317,     0,    76,
      78,   335,   193,   189,   182,   180,     0,     0,    92,    73,
      74,    84,   109,   199,   200,     0,   204,     0,   209,   210,
      87,    99,    95,    98,     0,     0,    81,     0,    75,   212,
     212,     0,    88,     0,    27,    28,    43,    29,    30,   215,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     238,   237,   235,   234,   233,   227,   228,   231,   232,   229,
     230,   225,   226,   223,   224,   220,   221,   222,    15,    26,
      24,    50,    48,    44,    20,    21,    35,    34,    53,    57,
       0,     0,   346,   347,     0,   342,   340,     0,   296,   288,
       0,   296,     0,     0,    86,     0,     0,   184,   185,     0,
     202,   205,   211,     0,   103,    94,    97,     0,    83,     0,
       0,     0,   336,    41,     0,   248,   254,     0,     0,   252,
       0,   239,   216,   243,   242,   244,   245,     0,     0,   259,
     260,   247,     0,   246,     0,    58,   363,   360,   353,   343,
     341,     0,     0,   296,     0,   264,   108,   303,     0,   304,
     286,   321,   322,     0,   197,     0,     0,   195,     0,     0,
      91,     0,     0,   101,   178,   179,     0,     0,     0,     0,
       0,     0,     0,     0,   236,   364,     0,     0,     0,   290,
     291,   292,   293,   294,   297,     0,     0,     0,     0,   299,
       0,   266,     0,   302,   305,   264,     0,   325,     0,   319,
       0,   198,   194,   196,     0,   181,   190,   100,     0,     0,
     112,   249,   250,   251,   253,   256,   257,   258,   356,     0,
     363,   295,     0,   298,     0,     0,   268,   289,   268,   108,
       0,   322,     0,     0,    77,   212,     0,   104,     0,   348,
       0,   296,     0,     0,     0,   274,   280,     0,     0,   323,
       0,   320,   191,     0,   188,   102,   354,     0,     0,   263,
       0,     0,   272,     0,   287,   326,   322,   212,     0,   300,
     265,     0,   269,   270,   271,     0,   281,   324,   192,     0,
     267,   275,   310,   296,   156,     0,     0,   133,   115,   114,
     158,   159,   160,   161,   162,     0,     0,     0,     0,     0,
     143,   145,   150,     0,     0,     0,   144,     0,   116,     0,
       0,   139,   147,   155,   157,     0,     0,     0,   311,   282,
     301,     0,     0,     0,   152,   212,     0,   140,     0,     0,
     113,     0,   132,   181,     0,   134,     0,     0,   154,   276,
     212,   142,     0,   307,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   156,     0,   163,     0,     0,   126,     0,
     130,     0,     0,   135,     0,   181,   181,     0,   307,     0,
     156,     0,   262,     0,     0,   146,     0,   118,     0,     0,
     119,   125,     0,   149,     0,   113,     0,     0,   128,     0,
     129,   131,   137,   136,   181,   262,   148,     0,   306,     0,
     308,     0,     0,     0,     0,     0,   153,     0,   141,   127,
     117,   138,   308,   312,     0,   165,     0,     0,     0,     0,
       0,     0,   165,   308,   261,   212,     0,   283,   121,   120,
       0,   122,   123,     0,   277,   165,   164,   309,   181,   124,
     151,   181,   313,   284,   278,   181,   314
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -687,  -687,   -67,  -687,  -687,  -687,  -687,   491,  -687,  -687,
    -687,  -687,  -687,  -687,   596,  -687,  -687,  -687,  -687,   549,
    -687,  -687,  -687,  -221,  -687,  -687,  -687,  -687,  -455,   -14,
    -687,  1087,  -298,  -687,  -687,    26,  -608,    50,  -687,  -687,
      96,  -687,  -687,  -687,  -635,  -687,    -5,  -686,  -687,  -552,
    -591,  -216,  -687,   324,  -687,   439,  -687,  -687,  -687,  -687,
    -687,  -687,   268,  -687,  -687,  -687,  -687,  -687,  -687,  -205,
    -108,  -687,   -74,    28,   230,  -687,   199,  -687,  -687,  -687,
    -687,  -687,  -687,  -687,  -687,  -687,  -687,  -687,  -687,  -687,
    -687,  -687,  -687,  -474,   341,  -687,  -687,    62,  -667,  -687,
    -687,  -687,  -687,  -687,  -687,  -687,  -687,  -687,  -687,  -523,
    -687,  -687,  -687,  -687,   745,  -687,  -687,  -687,  -687,  -687,
     532,   -20,  -687,   677,   -11,  -687,  -687,   227
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,   123,    11,    12,     9,    10,    19,    90,   245,
     182,   181,   179,   190,   191,   192,   305,     7,     8,    18,
      58,   136,   213,   235,   443,   549,   502,    59,   207,   323,
     140,   648,   649,   699,   650,   701,   673,   651,   652,   697,
     653,   666,   693,   654,   655,   656,   694,   767,   115,   144,
      61,   704,    62,   216,   217,   218,   332,   437,   545,   594,
     436,   496,   497,    63,    64,   228,    65,   229,    66,   231,
     695,   205,   250,   740,   531,   566,   585,   615,   324,   428,
     602,   624,   708,   781,   430,   603,   622,   683,   778,   431,
     536,   486,   525,   484,   485,   489,   535,   712,   755,   625,
     682,   763,   785,    67,   208,   327,   432,   573,   492,   539,
     571,    15,    16,    26,    27,   103,    13,    14,    68,    69,
      23,    24,   427,    97,    98,   518,   421,   516
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     176,   336,   204,   100,    60,   147,   494,   206,   494,   528,
     186,   243,   345,   347,   104,   357,   297,   195,   122,   352,
     353,   725,   230,   352,   353,   349,   670,   670,   537,   675,
     727,   532,   628,   657,  -183,   352,   353,   628,   628,   325,
     628,    21,   246,   419,   352,   353,    20,   214,   589,   629,
     232,   233,   445,   446,   629,   629,  -183,   629,   722,   425,
      17,   222,   223,   657,   225,   227,   705,   658,   706,    92,
     237,   671,   636,   637,   426,   737,   774,   248,   249,   671,
     636,   637,   479,   617,   670,   762,   765,   670,    91,   782,
     352,   353,   766,   326,    25,   628,   775,   480,   628,   734,
     270,   271,   657,   294,    99,   681,   335,   598,   215,    92,
     703,   301,   629,    22,   587,   629,   116,   310,   670,   657,
     354,   659,   335,   117,   354,   538,   733,   120,   328,   628,
     329,   317,   416,   417,   684,   685,   354,   671,   636,   637,
     121,   335,   310,   442,   244,   354,   629,   542,   333,   626,
     495,   234,   495,   447,   728,   298,   644,   645,   355,   226,
     356,   348,   355,   647,   448,   645,   361,   729,   758,   364,
     365,   676,   367,   368,   355,   247,   547,   370,   371,   372,
     373,   374,   420,   355,   377,   577,   307,   308,   124,   382,
     383,   354,    93,   386,   387,    94,    95,    96,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   398,   399,   400,
     401,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     687,   780,   501,   645,   122,   414,   415,   149,   150,   355,
     125,   595,    93,   118,   119,    94,   101,   102,   126,   670,
     311,   142,   143,   312,   313,   314,   127,    21,   452,   128,
     628,   449,   450,   429,   151,   152,   286,   287,   288,   289,
     290,   153,   154,   155,   335,   311,   344,   629,   312,   313,
     477,   318,   288,   289,   290,   156,   157,   158,   440,   145,
     441,   548,   129,   159,   612,   613,   614,   130,   160,   684,
     685,   131,   318,   519,   520,   521,   522,   523,   161,   335,
     527,   346,   597,   162,   163,   164,   165,   166,   167,   168,
     132,   519,   520,   521,   522,   523,   169,    60,   170,    22,
     335,   335,   732,   751,   567,   319,   133,   134,   578,   576,
     135,   137,   320,   171,   686,   138,     1,     2,     3,   172,
     321,   139,   141,   100,   146,    43,   148,     4,   177,   672,
     318,   670,   677,   320,   483,     5,   488,   483,   491,   178,
     180,   321,   628,   183,   322,   173,    43,   184,   185,   524,
      53,    54,   174,   175,   187,   687,   672,   188,   672,   629,
     507,   189,    55,   508,   509,   322,   510,   524,   194,   193,
     196,    53,    54,   511,   512,   197,   198,   199,   149,   150,
     514,   689,   690,    55,   604,   292,   731,   202,   200,   672,
     476,   320,   284,   285,   286,   287,   288,   289,   290,   321,
     203,   209,   210,   211,    43,   151,   152,   212,   219,   220,
     221,   224,   153,   154,   155,   230,   236,   238,   239,   240,
     242,   251,   252,   322,   253,   254,   156,   157,   158,    53,
      54,   255,   562,   256,   159,   295,   296,   257,   258,   160,
     302,    55,   303,   304,   309,   259,   260,   592,   306,   161,
     315,   316,   261,   262,   162,   163,   164,   165,   166,   167,
     168,   263,   264,   265,   266,   267,   268,   169,   269,   170,
     582,   351,   359,   330,   337,   334,   588,   338,   590,   618,
     360,   375,   339,   340,   171,   341,   559,   560,   376,   600,
     172,   342,   343,   350,   358,   378,   362,   379,   149,   150,
     380,   381,   384,   385,   388,   299,   411,   611,   412,   413,
     418,   422,   423,   424,   619,   433,   173,   435,   293,   439,
     444,   460,   461,   174,   175,   151,   152,   475,   463,   478,
     498,   464,   153,   154,   155,   465,   149,   150,   466,   506,
     469,   513,   783,   517,   503,   784,   156,   157,   158,   786,
     526,   664,   709,   530,   159,   470,   529,   473,   534,   160,
     540,   493,   541,   151,   152,   500,   504,   505,   544,   161,
     481,   154,   155,   482,   162,   163,   164,   165,   166,   167,
     168,   515,   546,   550,   156,   157,   158,   169,   557,   170,
     558,   561,   159,   563,   564,   569,   570,   160,   565,   572,
     574,   575,   724,   335,   171,   579,   583,   161,   591,   596,
     172,   593,   162,   163,   164,   165,   166,   167,   168,   149,
     150,   584,   601,   607,   608,   169,   609,   170,   616,   621,
     527,   660,   487,   661,   662,   663,   173,   665,   300,   667,
     668,   669,   171,   174,   175,   674,   151,   152,   172,   680,
     679,   696,   698,   153,   154,   155,   702,   149,   150,  -113,
     707,   711,   710,   713,   714,   715,   716,   156,   157,   158,
     717,   718,   719,   720,   173,   159,   721,   738,   746,   723,
     160,   174,   175,   739,   151,   152,   736,  -133,   748,   749,
     161,   153,   154,   155,   754,   162,   163,   164,   165,   166,
     167,   168,   753,   761,   764,   156,   157,   158,   169,   756,
     170,   757,   759,   159,   777,   760,   366,   241,   160,   768,
     769,   627,   743,   771,   772,   171,   773,   726,   161,   779,
     678,   172,   628,   162,   163,   164,   165,   166,   167,   168,
     776,   499,   331,   752,   543,   568,   169,   586,   170,   629,
     735,   105,   490,     0,   363,   438,   201,   173,   630,   631,
     632,   633,   634,   171,   174,   175,     0,   580,     0,   172,
       0,   635,   636,   637,     0,     0,     0,     0,     0,     0,
       0,     0,   638,   106,   107,   108,   109,   110,   111,   112,
     113,   114,     0,     0,     0,   173,     0,     0,     0,     0,
       0,     0,   174,   175,     0,     0,     0,     0,     0,     0,
     639,    28,   640,     0,  -113,     0,   641,     0,     0,     0,
      53,    54,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   272,   642,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,     0,   643,    29,    30,    31,   644,   645,     0,     0,
       0,   646,     0,   647,     0,     0,     0,    32,    33,    34,
      35,     0,    36,    37,    38,    39,     0,     0,     0,     0,
       0,     0,    40,    41,    42,    43,    28,     0,     0,     0,
       0,     0,     0,    44,    45,    46,    47,    48,    49,     0,
       0,     0,     0,    50,    51,    52,     0,     0,     0,     0,
      53,    54,     0,     0,     0,     0,     0,     0,   434,     0,
       0,     0,    55,     0,     0,     0,     0,     0,    29,    30,
      31,     0,     0,     0,    56,     0,     0,     0,     0,     0,
    -335,     0,    32,    33,    34,    35,     0,    36,    37,    38,
      39,    57,     0,     0,     0,     0,     0,    40,    41,    42,
      43,   369,     0,     0,     0,     0,     0,     0,    44,    45,
      46,    47,    48,    49,     0,     0,     0,     0,    50,    51,
      52,     0,     0,     0,     0,    53,    54,   106,   107,   108,
     109,   110,   111,   112,   113,   114,     0,    55,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,    56,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   272,    57,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   272,     0,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   272,     0,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   272,     0,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   272,     0,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   272,     0,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,     0,     0,     0,     0,     0,
       0,     0,     0,   454,   272,   455,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   272,   456,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   272,   459,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   272,   462,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   272,   471,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   272,   551,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   272,   552,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   272,   553,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   272,   554,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   272,   555,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   272,   556,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   272,   581,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   272,   599,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   272,   605,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   272,   606,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   272,   610,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   272,   620,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   272,   623,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,     0,     0,     0,     0,     0,     0,     0,   272,
     291,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   272,
     451,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,     0,
     457,     0,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     458,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      70,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     467,    71,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,     0,
     468,     0,   453,     0,    71,     0,     0,   272,    72,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   472,     0,   527,
       0,    72,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,   747,     0,    74,
      75,    76,    77,    78,   -43,    79,    80,    81,     0,    82,
      83,     0,    84,    85,    86,     0,    73,     0,     0,    87,
      88,    89,    74,    75,    76,    77,    78,     0,    79,    80,
      81,     0,    82,    83,     0,    84,    85,    86,   688,   691,
     692,     0,    87,    88,    89,     0,   700,   272,   474,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   730,   688,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     741,   742,     0,   700,     0,   744,   745,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   750,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     730,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   770,   272,   533,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   272,     0,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290
};

static const yytype_int16 yycheck[] =
{
      74,   217,   110,    23,    18,    72,     4,   115,     4,   483,
      84,    10,   228,   229,    25,   236,     4,    91,     4,     4,
       5,     4,     4,     4,     5,   230,     4,     4,     4,     4,
      21,   486,    15,   624,    36,     4,     5,    15,    15,     4,
      15,    57,    10,     4,     4,     5,     4,     4,   571,    32,
       4,     5,     4,     5,    32,    32,    58,    32,   693,   129,
       0,   128,   129,   654,   131,   132,   674,     4,   676,     4,
     137,    54,    55,    56,   144,   710,   762,   151,   152,    54,
      55,    56,   129,   606,     4,   752,    10,     4,    10,   775,
       4,     5,    16,    58,    57,    15,   763,   144,    15,   707,
     174,   175,   693,   177,    57,   657,   143,   581,    65,     4,
     147,   185,    32,   129,   569,    32,    57,     4,     4,   710,
     105,    58,   143,    57,   105,   101,   147,    37,   143,    15,
     145,   205,     3,     4,    54,    55,   105,    54,    55,    56,
      37,   143,     4,   348,   143,   105,    32,   145,   215,   623,
     148,   105,   148,   105,   145,   143,   139,   140,   143,   145,
     145,   143,   143,   146,   145,   140,   240,   145,   145,   243,
     244,   146,   246,   247,   143,   143,   145,   251,   252,   253,
     254,   255,   143,   143,   258,   145,   197,   198,    57,   263,
     264,   105,   127,   267,   268,   130,   131,   132,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     140,   773,   443,   140,     4,   299,   300,     3,     4,   143,
      37,   145,   127,    49,    50,   130,   131,   132,    37,     4,
     127,   143,   144,   130,   131,   132,    37,    57,    58,    37,
      15,   359,   360,   320,    30,    31,    30,    31,    32,    33,
      34,    37,    38,    39,   143,   127,   145,    32,   130,   131,
     132,     4,    32,    33,    34,    51,    52,    53,   345,   133,
     347,   502,    37,    59,   136,   137,   138,    37,    64,    54,
      55,    37,     4,    69,    70,    71,    72,    73,    74,   143,
      37,   145,    39,    79,    80,    81,    82,    83,    84,    85,
      37,    69,    70,    71,    72,    73,    92,   331,    94,   129,
     143,   143,   145,   145,    36,    58,    37,    37,   549,   545,
      37,    37,    65,   109,    99,    37,   123,   124,   125,   115,
      73,    37,    37,   363,     4,    78,     4,   134,     4,   647,
       4,     4,   650,    65,   428,   142,   430,   431,   432,     4,
       4,    73,    15,     4,    97,   141,    78,     4,     4,   145,
     103,   104,   148,   149,     4,   140,   674,     3,   676,    32,
     454,     4,   115,   457,   458,    97,   460,   145,   111,     4,
       4,   103,   104,   467,   468,    16,    16,    58,     3,     4,
     474,    54,    55,   115,    58,    10,   704,    58,   144,   707,
     421,    65,    28,    29,    30,    31,    32,    33,    34,    73,
     144,     4,     4,     4,    78,    30,    31,     4,     4,     4,
       4,     4,    37,    38,    39,     4,    37,     4,     4,    37,
      57,    37,    37,    97,    37,    37,    51,    52,    53,   103,
     104,    37,   526,    37,    59,   143,   143,    37,    37,    64,
     143,   115,   143,     4,   144,    37,    37,   575,    57,    74,
      58,   144,    37,    37,    79,    80,    81,    82,    83,    84,
      85,    37,    37,    37,    37,    37,    37,    92,    37,    94,
     564,    37,    10,   145,   143,    58,   570,   145,   572,   607,
      10,     4,   145,   145,   109,   145,   517,   518,     4,   583,
     115,   145,   145,   145,   145,     4,   145,     4,     3,     4,
       4,     4,     4,     4,     4,    10,     4,   601,     4,     4,
       4,   144,   144,     4,   608,     4,   141,    37,   143,     4,
      37,   143,   145,   148,   149,    30,    31,     4,   145,    57,
      16,   145,    37,    38,    39,   145,     3,     4,   145,     4,
     145,     4,   778,    16,    37,   781,    51,    52,    53,   785,
      37,   638,   680,   101,    59,   145,    16,   145,    91,    64,
       4,   143,     4,    30,    31,   145,   145,   145,    92,    74,
      37,    38,    39,    40,    79,    80,    81,    82,    83,    84,
      85,   144,    36,   145,    51,    52,    53,    92,   145,    94,
      58,   145,    59,    16,    37,    57,    37,    64,    38,    37,
     145,    10,   696,   143,   109,   144,    37,    74,   144,    58,
     115,    94,    79,    80,    81,    82,    83,    84,    85,     3,
       4,   102,    37,    10,    37,    92,    16,    94,    57,    57,
      37,    16,    16,    37,    37,    37,   141,    37,   143,    37,
      37,    37,   109,   148,   149,    37,    30,    31,   115,    37,
      58,    37,     4,    37,    38,    39,    37,     3,     4,    37,
      37,    25,    57,    37,    37,   145,    37,    51,    52,    53,
     145,    37,    37,   145,   141,    59,   145,     4,    36,   145,
      64,   148,   149,   101,    30,    31,   145,   145,   145,     4,
      74,    37,    38,    39,    25,    79,    80,    81,    82,    83,
      84,    85,    58,     4,     4,    51,    52,    53,    92,   145,
      94,   145,   145,    59,     4,   145,   245,   141,    64,   145,
     145,     4,   716,   145,   145,   109,   145,   697,    74,   145,
     654,   115,    15,    79,    80,    81,    82,    83,    84,    85,
     765,   437,   213,   735,   496,   535,    92,   568,    94,    32,
     708,    26,   431,    -1,   242,   336,    99,   141,    41,    42,
      43,    44,    45,   109,   148,   149,    -1,   560,    -1,   115,
      -1,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,   141,    -1,    -1,    -1,    -1,
      -1,    -1,   148,   149,    -1,    -1,    -1,    -1,    -1,    -1,
      93,     4,    95,    -1,    37,    -1,    99,    -1,    -1,    -1,
     103,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    15,   115,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,   135,    46,    47,    48,   139,   140,    -1,    -1,
      -1,   144,    -1,   146,    -1,    -1,    -1,    60,    61,    62,
      63,    -1,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,     4,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    90,    91,    -1,
      -1,    -1,    -1,    96,    97,    98,    -1,    -1,    -1,    -1,
     103,   104,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,   115,    -1,    -1,    -1,    -1,    -1,    46,    47,
      48,    -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,
     133,    -1,    60,    61,    62,    63,    -1,    65,    66,    67,
      68,   144,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,   145,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    90,    91,    -1,    -1,    -1,    -1,    96,    97,
      98,    -1,    -1,    -1,    -1,   103,   104,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,   115,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,   127,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    15,   144,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    15,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    15,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    15,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    15,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    15,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   143,    15,   145,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    15,   145,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    15,   145,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    15,   145,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    15,   145,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    15,   145,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    15,   145,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    15,   145,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    15,   145,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    15,   145,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    15,   145,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    15,   145,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    15,   145,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    15,   145,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    15,   145,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    15,   145,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    15,   145,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    15,   145,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,
     143,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    15,
     143,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
     143,    -1,    -1,    -1,    -1,    -1,    -1,     4,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     143,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       4,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     143,    38,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
     143,    -1,    36,    -1,    38,    -1,    -1,    15,    65,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,   143,    -1,    37,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   100,    -1,    -1,    -1,   143,    -1,   106,
     107,   108,   109,   110,   111,   112,   113,   114,    -1,   116,
     117,    -1,   119,   120,   121,    -1,   100,    -1,    -1,   126,
     127,   128,   106,   107,   108,   109,   110,    -1,   112,   113,
     114,    -1,   116,   117,    -1,   119,   120,   121,   661,   662,
     663,    -1,   126,   127,   128,    -1,   669,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   701,   702,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     713,   714,    -1,   716,    -1,   718,   719,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   729,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
     743,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,   758,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    15,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   123,   124,   125,   134,   142,   151,   167,   168,   155,
     156,   153,   154,   266,   267,   261,   262,     0,   169,   157,
       4,    57,   129,   270,   271,    57,   263,   264,     4,    46,
      47,    48,    60,    61,    62,    63,    65,    66,    67,    68,
      75,    76,    77,    78,    86,    87,    88,    89,    90,    91,
      96,    97,    98,   103,   104,   115,   127,   144,   170,   177,
     179,   200,   202,   213,   214,   216,   218,   253,   268,   269,
       4,    38,    65,   100,   106,   107,   108,   109,   110,   112,
     113,   114,   116,   117,   119,   120,   121,   126,   127,   128,
     158,    10,     4,   127,   130,   131,   132,   273,   274,    57,
     271,   131,   132,   265,   274,   264,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   198,    57,    57,    49,    50,
      37,    37,     4,   152,    57,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,   171,    37,    37,    37,
     180,    37,   143,   144,   199,   133,     4,   152,     4,     3,
       4,    30,    31,    37,    38,    39,    51,    52,    53,    59,
      64,    74,    79,    80,    81,    82,    83,    84,    85,    92,
      94,   109,   115,   141,   148,   149,   222,     4,     4,   162,
       4,   161,   160,     4,     4,     4,   222,     4,     3,     4,
     163,   164,   165,     4,   111,   222,     4,    16,    16,    58,
     144,   273,    58,   144,   220,   221,   220,   178,   254,     4,
       4,     4,     4,   172,     4,    65,   203,   204,   205,     4,
       4,     4,   152,   152,     4,   152,   145,   152,   215,   217,
       4,   219,     4,     5,   105,   173,    37,   152,     4,     4,
      37,   164,    57,    10,   143,   159,    10,   143,   222,   222,
     222,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
     222,   222,    15,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,   143,    10,   143,   222,   143,   143,     4,   143,    10,
     143,   222,   143,   143,     4,   166,    57,   274,   274,   144,
       4,   127,   130,   131,   132,    58,   144,   222,     4,    58,
      65,    73,    97,   179,   228,     4,    58,   255,   143,   145,
     145,   169,   206,   152,    58,   143,   201,   143,   145,   145,
     145,   145,   145,   145,   145,   201,   145,   201,   143,   219,
     145,    37,     4,     5,   105,   143,   145,   173,   145,    10,
      10,   222,   145,   270,   222,   222,   157,   222,   222,   145,
     222,   222,   222,   222,   222,     4,     4,   222,     4,     4,
       4,     4,   222,   222,     4,     4,   222,   222,     4,   222,
     222,   222,   222,   222,   222,   222,   222,   222,   222,   222,
     222,   222,   222,   222,   222,   222,   222,   222,   222,   222,
     222,     4,     4,     4,   222,   222,     3,     4,     4,     4,
     143,   276,   144,   144,     4,   129,   144,   272,   229,   152,
     234,   239,   256,     4,    36,    37,   210,   207,   205,     4,
     152,   152,   219,   174,    37,     4,     5,   105,   145,   220,
     220,   143,    58,    36,   143,   145,   145,   143,   143,   145,
     143,   145,   145,   145,   145,   145,   145,   143,   143,   145,
     145,   145,   143,   145,    16,     4,   274,   132,    57,   129,
     144,    37,    40,   222,   243,   244,   241,    16,   222,   245,
     244,   222,   258,   143,     4,   148,   211,   212,    16,   203,
     145,   173,   176,    37,   145,   145,     4,   222,   222,   222,
     222,   222,   222,     4,   222,   144,   277,    16,   275,    69,
      70,    71,    72,    73,   145,   242,    37,    37,   243,    16,
     101,   224,   178,    16,    91,   246,   240,     4,   101,   259,
       4,     4,   145,   212,    92,   208,    36,   145,   173,   175,
     145,   145,   145,   145,   145,   145,   145,   145,    58,   274,
     274,   145,   222,    16,    37,    38,   225,    36,   224,    57,
      37,   260,    37,   257,   145,    10,   201,   145,   173,   144,
     277,   145,   222,    37,   102,   226,   226,   178,   222,   259,
     222,   144,   220,    94,   209,   145,    58,    39,   243,   145,
     222,    37,   230,   235,    58,   145,   145,    10,    37,    16,
     145,   222,   136,   137,   138,   227,    57,   259,   220,   222,
     145,    57,   236,   145,   231,   249,   243,     4,    15,    32,
      41,    42,    43,    44,    45,    54,    55,    56,    65,    93,
      95,    99,   115,   135,   139,   140,   144,   146,   181,   182,
     184,   187,   188,   190,   193,   194,   195,   200,     4,    58,
      16,    37,    37,    37,   152,    37,   191,    37,    37,    37,
       4,    54,   182,   186,    37,     4,   146,   182,   190,    58,
      37,   199,   250,   237,    54,    55,    99,   140,   181,    54,
      55,   181,   181,   192,   196,   220,    37,   189,     4,   183,
     181,   185,    37,   147,   201,   186,   186,    37,   232,   220,
      57,    25,   247,    37,    37,   145,    37,   145,    37,    37,
     145,   145,   194,   145,   222,     4,   187,    21,   145,   145,
     181,   182,   145,   147,   186,   247,   145,   194,     4,   101,
     223,   181,   181,   185,   181,   181,    36,   143,   145,     4,
     181,   145,   223,    58,    25,   248,   145,   145,   145,   145,
     145,     4,   248,   251,     4,    10,    16,   197,   145,   145,
     181,   145,   145,   145,   197,   248,   196,     4,   238,   145,
     199,   233,   197,   201,   201,   252,   201
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   150,   151,   151,   151,   151,   151,   152,   154,   153,
     156,   155,   157,   157,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     159,   158,   158,   158,   160,   160,   160,   161,   161,   162,
     162,   163,   163,   163,   165,   164,   166,   166,   166,   168,
     167,   169,   169,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   171,   170,   170,   172,   170,   170,   170,   170,
     170,   170,   170,   173,   173,   173,   173,   173,   173,   174,
     173,   175,   173,   176,   173,   177,   178,   178,   178,   179,
     179,   180,   179,   181,   181,   181,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   183,   183,   184,   185,
     185,   186,   186,   187,   187,   187,   187,   187,   187,   188,
     189,   188,   190,   190,   190,   190,   190,   190,   190,   190,
     191,   190,   192,   190,   193,   193,   194,   194,   195,   195,
     195,   195,   195,   196,   197,   197,   198,   198,   198,   198,
     198,   198,   198,   198,   199,   199,   200,   200,   200,   200,
     201,   201,   202,   203,   203,   204,   204,   206,   205,   207,
     205,   208,   209,   210,   210,   211,   211,   212,   212,   213,
     214,   214,   215,   215,   216,   217,   217,   218,   218,   219,
     219,   219,   221,   220,   222,   222,   222,   222,   222,   222,
     222,   222,   222,   222,   222,   222,   222,   222,   222,   222,
     222,   222,   222,   222,   222,   222,   222,   222,   222,   222,
     222,   222,   222,   222,   222,   222,   222,   222,   222,   222,
     222,   222,   222,   222,   222,   222,   222,   222,   222,   222,
     222,   223,   223,   224,   224,   225,   225,   226,   226,   227,
     227,   227,   227,   229,   230,   231,   232,   233,   228,   234,
     235,   236,   237,   238,   228,   239,   240,   228,   241,   228,
     242,   242,   242,   242,   242,   243,   243,   243,   244,   244,
     244,   244,   245,   245,   246,   246,   247,   247,   248,   248,
     249,   250,   251,   252,   249,   253,   254,   254,   256,   257,
     255,   258,   259,   259,   259,   260,   260,   262,   261,   263,
     263,   264,   265,   267,   266,   269,   268,   270,   270,   271,
     271,   271,   272,   272,   273,   273,   273,   273,   273,   274,
     274,   274,   274,   275,   274,   276,   274,   274,   274,   274,
     274,   274,   274,   277,   277
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     1,     0,     4,
       0,     2,     3,     0,     2,     4,     1,     1,     2,     1,
       4,     4,     3,     2,     4,     3,     4,     4,     4,     4,
       4,     2,     2,     2,     4,     4,     2,     2,     2,     2,
       0,     5,     2,     0,     3,     2,     0,     1,     3,     1,
       3,     0,     1,     3,     0,     2,     1,     2,     3,     0,
       2,     2,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     4,     4,     4,     8,     4,     1,
       1,     4,     0,     5,     4,     0,     5,     4,     4,     3,
       3,     6,     4,     1,     3,     2,     1,     3,     2,     0,
       5,     0,     7,     0,     6,     4,     2,     2,     0,     4,
       2,     0,     7,     1,     1,     1,     1,     5,     4,     4,
       7,     7,     7,     7,     8,     4,     1,     3,     4,     2,
       1,     3,     1,     1,     2,     3,     4,     4,     5,     1,
       0,     5,     2,     1,     1,     1,     4,     1,     4,     4,
       0,     8,     0,     5,     2,     1,     0,     1,     1,     1,
       1,     1,     1,     1,     2,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     6,     6,
       1,     0,     4,     1,     0,     3,     1,     0,     7,     0,
       5,     3,     3,     0,     3,     1,     2,     1,     2,     4,
       4,     3,     3,     1,     4,     3,     0,     1,     1,     0,
       2,     3,     0,     2,     2,     3,     4,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     5,     3,     3,     4,
       1,     1,     4,     4,     4,     4,     4,     4,     4,     6,
       6,     6,     4,     6,     4,     1,     6,     6,     6,     4,
       4,     3,     0,     4,     0,     4,     0,     4,     0,     1,
       1,     1,     0,     0,     0,     0,     0,     0,    19,     0,
       0,     0,     0,     0,    18,     0,     0,     7,     0,     5,
       1,     1,     1,     1,     1,     3,     0,     2,     3,     2,
       6,    10,     2,     1,     0,     1,     2,     0,     0,     3,
       0,     0,     0,     0,    11,     4,     0,     2,     0,     0,
       6,     1,     0,     3,     5,     0,     3,     0,     2,     1,
       2,     4,     2,     0,     2,     0,     5,     1,     2,     4,
       5,     6,     1,     2,     0,     2,     4,     4,     8,     1,
       1,     3,     3,     0,     9,     0,     7,     1,     3,     1,
       3,     1,     3,     0,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 8:
#line 180 "ldgram.y" /* yacc.c:1646  */
    { ldlex_defsym(); }
#line 2333 "ldgram.c" /* yacc.c:1646  */
    break;

  case 9:
#line 182 "ldgram.y" /* yacc.c:1646  */
    {
		  ldlex_popstate();
		  lang_add_assignment (exp_defsym ((yyvsp[-2].name), (yyvsp[0].etree)));
		}
#line 2342 "ldgram.c" /* yacc.c:1646  */
    break;

  case 10:
#line 190 "ldgram.y" /* yacc.c:1646  */
    {
		  ldlex_mri_script ();
		  PUSH_ERROR (_("MRI style script"));
		}
#line 2351 "ldgram.c" /* yacc.c:1646  */
    break;

  case 11:
#line 195 "ldgram.y" /* yacc.c:1646  */
    {
		  ldlex_popstate ();
		  mri_draw_tree ();
		  POP_ERROR ();
		}
#line 2361 "ldgram.c" /* yacc.c:1646  */
    break;

  case 16:
#line 210 "ldgram.y" /* yacc.c:1646  */
    {
			einfo(_("%P%F: unrecognised keyword in MRI style script '%s'\n"),(yyvsp[0].name));
			}
#line 2369 "ldgram.c" /* yacc.c:1646  */
    break;

  case 17:
#line 213 "ldgram.y" /* yacc.c:1646  */
    {
			config.map_filename = "-";
			}
#line 2377 "ldgram.c" /* yacc.c:1646  */
    break;

  case 20:
#line 219 "ldgram.y" /* yacc.c:1646  */
    { mri_public((yyvsp[-2].name), (yyvsp[0].etree)); }
#line 2383 "ldgram.c" /* yacc.c:1646  */
    break;

  case 21:
#line 221 "ldgram.y" /* yacc.c:1646  */
    { mri_public((yyvsp[-2].name), (yyvsp[0].etree)); }
#line 2389 "ldgram.c" /* yacc.c:1646  */
    break;

  case 22:
#line 223 "ldgram.y" /* yacc.c:1646  */
    { mri_public((yyvsp[-1].name), (yyvsp[0].etree)); }
#line 2395 "ldgram.c" /* yacc.c:1646  */
    break;

  case 23:
#line 225 "ldgram.y" /* yacc.c:1646  */
    { mri_format((yyvsp[0].name)); }
#line 2401 "ldgram.c" /* yacc.c:1646  */
    break;

  case 24:
#line 227 "ldgram.y" /* yacc.c:1646  */
    { mri_output_section((yyvsp[-2].name), (yyvsp[0].etree));}
#line 2407 "ldgram.c" /* yacc.c:1646  */
    break;

  case 25:
#line 229 "ldgram.y" /* yacc.c:1646  */
    { mri_output_section((yyvsp[-1].name), (yyvsp[0].etree));}
#line 2413 "ldgram.c" /* yacc.c:1646  */
    break;

  case 26:
#line 231 "ldgram.y" /* yacc.c:1646  */
    { mri_output_section((yyvsp[-2].name), (yyvsp[0].etree));}
#line 2419 "ldgram.c" /* yacc.c:1646  */
    break;

  case 27:
#line 233 "ldgram.y" /* yacc.c:1646  */
    { mri_align((yyvsp[-2].name),(yyvsp[0].etree)); }
#line 2425 "ldgram.c" /* yacc.c:1646  */
    break;

  case 28:
#line 235 "ldgram.y" /* yacc.c:1646  */
    { mri_align((yyvsp[-2].name),(yyvsp[0].etree)); }
#line 2431 "ldgram.c" /* yacc.c:1646  */
    break;

  case 29:
#line 237 "ldgram.y" /* yacc.c:1646  */
    { mri_alignmod((yyvsp[-2].name),(yyvsp[0].etree)); }
#line 2437 "ldgram.c" /* yacc.c:1646  */
    break;

  case 30:
#line 239 "ldgram.y" /* yacc.c:1646  */
    { mri_alignmod((yyvsp[-2].name),(yyvsp[0].etree)); }
#line 2443 "ldgram.c" /* yacc.c:1646  */
    break;

  case 33:
#line 243 "ldgram.y" /* yacc.c:1646  */
    { mri_name((yyvsp[0].name)); }
#line 2449 "ldgram.c" /* yacc.c:1646  */
    break;

  case 34:
#line 245 "ldgram.y" /* yacc.c:1646  */
    { mri_alias((yyvsp[-2].name),(yyvsp[0].name),0);}
#line 2455 "ldgram.c" /* yacc.c:1646  */
    break;

  case 35:
#line 247 "ldgram.y" /* yacc.c:1646  */
    { mri_alias ((yyvsp[-2].name), 0, (int) (yyvsp[0].bigint).integer); }
#line 2461 "ldgram.c" /* yacc.c:1646  */
    break;

  case 36:
#line 249 "ldgram.y" /* yacc.c:1646  */
    { mri_base((yyvsp[0].etree)); }
#line 2467 "ldgram.c" /* yacc.c:1646  */
    break;

  case 37:
#line 251 "ldgram.y" /* yacc.c:1646  */
    { mri_truncate ((unsigned int) (yyvsp[0].bigint).integer); }
#line 2473 "ldgram.c" /* yacc.c:1646  */
    break;

  case 40:
#line 255 "ldgram.y" /* yacc.c:1646  */
    { ldlex_script (); ldfile_open_command_file((yyvsp[0].name)); }
#line 2479 "ldgram.c" /* yacc.c:1646  */
    break;

  case 41:
#line 257 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate (); }
#line 2485 "ldgram.c" /* yacc.c:1646  */
    break;

  case 42:
#line 259 "ldgram.y" /* yacc.c:1646  */
    { lang_add_entry ((yyvsp[0].name), FALSE); }
#line 2491 "ldgram.c" /* yacc.c:1646  */
    break;

  case 44:
#line 264 "ldgram.y" /* yacc.c:1646  */
    { mri_order((yyvsp[0].name)); }
#line 2497 "ldgram.c" /* yacc.c:1646  */
    break;

  case 45:
#line 265 "ldgram.y" /* yacc.c:1646  */
    { mri_order((yyvsp[0].name)); }
#line 2503 "ldgram.c" /* yacc.c:1646  */
    break;

  case 47:
#line 271 "ldgram.y" /* yacc.c:1646  */
    { mri_load((yyvsp[0].name)); }
#line 2509 "ldgram.c" /* yacc.c:1646  */
    break;

  case 48:
#line 272 "ldgram.y" /* yacc.c:1646  */
    { mri_load((yyvsp[0].name)); }
#line 2515 "ldgram.c" /* yacc.c:1646  */
    break;

  case 49:
#line 277 "ldgram.y" /* yacc.c:1646  */
    { mri_only_load((yyvsp[0].name)); }
#line 2521 "ldgram.c" /* yacc.c:1646  */
    break;

  case 50:
#line 279 "ldgram.y" /* yacc.c:1646  */
    { mri_only_load((yyvsp[0].name)); }
#line 2527 "ldgram.c" /* yacc.c:1646  */
    break;

  case 51:
#line 283 "ldgram.y" /* yacc.c:1646  */
    { (yyval.name) = NULL; }
#line 2533 "ldgram.c" /* yacc.c:1646  */
    break;

  case 54:
#line 290 "ldgram.y" /* yacc.c:1646  */
    { ldlex_expression (); }
#line 2539 "ldgram.c" /* yacc.c:1646  */
    break;

  case 55:
#line 292 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate (); }
#line 2545 "ldgram.c" /* yacc.c:1646  */
    break;

  case 56:
#line 296 "ldgram.y" /* yacc.c:1646  */
    { ldlang_add_undef ((yyvsp[0].name), FALSE); }
#line 2551 "ldgram.c" /* yacc.c:1646  */
    break;

  case 57:
#line 298 "ldgram.y" /* yacc.c:1646  */
    { ldlang_add_undef ((yyvsp[0].name), FALSE); }
#line 2557 "ldgram.c" /* yacc.c:1646  */
    break;

  case 58:
#line 300 "ldgram.y" /* yacc.c:1646  */
    { ldlang_add_undef ((yyvsp[0].name), FALSE); }
#line 2563 "ldgram.c" /* yacc.c:1646  */
    break;

  case 59:
#line 304 "ldgram.y" /* yacc.c:1646  */
    { ldlex_both(); }
#line 2569 "ldgram.c" /* yacc.c:1646  */
    break;

  case 60:
#line 306 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate(); }
#line 2575 "ldgram.c" /* yacc.c:1646  */
    break;

  case 73:
#line 327 "ldgram.y" /* yacc.c:1646  */
    { lang_add_target((yyvsp[-1].name)); }
#line 2581 "ldgram.c" /* yacc.c:1646  */
    break;

  case 74:
#line 329 "ldgram.y" /* yacc.c:1646  */
    { ldfile_add_library_path ((yyvsp[-1].name), FALSE); }
#line 2587 "ldgram.c" /* yacc.c:1646  */
    break;

  case 75:
#line 331 "ldgram.y" /* yacc.c:1646  */
    { lang_add_output((yyvsp[-1].name), 1); }
#line 2593 "ldgram.c" /* yacc.c:1646  */
    break;

  case 76:
#line 333 "ldgram.y" /* yacc.c:1646  */
    { lang_add_output_format ((yyvsp[-1].name), (char *) NULL,
					    (char *) NULL, 1); }
#line 2600 "ldgram.c" /* yacc.c:1646  */
    break;

  case 77:
#line 336 "ldgram.y" /* yacc.c:1646  */
    { lang_add_output_format ((yyvsp[-5].name), (yyvsp[-3].name), (yyvsp[-1].name), 1); }
#line 2606 "ldgram.c" /* yacc.c:1646  */
    break;

  case 78:
#line 338 "ldgram.y" /* yacc.c:1646  */
    { ldfile_set_output_arch ((yyvsp[-1].name), bfd_arch_unknown); }
#line 2612 "ldgram.c" /* yacc.c:1646  */
    break;

  case 79:
#line 340 "ldgram.y" /* yacc.c:1646  */
    { command_line.force_common_definition = TRUE ; }
#line 2618 "ldgram.c" /* yacc.c:1646  */
    break;

  case 80:
#line 342 "ldgram.y" /* yacc.c:1646  */
    { command_line.inhibit_common_definition = TRUE ; }
#line 2624 "ldgram.c" /* yacc.c:1646  */
    break;

  case 82:
#line 345 "ldgram.y" /* yacc.c:1646  */
    { lang_enter_group (); }
#line 2630 "ldgram.c" /* yacc.c:1646  */
    break;

  case 83:
#line 347 "ldgram.y" /* yacc.c:1646  */
    { lang_leave_group (); }
#line 2636 "ldgram.c" /* yacc.c:1646  */
    break;

  case 84:
#line 349 "ldgram.y" /* yacc.c:1646  */
    { lang_add_map((yyvsp[-1].name)); }
#line 2642 "ldgram.c" /* yacc.c:1646  */
    break;

  case 85:
#line 351 "ldgram.y" /* yacc.c:1646  */
    { ldlex_script (); ldfile_open_command_file((yyvsp[0].name)); }
#line 2648 "ldgram.c" /* yacc.c:1646  */
    break;

  case 86:
#line 353 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate (); }
#line 2654 "ldgram.c" /* yacc.c:1646  */
    break;

  case 87:
#line 355 "ldgram.y" /* yacc.c:1646  */
    {
		  lang_add_nocrossref ((yyvsp[-1].nocrossref));
		}
#line 2662 "ldgram.c" /* yacc.c:1646  */
    break;

  case 89:
#line 360 "ldgram.y" /* yacc.c:1646  */
    { lang_add_insert ((yyvsp[0].name), 0); }
#line 2668 "ldgram.c" /* yacc.c:1646  */
    break;

  case 90:
#line 362 "ldgram.y" /* yacc.c:1646  */
    { lang_add_insert ((yyvsp[0].name), 1); }
#line 2674 "ldgram.c" /* yacc.c:1646  */
    break;

  case 91:
#line 364 "ldgram.y" /* yacc.c:1646  */
    { lang_memory_region_alias ((yyvsp[-3].name), (yyvsp[-1].name)); }
#line 2680 "ldgram.c" /* yacc.c:1646  */
    break;

  case 92:
#line 366 "ldgram.y" /* yacc.c:1646  */
    { lang_ld_feature ((yyvsp[-1].name)); }
#line 2686 "ldgram.c" /* yacc.c:1646  */
    break;

  case 93:
#line 371 "ldgram.y" /* yacc.c:1646  */
    { lang_add_input_file((yyvsp[0].name),lang_input_file_is_search_file_enum,
				 (char *)NULL); }
#line 2693 "ldgram.c" /* yacc.c:1646  */
    break;

  case 94:
#line 374 "ldgram.y" /* yacc.c:1646  */
    { lang_add_input_file((yyvsp[0].name),lang_input_file_is_search_file_enum,
				 (char *)NULL); }
#line 2700 "ldgram.c" /* yacc.c:1646  */
    break;

  case 95:
#line 377 "ldgram.y" /* yacc.c:1646  */
    { lang_add_input_file((yyvsp[0].name),lang_input_file_is_search_file_enum,
				 (char *)NULL); }
#line 2707 "ldgram.c" /* yacc.c:1646  */
    break;

  case 96:
#line 380 "ldgram.y" /* yacc.c:1646  */
    { lang_add_input_file((yyvsp[0].name),lang_input_file_is_l_enum,
				 (char *)NULL); }
#line 2714 "ldgram.c" /* yacc.c:1646  */
    break;

  case 97:
#line 383 "ldgram.y" /* yacc.c:1646  */
    { lang_add_input_file((yyvsp[0].name),lang_input_file_is_l_enum,
				 (char *)NULL); }
#line 2721 "ldgram.c" /* yacc.c:1646  */
    break;

  case 98:
#line 386 "ldgram.y" /* yacc.c:1646  */
    { lang_add_input_file((yyvsp[0].name),lang_input_file_is_l_enum,
				 (char *)NULL); }
#line 2728 "ldgram.c" /* yacc.c:1646  */
    break;

  case 99:
#line 389 "ldgram.y" /* yacc.c:1646  */
    { (yyval.integer) = add_DT_NEEDED_for_regular; add_DT_NEEDED_for_regular = TRUE; }
#line 2734 "ldgram.c" /* yacc.c:1646  */
    break;

  case 100:
#line 391 "ldgram.y" /* yacc.c:1646  */
    { add_DT_NEEDED_for_regular = (yyvsp[-2].integer); }
#line 2740 "ldgram.c" /* yacc.c:1646  */
    break;

  case 101:
#line 393 "ldgram.y" /* yacc.c:1646  */
    { (yyval.integer) = add_DT_NEEDED_for_regular; add_DT_NEEDED_for_regular = TRUE; }
#line 2746 "ldgram.c" /* yacc.c:1646  */
    break;

  case 102:
#line 395 "ldgram.y" /* yacc.c:1646  */
    { add_DT_NEEDED_for_regular = (yyvsp[-2].integer); }
#line 2752 "ldgram.c" /* yacc.c:1646  */
    break;

  case 103:
#line 397 "ldgram.y" /* yacc.c:1646  */
    { (yyval.integer) = add_DT_NEEDED_for_regular; add_DT_NEEDED_for_regular = TRUE; }
#line 2758 "ldgram.c" /* yacc.c:1646  */
    break;

  case 104:
#line 399 "ldgram.y" /* yacc.c:1646  */
    { add_DT_NEEDED_for_regular = (yyvsp[-2].integer); }
#line 2764 "ldgram.c" /* yacc.c:1646  */
    break;

  case 109:
#line 414 "ldgram.y" /* yacc.c:1646  */
    { lang_add_entry ((yyvsp[-1].name), FALSE); }
#line 2770 "ldgram.c" /* yacc.c:1646  */
    break;

  case 111:
#line 416 "ldgram.y" /* yacc.c:1646  */
    {ldlex_expression ();}
#line 2776 "ldgram.c" /* yacc.c:1646  */
    break;

  case 112:
#line 417 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate ();
		  lang_add_assignment (exp_assert ((yyvsp[-3].etree), (yyvsp[-1].name))); }
#line 2783 "ldgram.c" /* yacc.c:1646  */
    break;

  case 113:
#line 425 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.cname) = (yyvsp[0].name);
			}
#line 2791 "ldgram.c" /* yacc.c:1646  */
    break;

  case 114:
#line 429 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.cname) = "*";
			}
#line 2799 "ldgram.c" /* yacc.c:1646  */
    break;

  case 115:
#line 433 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.cname) = "?";
			}
#line 2807 "ldgram.c" /* yacc.c:1646  */
    break;

  case 116:
#line 440 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.wildcard).name = (yyvsp[0].cname);
			  (yyval.wildcard).sorted = none;
			  (yyval.wildcard).exclude_name_list = NULL;
			  (yyval.wildcard).section_flag_list = NULL;
			}
#line 2818 "ldgram.c" /* yacc.c:1646  */
    break;

  case 117:
#line 447 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.wildcard).name = (yyvsp[0].cname);
			  (yyval.wildcard).sorted = none;
			  (yyval.wildcard).exclude_name_list = (yyvsp[-2].name_list);
			  (yyval.wildcard).section_flag_list = NULL;
			}
#line 2829 "ldgram.c" /* yacc.c:1646  */
    break;

  case 118:
#line 454 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.wildcard).name = (yyvsp[-1].cname);
			  (yyval.wildcard).sorted = by_name;
			  (yyval.wildcard).exclude_name_list = NULL;
			  (yyval.wildcard).section_flag_list = NULL;
			}
#line 2840 "ldgram.c" /* yacc.c:1646  */
    break;

  case 119:
#line 461 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.wildcard).name = (yyvsp[-1].cname);
			  (yyval.wildcard).sorted = by_alignment;
			  (yyval.wildcard).exclude_name_list = NULL;
			  (yyval.wildcard).section_flag_list = NULL;
			}
#line 2851 "ldgram.c" /* yacc.c:1646  */
    break;

  case 120:
#line 468 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.wildcard).name = (yyvsp[-2].cname);
			  (yyval.wildcard).sorted = by_name_alignment;
			  (yyval.wildcard).exclude_name_list = NULL;
			  (yyval.wildcard).section_flag_list = NULL;
			}
#line 2862 "ldgram.c" /* yacc.c:1646  */
    break;

  case 121:
#line 475 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.wildcard).name = (yyvsp[-2].cname);
			  (yyval.wildcard).sorted = by_name;
			  (yyval.wildcard).exclude_name_list = NULL;
			  (yyval.wildcard).section_flag_list = NULL;
			}
#line 2873 "ldgram.c" /* yacc.c:1646  */
    break;

  case 122:
#line 482 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.wildcard).name = (yyvsp[-2].cname);
			  (yyval.wildcard).sorted = by_alignment_name;
			  (yyval.wildcard).exclude_name_list = NULL;
			  (yyval.wildcard).section_flag_list = NULL;
			}
#line 2884 "ldgram.c" /* yacc.c:1646  */
    break;

  case 123:
#line 489 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.wildcard).name = (yyvsp[-2].cname);
			  (yyval.wildcard).sorted = by_alignment;
			  (yyval.wildcard).exclude_name_list = NULL;
			  (yyval.wildcard).section_flag_list = NULL;
			}
#line 2895 "ldgram.c" /* yacc.c:1646  */
    break;

  case 124:
#line 496 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.wildcard).name = (yyvsp[-1].cname);
			  (yyval.wildcard).sorted = by_name;
			  (yyval.wildcard).exclude_name_list = (yyvsp[-3].name_list);
			  (yyval.wildcard).section_flag_list = NULL;
			}
#line 2906 "ldgram.c" /* yacc.c:1646  */
    break;

  case 125:
#line 503 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.wildcard).name = (yyvsp[-1].cname);
			  (yyval.wildcard).sorted = by_init_priority;
			  (yyval.wildcard).exclude_name_list = NULL;
			  (yyval.wildcard).section_flag_list = NULL;
			}
#line 2917 "ldgram.c" /* yacc.c:1646  */
    break;

  case 126:
#line 512 "ldgram.y" /* yacc.c:1646  */
    {
			  struct flag_info_list *n;
			  n = ((struct flag_info_list *) xmalloc (sizeof *n));
			  if ((yyvsp[0].name)[0] == '!')
			    {
			      n->with = without_flags;
			      n->name = &(yyvsp[0].name)[1];
			    }
			  else
			    {
			      n->with = with_flags;
			      n->name = (yyvsp[0].name);
			    }
			  n->valid = FALSE;
			  n->next = NULL;
			  (yyval.flag_info_list) = n;
			}
#line 2939 "ldgram.c" /* yacc.c:1646  */
    break;

  case 127:
#line 530 "ldgram.y" /* yacc.c:1646  */
    {
			  struct flag_info_list *n;
			  n = ((struct flag_info_list *) xmalloc (sizeof *n));
			  if ((yyvsp[0].name)[0] == '!')
			    {
			      n->with = without_flags;
			      n->name = &(yyvsp[0].name)[1];
			    }
			  else
			    {
			      n->with = with_flags;
			      n->name = (yyvsp[0].name);
			    }
			  n->valid = FALSE;
			  n->next = (yyvsp[-2].flag_info_list);
			  (yyval.flag_info_list) = n;
			}
#line 2961 "ldgram.c" /* yacc.c:1646  */
    break;

  case 128:
#line 551 "ldgram.y" /* yacc.c:1646  */
    {
			  struct flag_info *n;
			  n = ((struct flag_info *) xmalloc (sizeof *n));
			  n->flag_list = (yyvsp[-1].flag_info_list);
			  n->flags_initialized = FALSE;
			  n->not_with_flags = 0;
			  n->only_with_flags = 0;
			  (yyval.flag_info) = n;
			}
#line 2975 "ldgram.c" /* yacc.c:1646  */
    break;

  case 129:
#line 564 "ldgram.y" /* yacc.c:1646  */
    {
			  struct name_list *tmp;
			  tmp = (struct name_list *) xmalloc (sizeof *tmp);
			  tmp->name = (yyvsp[0].cname);
			  tmp->next = (yyvsp[-1].name_list);
			  (yyval.name_list) = tmp;
			}
#line 2987 "ldgram.c" /* yacc.c:1646  */
    break;

  case 130:
#line 573 "ldgram.y" /* yacc.c:1646  */
    {
			  struct name_list *tmp;
			  tmp = (struct name_list *) xmalloc (sizeof *tmp);
			  tmp->name = (yyvsp[0].cname);
			  tmp->next = NULL;
			  (yyval.name_list) = tmp;
			}
#line 2999 "ldgram.c" /* yacc.c:1646  */
    break;

  case 131:
#line 584 "ldgram.y" /* yacc.c:1646  */
    {
			  struct wildcard_list *tmp;
			  tmp = (struct wildcard_list *) xmalloc (sizeof *tmp);
			  tmp->next = (yyvsp[-2].wildcard_list);
			  tmp->spec = (yyvsp[0].wildcard);
			  (yyval.wildcard_list) = tmp;
			}
#line 3011 "ldgram.c" /* yacc.c:1646  */
    break;

  case 132:
#line 593 "ldgram.y" /* yacc.c:1646  */
    {
			  struct wildcard_list *tmp;
			  tmp = (struct wildcard_list *) xmalloc (sizeof *tmp);
			  tmp->next = NULL;
			  tmp->spec = (yyvsp[0].wildcard);
			  (yyval.wildcard_list) = tmp;
			}
#line 3023 "ldgram.c" /* yacc.c:1646  */
    break;

  case 133:
#line 604 "ldgram.y" /* yacc.c:1646  */
    {
			  struct wildcard_spec tmp;
			  tmp.name = (yyvsp[0].name);
			  tmp.exclude_name_list = NULL;
			  tmp.sorted = none;
			  tmp.section_flag_list = NULL;
			  lang_add_wild (&tmp, NULL, ldgram_had_keep);
			}
#line 3036 "ldgram.c" /* yacc.c:1646  */
    break;

  case 134:
#line 613 "ldgram.y" /* yacc.c:1646  */
    {
			  struct wildcard_spec tmp;
			  tmp.name = (yyvsp[0].name);
			  tmp.exclude_name_list = NULL;
			  tmp.sorted = none;
			  tmp.section_flag_list = (yyvsp[-1].flag_info);
			  lang_add_wild (&tmp, NULL, ldgram_had_keep);
			}
#line 3049 "ldgram.c" /* yacc.c:1646  */
    break;

  case 135:
#line 622 "ldgram.y" /* yacc.c:1646  */
    {
			  lang_add_wild (NULL, (yyvsp[-1].wildcard_list), ldgram_had_keep);
			}
#line 3057 "ldgram.c" /* yacc.c:1646  */
    break;

  case 136:
#line 626 "ldgram.y" /* yacc.c:1646  */
    {
			  struct wildcard_spec tmp;
			  tmp.name = NULL;
			  tmp.exclude_name_list = NULL;
			  tmp.sorted = none;
			  tmp.section_flag_list = (yyvsp[-3].flag_info);
			  lang_add_wild (NULL, (yyvsp[-1].wildcard_list), ldgram_had_keep);
			}
#line 3070 "ldgram.c" /* yacc.c:1646  */
    break;

  case 137:
#line 635 "ldgram.y" /* yacc.c:1646  */
    {
			  lang_add_wild (&(yyvsp[-3].wildcard), (yyvsp[-1].wildcard_list), ldgram_had_keep);
			}
#line 3078 "ldgram.c" /* yacc.c:1646  */
    break;

  case 138:
#line 639 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyvsp[-3].wildcard).section_flag_list = (yyvsp[-4].flag_info);
			  lang_add_wild (&(yyvsp[-3].wildcard), (yyvsp[-1].wildcard_list), ldgram_had_keep);
			}
#line 3087 "ldgram.c" /* yacc.c:1646  */
    break;

  case 140:
#line 648 "ldgram.y" /* yacc.c:1646  */
    { ldgram_had_keep = TRUE; }
#line 3093 "ldgram.c" /* yacc.c:1646  */
    break;

  case 141:
#line 650 "ldgram.y" /* yacc.c:1646  */
    { ldgram_had_keep = FALSE; }
#line 3099 "ldgram.c" /* yacc.c:1646  */
    break;

  case 143:
#line 656 "ldgram.y" /* yacc.c:1646  */
    {
 		lang_add_attribute(lang_object_symbols_statement_enum);
	      	}
#line 3107 "ldgram.c" /* yacc.c:1646  */
    break;

  case 145:
#line 661 "ldgram.y" /* yacc.c:1646  */
    {

		  lang_add_attribute(lang_constructors_statement_enum);
		}
#line 3116 "ldgram.c" /* yacc.c:1646  */
    break;

  case 146:
#line 666 "ldgram.y" /* yacc.c:1646  */
    {
		  constructors_sorted = TRUE;
		  lang_add_attribute (lang_constructors_statement_enum);
		}
#line 3125 "ldgram.c" /* yacc.c:1646  */
    break;

  case 148:
#line 672 "ldgram.y" /* yacc.c:1646  */
    {
			  lang_add_data ((int) (yyvsp[-3].integer), (yyvsp[-1].etree));
			}
#line 3133 "ldgram.c" /* yacc.c:1646  */
    break;

  case 149:
#line 677 "ldgram.y" /* yacc.c:1646  */
    {
			  lang_add_fill ((yyvsp[-1].fill));
			}
#line 3141 "ldgram.c" /* yacc.c:1646  */
    break;

  case 150:
#line 680 "ldgram.y" /* yacc.c:1646  */
    {ldlex_expression ();}
#line 3147 "ldgram.c" /* yacc.c:1646  */
    break;

  case 151:
#line 681 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate ();
			  lang_add_assignment (exp_assert ((yyvsp[-4].etree), (yyvsp[-2].name))); }
#line 3154 "ldgram.c" /* yacc.c:1646  */
    break;

  case 152:
#line 684 "ldgram.y" /* yacc.c:1646  */
    { ldlex_script (); ldfile_open_command_file((yyvsp[0].name)); }
#line 3160 "ldgram.c" /* yacc.c:1646  */
    break;

  case 153:
#line 686 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate (); }
#line 3166 "ldgram.c" /* yacc.c:1646  */
    break;

  case 158:
#line 701 "ldgram.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[0].token); }
#line 3172 "ldgram.c" /* yacc.c:1646  */
    break;

  case 159:
#line 703 "ldgram.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[0].token); }
#line 3178 "ldgram.c" /* yacc.c:1646  */
    break;

  case 160:
#line 705 "ldgram.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[0].token); }
#line 3184 "ldgram.c" /* yacc.c:1646  */
    break;

  case 161:
#line 707 "ldgram.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[0].token); }
#line 3190 "ldgram.c" /* yacc.c:1646  */
    break;

  case 162:
#line 709 "ldgram.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[0].token); }
#line 3196 "ldgram.c" /* yacc.c:1646  */
    break;

  case 163:
#line 714 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.fill) = exp_get_fill ((yyvsp[0].etree), 0, "fill value");
		}
#line 3204 "ldgram.c" /* yacc.c:1646  */
    break;

  case 164:
#line 721 "ldgram.y" /* yacc.c:1646  */
    { (yyval.fill) = (yyvsp[0].fill); }
#line 3210 "ldgram.c" /* yacc.c:1646  */
    break;

  case 165:
#line 722 "ldgram.y" /* yacc.c:1646  */
    { (yyval.fill) = (fill_type *) 0; }
#line 3216 "ldgram.c" /* yacc.c:1646  */
    break;

  case 166:
#line 727 "ldgram.y" /* yacc.c:1646  */
    { (yyval.token) = '+'; }
#line 3222 "ldgram.c" /* yacc.c:1646  */
    break;

  case 167:
#line 729 "ldgram.y" /* yacc.c:1646  */
    { (yyval.token) = '-'; }
#line 3228 "ldgram.c" /* yacc.c:1646  */
    break;

  case 168:
#line 731 "ldgram.y" /* yacc.c:1646  */
    { (yyval.token) = '*'; }
#line 3234 "ldgram.c" /* yacc.c:1646  */
    break;

  case 169:
#line 733 "ldgram.y" /* yacc.c:1646  */
    { (yyval.token) = '/'; }
#line 3240 "ldgram.c" /* yacc.c:1646  */
    break;

  case 170:
#line 735 "ldgram.y" /* yacc.c:1646  */
    { (yyval.token) = LSHIFT; }
#line 3246 "ldgram.c" /* yacc.c:1646  */
    break;

  case 171:
#line 737 "ldgram.y" /* yacc.c:1646  */
    { (yyval.token) = RSHIFT; }
#line 3252 "ldgram.c" /* yacc.c:1646  */
    break;

  case 172:
#line 739 "ldgram.y" /* yacc.c:1646  */
    { (yyval.token) = '&'; }
#line 3258 "ldgram.c" /* yacc.c:1646  */
    break;

  case 173:
#line 741 "ldgram.y" /* yacc.c:1646  */
    { (yyval.token) = '|'; }
#line 3264 "ldgram.c" /* yacc.c:1646  */
    break;

  case 176:
#line 751 "ldgram.y" /* yacc.c:1646  */
    {
		  lang_add_assignment (exp_assign ((yyvsp[-2].name), (yyvsp[0].etree)));
		}
#line 3272 "ldgram.c" /* yacc.c:1646  */
    break;

  case 177:
#line 755 "ldgram.y" /* yacc.c:1646  */
    {
		  lang_add_assignment (exp_assign ((yyvsp[-2].name),
						   exp_binop ((yyvsp[-1].token),
							      exp_nameop (NAME,
									  (yyvsp[-2].name)),
							      (yyvsp[0].etree))));
		}
#line 3284 "ldgram.c" /* yacc.c:1646  */
    break;

  case 178:
#line 763 "ldgram.y" /* yacc.c:1646  */
    {
		  lang_add_assignment (exp_provide ((yyvsp[-3].name), (yyvsp[-1].etree), FALSE));
		}
#line 3292 "ldgram.c" /* yacc.c:1646  */
    break;

  case 179:
#line 767 "ldgram.y" /* yacc.c:1646  */
    {
		  lang_add_assignment (exp_provide ((yyvsp[-3].name), (yyvsp[-1].etree), TRUE));
		}
#line 3300 "ldgram.c" /* yacc.c:1646  */
    break;

  case 187:
#line 790 "ldgram.y" /* yacc.c:1646  */
    { region = lang_memory_region_lookup ((yyvsp[0].name), TRUE); }
#line 3306 "ldgram.c" /* yacc.c:1646  */
    break;

  case 188:
#line 793 "ldgram.y" /* yacc.c:1646  */
    {}
#line 3312 "ldgram.c" /* yacc.c:1646  */
    break;

  case 189:
#line 795 "ldgram.y" /* yacc.c:1646  */
    { ldlex_script (); ldfile_open_command_file((yyvsp[0].name)); }
#line 3318 "ldgram.c" /* yacc.c:1646  */
    break;

  case 190:
#line 797 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate (); }
#line 3324 "ldgram.c" /* yacc.c:1646  */
    break;

  case 191:
#line 802 "ldgram.y" /* yacc.c:1646  */
    {
		  region->origin = exp_get_vma ((yyvsp[0].etree), 0, "origin");
		  region->current = region->origin;
		}
#line 3333 "ldgram.c" /* yacc.c:1646  */
    break;

  case 192:
#line 810 "ldgram.y" /* yacc.c:1646  */
    {
		  region->length = exp_get_vma ((yyvsp[0].etree), -1, "length");
		}
#line 3341 "ldgram.c" /* yacc.c:1646  */
    break;

  case 193:
#line 817 "ldgram.y" /* yacc.c:1646  */
    { /* dummy action to avoid bison 1.25 error message */ }
#line 3347 "ldgram.c" /* yacc.c:1646  */
    break;

  case 197:
#line 828 "ldgram.y" /* yacc.c:1646  */
    { lang_set_flags (region, (yyvsp[0].name), 0); }
#line 3353 "ldgram.c" /* yacc.c:1646  */
    break;

  case 198:
#line 830 "ldgram.y" /* yacc.c:1646  */
    { lang_set_flags (region, (yyvsp[0].name), 1); }
#line 3359 "ldgram.c" /* yacc.c:1646  */
    break;

  case 199:
#line 835 "ldgram.y" /* yacc.c:1646  */
    { lang_startup((yyvsp[-1].name)); }
#line 3365 "ldgram.c" /* yacc.c:1646  */
    break;

  case 201:
#line 841 "ldgram.y" /* yacc.c:1646  */
    { ldemul_hll((char *)NULL); }
#line 3371 "ldgram.c" /* yacc.c:1646  */
    break;

  case 202:
#line 846 "ldgram.y" /* yacc.c:1646  */
    { ldemul_hll((yyvsp[0].name)); }
#line 3377 "ldgram.c" /* yacc.c:1646  */
    break;

  case 203:
#line 848 "ldgram.y" /* yacc.c:1646  */
    { ldemul_hll((yyvsp[0].name)); }
#line 3383 "ldgram.c" /* yacc.c:1646  */
    break;

  case 205:
#line 856 "ldgram.y" /* yacc.c:1646  */
    { ldemul_syslib((yyvsp[0].name)); }
#line 3389 "ldgram.c" /* yacc.c:1646  */
    break;

  case 207:
#line 862 "ldgram.y" /* yacc.c:1646  */
    { lang_float(TRUE); }
#line 3395 "ldgram.c" /* yacc.c:1646  */
    break;

  case 208:
#line 864 "ldgram.y" /* yacc.c:1646  */
    { lang_float(FALSE); }
#line 3401 "ldgram.c" /* yacc.c:1646  */
    break;

  case 209:
#line 869 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.nocrossref) = NULL;
		}
#line 3409 "ldgram.c" /* yacc.c:1646  */
    break;

  case 210:
#line 873 "ldgram.y" /* yacc.c:1646  */
    {
		  struct lang_nocrossref *n;

		  n = (struct lang_nocrossref *) xmalloc (sizeof *n);
		  n->name = (yyvsp[-1].name);
		  n->next = (yyvsp[0].nocrossref);
		  (yyval.nocrossref) = n;
		}
#line 3422 "ldgram.c" /* yacc.c:1646  */
    break;

  case 211:
#line 882 "ldgram.y" /* yacc.c:1646  */
    {
		  struct lang_nocrossref *n;

		  n = (struct lang_nocrossref *) xmalloc (sizeof *n);
		  n->name = (yyvsp[-2].name);
		  n->next = (yyvsp[0].nocrossref);
		  (yyval.nocrossref) = n;
		}
#line 3435 "ldgram.c" /* yacc.c:1646  */
    break;

  case 212:
#line 892 "ldgram.y" /* yacc.c:1646  */
    { ldlex_expression (); }
#line 3441 "ldgram.c" /* yacc.c:1646  */
    break;

  case 213:
#line 894 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate (); (yyval.etree)=(yyvsp[0].etree);}
#line 3447 "ldgram.c" /* yacc.c:1646  */
    break;

  case 214:
#line 899 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_unop ('-', (yyvsp[0].etree)); }
#line 3453 "ldgram.c" /* yacc.c:1646  */
    break;

  case 215:
#line 901 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = (yyvsp[-1].etree); }
#line 3459 "ldgram.c" /* yacc.c:1646  */
    break;

  case 216:
#line 903 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_unop ((int) (yyvsp[-3].integer),(yyvsp[-1].etree)); }
#line 3465 "ldgram.c" /* yacc.c:1646  */
    break;

  case 217:
#line 905 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_unop ('!', (yyvsp[0].etree)); }
#line 3471 "ldgram.c" /* yacc.c:1646  */
    break;

  case 218:
#line 907 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = (yyvsp[0].etree); }
#line 3477 "ldgram.c" /* yacc.c:1646  */
    break;

  case 219:
#line 909 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_unop ('~', (yyvsp[0].etree));}
#line 3483 "ldgram.c" /* yacc.c:1646  */
    break;

  case 220:
#line 912 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop ('*', (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3489 "ldgram.c" /* yacc.c:1646  */
    break;

  case 221:
#line 914 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop ('/', (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3495 "ldgram.c" /* yacc.c:1646  */
    break;

  case 222:
#line 916 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop ('%', (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3501 "ldgram.c" /* yacc.c:1646  */
    break;

  case 223:
#line 918 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop ('+', (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3507 "ldgram.c" /* yacc.c:1646  */
    break;

  case 224:
#line 920 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop ('-' , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3513 "ldgram.c" /* yacc.c:1646  */
    break;

  case 225:
#line 922 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop (LSHIFT , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3519 "ldgram.c" /* yacc.c:1646  */
    break;

  case 226:
#line 924 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop (RSHIFT , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3525 "ldgram.c" /* yacc.c:1646  */
    break;

  case 227:
#line 926 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop (EQ , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3531 "ldgram.c" /* yacc.c:1646  */
    break;

  case 228:
#line 928 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop (NE , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3537 "ldgram.c" /* yacc.c:1646  */
    break;

  case 229:
#line 930 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop (LE , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3543 "ldgram.c" /* yacc.c:1646  */
    break;

  case 230:
#line 932 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop (GE , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3549 "ldgram.c" /* yacc.c:1646  */
    break;

  case 231:
#line 934 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop ('<' , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3555 "ldgram.c" /* yacc.c:1646  */
    break;

  case 232:
#line 936 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop ('>' , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3561 "ldgram.c" /* yacc.c:1646  */
    break;

  case 233:
#line 938 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop ('&' , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3567 "ldgram.c" /* yacc.c:1646  */
    break;

  case 234:
#line 940 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop ('^' , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3573 "ldgram.c" /* yacc.c:1646  */
    break;

  case 235:
#line 942 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop ('|' , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3579 "ldgram.c" /* yacc.c:1646  */
    break;

  case 236:
#line 944 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_trinop ('?' , (yyvsp[-4].etree), (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3585 "ldgram.c" /* yacc.c:1646  */
    break;

  case 237:
#line 946 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop (ANDAND , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3591 "ldgram.c" /* yacc.c:1646  */
    break;

  case 238:
#line 948 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop (OROR , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3597 "ldgram.c" /* yacc.c:1646  */
    break;

  case 239:
#line 950 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_nameop (DEFINED, (yyvsp[-1].name)); }
#line 3603 "ldgram.c" /* yacc.c:1646  */
    break;

  case 240:
#line 952 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_bigintop ((yyvsp[0].bigint).integer, (yyvsp[0].bigint).str); }
#line 3609 "ldgram.c" /* yacc.c:1646  */
    break;

  case 241:
#line 954 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_nameop (SIZEOF_HEADERS,0); }
#line 3615 "ldgram.c" /* yacc.c:1646  */
    break;

  case 242:
#line 957 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_nameop (ALIGNOF,(yyvsp[-1].name)); }
#line 3621 "ldgram.c" /* yacc.c:1646  */
    break;

  case 243:
#line 959 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_nameop (SIZEOF,(yyvsp[-1].name)); }
#line 3627 "ldgram.c" /* yacc.c:1646  */
    break;

  case 244:
#line 961 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_nameop (ADDR,(yyvsp[-1].name)); }
#line 3633 "ldgram.c" /* yacc.c:1646  */
    break;

  case 245:
#line 963 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_nameop (LOADADDR,(yyvsp[-1].name)); }
#line 3639 "ldgram.c" /* yacc.c:1646  */
    break;

  case 246:
#line 965 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_nameop (CONSTANT,(yyvsp[-1].name)); }
#line 3645 "ldgram.c" /* yacc.c:1646  */
    break;

  case 247:
#line 967 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_unop (ABSOLUTE, (yyvsp[-1].etree)); }
#line 3651 "ldgram.c" /* yacc.c:1646  */
    break;

  case 248:
#line 969 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_unop (ALIGN_K,(yyvsp[-1].etree)); }
#line 3657 "ldgram.c" /* yacc.c:1646  */
    break;

  case 249:
#line 971 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop (ALIGN_K,(yyvsp[-3].etree),(yyvsp[-1].etree)); }
#line 3663 "ldgram.c" /* yacc.c:1646  */
    break;

  case 250:
#line 973 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop (DATA_SEGMENT_ALIGN, (yyvsp[-3].etree), (yyvsp[-1].etree)); }
#line 3669 "ldgram.c" /* yacc.c:1646  */
    break;

  case 251:
#line 975 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop (DATA_SEGMENT_RELRO_END, (yyvsp[-1].etree), (yyvsp[-3].etree)); }
#line 3675 "ldgram.c" /* yacc.c:1646  */
    break;

  case 252:
#line 977 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_unop (DATA_SEGMENT_END, (yyvsp[-1].etree)); }
#line 3681 "ldgram.c" /* yacc.c:1646  */
    break;

  case 253:
#line 979 "ldgram.y" /* yacc.c:1646  */
    { /* The operands to the expression node are
			     placed in the opposite order from the way
			     in which they appear in the script as
			     that allows us to reuse more code in
			     fold_binary.  */
			  (yyval.etree) = exp_binop (SEGMENT_START,
					  (yyvsp[-1].etree),
					  exp_nameop (NAME, (yyvsp[-3].name))); }
#line 3694 "ldgram.c" /* yacc.c:1646  */
    break;

  case 254:
#line 988 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_unop (ALIGN_K,(yyvsp[-1].etree)); }
#line 3700 "ldgram.c" /* yacc.c:1646  */
    break;

  case 255:
#line 990 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_nameop (NAME,(yyvsp[0].name)); }
#line 3706 "ldgram.c" /* yacc.c:1646  */
    break;

  case 256:
#line 992 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop (MAX_K, (yyvsp[-3].etree), (yyvsp[-1].etree) ); }
#line 3712 "ldgram.c" /* yacc.c:1646  */
    break;

  case 257:
#line 994 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_binop (MIN_K, (yyvsp[-3].etree), (yyvsp[-1].etree) ); }
#line 3718 "ldgram.c" /* yacc.c:1646  */
    break;

  case 258:
#line 996 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_assert ((yyvsp[-3].etree), (yyvsp[-1].name)); }
#line 3724 "ldgram.c" /* yacc.c:1646  */
    break;

  case 259:
#line 998 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_nameop (ORIGIN, (yyvsp[-1].name)); }
#line 3730 "ldgram.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1000 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = exp_nameop (LENGTH, (yyvsp[-1].name)); }
#line 3736 "ldgram.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1005 "ldgram.y" /* yacc.c:1646  */
    { (yyval.name) = (yyvsp[0].name); }
#line 3742 "ldgram.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1006 "ldgram.y" /* yacc.c:1646  */
    { (yyval.name) = 0; }
#line 3748 "ldgram.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1010 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = (yyvsp[-1].etree); }
#line 3754 "ldgram.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1011 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = 0; }
#line 3760 "ldgram.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1015 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = (yyvsp[-1].etree); }
#line 3766 "ldgram.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1016 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = 0; }
#line 3772 "ldgram.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1020 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = (yyvsp[-1].etree); }
#line 3778 "ldgram.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1021 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = 0; }
#line 3784 "ldgram.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1025 "ldgram.y" /* yacc.c:1646  */
    { (yyval.token) = ONLY_IF_RO; }
#line 3790 "ldgram.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1026 "ldgram.y" /* yacc.c:1646  */
    { (yyval.token) = ONLY_IF_RW; }
#line 3796 "ldgram.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1027 "ldgram.y" /* yacc.c:1646  */
    { (yyval.token) = SPECIAL; }
#line 3802 "ldgram.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1028 "ldgram.y" /* yacc.c:1646  */
    { (yyval.token) = 0; }
#line 3808 "ldgram.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1031 "ldgram.y" /* yacc.c:1646  */
    { ldlex_expression(); }
#line 3814 "ldgram.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1035 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate (); ldlex_script (); }
#line 3820 "ldgram.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1038 "ldgram.y" /* yacc.c:1646  */
    {
			  lang_enter_output_section_statement((yyvsp[-8].name), (yyvsp[-6].etree),
							      sectype,
							      (yyvsp[-4].etree), (yyvsp[-3].etree), (yyvsp[-5].etree), (yyvsp[-1].token));
			}
#line 3830 "ldgram.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1044 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate (); ldlex_expression (); }
#line 3836 "ldgram.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1046 "ldgram.y" /* yacc.c:1646  */
    {
		  ldlex_popstate ();
		  lang_leave_output_section_statement ((yyvsp[0].fill), (yyvsp[-3].name), (yyvsp[-1].section_phdr), (yyvsp[-2].name));
		}
#line 3845 "ldgram.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1051 "ldgram.y" /* yacc.c:1646  */
    {}
#line 3851 "ldgram.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1053 "ldgram.y" /* yacc.c:1646  */
    { ldlex_expression (); }
#line 3857 "ldgram.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1055 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate (); ldlex_script (); }
#line 3863 "ldgram.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1057 "ldgram.y" /* yacc.c:1646  */
    {
			  lang_enter_overlay ((yyvsp[-5].etree), (yyvsp[-2].etree));
			}
#line 3871 "ldgram.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1062 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate (); ldlex_expression (); }
#line 3877 "ldgram.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1064 "ldgram.y" /* yacc.c:1646  */
    {
			  ldlex_popstate ();
			  lang_leave_overlay ((yyvsp[-11].etree), (int) (yyvsp[-12].integer),
					      (yyvsp[0].fill), (yyvsp[-3].name), (yyvsp[-1].section_phdr), (yyvsp[-2].name));
			}
#line 3887 "ldgram.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1074 "ldgram.y" /* yacc.c:1646  */
    { ldlex_expression (); }
#line 3893 "ldgram.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1076 "ldgram.y" /* yacc.c:1646  */
    {
		  ldlex_popstate ();
		  lang_add_assignment (exp_assign (".", (yyvsp[0].etree)));
		}
#line 3902 "ldgram.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1082 "ldgram.y" /* yacc.c:1646  */
    { ldlex_script (); ldfile_open_command_file((yyvsp[0].name)); }
#line 3908 "ldgram.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1084 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate (); }
#line 3914 "ldgram.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1088 "ldgram.y" /* yacc.c:1646  */
    { sectype = noload_section; }
#line 3920 "ldgram.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1089 "ldgram.y" /* yacc.c:1646  */
    { sectype = noalloc_section; }
#line 3926 "ldgram.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1090 "ldgram.y" /* yacc.c:1646  */
    { sectype = noalloc_section; }
#line 3932 "ldgram.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1091 "ldgram.y" /* yacc.c:1646  */
    { sectype = noalloc_section; }
#line 3938 "ldgram.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1092 "ldgram.y" /* yacc.c:1646  */
    { sectype = noalloc_section; }
#line 3944 "ldgram.c" /* yacc.c:1646  */
    break;

  case 296:
#line 1097 "ldgram.y" /* yacc.c:1646  */
    { sectype = normal_section; }
#line 3950 "ldgram.c" /* yacc.c:1646  */
    break;

  case 297:
#line 1098 "ldgram.y" /* yacc.c:1646  */
    { sectype = normal_section; }
#line 3956 "ldgram.c" /* yacc.c:1646  */
    break;

  case 298:
#line 1102 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = (yyvsp[-2].etree); }
#line 3962 "ldgram.c" /* yacc.c:1646  */
    break;

  case 299:
#line 1103 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = (etree_type *)NULL;  }
#line 3968 "ldgram.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1108 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = (yyvsp[-3].etree); }
#line 3974 "ldgram.c" /* yacc.c:1646  */
    break;

  case 301:
#line 1110 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = (yyvsp[-7].etree); }
#line 3980 "ldgram.c" /* yacc.c:1646  */
    break;

  case 302:
#line 1114 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = (yyvsp[-1].etree); }
#line 3986 "ldgram.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1115 "ldgram.y" /* yacc.c:1646  */
    { (yyval.etree) = (etree_type *) NULL;  }
#line 3992 "ldgram.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1120 "ldgram.y" /* yacc.c:1646  */
    { (yyval.integer) = 0; }
#line 3998 "ldgram.c" /* yacc.c:1646  */
    break;

  case 305:
#line 1122 "ldgram.y" /* yacc.c:1646  */
    { (yyval.integer) = 1; }
#line 4004 "ldgram.c" /* yacc.c:1646  */
    break;

  case 306:
#line 1127 "ldgram.y" /* yacc.c:1646  */
    { (yyval.name) = (yyvsp[0].name); }
#line 4010 "ldgram.c" /* yacc.c:1646  */
    break;

  case 307:
#line 1128 "ldgram.y" /* yacc.c:1646  */
    { (yyval.name) = DEFAULT_MEMORY_REGION; }
#line 4016 "ldgram.c" /* yacc.c:1646  */
    break;

  case 308:
#line 1133 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.section_phdr) = NULL;
		}
#line 4024 "ldgram.c" /* yacc.c:1646  */
    break;

  case 309:
#line 1137 "ldgram.y" /* yacc.c:1646  */
    {
		  struct lang_output_section_phdr_list *n;

		  n = ((struct lang_output_section_phdr_list *)
		       xmalloc (sizeof *n));
		  n->name = (yyvsp[0].name);
		  n->used = FALSE;
		  n->next = (yyvsp[-2].section_phdr);
		  (yyval.section_phdr) = n;
		}
#line 4039 "ldgram.c" /* yacc.c:1646  */
    break;

  case 311:
#line 1153 "ldgram.y" /* yacc.c:1646  */
    {
			  ldlex_script ();
			  lang_enter_overlay_section ((yyvsp[0].name));
			}
#line 4048 "ldgram.c" /* yacc.c:1646  */
    break;

  case 312:
#line 1158 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate (); ldlex_expression (); }
#line 4054 "ldgram.c" /* yacc.c:1646  */
    break;

  case 313:
#line 1160 "ldgram.y" /* yacc.c:1646  */
    {
			  ldlex_popstate ();
			  lang_leave_overlay_section ((yyvsp[0].fill), (yyvsp[-1].section_phdr));
			}
#line 4063 "ldgram.c" /* yacc.c:1646  */
    break;

  case 318:
#line 1177 "ldgram.y" /* yacc.c:1646  */
    { ldlex_expression (); }
#line 4069 "ldgram.c" /* yacc.c:1646  */
    break;

  case 319:
#line 1178 "ldgram.y" /* yacc.c:1646  */
    { ldlex_popstate (); }
#line 4075 "ldgram.c" /* yacc.c:1646  */
    break;

  case 320:
#line 1180 "ldgram.y" /* yacc.c:1646  */
    {
		  lang_new_phdr ((yyvsp[-5].name), (yyvsp[-3].etree), (yyvsp[-2].phdr).filehdr, (yyvsp[-2].phdr).phdrs, (yyvsp[-2].phdr).at,
				 (yyvsp[-2].phdr).flags);
		}
#line 4084 "ldgram.c" /* yacc.c:1646  */
    break;

  case 321:
#line 1188 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.etree) = (yyvsp[0].etree);

		  if ((yyvsp[0].etree)->type.node_class == etree_name
		      && (yyvsp[0].etree)->type.node_code == NAME)
		    {
		      const char *s;
		      unsigned int i;
		      static const char * const phdr_types[] =
			{
			  "PT_NULL", "PT_LOAD", "PT_DYNAMIC",
			  "PT_INTERP", "PT_NOTE", "PT_SHLIB",
			  "PT_PHDR", "PT_TLS"
			};

		      s = (yyvsp[0].etree)->name.name;
		      for (i = 0;
			   i < sizeof phdr_types / sizeof phdr_types[0];
			   i++)
			if (strcmp (s, phdr_types[i]) == 0)
			  {
			    (yyval.etree) = exp_intop (i);
			    break;
			  }
		      if (i == sizeof phdr_types / sizeof phdr_types[0])
			{
			  if (strcmp (s, "PT_GNU_EH_FRAME") == 0)
			    (yyval.etree) = exp_intop (0x6474e550);
			  else if (strcmp (s, "PT_GNU_STACK") == 0)
			    (yyval.etree) = exp_intop (0x6474e551);
			  else
			    {
			      einfo (_("\
%X%P:%S: unknown phdr type `%s' (try integer literal)\n"),
				     s);
			      (yyval.etree) = exp_intop (0);
			    }
			}
		    }
		}
#line 4129 "ldgram.c" /* yacc.c:1646  */
    break;

  case 322:
#line 1232 "ldgram.y" /* yacc.c:1646  */
    {
		  memset (&(yyval.phdr), 0, sizeof (struct phdr_info));
		}
#line 4137 "ldgram.c" /* yacc.c:1646  */
    break;

  case 323:
#line 1236 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.phdr) = (yyvsp[0].phdr);
		  if (strcmp ((yyvsp[-2].name), "FILEHDR") == 0 && (yyvsp[-1].etree) == NULL)
		    (yyval.phdr).filehdr = TRUE;
		  else if (strcmp ((yyvsp[-2].name), "PHDRS") == 0 && (yyvsp[-1].etree) == NULL)
		    (yyval.phdr).phdrs = TRUE;
		  else if (strcmp ((yyvsp[-2].name), "FLAGS") == 0 && (yyvsp[-1].etree) != NULL)
		    (yyval.phdr).flags = (yyvsp[-1].etree);
		  else
		    einfo (_("%X%P:%S: PHDRS syntax error at `%s'\n"), (yyvsp[-2].name));
		}
#line 4153 "ldgram.c" /* yacc.c:1646  */
    break;

  case 324:
#line 1248 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.phdr) = (yyvsp[0].phdr);
		  (yyval.phdr).at = (yyvsp[-2].etree);
		}
#line 4162 "ldgram.c" /* yacc.c:1646  */
    break;

  case 325:
#line 1256 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.etree) = NULL;
		}
#line 4170 "ldgram.c" /* yacc.c:1646  */
    break;

  case 326:
#line 1260 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.etree) = (yyvsp[-1].etree);
		}
#line 4178 "ldgram.c" /* yacc.c:1646  */
    break;

  case 327:
#line 1266 "ldgram.y" /* yacc.c:1646  */
    {
		  ldlex_version_file ();
		  PUSH_ERROR (_("dynamic list"));
		}
#line 4187 "ldgram.c" /* yacc.c:1646  */
    break;

  case 328:
#line 1271 "ldgram.y" /* yacc.c:1646  */
    {
		  ldlex_popstate ();
		  POP_ERROR ();
		}
#line 4196 "ldgram.c" /* yacc.c:1646  */
    break;

  case 332:
#line 1288 "ldgram.y" /* yacc.c:1646  */
    {
		  lang_append_dynamic_list ((yyvsp[-1].versyms));
		}
#line 4204 "ldgram.c" /* yacc.c:1646  */
    break;

  case 333:
#line 1296 "ldgram.y" /* yacc.c:1646  */
    {
		  ldlex_version_file ();
		  PUSH_ERROR (_("VERSION script"));
		}
#line 4213 "ldgram.c" /* yacc.c:1646  */
    break;

  case 334:
#line 1301 "ldgram.y" /* yacc.c:1646  */
    {
		  ldlex_popstate ();
		  POP_ERROR ();
		}
#line 4222 "ldgram.c" /* yacc.c:1646  */
    break;

  case 335:
#line 1310 "ldgram.y" /* yacc.c:1646  */
    {
		  ldlex_version_script ();
		}
#line 4230 "ldgram.c" /* yacc.c:1646  */
    break;

  case 336:
#line 1314 "ldgram.y" /* yacc.c:1646  */
    {
		  ldlex_popstate ();
		}
#line 4238 "ldgram.c" /* yacc.c:1646  */
    break;

  case 339:
#line 1326 "ldgram.y" /* yacc.c:1646  */
    {
		  lang_register_vers_node (NULL, (yyvsp[-2].versnode), NULL);
		}
#line 4246 "ldgram.c" /* yacc.c:1646  */
    break;

  case 340:
#line 1330 "ldgram.y" /* yacc.c:1646  */
    {
		  lang_register_vers_node ((yyvsp[-4].name), (yyvsp[-2].versnode), NULL);
		}
#line 4254 "ldgram.c" /* yacc.c:1646  */
    break;

  case 341:
#line 1334 "ldgram.y" /* yacc.c:1646  */
    {
		  lang_register_vers_node ((yyvsp[-5].name), (yyvsp[-3].versnode), (yyvsp[-1].deflist));
		}
#line 4262 "ldgram.c" /* yacc.c:1646  */
    break;

  case 342:
#line 1341 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.deflist) = lang_add_vers_depend (NULL, (yyvsp[0].name));
		}
#line 4270 "ldgram.c" /* yacc.c:1646  */
    break;

  case 343:
#line 1345 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.deflist) = lang_add_vers_depend ((yyvsp[-1].deflist), (yyvsp[0].name));
		}
#line 4278 "ldgram.c" /* yacc.c:1646  */
    break;

  case 344:
#line 1352 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.versnode) = lang_new_vers_node (NULL, NULL);
		}
#line 4286 "ldgram.c" /* yacc.c:1646  */
    break;

  case 345:
#line 1356 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.versnode) = lang_new_vers_node ((yyvsp[-1].versyms), NULL);
		}
#line 4294 "ldgram.c" /* yacc.c:1646  */
    break;

  case 346:
#line 1360 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.versnode) = lang_new_vers_node ((yyvsp[-1].versyms), NULL);
		}
#line 4302 "ldgram.c" /* yacc.c:1646  */
    break;

  case 347:
#line 1364 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.versnode) = lang_new_vers_node (NULL, (yyvsp[-1].versyms));
		}
#line 4310 "ldgram.c" /* yacc.c:1646  */
    break;

  case 348:
#line 1368 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.versnode) = lang_new_vers_node ((yyvsp[-5].versyms), (yyvsp[-1].versyms));
		}
#line 4318 "ldgram.c" /* yacc.c:1646  */
    break;

  case 349:
#line 1375 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.versyms) = lang_new_vers_pattern (NULL, (yyvsp[0].name), ldgram_vers_current_lang, FALSE);
		}
#line 4326 "ldgram.c" /* yacc.c:1646  */
    break;

  case 350:
#line 1379 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.versyms) = lang_new_vers_pattern (NULL, (yyvsp[0].name), ldgram_vers_current_lang, TRUE);
		}
#line 4334 "ldgram.c" /* yacc.c:1646  */
    break;

  case 351:
#line 1383 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.versyms) = lang_new_vers_pattern ((yyvsp[-2].versyms), (yyvsp[0].name), ldgram_vers_current_lang, FALSE);
		}
#line 4342 "ldgram.c" /* yacc.c:1646  */
    break;

  case 352:
#line 1387 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.versyms) = lang_new_vers_pattern ((yyvsp[-2].versyms), (yyvsp[0].name), ldgram_vers_current_lang, TRUE);
		}
#line 4350 "ldgram.c" /* yacc.c:1646  */
    break;

  case 353:
#line 1391 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.name) = ldgram_vers_current_lang;
			  ldgram_vers_current_lang = (yyvsp[-1].name);
			}
#line 4359 "ldgram.c" /* yacc.c:1646  */
    break;

  case 354:
#line 1396 "ldgram.y" /* yacc.c:1646  */
    {
			  struct bfd_elf_version_expr *pat;
			  for (pat = (yyvsp[-2].versyms); pat->next != NULL; pat = pat->next);
			  pat->next = (yyvsp[-8].versyms);
			  (yyval.versyms) = (yyvsp[-2].versyms);
			  ldgram_vers_current_lang = (yyvsp[-3].name);
			}
#line 4371 "ldgram.c" /* yacc.c:1646  */
    break;

  case 355:
#line 1404 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.name) = ldgram_vers_current_lang;
			  ldgram_vers_current_lang = (yyvsp[-1].name);
			}
#line 4380 "ldgram.c" /* yacc.c:1646  */
    break;

  case 356:
#line 1409 "ldgram.y" /* yacc.c:1646  */
    {
			  (yyval.versyms) = (yyvsp[-2].versyms);
			  ldgram_vers_current_lang = (yyvsp[-3].name);
			}
#line 4389 "ldgram.c" /* yacc.c:1646  */
    break;

  case 357:
#line 1414 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.versyms) = lang_new_vers_pattern (NULL, "global", ldgram_vers_current_lang, FALSE);
		}
#line 4397 "ldgram.c" /* yacc.c:1646  */
    break;

  case 358:
#line 1418 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.versyms) = lang_new_vers_pattern ((yyvsp[-2].versyms), "global", ldgram_vers_current_lang, FALSE);
		}
#line 4405 "ldgram.c" /* yacc.c:1646  */
    break;

  case 359:
#line 1422 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.versyms) = lang_new_vers_pattern (NULL, "local", ldgram_vers_current_lang, FALSE);
		}
#line 4413 "ldgram.c" /* yacc.c:1646  */
    break;

  case 360:
#line 1426 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.versyms) = lang_new_vers_pattern ((yyvsp[-2].versyms), "local", ldgram_vers_current_lang, FALSE);
		}
#line 4421 "ldgram.c" /* yacc.c:1646  */
    break;

  case 361:
#line 1430 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.versyms) = lang_new_vers_pattern (NULL, "extern", ldgram_vers_current_lang, FALSE);
		}
#line 4429 "ldgram.c" /* yacc.c:1646  */
    break;

  case 362:
#line 1434 "ldgram.y" /* yacc.c:1646  */
    {
		  (yyval.versyms) = lang_new_vers_pattern ((yyvsp[-2].versyms), "extern", ldgram_vers_current_lang, FALSE);
		}
#line 4437 "ldgram.c" /* yacc.c:1646  */
    break;


#line 4441 "ldgram.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1444 "ldgram.y" /* yacc.c:1906  */

void
yyerror(arg)
     const char *arg;
{
  if (ldfile_assumed_script)
    einfo (_("%P:%s: file format not recognized; treating as linker script\n"),
	   ldfile_input_filename);
  if (error_index > 0 && error_index < ERROR_NAME_MAX)
     einfo ("%P%F:%S: %s in %s\n", arg, error_names[error_index-1]);
  else
     einfo ("%P%F:%S: %s\n", arg);
}
