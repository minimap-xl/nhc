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

#include <ft.h>
#include <dump.h>

/* This function expands the Replica_In and Replica_Out data structure
 * in the NVP skeleton, according to the parameter list of a process
 * definition. in_out specifies whether we are interested in the input
 * parameter or the output parameter. ft_tree is for future use. It
 * can be removed, if not needed. */
void expand_Replica_INOUT(AST *param_list, AST *replica_inout, enum argument_type in_out, AST *ft_tree)
{
	if (!param_list) return;

	AST *current = param_list->next;
	AST *default_field = replica_inout->ast_node_specific.type.symbol_list->next;

	bool default_field_removed = false; 

	/* Walk through the parameter list, look for the parameter with
	 * the right input or output type, and build a field for the
	 * Replica_In or Replica_Out data structure. */
	while ((current != NULL))
	{
		if (current->ast_node_specific.param.in_out == in_out)
		{
			typeId_t type_spec = MT_Dup(current->ast_node_specific.param.typeid);

			/* The parameter name will become the field name.*/
			AST *struct_field = MT_Dup(current->ast_node_specific.param.symbol);

			AST *new_field = defType_makeField(NULL, type_spec, struct_field);
			
			/* In the NVP sketelon, there is a default field for both
			 * Replica_In and Replica_Out data structure as a
			 * placeholder. They are there just to be compliant with
			 * the CPAL grammar so that even the skeleton itself is
			 * syntatic correct. It needs to be removed after we build
			 * new field for the data structure. */
			if(!default_field_removed)
			{
				/* adjust the head and tail of field list of the
				 * replica_inout data structure */
				new_field->next = default_field->next;
				replica_inout->ast_node_specific.type.symbol_list->next = new_field;
				replica_inout->ast_node_specific.type.symbol_list->ast_node_specific.list.tail = new_field;
				default_field_removed = true;

				MT_Free(default_field);
			}
			else
			{
				AST_addListLast(NULL, replica_inout->ast_node_specific.type.symbol_list, new_field, 0);
			}
			
			current = current->next;
		}
		else
			/* If the input/output type doesn't match, keep moving
			 * along the parameter list. */
			current = current->next;	
	}
}

/* This function expands the parameter list of the
 * encapsulate_inputs(), encapsulate_outputs(), unfold_inputs() and
 * unfold_outputs() functions in the NVP skeleton, according to the
 * parameter list of the original process definition. in_out specifies
 * whether we are interested in the input parameter or output
 * parameter. encap_unfold indicates whether it is for encapsulating
 * or unfolding function.  If it is encapsulating, the original
 * input/output parameters will be encapsulated in
 * Replica_In/Replica_Out. In both cases they are input to the
 * encapsulate_xxx functions. If it is unfolding, the original
 * input/output parameters will be unfolded from
 * Replica_In/Replica_Out. In both cases, they are output for the
 * unfold_xxx functions.  */
void encap_unfold_INOUT_param(AST *source_list, AST *dest_list, enum argument_type in_out, enum func_kind encap_unfold, AST *ft_tree)
{
	AST *current =  source_list->next;
	bool default_field_removed = false;
	AST *previous_node;
	AST *default_input_param = NULL;
	AST *cursor;
    /* struct dump_opts dump_opts = { .max_depth = 100 }; */

	if (!source_list) return;

	/* Locate the default input/output parameter in the dest_list
	 * according to in_out. */
	AST *tmp = dest_list->next;
	previous_node = dest_list;
	while (tmp != NULL)
	{
		/* If it is for encapsulate_inputs/outputs, the default
		 * parameter is the input parameter. */
		if (encap_unfold == ENCAPSULATE)
		{
			if (tmp->ast_node_specific.param.in_out == ArgInType)
			{
				default_input_param = tmp;
				break;
			}
		}
		/* If it is for unfold_inputs/outputs, the default
		 * parameter is the output parameter. */
		else if (encap_unfold == UNFOLD)
		{
			if (tmp->ast_node_specific.param.in_out == ArgOutType)
			{
				default_input_param = tmp;
				break;
			}
		}
				
		tmp = tmp->next;
		previous_node = previous_node->next;
	}

	/* walking through the source parameter list, and update the
	 * destination list accordingly */
	while (current != NULL)
	{
		if (current->ast_node_specific.param.in_out == in_out)
		{
			/* build a AST parameter node */
			AST *new_param_node =  MT_Dup(current);
			/* When we are encapsulating input or output parameter into
			 * Replica_IN and Replica_Out, they all become input parameter
			 * of the encapsulate_input() and encapsulate_output()
			 * function of the target NVP model.*/
			if (encap_unfold == ENCAPSULATE)
				new_param_node->ast_node_specific.param.in_out = ArgInType;
			else
				new_param_node->ast_node_specific.param.in_out = ArgOutType;

			new_param_node->next=NULL;
			
			/* Append after the default field. */
			if (!default_field_removed)
			{
				/* If the default field is at the head. */
				if(dest_list->next == default_input_param)
				{
					dest_list->next = new_param_node;
					new_param_node->next = default_input_param->next;
				}
				/* If the default field is at the tail. */
				if(dest_list->ast_node_specific.list.tail == default_input_param)
				{
					previous_node->next = new_param_node;
					
					/* Update the tail. */
					dest_list->ast_node_specific.list.tail = new_param_node;
				}
				
				cursor = new_param_node;
				default_field_removed = true;

				MT_Free(default_input_param);
			}
			else
			{
				/* Insert the new parameter node in the dest_list. */
				new_param_node->next = cursor->next;
				cursor->next = new_param_node;
				cursor = new_param_node;
			}
		}
		current = current->next;
	}

}

