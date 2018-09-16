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

#include "rAST.h"

/* This function is not used by the parser.  It creates an empty
   AST_CODE_LIST, suitable for appending "things" to it by means of
   AST_addListLast().  It ignores 'program', like the other
   list-creation functions defined in this module, but it has been
   kept as a parameter anyway for consistency.

   An empty list has both .next and .tail set to NULL.  We should take
   this into account as a special case when we append.
*/
AST *AST_makeList0(env_program *program, int lineno)
{
    AST *list = AST_createNode();

    list->code = AST_CODE_LIST;
    list->ast_node_specific.list.tail = NULL;
    list->ast_node_specific.list.lineno = lineno;
    list->next = NULL;
    return list;
}

AST *AST_makeList1(env_program *program, AST *node, int lineno)
{
    AST *list = AST_createNode();

    list->code = AST_CODE_LIST;
    list->ast_node_specific.list.tail = node;
    list->ast_node_specific.list.lineno = lineno;
    list->next = node;
    return list;
}

AST *AST_makeList2(env_program *program, AST *node_1, AST *node_2, int lineno)
{
    AST *list = AST_createNode();

    list->code = AST_CODE_LIST;
    list->ast_node_specific.list.lineno = lineno;
	if (NULL != node_1)
	{
		list->next = node_1;
		if (NULL != node_2)
		{
			node_1->next = node_2;
			list->ast_node_specific.list.tail = node_2; 
		}
		else
			list->ast_node_specific.list.tail = node_1; 			
	}	
    return list;
}

AST *AST_makeList3(
    env_program *program, AST *node_1, AST *node_2, AST *node_3, int lineno)
{
    AST *list = AST_createNode();

    list->code = AST_CODE_LIST;
    list->ast_node_specific.list.lineno = lineno;

	list->next = node_1;
	node_1->next = node_2;
	node_2->next = node_3;
	list->ast_node_specific.list.tail = node_3; 	
    return list;
}

AST *AST_addListLast(env_program *program, AST *list, AST *new_node, int lineno)
{
    if(list->ast_node_specific.list.tail)
	/* Non-empty list, extend it at .tail. */
	list->ast_node_specific.list.tail->next = new_node;
    else
	/* Empty list, set .next */
	list->next = new_node;

    /* Adjust .tail */
    list->ast_node_specific.list.tail = new_node;
    return list;
}

/* Concatenate (and flatten) two lists. */
void AST_concatLists(env_program *program, AST *list1, AST *list2, int lineno)
{
    assert(list1->code == AST_CODE_LIST
	   && list2->code == AST_CODE_LIST);

    if(list1->ast_node_specific.list.tail)
    {
	/* list1 is not empty, keep its ->next
	   and link its tail to the head of list2
	*/

	list1->ast_node_specific.list.tail->next =
	    list2->next;
    }

    else
    {
	/* list1 is empty, set its ->next
	   to the head of list2
	*/
	list1->next = list2->next;
    }

    /* now list1->next is ok and its tail element points to the first
       element of list2, if any.  We must adjust the tail pointer of
       list1 if we actually added some elements to it, that is, list2
       was not empty.
    */
    if(list2->ast_node_specific.list.tail)
	list1->ast_node_specific.list.tail =
	    list2->ast_node_specific.list.tail;
}

symbolId_t AST_getSymbolId(AST *node)
{
    /* I: This function interns an AST node corresponding to a SYMBOL
       and returns its unique identifier.

       I TBD: For the time being, return directly the AST *
       we got as input and use it as a non-unique identifier.
    */
    return node;
}

AST *AST_makeIntegerNode(env_program *program, uint64_t value, int lineno, ...)
{
    /* This function must create an AST node with code
       AST_CODE_INTEGER and save its arguments into it.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_INTEGER;
    node->ast_node_specific.integer.value = value;
    node->ast_node_specific.integer.lineno = lineno;
    return node;
}

AST *AST_createNode()
{
	
	AST *newNode = calloc(1, sizeof(AST));
	assert("Failed to allocate a AST node" && (newNode != NULL));	

	/* Initialize the structure. */
	newNode->op = NONE;
	newNode->value.id.type = NO_SYMBOL_ID;

 
	newNode->code = ILLEGAL_AST_CODE;  


	newNode->next = NULL;
	
	return newNode;
}

/* TBD: node_1, node_2 should be replaced with a more sensible argument name. */
AST *AST_makeNode(env_program *program, enum statement_type type, uint32_t not_used, AST *subnode_1, AST *subnode_2, int lineno)
{
	/* Create a new AST node to be the parent node. Remember to
	 * initialize all fields. So that we don't need to take care of
	 * NULL pointers in the following. */

	AST *parent_node = AST_createNode();
	

	parent_node->code = AST_CODE_STATEMENT; 

	parent_node->ast_node_specific.statement.type = type;

	/* 
	 */
	if (NULL != subnode_1) {
		parent_node->ast_node_specific.statement.part1 = subnode_1;
	}

	if (NULL != subnode_2) {
		parent_node->ast_node_specific.statement.part2 = subnode_2;
	}

	return parent_node;
}


