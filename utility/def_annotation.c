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

#include "def_annotation.h"
#include "rAST.h"

AST *defineAnnotation(
    parser_Env *env, AST *hierarchical_symbol, AST *scope)
{
    /* This function creates an AST node with code AST_CODE_ANNOTATION
       and saves its arguments into it.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_ANNOTATION;
    node->ast_node_specific.annotation.hierarchical_symbol
	= hierarchical_symbol;
    node->ast_node_specific.annotation.scope = scope;
    return node;
}
