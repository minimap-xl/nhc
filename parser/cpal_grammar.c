/* A Bison parser, made by GNU Bison 3.0.5.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser/cpal_grammar.y" /* yacc.c:339  */


#include "rENV.h"

#include "lex_fix.h"
#include "cpal_grammar.h"
#include "cpal_lex.h"

extern void yyerror(yyscan_t, parser_Env *, const char *);
extern void scan_string(yyscan_t,  char *);

#include "parser_config.h"
#include "rAST.h"
#include "def_expression.h"
#include "def_process.h"
#include "def_variable.h"
#include "def_parameter.h"
#include "def_buffer.h"
#include "def_function.h"
#include "def_type.h"
#include "def_iterator.h"
#include "def_statement.h"
#include "def_annotation.h"
#include "builtin_prototypes.h"
#include "parser_data.h"
#include "parser_error.h"
#include "cpal_system.h"

extern AST * parser_LineNode;
extern YY_DECL;


#line 99 "parser/cpal_grammar.c" /* yacc.c:339  */

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
   by #include "cpal_grammar.h".  */
#ifndef YY_YY_PARSER_CPAL_GRAMMAR_H_INCLUDED
# define YY_YY_PARSER_CPAL_GRAMMAR_H_INCLUDED
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
    INTEGER = 258,
    SYMBOL = 259,
    STRING = 260,
    FLOAT = 261,
    BOOLEAN = 262,
    TVAR = 263,
    IF = 264,
    ELSE = 265,
    WHILE = 266,
    FOR = 267,
    TENUM = 268,
    TTYPE = 269,
    TON = 270,
    TTO = 271,
    AFTER = 272,
    TSTATE = 273,
    TPROCESS = 274,
    TCHANNEL = 275,
    TCEQ = 276,
    TCNE = 277,
    TCLT = 278,
    TCLE = 279,
    TCGT = 280,
    TCGE = 281,
    TEQUAL = 282,
    TAND = 283,
    TOR = 284,
    TNOT = 285,
    TLPAREN = 286,
    TRPAREN = 287,
    TLBRACE = 288,
    TRBRACE = 289,
    TLBRACKET = 290,
    TRBRACKET = 291,
    TCOMMA = 292,
    TDOT = 293,
    TSEMICOLON = 294,
    TCOLON = 295,
    TPLUS = 296,
    TMINUS = 297,
    TMUL = 298,
    TDIV = 299,
    TSTRUCT = 300,
    TQUEUE = 301,
    TSTACK = 302,
    TKIN = 303,
    TKOUT = 304,
    TCONST = 305,
    TAFTER = 306,
    TEXIT = 307,
    TSTATIC = 308,
    TCOMMON = 309,
    TFINALLY = 310,
    TKPROCESSDEF = 311,
    TMOD = 312,
    TLOOP = 313,
    TOVER = 314,
    TWITH = 315,
    CONTINUE = 316,
    BREAK = 317,
    TREMOVE = 318,
    TBITWISEAND = 319,
    TBITWISEOR = 320,
    TBITWISEXOR = 321,
    TBITWISENOT = 322,
    TBITWISELEFTSHIFT = 323,
    TBITWISERIGHTSHIFT = 324,
    T__LINE__ = 325,
    UMINUS = 326,
    TAROBASE = 327,
    TDOLLAR = 328,
    TIME = 329,
    FREQ = 330,
    THERTZ = 331
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 41 "parser/cpal_grammar.y" /* yacc.c:355  */

    AST *        val;
    uint32_t    ival;

#line 221 "parser/cpal_grammar.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner, parser_Env *env);

#endif /* !YY_YY_PARSER_CPAL_GRAMMAR_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 237 "parser/cpal_grammar.c" /* yacc.c:358  */

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
#define YYFINAL  91
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   840

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  84
/* YYNRULES -- Number of rules.  */
#define YYNRULES  213
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  424

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   331

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      75,    76
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   121,   121,   122,   123,   127,   130,   131,   132,   136,
     137,   138,   139,   140,   141,   142,   143,   147,   151,   152,
     157,   161,   162,   175,   178,   181,   182,   186,   187,   191,
     192,   193,   197,   198,   202,   206,   207,   211,   212,   216,
     219,   219,   225,   226,   230,   231,   232,   233,   234,   238,
     242,   243,   244,   245,   246,   250,   251,   254,   255,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   271,   272,
     272,   276,   277,   278,   282,   283,   284,   288,   289,   293,
     294,   295,   296,   300,   301,   302,   306,   310,   311,   312,
     316,   320,   320,   327,   328,   329,   330,   331,   335,   336,
     339,   343,   346,   347,   351,   352,   357,   358,   362,   366,
     367,   368,   372,   373,   374,   378,   379,   380,   381,   382,
     383,   387,   391,   392,   396,   397,   398,   399,   403,   404,
     408,   409,   410,   411,   415,   419,   420,   424,   425,   429,
     430,   434,   435,   439,   440,   444,   445,   446,   450,   451,
     452,   456,   457,   461,   462,   466,   467,   471,   472,   473,
     477,   478,   482,   483,   484,   485,   486,   490,   491,   492,
     493,   497,   498,   499,   500,   501,   502,   503,   504,   505,
     509,   510,   514,   515,   519,   520,   524,   525,   526,   527,
     528,   529,   530,   531,   534,   535,   536,   539,   540,   541,
     551,   555,   556,   557,   561,   562,   563,   564,   568,   569,
     573,   574,   575,   579
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "SYMBOL", "STRING", "FLOAT",
  "BOOLEAN", "TVAR", "IF", "ELSE", "WHILE", "FOR", "TENUM", "TTYPE", "TON",
  "TTO", "AFTER", "TSTATE", "TPROCESS", "TCHANNEL", "TCEQ", "TCNE", "TCLT",
  "TCLE", "TCGT", "TCGE", "TEQUAL", "TAND", "TOR", "TNOT", "TLPAREN",
  "TRPAREN", "TLBRACE", "TRBRACE", "TLBRACKET", "TRBRACKET", "TCOMMA",
  "TDOT", "TSEMICOLON", "TCOLON", "TPLUS", "TMINUS", "TMUL", "TDIV",
  "TSTRUCT", "TQUEUE", "TSTACK", "TKIN", "TKOUT", "TCONST", "TAFTER",
  "TEXIT", "TSTATIC", "TCOMMON", "TFINALLY", "TKPROCESSDEF", "TMOD",
  "TLOOP", "TOVER", "TWITH", "CONTINUE", "BREAK", "TREMOVE", "TBITWISEAND",
  "TBITWISEOR", "TBITWISEXOR", "TBITWISENOT", "TBITWISELEFTSHIFT",
  "TBITWISERIGHTSHIFT", "T__LINE__", "UMINUS", "TAROBASE", "TDOLLAR",
  "TIME", "FREQ", "THERTZ", "$accept", "anything", "program",
  "external_definitions", "external_definition", "annotation",
  "hierarchical_symbol", "function_prototype", "process_definiton",
  "processdef_key_word", "process_implicit_declaration",
  "common_optional_block", "finally_optional_block",
  "process_variables_declaration_list", "process_variable_declaration",
  "process_prototype", "states_list", "enum_definition", "enum_start",
  "struct_definition", "$@1", "struct_declaration_list",
  "struct_declaration", "type_spec", "variable_declaration",
  "scope_variables_declaration_list", "scope_variable_declaration",
  "buffer_declaration", "function_definition", "$@2", "parameter_list",
  "parameter", "in_out", "scope", "block", "block_name",
  "subprocess_declaration_list", "subprocess_declaration",
  "global_process_instanciation", "$@3", "time_trigger", "cond_trigger",
  "state", "state_name", "symbol_list", "statements_list", "loop_command",
  "iterator_declaration", "statement", "triggers_optional_list", "trigger",
  "transition", "assignment", "initializer", "initializer_element_list",
  "initializer_element", "expression", "logical_or_expression",
  "logical_and_expression", "bitwise_or_expression",
  "bitwise_xor_expression", "bitwise_and_expression",
  "multiple_equality_expression", "equality_expression",
  "multiple_relational_expression", "relational_expression",
  "bitwise_shift_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "postfix_expression",
  "primary_expression", "call_operation", "call_data", "call",
  "standard_statement", "if_statement", "argument_expression_list",
  "custom_expression", "channel_type", "comparison_token",
  "bitwise_shift_token", "multiplicative_token", "frequency", YY_NULLPTR
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
     325,   326,   327,   328,   329,   330,   331
};
# endif