/* This function expands the function body of the
 * encapsulate_inputs(), encapsulate_outputs(), unfold_inputs(),
 * unfold_outputs() functions. In particular, it extends the statement
 * list in the function body based on the parameter list of the
 * original process. in_out specifies whether it is for xxx_inputs()
 * functions or xxx_outputs() functions. The way to expand the
 * statement list is to keep appending after the default statement.
 * When done with expansion, remove the default statement. */
void encap_unfold_INOUT_body(AST *param_list, AST *statement_list, enum argument_type in_out, AST *ft_tree)
{

	if (!param_list) return;

	AST *current = param_list->next;
	AST *default_statement = statement_list->next;

	while(current != NULL)
	{
		/* If the current parameter matches the input/output type,
		 * then build new statement. */ 
		if (current->ast_node_specific.param.in_out == in_out)
		{
			/* Dump statement of the same format and update it
			 * according to the current parameter name. */
			AST *new_statement = MT_Dup(default_statement);
			new_statement->next = NULL;

			char *param_name = current->ast_node_specific.param.symbol->ast_node_specific.symbol.text;
			if (in_out == ArgInType)
				MT_Rename(new_statement, "a", param_name);
			else
				MT_Rename(new_statement, "sum", param_name);
			
			/* Apend after the default statement. */
			AST_addListLast(NULL, statement_list, new_statement, 0);
		}

		current = current->next;
	}

	/* when done with the parameter list of the right type
	 * (input/output), remove the default statement. */
	statement_list->next = default_statement->next;

	MT_Free(default_statement);
}

/* This function expands the comp_ballot() function by extending the
 * if condition in the function body, based on the output parameter in
 * the parameter list. This is because this function will be used by
 * the voter to compare the results geneated by different member
 * versions. */
void expand_comp_ballot(AST *param_list, AST *comp_ballot_func, AST *ft_tree)
{
	if (NULL == param_list || NULL == comp_ballot_func) return;

	/* move to the function body, which contains the block statement*/
	AST *func_body = comp_ballot_func->ast_node_specific.function_def.block; 
	AST *default_condition = NULL;

	/* Find where the logic expression of the if statement is. */
	default_condition = MT_Find(func_body, AST_CODE_LOGICAL_OP, NULL);
	if (!default_condition) return;

	AST *extended_condition = default_condition;
	AST *current = param_list->next;
	bool default_field_removed = false;
	char *new_name;
	char *param_name;
	AST *new_expression;
	
	/* Walk through the parameter list and identify the output
	 * parameters. Because the ballot only concerns the output
	 * value. */
	while (current != NULL)
	{
		if (current->ast_node_specific.param.in_out == ArgOutType)
		{
			/* keep recode of the name of the output paramenter. It
			 * will be used to rename the if condition. */
			param_name = current->ast_node_specific.param.symbol->ast_node_specific.symbol.text;
				
			if(!default_field_removed)
			{
				/* If the default expression is not updated, rename
				 * the default expression with the parameter name. */
				MT_Rename(default_condition, "sum", param_name);
				default_field_removed = true;
				/* Since the name in the default condition changed,
				 * this is used to help when expanding the if
				 * condition like done in the else branch in the
				 * following. */
				new_name = strdup(param_name);
			}
			else 
			{
				/* Dup the default condtion, rename and build a new
				 * expression. */
				new_expression = MT_Dup(default_condition);
				new_expression->next = NULL;

				MT_Rename(new_expression, new_name, param_name);

				/* Concatenate the old condition with the new expression
				 * to build the new condition for the if statement. */
				extended_condition = defExpr_makeLogicalOp(NULL, AND_OP, extended_condition, new_expression);
			}
		}

		/* Move to the next element in the list. */
		current = current->next;
	}
	
	/* Locate where the if statement is, and link if condition with
	 * the new condition. */
    AST *if_statement = func_body->ast_node_specific.statement.part2->next;
	if_statement->ast_node_specific.statement.part1 = extended_condition;

	/* Free dynamic allocated memory. */
	free(new_name);
}

