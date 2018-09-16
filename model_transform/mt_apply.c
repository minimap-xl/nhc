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

/* This module implements the MT_Apply function.

   See mt.h for a short description of what it does.
*/

#include <stdlib.h>
#include <string.h>
#include <mt.h>
#include "mt_private.h"

static AST *apply_on_node(AST *node, struct mt_cookie *cookie)
{
    /* Intercept NULL pointers */
    if(! node) return node;

    /* Use a generic MT function to determine whether we should act on
       the current node or not.
    */
    if(MT_Node_Matches_Pattern(node, cookie))
    {
	int retval;

	/* Apply the function.  If it returns a non-zero value,
	   store it in the 'retval' of the cookie and abort the
	   recursion.

	   To apply the function, we need
	   - the root of the tree, from the cookie
	   - the current node, we have it as an argument
	   - the higher-level cookie, also from the cookie
	*/
	retval = cookie->apply.apply_f(
	    cookie->apply.root, node, cookie->apply.depth,
	    cookie->apply.hl_cookie);

	if(retval)
	{
	    cookie->apply.retval = retval;
	    MT_To_Top_Level(cookie, NULL);
	}
    }

    return node;
}

static AST *apply(AST *node, struct mt_cookie *cookie)
{
	apply_on_node(node, cookie);

	cookie->apply.depth++;
	MT_Recurse(node, apply, cookie);
	cookie->apply.depth--;
	return node;
}

int MT_Apply(AST *tree, enum ast_node_code type, char *name,
	      mt_apply_f f, void *hl_cookie)
{
    struct mt_cookie cookie;

    /* Store 'type' and 'name' in the 'search_pattern' sub-structure
       of the mt_cookie.  Store 'f', 'tree', and 'hl_cookie' in the
       'apply' sub-structure.  Initialize 'retval' to 0.
    */
    cookie.search_pattern.ast_node_type = type;
    cookie.search_pattern.search_name = name;
    cookie.apply.apply_f = f;
    cookie.apply.root = tree;
    cookie.apply.hl_cookie = hl_cookie;
    cookie.apply.depth = 0;
    cookie.apply.retval = 0;

    /* Ignore the return value of MT_Transform, which is useless in
       this case.  Return the value of the 'retval' field instead.  It
       will still be 0 (see above) if apply_on_node didn't touch it.
    */
    (void)MT_Transform(tree, apply, &cookie);
    return cookie.apply.retval;
}
