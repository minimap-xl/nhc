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

/* This module implements the function that dumps a symbol identifier,
   generated and returned by AST_getSymbolId().

   I TBD: Implemented with a recursion because types are represented
   by AST * for the time being.
*/

#include <dump.h>
#include "dump_private.h"


DECL_SPEC_FUNCTOR(dump_symbolId, symbolId_t)
{
    DUMP_PROLOGUE;
    RECURSE(dump_ast_internal, pivot);
    DUMP_EPILOGUE;
}
