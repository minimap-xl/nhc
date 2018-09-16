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

/* This header provides a full definition of struct AST_node, while
   rAST_stub.h contains the corresponding stub definition.  Each AST
   node is described by a struct AST_node, also called AST thanks to
   the typedef in the stub.  The structure contains:

   1)  enum proc_optional_block op;
       struct  symbol_value value;

       These fields are required/dictated by the CPAL parser.

   2)  enum ast_node_code code;

	   A code/tag which indicates the node type, see TT's comments in
	   the commit log of r725

   3)  struct ast_node_common common;

       A data structure common to all possible types of AST nodes.

   4)  union { ... } ast_node_specific;

	   A container for data structures specific to each node type.

   This definition must come before we include any def_... headers
   because their function prototype make use of AST *.
*/

#ifndef RAST_H
#define RAST_H
#include <stdlib.h>          /* For calloc() */
#include <assert.h>          /* For assert() */
#include <stdio.h>           /* For printf() */

#include "def_variable.h"    /* For enum var_decl_op */
#include "def_type.h"        /* For typeId_t */
#include "def_expression.h"  /* For enum operator_type */
#include "def_parameter.h"   /* For enum argument_type */
#include "def_type.h"        /* For enum compound_struct */
#include "def_process.h"     /* For enum transition_type */

enum proc_optional_block {
	NONE,
	COMMON_BLOCK,
	FINALLY_BLOCK
};

enum statement_type {
	BLOCK_STATEMENT,
	IF_STATEMENT,
	FOR_STATEMENT,
	WHILE_STATEMENT,
	BREAK_OP,
	CONTINUE_OP,
	LOOPOVER_OP,
	INCLUDE_OP
};

enum ast_node_code {
    ILLEGAL_AST_CODE,       /* Catch-all for illegal codes (to TT: good idea) */
    AST_CODE_LIST,          /* I: -> struct tree_list XXX: Dummy
			       implementation, TT already designed the
			       structure though */
    AST_CODE_VAR_DECL,      /* -> struct tree_var_decl */
    AST_CODE_SYMBOL,        /* -> struct tree_symbol */
    AST_CODE_INITIALIZER,   /* -> struct tree_initializer */
    AST_CODE_FREQUENCY,     /* -> struct tree_frequency */
    AST_CODE_LOGICAL_OP,    /* -> struct tree_expression */
    AST_CODE_ARITHMETIC_OP, /* -> struct tree_expression */
    AST_CODE_MULTI_EQ_OP,   /* -> struct tree_expression */
    AST_CODE_MULTI_REL_OP,  /* -> struct tree_expression */
    AST_CODE_ARRAY_CALL,    /* -> struct tree_array_call */
    AST_CODE_POST_SYMBOL_CALL, /* -> struct tree_post_symbol_call */
    AST_CODE_TIME_LITERAL,  /* -> struct tree_time_literal */
    AST_CODE_ACCESS,        /* -> struct tree_access */
    AST_CODE_INTEGER,       /* -> struct tree_integer */
    AST_CODE_STRING,        /* -> struct tree_string */
    AST_CODE_LABEL_STRING,  /* -> struct tree_label_string */
    AST_CODE_FLOAT,         /* -> struct tree_float */
    AST_CODE_BOOLEAN,       /* -> struct tree_boolean */
    AST_CODE_STATEMENT,     /* -> struct tree_statement */
    AST_CODE_PROTOTYPE,     /* -> struct tree_prototype */
    AST_CODE_NAMED_BLOCK,   /* -> struct tree_named_block */
    AST_CODE_NAMED_BLOCK_DEF, /* -> struct tree_named_block_def */
    AST_CODE_PARAM,         /* -> struct tree_param */
    AST_CODE_BUFFER,        /* -> struct tree_buffer */
    AST_CODE_BUFFER_DECL,   /* -> struct tree_buffer_decl */
    AST_CODE_ITERATOR,      /* -> struct tree_iterator */
    AST_CODE_ASSIGNMENT,    /* -> struct tree_assignment */
    AST_CODE_FUNCTION_CALL, /* -> struct tree_function_call */
    AST_CODE_ANNOTATION,    /* -> struct tree_annotation */
    AST_CODE_DATA_TYPE,     /* -> struct tree_data_type */
    AST_CODE_FIELD,         /* -> struct tree_field */
    AST_CODE_BUILTIN_MTD_CALL, /* -> struct tree_builtin_mtd_call */
    AST_CODE_FIELD_CALL,    /* -> struct tree_field_call */
    AST_CODE_FUNCTION_DEF,  /* -> struct tree_function_def */
    AST_CODE_STATE_MACHINE, /* -> struct tree_state_machine */
    AST_CODE_PROC_VAR,      /* -> struct tree_proc_var */
    AST_CODE_PROC_INSTANCE, /* -> struct tree_proc_instance */
    AST_CODE_STATE_DEF,     /* -> struct tree_state_def */
    AST_CODE_STATE,         /* -> struct tree_state */
    AST_CODE_TRANSITION,    /* -> struct tree_transition */
    AST_CODE_GLOBAL_INSTANCE, /* -> struct tree_global_instance */
    AST_CODE_SM_PROTOTYPE   /* -> strict tree_sm_prototype */
};