#define YYPACT_NINF -241

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-241)))

#define YYTABLE_NINF -194

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     156,    86,    88,  -241,    25,  -241,    88,  -241,    27,   574,
      62,  -241,   234,  -241,  -241,  -241,  -241,    50,  -241,  -241,
      95,  -241,  -241,  -241,  -241,   -19,  -241,   192,  -241,  -241,
    -241,  -241,  -241,    73,   145,    75,   166,   158,   161,  -241,
      -5,  -241,   116,  -241,  -241,  -241,   160,   184,   190,   221,
     716,   716,   328,   716,   189,   211,   224,   716,  -241,  -241,
    -241,  -241,  -241,  -241,   -19,  -241,  -241,   226,  -241,   240,
     244,   217,   225,   223,   254,  -241,   326,  -241,   120,   214,
      20,   268,   164,  -241,   255,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,   272,   275,  -241,  -241,  -241,     8,  -241,
      88,   301,   306,   310,   282,   315,   306,   316,  -241,   716,
     716,   716,   716,  -241,   290,  -241,  -241,   291,  -241,  -241,
      26,  -241,   405,  -241,   478,  -241,   268,  -241,    19,  -241,
    -241,  -241,  -241,  -241,   716,   716,   716,   716,   716,   716,
     716,   716,   716,  -241,  -241,  -241,  -241,   716,  -241,  -241,
     716,   716,   716,   716,  -241,  -241,  -241,   716,   666,   716,
      13,  -241,   192,   320,   287,   192,   288,   318,   126,   313,
    -241,    88,   165,   317,  -241,  -241,    41,   311,   312,   314,
     350,  -241,  -241,  -241,   526,  -241,  -241,   -19,   103,   244,
     217,   225,   223,  -241,   210,   210,   210,   210,   209,   209,
     214,    20,    20,  -241,    54,  -241,  -241,   771,   319,   325,
    -241,   122,  -241,   121,  -241,    37,  -241,   353,   306,   666,
     716,  -241,   323,   330,   163,  -241,   327,   337,   666,   716,
    -241,   329,  -241,   716,   -19,   -19,   716,  -241,  -241,  -241,
     364,   620,  -241,   185,  -241,  -241,   215,  -241,   716,    58,
     332,    34,   333,  -241,   339,   347,   336,  -241,   340,   373,
     675,   344,   341,  -241,    14,   306,   343,   348,   379,  -241,
     375,  -241,   349,  -241,  -241,   220,  -241,   697,   125,  -241,
    -241,  -241,  -241,   352,   351,   354,  -241,    28,   191,  -241,
     256,   263,   716,   365,  -241,    97,   358,   374,  -241,    59,
     366,     0,   716,  -241,  -241,  -241,   385,  -241,  -241,   401,
     666,  -241,   666,   716,  -241,  -241,   716,  -241,   716,   370,
     716,   716,  -241,  -241,   378,   666,  -241,   716,  -241,  -241,
     383,   415,   129,  -241,  -241,   381,   382,   386,   388,   389,
    -241,   144,   390,   423,   391,   392,    37,   393,    26,    29,
    -241,  -241,  -241,  -241,  -241,    92,  -241,  -241,   395,   398,
     151,  -241,   402,  -241,   427,  -241,   -19,   414,  -241,   666,
    -241,  -241,  -241,   716,  -241,   666,   403,  -241,   436,    -3,
    -241,   404,   408,   406,  -241,  -241,    37,   -19,   407,  -241,
    -241,   409,  -241,    -2,  -241,  -241,  -241,   418,   419,    -2,
    -241,   716,   716,  -241,   420,   421,    32,    23,   442,   435,
    -241,   425,   435,  -241,   422,  -241,   716,  -241,  -241,   428,
      32,   435,  -241,  -241
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       8,     0,     0,    39,     0,    40,     0,    23,     0,     0,
       0,     2,     5,     6,    15,    68,    11,     0,    21,    12,
       0,    13,    10,    54,     9,     0,    14,    71,    86,    49,
     203,   201,   202,     0,     0,     0,     0,     0,     0,    18,
       0,   173,   172,   174,   175,   176,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   178,   170,
     213,    84,    85,   110,     0,   111,     3,   192,     4,   134,
     135,   137,   139,   141,   143,   145,   148,   151,   153,   155,
     157,   160,   162,   167,   184,   185,   171,   109,   188,   166,
     179,     1,     7,     0,     0,    16,    77,    78,     0,    72,
       0,     0,     0,     0,     0,     0,     0,     0,    17,   197,
       0,     0,     0,   200,   172,   164,   184,     0,   160,    82,
       0,    57,     0,    55,     0,   104,     0,   163,     0,   107,
     106,   165,    83,   186,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   204,   207,   205,   206,     0,   208,   209,
       0,     0,     0,     0,   210,   211,   212,     0,     0,     0,
       0,   187,    71,     0,    69,     0,     0,     0,     0,     0,
      91,     0,     0,     0,    19,   198,     0,     0,     0,     0,
     177,    58,    81,    56,     0,    80,   105,     0,     0,   136,
     138,   140,   142,   144,   146,   147,   149,   150,   152,   154,
     156,   158,   159,   161,     0,   123,   122,   124,     0,   182,
     183,     0,   102,     0,    20,     0,    73,     0,     0,     0,
       0,    50,     0,     0,     0,    42,     0,     0,     0,     0,
      53,     0,   180,     0,     0,     0,     0,   169,    79,   191,
       0,     0,   126,     0,   128,   131,   179,   168,   197,     0,
       0,     0,     0,    70,    74,     0,     0,   125,     0,     0,
       0,    98,     0,    43,     0,     0,     0,     0,     0,   199,
     194,   189,     0,   108,   133,     0,   127,     0,     0,    24,
      34,    37,   103,     0,     0,     0,    51,     0,     0,    93,
       0,   179,     0,     0,    41,     0,     0,     0,    52,     0,
       0,     0,     0,   132,   129,   181,    87,    38,    76,     0,
       0,    59,     0,     0,    66,    94,     0,    96,     0,     0,
     197,     0,    44,    45,     0,     0,    62,     0,   195,   196,
       0,     0,    29,    88,    75,     0,     0,     0,     0,     0,
      99,     0,     0,     0,     0,     0,     0,     0,     0,    25,
      30,    33,    89,    60,    67,     0,    95,    97,     0,     0,
       0,    61,     0,   190,     0,    32,     0,     0,    31,     0,
      63,    92,    46,     0,    48,     0,     0,    26,     0,    27,
      35,     0,     0,     0,    90,   101,     0,     0,     0,    36,
      64,     0,    65,   112,    28,    22,    47,     0,     0,   100,
     113,     0,     0,   114,     0,     0,     0,     0,     0,     0,
     116,     0,     0,   118,     0,   115,     0,   117,   121,     0,
       0,     0,   120,   119
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -241,  -241,  -241,  -241,   445,   130,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,   105,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,   235,     5,   -51,  -241,   342,  -241,  -241,  -241,
     300,   303,  -241,   -21,  -213,   140,  -241,   133,  -241,  -241,
    -241,  -241,    90,  -241,  -241,   356,  -241,  -241,    -4,  -241,
      71,  -204,  -106,  -198,   230,   196,    -9,  -241,   357,   359,
     338,   355,  -241,   360,   104,  -241,   124,   335,   149,    -6,
     367,  -241,     1,  -241,  -241,  -241,   175,  -240,  -241,    10,
     410,  -241,  -241,  -138
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,    11,    12,    13,    61,    40,    15,    16,    17,
     306,   367,   388,   349,   350,    18,   379,    19,    20,    21,
      36,   224,   225,   226,    22,   122,   123,    23,    24,   215,
      98,    99,   100,    62,    63,    64,   332,   333,    26,   223,
     261,   293,   380,   386,   213,   124,    65,   187,   125,   399,
     400,   410,    67,   205,   243,   244,   257,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,   118,
      82,    83,   116,    85,    86,    87,    88,   176,    89,   227,
     147,   151,   157,    90
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,   121,   253,    81,    95,    66,   179,    33,   278,    46,
      84,    37,    34,   397,    52,   378,    38,   209,   295,   108,
     207,   256,    41,   114,    43,    44,    45,   252,    52,    35,
     266,    39,   411,    52,     2,   107,   252,     2,   282,   408,
     164,   252,   117,   132,   115,   165,   126,   127,   408,   398,
      51,   131,   387,    84,    93,   310,    52,    41,   114,    43,
      44,    45,    91,   154,   155,    52,   246,   311,   283,   181,
      52,   121,    49,   232,   210,   296,     6,   156,   233,     6,
     341,   207,   348,   366,    50,    51,   325,   241,   242,    58,
     207,   279,    29,    59,    60,     8,    53,   280,   326,    94,
     175,   177,   178,   246,     8,   166,   126,   169,    30,     8,
     167,   173,   335,   101,   336,   103,   126,    27,   126,   369,
     186,    57,   291,    84,    58,    84,    28,   344,    59,    60,
      14,   370,   321,   363,    31,    32,   322,     2,   159,   246,
      25,   160,    14,   143,   144,   145,   146,   109,   331,   206,
     208,   203,    25,   219,   249,   250,    28,   305,   251,   165,
       1,   220,   233,   240,     2,   221,   239,    29,   102,     3,
     104,   381,   207,   393,   207,     4,   358,   383,   126,     6,
     186,   233,   348,    30,   106,    84,   373,   207,   148,   149,
     374,   110,   228,   409,   412,   245,   330,   262,   105,   159,
     229,     5,   160,   413,   230,   415,     6,   421,   417,    31,
      32,   258,     7,   270,   271,   111,   422,   423,   312,   276,
     267,   112,   277,   255,   269,   113,   313,   272,     8,     9,
     314,   207,   245,   143,   144,   145,   146,   207,     1,   175,
      96,    97,     2,   194,   195,   196,   197,     3,   128,  -130,
     129,   290,  -130,     4,   303,   152,   153,   277,  -193,  -193,
    -193,  -193,  -193,   130,  -193,   133,  -193,  -193,   245,   134,
     297,   198,   135,  -193,   199,   139,   140,   148,   149,     5,
     328,   351,   136,   319,     6,  -193,  -193,   138,  -193,  -193,
       7,   137,   315,   316,   161,   158,   126,   365,   351,   317,
     318,   201,   202,   162,   337,   168,     8,   338,   163,   339,
      29,   175,   342,  -193,   170,   171,  -193,  -193,   345,   172,
     174,   109,  -193,   180,   212,  -193,   214,  -193,   217,  -193,
    -193,    41,    42,    43,    44,    45,     2,    46,   222,    47,
      48,   218,   231,   234,   235,   377,    49,   141,   142,   143,
     144,   145,   146,   236,   237,   247,   248,   254,    50,    51,
     265,    52,   119,   259,   382,   260,   394,   264,   273,   268,
      53,   281,   285,    28,   284,   286,   287,   288,     6,   292,
     294,   120,   298,   300,   299,   301,    54,   308,   302,    55,
      56,   307,   404,   405,   309,    57,   320,   323,    58,   324,
       8,   327,    59,    60,   331,   334,   340,   419,    41,    42,
      43,    44,    45,     2,    46,   346,    47,    48,   343,   347,
     353,   354,   355,    49,   356,   357,   359,   360,   362,   375,
     361,   376,   378,   364,   371,    50,    51,   372,    52,   182,
     385,   395,   384,   390,   391,   392,   414,    53,   396,   401,
     402,   408,   406,   407,   368,     6,   416,    92,   120,   263,
     420,   418,   211,    54,   183,   352,    55,    56,   216,   389,
     403,   275,    57,   304,   191,    58,   329,     8,   184,    59,
      60,    41,    42,    43,    44,    45,   200,    46,   150,    47,
      48,   189,   192,     0,   190,   188,    49,     0,   193,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,    51,
       0,    52,   185,     0,     0,     0,     0,     0,     0,     0,
      53,     0,     0,     0,     0,     0,     0,     0,     0,    41,
      42,    43,    44,    45,     0,    46,    54,    47,    48,    55,
      56,     0,     0,     0,    49,    57,     0,     0,    58,     0,
       8,     0,    59,    60,     0,     0,    50,    51,     0,    52,
     238,     0,     0,     0,     0,     0,     0,     0,    53,     0,
       0,     0,     0,     0,     0,     0,     0,    41,    42,    43,
      44,    45,     0,    46,    54,    47,    48,    55,    56,     0,
       0,     0,    49,    57,     0,     0,    58,     0,     8,     0,
      59,    60,     0,     0,    50,    51,     0,    52,     0,     0,
       0,     0,     0,     0,     0,     0,    53,     0,     0,     0,
       0,     0,     0,    41,   114,    43,    44,    45,     0,     0,
       0,     0,    54,     0,     0,    55,    56,     0,    49,     0,
       0,    57,     0,     0,    58,     0,     8,     0,    59,    60,
      50,    51,     0,   241,   274,     0,     0,     0,     0,     0,
       0,     0,    53,     0,     0,     0,     0,     0,     0,    41,
     114,    43,    44,    45,     0,     0,     0,     0,    41,   114,
      43,    44,    45,     0,    49,     0,     0,    57,     0,     0,
      58,     0,     0,    49,    59,    60,    50,    51,     0,   204,
      41,   114,    43,    44,    45,    50,    51,     0,    53,     0,
       0,   289,     0,     0,     0,    49,     0,    53,     0,    41,
     114,    43,    44,    45,     0,     0,     0,    50,    51,     0,
     241,     0,     0,    57,    49,     0,    58,     0,     0,    53,
      59,    60,    57,     0,     0,    58,    50,    51,     0,    59,
      60,     0,     0,     0,     0,     0,     0,     0,    53,     0,
       0,     0,     0,     0,    57,     0,     0,    58,     0,     0,
       0,    59,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    57,     0,     0,    58,     0,     0,     0,
      59,    60,  -179,  -179,  -179,  -179,  -179,  -179,     0,  -179,
    -179,     0,     0,     0,     0,     0,  -179,     0,     0,  -179,
       0,     0,  -179,     0,  -179,  -179,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -179,     0,
       0,     0,     0,     0,     0,  -179,  -179,  -179,     0,  -179,
    -179
};

