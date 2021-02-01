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
#line 1 "rcparse.y" /* yacc.c:339  */
 /* rcparse.y -- parser for Windows rc files
   Copyright 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2005, 2007, 2008
   Free Software Foundation, Inc.
   Written by Ian Lance Taylor, Cygnus Support.
   Extended by Kai Tietz, Onevision.

   This file is part of GNU Binutils.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */


/* This is a parser for Windows rc files.  It is based on the parser
   by Gunther Ebert <gunther.ebert@ixos-leipzig.de>.  */

#include "sysdep.h"
#include "bfd.h"
#include "bucomm.h"
#include "libiberty.h"
#include "windres.h"
#include "safe-ctype.h"

/* The current language.  */

static unsigned short language;

/* The resource information during a sub statement.  */

static rc_res_res_info sub_res_info;

/* Dialog information.  This is built by the nonterminals styles and
   controls.  */

static rc_dialog dialog;

/* This is used when building a style.  It is modified by the
   nonterminal styleexpr.  */

static unsigned long style;

/* These are used when building a control.  They are set before using
   control_params.  */

static rc_uint_type base_style;
static rc_uint_type default_style;
static rc_res_id class;
static rc_res_id res_text_field;
static unichar null_unichar;

/* This is used for COMBOBOX, LISTBOX and EDITTEXT which
   do not allow resource 'text' field in control definition. */
static const rc_res_id res_null_text = { 1, {{0, &null_unichar}}};


#line 133 "rcparse.c" /* yacc.c:339  */

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
    BEG = 258,
    END = 259,
    ACCELERATORS = 260,
    VIRTKEY = 261,
    ASCII = 262,
    NOINVERT = 263,
    SHIFT = 264,
    CONTROL = 265,
    ALT = 266,
    BITMAP = 267,
    CURSOR = 268,
    DIALOG = 269,
    DIALOGEX = 270,
    EXSTYLE = 271,
    CAPTION = 272,
    CLASS = 273,
    STYLE = 274,
    AUTO3STATE = 275,
    AUTOCHECKBOX = 276,
    AUTORADIOBUTTON = 277,
    CHECKBOX = 278,
    COMBOBOX = 279,
    CTEXT = 280,
    DEFPUSHBUTTON = 281,
    EDITTEXT = 282,
    GROUPBOX = 283,
    LISTBOX = 284,
    LTEXT = 285,
    PUSHBOX = 286,
    PUSHBUTTON = 287,
    RADIOBUTTON = 288,
    RTEXT = 289,
    SCROLLBAR = 290,
    STATE3 = 291,
    USERBUTTON = 292,
    BEDIT = 293,
    HEDIT = 294,
    IEDIT = 295,
    FONT = 296,
    ICON = 297,
    ANICURSOR = 298,
    ANIICON = 299,
    DLGINCLUDE = 300,
    DLGINIT = 301,
    FONTDIR = 302,
    HTML = 303,
    MANIFEST = 304,
    PLUGPLAY = 305,
    VXD = 306,
    TOOLBAR = 307,
    BUTTON = 308,
    LANGUAGE = 309,
    CHARACTERISTICS = 310,
    VERSIONK = 311,
    MENU = 312,
    MENUEX = 313,
    MENUITEM = 314,
    SEPARATOR = 315,
    POPUP = 316,
    CHECKED = 317,
    GRAYED = 318,
    HELP = 319,
    INACTIVE = 320,
    MENUBARBREAK = 321,
    MENUBREAK = 322,
    MESSAGETABLE = 323,
    RCDATA = 324,
    STRINGTABLE = 325,
    VERSIONINFO = 326,
    FILEVERSION = 327,
    PRODUCTVERSION = 328,
    FILEFLAGSMASK = 329,
    FILEFLAGS = 330,
    FILEOS = 331,
    FILETYPE = 332,
    FILESUBTYPE = 333,
    BLOCKSTRINGFILEINFO = 334,
    BLOCKVARFILEINFO = 335,
    VALUE = 336,
    BLOCK = 337,
    MOVEABLE = 338,
    FIXED = 339,
    PURE = 340,
    IMPURE = 341,
    PRELOAD = 342,
    LOADONCALL = 343,
    DISCARDABLE = 344,
    NOT = 345,
    QUOTEDUNISTRING = 346,
    QUOTEDSTRING = 347,
    STRING = 348,
    NUMBER = 349,
    SIZEDUNISTRING = 350,
    SIZEDSTRING = 351,
    IGNORED_TOKEN = 352,
    NEG = 353
  };
#endif
/* Tokens.  */
#define BEG 258
#define END 259
#define ACCELERATORS 260
#define VIRTKEY 261
#define ASCII 262
#define NOINVERT 263
#define SHIFT 264
#define CONTROL 265
#define ALT 266
#define BITMAP 267
#define CURSOR 268
#define DIALOG 269
#define DIALOGEX 270
#define EXSTYLE 271
#define CAPTION 272
#define CLASS 273
#define STYLE 274
#define AUTO3STATE 275
#define AUTOCHECKBOX 276
#define AUTORADIOBUTTON 277
#define CHECKBOX 278
#define COMBOBOX 279
#define CTEXT 280
#define DEFPUSHBUTTON 281
#define EDITTEXT 282
#define GROUPBOX 283
#define LISTBOX 284
#define LTEXT 285
#define PUSHBOX 286
#define PUSHBUTTON 287
#define RADIOBUTTON 288
#define RTEXT 289
#define SCROLLBAR 290
#define STATE3 291
#define USERBUTTON 292
#define BEDIT 293
#define HEDIT 294
#define IEDIT 295
#define FONT 296
#define ICON 297
#define ANICURSOR 298
#define ANIICON 299
#define DLGINCLUDE 300
#define DLGINIT 301
#define FONTDIR 302
#define HTML 303
#define MANIFEST 304
#define PLUGPLAY 305
#define VXD 306
#define TOOLBAR 307
#define BUTTON 308
#define LANGUAGE 309
#define CHARACTERISTICS 310
#define VERSIONK 311
#define MENU 312
#define MENUEX 313
#define MENUITEM 314
#define SEPARATOR 315
#define POPUP 316
#define CHECKED 317
#define GRAYED 318
#define HELP 319
#define INACTIVE 320
#define MENUBARBREAK 321
#define MENUBREAK 322
#define MESSAGETABLE 323
#define RCDATA 324
#define STRINGTABLE 325
#define VERSIONINFO 326
#define FILEVERSION 327
#define PRODUCTVERSION 328
#define FILEFLAGSMASK 329
#define FILEFLAGS 330
#define FILEOS 331
#define FILETYPE 332
#define FILESUBTYPE 333
#define BLOCKSTRINGFILEINFO 334
#define BLOCKVARFILEINFO 335
#define VALUE 336
#define BLOCK 337
#define MOVEABLE 338
#define FIXED 339
#define PURE 340
#define IMPURE 341
#define PRELOAD 342
#define LOADONCALL 343
#define DISCARDABLE 344
#define NOT 345
#define QUOTEDUNISTRING 346
#define QUOTEDSTRING 347
#define STRING 348
#define NUMBER 349
#define SIZEDUNISTRING 350
#define SIZEDSTRING 351
#define IGNORED_TOKEN 352
#define NEG 353

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 69 "rcparse.y" /* yacc.c:355  */

  rc_accelerator acc;
  rc_accelerator *pacc;
  rc_dialog_control *dialog_control;
  rc_menuitem *menuitem;
  struct
  {
    rc_rcdata_item *first;
    rc_rcdata_item *last;
  } rcdata;
  rc_rcdata_item *rcdata_item;
  rc_fixed_versioninfo *fixver;
  rc_ver_info *verinfo;
  rc_ver_stringinfo *verstring;
  rc_ver_varinfo *vervar;
  rc_toolbar_item *toobar_item;
  rc_res_id id;
  rc_res_res_info res_info;
  struct
  {
    rc_uint_type on;
    rc_uint_type off;
  } memflags;
  struct
  {
    rc_uint_type val;
    /* Nonzero if this number was explicitly specified as long.  */
    int dword;
  } i;
  rc_uint_type il;
  rc_uint_type is;
  const char *s;
  struct
  {
    rc_uint_type length;
    const char *s;
  } ss;
  unichar *uni;
  struct
  {
    rc_uint_type length;
    const unichar *s;
  } suni;

#line 414 "rcparse.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 431 "rcparse.c" /* yacc.c:358  */

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   835

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  112
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  99
/* YYNRULES -- Number of rules.  */
#define YYNRULES  270
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  515

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   353

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   105,   100,     2,
     110,   111,   103,   101,   108,   102,     2,   104,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   109,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    99,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    98,     2,   106,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,   107
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   177,   177,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   199,   210,
     213,   234,   239,   251,   271,   281,   285,   290,   297,   301,
     306,   310,   314,   318,   327,   339,   353,   351,   378,   376,
     405,   403,   435,   438,   444,   446,   452,   456,   461,   465,
     469,   482,   497,   512,   527,   531,   535,   539,   545,   547,
     559,   558,   571,   570,   583,   582,   595,   594,   610,   609,
     622,   621,   635,   646,   656,   655,   668,   667,   680,   679,
     692,   691,   704,   703,   718,   723,   729,   735,   742,   741,
     757,   756,   769,   768,   781,   780,   792,   791,   804,   803,
     816,   815,   828,   827,   840,   839,   853,   851,   872,   883,
     894,   906,   917,   920,   924,   929,   939,   942,   952,   951,
     958,   957,   964,   963,   971,   983,   996,  1005,  1016,  1019,
    1036,  1040,  1044,  1052,  1055,  1059,  1066,  1070,  1074,  1078,
    1082,  1086,  1095,  1106,  1109,  1126,  1130,  1134,  1138,  1142,
    1146,  1150,  1154,  1164,  1177,  1177,  1189,  1193,  1200,  1208,
    1216,  1224,  1233,  1242,  1251,  1261,  1260,  1265,  1267,  1272,
    1277,  1285,  1289,  1294,  1299,  1304,  1309,  1314,  1319,  1324,
    1329,  1340,  1347,  1357,  1363,  1364,  1383,  1408,  1419,  1424,
    1430,  1436,  1441,  1446,  1451,  1456,  1471,  1474,  1478,  1486,
    1489,  1497,  1500,  1509,  1514,  1523,  1527,  1537,  1542,  1546,
    1557,  1563,  1569,  1574,  1579,  1590,  1595,  1607,  1612,  1624,
    1629,  1634,  1639,  1644,  1649,  1654,  1664,  1668,  1676,  1681,
    1696,  1700,  1709,  1713,  1725,  1729,  1751,  1755,  1759,  1763,
    1770,  1774,  1784,  1787,  1796,  1805,  1814,  1818,  1822,  1827,
    1832,  1837,  1842,  1847,  1852,  1857,  1862,  1867,  1878,  1887,
    1898,  1902,  1906,  1911,  1916,  1921,  1926,  1931,  1936,  1941,
    1946
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BEG", "END", "ACCELERATORS", "VIRTKEY",
  "ASCII", "NOINVERT", "SHIFT", "CONTROL", "ALT", "BITMAP", "CURSOR",
  "DIALOG", "DIALOGEX", "EXSTYLE", "CAPTION", "CLASS", "STYLE",
  "AUTO3STATE", "AUTOCHECKBOX", "AUTORADIOBUTTON", "CHECKBOX", "COMBOBOX",
  "CTEXT", "DEFPUSHBUTTON", "EDITTEXT", "GROUPBOX", "LISTBOX", "LTEXT",
  "PUSHBOX", "PUSHBUTTON", "RADIOBUTTON", "RTEXT", "SCROLLBAR", "STATE3",
  "USERBUTTON", "BEDIT", "HEDIT", "IEDIT", "FONT", "ICON", "ANICURSOR",
  "ANIICON", "DLGINCLUDE", "DLGINIT", "FONTDIR", "HTML", "MANIFEST",
  "PLUGPLAY", "VXD", "TOOLBAR", "BUTTON", "LANGUAGE", "CHARACTERISTICS",
  "VERSIONK", "MENU", "MENUEX", "MENUITEM", "SEPARATOR", "POPUP",
  "CHECKED", "GRAYED", "HELP", "INACTIVE", "MENUBARBREAK", "MENUBREAK",
  "MESSAGETABLE", "RCDATA", "STRINGTABLE", "VERSIONINFO", "FILEVERSION",
  "PRODUCTVERSION", "FILEFLAGSMASK", "FILEFLAGS", "FILEOS", "FILETYPE",
  "FILESUBTYPE", "BLOCKSTRINGFILEINFO", "BLOCKVARFILEINFO", "VALUE",
  "BLOCK", "MOVEABLE", "FIXED", "PURE", "IMPURE", "PRELOAD", "LOADONCALL",
  "DISCARDABLE", "NOT", "QUOTEDUNISTRING", "QUOTEDSTRING", "STRING",
  "NUMBER", "SIZEDUNISTRING", "SIZEDSTRING", "IGNORED_TOKEN", "'|'", "'^'",
  "'&'", "'+'", "'-'", "'*'", "'/'", "'%'", "'~'", "NEG", "','", "'='",
  "'('", "')'", "$accept", "input", "accelerator", "acc_entries",
  "acc_entry", "acc_event", "acc_options", "acc_option", "bitmap",
  "cursor", "dialog", "$@1", "$@2", "$@3", "exstyle", "styles", "controls",
  "control", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11",
  "$@12", "$@13", "$@14", "$@15", "$@16", "$@17", "$@18", "$@19", "$@20",
  "$@21", "$@22", "$@23", "$@24", "control_params", "cresid", "optresidc",
  "resid", "opt_control_data", "control_styleexpr", "$@25",
  "icon_styleexpr", "$@26", "control_params_styleexpr", "$@27", "font",
  "icon", "language", "menu", "menuitems", "menuitem", "menuitem_flags",
  "menuitem_flag", "menuex", "menuexitems", "menuexitem", "messagetable",
  "optrcdata_data", "$@28", "optrcdata_data_int", "rcdata_data",
  "stringtable", "$@29", "string_data", "rcdata_id", "user", "toolbar",
  "toolbar_data", "versioninfo", "fixedverinfo", "verblocks", "vervals",
  "vertrans", "id", "resname", "resref", "suboptions",
  "memflags_move_discard", "memflags_move", "memflag", "file_name",
  "res_unicode_string_concat", "res_unicode_string", "sizedstring",
  "sizedunistring", "styleexpr", "parennumber", "optcnumexpr", "cnumexpr",
  "numexpr", "sizednumexpr", "cposnumexpr", "posnumexpr",
  "sizedposnumexpr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   124,    94,
      38,    43,    45,    42,    47,    37,   126,   353,    44,    61,
      40,    41
};
# endif

