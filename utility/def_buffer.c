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

#include "def_buffer.h"
#include "rAST.h"

AST *defBuff_makeDefinition(
    parser_Env *env, typeId_t typeid, AST *symbol,
    AST *size, AST *initializer, bool constant)
{
    /* This function creates a node with code AST_CODE_BUFFER_DECL and
       fills it with its arguments.

       Notes: 'typeid' identifies a AST_CODE_BUFFER (actually, it
       points at its AST as long as we don't have interning), 'size'
       is the same as 'size' in 'typeid' by construction.  See, for
       instance, cpal_grammar.y:259, namely the repetition of $6 in
       the calls to both defType_getBuffer() and
       defBuff_makeDefinition().
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_BUFFER_DECL;
    node->ast_node_specific.buffer_decl.typeid = typeid;
    node->ast_node_specific.buffer_decl.symbol = symbol;
    node->ast_node_specific.buffer_decl.size = size;
    node->ast_node_specific.buffer_decl.initializer = initializer;
    node->ast_node_specific.buffer_decl.constant = constant;
    return node;
}

AST *defBuff_makeArrayCall(parser_Env *env, AST *array, AST *index)
{
    /* This function must create an AST node with code
       AST_CODE_ARRAY_CALL.  The code-specific part of the node comes
       directly from this function's arguments.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_ARRAY_CALL;
    node->ast_node_specific.array_call.array = array;
    node->ast_node_specific.array_call.index = index;
    return node;
}
