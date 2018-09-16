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

/* This module implements the functions that dump a type identifier,
   generated and returned by the defType_lookup and others.

   I TBD: Implemented by means of a straight recursion into
   dump_ast_internal because types are represented by AST * for the
   time being.
*/

#include <dump.h>
#include "dump_private.h"


DECL_SPEC_FUNCTOR(dump_typeId, typeId_t)
{
    DUMP_PROLOGUE;
    RECURSE(dump_ast_internal, pivot);
    DUMP_EPILOGUE;
}

static DECL_SPEC_FUNCTOR(dump_buffer_prefix, typeId_t)
{
    DUMP_PROLOGUE;
    switch(pivot->ast_node_specific.buffer.buffer_type)
    {
    case ARRAY_BUFFER:
	/* ARRAY_BUFFER requires postfix notation.  Dump only the
	   element type name in the prefix part.
	*/
	RECURSE(dump_typeId, pivot->ast_node_specific.buffer.type_spec);
	break;

    case QUEUE_BUFFER:
	fprintf(o, "queue < ");
	RECURSE(dump_typeId, pivot->ast_node_specific.buffer.type_spec);
	fprintf(o, "> ");
	break;

    case STACK_BUFFER:
	fprintf(o, "stack < ");
	RECURSE(dump_typeId, pivot->ast_node_specific.buffer.type_spec);
	fprintf(o, "> ");
	break;

    case CHANNEL_BUFFER:
	fprintf(o, "channel < ");
	RECURSE(dump_typeId, pivot->ast_node_specific.buffer.type_spec);
	fprintf(o, "> ");
	break;

    default:
	DUMP_ERROR(
	    fprintf(o, "^(buffer_type=%d)",
		    pivot->ast_node_specific.buffer.buffer_type));
	break;
    }
    DUMP_EPILOGUE;
}

DECL_SPEC_FUNCTOR(dump_typeId_prefix, typeId_t)
{
    DUMP_PROLOGUE;
    /* I: TBD: These checks should be adjusted when we have
       interning.
    */
    if(pivot->code == AST_CODE_BUFFER)
	RECURSE(dump_buffer_prefix, pivot);
    else
	RECURSE(dump_ast_internal, pivot);
    DUMP_EPILOGUE;
}

/* Dump the postfix portion of the AST_CODE_BUFFER as part of a
   declaration (no size).
*/
DECL_SPEC_FUNCTOR(dump_typeId_postfix_decl, typeId_t)
{
    DUMP_PROLOGUE;

    /* Only AST_CODE_BUFFER may require a postfix part */
    if(pivot->code == AST_CODE_BUFFER)
    {
	/* Special case for ARRAY_BUFFER, which requires postfix
	   notation.  dump_typeid_prefix, through dump_buffer_prefix
	   above, dumps only the element type name, then we add the
	   postfix brackets here.  I: TBD: These checks should be
	   adjusted when we have interning.
	*/
	if(pivot->ast_node_specific.buffer.buffer_type == ARRAY_BUFFER)
	    fprintf(o, "[] ");
    }

    DUMP_EPILOGUE;
}

/* Dump the postfix portion of the AST_CODE_BUFFER as part of a
   declaration (with size).
*/
DECL_SPEC_FUNCTOR(dump_typeId_postfix_def, typeId_t)
{
    DUMP_PROLOGUE;

    /* Only AST_CODE_BUFFER may require a postfix part */
    if(pivot->code == AST_CODE_BUFFER)
    {
	/* For all kinds of buffer, dump the 'size' between brackets */
	fprintf(o, "[ ");
	RECURSE(dump_ast_internal, pivot->ast_node_specific.buffer.size);
	fprintf(o, "] ");
    }

    DUMP_EPILOGUE;
}
