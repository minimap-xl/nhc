/* A Bison parser, made by GNU Bison 3.0.5.  */

/* Bison interface for Yacc-like parsers in C

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
#line 41 "parser/cpal_grammar.y" /* yacc.c:1916  */

    AST *        val;
    uint32_t    ival;

#line 136 "parser/cpal_grammar.h" /* yacc.c:1916  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner, parser_Env *env);

#endif /* !YY_YY_PARSER_CPAL_GRAMMAR_H_INCLUDED  */