/* Expand the initiator according to the input parameter list of the
 * original process, since initiator is mainly responsible for pushing
 * inputs to the member versions. */
void expand_process_param_list(AST *param_list, AST *initiator_voter, enum argument_type in_out, AST *ft_tree)
{
	if (!param_list || !initiator_voter) return;

	AST *proc_param_list = initiator_voter->ast_node_specific.state_machine.parameter_list;
	AST *default_param = NULL;

	if(in_out == ArgInType)
		default_param = MT_Find(proc_param_list, AST_CODE_PARAM, "a");
	else
		default_param = MT_Find(proc_param_list, AST_CODE_PARAM, "sum");

	AST *current = param_list->next;
	AST *new_param = NULL;
	bool default_field_removed = false;

	while(current != NULL)
	{
		if (current->ast_node_specific.param.in_out == in_out)
		{
			if (!default_field_removed)
			{
				char *default_type_name = default_param->ast_node_specific.param.typeid->ast_node_specific.symbol.text;
				char *new_type_name = current->ast_node_specific.param.typeid->ast_node_specific.symbol.text;
				MT_Rename(default_param, default_type_name, new_type_name);

				char *default_param_name = default_param->ast_node_specific.param.symbol->ast_node_specific.symbol.text;
				char *new_param_name = current->ast_node_specific.param.symbol->ast_node_specific.symbol.text;
				MT_Rename(default_param, default_param_name, new_param_name);
				
				default_field_removed = true;
			}
			else
			{
				new_param = MT_Dup(current);

				new_param->next = default_param->next;
				default_param->next = new_param;
				default_param = default_param->next;
			}
		}


		current = current->next;
	}
	

}

/* This function is used to expand the function calls of
 * encapsulate_inputs(), unfold_outputs() in the body of the process
 * definition for the initiator and the voter. It is done based on the
 * input/output parameters in the parameter list of the original
 * process. IMPORTANT_UPDATES: this function can be used to expand the
 * function calls of unfold_inputs(), encapsulate_outputs() in the
 * member version as well.*/

void expand_process_func_call(AST *param_list, AST *initiator_voter, enum argument_type in_out, AST *ft_tree)
{
	if (NULL == param_list || NULL == initiator_voter) return;

	AST *default_argument = NULL;
	AST *new_argument = NULL;
	bool default_field_removed = false;
	char *default_argu_name;
	char *new_argu_name;

	/* Locate the input/output placeholder in the process definition
	 * body of the initiator or the voter. */
	if(in_out == ArgInType)
		default_argument = MT_Find(initiator_voter, AST_CODE_ACCESS, "a");
	else
		default_argument = MT_Find(initiator_voter, AST_CODE_ACCESS, "sum");

	if (!default_argument)
	{
		fprintf(stderr, "expand_process_func_call(): can not find the default argument\n");
		return;
	}

	AST *current = param_list->next;

	/* Walk through the parameter list, extend the argument using the
	 * same name as the input/output parameter. For the placeholder,
	 * it will be renamed and instead for the following argument, a
	 * new argument node will be created and appended after the
	 * placeholder. */
	while(current != NULL)
	{
		
		if (current->ast_node_specific.param.in_out == in_out)
		{
			default_argu_name = default_argument->ast_node_specific.access.symbol->ast_node_specific.symbol.text;
			new_argu_name = current->ast_node_specific.param.symbol->ast_node_specific.symbol.text;

			if (!default_field_removed)
			{
				MT_Rename(default_argument, default_argu_name, new_argu_name);

				default_argu_name = strdup(new_argu_name);

				default_field_removed = true;
			}
			else 
			{
				new_argument = MT_Dup(default_argument);
				
				MT_Rename(new_argument, default_argu_name, new_argu_name);

				new_argument->next = default_argument->next;
				default_argument->next = new_argument;
				default_argument = default_argument->next;

			}
		}
		
		current = current->next;
	}
	
}

/* This function expands the initiator and voter process instances in
 * the NVP skeleton, based on the argument list of the original
 * process instance, and the parameter list of the process
 * definition. Because in the argument list of the original process
 * instance, there is no knowledge we can explore to distinguish
 * between input and output argument. The initiator will inherit the
 * activation condition (time trigger and the condition
 * trigger). Initiator will inherit the input arguments, whereas the
 * voter inherits the output arguments. */