static const yytype_int16 yycheck[] =
{
       9,    52,   215,     9,    25,     9,   112,     2,   248,     9,
       9,     6,     2,    15,    33,    18,     6,     4,     4,    40,
     158,   219,     3,     4,     5,     6,     7,     4,    33,     4,
     228,     4,     9,    33,     8,    40,     4,     8,     4,    16,
      32,     4,    51,    64,    50,    37,    52,    53,    16,    51,
      31,    57,    55,    52,     4,    27,    33,     3,     4,     5,
       6,     7,     0,    43,    44,    33,   204,    39,    34,   120,
      33,   122,    18,    32,    61,    61,    50,    57,    37,    50,
     320,   219,    53,    54,    30,    31,    27,    33,    34,    70,
     228,    33,     4,    74,    75,    72,    42,    39,    39,     4,
     109,   110,   111,   241,    72,   100,   112,   102,    20,    72,
     100,   106,   310,    40,   312,    40,   122,    31,   124,    27,
     124,    67,   260,   122,    70,   124,    40,   325,    74,    75,
       0,    39,    35,   346,    46,    47,    39,     8,    35,   277,
       0,    38,    12,    23,    24,    25,    26,    31,    19,   158,
     159,   157,    12,    27,    32,    34,    40,    32,    37,    37,
       4,    35,    37,    60,     8,    39,   187,     4,    23,    13,
       4,   369,   310,   386,   312,    19,    32,   375,   184,    50,
     184,    37,    53,    20,    23,   184,    35,   325,    68,    69,
      39,    31,    27,   406,   407,   204,   302,    34,    40,    35,
      35,    45,    38,   407,    39,   409,    50,   420,   412,    46,
      47,   220,    56,   234,   235,    31,   420,   421,    27,    34,
     229,    31,    37,   218,   233,     4,    35,   236,    72,    73,
      39,   369,   241,    23,    24,    25,    26,   375,     4,   248,
      48,    49,     8,   139,   140,   141,   142,    13,    59,    34,
      39,   260,    37,    19,    34,    41,    42,    37,     3,     4,
       5,     6,     7,    39,     9,    39,    11,    12,   277,    29,
     265,   147,    28,    18,   150,    21,    22,    68,    69,    45,
     301,   332,    65,   292,    50,    30,    31,    64,    33,    34,
      56,    66,    36,    37,    39,    27,   302,   348,   349,    36,
      37,   152,   153,    31,   313,     4,    72,   316,    33,   318,
       4,   320,   321,    58,     4,    33,    61,    62,   327,     4,
       4,    31,    67,    32,     4,    70,    39,    72,    40,    74,
      75,     3,     4,     5,     6,     7,     8,     9,    25,    11,
      12,    23,    25,    32,    32,   366,    18,    21,    22,    23,
      24,    25,    26,    39,     4,    36,    31,     4,    30,    31,
      23,    33,    34,    40,   373,    35,   387,    40,     4,    40,
      42,    39,    25,    40,    35,    39,    36,     4,    50,    35,
      39,    53,    39,     4,    36,    10,    58,    36,    39,    61,
      62,    39,   401,   402,    40,    67,    31,    39,    70,    25,
      72,    35,    74,    75,    19,     4,    36,   416,     3,     4,
       5,     6,     7,     8,     9,    32,    11,    12,    40,     4,
      39,    39,    36,    18,    36,    36,    36,     4,    36,    27,
      39,     4,    18,    40,    39,    30,    31,    39,    33,    34,
       4,    34,    39,    39,    36,    39,     4,    42,    39,    31,
      31,    16,    32,    32,   349,    50,    31,    12,    53,   224,
      32,    39,   162,    58,   122,   332,    61,    62,   165,   379,
     399,   241,    67,   277,   136,    70,   301,    72,   122,    74,
      75,     3,     4,     5,     6,     7,   151,     9,    78,    11,
      12,   134,   137,    -1,   135,   128,    18,    -1,   138,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    58,    11,    12,    61,
      62,    -1,    -1,    -1,    18,    67,    -1,    -1,    70,    -1,
      72,    -1,    74,    75,    -1,    -1,    30,    31,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,    -1,     9,    58,    11,    12,    61,    62,    -1,
      -1,    -1,    18,    67,    -1,    -1,    70,    -1,    72,    -1,
      74,    75,    -1,    -1,    30,    31,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    58,    -1,    -1,    61,    62,    -1,    18,    -1,
      -1,    67,    -1,    -1,    70,    -1,    72,    -1,    74,    75,
      30,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,    -1,    18,    -1,    -1,    67,    -1,    -1,
      70,    -1,    -1,    18,    74,    75,    30,    31,    -1,    33,
       3,     4,     5,     6,     7,    30,    31,    -1,    42,    -1,
      -1,    36,    -1,    -1,    -1,    18,    -1,    42,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    30,    31,    -1,
      33,    -1,    -1,    67,    18,    -1,    70,    -1,    -1,    42,
      74,    75,    67,    -1,    -1,    70,    30,    31,    -1,    74,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    70,    -1,    -1,
      -1,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    70,    -1,    -1,    -1,
      74,    75,    21,    22,    23,    24,    25,    26,    -1,    28,
      29,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,
      -1,    -1,    41,    -1,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    -1,    68,
      69
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     8,    13,    19,    45,    50,    56,    72,    73,
      78,    79,    80,    81,    82,    84,    85,    86,    92,    94,
      95,    96,   101,   104,   105,   112,   115,    31,    40,     4,
      20,    46,    47,   100,   156,     4,    97,   100,   156,     4,
      83,     3,     4,     5,     6,     7,     9,    11,    12,    18,
      30,    31,    33,    42,    58,    61,    62,    67,    70,    74,
      75,    82,   110,   111,   112,   123,   125,   129,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   155,
     160,     0,    81,     4,     4,   110,    48,    49,   107,   108,
     109,    40,    23,    40,     4,    40,    23,    40,   110,    31,
      31,    31,    31,     4,     4,   146,   149,   133,   146,    34,
      53,   101,   102,   103,   122,   125,   146,   146,    59,    39,
      39,   146,   110,    39,    29,    28,    65,    66,    64,    21,
      22,    21,    22,    23,    24,    25,    26,   157,    68,    69,
     157,   158,    41,    42,    43,    44,    57,   159,    27,    35,
      38,    39,    31,    33,    32,    37,   100,   156,     4,   100,
       4,    33,     4,   100,     4,   133,   154,   133,   133,   129,
      32,   101,    34,   103,   122,    34,   125,   124,   147,   135,
     136,   137,   138,   140,   141,   141,   141,   141,   143,   143,
     144,   145,   145,   146,    33,   130,   133,   160,   133,     4,
      61,   107,     4,   121,    39,   106,   108,    40,    23,    27,
      35,    39,    25,   116,    98,    99,   100,   156,    27,    35,
      39,    25,    32,    37,    32,    32,    39,     4,    34,   110,
      60,    33,    34,   131,   132,   133,   160,    36,    31,    32,
      34,    37,     4,   111,     4,   100,   130,   133,   133,    40,
      35,   117,    34,    99,    40,    23,   130,   133,    40,   133,
     110,   110,   133,     4,    34,   131,    34,    37,   154,    33,
      39,    39,     4,    34,    35,    25,    39,    36,     4,    36,
     133,   160,    35,   118,    39,     4,    61,   100,    39,    36,
       4,    10,    39,    34,   132,    32,    87,    39,    36,    40,
      27,    39,    27,    35,    39,    36,    37,    36,    37,   133,
      31,    35,    39,    39,    25,    27,    39,    35,   110,   153,
     129,    19,   113,   114,     4,   130,   130,   133,   133,   133,
      36,   154,   133,    40,   130,   133,    32,     4,    53,    90,
      91,   101,   114,    39,    39,    36,    36,    36,    32,    36,
       4,    39,    36,   111,    40,   101,    54,    88,    91,    27,
      39,    39,    39,    35,    39,    27,     4,   110,    18,    93,
     119,   130,   133,   130,    39,     4,   120,    55,    89,   119,
      39,    36,    39,   111,   110,    34,    39,    15,    51,   126,
     127,    31,    31,   127,   133,   133,    32,    32,    16,   111,
     128,     9,   111,   128,     4,   128,    31,   128,    39,   133,
      32,   111,   128,   128
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    77,    78,    78,    78,    79,    80,    80,    80,    81,
      81,    81,    81,    81,    81,    81,    81,    82,    83,    83,
      84,    85,    85,    86,    87,    88,    88,    89,    89,    90,
      90,    90,    91,    91,    92,    93,    93,    94,    94,    95,
      97,    96,    98,    98,    99,    99,    99,    99,    99,   100,
     101,   101,   101,   101,   101,   102,   102,   103,   103,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   105,   106,
     105,   107,   107,   107,   108,   108,   108,   109,   109,   110,
     110,   110,   110,   111,   111,   111,   112,   113,   113,   113,
     114,   116,   115,   117,   117,   117,   117,   117,   118,   118,
     119,   120,   121,   121,   122,   122,   123,   123,   124,   125,
     125,   125,   126,   126,   126,   127,   127,   127,   127,   127,
     127,   128,   129,   129,   130,   130,   130,   130,   131,   131,
     132,   132,   132,   132,   133,   134,   134,   135,   135,   136,
     136,   137,   137,   138,   138,   139,   139,   139,   140,   140,
     140,   141,   141,   142,   142,   143,   143,   144,   144,   144,
     145,   145,   146,   146,   146,   146,   146,   147,   147,   147,
     147,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     149,   149,   150,   150,   151,   151,   152,   152,   152,   152,
     152,   152,   152,   152,   153,   153,   153,   154,   154,   154,
     155,   156,   156,   156,   157,   157,   157,   157,   158,   158,
     159,   159,   159,   160
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     2,     0,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     1,     3,
       5,     1,    13,     1,     0,     0,     2,     0,     2,     0,
       1,     2,     2,     1,     6,     1,     2,     6,     7,     1,
       0,     7,     1,     2,     4,     4,     7,    10,     7,     1,
       5,     7,     7,     5,     1,     1,     2,     1,     2,     8,
      10,    10,     8,    11,    13,    13,     8,    10,     1,     0,
       6,     0,     1,     3,     4,     7,     6,     1,     1,     4,
       3,     3,     2,     2,     1,     1,     2,     0,     1,     2,
       5,     0,    11,     2,     3,     5,     3,     5,     0,     3,
       4,     1,     1,     3,     1,     2,     2,     2,     3,     1,
       1,     1,     0,     1,     2,     6,     5,     6,     5,    10,
       9,     3,     3,     3,     1,     1,     2,     3,     1,     3,
       1,     1,     3,     2,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     1,     2,     2,     2,     1,     1,     4,     4,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       4,     6,     3,     3,     1,     1,     2,     2,     1,     5,
       9,     4,     1,     1,     5,     7,     7,     0,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
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
      yyerror (scanner, env, YY_("syntax error: cannot back up")); \
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
                  Type, Value, scanner, env); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *scanner, parser_Env *env)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (scanner);
  YYUSE (env);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *scanner, parser_Env *env)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, scanner, env);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, void *scanner, parser_Env *env)
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
                                              , scanner, env);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner, env); \
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
    default: /* Avoid compiler warnings. */
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *scanner, parser_Env *env)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  YYUSE (env);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner, parser_Env *env)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

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
      yychar = yylex (&yylval, scanner, env);
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
        case 2:
