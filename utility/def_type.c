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

#include "def_type.h"
#include "rAST.h"

AST *defType_declare(
    parser_Env * env, symbolId_t symbol_id, enum compound_struct type_info,
    uint32_t flag, AST *symbol_list, int lineno)
{
    /* This function creates a node with code AST_CODE_DATA_TYPE,
       which corresponds to a new data type definition, and fills it
       with its arguments.

       symbol_id is the name of the new type.  type_info can be either
       TypeEnum or TypeStruct, symbol_list is the list of enumerative
       constants (TypeEnum) or fields (TypeStruct).

    */
    AST *node = AST_createNode();

    node->code = AST_CODE_DATA_TYPE;
    node->ast_node_specific.type.symbol_id = symbol_id;
    node->ast_node_specific.type.type_info = type_info;
    node->ast_node_specific.type.flag = flag;
    node->ast_node_specific.type.symbol_list = symbol_list;
    node->ast_node_specific.type.lineno = lineno;
    return node;
}

AST *defType_makeField(parser_Env *env, typeId_t type_spec, AST *struct_field)
{
    /* This function creates a node with code AST_CODE_FIELD (a field
       of a struct definition) and fills it with its arguments.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_FIELD;
    node->ast_node_specific.field.type_spec = type_spec;
    node->ast_node_specific.field.struct_field = struct_field;
    return node;
}

typeId_t defType_getBuffer(
    parser_Env *env, enum buffer_type buffer_type,
    typeId_t type_spec, AST *size)
{
    /* This function creates a node with code AST_CODE_BUFFER and
       fills it with its arguments.  I: TBD: This is OK as long as we
       don't have interning.  When we do, this function should intern
       the new data type and return its id.

       'size' is the size of the buffer (can be a literal or an
       expression) when the buffer is defined (like in
       cpal_grammar.y:258).

       When the buffer is just declared (as in a parameter list,
       cpal_grammar.y:283-284), it is an AST_CODE_INTEGER node with
       UINT32_MAX in it, which acts as a marker.
    */
    AST *node = AST_createNode();

    node->code = AST_CODE_BUFFER;
    node->ast_node_specific.buffer.buffer_type = buffer_type;
    node->ast_node_specific.buffer.type_spec = type_spec;
    node->ast_node_specific.buffer.size = size;
    return node;
}

typeId_t defType_lookup(parser_Env *env,  symbolId_t symbol_id)
{
    /* I: This function is a bit complex.  It takes a symbol_id,
       returned by AST_getSymbolId() and should look it up in the type
       definition table presumably.

       AST_getSymbolId() takes as input an AST node corresponding to a
       SYMBOL (built by defExpr_makeSymbol()) and returns its unique
       identifier, presumably by interning it.

       I TBD: For the time being, use the symbolId_t we got as
       argument as a typeId_t.
    */
    return symbol_id;
}

void defType_add_enum(parser_Env *env, uint32_t proc_state_typeid, AST *state_identifier)
{

} 

/* I: TBD: This function is used only for parser error handling.
   Returning a dummy value for now to silence the compiler.
*/
char *Symbol_getName(env_program *program, symbolId_t symbol_id)
{
    return NULL;
}