void expand_initiator_instance(AST *original_instance, AST *initiator, AST *param_list, enum argument_type in_out, AST *ft_tree)
{
	AST *inherited_time_trigger;
	AST *inherited_cond_trigger;

	AST *default_time_trigger;
	AST *default_cond_trigger;

	AST *original_argument;

	AST *initiator_argument_list;
	AST *default_argument;

	AST *current;
	AST *new_argument;
	AST *cursor;

	if (NULL == original_instance || NULL == initiator || NULL == param_list) return;

	/* Only the initiator will inherit the activation condition from
	 * the original process.  The voter is purely event-triggered. */
	if (in_out == ArgInType)
	{
		inherited_time_trigger = MT_Dup(original_instance->ast_node_specific.global_instance.time_trigger);
		inherited_cond_trigger = MT_Dup(original_instance->ast_node_specific.global_instance.cond_trigger);
		
		default_time_trigger = initiator->ast_node_specific.global_instance.time_trigger;
		default_cond_trigger = initiator->ast_node_specific.global_instance.cond_trigger;

		/* Free the default activation condition of the initiator,
		 * including both the time trigger and condition trigger. */
		MT_Free(default_time_trigger);
		MT_Free(default_cond_trigger);

		initiator->ast_node_specific.global_instance.time_trigger = inherited_time_trigger;
		initiator->ast_node_specific.global_instance.cond_trigger = inherited_cond_trigger;
	}

	/* Update the argument list of the initiator (or the voter) with
	 * arguments of the inputs argument (or the output argument) of
	 * the original process instance. */
	original_argument = original_instance->ast_node_specific.global_instance.argument_list->next;	
	
	/* Locate the argument list of the initiator or the voter. */
	initiator_argument_list = initiator->ast_node_specific.global_instance.argument_list;

	/* Locate where the placeholder for the input/output argument is
	 * in the argument list of the initiator or the voter. */
	if (in_out == ArgInType)
		default_argument = MT_Find(initiator_argument_list, AST_CODE_ACCESS, "input1");
	else
		default_argument = MT_Find(initiator_argument_list, AST_CODE_ACCESS, "output1");

	cursor = default_argument;
	
	current = param_list->next;

	/* walking through the parameter list and update the argument list
	 * of the initiator or the voter. For the initiator, we will just
	 * copy the input argument from the original process instance to
	 * the initiator. For the voter, just the output arguments. Keep
	 * appending them after the placeholder in the argument list of
	 * the initiator or the voter. */
	while (NULL != current && NULL != original_argument)
	{
		if (current->ast_node_specific.param.in_out == in_out)
		{
			new_argument = MT_Dup(original_argument);
			new_argument->next = cursor->next;
			cursor->next = new_argument;
			cursor = cursor->next;
		}


		current = current->next;
		original_argument = original_argument->next;
	}
	
	/* Locate the AST node before the default argument so as to
	 * prepare for the removal of the default argument. */
	AST *previous = initiator_argument_list;

	while(previous->next != default_argument && previous->next != NULL)
		previous = previous->next;
	
	previous->next = default_argument->next;

	MT_Free(default_argument);

}


/* This function expands the local variables of the member version in
 * the NVP skeleton based on both the user provided process defintion
 * that to be encapsulated in the member versions. */
static void expand_mv_local_variable(AST *member_proc_def, AST *member_version, AST *ft_tree)
{
	AST *original_local_variable;
	AST *default_variable_list;
	AST *original_param_list;
	
	AST *current;

	typeId_t type_spec;
	AST *var_name;
	AST *new_var_decl;
	AST *new_proc_var;

	AST *in_placeholder;
	AST *out_placeholder;

	default_variable_list = member_version->ast_node_specific.state_machine.var_decl_list;

	original_param_list = member_proc_def->ast_node_specific.state_machine.parameter_list;
	
	/* if the original parameter list is not empty, walk through the
	 * parameter list, create variable declaration with the same type
	 * and name. */
	if (NULL != original_param_list)
	{
		current = original_param_list->next;
		
		while (current != NULL)
		{

			type_spec = MT_Dup(current->ast_node_specific.param.typeid);
			var_name = MT_Dup(current->ast_node_specific.param.symbol);

			new_var_decl = defVar_makeDefinition(NULL, VARIABLE_DECL_OP, type_spec, var_name, NULL);

			new_proc_var = defProc_addVariable(NULL, new_var_decl);

			AST_addListLast(NULL, default_variable_list, new_proc_var, 0);	

			current = current->next;
		}
	}

	/* Extend the local variables of the member version with the local
	 * variables of the member process definitions. */
	original_local_variable = member_proc_def->ast_node_specific.state_machine.var_decl_list;
	
	if (NULL != original_local_variable)
	{

		/* If the original local variable is not NULL, dump it and append
		 * to the variable declaration list of the NVP member version. */
		current = original_local_variable->next;

		while (current != NULL)
		{
			new_var_decl = MT_Dup(current);
			new_var_decl->next = NULL;

			AST_addListLast(NULL, default_variable_list, new_var_decl, 0);	

			current = current->next;
		}
	}

	/* Remove the placeholder and adjust the head of the local
	 * variable list of NVP member version. */
	in_placeholder = MT_Find(default_variable_list, AST_CODE_VAR_DECL, "a");
	out_placeholder = MT_Find(default_variable_list, AST_CODE_VAR_DECL, "sum"); 

	/* Walk through the local variable list of the NVP member version,
	 * unlink the placeholders from the list. This code should work
	 * regardless where the placeholders are in the list: head,
	 * middle, or tail of a list. */
	AST *previous = default_variable_list;
	current = default_variable_list->next;

	while (current != NULL)
	{
		if(current == in_placeholder  || current == out_placeholder)
		{
			/* If the current node matches one of the placeholder,
			 * adjust the previous pointer. */
			previous->next = current->next;
		}
		else
		{
			previous = previous->next;
		}

		current = current->next;
	}

	/* Free the placeholder. */
	MT_Free(in_placeholder);
	MT_Free(out_placeholder);
}
enum list_merge_position {
	APPEND_TO_TAIL,
	INSERT_TO_HEAD
};

