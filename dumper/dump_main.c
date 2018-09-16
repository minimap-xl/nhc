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

/* This module implements the main function of the dumper,
   CPAL_Dump_AST().  It can start dumping from any point of an AST,
   with the implicit quirk that, unless it is invoked on the AST root,
   its output may be incomplete and cannot be parsed back.

   In the dump, information preceded by ^ and surrounded by () is for
   parser debugging.
*/

#include <dump.h>
#include "dump_private.h"


void init_cookie(struct dump_cookie *cookie, const struct dump_opts *opts)
{
    cookie->opts = opts;  /* Link options to the cookie */
    cookie->depth = 0;    /* Initialize dump depth */

    cookie->full_dump = 0; /* No full dumps at the beginning */
}

DECL_DUMP_FUNCTOR(dump_list)
{
    DUMP_PROLOGUE;


    while (ast->next)
    {
	RECURSE(dump_ast_internal, ast->next);

	switch(ast->next->code)
	{
	    /* AST_CODE_ACCESS is used for function call and builtin
	       method call arguments.

	       AST_CODE_STRING is used for strings passed as
	       arguments.
	    */
	case AST_CODE_PARAM:
	case AST_CODE_ACCESS:
	case AST_CODE_STRING:
	case AST_CODE_LOGICAL_OP:
	case AST_CODE_ARITHMETIC_OP:
	case AST_CODE_MULTI_EQ_OP:
	case AST_CODE_MULTI_REL_OP:
	case AST_CODE_TIME_LITERAL:
	case AST_CODE_FREQUENCY:
	case AST_CODE_SYMBOL:
	case AST_CODE_BOOLEAN:
	case AST_CODE_INTEGER:
	case AST_CODE_FLOAT:
	case AST_CODE_ARRAY_CALL:
	case AST_CODE_FIELD_CALL:
	case AST_CODE_FUNCTION_CALL:
	case AST_CODE_BUILTIN_MTD_CALL:
	    if(ast->next->next == NULL)
	    {
	    }
	    else
		fprintf(o, ", ");
	    break;

	default:
	    break;
	}

	ast = ast->next;
    }

    DUMP_EPILOGUE;
}


DECL_DUMP_FUNCTOR(dump_var_decl)
{
    DUMP_PROLOGUE;

    switch(ast->ast_node_specific.var_decl.op)
    {
    case VARIABLE_DECL_OP:
	fprintf(o, "var ");
	break;

    case CONSTANT_DECL_OP:
	fprintf(o, "const ");
	break;

    default:
	DUMP_ERROR(fprintf(o, "^(ast->ast_node_specific.var_decl.op=%d)",
			   ast->ast_node_specific.var_decl.op));
	break;
    }

    RECURSE(dump_typeId, ast->ast_node_specific.var_decl.typeid);
    fprintf(o, ": ");
    WITH_FULL_DUMP(
	RECURSE(dump_ast_internal, ast->ast_node_specific.var_decl.symbol));
    if(ast->ast_node_specific.var_decl.initializer)
    {
	fprintf(o, "= ");
	RECURSE(dump_ast_internal, ast->ast_node_specific.var_decl.initializer);
    }
    fprintf(o, ";\n");

    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_symbol)
{
    DUMP_PROLOGUE;
    fprintf(o, "%s ", ast->ast_node_specific.symbol.text);
    if(cookie->full_dump)
	fprintf(o, "/* declared @line %d */ ",
	    ast->ast_node_specific.symbol.lineno);
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_initializer)
{
    DUMP_PROLOGUE;

    /* An initializer can point to a frequency, an expression, an
       empty brace-delimited list (NULL pointer) or a brace-delimited,
       comma-separated list.  The last two cases need special care and
       are handled specially.  The first two cases are handled by a
       standard recursive descent into initializer_element.
    */
    if(ast->ast_node_specific.initializer.initializer_element)
    {
		if(ast->ast_node_specific.initializer.initializer_element
		   ->code == AST_CODE_LIST)
		{
			fprintf(o, "{ ");
			AST *tmp;
			tmp = ast->ast_node_specific.initializer.initializer_element;
			while (tmp->next) {
				RECURSE(dump_ast_internal, tmp->next);
				if (tmp->next->next == NULL)
				{
				}
				else 
					fprintf(o, ", ");
				tmp = tmp->next;
			}
			fprintf(o, "} ");
		}

		else
			RECURSE(dump_ast_internal,
					ast->ast_node_specific.initializer.initializer_element);
    }

    else
		fprintf(o, "{} ");

    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_frequency)
{
    DUMP_PROLOGUE;
    /* ast->ast_node_specific.frequency.lineno omitted */
    fprintf(o, "%s ",
	    ast->ast_node_specific.frequency.text);
    DUMP_EPILOGUE;
}