struct symbol_value_id {
    symbolId_t type;
};

struct symbol_value {
	struct symbol_value_id id;
};

#ifndef AST_STRUCT
#define AST_STRUCT


struct ast_node_common {
	bool ignore;
};


/* This structure is used for data type definition, either enum or
   struct, created by defType_declare(), cpal_grammar.y:221 and other
   places.
*/
struct tree_data_type {
    symbolId_t symbol_id;
    enum compound_struct type_info;
    uint32_t flag;
    AST *symbol_list;
    int lineno;
};


/* This structure is used for nodes with code AST_CODE_SYMBOL, created
   by defExpr_makeSymbol(), cpal_lex.l:361.  Depending on whether we
   decide to implement the symbol table or not, it may hold a pointer
   to the name of the symbol and the line number, or an index into the
   symbol table.  I TBD:  For the time being, I assumed there will not
   be a symbol table and followed the first option.
*/
struct tree_symbol {
    char *text;  /* 2nd and 3rd argument of defExpr_makeSymbol */
    int lineno;
};


/* This structure is used for nodes with code AST_CODE_VAR_DECL,
   created by defVar_makeDefinition(), cpal_grammar.y:236.  It
   contains flags and attributes specific to variable and constant
   declarations.  The field 'op' tells which is which.
*/
struct tree_var_decl {
    enum var_decl_op op;  /* 2nd ... 5th args of defVar_makeDefinition */
    typeId_t typeid;
    AST *symbol;
    AST *initializer;
};


/* This structure holds the initializer of a variable declaration
   defVar_makeInitializer(), cpal_grammar.y:389.  It acts as a marker
   because there is a one-to-one relationship between this kind of
   node and the initializer_element it contains.
*/
struct tree_initializer {
    AST *initializer_element;  /* 2nd argument of defVar_makeInitializer */
};


/* This structure holds a frequency, built by
   defExpr_makeFrequencyLiteral, cpal_lex.l:358. I TBD: For the time
   being, I assume that the function above does nothing fancy with the
   literal, except strdup()ing the text here.  I also keep the lineno,
   for debugging's sake.
*/
struct tree_frequency {
    char *text;
    int lineno;
};


/* I: Filled TT's placeholder.  This structure holds a parameter
   declaration.
*/
struct tree_param {
    typeId_t typeid;
    AST *symbol;
    enum argument_type in_out;
};

/* This structure holds information about operators appearing in an
   expression, corresponding to the following AST codes:

   AST_CODE_LOGICAL_OP, cpal_grammar.y:412 and elsewhere
   AST_CODE_ARITHMETIC_OP, cpal_grammar.y:422 and elsewhere
   AST_CODE_MULTI_EQ_OP, cpal_grammar.y:437
   AST_CODE_MULTI_REL_OP, cpal_grammar.y:449
*/
struct tree_expression {
    enum operator_type op;
    int prec;
    AST *left;
    AST *right;
};


/* This structure holds information about AST_CODE_ARRAY_CALL, which
   is a reference to an element of an array, cpal_grammar.y:485.
*/
struct tree_array_call {
    AST *array;
    AST *index;
};


/* This structure holds information about AST_CODE_POST_SYMBOL_CALL,
   cpal_grammar.y:486.
*/
struct tree_post_symbol_call {
    AST *expr;
    AST *symbol;
};


/* This structure holds information about AST_CODE_TIME_LITERAL,
   defExpr_makeTimeLiteral, cpal_lex.l:357.  I TBD: For the time
   being, I assume that the function above does nothing fancy with the
   literal, except strdup()ing the text here.  I also keep the lineno,
   for debugging's sake.
*/
struct tree_time_literal {
    char *text;
    int lineno;
};


/* This structure encloses a reference to a SYMBOL made from within a
   primary_expression, cpal_grammar.y:492.  It acts as a marker
   because there is a one-to-one relationship between this kind of
   node and the SYMBOL it contains.
*/
struct tree_access {
    AST *symbol;
};


/* The following structures enclose:

   an integer, AST_makeIntegerNode, cpal_lex.l:360
   a string, defExpr_makeStr, cpal_lex.l:364
   a floating-point value, defExpr_makeFloatLiteralNode, cpal_lex.l:362
   a Boolean, AST_makeBooleanNode, cpal_lex.l:295

   I TBD: For the time being, I assume that the functions above do
   nothing fancy with the literal.  I also keep the lineno, for
   debugging's sake.
*/
struct tree_integer {
    uint64_t value;
    int lineno;
};

