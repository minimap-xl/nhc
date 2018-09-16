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

#include <stdlib.h>
#include "parser_error.h"

/* I: TBD: This function is used only for parser error handling.
   Returning a dummy value for now, to silence the compiler.
*/
int parser_lineno(parser_Env *env)
{
    return 0;
}

void parser_failure(parser_Env *env, const uint32_t magic_num, char *file_name, int lineno, void *not_used, char *error_msg, ... )
{
    /* I: Very simple (too simple, probably) implementation, just to
       be aware of errors.
    */
    fprintf(stderr, "parser_failure: %s\n", error_msg);
    exit(EXIT_FAILURE);
}

void parser_warning(char *file_name, int lineno, void *not_used, char *error_msg, char *text)
{
}
