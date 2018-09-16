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

/* This module implements the MT_Recurse function.

   See mt_private.h for a short description of what it does.
*/

#include <assert.h>
#include <mt.h>
#include "mt_private.h"

/* Apply trans_f to n, passing the cookie */
#define A_TRANS_F(n)  (n) = trans_f((n), cookie)

void MT_Recurse(AST *node, mt_trans_f trans_f, struct mt_cookie *cookie)
{
    /* Neutralize NULL pointers in a centralized way, unlike in the
       dumper.
    */
    if(! node) return;

    switch(node->code)
    {
    case AST_CODE_LIST:
    {
	AST *header = node;
	AST *cursor = node->next;
	AST *new_cursor;

	while(cursor)
	{
	    /* Apply trans_f and update at cursor position */
	    new_cursor = trans_f(cursor, cookie);
	    node->next = new_cursor;

	    /* If cursor was at the tail, update the tail as well */
	    if(header->ast_node_specific.list.tail == cursor)
		header->ast_node_specific.list.tail = new_cursor;

	    node = node->next;
	    cursor = node->next;
	}

	break;
    }

    case AST_CODE_VAR_DECL:
	A_TRANS_F(node->ast_node_specific.var_decl.typeid);
	A_TRANS_F(node->ast_node_specific.var_decl.symbol);
	A_TRANS_F(node->ast_node_specific.var_decl.initializer);
	break;

    case AST_CODE_SYMBOL:
	break;

    case AST_CODE_INITIALIZER:
	A_TRANS_F(node->ast_node_specific.initializer.initializer_element);
	break;

    case AST_CODE_FREQUENCY:
	break;

    case AST_CODE_LOGICAL_OP:
    case AST_CODE_ARITHMETIC_OP:
    case AST_CODE_MULTI_EQ_OP:
    case AST_CODE_MULTI_REL_OP:
	A_TRANS_F(node->ast_node_specific.expression.left);
	A_TRANS_F(node->ast_node_specific.expression.right);
	break;

    case AST_CODE_ARRAY_CALL:
	A_TRANS_F(node->ast_node_specific.array_call.array);
	A_TRANS_F(node->ast_node_specific.array_call.index);
	break;

    case AST_CODE_POST_SYMBOL_CALL:
	A_TRANS_F(node->ast_node_specific.post_symbol_call.expr);
	A_TRANS_F(node->ast_node_specific.post_symbol_call.symbol);
	break;

    case AST_CODE_TIME_LITERAL:
	break;

    case AST_CODE_ACCESS:
	A_TRANS_F(node->ast_node_specific.access.symbol);
	break;

    case AST_CODE_INTEGER:
	break;

    case AST_CODE_STRING:
	break;

    case AST_CODE_LABEL_STRING:
	break;

    case AST_CODE_FLOAT:
	break;

    case AST_CODE_BOOLEAN:
	break;

    case AST_CODE_PROTOTYPE:
	A_TRANS_F(node->ast_node_specific.prototype.function_name);
	A_TRANS_F(node->ast_node_specific.prototype.parameters);
	break;

    case AST_CODE_STATEMENT:
	A_TRANS_F(node->ast_node_specific.statement.part1);
	A_TRANS_F(node->ast_node_specific.statement.part2);
	break;

    case AST_CODE_NAMED_BLOCK:
	A_TRANS_F(node->ast_node_specific.named_block.name);
	A_TRANS_F(node->ast_node_specific.named_block.scope);
	break;

    case AST_CODE_NAMED_BLOCK_DEF:
	A_TRANS_F(node->ast_node_specific.named_block_def.symbol);
	break;

    case AST_CODE_PARAM:
	A_TRANS_F(node->ast_node_specific.param.typeid);
	A_TRANS_F(node->ast_node_specific.param.symbol);
	break;

    case AST_CODE_BUFFER:
	/* Although AST_CODE_BUFFER cannot appear at the top level,
	   we may encounter it anyway.
	*/
	A_TRANS_F(node->ast_node_specific.buffer.type_spec);
	A_TRANS_F(node->ast_node_specific.buffer.size);
	break;

    case AST_CODE_BUFFER_DECL:
	A_TRANS_F(node->ast_node_specific.buffer_decl.typeid);
	A_TRANS_F(node->ast_node_specific.buffer_decl.symbol);
	A_TRANS_F(node->ast_node_specific.buffer_decl.initializer);
	break;

    case AST_CODE_ITERATOR:
	A_TRANS_F(node->ast_node_specific.iterator.collection);
	A_TRANS_F(node->ast_node_specific.iterator.iterator);
	break;

    case AST_CODE_ASSIGNMENT:
	A_TRANS_F(node->ast_node_specific.assignment.left);
	A_TRANS_F(node->ast_node_specific.assignment.right);
	break;

    case AST_CODE_FUNCTION_CALL:
	A_TRANS_F(node->ast_node_specific.function_call.function_name);
	A_TRANS_F(node->ast_node_specific.function_call.arguments);
	break;

    case AST_CODE_ANNOTATION:
	A_TRANS_F(node->ast_node_specific.annotation.hierarchical_symbol);
	A_TRANS_F(node->ast_node_specific.annotation.scope);
	break;

    case AST_CODE_DATA_TYPE:
	A_TRANS_F(node->ast_node_specific.type.symbol_id);
	A_TRANS_F(node->ast_node_specific.type.symbol_list);
	break;

    case AST_CODE_FIELD:
	A_TRANS_F(node->ast_node_specific.field.type_spec);
	A_TRANS_F(node->ast_node_specific.field.struct_field);
	break;

    case AST_CODE_BUILTIN_MTD_CALL:
	A_TRANS_F(node->ast_node_specific.builtin_mtd_call.expr);
	A_TRANS_F(node->ast_node_specific.builtin_mtd_call.symbol);
	A_TRANS_F(node->ast_node_specific.builtin_mtd_call.arguments);
	break;

    case AST_CODE_FIELD_CALL:
	A_TRANS_F(node->ast_node_specific.field_call.expr);
	A_TRANS_F(node->ast_node_specific.field_call.field);
	break;

    case AST_CODE_FUNCTION_DEF:
	A_TRANS_F(node->ast_node_specific.function_def.symbol_id);
	A_TRANS_F(node->ast_node_specific.function_def.parameter_list);
	A_TRANS_F(node->ast_node_specific.function_def.block);
	break;

    case AST_CODE_STATE_MACHINE:
	A_TRANS_F(node->ast_node_specific.state_machine.symbol_id);
	A_TRANS_F(node->ast_node_specific.state_machine.parameter_list);
	A_TRANS_F(node->ast_node_specific.state_machine.subprocess_list);
	A_TRANS_F(node->ast_node_specific.state_machine.var_decl_list);
	A_TRANS_F(node->ast_node_specific.state_machine.common_block);
	A_TRANS_F(node->ast_node_specific.state_machine.state_list);
	A_TRANS_F(node->ast_node_specific.state_machine.finally_block);
	break;

    case AST_CODE_PROC_VAR:
	A_TRANS_F(node->ast_node_specific.proc_var.decl);
	break;

    case AST_CODE_PROC_INSTANCE:
	A_TRANS_F(node->ast_node_specific.proc_instance.process_type);
	A_TRANS_F(node->ast_node_specific.proc_instance.instance_name);
	break;

    case AST_CODE_STATE_DEF:
	A_TRANS_F(node->ast_node_specific.state_def.state_name);
	break;

    case AST_CODE_STATE:
	A_TRANS_F(node->ast_node_specific.state.state_name);
	A_TRANS_F(node->ast_node_specific.state.state_block);
	A_TRANS_F(node->ast_node_specific.state.triggers_list);
	break;

    case AST_CODE_TRANSITION:
	A_TRANS_F(node->ast_node_specific.transition.transition_condition);
	A_TRANS_F(node->ast_node_specific.transition.time_elapsed);
	A_TRANS_F(node->ast_node_specific.transition.transition_code);
	A_TRANS_F(node->ast_node_specific.transition.symbol_id);
	break;

    case AST_CODE_GLOBAL_INSTANCE:
	A_TRANS_F(node->ast_node_specific.global_instance.process_type);
	A_TRANS_F(node->ast_node_specific.global_instance.instance_name);
	A_TRANS_F(node->ast_node_specific.global_instance.time_trigger);
	A_TRANS_F(node->ast_node_specific.global_instance.cond_trigger);
	A_TRANS_F(node->ast_node_specific.global_instance.argument_list);
	break;

    case AST_CODE_SM_PROTOTYPE:
	A_TRANS_F(node->ast_node_specific.sm_prototype.sm_name);
	A_TRANS_F(node->ast_node_specific.sm_prototype.parameters);
	break;

    default:
	/* Something must be missing above */
	assert(0);
	break;
    }
}
