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

#include "def_process.h"
#include "rAST.h"

AST *defProc_declareStateMachine(
    parser_Env *env, symbolId_t symbol_id,
    AST *parameter_list, AST *subprocess_list, AST *var_decl_list,
    AST *common_block, AST *state_list, AST *finally_block)
{
    /* This is the top level of a process definition.  This function
       creates an AST node with code AST_CODE_STATE_MACHINE and saves
       its arguments into it.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_STATE_MACHINE;
    node->ast_node_specific.state_machine.symbol_id = symbol_id;
    node->ast_node_specific.state_machine.parameter_list = parameter_list;
    node->ast_node_specific.state_machine.subprocess_list = subprocess_list;
    node->ast_node_specific.state_machine.var_decl_list = var_decl_list;
    node->ast_node_specific.state_machine.common_block = common_block;
    node->ast_node_specific.state_machine.state_list = state_list;
    node->ast_node_specific.state_machine.finally_block = finally_block;
    return node;
}

AST *defProc_declareStateMachinePrototype(
    parser_Env *env, symbolId_t sm_name, AST *parameters)
{
    /* This function creates a AST_CODE_SM_PROTOTYPE, which contains
       the prototype of a process.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_SM_PROTOTYPE;
    node->ast_node_specific.sm_prototype.sm_name = sm_name;
    node->ast_node_specific.sm_prototype.parameters = parameters;
    return node;
}

void defProc_declareLocalInstance(parser_Env *env, AST *subprocess_decl)
{
}

void defProc_clearLocalInstances(parser_Env *env)
{

}

/* The following two functions create a AST_CODE_PROC_VAR node to wrap
   an AST_CODE_VAR_DECL or AST_CODE_BUFFER_DECL found within a process
   definition.
*/
AST *defProc_addVariable(parser_Env *env, AST *variable_declaration)
{
    AST *node = AST_createNode();

    node->code = AST_CODE_PROC_VAR;
    node->ast_node_specific.proc_var.is_static = false;
    node->ast_node_specific.proc_var.decl = variable_declaration;
    return node;
}

AST *defProc_addStaticVariable(parser_Env *env, AST *variable_declaration)
{
    AST *node = AST_createNode();

    node->code = AST_CODE_PROC_VAR;
    node->ast_node_specific.proc_var.is_static = true;
    node->ast_node_specific.proc_var.decl = variable_declaration;
    return node;
}

AST *defProc_makeInstance(
    parser_Env *env, AST *process_type, AST *instance_name)
{
    /* This function creates a AST_CODE_PROC_INSTANCE, that is a
       sub-process instance within a process definition.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_PROC_INSTANCE;
    node->ast_node_specific.proc_instance.process_type = process_type;
    node->ast_node_specific.proc_instance.instance_name = instance_name;
    return node;
}

AST *defProc_makeTransition(
    parser_Env *env, enum transition_type on_after_type, symbolId_t symbol_id,
    AST *transition_condition, AST *time_elapsed, AST *transition_code)
{
    /* This function creates a AST_CODE_TRANSITION, that is a state
       transition within a process definition.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_TRANSITION;
    node->ast_node_specific.transition.on_after_type = on_after_type;
    node->ast_node_specific.transition.symbol_id = symbol_id;
    node->ast_node_specific.transition.transition_condition
	= transition_condition;
    node->ast_node_specific.transition.time_elapsed = time_elapsed;
    node->ast_node_specific.transition.transition_code = transition_code;
    return node;
}

void defProc_define_global_process_implicit(parser_Env *env, AST *symbol)
{
}

AST *defProc_defineGlobalInstance(
    parser_Env *env, AST *process_type, AST *instance_name,
    AST *time_trigger, AST *cond_trigger, AST *argument_list)
{
    /* This function creates a AST_CODE_GLOBAL_INSTANCE, which is a
       process instance in global context.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_GLOBAL_INSTANCE;

    node->ast_node_specific.global_instance.process_type = process_type;
    node->ast_node_specific.global_instance.instance_name = instance_name;
    node->ast_node_specific.global_instance.time_trigger = time_trigger;
    node->ast_node_specific.global_instance.cond_trigger = cond_trigger;
    node->ast_node_specific.global_instance.argument_list = argument_list;
    return node;
}

AST *process_makeState(parser_Env *env, AST *state_name, AST *state_block, AST *triggers_list)
{
    /* This function creates a AST_CODE_STATE, which corresponds to a
       state within a process definition.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_STATE;

    node->ast_node_specific.state.state_name = state_name;
    node->ast_node_specific.state.state_block = state_block;
    node->ast_node_specific.state.triggers_list = triggers_list;
    return node;
}

uint32_t Process_State_getTypeID(uint32_t ienv)
{
    return 0;
}