#define YYPACT_NINF -309

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-309)))

#define YYTABLE_NINF -229

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -309,    68,  -309,   338,  -309,  -309,  -309,  -309,  -309,  -309,
     338,   338,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,   458,  -309,  -309,  -309,
     605,  -309,   338,   338,   338,   -92,   642,   230,  -309,   534,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,   338,   338,   338,   338,   338,   338,   338,
     338,  -309,  -309,   695,   338,  -309,   338,   338,   338,   338,
     338,   338,   338,   338,  -309,   338,   338,   338,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,   329,   724,   724,
     242,   242,   724,   724,   499,   434,   457,   724,   192,   250,
     392,   718,   318,   174,   174,  -309,  -309,  -309,  -309,  -309,
     392,   718,   318,   174,   174,  -309,  -309,  -309,  -309,   -92,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,   -81,
     263,   263,  -309,  -309,   -92,  -309,  -309,  -309,  -309,   338,
     338,   338,   338,   338,   338,   338,  -309,  -309,     6,  -309,
      13,   338,   -92,   -92,    48,     8,   105,    35,   -92,   -92,
    -309,  -309,  -309,  -309,  -309,    53,   373,  -309,  -309,   -38,
    -309,  -309,  -309,   -48,  -309,  -309,   -92,   -92,  -309,  -309,
     -36,     7,  -309,  -309,    80,     7,  -309,  -309,    60,   103,
     -92,   -92,  -309,  -309,  -309,  -309,    17,    38,    47,   642,
       7,     7,  -309,   263,    65,   -92,   -92,    -1,  -309,   163,
       7,  -309,   163,    12,    74,    94,   -92,   -92,   373,  -309,
    -309,     7,  -309,  -309,   818,  -309,   -92,  -309,   253,  -309,
    -309,   184,   -92,  -309,     5,   177,     7,  -309,  -309,    38,
      47,   642,  -309,  -309,  -309,  -309,  -309,  -309,    25,  -309,
    -309,  -309,  -309,  -309,   155,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,   768,  -309,   -92,   120,  -309,    10,  -309,     7,
     818,  -309,   556,   562,  -309,   137,  -309,  -309,  -309,  -309,
     141,  -309,   -92,    21,     2,  -309,  -309,   338,     7,   253,
     -46,   338,   338,   338,   338,   253,  -309,   573,  -309,  -309,
     153,   188,   172,     7,  -309,   -92,   655,  -309,     7,  -309,
       7,    40,    27,  -309,   338,    99,  -309,    93,   -92,  -309,
    -309,  -309,   692,  -309,  -309,  -309,  -309,   168,  -309,  -309,
     258,   258,   258,   258,   258,  -309,   258,   258,  -309,   258,
    -309,   258,   258,   258,   258,   258,  -309,   258,   253,   258,
     258,   258,   253,  -309,  -309,    95,    98,     7,  -309,  -309,
     729,   173,     7,   338,   102,     7,  -309,  -309,  -309,  -309,
    -309,   338,  -309,  -309,   338,  -309,   338,  -309,  -309,  -309,
    -309,  -309,   338,  -309,   117,   338,   123,  -309,  -309,  -309,
     338,  -309,    27,  -309,   163,  -309,  -309,     7,   128,  -309,
     338,   338,   338,   338,  -309,   -92,   338,   338,  -309,   338,
    -309,   338,   338,   338,   338,   338,  -309,   338,  -309,   131,
    -309,   338,   338,   338,   -92,  -309,   -92,   258,   132,  -309,
    -309,  -309,  -309,   -92,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,   338,  -309,  -309,  -309,   -92,   -92,  -309,
    -309,   -92,   -92,   149,    18,  -309,   -46,   -92,   -92,   338,
    -309,  -309,   -92,    99,   -92,    19,   154,   203,    20,   -92,
    -309,  -309,   -92,   338,  -309,  -309,  -309,   -92,   -92,   -46,
     225,   -92,   165,   -46,   225,   -92,   225,   -92,    99,  -309,
     225,   338,    99,  -309,   225,  -309,   225,  -309,   182,  -309,
    -309,  -309,   -46,   -71,  -309
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,   210,   230,   231,   206,   260,    17,
       0,     0,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    15,    14,    16,     0,   204,   205,   203,
     259,   246,     0,     0,     0,     0,   245,     0,   262,     0,
     210,   217,   215,   217,   217,   215,   215,   179,   180,   177,
     178,   172,   174,   175,   176,   210,   210,   210,   217,   173,
     188,   210,   171,     0,     0,     0,     0,     0,     0,     0,
       0,   249,   248,     0,     0,   126,     0,     0,     0,     0,
       0,     0,     0,     0,   165,     0,     0,     0,   219,   220,
     221,   222,   223,   224,   225,   211,   261,     0,     0,     0,
      42,    42,     0,     0,     0,     0,     0,     0,     0,     0,
     270,   269,   268,   266,   267,   263,   264,   265,   247,   244,
     257,   256,   255,   253,   254,   250,   251,   252,   167,     0,
     212,   214,    19,   226,   227,   218,    34,   216,    35,     0,
       0,     0,   124,   125,     0,   128,   143,   153,   196,     0,
       0,     0,     0,     0,     0,     0,   154,   182,     0,   213,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     191,   192,   193,   194,   195,     0,   156,   170,   166,     0,
      18,    23,    20,     0,    24,    43,     0,     0,   184,   127,
       0,     0,   129,   142,     0,     0,   144,   187,     0,     0,
       0,     0,   181,   234,   232,   155,   157,   158,   159,   160,
       0,   168,   228,     0,    21,     0,     0,     0,   131,     0,
     133,   148,   145,     0,     0,     0,     0,     0,   164,   233,
     235,   169,   229,   258,     0,    36,    38,   183,     0,   186,
     133,     0,   146,   143,     0,     0,     0,   189,   190,   161,
     162,   163,    28,    29,    30,    31,    32,    33,    22,    25,
      44,    44,    40,   185,   130,   128,   136,   137,   138,   139,
     140,   141,     0,   135,   242,     0,   143,     0,   199,   201,
       0,    27,     0,     0,    44,     0,   134,   147,   243,   149,
       0,   143,   242,     0,     0,    26,    58,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    58,     0,   132,   150,
       0,     0,     0,     0,   198,     0,     0,    48,    45,    46,
      49,   205,     0,   240,     0,    47,   236,     0,     0,    55,
      57,    54,     0,    58,   151,   143,   197,     0,   202,    37,
     112,   112,   112,   112,   112,    70,   112,   112,    78,   112,
      90,   112,   112,   112,   112,   112,   102,   112,     0,   112,
     112,   112,     0,    59,   237,     0,     0,     0,    56,    39,
       0,     0,     0,     0,     0,   115,   114,    60,    62,    64,
      68,     0,    74,    76,     0,    80,     0,    92,    94,    96,
      98,   100,     0,   104,   208,     0,     0,    66,    82,    88,
       0,   241,     0,   238,    50,    41,   152,   200,     0,   113,
       0,     0,     0,     0,    71,     0,     0,     0,    79,     0,
      91,     0,     0,     0,     0,     0,   103,     0,   209,     0,
     207,     0,     0,     0,     0,   239,    51,     0,     0,    61,
      63,    65,    69,     0,    75,    77,    81,    93,    95,    97,
      99,   101,   105,     0,    67,    83,    89,     0,    52,   111,
     118,     0,     0,     0,   116,    53,     0,     0,     0,     0,
     154,    84,     0,   119,     0,   116,     0,     0,   116,     0,
     122,   108,   242,     0,   117,   120,    85,   242,   242,     0,
     116,   243,     0,     0,   116,   243,   116,   243,   123,   109,
     116,     0,   121,    86,   116,    72,   116,   110,     0,    87,
      73,   106,     0,   242,   107
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -240,  -309,  -309,
    -309,  -309,  -309,  -309,   144,  -235,  -295,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,   239,
    -309,   431,  -156,  -100,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,    26,  -309,    56,    39,  -309,  -196,
    -309,  -309,  -173,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,   -25,  -265,
     -55,   232,     0,   333,   432,   375,  -129,     4,    82,    84,
    -237,  -308,  -283,   -33,    -3,     9,  -309,     3,  -309
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    12,   160,   182,   183,   258,   259,    13,    14,
      15,   260,   261,   284,   140,   282,   316,   363,   410,   411,
     412,   431,   413,   381,   416,   417,   384,   419,   432,   433,
     386,   421,   422,   423,   424,   425,   392,   427,   512,   414,
     438,   373,   374,   471,   461,   466,   487,   493,   482,   489,
      16,    17,    18,    19,   165,   192,   241,   273,    20,   166,
     196,    21,   175,   176,   205,   206,    22,   128,   158,    61,
      23,    24,   217,    25,   108,   167,   293,   294,    26,    27,
     395,    37,    99,    98,    95,   136,   375,   212,   207,   208,
     325,   326,   287,   288,   415,    36,   214,   376,    30
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,    62,    75,   237,    29,    28,   314,   177,   276,   311,
     178,   332,   189,   291,   364,   243,    74,   180,   281,    38,
      39,   470,   470,   470,   218,   312,   283,   366,   161,    29,
      28,   252,   253,   254,   255,   256,   257,    74,   370,   197,
     295,    71,    72,    73,   322,   102,   103,   275,   323,   307,
     211,   188,   238,     5,     6,     5,     6,   202,   403,   239,
     213,   219,   220,   224,   324,   222,   223,   190,     2,   191,
     210,   119,   110,   111,   112,   113,   114,   115,   116,   117,
     290,   231,   129,   130,   131,   120,   121,   122,   123,   124,
     125,   126,   127,   394,   435,   310,   159,   394,     5,     6,
      31,   144,   313,     5,     6,   181,   225,     8,    32,   193,
      74,   164,    33,    74,   198,   199,    34,   279,    74,    10,
      74,   323,     3,    11,   289,   228,    74,   480,   485,   186,
     187,  -228,  -228,   280,   229,   200,   201,   324,     4,   371,
     221,   308,   230,   162,   163,   309,   168,   169,   170,   171,
     172,   173,   174,   215,   216,   179,   245,   334,   185,     5,
       6,     7,     8,   184,   194,     9,   195,   226,   227,   318,
     320,     5,     6,   234,    10,   246,   336,   406,    11,   194,
     278,   195,   235,   236,   337,   209,   240,   265,   402,   242,
     244,   335,   323,   247,   248,   148,   190,   366,   191,   490,
     194,   367,   195,   262,   494,   496,   401,   484,   324,   274,
     409,   277,   194,   263,   195,   232,   233,   266,   267,   268,
     269,   270,   271,   232,   232,   428,   232,   232,   470,   473,
     514,   430,   194,    84,   195,   232,   437,   251,   404,   453,
     460,    29,    28,   407,   292,   141,   266,   267,   268,   269,
     270,   271,   498,   156,     5,     6,   502,   469,   139,     5,
       6,   315,   483,   272,   149,   150,   151,   152,   153,   154,
     155,    74,    97,   501,   319,   513,   372,    81,    82,    83,
     331,   459,   338,   232,    85,    86,    87,   104,   105,   106,
     511,   285,   272,   109,   317,   368,   264,   477,   327,   328,
     329,   330,    29,   321,    85,    86,    87,   400,    29,    28,
     249,   286,   250,    88,    89,    90,    91,    92,    93,    94,
       0,   365,   232,     0,   232,    88,    89,    90,    91,    92,
      93,    94,   132,    88,    89,    90,    91,    92,    93,    94,
       0,   232,   133,   134,     5,     6,     7,     8,     0,     5,
       6,     0,     8,     0,     0,     0,     0,     8,     0,    10,
       0,   396,    28,    11,    10,   396,    28,     0,    11,    10,
     408,   436,     0,    11,     0,   481,   100,   101,   486,   232,
       0,     0,   443,    85,    86,    87,     0,     0,     0,     0,
     499,   107,   429,     0,   503,     0,   505,   434,     0,     0,
     507,   457,     0,   458,   509,     0,   510,     0,   232,     0,
     462,   232,    88,    89,    90,    91,    92,    93,    94,    79,
      80,    81,    82,    83,   464,   465,     0,     0,   467,   468,
       0,   472,    31,     0,   474,   475,     0,   145,     0,   478,
      32,   479,     0,     0,    33,     0,   488,     0,    34,   491,
     463,     0,     0,     0,   495,   497,     0,     0,   500,     0,
     146,     0,   504,    40,   506,     0,   476,    31,   203,   204,
      41,    42,    43,    44,   138,    32,     0,   142,   143,    33,
     492,     0,   147,    34,   157,     0,     0,     0,    85,    86,
      87,    77,    78,    79,    80,    81,    82,    83,   508,    45,
      46,    47,    48,    49,    50,     0,    51,    52,    53,    54,
      55,    85,    86,    87,     0,    56,    57,    88,    89,    90,
      91,    92,    93,    94,     0,     0,    58,    59,     0,    60,
     135,   137,   135,   135,   137,   137,     0,     0,     0,   135,
      88,    89,    90,    91,    92,    93,    94,     0,     0,     5,
       6,     7,     8,    85,    86,    87,     0,     0,     0,   296,
       0,     0,     0,     0,    10,   306,     0,     0,    11,     0,
       0,     0,   297,   298,   299,   300,   333,     0,   297,   298,
     299,   300,    88,    89,    90,    91,    92,    93,    94,   297,
     298,   299,   300,    31,     0,     0,     0,   301,     0,     0,
       0,    32,     0,   301,     0,    33,     0,     0,     0,    34,
     302,   303,   304,   305,   301,     0,   302,   303,   304,   305,
       0,     0,     0,   418,     0,   420,     0,   302,   303,   304,
     305,   426,    76,    77,    78,    79,    80,    81,    82,    83,
       0,     0,     0,     0,     0,    96,     0,     0,     0,   439,
     440,   441,   442,     0,     0,   444,   445,     0,   446,   339,
     447,   448,   449,   450,   451,   340,   452,     0,     0,     0,
     454,   455,   456,     0,     0,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   369,   362,     0,     0,
       0,     0,   340,    63,    64,    65,    66,    67,    68,    69,
      70,     0,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   405,   362,     0,     0,     0,     0,   340,
      76,    77,    78,    79,    80,    81,    82,    83,     0,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
       0,   362,   377,   378,   379,   380,     0,   382,   383,     0,
     385,     0,   387,   388,   389,   390,   391,     0,   393,     0,
     397,   398,   399,    76,    77,    78,    79,    80,    81,    82,
      83,     0,     0,     0,     0,     0,   118,    88,    89,    90,
      91,    92,    93,    94,     0,     0,   133,   134,    78,    79,
      80,    81,    82,    83,   252,   253,   254,   255,   256,   257,
     266,   267,   268,   269,   270,   271
};

