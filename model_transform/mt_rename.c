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

/* This module implements the MT_Rename function.

   See mt.h for a short description of what it does.
*/

#include <string.h>
#include <mt.h>
#include "mt_private.h"

static void rename_node(AST *node, struct mt_cookie *cookie)
{
    /* No need to intercept NULL pointers here because it is now done
       in do_rename().
    */
    switch(node->code)
    {
    case AST_CODE_SYMBOL:
	if(strcmp(node->ast_node_specific.symbol.text, cookie->data.old) == 0)
	{
	    free(node->ast_node_specific.symbol.text);
	    node->ast_node_specific.symbol.text = strdup(cookie->data.new);
	}
	break;

    default:
	break;
    }
}

/* See below for a not-so-short and not-so-clear description of what
   these functions do.
*/
static int is_name_defined_in(AST *node, const char *name)
{
    AST *cursor, *symbol, *var_decl;

    /* Parameter lists and argument declarations may be empty.  In
       this case, this function receives a NULL pointer.  In this
       case, return false because an empty list does not define
       anything.  If node is not NULL, it must be an AST_CODE_LIST.
    */
    if(!node)  return 0;
    assert(node->code == AST_CODE_LIST);

    cursor = node->next;
    while(cursor)
    {
	switch(cursor->code)
	{
	case AST_CODE_PARAM:
	    symbol = cursor->ast_node_specific.param.symbol;
	    assert(symbol->code == AST_CODE_SYMBOL);

	    if(strcmp(symbol->ast_node_specific.symbol.text, name) == 0)
		return 1;
	    break;

	case AST_CODE_VAR_DECL:
	    symbol = cursor->ast_node_specific.var_decl.symbol;
	    assert(symbol->code == AST_CODE_SYMBOL);

	    if(strcmp(symbol->ast_node_specific.symbol.text, name) == 0)
		return 1;
	    break;

	case AST_CODE_BUFFER_DECL:
	    /* This is a AST_CODE_BUFFER_DECL */
	    symbol = cursor->ast_node_specific.buffer_decl.symbol;
	    assert(symbol->code == AST_CODE_SYMBOL);

	    if(strcmp(symbol->ast_node_specific.symbol.text, name) == 0)
		return 1;
	    break;

	case AST_CODE_PROC_VAR:
	    /* These are the same two cases as above, but wrapped in
	       an AST_CODE_PROC_VAR.  This happens then the
	       declarations are at the top level of a process
	       definition.
	    */
	    var_decl = cursor->ast_node_specific.proc_var.decl;
	    assert(var_decl->code == AST_CODE_VAR_DECL
		   || var_decl->code == AST_CODE_BUFFER_DECL);

	    if(var_decl->code == AST_CODE_VAR_DECL)
		symbol = var_decl->ast_node_specific.var_decl.symbol;
	    else
		symbol = var_decl->ast_node_specific.buffer_decl.symbol;

	    assert(symbol->code == AST_CODE_SYMBOL);

	    if(strcmp(symbol->ast_node_specific.symbol.text, name) == 0)
		return 1;
	    break;

	default:
	    /* Other kinds of node don't define anything, keep going */
	    break;
	}

	cursor = cursor->next;
    }

    /* Return 'not defined' if we scanned the whole list without
       finding a match.
    */
    return 0;
}

static int name_has_been_shadowed(AST *node, const char *name)
{
    int shadowed;

    switch(node->code)
    {
    case AST_CODE_STATE_MACHINE:
	shadowed =
	    is_name_defined_in(
		node->ast_node_specific.state_machine.var_decl_list, name)
	    || is_name_defined_in(
		node->ast_node_specific.state_machine.parameter_list, name);
	break;

    case AST_CODE_FUNCTION_DEF:
	shadowed =
	    is_name_defined_in(
		node->ast_node_specific.function_def.parameter_list, name);
	break;

    case AST_CODE_STATEMENT:
	shadowed =
	    node->ast_node_specific.statement.type == BLOCK_STATEMENT
	    && is_name_defined_in(
		node->ast_node_specific.statement.part1, name);
	break;

    default:
	shadowed = 0;
	break;
    }

    return shadowed;
}

