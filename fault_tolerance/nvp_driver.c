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

/* This module implements the pre-processor, ft function, and
   post-processor for the NVP module.
*/

/* Enable debugging printouts if needed */
#define DEBUG

#include <string.h>
#include <ft.h>

#ifdef DEBUG
#include <dump.h>
#endif


/* The NVP driver performs the following operations:

   0) Make a copy of the skeleton, for later expansion.

   1) With the help of extract_arguments, extracts the relevant
      arguments from the argument list it receives.

   2) Locate the process definition in the output AST from the name of
      the process instance, by means of find_processdef.

   3) Locate and expand the Replica_In and Replica_Out structures in
      the skeleton and append the result after the process instance,
      with the help of expand_replica_in_out().

   4) Expand the encapsulate_inputs() and encapsulate_outputs()
      functions in the skeleton, with the help of the
      expand_encapsulate_in_out() function.

   5) The same as 4) for unfold_inputs() and unfold_outputs(),
      using the expand_unfold_in_out() function.

   6) Expand the comp_ballot() function.  This is done directly in
      NVP_driver() because expand_comp_ballot() takes care of
      everything by itself.

   7) Expand the initiator process definition, with the help of
      expand_initiator().

   8) Expand the voter process definition, with the help of
      expand_voter().

   9) Expand the initiator instance, done directly in NVP_driver()
      because it consists of a single call.

   10) Expand the voter instance, done directly in NVP_driver()
       because it consists of a single call.

   11) Expand the member version process definition found in the
       skeleton multiple times, once for each member version the user
       mentioned in the dependability annotation.  This is done
       directly in NVP_driver() because expand_member_version() takes
       care of everything by itself.

   12) Expand the member version process instance found in the
       skeleton multiple times, once for each expanded member version.
       This is done directly in NVP_driver() because
       expand_member_version() takes care of everything by itself.

   --) Suppress the definitions of placeholders 'input1' and 'output1'
       by calling the function remove_placeholder_def().  These
       definitions are useful to make the skeleton correct from cpal2x
       point of view, but should not be kept in the output, otherwise
       they may conflict with user variables.

   --) Make all names unique in the expanded skeleton and append it to
       the output, after the original process instance.  Suppress the
       original process instance and original process definition.
*/
static int extract_arguments(
    AST *arguments,
    char **voter, char **proc_instance, AST **member_version_list,
    int *n_members)
{
    int n;

    /* Extract voter selector (1st argument) */
    if(!arguments)
    {
	fprintf(stderr, "Warning: no voter selector\n");
	return -1;
    }

    assert(arguments->code == AST_CODE_SYMBOL);
    *voter = arguments->ast_node_specific.symbol.text;

    arguments = arguments->next;

    /* Parse process instance */
    if(!arguments)
    {
	fprintf(stderr, "Warning: no process instance\n");
	return -1;
    }

    assert(arguments->code == AST_CODE_SYMBOL);
    *proc_instance = arguments->ast_node_specific.symbol.text;

    arguments = arguments->next;
    *member_version_list = arguments;

    n = 0;
    while(arguments)
    {
	arguments = arguments->next;
	n++;
    }

    *n_members = n;
    return 0;
}

static AST *find_process_inst(
    AST *tree,
    char *proc_instance)
{
    AST *global_inst;

    global_inst = MT_Find(tree, AST_CODE_GLOBAL_INSTANCE, proc_instance);
    if(global_inst == NULL)
    {
	fprintf(stderr, "Warning: process instance %s not found\n",
		proc_instance);
	return NULL;
    }

    return global_inst;
}

static AST *find_processdef(
    AST *tree,
    AST *global_inst)
{
    AST *proc_type;
    AST *proc_sm;

    proc_type = global_inst->ast_node_specific.global_instance.process_type;
    assert(proc_type->code == AST_CODE_SYMBOL);

    proc_sm = MT_Find(tree, AST_CODE_STATE_MACHINE,
		      proc_type->ast_node_specific.symbol.text);
    if(proc_sm == NULL)
    {
	fprintf(stderr, "Warning: processdef %s not found\n",
		proc_type->ast_node_specific.symbol.text);

	return NULL;
    }

    return proc_sm;
}

void expand_replica_in_out(AST *skeleton, AST* param_list)
{
    AST *replica_in = MT_Find(skeleton, AST_CODE_DATA_TYPE, "Replica_In");
    AST *replica_out = MT_Find(skeleton, AST_CODE_DATA_TYPE, "Replica_Out");

    assert(replica_in && replica_out);

    /* Last argument unused at the moment by these functions, give
       them a NULL pointer.
    */
    expand_Replica_INOUT(param_list, replica_in, ArgInType, NULL);
    expand_Replica_INOUT(param_list, replica_out, ArgOutType, NULL);
}

