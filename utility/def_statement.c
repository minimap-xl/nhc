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

#include "def_statement.h"
#include "rAST.h"


AST *makeNamedBlock(parser_Env *env, AST *name, AST *scope)
{
    /* This function must create an AST node with code
       AST_CODE_NAMED_BLOCK.  The code-specific part of the node comes
       directly from this function's arguments.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_NAMED_BLOCK;
    node->ast_node_specific.named_block.name = name;
    node->ast_node_specific.named_block.scope = scope;
    return node;
}

AST *defStmt_makePostSymbolCall(parser_Env *env, AST *expr, AST *symbol)
{
    /* This function must create an AST node with code
       AST_CODE_POST_SYMBOL_CALL.  The code-specific part of the node
       comes directly from this function's arguments.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_POST_SYMBOL_CALL;
    node->ast_node_specific.post_symbol_call.expr = expr;
    node->ast_node_specific.post_symbol_call.symbol = symbol;
    return node;
}