#line 121 "parser/cpal_grammar.y" /* yacc.c:1663  */
    {}
#line 1736 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 3:
#line 122 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { env->pctx->parser_LineNode = (yyvsp[0].val);}
#line 1742 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 4:
#line 123 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { env->pctx->parser_LineNode = (yyvsp[0].val);}
#line 1748 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 6:
#line 130 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { parser_add_external_definition(env,(yyvsp[0].val)); }
#line 1754 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 7:
#line 131 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { parser_add_external_definition(env,(yyvsp[0].val)); }
#line 1760 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 8:
#line 132 "parser/cpal_grammar.y" /* yacc.c:1663  */
    {}
#line 1766 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 9:
#line 136 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 1772 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 10:
#line 137 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { defVar_declareGlobal(env,(yyvsp[0].val)); (yyval.val) = (yyvsp[0].val); }
#line 1778 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 11:
#line 138 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 1784 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 12:
#line 139 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 1790 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 13:
#line 140 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 1796 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 14:
#line 141 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 1802 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 15:
#line 142 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 1808 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 16:
#line 143 "parser/cpal_grammar.y" /* yacc.c:1663  */
    {	(yyval.val) = makeNamedBlock(env,(yyvsp[-1].val),(yyvsp[0].val));}
#line 1814 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 17:
#line 147 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { /*$$ = NULL;*/ (yyval.val)=defineAnnotation(env,(yyvsp[-1].val),(yyvsp[0].val)); }
#line 1820 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 18:
#line 151 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList1(env->program,(yyvsp[0].val),yyget_lineno(scanner)); }
#line 1826 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 19:
#line 152 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_addListLast(env->program,(yyvsp[-2].val),(yyvsp[0].val),yyget_lineno(scanner)); }
#line 1832 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 20:
#line 157 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { env->pctx->definition_line_no = yyget_lineno(scanner); (yyval.val) = defFunc_definePrototype(env,AST_getSymbolId((yyvsp[-4].val)),(yyvsp[-2].val)); defVar_clearLocals(env, (yyvsp[-2].val)); }
#line 1838 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 21:
#line 161 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 1844 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 22:
#line 168 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defProc_declareStateMachine(env,AST_getSymbolId((yyvsp[-11].val)),(yyvsp[-9].val),(yyvsp[-5].val),(yyvsp[-4].val),(yyvsp[-3].val),(yyvsp[-2].val),(yyvsp[-1].val));
                                       defVar_clearLocals(env,(yyvsp[-9].val));
                                       defVar_clearProcessLocalImplicitVariables(env, (yyvsp[-5].val)); 
                                       defProc_clearLocalInstances(env); }