/* This function will merge the source list into the destination list,
 * either append to the tail or insert in front. */
static AST *merge_list (AST *source, AST *dest, enum list_merge_position head_tail)
{
	AST *current;
	AST *new_element;
	AST *new_list;
	AST *cursor;

	/* If the source is an empty list, there is nothing to be merged,
	 * return the destination list directly. */
	if (NULL == source) return dest;

	/* If the source list is not empty and the destination list is not
	 * empty, start merging by walking through the source list, dump
	 * individual element in the source list and insert into suitable
	 * position of the destination list, depending whether it is
	 * append to tail or insert in front. */
	if (NULL != dest)
	{
		/* At the beginning, cursor points to the AST_CODE_LIST node
		 * itself. This is handy especially when we need to insert in
		 * front */
		cursor = dest;
		
		/* Walk through the source list. */
		current = source->next;
		
		while (current != NULL)
		{
			/* Dump individual element in the source list. */
			new_element = MT_Dup(current);
			new_element->next = NULL;

			if (head_tail == APPEND_TO_TAIL)
			{
				/* If it is append to tail, AST_addListLast will
				 * automatically adjust the tail of the destination
				 * list. */
				AST_addListLast(NULL, dest, new_element, 0);
			}
			else
			{
				/* Insert in the list, but keep the original order of
				 * the node in the source list. So the source list
				 * will be inserted in front of the destination list
				 * as a whole. */
				new_element->next = cursor->next;
				cursor->next = new_element;
				cursor = cursor->next;
			}
				
			/* Move to the next element in the source list. */
			current = current->next;
		}
	}
	else
	{
		/* If the destination list is empty, then dump the whole
		 * source list (including the AST_CODE_LIST node itselt) and
		 * points to it.*/
		new_list = MT_Dup(source);

		dest = new_list;
	}

	return dest;
	
}

/* This function expands the common{} and finally{} block of the
 * member version in the NVP skeleton, based on the user provided
 * process definition. To comply with the CPAL grammar, the variable
 * declaration and the statements in a common{} or finally{} block are
 * handled separately. For the common{} block, the one coming from the
 * user provided process definition, should be appended after the ones
 * in the NVP skeleton, whereas for the finally{} block they should be
 * inserted in front of the ones in the NVP skeleton. */