static AST* do_rename(AST *node, struct mt_cookie *cookie)
{
    /* Intercept NULL pointers that may come in during the recursive
       descent
    */
    if(! node) return node;

    /* Local rename, consider AST_CODE_SYMBOL nodes,
       ignore all the others
    */
    rename_node(node, cookie);

    /* In order to consider shadowing of variable names, we must
       consider the following cases that may contain a redefinition of
       the name we are looking for, and hence, shadow it.  Parameter
       definitions have the same effect as variable definitions from
       the point of view of shadowing.

       1) .var_decl_list and .parameter_list of a struct
       tree_state_machine (variable declarations and parameter list of
       a process definition)

       2) .parameter_list of a struct tree_function_def (parameter
       list of a function definition)

       3) .part1 of a struct tree_statement with .type ==
       BLOCK_STATEMENT (variable declarations within a named or
       unnamed scope).  This includes the case of outermost variable
       declarations within a function definition, which are attached
       to the outermost scope of the function.  Notice this is
       asymmetric with respect to a process definition, in which
       outermost variable declarations are handled in a special way,
       see case 1).

       These cases must be handled as follows:

       1) When looking at a AST_CODE_STATE_MACHINE, look in
       .var_decl_list and .parameter_list; abort the recursion when
       finding a match.  If the recursion proceeds, it will perform
       the rename operation also on .var_decl_list and
       .parameter_list, which is harmless if we are renaming a
       non-shadowed variable, and is what we want if we are renaming a
       data type that might be used there.

       2) When looking at a AST_CODE_FUNCTION_DEF, look in
       .parameter_list and abort the recursion when finding a match.
       If the recursion proceeds, it will descend into the outermost
       scope of the function definition and check local declarations
       according to case 3).

       3) When looking at a AST_CODE_STATEMENT with .type ==
       BLOCK_STATEMENT, look in .part1 and abort the recursion when
       finding a match.

       We don't have to worry about data type shadowing, because it
       may not happen in CPAL.  enum and struct definitions may only
       be at the top level.

       Structure of the AST parts containing variable or parameter
       definitions is as follows.  This affects how the "name lookup"
       function mentioned above must be written.  There are two cases:

       a) .parameter_list (the structure is the same for both process
       and function definitions): AST_CODE_LIST of AST_CODE_PARAM
       whose .symbol points to a AST_CODE_SYMBOL that holds the name
       in .text.

       b) .var_decl_list: AST_CODE_LIST of
       AST_CODE_PROC_VAR, which can point to:

       b.1) An AST_CODE_VAR_DECL whose .symbol points to a
       AST_CODE_SYMBOL that holds the name in .text.  In the
       AST_CODE_VAR_DECL, .op can be VARIABLE_DECL_OP or
       CONSTANT_DECL_OP but they are the same for us.

       b.2) An AST_CODE_BUFFER_DECL not handled for now. (TBD)

       c) .part1: same structure as above, but without the
       AST_CODE_PROC_VAR wrapper.

       We can write a generic function that scans a AST_CODE_LIST and
       handles both AST_CODE_PARAM and AST_CODE_PROC_VAR within it.
    */
    if(!name_has_been_shadowed(node, cookie->data.old))
	MT_Recurse(node, do_rename, cookie);

    /* rename() always returns the same 'node' it got as input,
       because it works in place and does not duplicate anything.
    */
    return node;
}

void MT_Rename(AST *tree, char *old, char *new)
{
    struct mt_cookie cookie;

    /* In this case, we must store 'old' and 'new' into the cookie
       before we begin the recursive descent.  strdup() them, just to
       be sure.
    */
    cookie.data.old = strdup(old);
    cookie.data.new = strdup(new);

    (void)MT_Transform(tree, do_rename, &cookie);

    /* Remember to free what we allocated above */
    free(cookie.data.old);
    free(cookie.data.new);
}