#line 1853 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 23:
#line 175 "parser/cpal_grammar.y" /* yacc.c:1663  */
    {env->pctx->definition_line_no = yyget_lineno(scanner); }
#line 1859 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 24:
#line 178 "parser/cpal_grammar.y" /* yacc.c:1663  */
    {(yyval.val)=defVar_makeAndDeclareProcessInstanceData(env);}
#line 1865 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 25:
#line 181 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = NULL;}
#line 1871 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 26:
#line 182 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyvsp[0].val)->op= COMMON_BLOCK; (yyval.val) = (yyvsp[0].val); }
#line 1877 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 27:
#line 186 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = NULL;}
#line 1883 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 28:
#line 187 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyvsp[0].val)->op= FINALLY_BLOCK; (yyval.val) = (yyvsp[0].val); }
#line 1889 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 29:
#line 191 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = NULL; }
#line 1895 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 30:
#line 192 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList1(env->program,(yyvsp[0].val),yyget_lineno(scanner)); }
#line 1901 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 31:
#line 193 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_addListLast(env->program,(yyvsp[-1].val),(yyvsp[0].val),yyget_lineno(scanner)); }
#line 1907 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 32:
#line 197 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defProc_addStaticVariable(env,(yyvsp[0].val)); defVar_declareStatic(env,(yyvsp[0].val));}
#line 1913 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 33:
#line 198 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defProc_addVariable(env,(yyvsp[0].val)); defVar_declareLocal(env,(yyvsp[0].val)); }
#line 1919 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 34:
#line 202 "parser/cpal_grammar.y" /* yacc.c:1663  */
    {(yyval.val)= defProc_declareStateMachinePrototype(env,AST_getSymbolId((yyvsp[-4].val)),(yyvsp[-2].val)); defVar_clearLocals(env,(yyvsp[-2].val)); }
#line 1925 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 35:
#line 206 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList1(env->program,(yyvsp[0].val),yyget_lineno(scanner)); }
#line 1931 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 36:
#line 207 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_addListLast(env->program,(yyvsp[-1].val),(yyvsp[0].val),yyget_lineno(scanner)); }
#line 1937 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 37:
#line 211 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val)=defType_declare(env,AST_getSymbolId((yyvsp[-4].val)),TypeEnum,0,(yyvsp[-2].val), env->pctx->definition_line_no); }
#line 1943 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 38:
#line 212 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val)=defType_declare(env,AST_getSymbolId((yyvsp[-5].val)),TypeEnum,0,(yyvsp[-3].val), env->pctx->definition_line_no); }
#line 1949 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 39:
#line 216 "parser/cpal_grammar.y" /* yacc.c:1663  */
    {env->pctx->definition_line_no = yyget_lineno(scanner); }