static const yytype_int16 yycheck[] =
{
       3,    26,    35,     4,     1,     1,     4,     1,     3,   292,
       4,   306,     4,     3,   322,     3,   108,     4,   258,    10,
      11,     3,     3,     3,    60,     4,   261,    98,   109,    26,
      26,     6,     7,     8,     9,    10,    11,   108,   333,     4,
     280,    32,    33,    34,    90,    45,    46,   243,    94,   284,
     179,     3,    53,    91,    92,    91,    92,     4,   366,    60,
     108,   190,   191,     3,   110,   194,   195,    59,     0,    61,
     108,    74,    63,    64,    65,    66,    67,    68,    69,    70,
     276,   210,    85,    86,    87,    76,    77,    78,    79,    80,
      81,    82,    83,   358,   402,   291,   129,   362,    91,    92,
      94,   104,    81,    91,    92,    92,     3,    94,   102,     4,
     108,   144,   106,   108,    79,    80,   110,   246,   108,   106,
     108,    94,    54,   110,     4,   108,   108,   108,   108,   162,
     163,    91,    92,   108,    96,   168,   169,   110,    70,   335,
      60,     4,    95,   140,   141,     4,   149,   150,   151,   152,
     153,   154,   155,   186,   187,   158,    82,     4,   161,    91,
      92,    93,    94,   160,    59,    97,    61,   200,   201,   298,
     299,    91,    92,   108,   106,    81,     4,     4,   110,    59,
       3,    61,   215,   216,   313,   176,   219,     3,    90,   222,
     223,     3,    94,   226,   227,     3,    59,    98,    61,   482,
      59,   108,    61,   236,   487,   488,   111,     4,   110,   242,
     108,   244,    59,   238,    61,   211,   213,    62,    63,    64,
      65,    66,    67,   219,   220,   108,   222,   223,     3,   466,
     513,   108,    59,     3,    61,   231,   108,   228,   367,   108,
     108,   238,   238,   372,   277,   101,    62,    63,    64,    65,
      66,    67,   489,     3,    91,    92,   493,   108,    16,    91,
      92,   294,   108,   108,    72,    73,    74,    75,    76,    77,
      78,   108,    40,   108,   299,   512,   108,   103,   104,   105,
     305,   437,   315,   279,    54,    55,    56,    55,    56,    57,
     108,   265,   108,    61,   297,   328,   240,   470,   301,   302,
     303,   304,   299,   299,    54,    55,    56,   362,   305,   305,
     228,   272,   228,    83,    84,    85,    86,    87,    88,    89,
      -1,   324,   318,    -1,   320,    83,    84,    85,    86,    87,
      88,    89,     3,    83,    84,    85,    86,    87,    88,    89,
      -1,   337,    92,    93,    91,    92,    93,    94,    -1,    91,
      92,    -1,    94,    -1,    -1,    -1,    -1,    94,    -1,   106,
      -1,   358,   358,   110,   106,   362,   362,    -1,   110,   106,
     373,   404,    -1,   110,    -1,   475,    43,    44,   478,   375,
      -1,    -1,   415,    54,    55,    56,    -1,    -1,    -1,    -1,
     490,    58,   395,    -1,   494,    -1,   496,   400,    -1,    -1,
     500,   434,    -1,   436,   504,    -1,   506,    -1,   404,    -1,
     443,   407,    83,    84,    85,    86,    87,    88,    89,   101,
     102,   103,   104,   105,   457,   458,    -1,    -1,   461,   462,
      -1,   464,    94,    -1,   467,   468,    -1,     3,    -1,   472,
     102,   474,    -1,    -1,   106,    -1,   479,    -1,   110,   482,
     453,    -1,    -1,    -1,   487,   488,    -1,    -1,   491,    -1,
       3,    -1,   495,     5,   497,    -1,   469,    94,    95,    96,
      12,    13,    14,    15,    99,   102,    -1,   102,   103,   106,
     483,    -1,   107,   110,   109,    -1,    -1,    -1,    54,    55,
      56,    99,   100,   101,   102,   103,   104,   105,   501,    41,
      42,    43,    44,    45,    46,    -1,    48,    49,    50,    51,
      52,    54,    55,    56,    -1,    57,    58,    83,    84,    85,
      86,    87,    88,    89,    -1,    -1,    68,    69,    -1,    71,
      98,    99,   100,   101,   102,   103,    -1,    -1,    -1,   107,
      83,    84,    85,    86,    87,    88,    89,    -1,    -1,    91,
      92,    93,    94,    54,    55,    56,    -1,    -1,    -1,     3,
      -1,    -1,    -1,    -1,   106,     3,    -1,    -1,   110,    -1,
      -1,    -1,    16,    17,    18,    19,     3,    -1,    16,    17,
      18,    19,    83,    84,    85,    86,    87,    88,    89,    16,
      17,    18,    19,    94,    -1,    -1,    -1,    41,    -1,    -1,
      -1,   102,    -1,    41,    -1,   106,    -1,    -1,    -1,   110,
      54,    55,    56,    57,    41,    -1,    54,    55,    56,    57,
      -1,    -1,    -1,   384,    -1,   386,    -1,    54,    55,    56,
      57,   392,    98,    99,   100,   101,   102,   103,   104,   105,
      -1,    -1,    -1,    -1,    -1,   111,    -1,    -1,    -1,   410,
     411,   412,   413,    -1,    -1,   416,   417,    -1,   419,     4,
     421,   422,   423,   424,   425,    10,   427,    -1,    -1,    -1,
     431,   432,   433,    -1,    -1,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     4,    42,    -1,    -1,
      -1,    -1,    10,    98,    99,   100,   101,   102,   103,   104,
     105,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,     4,    42,    -1,    -1,    -1,    -1,    10,
      98,    99,   100,   101,   102,   103,   104,   105,    -1,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      -1,    42,   341,   342,   343,   344,    -1,   346,   347,    -1,
     349,    -1,   351,   352,   353,   354,   355,    -1,   357,    -1,
     359,   360,   361,    98,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,    -1,   111,    83,    84,    85,
      86,    87,    88,    89,    -1,    -1,    92,    93,   100,   101,
     102,   103,   104,   105,     6,     7,     8,     9,    10,    11,
      62,    63,    64,    65,    66,    67
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   113,     0,    54,    70,    91,    92,    93,    94,    97,
     106,   110,   114,   120,   121,   122,   162,   163,   164,   165,
     170,   173,   178,   182,   183,   185,   190,   191,   199,   209,
     210,    94,   102,   106,   110,   206,   207,   193,   207,   207,
       5,    12,    13,    14,    15,    41,    42,    43,    44,    45,
      46,    48,    49,    50,    51,    52,    57,    58,    68,    69,
      71,   181,   190,    98,    99,   100,   101,   102,   103,   104,
     105,   207,   207,   207,   108,   205,    98,    99,   100,   101,
     102,   103,   104,   105,     3,    54,    55,    56,    83,    84,
      85,    86,    87,    88,    89,   196,   111,   193,   195,   194,
     195,   195,   194,   194,   193,   193,   193,   195,   186,   193,
     207,   207,   207,   207,   207,   207,   207,   207,   111,   206,
     207,   207,   207,   207,   207,   207,   207,   207,   179,   206,
     206,   206,     3,    92,    93,   196,   197,   196,   197,    16,
     126,   126,   197,   197,   206,     3,     3,   197,     3,    72,
      73,    74,    75,    76,    77,    78,     3,   197,   180,   205,
     115,   109,   209,   209,   205,   166,   171,   187,   206,   206,
     206,   206,   206,   206,   206,   174,   175,     1,     4,   206,
       4,    92,   116,   117,   209,   206,   205,   205,     3,     4,
      59,    61,   167,     4,    59,    61,   172,     4,    79,    80,
     205,   205,     4,    95,    96,   176,   177,   200,   201,   207,
     108,   198,   199,   108,   208,   205,   205,   184,    60,   198,
     198,    60,   198,   198,     3,     3,   205,   205,   108,    96,
      95,   198,   199,   209,   108,   205,   205,     4,    53,    60,
     205,   168,   205,     3,   205,    82,    81,   205,   205,   200,
     201,   207,     6,     7,     8,     9,    10,    11,   118,   119,
     123,   124,   205,   190,   168,     3,    62,    63,    64,    65,
      66,    67,   108,   169,   205,   171,     3,   205,     3,   198,
     108,   119,   127,   127,   125,   166,   169,   204,   205,     4,
     171,     3,   205,   188,   189,   119,     3,    16,    17,    18,
      19,    41,    54,    55,    56,    57,     3,   127,     4,     4,
     171,   204,     4,    81,     4,   205,   128,   206,   198,   190,
     198,   199,    90,    94,   110,   202,   203,   206,   206,   206,
     206,   190,   128,     3,     4,     3,     4,   198,   205,     4,
      10,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    42,   129,   203,   206,    98,   108,   205,     4,
     128,   171,   108,   153,   154,   198,   209,   153,   153,   153,
     153,   135,   153,   153,   138,   153,   142,   153,   153,   153,
     153,   153,   148,   153,   191,   192,   209,   153,   153,   153,
     192,   111,    90,   203,   198,     4,     4,   198,   206,   108,
     130,   131,   132,   134,   151,   206,   136,   137,   151,   139,
     151,   143,   144,   145,   146,   147,   151,   149,   108,   206,
     108,   133,   140,   141,   206,   203,   205,   108,   152,   151,
     151,   151,   151,   205,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   108,   151,   151,   151,   205,   205,   154,
     108,   156,   205,   206,   205,   205,   157,   205,   205,   108,
       3,   155,   205,   202,   205,   205,   206,   174,   205,   205,
     108,   155,   160,   108,     4,   108,   155,   158,   205,   161,
     204,   205,   206,   159,   204,   205,   204,   205,   202,   155,
     205,   108,   202,   155,   205,   155,   205,   155,   206,   155,
     155,   108,   150,   202,   204
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   112,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   114,   115,
     115,   116,   116,   117,   117,   118,   118,   118,   119,   119,
     119,   119,   119,   119,   120,   121,   123,   122,   124,   122,
     125,   122,   126,   126,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   128,   128,
     130,   129,   131,   129,   132,   129,   133,   129,   134,   129,
     135,   129,   129,   129,   136,   129,   137,   129,   138,   129,
     139,   129,   140,   129,   129,   129,   129,   129,   141,   129,
     142,   129,   143,   129,   144,   129,   145,   129,   146,   129,
     147,   129,   148,   129,   149,   129,   150,   129,   151,   151,
     151,   152,   153,   153,   154,   154,   155,   155,   157,   156,
     159,   158,   161,   160,   162,   163,   164,   165,   166,   166,
     167,   167,   167,   168,   168,   168,   169,   169,   169,   169,
     169,   169,   170,   171,   171,   172,   172,   172,   172,   172,
     172,   172,   172,   173,   175,   174,   176,   176,   177,   177,
     177,   177,   177,   177,   177,   179,   178,   180,   180,   180,
     180,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   182,   182,   183,   184,   184,   184,   185,   186,   186,
     186,   186,   186,   186,   186,   186,   187,   187,   187,   188,
     188,   189,   189,   190,   190,   191,   191,   192,   192,   192,
     193,   193,   193,   193,   193,   194,   194,   195,   195,   196,
     196,   196,   196,   196,   196,   196,   197,   197,   198,   198,
     199,   199,   200,   200,   201,   201,   202,   202,   202,   202,
     203,   203,   204,   204,   205,   206,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   208,   209,
     210,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     6,     0,
       2,     2,     4,     1,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     4,     4,     0,    13,     0,    13,
       0,    14,     0,     3,     0,     3,     3,     3,     3,     3,
       5,     6,     7,     8,     3,     3,     4,     3,     0,     2,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     3,    11,    12,     0,     4,     0,     4,     0,     3,
       0,     4,     0,     4,     6,     8,    10,    11,     0,     4,
       0,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     3,     0,     4,     0,    15,     6,     8,
       9,     2,     0,     2,     1,     1,     0,     3,     0,     3,
       0,     3,     0,     3,     4,     4,     3,     6,     0,     2,
       4,     2,     6,     0,     3,     2,     1,     1,     1,     1,
       1,     1,     6,     0,     2,     2,     3,     5,     2,     5,
       6,     7,     9,     4,     0,     2,     0,     1,     1,     1,
       1,     3,     3,     3,     2,     0,     6,     0,     3,     4,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     6,     4,     8,     0,     3,     2,     6,     0,     6,
       6,     3,     3,     3,     3,     3,     0,     8,     7,     0,
       5,     0,     3,     1,     1,     1,     1,     2,     1,     2,
       0,     2,     3,     4,     3,     0,     2,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     2,     1,     2,     1,     2,     3,     4,
       1,     3,     0,     1,     2,     1,     1,     3,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     3,     2,     3,     3,     3,     3,     3,     3,     3,
       3
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
        case 18:
#line 200 "rcparse.y" /* yacc.c:1646  */
    {
	    define_accelerator ((yyvsp[-5].id), &(yyvsp[-3].res_info), (yyvsp[-1].pacc));
	    if (yychar != YYEMPTY)
	      YYERROR;
	    rcparse_discard_strings ();
	  }
#line 1975 "rcparse.c" /* yacc.c:1646  */
    break;

  case 19:
#line 210 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.pacc) = NULL;
	  }
