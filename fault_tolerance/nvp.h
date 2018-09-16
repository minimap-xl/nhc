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

enum func_kind {
	ENCAPSULATE,
	UNFOLD
};

/* This function expands the Replica_In and Replica_Out data structure
 * in the NVP skeleton, according to the parameter list of a process
 * definition. in_out specifies whether we are interested in the input
 * parameter or the output parameter. ft_tree is for future use. It
 * can be removed, if not needed. */
void expand_Replica_INOUT(AST *param_list, AST *replica_in, enum argument_type in_out, AST *ft_tree);

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
void encap_unfold_INOUT_param(AST *source_list, AST *dest_list, enum argument_type in_out, enum func_kind encap_unfold, AST *ft_tree);

/* This function expands the function body of the
 * encapsulate_inputs(), encapsulate_outputs(), unfold_inputs(),
 * unfold_outputs() functions. In particular, it extends the statement
 * list in the function body based on the parameter list of the
 * original process. in_out specifies whether it is for xxx_inputs()
 * functions or xxx_outputs() functions. The way to expand the
 * statement list is to keep appending after the default statement.
 * When done with expansion, remove the default statement. */
void encap_unfold_INOUT_body(AST *param_list, AST *statement_list, enum argument_type in_out, AST *ft_tree);

/* This function expands the comp_ballot() function by extending the
 * if condition in the function body, based on the output parameter in
 * the parameter list. This is because this function will be used by
 * the voter to compare the results geneated by different member
 * versions. */
void expand_comp_ballot(AST *param_list, AST *comp_ballot_func, AST *ft_tree);

/* Expand the initiator according to the input parameter list of the
 * original process, since initiator is mainly responsible for pushing
 * inputs to the member versions. */
void expand_process_param_list(AST *param_list, AST *initiator_voter, enum argument_type in_out, AST *ft_tree);


/* This function is used to expand the function calls of
 * encapsulate_inputs(), unfold_outputs() in the body of the process
 * definition for the initiator and the voter. It is done based on the
 * input/output parameters in the parameter list of the original
 * process. IMPORTANT_UPDATES: this function can be used to expand the
 * function calls of unfold_inputs(), encapsulate_outputs() in the
 * member version as well.*/
void expand_process_func_call(AST *param_list, AST *initiator_voter, enum argument_type in_out, AST *ft_tree);

/* This function expands the initiator and voter process instances in
 * the NVP skeleton, based on the argument list of the original
 * process instance, and the parameter list of the process
 * definition. Because in the argument list of the original process
 * instance, there is no knowledge we can explore to distinguish
 * between input and output argument. The initiator will inherit the
 * activation condition (time trigger and the condition
 * trigger). Initiator will inherit the input arguments, whereas the
 * voter inherits the output arguments. */
void expand_initiator_instance(AST *original_instance, AST *initiator, AST *param_list, enum argument_type in_out, AST *ft_tree);

/* This function will expand the member version in the NVP skeleton,
 * including local process variables, the common{}, finally{} block,
 * as well as the FSM. In addition, any subprocess declaration, or
 * implicit declaration in the user provided model will be inherited
 * by the member version to not loss any information. */
void expand_member_version(AST *user_model, AST *template_member_version, AST *dependability_annotation, AST *ft_tree);

/* Expand the member version instance multiple times, using the
 * template in the NVP skeleton, based on the number of member
 * versions found in the dependability annotation. */
void expand_member_version_instance(AST *user_model, AST *template_mv_instance, AST *dependability_annotation, AST *ft_tree);


/* Driver functions, to be inserted in the table of
   parse_annotations()
*/
void NVP_driver(
    int seq, AST *user_model, AST *arguments, AST *skeleton,
    AST *output);

void NVP_pre_processor(
    int seq, AST *user_model, AST *skeleton,
    AST *output);

void NVP_post_processor(
    int seq, AST *user_model, AST *skeleton,
    AST *output);
