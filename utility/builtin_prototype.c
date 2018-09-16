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

#include "builtin_prototypes.h"
#include "rAST.h"

AST *builtinMtd_makeCall(parser_Env *env, AST *expr, AST *symbol, AST *arguments)
{
    /* This function creates a node of type AST_CODE_BUILTIN_MTD_CALL
       and fills it with its arguments.

       'expr' is the postfix expression at the left of the builtin
       method call.  'symbol' is the symbol at the right of the dot,
       that is, it is the method selector.  'arguments' is the list of
       arguments of the call.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_BUILTIN_MTD_CALL;
    node->ast_node_specific.builtin_mtd_call.expr = expr;
    node->ast_node_specific.builtin_mtd_call.symbol = symbol;
    node->ast_node_specific.builtin_mtd_call.arguments = arguments;
    return node;
}