#line 1983 "rcparse.c" /* yacc.c:1646  */
    break;

  case 20:
#line 214 "rcparse.y" /* yacc.c:1646  */
    {
	    rc_accelerator *a;

	    a = (rc_accelerator *) res_alloc (sizeof *a);
	    *a = (yyvsp[0].acc);
	    if ((yyvsp[-1].pacc) == NULL)
	      (yyval.pacc) = a;
	    else
	      {
		rc_accelerator **pp;

		for (pp = &(yyvsp[-1].pacc)->next; *pp != NULL; pp = &(*pp)->next)
		  ;
		*pp = a;
		(yyval.pacc) = (yyvsp[-1].pacc);
	      }
	  }
#line 2005 "rcparse.c" /* yacc.c:1646  */
    break;

  case 21:
#line 235 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.acc) = (yyvsp[-1].acc);
	    (yyval.acc).id = (yyvsp[0].il);
	  }
#line 2014 "rcparse.c" /* yacc.c:1646  */
    break;

  case 22:
#line 240 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.acc) = (yyvsp[-3].acc);
	    (yyval.acc).id = (yyvsp[-2].il);
	    (yyval.acc).flags |= (yyvsp[0].is);
	    if (((yyval.acc).flags & ACC_VIRTKEY) == 0
		&& ((yyval.acc).flags & (ACC_SHIFT | ACC_CONTROL)) != 0)
	      rcparse_warning (_("inappropriate modifiers for non-VIRTKEY"));
	  }
#line 2027 "rcparse.c" /* yacc.c:1646  */
    break;

  case 23:
#line 252 "rcparse.y" /* yacc.c:1646  */
    {
	    const char *s = (yyvsp[0].s);
	    char ch;

	    (yyval.acc).next = NULL;
	    (yyval.acc).id = 0;
	    ch = *s;
	    if (ch != '^')
	      (yyval.acc).flags = 0;
	    else
	      {
		(yyval.acc).flags = ACC_CONTROL | ACC_VIRTKEY;
		++s;
		ch = TOUPPER (s[0]);
	      }
	    (yyval.acc).key = ch;
	    if (s[1] != '\0')
	      rcparse_warning (_("accelerator should only be one character"));
	  }
#line 2051 "rcparse.c" /* yacc.c:1646  */
    break;

  case 24:
#line 272 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.acc).next = NULL;
	    (yyval.acc).flags = 0;
	    (yyval.acc).id = 0;
	    (yyval.acc).key = (yyvsp[0].il);
	  }
#line 2062 "rcparse.c" /* yacc.c:1646  */
    break;

  case 25:
#line 282 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = (yyvsp[0].is);
	  }
#line 2070 "rcparse.c" /* yacc.c:1646  */
    break;

  case 26:
#line 286 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = (yyvsp[-2].is) | (yyvsp[0].is);
	  }
#line 2078 "rcparse.c" /* yacc.c:1646  */
    break;

  case 27:
#line 291 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = (yyvsp[-1].is) | (yyvsp[0].is);
	  }
#line 2086 "rcparse.c" /* yacc.c:1646  */
    break;

  case 28:
#line 298 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = ACC_VIRTKEY;
	  }
#line 2094 "rcparse.c" /* yacc.c:1646  */
    break;

  case 29:
#line 302 "rcparse.y" /* yacc.c:1646  */
    {
	    /* This is just the absence of VIRTKEY.  */
	    (yyval.is) = 0;
	  }
#line 2103 "rcparse.c" /* yacc.c:1646  */
    break;

  case 30:
#line 307 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = ACC_NOINVERT;
	  }
#line 2111 "rcparse.c" /* yacc.c:1646  */
    break;

  case 31:
#line 311 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = ACC_SHIFT;
	  }
#line 2119 "rcparse.c" /* yacc.c:1646  */
    break;

  case 32:
#line 315 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = ACC_CONTROL;
	  }
#line 2127 "rcparse.c" /* yacc.c:1646  */
    break;

  case 33:
#line 319 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = ACC_ALT;
	  }
#line 2135 "rcparse.c" /* yacc.c:1646  */
    break;

  case 34:
#line 328 "rcparse.y" /* yacc.c:1646  */
    {
	    define_bitmap ((yyvsp[-3].id), &(yyvsp[-1].res_info), (yyvsp[0].s));
	    if (yychar != YYEMPTY)
	      YYERROR;
	    rcparse_discard_strings ();
	  }
#line 2146 "rcparse.c" /* yacc.c:1646  */
    break;

  case 35:
#line 340 "rcparse.y" /* yacc.c:1646  */
    {
	    define_cursor ((yyvsp[-3].id), &(yyvsp[-1].res_info), (yyvsp[0].s));
	    if (yychar != YYEMPTY)
	      YYERROR;
	    rcparse_discard_strings ();
	  }
#line 2157 "rcparse.c" /* yacc.c:1646  */
    break;

  case 36:
#line 353 "rcparse.y" /* yacc.c:1646  */
    {
	      memset (&dialog, 0, sizeof dialog);
	      dialog.x = (yyvsp[-3].il);
	      dialog.y = (yyvsp[-2].il);
	      dialog.width = (yyvsp[-1].il);
	      dialog.height = (yyvsp[0].il);
	      dialog.style = WS_POPUP | WS_BORDER | WS_SYSMENU;
	      dialog.exstyle = (yyvsp[-4].il);
	      dialog.menu.named = 1;
	      dialog.class.named = 1;
	      dialog.font = NULL;
	      dialog.ex = NULL;
	      dialog.controls = NULL;
	      sub_res_info = (yyvsp[-5].res_info);
	      style = 0;
	    }
#line 2178 "rcparse.c" /* yacc.c:1646  */
    break;

  case 37:
#line 370 "rcparse.y" /* yacc.c:1646  */
    {
	    define_dialog ((yyvsp[-12].id), &sub_res_info, &dialog);
	    if (yychar != YYEMPTY)
	      YYERROR;
	    rcparse_discard_strings ();
	  }
#line 2189 "rcparse.c" /* yacc.c:1646  */
    break;

  case 38:
#line 378 "rcparse.y" /* yacc.c:1646  */
    {
	      memset (&dialog, 0, sizeof dialog);
	      dialog.x = (yyvsp[-3].il);
	      dialog.y = (yyvsp[-2].il);
	      dialog.width = (yyvsp[-1].il);
	      dialog.height = (yyvsp[0].il);
	      dialog.style = WS_POPUP | WS_BORDER | WS_SYSMENU;
	      dialog.exstyle = (yyvsp[-4].il);
	      dialog.menu.named = 1;
	      dialog.class.named = 1;
	      dialog.font = NULL;
	      dialog.ex = ((rc_dialog_ex *)
			   res_alloc (sizeof (rc_dialog_ex)));
	      memset (dialog.ex, 0, sizeof (rc_dialog_ex));
	      dialog.controls = NULL;
	      sub_res_info = (yyvsp[-5].res_info);
	      style = 0;
	    }
#line 2212 "rcparse.c" /* yacc.c:1646  */
    break;

  case 39:
#line 397 "rcparse.y" /* yacc.c:1646  */
    {
	    define_dialog ((yyvsp[-12].id), &sub_res_info, &dialog);
	    if (yychar != YYEMPTY)
	      YYERROR;
	    rcparse_discard_strings ();
	  }
#line 2223 "rcparse.c" /* yacc.c:1646  */
    break;

  case 40:
#line 405 "rcparse.y" /* yacc.c:1646  */
    {
	      memset (&dialog, 0, sizeof dialog);
	      dialog.x = (yyvsp[-4].il);
	      dialog.y = (yyvsp[-3].il);
	      dialog.width = (yyvsp[-2].il);
	      dialog.height = (yyvsp[-1].il);
	      dialog.style = WS_POPUP | WS_BORDER | WS_SYSMENU;
	      dialog.exstyle = (yyvsp[-5].il);
	      dialog.menu.named = 1;
	      dialog.class.named = 1;
	      dialog.font = NULL;
	      dialog.ex = ((rc_dialog_ex *)
			   res_alloc (sizeof (rc_dialog_ex)));
	      memset (dialog.ex, 0, sizeof (rc_dialog_ex));
	      dialog.ex->help = (yyvsp[0].il);
	      dialog.controls = NULL;
	      sub_res_info = (yyvsp[-6].res_info);
	      style = 0;
	    }
#line 2247 "rcparse.c" /* yacc.c:1646  */
    break;

  case 41:
#line 425 "rcparse.y" /* yacc.c:1646  */
    {
	    define_dialog ((yyvsp[-13].id), &sub_res_info, &dialog);
	    if (yychar != YYEMPTY)
	      YYERROR;
	    rcparse_discard_strings ();
	  }
