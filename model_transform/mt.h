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

/* This is the main header of the AST model transformation (MT)
   functions.  Besides containing all definitions needed by the model
   transformation functions themselves, it is also responsible of
   including any other header their public interface may require.
*/

#ifndef MT_H
#define MT_H

#include <setjmp.h> /* For jmp_buf */
#include <rAST.h>   /* For AST* */

/* Data type of the higher-level function passed to MT_Apply.  The
   function has access to the whole AST from the 'root', as well as
   the specific 'node' that triggered its execution.  'depth'
   indicates the depth of 'node' in the AST.
*/
typedef int (* mt_apply_f)(
    AST *root, AST *node, int depth, void *hl_cookie);

/* MT cookie, passed around during recursions.  It currently contains
   information to perform a non-local jump back to the top level (by
   means of longjmp) and, in that case, return an alternate value to
   the top-level caller.
*/
struct mt_cookie {
    jmp_buf to_top_level;
    AST* volatile alt_value;

    /* The sub-structures that follow contain all the
       function-specific data we may need to implement the various
       MT_... functions.  I did not use a union for the time being.

       If we ever need it, we can use a similar method as for AST
       nodes, keeping in mind that, in this case, we may use more than
       one sub-structure.
    */
    struct {
	char *old; /* Used by MT_Rename */
	char *new; /* Used by MT_Rename */
    } data;

    struct {
	enum ast_node_code ast_node_type;
	char *search_name;
	AST *found_node;
    } search_pattern;  /* Used by MT_Find
			  and MT_Node_Matches_Pattern */

    struct {
	mt_apply_f apply_f;
	AST *root;
	void *hl_cookie;
	int depth;
	volatile int retval;
    } apply; /* Used by MT_Apply */

    struct {
	AST *previous_node;
    } free_path;  /* Used by MT_Find */
};

/* Data type of the MT function.  This function performs a local
   transformation on the local node, then (optionally) traverses the
   sub-tree recursively, by means of one of the helper functions
   below.
*/
typedef AST* (* mt_trans_f)(
    AST *node, struct mt_cookie *cookie);



/* This is the top-level function to apply a certain transformation
   function trans_f to an AST.
*/
AST *MT_Transform(AST *tree, mt_trans_f trans_f, struct mt_cookie *cookie);

/* Specialized functions. */

AST *MT_Find(AST *tree, enum ast_node_code type, char *name);

/* This function applies function 'f' to all nodes of 'tree' that
   match a certain pattern, determined by MT_Node_Matches_Pattern
   according to 'type' and 'name'.  The function is given 'hl_cookie'
   as one of the arguments.  Since this is a higher-level cookie it is
   represented here as a void * instead of a more specific data type.
   If 'f' returns a non-zero value at any point, MT_Apply aborts and
   returns that value to the caller, otherwise it returns zero.
*/
int MT_Apply(AST *tree, enum ast_node_code type, char *name,
	      mt_apply_f f, void *hl_cookie);

/* This function duplicates an AST and returns the result. */
AST *MT_Dup(AST *tree);

/* This function renames an AST variable or data type in-place.  For
   variables, it takes shadowing into account.  Due to the structure
   of the CPAL language, no data type shadowing can ever take place
   because data type definitions (enum and struct definitions) may
   only appear at the top level.
*/
void MT_Rename(AST *tree, char *old, char *new);

/* This function makes all top-level definitions in 'tree' unique, by
   appending 'suffix' to their name.  It also adjusts all non-shadowed
   references to them in the whole AST.  It returns the number of
   definitions it changed.
*/
int MT_Make_Unique(AST *tree, char *suffix);

void MT_Insert_After(AST *tree, AST *node);

/* Free the memory allocated for a subtree, needs to be done in a
 * recursive way. */
void MT_Free(AST *tree);

#endif