/* The only difference between tree_string and tree_label_string is
   that the former is created by defExpr_makeStr() while the latter is
   created by defExpr_makeLabelStr().
*/
struct tree_string {
    char *text;
    int lineno;
};

struct tree_label_string {
    char *text;
    int lineno;
};

struct tree_float {
    char *text;
    int lineno;
};

struct tree_boolean {
    bool value;
    int lineno;
};

struct tree_statement_list {

};

struct tree_proc_def {

};

struct tree_statement {
	enum statement_type type;
	AST *part1;
	AST *part2;
};

/* I: XXX: This is a dummy data type definition,
   please see the comments in rAST.c for details.
*/
struct tree_list {
	AST *tail;       /* To facilitate appending to the end of the list. */
    int lineno;
};

/* This data structure holds information about a function prototype.
   It is created by defFunc_definePrototype, cpal_grammar.y:157.
*/
struct tree_prototype {
	symbolId_t function_name;
	AST *parameters;
};

struct tree_named_block {
    AST *name;
    AST *scope;
};

struct tree_named_block_def {
    symbolId_t symbol;
};

/* This data structure holds information about a buffer,
   AST_CODE_BUFFER, performed by defType_getBuffer, in various parts
   of the grammar.
*/
struct tree_buffer {
    enum buffer_type buffer_type;
    typeId_t type_spec;
    AST *size;
};

/* This data structure holds information about a buffer (channel,
   queue, stack, array, ...) declaration, AST_CODE_BUFFER_DECL,
   performed by defBuff_makeDefinition, cpal_grammar.y:258.
*/
struct tree_buffer_decl {
    typeId_t typeid;
    AST *symbol;
    AST *size;
    AST *initializer;
    bool constant;
};

/* This data structure holds information about an iterator (used in a
   loop over statement), AST_CODE_ITERATOR.  This kind of node is
   created by defIter_makeDeclaration, cpal_grammar.y:362.
*/
struct tree_iterator {
    AST *iterator;
    AST *collection;
};

/* This data structure holds information about an assignment,
   AST_CODE_ASSIGNMENT.  This kind of node is created by
   defExpr_makeAssignment, cpal_grammar.y:390-391.
*/
struct tree_assignment {
    AST *left;
    AST *right;
};

/* This data structure holds information about an assignment,
   AST_CODE_FUNCTION_CALL.  This kind of node is created by
   defFunc_makeFunctionCall, cpal_grammar.y:509.
*/
struct tree_function_call {
	symbolId_t function_name;
	AST *arguments;
};

/* This data structure holds information about an annotation,
   AST_CODE_ANNOTATION.  This kind of node is created by
   defineAnnotation, cpal_grammar.y:147.
*/
struct tree_annotation {
    AST *hierarchical_symbol;  /* Colon-separated list of symbols */
    AST *scope; /* Scope the annotation pertains or applies to */
};

/* This data structure holds information about a field of a data
   structure, AST_CODE_FIELD.  This kind of node is created by
   defType_makeField, cpal_grammar.y:230 and other places.
*/
struct tree_field {
    typeId_t type_spec;
    AST *struct_field;
};

/* This data structure holds information about a builtin method call,
   AST_CODE_BUILTIN_MTD_CALL.  This kind of node is created by
   builtinMtd_makeCall, cpal_grammar.y:510.
*/
struct tree_builtin_mtd_call {
    AST *expr;
    AST *symbol;
    AST *arguments;
};

/* This data structure holds information about a field call (or, maybe
   we should call it 'field selection').  This kind of node is created
   by defExpr_makeFieldCall, cpal_grammar.y:514-515.
*/
struct tree_field_call {
    AST *expr;
    AST *field;
};

/* This data structure holds information about a function definition.
   This kind of node is created by defFunc_define, cpal_grammar.y:272.
*/
struct tree_function_def {
    symbolId_t symbol_id;
    AST *parameter_list;
    AST *block;
};

/* This data structure holds information about a state machine, the
   top level of a process definition.  This kind of node is created by
   defProc_declareStateMachine, cpal_grammar.y:168.
*/
struct tree_state_machine {
    symbolId_t symbol_id;
    AST *parameter_list;
    AST *subprocess_list;
    AST *var_decl_list;
    AST *common_block;
    AST *state_list;
    AST *finally_block;
};

/* This data structure is merely a wrapper for a AST_CODE_VAR_DECL or
   AST_CODE_BUFFER_DECL found within a process definition.  The flag
   'is_static' says whether the declaration is static or not.  This
   kind of node is created by defProc_addStaticVariable and
   defProc_addVariable, cpal_grammar.y:197-198.
*/
struct tree_proc_var {
    bool is_static;
    AST *decl;
};

