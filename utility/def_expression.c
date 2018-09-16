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

#include "def_expression.h"
#include "rAST.h"

/* Precedence order of expression operators (lowest to highest), as
   specified by grammar rules (cpal_grammar.y).  It is encoded in the
   prec[] array below.

    1 OR_OP (logical)
    2 AND_OP (logical)
    3 BITWISE_OR_OP (arithmetic)
    4 BITWISE_XOR_OP (arithmetic)
    5 BITWISE_AND_OP (arithmetic)
    6 CEQ_OP, CNE_OP (multiple equality, logical)
    7 LT_OP, GT_OP, CGE_OP, CLE_OP (multiple relational, logical)
    8 BITWISE_LEFT_SHIFT_OP, BITWISE_RIGHT_SHIFT_OP (arithmetic)
    9 PLUS_OP, MINUS_OP (arithmetic)
   10 MUL_OP, DIV_OP, MOD_OP (arithmetic)
   11 NEG_OP (arithmetic), NOT_OP (logical), BITWISE_NOT_OP (arithmetic)

*/

static int prec[] = {
    [OR_OP] = 1,
    [AND_OP] = 2,
    [BITWISE_OR_OP] = 3,
    [BITWISE_XOR_OP] = 4,
    [BITWISE_AND_OP] = 5,
    [CEQ_OP] = 6,
    [CNE_OP] = 6,
    [LT_OP] = 7,
    [GT_OP] = 7,
    [CGE_OP] = 7,
    [CLE_OP] = 7,
    [BITWISE_LEFT_SHIFT_OP] = 8,
    [BITWISE_RIGHT_SHIFT_OP] = 8,
    [PLUS_OP] = 9,
    [MINUS_OP] = 9,
    [MUL_OP] = 10,
    [DIV_OP] = 10,
    [MOD_OP] = 10,
    [NEG_OP] = 11,
    [NOT_OP] = 11,
    [BITWISE_NOT_OP] = 11
};