#line 1955 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 40:
#line 219 "parser/cpal_grammar.y" /* yacc.c:1663  */
    {env->pctx->definition_line_no = yyget_lineno(scanner); }
#line 1961 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 41:
#line 221 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val)=defType_declare(env, AST_getSymbolId((yyvsp[-4].val)), TypeStruct, 0, (yyvsp[-2].val), env->pctx->definition_line_no); }
#line 1967 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 42:
#line 225 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList1(env->program,(yyvsp[0].val),yyget_lineno(scanner)); }
#line 1973 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 43:
#line 226 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_addListLast(env->program,(yyvsp[-1].val),(yyvsp[0].val),yyget_lineno(scanner)); }
#line 1979 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 44:
#line 230 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defType_makeField(env,(yyvsp[-3].val),(yyvsp[-1].val)); }
#line 1985 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 45:
#line 231 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defType_makeField(env,(yyvsp[-3].val),(yyvsp[-1].val)); }
#line 1991 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 46:
#line 232 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { const typeId_t typeId = defType_getBuffer(env,ARRAY_BUFFER,(yyvsp[-6].val),(yyvsp[-2].val)); (yyval.val) = defType_makeField(env,typeId,(yyvsp[-4].val)); }
#line 1997 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 47:
#line 233 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { const typeId_t typeId = defType_getBuffer(env,(yyvsp[-9].ival),(yyvsp[-7].val),(yyvsp[-2].val)); (yyval.val) = defType_makeField(env,typeId,(yyvsp[-4].val)); }
#line 2003 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 48:
#line 234 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { parser_failure(env, 180, env->pctx->parseFilename, parser_lineno(env), NULL, "channel size not specified\n"); }
#line 2009 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 49:
#line 238 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { const typeId_t typeId = defType_lookup(env,AST_getSymbolId((yyvsp[0].val))); if (typeId == NO_ID) parser_failure(env, 184, env->pctx->parseFilename, parser_lineno(env), NULL, "type \"%s\" do not exist\n", Symbol_getName(env->program, (yyvsp[0].val)->value.id.type)); else (yyval.val) = typeId; }
#line 2015 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 50:
#line 242 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defVar_makeDefinition(env,VARIABLE_DECL_OP,(yyvsp[-3].val),(yyvsp[-1].val),NULL); }
#line 2021 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 51:
#line 243 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defVar_makeDefinition(env,VARIABLE_DECL_OP,(yyvsp[-5].val),(yyvsp[-3].val),(yyvsp[-1].val)); }
#line 2027 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 52:
#line 244 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defVar_makeDefinition(env,CONSTANT_DECL_OP,(yyvsp[-5].val),(yyvsp[-3].val),(yyvsp[-1].val)); }
#line 2033 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 53:
#line 245 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { parser_failure(env, 121, env->pctx->parseFilename, parser_lineno(env), NULL, "constant \"%s\" declaration needs an initialization\n", Symbol_getName(env->program, AST_getSymbolId((yyvsp[-1].val)))); }
#line 2039 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 54:
#line 246 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2045 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 55:
#line 250 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList1(env->program,(yyvsp[0].val),yyget_lineno(scanner)); defVar_declareLocal(env,(yyvsp[0].val)); }
#line 2051 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 56:
#line 251 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_addListLast(env->program,(yyvsp[-1].val),(yyvsp[0].val),yyget_lineno(scanner)); defVar_declareLocal(env,(yyvsp[0].val)); }
#line 2057 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 57:
#line 254 "parser/cpal_grammar.y" /* yacc.c:1663  */
    {(yyval.val)=(yyvsp[0].val);}
#line 2063 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 58:
#line 255 "parser/cpal_grammar.y" /* yacc.c:1663  */
    {parser_failure(env, 191, env->pctx->parseFilename, parser_lineno(env), NULL, "static declaration not allowed in this scope");}
#line 2069 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 59:
#line 259 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defBuff_makeDefinition(env,defType_getBuffer(env,ARRAY_BUFFER,(yyvsp[-6].val),(yyvsp[-2].val)),(yyvsp[-4].val),(yyvsp[-2].val),NULL,false); }
#line 2075 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 60:
#line 260 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defBuff_makeDefinition(env,defType_getBuffer(env,ARRAY_BUFFER,(yyvsp[-8].val),(yyvsp[-4].val)),(yyvsp[-6].val),(yyvsp[-4].val),(yyvsp[-1].val),false); }
#line 2081 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 61:
#line 261 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defBuff_makeDefinition(env,defType_getBuffer(env,ARRAY_BUFFER,(yyvsp[-8].val),(yyvsp[-4].val)),(yyvsp[-6].val),(yyvsp[-4].val),(yyvsp[-1].val),true); }
#line 2087 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 62:
#line 262 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { parser_failure(env, 121, env->pctx->parseFilename, parser_lineno(env), NULL, "constant \"%s\" declaration needs an initialization\n", Symbol_getName(env->program, AST_getSymbolId((yyvsp[-4].val)))); }
#line 2093 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 63:
#line 263 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defBuff_makeDefinition(env,defType_getBuffer(env,(yyvsp[-9].ival),(yyvsp[-7].val),(yyvsp[-2].val)),(yyvsp[-4].val),(yyvsp[-2].val),NULL,false); }
#line 2099 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 64:
#line 264 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defBuff_makeDefinition(env,defType_getBuffer(env,(yyvsp[-11].ival),(yyvsp[-9].val),(yyvsp[-4].val)),(yyvsp[-6].val),(yyvsp[-4].val),(yyvsp[-1].val),false); }
#line 2105 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 65:
#line 265 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { parser_failure(env, 124, env->pctx->parseFilename, parser_lineno(env), NULL, "constant channel not allowed\n"); }
#line 2111 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 66:
#line 266 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { parser_failure(env, 180, env->pctx->parseFilename, parser_lineno(env), NULL, "channel size not specified\n"); }
#line 2117 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 67:
#line 267 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { parser_failure(env, 180, env->pctx->parseFilename, parser_lineno(env), NULL, "channel size not specified\n"); }
#line 2123 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 68:
#line 271 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2129 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 69:
#line 272 "parser/cpal_grammar.y" /* yacc.c:1663  */
    {env->pctx->definition_line_no = yyget_lineno(scanner); }
#line 2135 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 70:
#line 272 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defFunc_define(env,AST_getSymbolId((yyvsp[-5].val)),(yyvsp[-3].val),(yyvsp[0].val)); defVar_clearLocals(env,(yyvsp[-3].val)); }
#line 2141 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 71:
#line 276 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = NULL; }
#line 2147 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 72:
#line 277 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList1(env->program,(yyvsp[0].val),yyget_lineno(scanner)); defVar_declareLocal(env,(yyvsp[0].val)); }
#line 2153 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 73:
#line 278 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_addListLast(env->program,(yyvsp[-2].val),(yyvsp[0].val),yyget_lineno(scanner)); defVar_declareLocal(env,(yyvsp[0].val)); }
#line 2159 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 74:
#line 282 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defParam_make(env,(yyvsp[-2].val),(yyvsp[0].val),(yyvsp[-3].ival)); }
#line 2165 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 75:
#line 283 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defParam_make(env,defType_getBuffer(env,(yyvsp[-5].ival),(yyvsp[-3].val),AST_makeIntegerNode(env->program,UINT32_MAX, yyget_lineno(scanner))),(yyvsp[0].val),(yyvsp[-6].ival)); }
#line 2171 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 76:
#line 284 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defParam_make(env,defType_getBuffer(env,ARRAY_BUFFER,(yyvsp[-4].val),AST_makeIntegerNode(env->program,UINT32_MAX, yyget_lineno(scanner))),(yyvsp[-2].val),(yyvsp[-5].ival)); }
#line 2177 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 77:
#line 288 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.ival) = ArgInType; }
#line 2183 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 78:
#line 289 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.ival) = ArgOutType; }
#line 2189 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 79:
#line 293 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeNode(env->program,BLOCK_STATEMENT,0,(yyvsp[-2].val),(yyvsp[-1].val),yyget_lineno(scanner)); defVar_clearLocals(env,(yyvsp[-2].val)); }
#line 2195 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 80:
#line 294 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeNode(env->program,BLOCK_STATEMENT,0,NULL,(yyvsp[-1].val),yyget_lineno(scanner)); }
#line 2201 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 81:
#line 295 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeNode(env->program,BLOCK_STATEMENT,0,(yyvsp[-1].val),NULL,yyget_lineno(scanner)); defVar_clearLocals(env,(yyvsp[-1].val)); }
#line 2207 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 82:
#line 296 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeNode(env->program,BLOCK_STATEMENT,0,NULL,NULL,yyget_lineno(scanner)); }
#line 2213 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 83:
#line 300 "parser/cpal_grammar.y" /* yacc.c:1663  */
    {	(yyval.val) = makeNamedBlock(env,(yyvsp[-1].val),(yyvsp[0].val));}