#define HIGH_PREC 999


/* For expression operators, we can find the precedence in the
   tree_expression part.  For others, we say it's very high.
*/
static int prec_of(const AST *ast)
{
    int prec;

    if(ast == NULL)  return HIGH_PREC;
    switch(ast->code)
    {
	/* I TBD: Add the other codes here  */
    case AST_CODE_LOGICAL_OP:
    case AST_CODE_ARITHMETIC_OP:
    case AST_CODE_MULTI_EQ_OP:
    case AST_CODE_MULTI_REL_OP:
	prec = ast->ast_node_specific.expression.prec;
	break;

    default:
	prec = HIGH_PREC;
	break;
    }

    return prec;
}

DECL_DUMP_FUNCTOR(dump_logical_op)
{
    int pl, pm, pr;

    DUMP_PROLOGUE;

    /* Unary operators must be handled specially.  One of the reasons
       is that the child is stored in the left pointer, although it
       must be dumped on the right of the operator and (unless I'm
       mistaken) we must use the right-hand precedence rules for
       parentheses.
    */
    if(ast->ast_node_specific.expression.op == NOT_OP)
    {
	pl = prec_of(ast->ast_node_specific.expression.left);
	pm = prec_of(ast);

	fprintf(o, " not ");

	if(pm > pl)  fprintf(o, "(");
	RECURSE(dump_ast_internal, ast->ast_node_specific.expression.left);
	if(pm > pl)  fprintf(o, ") ");
    }

    else
    {
	pl = prec_of(ast->ast_node_specific.expression.left);
	pm = prec_of(ast);
	pr = prec_of(ast->ast_node_specific.expression.right);

	if(pl < pm)  fprintf(o, "(");
	RECURSE(dump_ast_internal, ast->ast_node_specific.expression.left);
	if(pl < pm)  fprintf(o, ") ");

	switch(ast->ast_node_specific.expression.op)
	{
	case OR_OP:
	    fprintf(o, " or ");
	    break;

	case AND_OP:
	    fprintf(o, " and ");
	    break;

	    /* CEQ_OP and CNE_OP are also multi_eq operators,
	       when not used in a multiple operator context
	    */
	case CEQ_OP:
	    fprintf(o, " == ");
	    break;

	case CNE_OP:
	    fprintf(o, " != ");
	    break;

	    /* LT_OP, GT_OP, CGE_OP, CLE_OP are also logical operators,
	       when not used in a multiple operator context
	    */
	case LT_OP:
	    fprintf(o, " < ");
	    break;

	case GT_OP:
	    fprintf(o, " > ");
	    break;

	case CGE_OP:
	    fprintf(o, " >= ");
	    break;

	case CLE_OP:
	    fprintf(o, " <= ");
	    break;

	default:
	    DUMP_ERROR(fprintf(o, " ^(logical op %d) ",
			       ast->ast_node_specific.expression.op));
	    break;
	}

	/* This code assumes that all operators are left-associative
	*/
	if(pm >= pr)  fprintf(o, "(");
	RECURSE(dump_ast_internal, ast->ast_node_specific.expression.right);
	if(pm >= pr)  fprintf(o, ") ");
    }

    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_arithmetic_op)
{
    int pl, pm, pr;

    DUMP_PROLOGUE;

    /* Unary operators must be handled specially.  One of the reasons
       is that the child is stored in the left pointer, although it
       must be dumped on the right of the operator and (unless I'm
       mistaken) we must use the right-hand precedence rules for
       parentheses.
    */
    if(ast->ast_node_specific.expression.op == NEG_OP
       || ast->ast_node_specific.expression.op == BITWISE_NOT_OP)
    {
	pl = prec_of(ast->ast_node_specific.expression.left);
	pm = prec_of(ast);

	switch(ast->ast_node_specific.expression.op)
	{
	case NEG_OP:
	    fprintf(o, " - ");
	    break;

	case BITWISE_NOT_OP:
	    fprintf(o, " ~ ");
	    break;

	default:
	    DUMP_ERROR(fprintf(o, " ^(arithmetic unary op %d) ",
			       ast->ast_node_specific.expression.op));
	    break;
	}

	if(pm > pl)  fprintf(o, "(");
	RECURSE(dump_ast_internal, ast->ast_node_specific.expression.left);
	if(pm > pl)  fprintf(o, ") ");
    }

    else
    {
	pl = prec_of(ast->ast_node_specific.expression.left);
	pm = prec_of(ast);
	pr = prec_of(ast->ast_node_specific.expression.right);

	if(pl < pm)  fprintf(o, "(");
	RECURSE(dump_ast_internal, ast->ast_node_specific.expression.left);
	if(pl < pm)  fprintf(o, ") ");

	switch(ast->ast_node_specific.expression.op)
	{
	case BITWISE_OR_OP:
	    fprintf(o, " | ");
	    break;

	case BITWISE_XOR_OP:
	    fprintf(o, " ^ ");
	    break;

	case BITWISE_AND_OP:
	    fprintf(o, " & ");
	    break;

	case BITWISE_LEFT_SHIFT_OP:
	    fprintf(o, " << ");
	    break;

	case BITWISE_RIGHT_SHIFT_OP:
	    fprintf(o, " >> ");
	    break;

	case PLUS_OP:
	    fprintf(o, " + ");
	    break;

	case MINUS_OP:
	    fprintf(o, " - ");
	    break;

	case MUL_OP:
	    fprintf(o, " * ");
	    break;

	case DIV_OP:
	    fprintf(o, " / ");
	    break;

	case MOD_OP:
	    fprintf(o, " mod ");
	    break;

	default:
	    DUMP_ERROR(fprintf(o, " ^(arithmetic binary op %d) ",
			       ast->ast_node_specific.expression.op));
	    break;
	}

	/* This assumes that all operators are left-associative.
	*/
	if(pm >= pr)  fprintf(o, "(");
	RECURSE(dump_ast_internal, ast->ast_node_specific.expression.right);
	if(pm >= pr)  fprintf(o, ") ");
    }

    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_multi_eq_op)
{
    int pl, pm, pr;

    DUMP_PROLOGUE;
    pl = prec_of(ast->ast_node_specific.expression.left);
    pm = prec_of(ast);
    pr = prec_of(ast->ast_node_specific.expression.right);

    if(pl < pm)  fprintf(o, "(");
    RECURSE(dump_ast_internal, ast->ast_node_specific.expression.left);
    if(pl < pm)  fprintf(o, ") ");

    switch(ast->ast_node_specific.expression.op)
    {
	/* CEQ_OP and CNE_OP are also logical operators,
	   when not used in a multiple operator context
	*/
    case CEQ_OP:
	fprintf(o, " == ");
	break;

    case CNE_OP:
	fprintf(o, " != ");
	break;

    default:
	DUMP_ERROR(fprintf(o, " ^(multi_eq_op %d) ",
			   ast->ast_node_specific.expression.op));
	break;
    }

    /* This assumes that all operators are left-associative.
    */
    if(pm >= pr)  fprintf(o, "(");
    RECURSE(dump_ast_internal, ast->ast_node_specific.expression.right);
    if(pm >= pr)  fprintf(o, ") ");

    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_multi_rel_op)
{
    int pl, pm, pr;

    DUMP_PROLOGUE;
    pl = prec_of(ast->ast_node_specific.expression.left);
    pm = prec_of(ast);
    pr = prec_of(ast->ast_node_specific.expression.right);

    if(pl < pm)  fprintf(o, "(");
    RECURSE(dump_ast_internal, ast->ast_node_specific.expression.left);
    if(pl < pm)  fprintf(o, ") ");

    switch(ast->ast_node_specific.expression.op)
    {
	/* LT_OP, GT_OP, CGE_OP, CLE_OP are also logical operators,
	   when not used in a multiple operator context
	*/
    case LT_OP:
	fprintf(o, " < ");
	break;

    case GT_OP:
	fprintf(o, " > ");
	break;

    case CGE_OP:
	fprintf(o, " >= ");
	break;

    case CLE_OP:
	fprintf(o, " <= ");
	break;

    default:
	DUMP_ERROR(fprintf(o, " ^(multi_rel_op %d)",
			   ast->ast_node_specific.expression.op));
	break;
    }

    /* This assumes that all operators are left-associative.
    */
    if(pm >= pr)  fprintf(o, "(");
    RECURSE(dump_ast_internal, ast->ast_node_specific.expression.right);
    if(pm >= pr)  fprintf(o, ") ");

    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_array_call)
{
    DUMP_PROLOGUE;

    RECURSE(dump_ast_internal, ast->ast_node_specific.array_call.array);
    fprintf(o, "[ ");
    RECURSE(dump_ast_internal, ast->ast_node_specific.array_call.index);
    fprintf(o, "] ");

    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_post_symbol_call)
{
    DUMP_PROLOGUE;

    fprintf(o, "( ");
    RECURSE(dump_ast_internal, ast->ast_node_specific.post_symbol_call.expr);
    fprintf(o, ") ");
    RECURSE(dump_ast_internal, ast->ast_node_specific.post_symbol_call.symbol);

    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_time_literal)
{
    DUMP_PROLOGUE;
    /* ast->ast_node_specific.time_literal.lineno omitted */
    fprintf(o, "%s ",
	    ast->ast_node_specific.time_literal.text);
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_access)
{
    DUMP_PROLOGUE;
    RECURSE(dump_ast_internal, ast->ast_node_specific.access.symbol);
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_integer)
{
    DUMP_PROLOGUE;
    fprintf(o, " %llu ", ast->ast_node_specific.integer.value);
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_string)
{
    DUMP_PROLOGUE;
    /* I TBD: This is simplistic because we don't escape characters in
       the text that could terminate the string prematurely.
    */
    fprintf(o, " \"%s\" ", ast->ast_node_specific.string.text);
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_label_string)
{
    DUMP_PROLOGUE;
    /* I TBD: This is simplistic because we don't escape characters in
       the text that could terminate the string prematurely.
    */
    fprintf(o, " \"%s\" ", ast->ast_node_specific.label_string.text);
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_float)
{
    DUMP_PROLOGUE;
    fprintf(o, " %s ", ast->ast_node_specific.afloat.
	    text);
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_boolean)
{
    DUMP_PROLOGUE;
    fprintf(o, " %s ",
	    (ast->ast_node_specific.boolean.value) ? "true" : "false");
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_prototype)
{
    DUMP_PROLOGUE;
    RECURSE(dump_symbolId, ast->ast_node_specific.prototype.function_name);
    fprintf(o, "(");
    if(ast->ast_node_specific.prototype.parameters)
	RECURSE(dump_ast_internal, ast->ast_node_specific.prototype.parameters);
    fprintf(o, ");\n");
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_list_of_statements)
{
    DUMP_PROLOGUE;

    while (ast->next)
    {
	/* Dump element. */
	RECURSE(dump_ast_internal, ast->next);

	/* Terminate the element properly.  These AST nodes need to be
	   terminated differently (or not terminated at all) depending
	   on the outer context.
	*/
	if(ast->next->code == AST_CODE_ASSIGNMENT
	   || ast->next->code == AST_CODE_FUNCTION_CALL
	   || ast->next->code == AST_CODE_BUILTIN_MTD_CALL)
	    fprintf(o, ";\n");

	ast = ast->next;
    }

    DUMP_EPILOGUE;

}