/* This data structure holds information about a sub-process instance
   within a process definition.  This kind of node is created by
   defProc_makeInstance, cpal_grammar.y:316.
*/
struct tree_proc_instance {
    AST *process_type;
    AST *instance_name;
};

/* This data structure holds information about the state definition,
   namely, the name of the state.  This kind of node is created by
   defVar_makeAndDeclareStateDefinition, cpal_grammar.y:343.
*/
struct tree_state_def {
    AST *state_name;
};

/* This data structure holds information about a state within a
   process definition.  This kind of node is created by
   process_makeState, cpal_grammar.y:340.
*/
struct tree_state {
    AST *state_name;
    AST *state_block;
    AST *triggers_list;
};

/* This data structure holds information about a state transition
   within a process definition.  This kind of node is created by
   defProc_makeTransition, cpal_grammar.y:378-383.
*/
struct tree_transition {
    enum transition_type on_after_type;
    symbolId_t symbol_id;
    AST *transition_condition;
    AST *time_elapsed;
    AST *transition_code;
};

/* This data structure holds information about a process instance
   in global context.  This kind of node is created by
   defProc_defineGlobalInstance, cpal_grammar.h:323.
*/
struct tree_global_instance {
    AST *process_type;
    AST *instance_name;
    AST *time_trigger;
    AST *cond_trigger;
    AST *argument_list;
};

/* This data structure holds information about a process (called state
   machine in the grammar) prototype.  It is similar to
   tree_prototype, which pertains to a function prototype.  It is
   created by defProc_declareStateMachinePrototype,
   cpal_grammar.y:202.
*/
struct tree_sm_prototype {
	symbolId_t sm_name;
	AST *parameters;
};

struct AST_node {
    enum proc_optional_block op;
    struct  symbol_value value;

    /* Type of an AST node */
    enum ast_node_code code;

    /* Structure common to all types of AST node */
    struct ast_node_common common;

    /* Union that encloses the node code-dependent parts */
    union {
	struct tree_list list;
	struct tree_data_type type;
	struct tree_symbol symbol;
	struct tree_var_decl var_decl;  /* Variable and constant declaration */
	struct tree_initializer initializer; /* Declaration initializer */
	struct tree_frequency frequency; /* Frequency */
	struct tree_param param;
	struct tree_expression expression;  /* Expression operators */
	struct tree_array_call array_call;  /* Ref. to array element */
	struct tree_post_symbol_call post_symbol_call;  /* Postfix call (?) */
	struct tree_time_literal time_literal;
	struct tree_access access;  /* Access to a sym from within a expr */
	struct tree_integer integer;
	struct tree_string string;
	struct tree_label_string label_string;
	struct tree_float afloat;  /* Can't use float */
	struct tree_boolean boolean;
	struct tree_statement statement;
	struct tree_statement_list stmt_list;
	struct tree_proc_def proc_def;
	struct tree_prototype prototype;
	struct tree_named_block named_block;
	struct tree_named_block_def named_block_def;
	struct tree_buffer buffer;
	struct tree_buffer_decl buffer_decl;
	struct tree_iterator iterator;
	struct tree_assignment assignment;
	struct tree_function_call function_call;
	struct tree_annotation annotation;
	struct tree_field field;
	struct tree_builtin_mtd_call builtin_mtd_call;
	struct tree_field_call field_call;
	struct tree_function_def function_def;
	struct tree_state_machine state_machine;
	struct tree_proc_var proc_var;
	struct tree_proc_instance proc_instance;
	struct tree_state_def state_def;
	struct tree_state state;
	struct tree_transition transition;
	struct tree_global_instance global_instance;
	struct tree_sm_prototype sm_prototype;

    } ast_node_specific ;  /* End of union */

    struct AST_node *next;
};

#endif /* AST_STRUCT */


AST *AST_makeList0(env_program *, int);

AST *AST_makeList1(env_program *, AST *, int);

AST *AST_makeList2(env_program *, AST *, AST *, int);

AST *AST_makeList3(env_program *, AST *, AST *, AST *, int);

AST *AST_addListLast(env_program *, AST *, AST *, int);

void AST_concatLists(env_program *, AST *, AST *, int);

/* TT_Note: here we assume this function returns the index to the
 * symbol table for a particular symbol. */

symbolId_t AST_getSymbolId(AST *);

/* Note: this function expects variable number of arguments. */

AST *AST_makeIntegerNode(env_program *, uint64_t, int, ...);

AST *AST_createNode();

AST *AST_makeNode(env_program *, enum statement_type, uint32_t, AST *, AST *, int);

AST *AST_makeBooleanNode(env_program *, bool, int);

char *echo(enum ast_node_code type);

#endif /* RAST_H */