#line 2258 "rcparse.c" /* yacc.c:1646  */
    break;

  case 42:
#line 435 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.il) = 0;
	  }
#line 2266 "rcparse.c" /* yacc.c:1646  */
    break;

  case 43:
#line 439 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.il) = (yyvsp[0].il);
	  }
#line 2274 "rcparse.c" /* yacc.c:1646  */
    break;

  case 45:
#line 447 "rcparse.y" /* yacc.c:1646  */
    {
	    dialog.style |= WS_CAPTION;
	    style |= WS_CAPTION;
	    dialog.caption = (yyvsp[0].uni);
	  }
#line 2284 "rcparse.c" /* yacc.c:1646  */
    break;

  case 46:
#line 453 "rcparse.y" /* yacc.c:1646  */
    {
	    dialog.class = (yyvsp[0].id);
	  }
#line 2292 "rcparse.c" /* yacc.c:1646  */
    break;

  case 47:
#line 458 "rcparse.y" /* yacc.c:1646  */
    {
	    dialog.style = style;
	  }
#line 2300 "rcparse.c" /* yacc.c:1646  */
    break;

  case 48:
#line 462 "rcparse.y" /* yacc.c:1646  */
    {
	    dialog.exstyle = (yyvsp[0].il);
	  }
#line 2308 "rcparse.c" /* yacc.c:1646  */
    break;

  case 49:
#line 466 "rcparse.y" /* yacc.c:1646  */
    {
	    res_unistring_to_id (& dialog.class, (yyvsp[0].uni));
	  }
#line 2316 "rcparse.c" /* yacc.c:1646  */
    break;

  case 50:
#line 470 "rcparse.y" /* yacc.c:1646  */
    {
	    dialog.style |= DS_SETFONT;
	    style |= DS_SETFONT;
	    dialog.pointsize = (yyvsp[-2].il);
	    dialog.font = (yyvsp[0].uni);
	    if (dialog.ex != NULL)
	      {
		dialog.ex->weight = 0;
		dialog.ex->italic = 0;
		dialog.ex->charset = 1;
	      }
	  }
#line 2333 "rcparse.c" /* yacc.c:1646  */
    break;

  case 51:
#line 483 "rcparse.y" /* yacc.c:1646  */
    {
	    dialog.style |= DS_SETFONT;
	    style |= DS_SETFONT;
	    dialog.pointsize = (yyvsp[-3].il);
	    dialog.font = (yyvsp[-1].uni);
	    if (dialog.ex == NULL)
	      rcparse_warning (_("extended FONT requires DIALOGEX"));
	    else
	      {
		dialog.ex->weight = (yyvsp[0].il);
		dialog.ex->italic = 0;
		dialog.ex->charset = 1;
	      }
	  }
#line 2352 "rcparse.c" /* yacc.c:1646  */
    break;

  case 52:
#line 498 "rcparse.y" /* yacc.c:1646  */
    {
	    dialog.style |= DS_SETFONT;
	    style |= DS_SETFONT;
	    dialog.pointsize = (yyvsp[-4].il);
	    dialog.font = (yyvsp[-2].uni);
	    if (dialog.ex == NULL)
	      rcparse_warning (_("extended FONT requires DIALOGEX"));
	    else
	      {
		dialog.ex->weight = (yyvsp[-1].il);
		dialog.ex->italic = (yyvsp[0].il);
		dialog.ex->charset = 1;
	      }
	  }
#line 2371 "rcparse.c" /* yacc.c:1646  */
    break;

  case 53:
#line 513 "rcparse.y" /* yacc.c:1646  */
    {
	    dialog.style |= DS_SETFONT;
	    style |= DS_SETFONT;
	    dialog.pointsize = (yyvsp[-5].il);
	    dialog.font = (yyvsp[-3].uni);
	    if (dialog.ex == NULL)
	      rcparse_warning (_("extended FONT requires DIALOGEX"));
	    else
	      {
		dialog.ex->weight = (yyvsp[-2].il);
		dialog.ex->italic = (yyvsp[-1].il);
		dialog.ex->charset = (yyvsp[0].il);
	      }
	  }
#line 2390 "rcparse.c" /* yacc.c:1646  */
    break;

  case 54:
#line 528 "rcparse.y" /* yacc.c:1646  */
    {
	    dialog.menu = (yyvsp[0].id);
	  }
#line 2398 "rcparse.c" /* yacc.c:1646  */
    break;

  case 55:
#line 532 "rcparse.y" /* yacc.c:1646  */
    {
	    sub_res_info.characteristics = (yyvsp[0].il);
	  }
#line 2406 "rcparse.c" /* yacc.c:1646  */
    break;

  case 56:
#line 536 "rcparse.y" /* yacc.c:1646  */
    {
	    sub_res_info.language = (yyvsp[-1].il) | ((yyvsp[0].il) << SUBLANG_SHIFT);
	  }
#line 2414 "rcparse.c" /* yacc.c:1646  */
    break;

  case 57:
#line 540 "rcparse.y" /* yacc.c:1646  */
    {
	    sub_res_info.version = (yyvsp[0].il);
	  }
#line 2422 "rcparse.c" /* yacc.c:1646  */
    break;

  case 59:
#line 548 "rcparse.y" /* yacc.c:1646  */
    {
	    rc_dialog_control **pp;

	    for (pp = &dialog.controls; *pp != NULL; pp = &(*pp)->next)
	      ;
	    *pp = (yyvsp[0].dialog_control);
	  }
#line 2434 "rcparse.c" /* yacc.c:1646  */
    break;

  case 60:
#line 559 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = BS_AUTO3STATE | WS_TABSTOP;
	      base_style = BS_AUTO3STATE;
	      class.named = 0;
	      class.u.id = CTL_BUTTON;
	      res_text_field = (yyvsp[0].id);	
	    }
#line 2446 "rcparse.c" /* yacc.c:1646  */
    break;

  case 61:
#line 567 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2454 "rcparse.c" /* yacc.c:1646  */
    break;

  case 62:
#line 571 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = BS_AUTOCHECKBOX | WS_TABSTOP;
	      base_style = BS_AUTOCHECKBOX;
	      class.named = 0;
	      class.u.id = CTL_BUTTON;
	      res_text_field = (yyvsp[0].id);	
	    }
#line 2466 "rcparse.c" /* yacc.c:1646  */
    break;

  case 63:
#line 579 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2474 "rcparse.c" /* yacc.c:1646  */
    break;

  case 64:
#line 583 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = BS_AUTORADIOBUTTON | WS_TABSTOP;
	      base_style = BS_AUTORADIOBUTTON;
	      class.named = 0;
	      class.u.id = CTL_BUTTON;
	      res_text_field = (yyvsp[0].id);	
	    }
#line 2486 "rcparse.c" /* yacc.c:1646  */
    break;

  case 65:
#line 591 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2494 "rcparse.c" /* yacc.c:1646  */
    break;

  case 66:
#line 595 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = ES_LEFT | WS_BORDER | WS_TABSTOP;
	      base_style = ES_LEFT | WS_BORDER | WS_TABSTOP;
	      class.named = 0;
	      class.u.id = CTL_EDIT;
	      res_text_field = (yyvsp[0].id);	
	    }
#line 2506 "rcparse.c" /* yacc.c:1646  */
    break;

  case 67:
#line 603 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	    if (dialog.ex == NULL)
	      rcparse_warning (_("BEDIT requires DIALOGEX"));
	    res_string_to_id (&(yyval.dialog_control)->class, "BEDIT");
	  }
#line 2517 "rcparse.c" /* yacc.c:1646  */
    break;

  case 68:
#line 610 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = BS_CHECKBOX | WS_TABSTOP;
	      base_style = BS_CHECKBOX | WS_TABSTOP;
	      class.named = 0;
	      class.u.id = CTL_BUTTON;
	      res_text_field = (yyvsp[0].id);	
	    }
#line 2529 "rcparse.c" /* yacc.c:1646  */
    break;

  case 69:
#line 618 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2537 "rcparse.c" /* yacc.c:1646  */
    break;

  case 70:
#line 622 "rcparse.y" /* yacc.c:1646  */
    {
	      /* This is as per MSDN documentation.  With some (???)
		 versions of MS rc.exe their is no default style.  */
	      default_style = CBS_SIMPLE | WS_TABSTOP;
	      base_style = 0;
	      class.named = 0;
	      class.u.id = CTL_COMBOBOX;
	      res_text_field = res_null_text;	
	    }
#line 2551 "rcparse.c" /* yacc.c:1646  */
    break;

  case 71:
#line 632 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2559 "rcparse.c" /* yacc.c:1646  */
    break;

  case 72:
#line 637 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = define_control ((yyvsp[-9].id), (yyvsp[-8].il), (yyvsp[-5].il), (yyvsp[-4].il), (yyvsp[-3].il), (yyvsp[-2].il), (yyvsp[-7].id), style, (yyvsp[-1].il));
	    if ((yyvsp[0].rcdata_item) != NULL)
	      {
		if (dialog.ex == NULL)
		  rcparse_warning (_("control data requires DIALOGEX"));
		(yyval.dialog_control)->data = (yyvsp[0].rcdata_item);
	      }
	  }
#line 2573 "rcparse.c" /* yacc.c:1646  */
    break;

  case 73:
#line 648 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = define_control ((yyvsp[-10].id), (yyvsp[-9].il), (yyvsp[-6].il), (yyvsp[-5].il), (yyvsp[-4].il), (yyvsp[-3].il), (yyvsp[-8].id), style, (yyvsp[-2].il));
	    if (dialog.ex == NULL)
	      rcparse_warning (_("help ID requires DIALOGEX"));
	    (yyval.dialog_control)->help = (yyvsp[-1].il);
	    (yyval.dialog_control)->data = (yyvsp[0].rcdata_item);
	  }
#line 2585 "rcparse.c" /* yacc.c:1646  */
    break;

  case 74:
#line 656 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = SS_CENTER | WS_GROUP;
	      base_style = SS_CENTER;
	      class.named = 0;
	      class.u.id = CTL_STATIC;
	      res_text_field = (yyvsp[0].id);	
	    }
#line 2597 "rcparse.c" /* yacc.c:1646  */
    break;

  case 75:
#line 664 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2605 "rcparse.c" /* yacc.c:1646  */
    break;

  case 76:
#line 668 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = BS_DEFPUSHBUTTON | WS_TABSTOP;
	      base_style = BS_DEFPUSHBUTTON | WS_TABSTOP;
	      class.named = 0;
	      class.u.id = CTL_BUTTON;
	      res_text_field = (yyvsp[0].id);	
	    }
#line 2617 "rcparse.c" /* yacc.c:1646  */
    break;

  case 77:
#line 676 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2625 "rcparse.c" /* yacc.c:1646  */
    break;

  case 78:
#line 680 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = ES_LEFT | WS_BORDER | WS_TABSTOP;
	      base_style = ES_LEFT | WS_BORDER | WS_TABSTOP;
	      class.named = 0;
	      class.u.id = CTL_EDIT;
	      res_text_field = res_null_text;	
	    }
#line 2637 "rcparse.c" /* yacc.c:1646  */
    break;

  case 79:
#line 688 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2645 "rcparse.c" /* yacc.c:1646  */
    break;

  case 80:
#line 692 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = BS_GROUPBOX;
	      base_style = BS_GROUPBOX;
	      class.named = 0;
	      class.u.id = CTL_BUTTON;
	      res_text_field = (yyvsp[0].id);	
	    }
#line 2657 "rcparse.c" /* yacc.c:1646  */
    break;

  case 81:
#line 700 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2665 "rcparse.c" /* yacc.c:1646  */
    break;

  case 82:
#line 704 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = ES_LEFT | WS_BORDER | WS_TABSTOP;
	      base_style = ES_LEFT | WS_BORDER | WS_TABSTOP;
	      class.named = 0;
	      class.u.id = CTL_EDIT;
	      res_text_field = (yyvsp[0].id);	
	    }
#line 2677 "rcparse.c" /* yacc.c:1646  */
    break;

  case 83:
#line 712 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	    if (dialog.ex == NULL)
	      rcparse_warning (_("IEDIT requires DIALOGEX"));
	    res_string_to_id (&(yyval.dialog_control)->class, "HEDIT");
	  }
#line 2688 "rcparse.c" /* yacc.c:1646  */
    break;

  case 84:
#line 719 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = define_icon_control ((yyvsp[-4].id), (yyvsp[-3].il), (yyvsp[-2].il), (yyvsp[-1].il), 0, 0, 0, (yyvsp[0].rcdata_item),
				      dialog.ex);
          }
#line 2697 "rcparse.c" /* yacc.c:1646  */
    break;

  case 85:
#line 725 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = define_icon_control ((yyvsp[-6].id), (yyvsp[-5].il), (yyvsp[-4].il), (yyvsp[-3].il), 0, 0, 0, (yyvsp[0].rcdata_item),
				      dialog.ex);
          }