DECL_DUMP_FUNCTOR(dump_statement)
{
    DUMP_PROLOGUE;
    switch(ast->ast_node_specific.statement.type)
    {
    case BLOCK_STATEMENT:
	fprintf(o, "{\n");

	/* This is a list of variable declarations and must likely be
	   dumped specially, using semicolon rather than comma as a
	   separator.  Use the generic dumper for the time being.
	*/
	if(ast->ast_node_specific.statement.part1)
	    RECURSE(dump_ast_internal,
		    ast->ast_node_specific.statement.part1);

	/* This is a list of statements. Dump with its own dumper.
	*/
	if(ast->ast_node_specific.statement.part2)
	RECURSE(dump_list_of_statements,
		ast->ast_node_specific.statement.part2);

	fprintf(o, "}\n");
	break;

    case IF_STATEMENT:
	fprintf(o, "if( ");
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.statement.part1);
	fprintf(o, ") ");
	assert(ast->ast_node_specific.statement.part2->code
	       == AST_CODE_LIST);
	/* This is the 'then' part, it is mandatory */
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.statement.part2->next
		);
	/* TBD: The 'else' part is optional.  If present, it is in the
	   second element of the list pointed by
	   ast->ast_node_specific.statement.part2.  Dump it when we
	   can reach the second element of a list.
	*/
	if (ast->ast_node_specific.statement.part2->next->next) {
	    fprintf(o, "else\n");
	    RECURSE(dump_ast_internal,
		    ast->ast_node_specific.statement.part2->next->next
		);
	}
	break;

    case FOR_STATEMENT:
	fprintf(o, "for (");
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.statement.part1);
	fprintf(o, ") ");
	RECURSE(dump_ast_internal,
		    ast->ast_node_specific.statement.part2);
	break;

    case WHILE_STATEMENT:
	fprintf(o, "while (");
	RECURSE(dump_ast_internal,
		    ast->ast_node_specific.statement.part1);
	fprintf(o, ") ");
	RECURSE(dump_ast_internal,
		    ast->ast_node_specific.statement.part2);
	break;

    case BREAK_OP:
	fprintf(o, "break;\n");
	break;

    case CONTINUE_OP:
	fprintf(o, "continue;\n");
	break;

    case LOOPOVER_OP:
	fprintf(o, "loop over ");
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.statement.part1);
	RECURSE(dump_ast_internal,
		    ast->ast_node_specific.statement.part2);
	break;

    case INCLUDE_OP:
	/* TBD: Partial implementation, only dump the top-level node
	   of the include sub-tree.  This is what we have for the time
	   being.

	   No need to quote the file name, because dump_label_string
	   does it by itself.
	*/
	fprintf(o, "include");
	RECURSE(dump_ast_internal, ast->ast_node_specific.statement.part2);
	fprintf(o, "\n");
	break;

    default:
	DUMP_ERROR(
	    fprintf(o,
		    "^(ast->ast_node_specific.statement.type=%d)",
		    ast->ast_node_specific.statement.type));
	break;
    }

    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_named_block)
{
    DUMP_PROLOGUE;
    RECURSE(dump_ast_internal, ast->ast_node_specific.named_block.name);
    RECURSE(dump_ast_internal, ast->ast_node_specific.named_block.scope);
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_named_block_def)
{
    DUMP_PROLOGUE;
    RECURSE(dump_symbolId, ast->ast_node_specific.named_block_def.symbol);
    fprintf(o, ": ");
    DUMP_EPILOGUE;
}

