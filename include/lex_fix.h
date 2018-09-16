/*+
    NHC - A model transformation framework for CPAL
    Copyright (C) 2018 University of Luxembourg,
      National Research Council of Italy, and
      RealTime-at-Work

    Authors: Tingting Hu, Nicolas Navet,
      Ivan Cibrario Bertolotti,
      Loïc Fejoz, and Lionel Havet

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
+*/

#ifndef LEX_FIX_H
#define LEX_FIX_H

#include "rAST.h"

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif /* YY_TYPEDEF_YY_SCANNER_T */

#ifndef YY_DECL
#define YY_DECL int yylex \
	(YYSTYPE * yylval_param , yyscan_t yyscanner, parser_Env *env)

#endif /* YY_DECL*/

void yyerror(yyscan_t, parser_Env *, const char *);
void scan_string(yyscan_t,  char *);


#endif /* LEX_FIX_H */