#line 2706 "rcparse.c" /* yacc.c:1646  */
    break;

  case 86:
#line 731 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = define_icon_control ((yyvsp[-8].id), (yyvsp[-7].il), (yyvsp[-6].il), (yyvsp[-5].il), style, (yyvsp[-1].il), 0, (yyvsp[0].rcdata_item),
				      dialog.ex);
          }
#line 2715 "rcparse.c" /* yacc.c:1646  */
    break;

  case 87:
#line 737 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = define_icon_control ((yyvsp[-9].id), (yyvsp[-8].il), (yyvsp[-7].il), (yyvsp[-6].il), style, (yyvsp[-2].il), (yyvsp[-1].il), (yyvsp[0].rcdata_item),
				      dialog.ex);
          }
#line 2724 "rcparse.c" /* yacc.c:1646  */
    break;

  case 88:
#line 742 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = ES_LEFT | WS_BORDER | WS_TABSTOP;
	      base_style = ES_LEFT | WS_BORDER | WS_TABSTOP;
	      class.named = 0;
	      class.u.id = CTL_EDIT;
	      res_text_field = (yyvsp[0].id);	
	    }
#line 2736 "rcparse.c" /* yacc.c:1646  */
    break;

  case 89:
#line 750 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	    if (dialog.ex == NULL)
	      rcparse_warning (_("IEDIT requires DIALOGEX"));
	    res_string_to_id (&(yyval.dialog_control)->class, "IEDIT");
	  }
#line 2747 "rcparse.c" /* yacc.c:1646  */
    break;

  case 90:
#line 757 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = LBS_NOTIFY | WS_BORDER;
	      base_style = LBS_NOTIFY | WS_BORDER;
	      class.named = 0;
	      class.u.id = CTL_LISTBOX;
	      res_text_field = res_null_text;	
	    }
#line 2759 "rcparse.c" /* yacc.c:1646  */
    break;

  case 91:
#line 765 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2767 "rcparse.c" /* yacc.c:1646  */
    break;

  case 92:
#line 769 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = SS_LEFT | WS_GROUP;
	      base_style = SS_LEFT;
	      class.named = 0;
	      class.u.id = CTL_STATIC;
	      res_text_field = (yyvsp[0].id);	
	    }
#line 2779 "rcparse.c" /* yacc.c:1646  */
    break;

  case 93:
#line 777 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2787 "rcparse.c" /* yacc.c:1646  */
    break;

  case 94:
#line 781 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = BS_PUSHBOX | WS_TABSTOP;
	      base_style = BS_PUSHBOX;
	      class.named = 0;
	      class.u.id = CTL_BUTTON;
	    }
#line 2798 "rcparse.c" /* yacc.c:1646  */
    break;

  case 95:
#line 788 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2806 "rcparse.c" /* yacc.c:1646  */
    break;

  case 96:
#line 792 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = BS_PUSHBUTTON | WS_TABSTOP;
	      base_style = BS_PUSHBUTTON | WS_TABSTOP;
	      class.named = 0;
	      class.u.id = CTL_BUTTON;
	      res_text_field = (yyvsp[0].id);	
	    }
#line 2818 "rcparse.c" /* yacc.c:1646  */
    break;

  case 97:
#line 800 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2826 "rcparse.c" /* yacc.c:1646  */
    break;

  case 98:
#line 804 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = BS_RADIOBUTTON | WS_TABSTOP;
	      base_style = BS_RADIOBUTTON;
	      class.named = 0;
	      class.u.id = CTL_BUTTON;
	      res_text_field = (yyvsp[0].id);	
	    }
#line 2838 "rcparse.c" /* yacc.c:1646  */
    break;

  case 99:
#line 812 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2846 "rcparse.c" /* yacc.c:1646  */
    break;

  case 100:
#line 816 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = SS_RIGHT | WS_GROUP;
	      base_style = SS_RIGHT;
	      class.named = 0;
	      class.u.id = CTL_STATIC;
	      res_text_field = (yyvsp[0].id);	
	    }
#line 2858 "rcparse.c" /* yacc.c:1646  */
    break;

  case 101:
#line 824 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2866 "rcparse.c" /* yacc.c:1646  */
    break;

  case 102:
#line 828 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = SBS_HORZ;
	      base_style = 0;
	      class.named = 0;
	      class.u.id = CTL_SCROLLBAR;
	      res_text_field = res_null_text;	
	    }
#line 2878 "rcparse.c" /* yacc.c:1646  */
    break;

  case 103:
#line 836 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2886 "rcparse.c" /* yacc.c:1646  */
    break;

  case 104:
#line 840 "rcparse.y" /* yacc.c:1646  */
    {
	      default_style = BS_3STATE | WS_TABSTOP;
	      base_style = BS_3STATE;
	      class.named = 0;
	      class.u.id = CTL_BUTTON;
	      res_text_field = (yyvsp[0].id);	
	    }
#line 2898 "rcparse.c" /* yacc.c:1646  */
    break;

  case 105:
#line 848 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = (yyvsp[0].dialog_control);
	  }
#line 2906 "rcparse.c" /* yacc.c:1646  */
    break;

  case 106:
#line 853 "rcparse.y" /* yacc.c:1646  */
    { style = WS_CHILD | WS_VISIBLE; }
#line 2912 "rcparse.c" /* yacc.c:1646  */
    break;

  case 107:
#line 855 "rcparse.y" /* yacc.c:1646  */
    {
	    rc_res_id cid;
	    cid.named = 0;
	    cid.u.id = CTL_BUTTON;
	    (yyval.dialog_control) = define_control ((yyvsp[-13].id), (yyvsp[-12].il), (yyvsp[-10].il), (yyvsp[-8].il), (yyvsp[-6].il), (yyvsp[-4].il), cid,
				 style, (yyvsp[0].il));
	  }
#line 2924 "rcparse.c" /* yacc.c:1646  */
    break;

  case 108:
#line 873 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = define_control (res_text_field, (yyvsp[-5].il), (yyvsp[-4].il), (yyvsp[-3].il), (yyvsp[-2].il), (yyvsp[-1].il), class,
				 default_style | WS_CHILD | WS_VISIBLE, 0);
	    if ((yyvsp[0].rcdata_item) != NULL)
	      {
		if (dialog.ex == NULL)
		  rcparse_warning (_("control data requires DIALOGEX"));
		(yyval.dialog_control)->data = (yyvsp[0].rcdata_item);
	      }
	  }
#line 2939 "rcparse.c" /* yacc.c:1646  */
    break;

  case 109:
#line 885 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = define_control (res_text_field, (yyvsp[-7].il), (yyvsp[-6].il), (yyvsp[-5].il), (yyvsp[-4].il), (yyvsp[-3].il), class, style, (yyvsp[-1].il));
	    if ((yyvsp[0].rcdata_item) != NULL)
	      {
		if (dialog.ex == NULL)
		  rcparse_warning (_("control data requires DIALOGEX"));
		(yyval.dialog_control)->data = (yyvsp[0].rcdata_item);
	      }
	  }
#line 2953 "rcparse.c" /* yacc.c:1646  */
    break;

  case 110:
#line 896 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.dialog_control) = define_control (res_text_field, (yyvsp[-8].il), (yyvsp[-7].il), (yyvsp[-6].il), (yyvsp[-5].il), (yyvsp[-4].il), class, style, (yyvsp[-2].il));
	    if (dialog.ex == NULL)
	      rcparse_warning (_("help ID requires DIALOGEX"));
	    (yyval.dialog_control)->help = (yyvsp[-1].il);
	    (yyval.dialog_control)->data = (yyvsp[0].rcdata_item);
	  }
#line 2965 "rcparse.c" /* yacc.c:1646  */
    break;

  case 111:
#line 907 "rcparse.y" /* yacc.c:1646  */
    {
	    if ((yyvsp[0].id).named)
	      res_unistring_to_id (&(yyval.id), (yyvsp[0].id).u.n.name);
	    else
	      (yyval.id)=(yyvsp[0].id);
	  }
#line 2976 "rcparse.c" /* yacc.c:1646  */
    break;

  case 112:
#line 917 "rcparse.y" /* yacc.c:1646  */
    {
	    res_string_to_id (&(yyval.id), "");
	  }
#line 2984 "rcparse.c" /* yacc.c:1646  */
    break;

  case 113:
#line 920 "rcparse.y" /* yacc.c:1646  */
    { (yyval.id)=(yyvsp[-1].id); }
#line 2990 "rcparse.c" /* yacc.c:1646  */
    break;

  case 114:
#line 925 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.id).named = 0;
	    (yyval.id).u.id = (yyvsp[0].il);
	  }
#line 2999 "rcparse.c" /* yacc.c:1646  */
    break;

  case 115:
#line 930 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.id).named = 1;
	    (yyval.id).u.n.name = (yyvsp[0].uni);
	    (yyval.id).u.n.length = unichar_len ((yyvsp[0].uni));
	  }
#line 3009 "rcparse.c" /* yacc.c:1646  */
    break;

  case 116:
#line 939 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.rcdata_item) = NULL;
	  }
#line 3017 "rcparse.c" /* yacc.c:1646  */
    break;

  case 117:
#line 943 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.rcdata_item) = (yyvsp[-1].rcdata).first;
	  }
#line 3025 "rcparse.c" /* yacc.c:1646  */
    break;

  case 118:
#line 952 "rcparse.y" /* yacc.c:1646  */
    { style = WS_CHILD | WS_VISIBLE; }
#line 3031 "rcparse.c" /* yacc.c:1646  */
    break;

  case 120:
#line 958 "rcparse.y" /* yacc.c:1646  */
    { style = SS_ICON | WS_CHILD | WS_VISIBLE; }
#line 3037 "rcparse.c" /* yacc.c:1646  */
    break;

  case 122:
#line 964 "rcparse.y" /* yacc.c:1646  */
    { style = base_style | WS_CHILD | WS_VISIBLE; }
#line 3043 "rcparse.c" /* yacc.c:1646  */
    break;

  case 124:
#line 972 "rcparse.y" /* yacc.c:1646  */
    {
	    define_font ((yyvsp[-3].id), &(yyvsp[-1].res_info), (yyvsp[0].s));
	    if (yychar != YYEMPTY)
	      YYERROR;
	    rcparse_discard_strings ();
	  }
#line 3054 "rcparse.c" /* yacc.c:1646  */
    break;

  case 125:
#line 984 "rcparse.y" /* yacc.c:1646  */
    {
	    define_icon ((yyvsp[-3].id), &(yyvsp[-1].res_info), (yyvsp[0].s));
	    if (yychar != YYEMPTY)
	      YYERROR;
	    rcparse_discard_strings ();
	  }
#line 3065 "rcparse.c" /* yacc.c:1646  */
    break;

  case 126:
#line 997 "rcparse.y" /* yacc.c:1646  */
    {
	    language = (yyvsp[-1].il) | ((yyvsp[0].il) << SUBLANG_SHIFT);
	  }
#line 3073 "rcparse.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1006 "rcparse.y" /* yacc.c:1646  */
    {
	    define_menu ((yyvsp[-5].id), &(yyvsp[-3].res_info), (yyvsp[-1].menuitem));
	    if (yychar != YYEMPTY)
	      YYERROR;
	    rcparse_discard_strings ();
	  }
#line 3084 "rcparse.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1016 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.menuitem) = NULL;
	  }
#line 3092 "rcparse.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1020 "rcparse.y" /* yacc.c:1646  */
    {
	    if ((yyvsp[-1].menuitem) == NULL)
	      (yyval.menuitem) = (yyvsp[0].menuitem);
	    else
	      {
		rc_menuitem **pp;

		for (pp = &(yyvsp[-1].menuitem)->next; *pp != NULL; pp = &(*pp)->next)
		  ;
		*pp = (yyvsp[0].menuitem);
		(yyval.menuitem) = (yyvsp[-1].menuitem);
	      }
	  }
#line 3110 "rcparse.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1037 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.menuitem) = define_menuitem ((yyvsp[-2].uni), (yyvsp[-1].il), (yyvsp[0].is), 0, 0, NULL);
	  }
#line 3118 "rcparse.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1041 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.menuitem) = define_menuitem (NULL, 0, 0, 0, 0, NULL);
	  }
#line 3126 "rcparse.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1045 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.menuitem) = define_menuitem ((yyvsp[-4].uni), 0, (yyvsp[-3].is), 0, 0, (yyvsp[-1].menuitem));
	  }
#line 3134 "rcparse.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1052 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = 0;
	  }
#line 3142 "rcparse.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1056 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = (yyvsp[-2].is) | (yyvsp[0].is);
	  }
#line 3150 "rcparse.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1060 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = (yyvsp[-1].is) | (yyvsp[0].is);
	  }
#line 3158 "rcparse.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1067 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = MENUITEM_CHECKED;
	  }
#line 3166 "rcparse.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1071 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = MENUITEM_GRAYED;
	  }
