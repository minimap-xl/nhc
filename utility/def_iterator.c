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

#include "def_iterator.h"
#include "rAST.h"

/* This function uses the official names of the arguments found in the
   CPAL manual, Section (2.6.5).
*/
AST *defIter_makeDeclaration(parser_Env *env, AST *iterator, AST *collection)
{
    /* This function must create an AST node with code
       AST_CODE_ITERATOR.  The code-specific part of the node comes
       directly from this function's arguments.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_ITERATOR;
    node->ast_node_specific.iterator.iterator = iterator;
    node->ast_node_specific.iterator.collection = collection;
    return node;
}