#line 2219 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 84:
#line 301 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2225 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 85:
#line 302 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2231 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 86:
#line 306 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defVar_makeAndDeclareNamedBlockDefinition(env,(yyvsp[-1].val)); }
#line 2237 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 87:
#line 310 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = NULL; }
#line 2243 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 88:
#line 311 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList1(env->program,(yyvsp[0].val),yyget_lineno(scanner)); defProc_declareLocalInstance(env,(yyvsp[0].val));  }
#line 2249 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 89:
#line 312 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_addListLast(env->program,(yyvsp[-1].val),(yyvsp[0].val),yyget_lineno(scanner)); defProc_declareLocalInstance(env,(yyvsp[0].val));  }
#line 2255 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 90:
#line 316 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defProc_makeInstance(env,(yyvsp[-3].val),(yyvsp[-1].val)); }
#line 2261 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 91:
#line 320 "parser/cpal_grammar.y" /* yacc.c:1663  */
    {
      				defProc_define_global_process_implicit(env, (yyvsp[0].val));
                      }
#line 2269 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 92:
#line 323 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val)=defProc_defineGlobalInstance(env,(yyvsp[-9].val),(yyvsp[-7].val),(yyvsp[-5].val),(yyvsp[-4].val),(yyvsp[-2].val)); }
#line 2275 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 93:
#line 327 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = NULL; }
#line 2281 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 94:
#line 328 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList1(env->program,(yyvsp[-1].val),yyget_lineno(scanner)); }
#line 2287 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 95:
#line 329 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList2(env->program,(yyvsp[-3].val),(yyvsp[-1].val),yyget_lineno(scanner)); }
#line 2293 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 96:
#line 330 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList1(env->program,(yyvsp[-1].val),yyget_lineno(scanner)); }
#line 2299 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 97:
#line 331 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList2(env->program,(yyvsp[-3].val),(yyvsp[-1].val),yyget_lineno(scanner)); }
#line 2305 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 98:
#line 335 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = NULL; }
#line 2311 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 99:
#line 336 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 2317 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 100:
#line 340 "parser/cpal_grammar.y" /* yacc.c:1663  */
    {  (yyval.val) = process_makeState(env,(yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 2323 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 101:
#line 343 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { defType_add_enum(env, Process_State_getTypeID(env->ienv), (yyvsp[0].val)); (yyval.val) = defVar_makeAndDeclareStateDefinition(env,(yyvsp[0].val)); }
#line 2329 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 102:
#line 346 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList1(env->program,(yyvsp[0].val),yyget_lineno(scanner)); }
#line 2335 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 103:
#line 347 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_addListLast(env->program,(yyvsp[-2].val),(yyvsp[0].val),yyget_lineno(scanner)); }
#line 2341 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 104:
#line 351 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList1(env->program,(yyvsp[0].val),yyget_lineno(scanner)); }
#line 2347 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 105:
#line 352 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_addListLast(env->program,(yyvsp[-1].val),(yyvsp[0].val),yyget_lineno(scanner)); }
#line 2353 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 106:
#line 357 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeNode(env->program,BREAK_OP,0,NULL,NULL,yyget_lineno(scanner)); }
#line 2359 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 107:
#line 358 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeNode(env->program,CONTINUE_OP,0,NULL,NULL,yyget_lineno(scanner)); }
#line 2365 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 108:
#line 362 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defIter_makeDeclaration(env,(yyvsp[0].val),(yyvsp[-2].val)); }
#line 2371 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 109:
#line 366 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2377 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 110:
#line 367 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2383 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 111:
#line 368 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2389 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 112:
#line 372 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = NULL; }
#line 2395 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 113:
#line 373 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList1(env->program,(yyvsp[0].val),yyget_lineno(scanner)); }
#line 2401 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 114:
#line 374 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_addListLast(env->program,(yyvsp[-1].val),(yyvsp[0].val),yyget_lineno(scanner)); }
#line 2407 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 115:
#line 378 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defProc_makeTransition(env,ON_OP,AST_getSymbolId((yyvsp[0].val)),(yyvsp[-3].val),NULL,(yyvsp[-1].val)); }
#line 2413 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 116:
#line 379 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defProc_makeTransition(env,ON_OP,AST_getSymbolId((yyvsp[0].val)),(yyvsp[-2].val),NULL,NULL); }
#line 2419 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 117:
#line 380 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defProc_makeTransition(env,AFTER_OP,AST_getSymbolId((yyvsp[0].val)),NULL,(yyvsp[-3].val),(yyvsp[-1].val)); }
#line 2425 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 118:
#line 381 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defProc_makeTransition(env,AFTER_OP,AST_getSymbolId((yyvsp[0].val)),NULL,(yyvsp[-2].val),NULL); }
#line 2431 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 119:
#line 382 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defProc_makeTransition(env,AFTER_OP,AST_getSymbolId((yyvsp[0].val)),(yyvsp[-3].val),(yyvsp[-7].val),(yyvsp[-1].val)); }
#line 2437 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 120:
#line 383 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defProc_makeTransition(env,AFTER_OP,AST_getSymbolId((yyvsp[0].val)),(yyvsp[-2].val),(yyvsp[-6].val),NULL); }
#line 2443 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 121:
#line 387 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 2449 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 122:
#line 391 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeAssignment(env,(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2455 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 123:
#line 392 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeAssignment(env,(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2461 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 124:
#line 396 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defVar_makeInitializer(env,(yyvsp[0].val)); }
#line 2467 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 125:
#line 397 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defVar_makeInitializer(env,(yyvsp[0].val)); }
#line 2473 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 126:
#line 398 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defVar_makeInitializer(env,NULL); }
#line 2479 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 127:
#line 399 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defVar_makeInitializer(env,(yyvsp[-1].val)); }
#line 2485 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 128:
#line 403 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList1(env->program,(yyvsp[0].val),yyget_lineno(scanner)); }
#line 2491 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 129:
#line 404 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_addListLast(env->program,(yyvsp[-2].val),(yyvsp[0].val),yyget_lineno(scanner)); }
#line 2497 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 130:
#line 408 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2503 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 131:
#line 409 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2509 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 132:
#line 410 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defVar_makeInitializer(env,(yyvsp[-1].val)); }
#line 2515 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 133:
#line 411 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = NULL; }
#line 2521 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 134:
#line 415 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2527 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 135:
#line 419 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2533 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 136:
#line 420 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeLogicalOp(env,OR_OP,(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2539 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 137:
#line 424 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2545 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 138:
#line 425 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeLogicalOp(env,AND_OP,(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2551 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 139:
#line 429 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2557 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 140:
#line 430 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeArithmeticOp(env,BITWISE_OR_OP,(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2563 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 141:
#line 434 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2569 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 142:
#line 435 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeArithmeticOp(env,BITWISE_XOR_OP,(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2575 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 143:
#line 439 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2581 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 144:
#line 440 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeArithmeticOp(env,BITWISE_AND_OP,(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2587 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 145:
#line 444 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2593 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 146:
#line 445 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeMultipleEqualityExpression(env,CEQ_OP,(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2599 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 147:
#line 446 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeMultipleEqualityExpression(env,CNE_OP,(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2605 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 148:
#line 450 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2611 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 149:
#line 451 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeLogicalOp(env,CEQ_OP,(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2617 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 150:
#line 452 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeLogicalOp(env,CNE_OP,(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2623 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 151:
#line 456 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2629 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 152:
#line 457 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeMultipleRelationalExpression(env,(yyvsp[-1].ival),(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2635 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 153:
#line 461 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2641 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 154:
#line 462 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeLogicalOp(env,(yyvsp[-1].ival),(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2647 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 155:
#line 466 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2653 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 156:
#line 467 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeArithmeticOp(env,(yyvsp[-1].ival),(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2659 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 157:
#line 471 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2665 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 158:
#line 472 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeArithmeticOp(env,PLUS_OP,(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2671 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 159:
#line 473 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeArithmeticOp(env,MINUS_OP,(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2677 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 160:
#line 477 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2683 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 161:
#line 478 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeArithmeticOp(env,(yyvsp[-1].ival),(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2689 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 162:
#line 482 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2695 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 163:
#line 483 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeArithmeticOp(env,NEG_OP,(yyvsp[0].val),NULL); }
#line 2701 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 164:
#line 484 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeLogicalOp(env,NOT_OP,(yyvsp[0].val),NULL); }
#line 2707 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 165:
#line 485 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeArithmeticOp(env,BITWISE_NOT_OP,(yyvsp[0].val),NULL); }
#line 2713 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 166:
#line 486 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2719 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 167:
#line 490 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2725 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 168:
#line 491 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defBuff_makeArrayCall(env,(yyvsp[-3].val),(yyvsp[-1].val)); }
#line 2731 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 169:
#line 492 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defStmt_makePostSymbolCall(env,(yyvsp[-2].val),(yyvsp[0].val)); }
#line 2737 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 170:
#line 493 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2743 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 171:
#line 497 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2749 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 172:
#line 498 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defVar_makeAccess(env,(yyvsp[0].val));}
#line 2755 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 173:
#line 499 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2761 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 174:
#line 500 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2767 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 175:
#line 501 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2773 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 176:
#line 502 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2779 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 177:
#line 503 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 2785 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 178:
#line 504 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeIntegerNode(env->program,(uint64_t) yyget_lineno(scanner), yyget_lineno(scanner)); }
#line 2791 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 179:
#line 505 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { parser_failure(env, 222, env->pctx->parseFilename, parser_lineno(env), NULL, "Frequency cannot be used in conventional expression\n"); }
#line 2797 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 180:
#line 509 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defFunc_makeFunctionCall(env, (yyvsp[-3].val), (yyvsp[-1].val)); }
#line 2803 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 181:
#line 510 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = builtinMtd_makeCall(env, (yyvsp[-5].val), (yyvsp[-3].val), (yyvsp[-1].val)); }
#line 2809 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 182:
#line 514 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeFieldCall(env, (yyvsp[-2].val), (yyvsp[0].val)); }
#line 2815 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 183:
#line 515 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = defExpr_makeFieldCall(env, (yyvsp[-2].val), (yyvsp[0].val)); }
#line 2821 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 184:
#line 519 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2827 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 185:
#line 520 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2833 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 186:
#line 524 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 2839 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 187:
#line 525 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 2845 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 188:
#line 526 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2851 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 189:
#line 527 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeNode(env->program,WHILE_STATEMENT,0,(yyvsp[-2].val),(yyvsp[0].val),yyget_lineno(scanner)); }
#line 2857 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 190:
#line 528 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeNode(env->program,FOR_STATEMENT,0,AST_makeList3(env->program,(yyvsp[-6].val),(yyvsp[-4].val),(yyvsp[-2].val),yyget_lineno(scanner)),(yyvsp[0].val),yyget_lineno(scanner)); }
#line 2863 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 191:
#line 529 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeNode(env->program,LOOPOVER_OP, 0, (yyvsp[-1].val), (yyvsp[0].val), yyget_lineno(scanner)); defVar_clearLocals(env,AST_makeList1(env->program,(yyvsp[-1].val),yyget_lineno(scanner))); }
#line 2869 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 192:
#line 530 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { parser_failure(env, 50, env->pctx->parseFilename, parser_lineno(env), NULL, "expect ';' after assignment\n"); }
#line 2875 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 193:
#line 531 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { parser_failure(env, 50, env->pctx->parseFilename, parser_lineno(env), NULL, "expect ';' after statement\n"); }
#line 2881 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 194:
#line 534 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeNode(env->program,IF_STATEMENT,0,(yyvsp[-2].val),AST_makeList2(env->program,(yyvsp[0].val),NULL,yyget_lineno(scanner)),yyget_lineno(scanner)); }
#line 2887 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 195:
#line 535 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeNode(env->program,IF_STATEMENT,0,(yyvsp[-4].val),AST_makeList2(env->program,(yyvsp[-2].val),(yyvsp[0].val),yyget_lineno(scanner)),yyget_lineno(scanner)); }
#line 2893 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 196:
#line 536 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeNode(env->program,IF_STATEMENT,0,(yyvsp[-4].val),AST_makeList2(env->program,(yyvsp[-2].val),(yyvsp[0].val),yyget_lineno(scanner)),yyget_lineno(scanner)); }
#line 2899 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 197:
#line 539 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = NULL; }
#line 2905 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 198:
#line 540 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_makeList1(env->program,(yyvsp[0].val),yyget_lineno(scanner)); }
#line 2911 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 199:
#line 541 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = AST_addListLast(env->program,(yyvsp[-2].val),(yyvsp[0].val),yyget_lineno(scanner)); }
#line 2917 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 200:
#line 551 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 2923 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 201:
#line 555 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.ival) = QUEUE_BUFFER; }
#line 2929 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 202:
#line 556 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.ival) = STACK_BUFFER; }
#line 2935 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 203:
#line 557 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.ival) = CHANNEL_BUFFER; }
#line 2941 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 204:
#line 561 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.ival) = LT_OP; }
#line 2947 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 205:
#line 562 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.ival) = GT_OP; }
#line 2953 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 206:
#line 563 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.ival) = CGE_OP; }
#line 2959 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 207:
#line 564 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.ival) = CLE_OP; }
#line 2965 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 208:
#line 568 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.ival) = BITWISE_LEFT_SHIFT_OP; }
#line 2971 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 209:
#line 569 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.ival) = BITWISE_RIGHT_SHIFT_OP; }
#line 2977 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 210:
#line 573 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.ival) = MUL_OP; }
#line 2983 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 211:
#line 574 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.ival) = DIV_OP; }
#line 2989 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 212:
#line 575 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.ival) = MOD_OP; }
#line 2995 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;

  case 213:
#line 579 "parser/cpal_grammar.y" /* yacc.c:1663  */
    { (yyval.val) = (yyvsp[0].val); }
#line 3001 "parser/cpal_grammar.c" /* yacc.c:1663  */
    break;


#line 3005 "parser/cpal_grammar.c" /* yacc.c:1663  */
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
      yyerror (scanner, env, YY_("syntax error"));
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
        yyerror (scanner, env, yymsgp);
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
                      yytoken, &yylval, scanner, env);
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
                  yystos[yystate], yyvsp, scanner, env);
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
  yyerror (scanner, env, YY_("memory exhausted"));
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
                  yytoken, &yylval, scanner, env);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, scanner, env);
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
#line 584 "parser/cpal_grammar.y" /* yacc.c:1907  */