static void expand_mv_common_finally_block(AST *member_proc_def, AST *member_version, AST *ft_tree)
{
	AST *original_commonfinally_block = NULL;
	AST *default_commonfinally_block = NULL;
	AST *original_var_decl_list = NULL;
	AST *original_statement_list = NULL;

	AST *default_var_decl_list = NULL;
	AST *default_statement_list = NULL;

	/* ---------------- Expand the common block -------------- */
	/* expand the unfold_inputs() function call based on the parameter
	 * list of user provided process definition to be used as a member
	 * version. */
	AST *param_list = member_proc_def->ast_node_specific.state_machine.parameter_list;
	expand_process_func_call(param_list, member_version, ArgInType, NULL);

	/* The content in the common block of the user provided process
	 * definition will be attached to the end of the common block in
	 * the NVP member version. */
	original_commonfinally_block =  member_proc_def->ast_node_specific.state_machine.common_block;
	default_commonfinally_block = member_version->ast_node_specific.state_machine.common_block;

	if (NULL != original_commonfinally_block)
	{
		/* part1 and part2 correspond to the variable declaration list
		 * and the statement list of a common{} or finally{} block. */
		original_var_decl_list = original_commonfinally_block->ast_node_specific.statement.part1;
		original_statement_list = original_commonfinally_block->ast_node_specific.statement.part2;
	}

	if (NULL != default_commonfinally_block)
	{
		default_var_decl_list = default_commonfinally_block->ast_node_specific.statement.part1;
		default_statement_list = default_commonfinally_block->ast_node_specific.statement.part2;
	}

	/* Merge the variable declaration list and the statement list in the common{} block. */
	default_commonfinally_block->ast_node_specific.statement.part1 = merge_list(original_var_decl_list, default_var_decl_list, APPEND_TO_TAIL);
	default_commonfinally_block->ast_node_specific.statement.part2 = merge_list(original_statement_list, default_statement_list, APPEND_TO_TAIL);



	/* ---------------- Expand the finally block ----------------  */
    /* expand the encapsulated_outputs() function call in the finally{} block. */
	expand_process_func_call(param_list, member_version, ArgOutType, NULL);	

	/* The content in the finally{} block of the user provided process
	 * definition will be inserted to the front of the finally{} block
	 * in the NVP member version. */
	original_commonfinally_block =  member_proc_def->ast_node_specific.state_machine.finally_block;
	default_commonfinally_block = member_version->ast_node_specific.state_machine.finally_block;

	if (NULL != original_commonfinally_block)
	{
		original_var_decl_list = original_commonfinally_block->ast_node_specific.statement.part1;
		original_statement_list = original_commonfinally_block->ast_node_specific.statement.part2;
	}

	if (NULL != default_commonfinally_block)
	{
		default_var_decl_list = default_commonfinally_block->ast_node_specific.statement.part1;
		default_statement_list = default_commonfinally_block->ast_node_specific.statement.part2;
	}

	/* Merge the variable declaration list and the statement list in the common{} block. */
	default_commonfinally_block->ast_node_specific.statement.part1 = merge_list(original_var_decl_list, default_var_decl_list, APPEND_TO_TAIL);
	default_commonfinally_block->ast_node_specific.statement.part2 = merge_list(original_statement_list, default_statement_list, INSERT_TO_HEAD);

}

/* The NVP member version will inherit the FSM from the user provided
 * process definition. */
static void expand_mv_fsm(AST *member_proc_def, AST *member_version, AST *ft_tree)
{
	/* For any CPAL process, there should be at least 1 state, so
	 * there is no need to check whether the list is NULL or not. */
	AST *original_fsm = member_proc_def->ast_node_specific.state_machine.state_list;
	AST *default_fsm = member_version->ast_node_specific.state_machine.state_list;

	member_version->ast_node_specific.state_machine.state_list = MT_Dup(original_fsm);

	MT_Free(default_fsm);
}

/* This function will dump the subprocesses in the user provided process definitions. */
static void mv_inherit_subprocess(AST *member_proc_def, AST *member_version, AST *ft_tree)
{
	AST *original_subprocess_list = member_proc_def->ast_node_specific.state_machine.subprocess_list;
	member_version->ast_node_specific.state_machine.subprocess_list = MT_Dup(original_subprocess_list);
}

/* This process will rename the member version as
 * "Member_Version_XXX", where XXX is the user provided process
 * definition name. */
static void mv_process_rename(AST *member_proc_def, AST *member_version, AST *ft_tree)
{


	AST *user_process_name = member_proc_def->ast_node_specific.state_machine.symbol_id;
	char *new_name = user_process_name->ast_node_specific.symbol.text;

	AST *member_version_name = member_version->ast_node_specific.state_machine.symbol_id;
	char *old_name = member_version_name->ast_node_specific.symbol.text;

	char *unique = malloc(strlen(old_name) + strlen(new_name) +2);
	strcpy(unique, old_name);
	strcat(unique, "_");
	strcat(unique, new_name);

	free(member_version_name->ast_node_specific.symbol.text);

	member_version_name->ast_node_specific.symbol.text = strdup(unique);

	free(unique);
}

/* This function is mainly used in expanding the member version
 * instance. It concatinates the name found in the placeholder_symbol
 * with the name found in the user_specific_symbol and stores it back
 * int eh formal. */
static void mv_rename(AST *placeholder_symbol, AST *user_specific_symbol, AST *ft_tree)
{
	char *old_name = placeholder_symbol->ast_node_specific.symbol.text;

	char *new_name = user_specific_symbol->ast_node_specific.symbol.text;

	char *unique = malloc(strlen(old_name) + strlen(new_name) +2);
	strcpy(unique, old_name);
	strcat(unique, "_");
	strcat(unique, new_name);

	free(placeholder_symbol->ast_node_specific.symbol.text);

	placeholder_symbol->ast_node_specific.symbol.text = strdup(unique);

	free(unique);
}