#line 3174 "rcparse.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1075 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = MENUITEM_HELP;
	  }
#line 3182 "rcparse.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1079 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = MENUITEM_INACTIVE;
	  }
#line 3190 "rcparse.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1083 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = MENUITEM_MENUBARBREAK;
	  }
#line 3198 "rcparse.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1087 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.is) = MENUITEM_MENUBREAK;
	  }
#line 3206 "rcparse.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1096 "rcparse.y" /* yacc.c:1646  */
    {
	    define_menu ((yyvsp[-5].id), &(yyvsp[-3].res_info), (yyvsp[-1].menuitem));
	    if (yychar != YYEMPTY)
	      YYERROR;
	    rcparse_discard_strings ();
	  }
#line 3217 "rcparse.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1106 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.menuitem) = NULL;
	  }
#line 3225 "rcparse.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1110 "rcparse.y" /* yacc.c:1646  */
    {
	    if ((yyvsp[-1].menuitem) == NULL)
	      (yyval.menuitem) = (yyvsp[0].menuitem);
	    else
	      {
		rc_menuitem **pp;

		for (pp = &(yyvsp[-1].menuitem)->next; *pp != NULL; pp = &(*pp)->next)
		  ;
		*pp = (yyvsp[0].menuitem);
		(yyval.menuitem) = (yyvsp[-1].menuitem);
	      }
	  }
#line 3243 "rcparse.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1127 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.menuitem) = define_menuitem ((yyvsp[0].uni), 0, 0, 0, 0, NULL);
	  }
#line 3251 "rcparse.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1131 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.menuitem) = define_menuitem ((yyvsp[-1].uni), (yyvsp[0].il), 0, 0, 0, NULL);
	  }
#line 3259 "rcparse.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1135 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.menuitem) = define_menuitem ((yyvsp[-3].uni), (yyvsp[-2].il), (yyvsp[-1].il), (yyvsp[0].il), 0, NULL);
	  }
#line 3267 "rcparse.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1139 "rcparse.y" /* yacc.c:1646  */
    {
 	    (yyval.menuitem) = define_menuitem (NULL, 0, 0, 0, 0, NULL);
 	  }
#line 3275 "rcparse.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1143 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.menuitem) = define_menuitem ((yyvsp[-3].uni), 0, 0, 0, 0, (yyvsp[-1].menuitem));
	  }
#line 3283 "rcparse.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1147 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.menuitem) = define_menuitem ((yyvsp[-4].uni), (yyvsp[-3].il), 0, 0, 0, (yyvsp[-1].menuitem));
	  }
#line 3291 "rcparse.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1151 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.menuitem) = define_menuitem ((yyvsp[-5].uni), (yyvsp[-4].il), (yyvsp[-3].il), 0, 0, (yyvsp[-1].menuitem));
	  }
#line 3299 "rcparse.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1156 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.menuitem) = define_menuitem ((yyvsp[-7].uni), (yyvsp[-6].il), (yyvsp[-5].il), (yyvsp[-4].il), (yyvsp[-3].il), (yyvsp[-1].menuitem));
	  }
#line 3307 "rcparse.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1165 "rcparse.y" /* yacc.c:1646  */
    {
	    define_messagetable ((yyvsp[-3].id), &(yyvsp[-1].res_info), (yyvsp[0].s));
	    if (yychar != YYEMPTY)
	      YYERROR;
	    rcparse_discard_strings ();
	  }
#line 3318 "rcparse.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1177 "rcparse.y" /* yacc.c:1646  */
    {
	    rcparse_rcdata ();
	  }
#line 3326 "rcparse.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1181 "rcparse.y" /* yacc.c:1646  */
    {
	    rcparse_normal ();
	    (yyval.rcdata) = (yyvsp[0].rcdata);
	  }
#line 3335 "rcparse.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1189 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.rcdata).first = NULL;
	    (yyval.rcdata).last = NULL;
	  }
#line 3344 "rcparse.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1194 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.rcdata) = (yyvsp[0].rcdata);
	  }
#line 3352 "rcparse.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1201 "rcparse.y" /* yacc.c:1646  */
    {
	    rc_rcdata_item *ri;

	    ri = define_rcdata_string ((yyvsp[0].ss).s, (yyvsp[0].ss).length);
	    (yyval.rcdata).first = ri;
	    (yyval.rcdata).last = ri;
	  }
#line 3364 "rcparse.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1209 "rcparse.y" /* yacc.c:1646  */
    {
	    rc_rcdata_item *ri;

	    ri = define_rcdata_unistring ((yyvsp[0].suni).s, (yyvsp[0].suni).length);
	    (yyval.rcdata).first = ri;
	    (yyval.rcdata).last = ri;
	  }
#line 3376 "rcparse.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1217 "rcparse.y" /* yacc.c:1646  */
    {
	    rc_rcdata_item *ri;

	    ri = define_rcdata_number ((yyvsp[0].i).val, (yyvsp[0].i).dword);
	    (yyval.rcdata).first = ri;
	    (yyval.rcdata).last = ri;
	  }
#line 3388 "rcparse.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1225 "rcparse.y" /* yacc.c:1646  */
    {
	    rc_rcdata_item *ri;

	    ri = define_rcdata_string ((yyvsp[0].ss).s, (yyvsp[0].ss).length);
	    (yyval.rcdata).first = (yyvsp[-2].rcdata).first;
	    (yyvsp[-2].rcdata).last->next = ri;
	    (yyval.rcdata).last = ri;
	  }
#line 3401 "rcparse.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1234 "rcparse.y" /* yacc.c:1646  */
    {
	    rc_rcdata_item *ri;

	    ri = define_rcdata_unistring ((yyvsp[0].suni).s, (yyvsp[0].suni).length);
	    (yyval.rcdata).first = (yyvsp[-2].rcdata).first;
	    (yyvsp[-2].rcdata).last->next = ri;
	    (yyval.rcdata).last = ri;
	  }
#line 3414 "rcparse.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1243 "rcparse.y" /* yacc.c:1646  */
    {
	    rc_rcdata_item *ri;

	    ri = define_rcdata_number ((yyvsp[0].i).val, (yyvsp[0].i).dword);
	    (yyval.rcdata).first = (yyvsp[-2].rcdata).first;
	    (yyvsp[-2].rcdata).last->next = ri;
	    (yyval.rcdata).last = ri;
	  }
#line 3427 "rcparse.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1252 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.rcdata)=(yyvsp[-1].rcdata);
	  }
#line 3435 "rcparse.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1261 "rcparse.y" /* yacc.c:1646  */
    { sub_res_info = (yyvsp[-1].res_info); }
#line 3441 "rcparse.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1268 "rcparse.y" /* yacc.c:1646  */
    {
	    define_stringtable (&sub_res_info, (yyvsp[-1].il), (yyvsp[0].uni));
	    rcparse_discard_strings ();
	  }
#line 3450 "rcparse.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1273 "rcparse.y" /* yacc.c:1646  */
    {
	    define_stringtable (&sub_res_info, (yyvsp[-2].il), (yyvsp[0].uni));
	    rcparse_discard_strings ();
	  }
#line 3459 "rcparse.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1278 "rcparse.y" /* yacc.c:1646  */
    {
	    rcparse_warning (_("invalid stringtable resource."));
	    abort ();
	  }
#line 3468 "rcparse.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1286 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.id)=(yyvsp[0].id);
	  }
#line 3476 "rcparse.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1290 "rcparse.y" /* yacc.c:1646  */
    {
	  (yyval.id).named = 0;
	  (yyval.id).u.id = 23;
	}
#line 3485 "rcparse.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1295 "rcparse.y" /* yacc.c:1646  */
    {
          (yyval.id).named = 0;
          (yyval.id).u.id = RT_RCDATA;
        }
#line 3494 "rcparse.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1300 "rcparse.y" /* yacc.c:1646  */
    {
          (yyval.id).named = 0;
          (yyval.id).u.id = RT_MANIFEST;
        }
#line 3503 "rcparse.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1305 "rcparse.y" /* yacc.c:1646  */
    {
          (yyval.id).named = 0;
          (yyval.id).u.id = RT_PLUGPLAY;
        }
#line 3512 "rcparse.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1310 "rcparse.y" /* yacc.c:1646  */
    {
          (yyval.id).named = 0;
          (yyval.id).u.id = RT_VXD;
        }
#line 3521 "rcparse.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1315 "rcparse.y" /* yacc.c:1646  */
    {
          (yyval.id).named = 0;
          (yyval.id).u.id = RT_DLGINCLUDE;
        }
#line 3530 "rcparse.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1320 "rcparse.y" /* yacc.c:1646  */
    {
          (yyval.id).named = 0;
          (yyval.id).u.id = RT_DLGINIT;
        }
#line 3539 "rcparse.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1325 "rcparse.y" /* yacc.c:1646  */
    {
          (yyval.id).named = 0;
          (yyval.id).u.id = RT_ANICURSOR;
        }
#line 3548 "rcparse.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1330 "rcparse.y" /* yacc.c:1646  */
    {
          (yyval.id).named = 0;
          (yyval.id).u.id = RT_ANIICON;
        }
#line 3557 "rcparse.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1341 "rcparse.y" /* yacc.c:1646  */
    {
	    define_user_data ((yyvsp[-5].id), (yyvsp[-4].id), &(yyvsp[-3].res_info), (yyvsp[-1].rcdata).first);
	    if (yychar != YYEMPTY)
	      YYERROR;
	    rcparse_discard_strings ();
	  }
#line 3568 "rcparse.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1348 "rcparse.y" /* yacc.c:1646  */
    {
	    define_user_file ((yyvsp[-3].id), (yyvsp[-2].id), &(yyvsp[-1].res_info), (yyvsp[0].s));
	    if (yychar != YYEMPTY)
	      YYERROR;
	    rcparse_discard_strings ();
	  }
#line 3579 "rcparse.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1358 "rcparse.y" /* yacc.c:1646  */
    {
	  define_toolbar ((yyvsp[-7].id), &(yyvsp[-5].res_info), (yyvsp[-4].il), (yyvsp[-3].il), (yyvsp[-1].toobar_item));
	}
#line 3587 "rcparse.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1363 "rcparse.y" /* yacc.c:1646  */
    { (yyval.toobar_item)= NULL; }
#line 3593 "rcparse.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1365 "rcparse.y" /* yacc.c:1646  */
    {
	  rc_toolbar_item *c,*n;
	  c = (yyvsp[-2].toobar_item);
	  n= (rc_toolbar_item *)
	      res_alloc (sizeof (rc_toolbar_item));
	  if (c != NULL)
	    while (c->next != NULL)
	      c = c->next;
	  n->prev = c;
	  n->next = NULL;
	  if (c != NULL)
	    c->next = n;
	  n->id = (yyvsp[0].id);
	  if ((yyvsp[-2].toobar_item) == NULL)
	    (yyval.toobar_item) = n;
	  else
	    (yyval.toobar_item) = (yyvsp[-2].toobar_item);
	}
#line 3616 "rcparse.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1384 "rcparse.y" /* yacc.c:1646  */
    {
	  rc_toolbar_item *c,*n;
	  c = (yyvsp[-1].toobar_item);
	  n= (rc_toolbar_item *)
	      res_alloc (sizeof (rc_toolbar_item));
	  if (c != NULL)
	    while (c->next != NULL)
	      c = c->next;
	  n->prev = c;
	  n->next = NULL;
	  if (c != NULL)
	    c->next = n;
	  n->id.named = 0;
	  n->id.u.id = 0;
	  if ((yyvsp[-1].toobar_item) == NULL)
	    (yyval.toobar_item) = n;
	  else
	    (yyval.toobar_item) = (yyvsp[-1].toobar_item);
	}
#line 3640 "rcparse.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1409 "rcparse.y" /* yacc.c:1646  */
    {
	    define_versioninfo ((yyvsp[-5].id), language, (yyvsp[-3].fixver), (yyvsp[-1].verinfo));
	    if (yychar != YYEMPTY)
	      YYERROR;
	    rcparse_discard_strings ();
	  }
#line 3651 "rcparse.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1419 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.fixver) = ((rc_fixed_versioninfo *)
		  res_alloc (sizeof (rc_fixed_versioninfo)));
	    memset ((yyval.fixver), 0, sizeof (rc_fixed_versioninfo));
	  }
#line 3661 "rcparse.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1425 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyvsp[-5].fixver)->file_version_ms = ((yyvsp[-3].il) << 16) | (yyvsp[-2].il);
	    (yyvsp[-5].fixver)->file_version_ls = ((yyvsp[-1].il) << 16) | (yyvsp[0].il);
	    (yyval.fixver) = (yyvsp[-5].fixver);
	  }
#line 3671 "rcparse.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1431 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyvsp[-5].fixver)->product_version_ms = ((yyvsp[-3].il) << 16) | (yyvsp[-2].il);
	    (yyvsp[-5].fixver)->product_version_ls = ((yyvsp[-1].il) << 16) | (yyvsp[0].il);
	    (yyval.fixver) = (yyvsp[-5].fixver);
	  }