DECL_SPEC_FUNCTOR(dump_in_out, enum argument_type)
{
    DUMP_PROLOGUE;
    switch(pivot)
    {
    case ArgInType:
	fprintf(o, "in ");
	break;

    case ArgOutType:
	fprintf(o, "out ");
	break;

    default:
	DUMP_ERROR(fprintf(o, "^(argument_type=%d)", pivot));
	break;
    }
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_param)
{
    DUMP_PROLOGUE;
    RECURSE(dump_in_out, ast->ast_node_specific.param.in_out);

    RECURSE(dump_typeId_prefix, ast->ast_node_specific.param.typeid);
    fprintf(o, ": ");
    RECURSE(dump_ast_internal, ast->ast_node_specific.param.symbol);

    RECURSE(dump_typeId_postfix_decl, ast->ast_node_specific.param.typeid);
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_buffer_decl)
{
    DUMP_PROLOGUE;

    if(ast->ast_node_specific.buffer_decl.constant)
	fprintf(o, "const ");
    else
	fprintf(o, "var ");

    RECURSE(dump_typeId_prefix, ast->ast_node_specific.buffer_decl.typeid);
    fprintf(o, ": ");
    RECURSE(dump_ast_internal, ast->ast_node_specific.buffer_decl.symbol);
    RECURSE(dump_typeId_postfix_def, ast->ast_node_specific.buffer_decl.typeid);

    /* The initializer is optional and can be an arbitrary AST. */
    if(ast->ast_node_specific.buffer_decl.initializer)
    {
	fprintf(o, "= ");
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.buffer_decl.initializer);
    }

    fprintf(o, ";\n");
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_iterator)
{
    DUMP_PROLOGUE;

    RECURSE(dump_ast_internal, ast->ast_node_specific.iterator.collection);
    fprintf(o, "with ");
    RECURSE(dump_ast_internal, ast->ast_node_specific.iterator.iterator);
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_assignment)
{
    DUMP_PROLOGUE;

    RECURSE(dump_ast_internal, ast->ast_node_specific.assignment.left);
    fprintf(o, "= ");
    RECURSE(dump_ast_internal, ast->ast_node_specific.assignment.right);

    /* Do not terminate the assignment here because it must be
       terminated in different ways depending on the outer context.
    */
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_function_call)
{
    DUMP_PROLOGUE;

    RECURSE(dump_symbolId,
	    ast->ast_node_specific.function_call.function_name);
    fprintf(o, "( ");
    if(ast->ast_node_specific.function_call.arguments)
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.function_call.arguments);
    fprintf(o, ") ");

    /* Do not terminate the function call here because it must be
       terminated in different ways depending on the outer context.
    */
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_annotation)
{
    DUMP_PROLOGUE;

    fprintf(o, "@");
    /* This AST_CODE_LIST node must be dumped as a colon-separated
       list of symbols.
    */
	AST *tmp;
	tmp = ast->ast_node_specific.annotation.hierarchical_symbol;
	while(tmp->next)
	{
		RECURSE(dump_ast_internal,tmp->next);
		if (tmp->next->next == NULL)
		{
		}
		else
			fprintf(o, ": ");

		tmp = tmp->next;
	}
    RECURSE(dump_ast_internal, ast->ast_node_specific.annotation.scope);
    DUMP_EPILOGUE;
}