/* This function will expand the member version in the NVP skeleton,
 * including local process variables, the common{}, finally{} block,
 * as well as the FSM. In addition, any subprocess declaration, or
 * implicit declaration in the user provided model will be inherited
 * by the member version to not loss any information. */
static void expand_one_member_version(AST *member_proc_def, AST *member_version, AST *ft_tree)
{
	/* Expand the local variable list of the member version template
	 * based on the user-provided process defintion. */
	expand_mv_local_variable(member_proc_def, member_version, NULL);

	/* Expand the common{} block and the finally{} block of the member version. */
	expand_mv_common_finally_block(member_proc_def, member_version, NULL);\

	/* Expand the state machine in the member version */
	expand_mv_fsm(member_proc_def, member_version, NULL);

	/* Dump the subprocesses in the user provided process defintion. */
	mv_inherit_subprocess(member_proc_def, member_version, NULL);

	/* Rename the member version as Member_Version_XXX, where XXX is
	 * the user provided process name, which is unique by default. */
	mv_process_rename(member_proc_def, member_version, NULL);
	
}

/* This function first dumps the member version process definition in
 * the NVP skeleton, and then expands it according to the user
 * provided process definition. This operation will be done multiple
 * times depending on the number of member versions specified in the
 * dependability annotation. */
void expand_member_version(AST *user_model, AST *template_member_version, AST *dependability_annotation, AST *ft_tree)
{
	AST *current;
	AST *default_member_version;
	AST *member_proc_def;
	char *user_proc_name;
	AST *new_member_version;

	default_member_version = template_member_version;

	current = dependability_annotation;

	/* Walk through the dependability annotation, and create member
	 * version process definition.*/
	while ( current != NULL)
	{
		/* Locate the user provided process definition based on the
		 * process name indicated in the annotation. */
		user_proc_name = current->ast_node_specific.symbol.text;
		member_proc_def = MT_Find(user_model, AST_CODE_STATE_MACHINE, user_proc_name);
		
		/* Dump the member version skeleton to prepare for
		 * expansion. */
		new_member_version = MT_Dup(default_member_version);
		new_member_version->next = NULL;

		expand_one_member_version(member_proc_def, new_member_version, ft_tree);

		/* Append after the member version skeleton, after all
		 * expansion are done, we will remove the
		 * skeleton/placeholder. */
		new_member_version->next = template_member_version->next;
		template_member_version->next = new_member_version;
		template_member_version = template_member_version->next;

		current = current->next;
	}

	/* Remove the default member version from the list. */
	MT_Free(default_member_version);

	
}

/* This function adds a constant declaration for the member ID, and
 * updates the list of initializer of active members. Rename the
 * member ID id1 with a unique ID. */
static void expand_member_id(AST *member_proc_def, AST *member_instance, AST *ft_tree)
{
	AST *user_specific_symbol;
	AST *enum_member_id;
	AST *enum_symbol_list;
	AST *new_member;
	AST *var_active_member;
	AST *initializer;
	AST *initializer_list;
	AST *new_initializer;

	/* ----------------------- Expand the Member_ID enumeration -----------------------*/
	/* Obtain the default field in the enumeration which will be used
	 * to generate unique member ID.*/
	enum_member_id = MT_Find(ft_tree, AST_CODE_DATA_TYPE, "Member_ID");
	enum_symbol_list = enum_member_id->ast_node_specific.type.symbol_list;

	/* Create a new member for the enumeration Member_ID. */
	new_member = MT_Dup(enum_symbol_list->next);
	new_member->next = NULL;

	/* Obtain the user provided process definition name to generate
	 * unique member ID. */
	user_specific_symbol = member_proc_def->ast_node_specific.state_machine.symbol_id;

	/* Rename it as MV_XXX, where XXX is the user provided process
	 * definition name, which should be unique by default.*/
	mv_rename(new_member, user_specific_symbol, NULL);
	
	/* Expand the Member_ID enumeration with the new member. Pay
	 * attention that the placeholder is still there, we will remove
	 * it after the expansion for all member versions are done at the
	 * outer function. */
	AST_addListLast(NULL, enum_symbol_list, new_member, 0);


	/* ----------------------- Expand the initializer of active_members -----------------------*/
	var_active_member = MT_Find(ft_tree, AST_CODE_BUFFER_DECL, "active_members");
	/* According to cpal_grammar.y, the initializer is of type
	 * AST_CODE_INITIALIZER. the initializer is contains a
	 * AST_CODE_LIST because our initializer is for buffer and it is
	 * not empty. */
	initializer = var_active_member->ast_node_specific.buffer_decl.initializer;


	if (NULL != initializer)
	{
		/* The initializer element is in a list. */
		initializer_list = initializer->ast_node_specific.initializer.initializer_element;
		/* Create a new initalizer and rename it as the new member
		 * name, following the pattern, MV_XXX, where XXX is the user
		 * provided process name, and append to the list. The default
		 * initializer will be removed after the expansion is done for
		 * all member version. It will be performed in the outer
		 * loop.*/
		new_initializer = MT_Dup(initializer_list->next);
		new_initializer->next = NULL;
		
		
		MT_Rename(new_initializer, "MV", new_member->ast_node_specific.symbol.text);

		AST_addListLast(NULL, initializer_list, new_initializer, 0);

	}

	/* ----------------------- Expand the reference to Member_ID.MV in member instance  -----------------------*/
	MT_Rename(member_instance, "MV", new_member->ast_node_specific.symbol.text);

}