void expand_encapsulate_in_out(AST *skeleton, AST *param_list)
{
    AST *encap_input_func =
	MT_Find(skeleton, AST_CODE_FUNCTION_DEF, "encapsulate_inputs");
    AST *encap_output_func =
	MT_Find(skeleton, AST_CODE_FUNCTION_DEF, "encapsulate_outputs");

    AST *target_inparam_list, *target_outparam_list;
    AST *default_statement_in, *default_statement_out;

    assert(encap_input_func && encap_output_func);

    target_inparam_list =
	encap_input_func->ast_node_specific.function_def.parameter_list;
    encap_unfold_INOUT_param(
	param_list, target_inparam_list, ArgInType, ENCAPSULATE, NULL);

    target_outparam_list =
	encap_output_func->ast_node_specific.function_def.parameter_list;
    encap_unfold_INOUT_param(
	param_list, target_outparam_list, ArgOutType, ENCAPSULATE, NULL);

    default_statement_in =
	encap_input_func->ast_node_specific.function_def.block
	->ast_node_specific.statement.part2;
    encap_unfold_INOUT_body(param_list, default_statement_in, ArgInType, NULL);

    default_statement_out =
	encap_output_func->ast_node_specific.function_def.block
	->ast_node_specific.statement.part2;
    encap_unfold_INOUT_body(param_list, default_statement_out, ArgOutType, NULL);
}

void expand_unfold_in_out(AST *skeleton, AST *param_list)
{
    AST *unfold_inputs =
	MT_Find(skeleton, AST_CODE_FUNCTION_DEF, "unfold_inputs");
    AST *unfold_outputs =
	MT_Find(skeleton, AST_CODE_FUNCTION_DEF, "unfold_outputs");

    AST *unfold_inputs_param_list, *unfold_outputs_param_list;
    AST *default_statement_unfold_in, *default_statement_unfold_out;

    assert(unfold_inputs && unfold_outputs);

    unfold_inputs_param_list =
	unfold_inputs->ast_node_specific.function_def.parameter_list;
    encap_unfold_INOUT_param(
	param_list, unfold_inputs_param_list, ArgInType, UNFOLD, NULL);

    unfold_outputs_param_list =
	unfold_outputs->ast_node_specific.function_def.parameter_list;
    encap_unfold_INOUT_param(
	param_list, unfold_outputs_param_list, ArgOutType, UNFOLD, NULL);

    default_statement_unfold_in =
	unfold_inputs->ast_node_specific.function_def.block
	->ast_node_specific.statement.part2;
    encap_unfold_INOUT_body(
	param_list, default_statement_unfold_in, ArgInType, NULL);

    default_statement_unfold_out =
	unfold_outputs->ast_node_specific.function_def.block
	->ast_node_specific.statement.part2;
    encap_unfold_INOUT_body(
	param_list, default_statement_unfold_out, ArgOutType, NULL);
}

void expand_initiator(AST *skeleton, AST *param_list)
{
    AST *initiator = MT_Find(
	skeleton, AST_CODE_STATE_MACHINE, "Initiator");

    assert(initiator);
    expand_process_param_list(param_list, initiator, ArgInType, NULL);
    expand_process_func_call(param_list, initiator, ArgInType, NULL);
}

void expand_voter(AST *skeleton, AST *param_list)
{
    AST *voter = MT_Find(
	skeleton, AST_CODE_STATE_MACHINE, "Voter");

    assert(voter);

    expand_process_param_list(param_list, voter, ArgOutType, NULL);
    expand_process_func_call(param_list, voter, ArgOutType, NULL);
}


static int mt_free(AST *root, AST *node, int depth, void *hl_cookie)
{
    if(depth <= 1)  MT_Free(node);
    return 0;
}

void remove_placeholder_def(AST *skeleton, char *var_name)
{
    (void)MT_Apply(skeleton, AST_CODE_VAR_DECL, var_name, mt_free, NULL);
}

/* Append n after p.  p is an element of a list, n is a list.

   TBD: This leaves the .tail pointer of the container of p in an
   invalid state.  It shoud not be a big deal.
*/
void append_after(AST *p, AST *n)
{
    n->ast_node_specific.list.tail->next = p->next;
    p->next = n->next;  /* Skip n's header */
}


