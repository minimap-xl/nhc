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

#include "def_variable.h"
#include "rAST.h"

void defVar_declareGlobal(parser_Env *env, AST *variable_declaration)
{
    /* This function must declare a global variable, that is, as a
       minimum put it in the global symbol table associated to the
       environment.

       I TBD: Since this is related to how we handle symbol tables, it
       is empty for the time being.  The parser still works with an
       empty implementation because the sub-AST corresponding to the
       declaration is up-propagated by the grammar itself.
    */
}

void defVar_declareLocal(parser_Env *env, AST *variable_declaration)
{

}

void defVar_declareStatic(parser_Env *env, AST *variable_declaration)
{

}


void defVar_clearLocals(parser_Env *env, AST *parameter_list)
{

}

void defVar_clearProcessLocalImplicitVariables(parser_Env *env, AST *subprocess_list)
{
}

AST *defVar_makeAndDeclareProcessInstanceData(parser_Env *env)
{
    return NULL;
}

AST *defVar_makeAndDeclareNamedBlockDefinition(parser_Env *env, AST *symbol)
{
    /* This function creates an AST node with code AST_CODE_NAMED_BLOCK_DEF
       and saves its argument into it.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_NAMED_BLOCK_DEF;
    node->ast_node_specific.named_block_def.symbol = symbol;
    return node;
}

AST *defVar_makeAndDeclareStateDefinition(parser_Env *env, AST *state_name)
{
    /* This function creates an AST node with code AST_CODE_STATE_DEF
       and saves its argument into it.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_STATE_DEF;
    node->ast_node_specific.state_def.state_name = state_name;
    return node;
}

AST *defVar_makeDefinition(
    parser_Env *env,
    enum var_decl_op var_decl_op,
    typeId_t type_spec, AST *symbol, AST *initializer)
{
    /* This function must create an AST node with code
       AST_CODE_VAR_DECL and save its arguments into it.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_VAR_DECL;
    node->ast_node_specific.var_decl.op = var_decl_op;
    node->ast_node_specific.var_decl.typeid = type_spec;
    node->ast_node_specific.var_decl.symbol = symbol;
    node->ast_node_specific.var_decl.initializer = initializer;
    return node;
}

AST *defVar_makeInitializer(parser_Env *env, AST *initializer_element)
{
    /* This function must create an AST node with code
       AST_CODE_INITIALIZER.  Its only code-specific field is the
       initializer_element given to this function as argument.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_INITIALIZER;
    node->ast_node_specific.initializer.initializer_element =
	initializer_element;
    return node;
}

AST *defVar_makeAccess(parser_Env *env, AST *symbol)
{
    /* This function must create an AST node with code
       AST_CODE_ACCESS.  Its only code-specific field is the symbol
       given to this function as argument.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_ACCESS;
    node->ast_node_specific.access.symbol = symbol;
    return node;
}