AST *defExpr_makeAssignment(parser_Env *env, AST *left_expr, AST *right_expr)
{
    /* This function must create an AST node with code
       AST_CODE_ASSIGNMENT and fill it with its arguments.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_ASSIGNMENT;
    node->ast_node_specific.assignment.left = left_expr;
    node->ast_node_specific.assignment.right = right_expr;
    return node;
}

AST *defExpr_makeLogicalOp(
    parser_Env *env, enum operator_type operator,
    AST *left_expr, AST *right_expr)
{
    /* This function must create an AST node with code
       AST_CODE_LOGICAL_OP and .ast_node_specific.expression.op =
       operator.

       Moreover, like the other functions that create expression
       nodes, it must also fill the .ast_node_specific.expression.prec
       with an integer that indicates the precedence of the operator.
       This is used to avoid redundant parentheses.

       See notes below for _OP that may belong to different AST codes.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_LOGICAL_OP;
    node->ast_node_specific.expression.op = operator;
    node->ast_node_specific.expression.prec = prec[operator];
    node->ast_node_specific.expression.left = left_expr;
    node->ast_node_specific.expression.right = right_expr;
    return node;
}

AST *defExpr_makeArithmeticOp(
    parser_Env *env, enum operator_type operator,
    AST *left_expr, AST *right_expr)
{
    /* This function must create an AST node with code
       AST_CODE_ARITHMETIC_OP and .ast_node_specific.expression.op =
       operator.  See defExpr_makeLogicalOp() for info about prec.

       I TBD: Currently, defExpr_makeLogicalOp and
       defExpr_makeArithmeticOp are identical.  Factorize?
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_ARITHMETIC_OP;
    node->ast_node_specific.expression.op = operator;
    node->ast_node_specific.expression.prec = prec[operator];
    node->ast_node_specific.expression.left = left_expr;
    node->ast_node_specific.expression.right = right_expr;
    return node;
}

AST *defExpr_makeMultipleEqualityExpression(
    parser_Env *env, enum operator_type operator,
    AST *left_expr, AST *right_expr)
{
    /* This function must create an AST node with code
       AST_CODE_MULTI_EQ_OP and .ast_node_specific.expression.op =
       operator.  See defExpr_makeLogicalOp() for info about prec.

       Please also note that CEQ_OP and CNE_OP may be multi_eq or
       logical operators.  In theory, their precedence may be different
       in the two cases but I believe it is the same, it would be very
       confusing otherwise.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_MULTI_EQ_OP;
    node->ast_node_specific.expression.op = operator;
    node->ast_node_specific.expression.prec = prec[operator];
    node->ast_node_specific.expression.left = left_expr;
    node->ast_node_specific.expression.right = right_expr;
    return node;
}

AST *defExpr_makeMultipleRelationalExpression(
    parser_Env *env, enum operator_type comparison_type,
    AST *expression, AST *bitwise_shift_expr)
{
    /* This function must create an AST node with code
       AST_CODE_MULTI_REL_OP and .ast_node_specific.expression.op =
       operator.  See defExpr_makeLogicalOp() for info about prec.

       Please also note that LT_OP, GT_OP, CGE_OP, CLE_OP may be
       multi_rel or logical operators.  In theory, their precedence
       may be different in the two cases but I believe it is the same,
       it would be very confusing otherwise.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_MULTI_REL_OP;
    node->ast_node_specific.expression.op = comparison_type;
    node->ast_node_specific.expression.prec = prec[comparison_type];
    node->ast_node_specific.expression.left = expression;
    node->ast_node_specific.expression.right = bitwise_shift_expr;
    return node;
}

AST *defExpr_makeFieldCall(parser_Env *env, AST *expr, AST *field)
{
    /* This function must create an AST node with code
       AST_CODE_FIELD_CALL and fill it with its arguments. 'expr' is
       the postfix expression at the left of the field selector (the
       dot). 'field' is the field name at the right of the dot.

       'expr' may embed other field selectors.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_FIELD_CALL;
    node->ast_node_specific.field_call.expr = expr;
    node->ast_node_specific.field_call.field = field;
    return node;
}

AST *defExpr_makeSymbol(parser_Env *env, char *text, int lineno)
{
    /* This function must create an AST node with code
       AST_CODE_SYMBOL and save its arguments into it.

       Use strdup() on text because it probably comes from a flex
       buffer and it's going to evaporate soon.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_SYMBOL;
    node->ast_node_specific.symbol.text = strdup(text);
    node->ast_node_specific.symbol.lineno = lineno;
    return node;
}

AST *defExpr_makeTimeLiteral(parser_Env *env, char *text, int lineno)
{
    /* This function must create an AST node with code
       AST_CODE_TIME_LITERAL and save its arguments into it.

       Use strdup() on text because it comes from yytext, which is
       going to evaporate as the scanner proceeds to the next token.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_TIME_LITERAL;
    node->ast_node_specific.time_literal.text = strdup(text);
    node->ast_node_specific.time_literal.lineno = lineno;
    return node;
}

AST *defExpr_makeFrequencyLiteral(parser_Env *env, char *text, int lineno)
{
    /* This function must create an AST node with code
       AST_CODE_FREQUENCY and save its arguments into it.

       Use strdup() on text because it comes from yytext, which is
       going to evaporate as the scanner proceeds to the next token.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_FREQUENCY;
    node->ast_node_specific.symbol.text = strdup(text);
    node->ast_node_specific.symbol.lineno = lineno;
    return node;
}

AST *defExpr_makeFloatLiteralNode(parser_Env *env, char *text, int lineno)
{
    /* This function must create an AST node with code
       AST_CODE_FLOAT and save its arguments into it.

       Use strdup() on text because it comes from yytext, which is
       going to evaporate as the scanner proceeds to the next token.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_FLOAT;
    node->ast_node_specific.afloat.text = strdup(text);
    node->ast_node_specific.afloat.lineno = lineno;
    return node;
}

AST *defExpr_makeStr(parser_Env *env, char *text, int lineno)
{
    /* This function must create an AST node with code
       AST_CODE_STRING and save its arguments into it.

       Use strdup() on text because it comes from yytext, which is
       going to evaporate as the scanner proceeds to the next token.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_STRING;
    node->ast_node_specific.string.text = strdup(text);
    node->ast_node_specific.string.lineno = lineno;
    return node;
}

AST *defExpr_makeLabelStr(parser_Env *env, char *text, int lineno)
{
    /* This function must create an AST node with code
       AST_CODE_LABEL_STRING and save its arguments into it.

       Use strdup() on text because it comes from yytext, which is
       going to evaporate as the scanner proceeds to the next token.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_LABEL_STRING;
    node->ast_node_specific.label_string.text = strdup(text);
    node->ast_node_specific.label_string.lineno = lineno;
    return node;
}
