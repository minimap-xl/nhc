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

/* This header contains an incomplete (stub) definition of data type
   AST.  It is used to break circular references between the complete
   definition of struct AST_node, in rAST.h and the various data types
   defined in def_... headers.  With this rather classic approach:

   - def_... headers include rAST_stub.h.  This should be enough
     because all they need is AST *.  Being a pointer, it can be
     compiled even without yet knowing the exact structure of AST.

   - rAST.h includes the def_... headers it needs, which also bring in
     the stub definition, and then proceeds to define struct AST_node
     completely.
*/

#ifndef RAST_STUB_H
#define RAST_STUB_H

typedef struct AST_node AST;

/* I: Use a custom data type for a symbol id.  This should make it
   easier to have code that works both with and without symbol
   interning.

   With interning: typedef uint32_t symbolId_t;
   Without interning: typedef AST *symbolId_t;

   Anticipate this type definition here in the stub because some
   prototypes in the def_ headers need it.

   I TBD: For the time being, do without interning, AST_getSymbolId is
   a pass-through and the id of a symbol is the pointer to its AST
   node.  Note that in this way id is not going to be unique.
*/
typedef AST *symbolId_t;

#define NO_SYMBOL_ID (symbolId_t)NULL

#endif
