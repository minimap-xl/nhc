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

/* This module implements the MT_Node_Matches_Pattern function.  Most
   of the code is taken from Tingting's ad-hoc implementation in
   mt_find.c with some simplifications because just want to return a
   Boolean indication here.

   See mt.h for a short description of what this function does.
*/

#include <stdlib.h>
#include <string.h>
#include <mt.h>
#include "mt_private.h"

int MT_Node_Matches_Pattern(AST *node, struct mt_cookie *cookie)
{
    int found = 0;

    /* search_pattern.ast_node_type is mandatory and calls for an
       exact match.
    */
    if (node->code == cookie->search_pattern.ast_node_type)
    {
	/* search_pattern.search_name is optional and must be
	   considered only if it is not NULL.
	*/
	if (cookie->search_pattern.search_name)
	{
	    AST *tmp;

	    /* The way search_pattern.search_name is compared with
	       fields in a given node depends on the node code.
	    */
	    switch (node->code)
	    {
	    case AST_CODE_GLOBAL_INSTANCE:
		tmp = node->ast_node_specific.global_instance.instance_name;

		/* Look for a process instance with the right name */
		if(strcmp(tmp->ast_node_specific.symbol.text,
			  cookie->search_pattern.search_name) == 0)
		    found = 1;
		break;

	    case AST_CODE_STATE_MACHINE:
		tmp = node->ast_node_specific.state_machine.symbol_id;

		/* Look for a process definition with the right name */
		if(strcmp(tmp->ast_node_specific.symbol.text,
			  cookie->search_pattern.search_name) == 0)
		    found = 1;
		break;

	    case AST_CODE_VAR_DECL:
		tmp = node->ast_node_specific.var_decl.symbol;

		if(strcmp(tmp->ast_node_specific.symbol.text,
			  cookie->search_pattern.search_name) == 0)
		    found = 1;
		break;

	    case AST_CODE_DATA_TYPE:
		tmp = node->ast_node_specific.type.symbol_id;

		if(strcmp(tmp->ast_node_specific.symbol.text,
			  cookie->search_pattern.search_name) == 0)
		    found = 1;
		break;

	    case AST_CODE_FUNCTION_DEF:
		tmp = node->ast_node_specific.function_def.symbol_id;

		if(strcmp(tmp->ast_node_specific.symbol.text,
			  cookie->search_pattern.search_name) == 0)
		    found = 1;
		break;

	    case AST_CODE_ANNOTATION:
		/* For AST_CODE_ANNOTATION, the comparison is
		   performed on the first symbol of the
		   hierarchical_symbol (a AST_CODE_LIST) attached to
		   the annotation.
		*/
		tmp = node->ast_node_specific.annotation.hierarchical_symbol;
		assert(tmp->code == AST_CODE_LIST);

		tmp = tmp->next;
		assert(tmp->code == AST_CODE_SYMBOL);

		if(strcmp(tmp->ast_node_specific.symbol.text,
			  cookie->search_pattern.search_name) == 0)
		    found = 1;
		break;

	    default:
		/* Do not complain if we are asked to compare against
		   node codes we do not handle.  Return a 'not found'
		   indication.
		*/
		break;
	    }

	}

	else
	    found = 1;
    }

    return found;
}
