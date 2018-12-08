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

#include <string.h>
#include <mt.h>
#include "mt_private.h"

static void find_node(AST *node, struct mt_cookie *cookie)
{
	if (! node) return;

	/* If the current node has a matching AST node type, then compare
	 * whether it has the matching name. */
	if (node->code == cookie->search_pattern.ast_node_type)
	{
		if (cookie->search_pattern.search_name)
		{
			AST *tmp;
			switch (node->code)
			{
			case AST_CODE_GLOBAL_INSTANCE:
				tmp = node->ast_node_specific.global_instance.instance_name;
				
				/* If we find the process instance with the right name,
				 * return the top level pointer to this AST node. */
				if(strcmp(tmp->ast_node_specific.symbol.text, cookie->search_pattern.search_name)==0)
				{
					cookie->search_pattern.found_node = node;
				}
				else {
				}
				break;

			case AST_CODE_PROC_INSTANCE:
				tmp = node->ast_node_specific.proc_instance.process_type;
				
				/* If we find the subprocess instance with the right
				 * name, return the top level pointer to this AST
				 * node. */
				if(strcmp(tmp->ast_node_specific.symbol.text, cookie->search_pattern.search_name)==0)
				{
					cookie->search_pattern.found_node = node;
				}

				tmp = node->ast_node_specific.proc_instance.instance_name;
				
				/* If we find the subprocess instance with the right
				 * name, return the top level pointer to this AST
				 * node. */
				if(strcmp(tmp->ast_node_specific.symbol.text, cookie->search_pattern.search_name)==0)
				{
					cookie->search_pattern.found_node = node;
				}
				
				break;
				
			case AST_CODE_STATE_MACHINE: 
				tmp = node->ast_node_specific.state_machine.symbol_id;
				
				/* If we find the process definition with the right name,
				 * return the top level pointer to this AST node. */
				if(strcmp(tmp->ast_node_specific.symbol.text, cookie->search_pattern.search_name)==0)
				{
					cookie->search_pattern.found_node = node;
				}
				else {
				}
				break;

			case AST_CODE_VAR_DECL:
				tmp = node->ast_node_specific.var_decl.symbol;
				if(strcmp(tmp->ast_node_specific.symbol.text, cookie->search_pattern.search_name)==0)
				{
					cookie->search_pattern.found_node = node;
				}
				else {
				}
				break;

			case AST_CODE_BUFFER_DECL:
				tmp = node->ast_node_specific.buffer_decl.symbol;
				if(strcmp(tmp->ast_node_specific.symbol.text, cookie->search_pattern.search_name)==0)
				{
					cookie->search_pattern.found_node = node;
				}
				else {
				}
				break;


			case AST_CODE_DATA_TYPE:
				tmp = node->ast_node_specific.type.symbol_id;
				if(strcmp(tmp->ast_node_specific.symbol.text, cookie->search_pattern.search_name)==0)
				{
					cookie->search_pattern.found_node = node;
				}
				else {
				}
				break;

			case AST_CODE_FUNCTION_DEF:
				tmp = node->ast_node_specific.function_def.symbol_id;
				if(strcmp(tmp->ast_node_specific.symbol.text, cookie->search_pattern.search_name)==0)
				{
					cookie->search_pattern.found_node = node;
				}
				else {
				}
				break;

			case AST_CODE_FUNCTION_CALL:
				tmp = node->ast_node_specific.function_call.function_name;
				if(strcmp(tmp->ast_node_specific.symbol.text, cookie->search_pattern.search_name)==0)
				{
					cookie->search_pattern.found_node = node;
				}
				else {
				}
				break;
			
			case AST_CODE_PARAM:
				tmp = node->ast_node_specific.param.symbol;
				if(strcmp(tmp->ast_node_specific.symbol.text, cookie->search_pattern.search_name)==0)
				{
					cookie->search_pattern.found_node = node;
				}
				else {
				}
				break;

			case AST_CODE_ACCESS:
				tmp = node->ast_node_specific.access.symbol;
				if(strcmp(tmp->ast_node_specific.symbol.text, cookie->search_pattern.search_name)==0)
				{
					cookie->search_pattern.found_node = node;
				}
				else {
				}
				break;
			

			default:
				fprintf(stderr, "!!!!!!!! \033[31mfind_node()\033[0m:  Illegal AST node type !!!!!!\n");
				break;
			}
		}
		else
			cookie->search_pattern.found_node = node;	
	}
}

static AST *find(AST *node, struct mt_cookie *cookie)
{
	find_node(node, cookie);
	MT_Recurse(node, find, cookie);

	return node;
}

AST *MT_Find(AST *tree, enum ast_node_code type, char *name)
{
	struct mt_cookie cookie;

	cookie.search_pattern.ast_node_type = type;
	if (name != NULL)
		cookie.search_pattern.search_name = strdup(name);
	else
		cookie.search_pattern.search_name = NULL;
	cookie.search_pattern.found_node = NULL;

	MT_Transform(tree, find, &cookie);
	return cookie.search_pattern.found_node;
}