DECL_DUMP_FUNCTOR(dump_data_type)
{
    DUMP_PROLOGUE;

    switch(ast->ast_node_specific.type.type_info)
    {
    case TypeStruct:
	fprintf(o, "struct ");
	RECURSE(dump_symbolId, ast->ast_node_specific.type.symbol_id);
	if(cookie->full_dump)
	    fprintf(o, "/* declared @line %d */ ",
		    ast->ast_node_specific.type.lineno);
	fprintf(o, "{\n");
	RECURSE(dump_ast_internal, ast->ast_node_specific.type.symbol_list);
	fprintf(o, "};\n");
	break;

    case TypeEnum:
	/* I: TBD: Partial implementation, we should dump symbol_list
	   as a comma-separated list of symbols, rather than using
	   the standard dumper.
	*/
	fprintf(o, "enum ");
	RECURSE(dump_symbolId, ast->ast_node_specific.type.symbol_id);
	if(cookie->full_dump)
	    fprintf(o, "/* declared @line %d */ ",
		    ast->ast_node_specific.type.lineno);
	fprintf(o, "{\n");
	RECURSE(dump_ast_internal, ast->ast_node_specific.type.symbol_list);
	fprintf(o, "};\n");
	break;

    default:
	DUMP_ERROR(fprintf(o, "^(ast->ast_node_specific.type.type_info=%d)",
			   ast->ast_node_specific.type.type_info));
	break;

    }

    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_field)
{
    DUMP_PROLOGUE;

    RECURSE(dump_typeId_prefix, ast->ast_node_specific.field.type_spec);
    fprintf(o, ": ");
    RECURSE(dump_symbolId, ast->ast_node_specific.field.struct_field);
    RECURSE(dump_typeId_postfix_def, ast->ast_node_specific.field.type_spec);

    fprintf(o, ";\n");
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_builtin_mtd_call)
{
    DUMP_PROLOGUE;

    RECURSE(dump_ast_internal, ast->ast_node_specific.builtin_mtd_call.expr);
    fprintf(o, ".");
    RECURSE(dump_ast_internal, ast->ast_node_specific.builtin_mtd_call.symbol);
    fprintf(o, "(");
    /* I: TBD: This AST_CODE_LIST node must be dumped as a
       comma-separated list of symbols.  Use the generic dumper for
       the time being.
    */
    if(ast->ast_node_specific.builtin_mtd_call.arguments)
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.builtin_mtd_call.arguments);
    fprintf(o, ") ");

    /* Do not terminate the builtin method call here because it must
       be terminated in different ways depending on the outer context.
    */
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_field_call)
{
    DUMP_PROLOGUE;

    RECURSE(dump_ast_internal, ast->ast_node_specific.field_call.expr);
    fprintf(o, ".");
    RECURSE(dump_ast_internal, ast->ast_node_specific.field_call.field);
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_function_def)
{
    DUMP_PROLOGUE;

    RECURSE(dump_symbolId, ast->ast_node_specific.function_def.symbol_id);
    fprintf(o, "(");
    /* I: TBD: This AST_CODE_LIST node is a list of parameters and
       must be dumped as a comma-separated list of symbols.  Use the
       generic dumper for the time being.
    */
    if(ast->ast_node_specific.state_machine.parameter_list)
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.function_def.parameter_list);
    fprintf(o, ") ");
    RECURSE(dump_ast_internal, ast->ast_node_specific.function_def.block);
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_state_machine)
{
    DUMP_PROLOGUE;

    fprintf(o, "processdef ");
    RECURSE(dump_symbolId, ast->ast_node_specific.state_machine.symbol_id);
    fprintf(o, "(");
    /* I: TBD: This AST_CODE_LIST node is a list of parameters and
       must be dumped as a comma-separated list of symbols.  Use the
       generic dumper for the time being.

       The same note also applies to the other lists below.  They may
       need a custom dumper to obtain the right separator.
    */
    if(ast->ast_node_specific.state_machine.parameter_list)
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.state_machine.parameter_list);
    fprintf(o, ") {\n");
    if(ast->ast_node_specific.state_machine.subprocess_list)
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.state_machine.subprocess_list);
    if(ast->ast_node_specific.state_machine.var_decl_list)
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.state_machine.var_decl_list);
    if(ast->ast_node_specific.state_machine.common_block)
    {
	fprintf(o, "common ");
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.state_machine.common_block);
    }
    RECURSE(dump_ast_internal,
	    ast->ast_node_specific.state_machine.state_list);
    if(ast->ast_node_specific.state_machine.finally_block)
    {
	fprintf(o, "finally ");
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.state_machine.finally_block);
    }
    fprintf(o, "}\n");
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_proc_var)
{
    DUMP_PROLOGUE;

    if(ast->ast_node_specific.proc_var.is_static)
	fprintf(o, "static ");

    RECURSE(dump_ast_internal, ast->ast_node_specific.proc_var.decl);
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_proc_instance)
{
    DUMP_PROLOGUE;

    fprintf(o, "process ");
    RECURSE(dump_ast_internal,
	    ast->ast_node_specific.proc_instance.process_type);
    fprintf(o, ": ");
    RECURSE(dump_ast_internal,
	    ast->ast_node_specific.proc_instance.instance_name);
    fprintf(o, ";\n");
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_state_def)
{
    DUMP_PROLOGUE;
    RECURSE(dump_ast_internal, ast->ast_node_specific.state_def.state_name);
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_state)
{
    DUMP_PROLOGUE;
    fprintf(o, "state ");
    RECURSE(dump_ast_internal, ast->ast_node_specific.state.state_name);
    RECURSE(dump_ast_internal, ast->ast_node_specific.state.state_block);
    if(ast->ast_node_specific.state.triggers_list)
	RECURSE(dump_ast_internal, ast->ast_node_specific.state.triggers_list);
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_transition)
{
    DUMP_PROLOGUE;

    switch(ast->ast_node_specific.transition.on_after_type)
    {
    case ON_OP:
	fprintf(o, "on ( ");
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.transition.transition_condition);
	fprintf(o, ") ");
	break;

    case AFTER_OP:
	fprintf(o, "after ( ");
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.transition.time_elapsed);
	fprintf(o, ") ");
	if(ast->ast_node_specific.transition.transition_condition)
	{
	    fprintf(o, "if ( ");
	    RECURSE(dump_ast_internal,
		    ast->ast_node_specific.transition.transition_condition);
	    fprintf(o, ") ");
	}
	break;

    default:
	DUMP_ERROR(fprintf(o, "^(ast->ast_node_specific.transition.on_after_type=%d)",
			   ast->ast_node_specific.transition.on_after_type));
    }

    if(ast->ast_node_specific.transition.transition_code)
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.transition.transition_code);

    fprintf(o, "to ");
    RECURSE(dump_symbolId, ast->ast_node_specific.transition.symbol_id);
    fprintf(o, ";\n");
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_global_instance)
{
    DUMP_PROLOGUE;

    fprintf(o, "process ");
    RECURSE(dump_ast_internal,
	    ast->ast_node_specific.global_instance.process_type);
    fprintf(o, ": ");
    RECURSE(dump_ast_internal,
	    ast->ast_node_specific.global_instance.instance_name);

    /* A NULL time_trigger must be dumped as a pair of brackets
       without anything within them.  I: TBD: If it's not NULL, it
       must be dumped as a comma-separated list.  Use the generic
       dumper for the time being.
    */
    fprintf(o, "[ ");
    if(ast->ast_node_specific.global_instance.time_trigger)
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.global_instance.time_trigger);
    fprintf(o, "] ");

    /* Instead, a NULL cond_trigger results in nothing being dumped.
       cond_trigger is a single expression, so no need for the list
       dumper here.
    */
    if(ast->ast_node_specific.global_instance.cond_trigger)
    {
	fprintf(o, "[ ");
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.global_instance.cond_trigger);
	fprintf(o, "] ");
    }

    fprintf(o, "(");
    /* I: TBD: This AST_CODE_LIST node must be dumped as a
       comma-separated list.  Use the generic dumper for the time
       being.
    */
    if(ast->ast_node_specific.global_instance.argument_list)
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.global_instance.argument_list);

    fprintf(o, ");\n");
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_sm_prototype)
{
    DUMP_PROLOGUE;
    fprintf(o, "processdef ");
    RECURSE(dump_symbolId, ast->ast_node_specific.sm_prototype.sm_name);
    fprintf(o, "(");
    /* I: TBD: This AST_CODE_LIST node must be dumped as a
       comma-separated list.  Use the generic dumper for the time
       being.
    */
    if(ast->ast_node_specific.sm_prototype.parameters)
	RECURSE(dump_ast_internal,
		ast->ast_node_specific.sm_prototype.parameters);
    fprintf(o, ");\n");
    DUMP_EPILOGUE;
}

