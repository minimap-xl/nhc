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

#include "def_parameter.h"
#include "rAST.h"

AST *defParam_make(
    parser_Env *env, typeId_t typeid, AST *symbol, enum argument_type in_out)
{
    /* This function creates an AST node with code AST_CODE_PARAM and
       saves its arguments into it.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_PARAM;
    node->ast_node_specific.param.typeid = typeid;
    node->ast_node_specific.param.symbol = symbol;
    node->ast_node_specific.param.in_out = in_out;
    return node;
}