/* This function expands the member version instance, including the
 * process type, member version instance name, and the member ID
 * passed as argument.*/
void expand_one_mv_instance (AST *member_proc_def, AST *member_instance, AST *ft_tree)
{

	AST *placeholder_proc_type;
	AST *placeholder_instance_name;
	AST *user_specific_symbol;

	/* Rename the process type name as Member_Version_XXX. */
	placeholder_proc_type = member_instance->ast_node_specific.global_instance.process_type;
	user_specific_symbol = member_proc_def->ast_node_specific.state_machine.symbol_id;
	mv_rename(placeholder_proc_type, user_specific_symbol, NULL);

	/* Rename member version instance name as mv_XXX. */
	placeholder_instance_name = member_instance->ast_node_specific.global_instance.instance_name;
	mv_rename(placeholder_instance_name, user_specific_symbol, NULL);

	/* we also need to add a constant declaration for the member ID,
	 * and update the list of initializer of active members. Rename
	 * the member ID id1 with a unique ID. */
	expand_member_id(member_proc_def, member_instance, ft_tree);
}

/* Expand the member version instance multiple times, using the
 * template in the NVP skeleton, based on the number of member
 * versions found in the dependability annotation. */
void expand_member_version_instance(AST *user_model, AST *template_mv_instance, AST *dependability_annotation, AST *ft_tree)
{
	AST *enum_member_id;
	AST *enum_symbol_list;
	AST *default_enumeration;
	AST *member_proc_def;
	AST *var_active_member;
	AST *initializer;
	AST *initializer_list;
	AST *default_initializer;
	AST *current;
	AST *default_member_instance = template_mv_instance;
	char *user_proc_name;
	
	current = dependability_annotation;
	
	/* Walking through the dependability annotation, dump the
	 * placeholder member version instance in the NVP skeleton for
	 * expansion. */
	while ( current != NULL)
	{
		AST *new_instance = MT_Dup(default_member_instance);
		new_instance->next = NULL;

		user_proc_name = current->ast_node_specific.symbol.text;
		member_proc_def = MT_Find(user_model, AST_CODE_STATE_MACHINE, user_proc_name);

		/* Expand the member version instance, including the process
		 * type, member version instance name, and the member ID
		 * passed as argument.*/
		expand_one_mv_instance (member_proc_def, new_instance, ft_tree);

		/* Append after the placeholder. */
		new_instance->next = template_mv_instance->next;
		template_mv_instance->next = new_instance;
		template_mv_instance = template_mv_instance->next;

		current = current->next;
	}

	/* Remove the default member instance from the
	 * list. */
	MT_Free(default_member_instance);

	/* Extremely important: only when we are done with th expansion of
	 * the member version instances, we remove the placeholder in the
	 * Member_ID enumeration, and in the initializer of active
	 * members. */
	enum_member_id = MT_Find(ft_tree, AST_CODE_DATA_TYPE, "Member_ID");
	enum_symbol_list = enum_member_id->ast_node_specific.type.symbol_list;

	if(NULL != enum_symbol_list)
	{
		/* remove the placeholder in Member_ID enumeration. */
		default_enumeration = enum_symbol_list->next;
		enum_symbol_list->next = default_enumeration->next;

		MT_Free(default_enumeration);
	}

	
	var_active_member = MT_Find(ft_tree, AST_CODE_BUFFER_DECL, "active_members");
	initializer = var_active_member->ast_node_specific.buffer_decl.initializer;


	if (NULL != initializer)
	{
		/* The initializer element is in a list. */
		initializer_list = initializer->ast_node_specific.initializer.initializer_element;
		default_initializer = initializer_list->next;

		initializer_list->next = default_initializer->next;
		
		MT_Free(default_initializer);
	}
}

void NVP_main()
{

}