#line 3681 "rcparse.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1437 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyvsp[-2].fixver)->file_flags_mask = (yyvsp[0].il);
	    (yyval.fixver) = (yyvsp[-2].fixver);
	  }
#line 3690 "rcparse.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1442 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyvsp[-2].fixver)->file_flags = (yyvsp[0].il);
	    (yyval.fixver) = (yyvsp[-2].fixver);
	  }
#line 3699 "rcparse.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1447 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyvsp[-2].fixver)->file_os = (yyvsp[0].il);
	    (yyval.fixver) = (yyvsp[-2].fixver);
	  }
#line 3708 "rcparse.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1452 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyvsp[-2].fixver)->file_type = (yyvsp[0].il);
	    (yyval.fixver) = (yyvsp[-2].fixver);
	  }
#line 3717 "rcparse.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1457 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyvsp[-2].fixver)->file_subtype = (yyvsp[0].il);
	    (yyval.fixver) = (yyvsp[-2].fixver);
	  }
#line 3726 "rcparse.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1471 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.verinfo) = NULL;
	  }
#line 3734 "rcparse.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1475 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.verinfo) = append_ver_stringfileinfo ((yyvsp[-7].verinfo), (yyvsp[-4].s), (yyvsp[-2].verstring));
	  }
#line 3742 "rcparse.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1479 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.verinfo) = append_ver_varfileinfo ((yyvsp[-6].verinfo), (yyvsp[-2].uni), (yyvsp[-1].vervar));
	  }
#line 3750 "rcparse.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1486 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.verstring) = NULL;
	  }
#line 3758 "rcparse.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1490 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.verstring) = append_verval ((yyvsp[-4].verstring), (yyvsp[-2].uni), (yyvsp[0].uni));
	  }
#line 3766 "rcparse.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1497 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.vervar) = NULL;
	  }
#line 3774 "rcparse.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1501 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.vervar) = append_vertrans ((yyvsp[-2].vervar), (yyvsp[-1].il), (yyvsp[0].il));
	  }
#line 3782 "rcparse.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1510 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.id).named = 0;
	    (yyval.id).u.id = (yyvsp[0].il);
	  }
#line 3791 "rcparse.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1515 "rcparse.y" /* yacc.c:1646  */
    {
	    res_unistring_to_id (&(yyval.id), (yyvsp[0].uni));
	  }
#line 3799 "rcparse.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1524 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.uni) = (yyvsp[0].uni);
	  }
#line 3807 "rcparse.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1528 "rcparse.y" /* yacc.c:1646  */
    {
	    unichar *h = NULL;
	    unicode_from_ascii ((rc_uint_type *) NULL, &h, (yyvsp[0].s));
	    (yyval.uni) = h;
	  }
#line 3817 "rcparse.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1538 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.id).named = 0;
	    (yyval.id).u.id = (yyvsp[-1].il);
	  }
#line 3826 "rcparse.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1543 "rcparse.y" /* yacc.c:1646  */
    {
	    res_unistring_to_id (&(yyval.id), (yyvsp[0].uni));
	  }
#line 3834 "rcparse.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1547 "rcparse.y" /* yacc.c:1646  */
    {
	    res_unistring_to_id (&(yyval.id), (yyvsp[-1].uni));
	  }
#line 3842 "rcparse.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1557 "rcparse.y" /* yacc.c:1646  */
    {
	    memset (&(yyval.res_info), 0, sizeof (rc_res_res_info));
	    (yyval.res_info).language = language;
	    /* FIXME: Is this the right default?  */
	    (yyval.res_info).memflags = MEMFLAG_MOVEABLE | MEMFLAG_PURE | MEMFLAG_DISCARDABLE;
	  }
#line 3853 "rcparse.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1564 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.res_info) = (yyvsp[-1].res_info);
	    (yyval.res_info).memflags |= (yyvsp[0].memflags).on;
	    (yyval.res_info).memflags &=~ (yyvsp[0].memflags).off;
	  }
#line 3863 "rcparse.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1570 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.res_info) = (yyvsp[-2].res_info);
	    (yyval.res_info).characteristics = (yyvsp[0].il);
	  }
#line 3872 "rcparse.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1575 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.res_info) = (yyvsp[-3].res_info);
	    (yyval.res_info).language = (yyvsp[-1].il) | ((yyvsp[0].il) << SUBLANG_SHIFT);
	  }
#line 3881 "rcparse.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1580 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.res_info) = (yyvsp[-2].res_info);
	    (yyval.res_info).version = (yyvsp[0].il);
	  }
#line 3890 "rcparse.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1590 "rcparse.y" /* yacc.c:1646  */
    {
	    memset (&(yyval.res_info), 0, sizeof (rc_res_res_info));
	    (yyval.res_info).language = language;
	    (yyval.res_info).memflags = MEMFLAG_MOVEABLE | MEMFLAG_DISCARDABLE;
	  }
#line 3900 "rcparse.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1596 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.res_info) = (yyvsp[-1].res_info);
	    (yyval.res_info).memflags |= (yyvsp[0].memflags).on;
	    (yyval.res_info).memflags &=~ (yyvsp[0].memflags).off;
	  }
#line 3910 "rcparse.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1607 "rcparse.y" /* yacc.c:1646  */
    {
	    memset (&(yyval.res_info), 0, sizeof (rc_res_res_info));
	    (yyval.res_info).language = language;
	    (yyval.res_info).memflags = MEMFLAG_MOVEABLE | MEMFLAG_PURE | MEMFLAG_DISCARDABLE;
	  }
#line 3920 "rcparse.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1613 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.res_info) = (yyvsp[-1].res_info);
	    (yyval.res_info).memflags |= (yyvsp[0].memflags).on;
	    (yyval.res_info).memflags &=~ (yyvsp[0].memflags).off;
	  }
#line 3930 "rcparse.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1625 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.memflags).on = MEMFLAG_MOVEABLE;
	    (yyval.memflags).off = 0;
	  }
#line 3939 "rcparse.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1630 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.memflags).on = 0;
	    (yyval.memflags).off = MEMFLAG_MOVEABLE;
	  }
#line 3948 "rcparse.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1635 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.memflags).on = MEMFLAG_PURE;
	    (yyval.memflags).off = 0;
	  }
#line 3957 "rcparse.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1640 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.memflags).on = 0;
	    (yyval.memflags).off = MEMFLAG_PURE;
	  }
#line 3966 "rcparse.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1645 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.memflags).on = MEMFLAG_PRELOAD;
	    (yyval.memflags).off = 0;
	  }
#line 3975 "rcparse.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1650 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.memflags).on = 0;
	    (yyval.memflags).off = MEMFLAG_PRELOAD;
	  }
#line 3984 "rcparse.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1655 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.memflags).on = MEMFLAG_DISCARDABLE;
	    (yyval.memflags).off = 0;
	  }
#line 3993 "rcparse.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1665 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.s) = (yyvsp[0].s);
	  }
#line 4001 "rcparse.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1669 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.s) = (yyvsp[0].s);
	  }
#line 4009 "rcparse.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1677 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.uni) = (yyvsp[0].uni);
	  }
#line 4017 "rcparse.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1682 "rcparse.y" /* yacc.c:1646  */
    {
	    rc_uint_type l1 = unichar_len ((yyvsp[-1].uni));
	    rc_uint_type l2 = unichar_len ((yyvsp[0].uni));
	    unichar *h = (unichar *) res_alloc ((l1 + l2 + 1) * sizeof (unichar));
	    if (l1 != 0)
	      memcpy (h, (yyvsp[-1].uni), l1 * sizeof (unichar));
	    if (l2 != 0)
	      memcpy (h + l1, (yyvsp[0].uni), l2  * sizeof (unichar));
	    h[l1 + l2] = 0;
	    (yyval.uni) = h;
	  }
#line 4033 "rcparse.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1697 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.uni) = unichar_dup ((yyvsp[0].uni));
	  }
#line 4041 "rcparse.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1701 "rcparse.y" /* yacc.c:1646  */
    {
	    unichar *h = NULL;
	    unicode_from_ascii ((rc_uint_type *) NULL, &h, (yyvsp[0].s));
	    (yyval.uni) = h;
	  }
#line 4051 "rcparse.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1710 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.ss) = (yyvsp[0].ss);
	  }
#line 4059 "rcparse.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1714 "rcparse.y" /* yacc.c:1646  */
    {
	    rc_uint_type l = (yyvsp[-1].ss).length + (yyvsp[0].ss).length;
	    char *h = (char *) res_alloc (l);
	    memcpy (h, (yyvsp[-1].ss).s, (yyvsp[-1].ss).length);
	    memcpy (h + (yyvsp[-1].ss).length, (yyvsp[0].ss).s, (yyvsp[0].ss).length);
	    (yyval.ss).s = h;
	    (yyval.ss).length = l;
	  }
#line 4072 "rcparse.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1726 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.suni) = (yyvsp[0].suni);
	  }
#line 4080 "rcparse.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1730 "rcparse.y" /* yacc.c:1646  */
    {
	    rc_uint_type l = (yyvsp[-1].suni).length + (yyvsp[0].suni).length;
	    unichar *h = (unichar *) res_alloc (l * sizeof (unichar));
	    memcpy (h, (yyvsp[-1].suni).s, (yyvsp[-1].suni).length * sizeof (unichar));
	    memcpy (h + (yyvsp[-1].suni).length, (yyvsp[0].suni).s, (yyvsp[0].suni).length  * sizeof (unichar));
	    (yyval.suni).s = h;
	    (yyval.suni).length = l;
	  }
#line 4093 "rcparse.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1752 "rcparse.y" /* yacc.c:1646  */
    {
	    style |= (yyvsp[0].il);
	  }
#line 4101 "rcparse.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1756 "rcparse.y" /* yacc.c:1646  */
    {
	    style &=~ (yyvsp[0].il);
	  }
#line 4109 "rcparse.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1760 "rcparse.y" /* yacc.c:1646  */
    {
	    style |= (yyvsp[0].il);
	  }
#line 4117 "rcparse.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1764 "rcparse.y" /* yacc.c:1646  */
    {
	    style &=~ (yyvsp[0].il);
	  }
#line 4125 "rcparse.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1771 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.il) = (yyvsp[0].i).val;
	  }
#line 4133 "rcparse.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1775 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.il) = (yyvsp[-1].il);
	  }
#line 4141 "rcparse.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1784 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.il) = 0;
	  }
#line 4149 "rcparse.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1788 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.il) = (yyvsp[0].il);
	  }
#line 4157 "rcparse.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1797 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.il) = (yyvsp[0].il);
	  }
#line 4165 "rcparse.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1806 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.il) = (yyvsp[0].i).val;
	  }
#line 4173 "rcparse.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1815 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i) = (yyvsp[0].i);
	  }
#line 4181 "rcparse.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1819 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i) = (yyvsp[-1].i);
	  }
#line 4189 "rcparse.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1823 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = ~ (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[0].i).dword;
	  }
#line 4198 "rcparse.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1828 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = - (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[0].i).dword;
	  }
#line 4207 "rcparse.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1833 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val * (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4216 "rcparse.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1838 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val / (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4225 "rcparse.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1843 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val % (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4234 "rcparse.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1848 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val + (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4243 "rcparse.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1853 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val - (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4252 "rcparse.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1858 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val & (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4261 "rcparse.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1863 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val ^ (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4270 "rcparse.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1868 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val | (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4279 "rcparse.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1879 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.il) = (yyvsp[0].il);
	  }
#line 4287 "rcparse.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1888 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.il) = (yyvsp[0].i).val;
	  }
#line 4295 "rcparse.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1899 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i) = (yyvsp[0].i);
	  }
#line 4303 "rcparse.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1903 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i) = (yyvsp[-1].i);
	  }
#line 4311 "rcparse.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1907 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = ~ (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[0].i).dword;
	  }
#line 4320 "rcparse.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1912 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val * (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4329 "rcparse.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1917 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val / (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4338 "rcparse.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1922 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val % (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4347 "rcparse.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1927 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val + (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4356 "rcparse.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1932 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val - (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4365 "rcparse.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1937 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val & (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4374 "rcparse.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1942 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val ^ (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4383 "rcparse.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1947 "rcparse.y" /* yacc.c:1646  */
    {
	    (yyval.i).val = (yyvsp[-2].i).val | (yyvsp[0].i).val;
	    (yyval.i).dword = (yyvsp[-2].i).dword || (yyvsp[0].i).dword;
	  }
#line 4392 "rcparse.c" /* yacc.c:1646  */
    break;


#line 4396 "rcparse.c" /* yacc.c:1646  */
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
#line 1953 "rcparse.y" /* yacc.c:1906  */


/* Set the language from the command line.  */

void
rcparse_set_language (int lang)
{
  language = lang;
}