DECL_DUMP_FUNCTOR(dump_ast_internal)
{
    DUMP_PROLOGUE;

    if(ast == NULL)  DUMP_ERROR(fprintf(o, "^(nil)"));

    else if(! ast->common.ignore)
    {
	switch(ast->code)
	{
	case AST_CODE_LIST:
	    RECURSE(dump_list, ast);
	    break;

	case AST_CODE_VAR_DECL:
	    RECURSE(dump_var_decl, ast);
	    break;

	case AST_CODE_SYMBOL:
	    RECURSE(dump_symbol, ast);
	    break;

	case AST_CODE_INITIALIZER:
	    RECURSE(dump_initializer, ast);
	    break;

	case AST_CODE_FREQUENCY:
	    RECURSE(dump_frequency, ast);
	    break;

	    /* Codes for expressions */
	case AST_CODE_LOGICAL_OP:
	    RECURSE(dump_logical_op, ast);
	    break;

	case AST_CODE_ARITHMETIC_OP:
	    RECURSE(dump_arithmetic_op, ast);
	    break;

	case AST_CODE_MULTI_EQ_OP:
	    RECURSE(dump_multi_eq_op, ast);
	    break;

	case AST_CODE_MULTI_REL_OP:
	    RECURSE(dump_multi_rel_op, ast);
	    break;

	case AST_CODE_ARRAY_CALL:
	    RECURSE(dump_array_call, ast);
	    break;

	case AST_CODE_POST_SYMBOL_CALL:
	    RECURSE(dump_post_symbol_call, ast);
	    break;

	case AST_CODE_TIME_LITERAL:
	    RECURSE(dump_time_literal, ast);
	    break;

	case AST_CODE_ACCESS:
	    RECURSE(dump_access, ast);
	    break;

	case AST_CODE_INTEGER:
	    RECURSE(dump_integer, ast);
	    break;

	case AST_CODE_STRING:
	    RECURSE(dump_string, ast);
	    break;

	case AST_CODE_LABEL_STRING:
	    RECURSE(dump_label_string, ast);
	    break;

	case AST_CODE_FLOAT:
	    RECURSE(dump_float, ast);
	    break;

	case AST_CODE_BOOLEAN:
	    RECURSE(dump_boolean, ast);
	    break;

	    /* Statement-related codes */
	case AST_CODE_PROTOTYPE:
	    RECURSE(dump_prototype, ast);
	    break;

	case AST_CODE_STATEMENT:
	    RECURSE(dump_statement, ast);
	    break;

	case AST_CODE_NAMED_BLOCK:
	    RECURSE(dump_named_block, ast);
	    break;

	case AST_CODE_NAMED_BLOCK_DEF:
	    RECURSE(dump_named_block_def, ast);
	    break;

	case AST_CODE_PARAM:
	    RECURSE(dump_param, ast);
	    break;

	    /* AST_CODE_BUFFER cannot appear at the top level */

	case AST_CODE_BUFFER_DECL:
	    RECURSE(dump_buffer_decl, ast);
	    break;

	case AST_CODE_ITERATOR:
	    RECURSE(dump_iterator, ast);
	    break;

	case AST_CODE_ASSIGNMENT:
	    RECURSE(dump_assignment, ast);
	    break;

	case AST_CODE_FUNCTION_CALL:
	    RECURSE(dump_function_call, ast);
	    break;

	case AST_CODE_ANNOTATION:
	    RECURSE(dump_annotation, ast);
	    break;

	case AST_CODE_DATA_TYPE:
	    RECURSE(dump_data_type, ast);
	    break;

	case AST_CODE_FIELD:
	    RECURSE(dump_field, ast);
	    break;

	case AST_CODE_BUILTIN_MTD_CALL:
	    RECURSE(dump_builtin_mtd_call, ast);
	    break;

	case AST_CODE_FIELD_CALL:
	    RECURSE(dump_field_call, ast);
	    break;

	case AST_CODE_FUNCTION_DEF:
	    RECURSE(dump_function_def, ast);
	    break;

	case AST_CODE_STATE_MACHINE:
	    RECURSE(dump_state_machine, ast);
	    break;

	case AST_CODE_PROC_VAR:
	    RECURSE(dump_proc_var, ast);
	    break;

	case AST_CODE_PROC_INSTANCE:
	    RECURSE(dump_proc_instance, ast);
	    break;

	case AST_CODE_STATE_DEF:
	    RECURSE(dump_state_def, ast);
	    break;

	case AST_CODE_STATE:
	    RECURSE(dump_state, ast);
	    break;

	case AST_CODE_TRANSITION:
	    RECURSE(dump_transition, ast);
	    break;

	case AST_CODE_GLOBAL_INSTANCE:
	    RECURSE(dump_global_instance, ast);
	    break;

	case AST_CODE_SM_PROTOTYPE:
	    RECURSE(dump_sm_prototype, ast);
	    break;

	default:
	    DUMP_ERROR(fprintf(o, "^(ast->code=%d)", ast->code));
	    break;
	}
    }

    DUMP_EPILOGUE;
}

int Dump_AST(FILE *o, const AST *ast, const struct dump_opts *opts)
{
    struct dump_cookie cookie;

    init_cookie(&cookie, opts);
    return dump_ast_internal(o, ast, &cookie);
}