AST *AST_makeBooleanNode(env_program *program, bool value, int lineno)
{
    /* This function must create an AST node with code
       AST_CODE_BOOLEAN and save its arguments into it.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_BOOLEAN;
    node->ast_node_specific.boolean.value = value;
    node->ast_node_specific.boolean.lineno = lineno;
    return node;
}


char *echo(enum ast_node_code type)
{
	char *type_name="";
	switch(type)
	{
	case AST_CODE_LIST: 
		type_name="AST_CODE_LIST";
		break;

    case AST_CODE_VAR_DECL: 
		type_name="AST_CODE_VAR_DECL";
		break;

    case AST_CODE_SYMBOL:
		type_name="AST_CODE_SYMBOL";
		break;

    case AST_CODE_INITIALIZER:
		type_name="AST_CODE_INITIALIZER";
		break;

    case AST_CODE_FREQUENCY:
		type_name="AST_CODE_FREQUENCY";
		break;

    case AST_CODE_LOGICAL_OP:
		type_name="AST_CODE_LOGICAL_OP";
		break;

    case AST_CODE_ARITHMETIC_OP:
		type_name="AST_CODE_ARITHMETIC_OP";
		break;

    case AST_CODE_MULTI_EQ_OP:
		type_name="AST_CODE_MULTI_EQ_OP";
		break;

    case AST_CODE_MULTI_REL_OP:
		type_name="AST_CODE_MULTI_REL_OP";
		break;

    case AST_CODE_ARRAY_CALL:
		type_name="AST_CODE_ARRAY_CALL";
		break;

    case AST_CODE_POST_SYMBOL_CALL:
		type_name="AST_CODE_POST_SYMBOL_CALL";
		break;

    case AST_CODE_TIME_LITERAL:
		type_name="AST_CODE_TIME_LITERAL";
		break;

    case AST_CODE_ACCESS:
		type_name="AST_CODE_ACCESS";
		break;

    case AST_CODE_INTEGER:
		type_name="AST_CODE_INTEGER";
		break;

    case AST_CODE_STRING:
		type_name="AST_CODE_STRING";
		break;

    case AST_CODE_LABEL_STRING:
		type_name="AST_CODE_LABEL_STRING";
		break;

    case AST_CODE_FLOAT:
		type_name="AST_CODE_FLOAT";
		break;

    case AST_CODE_BOOLEAN:
		type_name="AST_CODE_BOOLEAN";
		break;

    case AST_CODE_STATEMENT:
		type_name="AST_CODE_STATEMENT";
		break;

    case AST_CODE_PROTOTYPE:
		type_name="AST_CODE_PROTOTYPE";
		break;

    case AST_CODE_NAMED_BLOCK:
		type_name="AST_CODE_NAMED_BLOCK";
		break;

    case AST_CODE_NAMED_BLOCK_DEF:
		type_name="AST_CODE_NAMED_BLOCK_DEF";
		break;

    case AST_CODE_PARAM:
		type_name="AST_CODE_PARAM";
		break;

    case AST_CODE_BUFFER:
		type_name="AST_CODE_BUFFER";
		break;

    case AST_CODE_BUFFER_DECL:
		type_name="AST_CODE_BUFFER_DECL";
		break;

    case AST_CODE_ITERATOR:
		type_name="AST_CODE_ITERATOR";
		break;

    case AST_CODE_ASSIGNMENT:
		type_name="AST_CODE_ASSIGNMENT";
		break;

    case AST_CODE_FUNCTION_CALL:
		type_name="AST_CODE_FUNCTION_CALL";
		break;

    case AST_CODE_ANNOTATION:
		type_name="AST_CODE_ANNOTATION";
		break;

    case AST_CODE_DATA_TYPE:
		type_name="AST_CODE_DATA_TYPE";
		break;

    case AST_CODE_FIELD:
		type_name="AST_CODE_FIELD";
		break;

    case AST_CODE_BUILTIN_MTD_CALL:
		type_name="AST_CODE_BUILTIN_MTD_CALL";
		break;

    case AST_CODE_FIELD_CALL:
		type_name="AST_CODE_FIELD_CALL";
		break;

    case AST_CODE_FUNCTION_DEF:
		type_name="AST_CODE_FUNCTION_DEF";
		break;

    case AST_CODE_STATE_MACHINE:
		type_name="AST_CODE_STATE_MACHINE";
		break;

    case AST_CODE_PROC_VAR:
		type_name="AST_CODE_PROC_VAR";
		break;

    case AST_CODE_PROC_INSTANCE:
		type_name="AST_CODE_PROC_INSTANCE";
		break;

    case AST_CODE_STATE_DEF:
		type_name="AST_CODE_STATE_DEF";
		break;

    case AST_CODE_STATE:
		type_name="AST_CODE_STATE";
		break;

    case AST_CODE_TRANSITION:
		type_name="AST_CODE_TRANSITION";
		break;

    case AST_CODE_GLOBAL_INSTANCE:
		type_name="AST_CODE_GLOBAL_INSTANCE";
		break;

    case AST_CODE_SM_PROTOTYPE:
		type_name="AST_CODE_SM_PROTOTYPE";
		break;

	default:
		type_name="ILLEGAL_AST_CODE";
		break;
	}
	
	return type_name;
}