void NVP_driver(
    int seq, AST *user_model, AST *arguments, AST *skeleton,
    AST *output)
{
    char *voter;
    char *proc_instance;
    AST *member_version_list;
    int n_members;

#ifdef DEBUG
    struct dump_opts dump_opts = { .max_depth = 100 };
#endif

    /* Extract arguments */
    if(extract_arguments(arguments, &voter, &proc_instance,
			 &member_version_list, &n_members))  return;
#ifdef DEBUG
    AST *member;
    fprintf(stderr,
	    "NVP_driver got @dependability:nvp:%s:%s,"
	    " plus %d member versions: ",
	    voter, proc_instance, n_members);

    member = member_version_list;
    while(member)
    {
	fprintf(stderr, "%s ", member->ast_node_specific.symbol.text);
	member = member->next;
    }
    fprintf(stderr, "\n");
#endif

    /* Duplicate the skeleton because we are going to expand it */
    assert(skeleton = MT_Dup(skeleton));

    /* Locate process instance in the output */
    AST *global_inst;
    if((global_inst = find_process_inst(output, proc_instance)) == NULL) return;

    /* Locate processdef in the output */
    AST *proc_sm;
    if((proc_sm = find_processdef(output, global_inst)) == NULL) return;

#ifdef DEBUG
    fprintf(stderr,
	    "Located processdef: ");
    Dump_AST(stderr, proc_sm, &dump_opts);
#endif

    /* Locate Replica_In and Replica_Out in the skeleton and expand
       them according to the parameter list taken from the process
       definition.
    */
    AST *param_list = proc_sm->ast_node_specific.state_machine.parameter_list;

    expand_replica_in_out(skeleton, param_list);

    /* Locate and Expand the encapsulate_inputs() and
       encapsulate_outputs() functions in the skeleton.  The same for
       unfold_inputs() and unfold_outputs().
    */
    expand_encapsulate_in_out(skeleton, param_list);
    expand_unfold_in_out(skeleton, param_list);

    /* Expand the comp_ballot() function */
    AST *comp_ballot_func = MT_Find(
	skeleton, AST_CODE_FUNCTION_DEF, "comp_ballot");
    assert(comp_ballot_func);
    expand_comp_ballot(param_list, comp_ballot_func, NULL);

    /* Expand the initiator process */
    expand_initiator(skeleton, param_list);

    /* Expand the voter process.  
    */
    expand_voter(skeleton, param_list);

    /* Expand the initiator instance */
    AST *initiator_instance =
	MT_Find(skeleton, AST_CODE_GLOBAL_INSTANCE, "initiator");
    assert(initiator_instance);
    expand_initiator_instance(
	global_inst, initiator_instance, param_list, ArgInType, NULL);

    /* Expand the voter instance */
    AST *voter_instance =
	MT_Find(skeleton, AST_CODE_GLOBAL_INSTANCE, "voter");
    assert(voter_instance);
    expand_initiator_instance(
	global_inst, voter_instance, param_list, ArgOutType, NULL);

    /* Expand the member version process definition as many times as
       necessary.
    */
    AST *mv_template =
	MT_Find(skeleton, AST_CODE_STATE_MACHINE, "Member_Version");
    assert(mv_template);
    expand_member_version(user_model, mv_template, member_version_list, NULL);

	/* In the subprocess-based NVP skeleton, there is a dummy process
	 * definition called Dummy_Template to make the NVP skeleton fully
	 * CPAL compliant. After the expansion of member versions, remove
	 * that dummy process definition. Even though it is harmless if we
	 * keep it, it is more elegant we remove it.*/
#ifdef NVP_SUBPROCESS_IMPL
	AST *dummy_proc_def = 
	MT_Find(skeleton, AST_CODE_STATE_MACHINE, "Dummy_Template");
	MT_Free(dummy_proc_def);
#endif
 
    /* Expand the member version instance as many times as necessary.
    */
    AST *mv_instance =
	MT_Find(skeleton, AST_CODE_GLOBAL_INSTANCE, "mv");
    assert(mv_instance);

    expand_member_version_instance(
	user_model, mv_instance, member_version_list, skeleton);

    /* Remove placeholder definitions from the output */
    remove_placeholder_def(skeleton, "input1");
    remove_placeholder_def(skeleton, "output1");

    /* Make names unique and append to the output, after global_inst */
    MT_Make_Unique(skeleton, proc_instance);
    append_after(global_inst, skeleton);

    /* TBD: Cleanup: Suppress original processdef and instantiation in
       the final output.  Suppressing the original processdef may be
       inappropriate if the user would like to refer to the same
       processdef in a subsequent annotation.  Probably a marker for
       delayed deletion, to be done in post-processing, would be
       better.
    */
    /* MT_Free(proc_sm);*/ /* TT: commented out by Tingting. For the NVP subprocess we need the original processdef.*/
    MT_Free(global_inst);
}


/* The NVP pre-processor performs the following operations:

   1) If it is the very first pre-processor to be called, copy and
      concatenate the user model into the output (that should still
      be empty).

   2) ... TBD ...
*/
void NVP_pre_processor(
    int seq, AST *user_model, AST *skeleton,
    AST *output)
{
    /* Duplicate the whole user_mode into the output if this is the
       very first pre-processor call.
    */
    if(seq == 0)
    {
	AST *dup_user = MT_Dup(user_model);
	AST_concatLists(NULL, output, dup_user, 0);
    }
}


/* The NVP post-processor performs the following operations:

   1) Suppress all @dependability annotations that have been copied in
      the output model, regardless of whether we have parsed them
      successfully or not, because they would confuse the CPAL parser.
      If we did, good news.  If we didn't we should have gotten a
      warning and there is nothing more we can do at this time.

   2) ... TBD ...
*/
static int kill_annotation(AST *root, AST *node, int depth, void *hl_cookie)
{
    MT_Free(node);
    return 0;  /* This function never fails */
}

void NVP_post_processor(
    int seq, AST *user_model, AST *skeleton,
    AST *output)
{
    /* Suppress all @dependability annotations */
    (void)MT_Apply(output, AST_CODE_ANNOTATION, "dependability",
		   kill_annotation, NULL);

}
