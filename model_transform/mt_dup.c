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

/* This module implements the MT_Dup function.

   See mt.h for a short description of what it does.
*/

#include <stdlib.h>
#include <string.h>
#include <mt.h>
#include "mt_private.h"

#define DUP_CHARP(p)  (p) = strdup(p)

static AST* dup_node(AST *node, struct mt_cookie *cookie)
{
    /* Intercept NULL pointers */
    if(! node) return node;

    /* Create a verbatim copy of node */
    AST *new_node = malloc(sizeof(AST));
    memcpy(new_node, node, sizeof(AST));

    /* Dup linked char * with strdup() if needed */
    switch(new_node->code)
    {
    case AST_CODE_SYMBOL:
	DUP_CHARP(new_node->ast_node_specific.symbol.text);
	break;

    case AST_CODE_FREQUENCY:
	DUP_CHARP(new_node->ast_node_specific.frequency.text);
	break;

    case AST_CODE_TIME_LITERAL:
	DUP_CHARP(new_node->ast_node_specific.time_literal.text);
	break;

    case AST_CODE_STRING:
	DUP_CHARP(new_node->ast_node_specific.string.text);
	break;

    case AST_CODE_LABEL_STRING:
	DUP_CHARP(new_node->ast_node_specific.label_string.text);
	break;

    case AST_CODE_FLOAT:
	DUP_CHARP(new_node->ast_node_specific.afloat.text);
	break;

    default:
	/* Nothing to do in all other cases */
	break;
    }

    return new_node;
}

static AST* dup(AST *node, struct mt_cookie *cookie)
{
    AST *new_node;

    new_node = dup_node(node, cookie);  /* This is the local dup */
    MT_Recurse(new_node, dup, cookie);
    return new_node;
}

AST *MT_Dup(AST *tree)
{
    struct mt_cookie cookie;

    /* Nothing to set in the cookie to implement this function,
       except the standard things Mt_Transform already takes care of
       by itself.
    */
    return MT_Transform(tree, dup, &cookie);
}
