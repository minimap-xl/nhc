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

#include <string.h>
#include <mt.h>
#include "mt_private.h"


static void free_node(AST *tree, struct mt_cookie *cookie)
{
	if (! tree) return;

	fprintf(stderr, "free_node(): I am going to free a node of type %s", echo(tree->code));
	if (tree->code == AST_CODE_SYMBOL)
		fprintf(stderr, ", with the name %s", tree->ast_node_specific.symbol.text);	
	fprintf(stderr, "\n");

	fprintf(stderr, "free_node(): The previous node is of type %s", echo(cookie->free_path.previous_node->code));
	if (cookie->free_path.previous_node->code== AST_CODE_SYMBOL)
		fprintf(stderr, ", with the name %s", cookie->free_path.previous_node->ast_node_specific.symbol.text);	
	fprintf(stderr, "\n\n");

	if (tree->code == AST_CODE_SYMBOL)
		free(tree->ast_node_specific.symbol.text);

	if (cookie->free_path.previous_node->code == AST_CODE_LIST)
	{
		if (cookie->free_path.previous_node->ast_node_specific.list.tail != tree)
			cookie->free_path.previous_node->next = tree->next;
		else
			cookie->free_path.previous_node->ast_node_specific.list.tail = NULL;
	}

	free(tree);
	tree = NULL;
}

static AST *do_free(AST *tree, struct mt_cookie *cookie)
{
	if (tree->code != AST_CODE_SYMBOL){
		cookie->free_path.previous_node = tree;
		fprintf(stderr, "do_free(): Follow the visiting path of the tree,  now the previous node is of type %s", echo(cookie->free_path.previous_node->code));
		if (cookie->free_path.previous_node->code== AST_CODE_SYMBOL)
			fprintf(stderr, ", with the name %s", cookie->free_path.previous_node->ast_node_specific.symbol.text);
		fprintf(stderr, "\n\n");
	}


	MT_Recurse(tree, do_free, cookie);


	free_node(tree, cookie);


	return tree;

}

#if 1
void MT_Free(AST *tree)
{
	if (!tree) return;
	else 
		tree->common.ignore=true;
}
#endif 

#if 0
/* Free the memory allocated for a subtree, needs to be done in a
 * recursive way. */
void MT_Free(AST *tree)
{
	if (!tree) return;

    struct mt_cookie cookie;
	cookie.free_path.previous_node = tree;

	fprintf(stderr, "MT_Free(): Initialize the previous node, it is of type %s", echo(cookie.free_path.previous_node->code));
	if (cookie.free_path.previous_node->code== AST_CODE_SYMBOL)
		fprintf(stderr, ", with the name %s", cookie.free_path.previous_node->ast_node_specific.symbol.text);
	fprintf(stderr, "\n\n");


	(void) MT_Transform(tree, do_free, &cookie);

	//fprintf(stderr, "The tree is NULL or not %d\n", tree->ast_node_specific.type.type_info);
}
#endif
