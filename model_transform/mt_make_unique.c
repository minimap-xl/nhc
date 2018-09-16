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

/* This module implements the MT_Make_Unique function.

   See mt.h for a short description of what it does.
*/

#include <mt.h>
#include "mt_private.h"

struct make_unique_cookie
{
    const char *suffix;
    int count;
};

/* built_unique_name returns a dynamically allocated string, remember
   to free() it when it is no longer needed.  TBD: It does not handle
   malloc() failure.
*/
static char *build_unique_name(const char *base, const char *suffix)
{
    char *unique = malloc(strlen(base) + strlen(suffix) + 1);

    strcpy(unique, base);
    strcat(unique, suffix);
    return unique;
}

static int make_unique(AST *root, AST *node, int depth, void *hl_cookie)
{
    struct make_unique_cookie *c = (struct make_unique_cookie *)hl_cookie;
    AST *symbol = NULL;
    char *old_name;
    char *new_name;

    /* Ignore the node if we are told to */
    if(node->common.ignore)  return 0;

    switch(node->code)
    {
    case AST_CODE_DATA_TYPE:
	/* Get access to the data type name being defined */
	symbol = node->ast_node_specific.type.symbol_id;
	break;

    case AST_CODE_STATE_MACHINE:
	symbol = node->ast_node_specific.state_machine.symbol_id;
	break;

    case AST_CODE_SM_PROTOTYPE:
	symbol = node->ast_node_specific.sm_prototype.sm_name;
	break;

    case AST_CODE_FUNCTION_DEF:
	symbol = node->ast_node_specific.function_def.symbol_id;
	break;

    case AST_CODE_VAR_DECL:
	/* Besides at the top level, AST_CODE_VAR_DECL may also appear
	   elsewhere, for instance, within a process definition.
	   Filter out non-top-level declarations using the depth with
	   respect to the root kindly provided by MT_Apply().  The
	   check is for <=1 to allow a AST_CODE_LIST as a container at
	   the top level.
	*/
	if(depth <= 1)
	    symbol = node->ast_node_specific.var_decl.symbol;
	break;

    case AST_CODE_BUFFER_DECL:
	/* Same as above for AST_CODE_BUFFER_DECL */
	if(depth <= 1)
	    symbol = node->ast_node_specific.buffer_decl.symbol;
	break;

    case AST_CODE_GLOBAL_INSTANCE:
	symbol = node->ast_node_specific.global_instance.instance_name;
	break;

    default:
	break;
    }

    /* Rename only if we found a symbol to work on :) */
    if(symbol)
    {
	assert(symbol->code == AST_CODE_SYMBOL);

	/* Build the unique name */
	old_name = symbol->ast_node_specific.symbol.text;

	new_name = build_unique_name(old_name, c->suffix);

	/* Rename accordingly in the whole tree, starting from the
	   root.  Yes, this is a second-order recursion if you're
	   wondering.  :)
	*/
	MT_Rename(root, old_name, new_name);

	free(new_name);  /* free() must not bomb on a NULL pointer */
	c->count++;
    }

    return 0;
}

int MT_Make_Unique(AST *tree, char *suffix)
{
    struct make_unique_cookie hl_cookie = { .count = 0 };
    char *real_suffix;

    /* Adjust the suffix to make sure it starts with an underscore */
    if(suffix[0] != '_')
    {
	real_suffix = malloc(strlen(suffix)+2);
	strcpy(real_suffix, "_");
	strcat(real_suffix, suffix);
    }
    else
	real_suffix = suffix;

    hl_cookie.suffix = real_suffix;

    /* Ignore the return value of MT_Apply, not significant.  We use
       only one functor for multiple node codes, for simplicity.
    */
    (void)MT_Apply(tree, AST_CODE_DATA_TYPE, NULL, make_unique, &hl_cookie);
    (void)MT_Apply(tree, AST_CODE_STATE_MACHINE, NULL, make_unique, &hl_cookie);
    (void)MT_Apply(tree, AST_CODE_SM_PROTOTYPE, NULL, make_unique, &hl_cookie);
    (void)MT_Apply(tree, AST_CODE_FUNCTION_DEF, NULL, make_unique, &hl_cookie);
    (void)MT_Apply(tree, AST_CODE_VAR_DECL, NULL, make_unique, &hl_cookie);
    (void)MT_Apply(tree, AST_CODE_BUFFER_DECL, NULL, make_unique, &hl_cookie);
    (void)MT_Apply(tree, AST_CODE_GLOBAL_INSTANCE, NULL, make_unique, &hl_cookie);

    if(suffix != real_suffix)  free(real_suffix);
    return hl_cookie.count;
}
