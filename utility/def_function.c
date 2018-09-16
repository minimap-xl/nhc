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

#include "def_function.h"
#include "rAST.h"

AST *defFunc_definePrototype(
    parser_Env *env, symbolId_t function_name, AST *parameters)
{
    /* This function must create an AST node with code
       AST_CODE_PROTOTYPE.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_PROTOTYPE;
    node->ast_node_specific.prototype.function_name = function_name;
    node->ast_node_specific.prototype.parameters = parameters;
    return node;
}

AST *defFunc_define(parser_Env *env, symbolId_t symbol_id, AST *parameter_list, AST *block)
{
    /* This function must create an AST node with code
       AST_CODE_FUNCTION_DEF and fill it with its arguments.

       'symbol_id' is the id of the name of the function being defined,
       'parameter_list' is the list of its formal parameters,
       'block' is the body of the function.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_FUNCTION_DEF;
    node->ast_node_specific.function_def.symbol_id = symbol_id;
    node->ast_node_specific.function_def.parameter_list = parameter_list;
    node->ast_node_specific.function_def.block = block;
    return node;
}

/* Renamed arguments by analogy to defFunc_definePrototype() */
AST *defFunc_makeFunctionCall(
    parser_Env *env, AST *function_name, AST *arguments)
{
    /* This function must create an AST node with code
       AST_CODE_PROTOTYPE.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_FUNCTION_CALL;
    node->ast_node_specific.function_call.function_name = function_name;
    node->ast_node_specific.function_call.arguments = arguments;
    return node;
}
