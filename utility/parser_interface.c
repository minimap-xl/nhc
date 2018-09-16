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

#include "parser_interface.h"

void parser_new_coment(parser_Env *env)
{
}


void parser_close_coment(parser_Env *env)
{
}

void parser_add_to_comment(parser_Env *env, char *comment)
{

}

/* This function links the sub-AST corresponding to an
   external_definition in the grammar to the environment, in order to
   make the external_definition accessible from elsewhere after
   parsing.  May be called multiple times in sequence if the source
   file contains multiple external_definitions (of different types). 
*/
void parser_add_external_definition(parser_Env *env, AST *include_node)
{
	/*  I: This is one of the use of the parser environment: make data
       structures built during parsing accessible after parsing.
       yyparse() by itself only returns a success/failure status code
       and nothing else.  In our case, we need the AST as a minimum,
       plus maybe the symbol tables, and so on and so forth.
    */
	AST *list; 

	if(env->program->root == NULL) {
		list = AST_makeList1(env->program, include_node, 0);
		env->program->root = list;
	}
	else
	{
		AST_addListLast(env->program, env->program->root, include_node, 0);
	}

	/* The following can be used to quick debug a single defiition by
	 * simply treating it as the program root. */ 

    /* env->program->root = include_node; */
}
