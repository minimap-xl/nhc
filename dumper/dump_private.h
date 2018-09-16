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

/* This is the private header file of the AST dumper.
*/

#ifndef DUMP_PRIVATE_H
#define DUMP_PRIVATE_H

struct dump_cookie
{
    const struct dump_opts *opts;  /* Link to dump options */
    int depth;  /* Current dump depth, checked wrt opts->max_depth */
    int full_dump;  /* Dump additional info as comments */
};


/* The following macros define generally used small excerpts of code
   that cannot be conveniently expressed as inline functions.
*/


/* Prologue and epilogue of a dumper function.  No semicolon because
   there is one already, immediately after the macro invocation.
*/
#define DUMP_PROLOGUE				\
    int st = 0;

#define DUMP_EPILOGUE				\
    return st

/* Do stmt, then flag a dump error.
*/
#define DUMP_ERROR(stmt)						\
    do									\
    {									\
	stmt;								\
	st = 1;								\
    }									\
    while(0)

/* This macro implements recursion within the dumper, using the given
   pivot.
*/
#define RECURSE(functor, pivot)						\
    do									\
    {									\
	if(cookie->depth >= cookie->opts->max_depth)			\
	    DUMP_ERROR(							\
		fprintf(o, "^(" #functor " omitted (max_depth))"));	\
	else								\
	{								\
	    cookie->depth++;						\
	    st |= functor(o, pivot, cookie);				\
	    cookie->depth--;						\
	}								\
    }									\
    while(0)

#define WITH_FULL_DUMP(stmt)						\
    do									\
    {									\
	cookie->full_dump = 1;						\
	stmt;								\
	cookie->full_dump = 0;						\
    }									\
    while(0)

/* The DECL_DUMP_FUNCTOR macro expands to the prototype declaration of
   a standard dump function, that is, a function responsible of
   dumping a syntactically-specific part of an AST.  Due to the way
   the code is structured, all functors must have exactly the same
   prototype.  See also the RECURSE macro above.

   The DECL_SPEC_FUNCTOR does the same, but for a dump function that
   takes a custom data type as pivot.
*/

#define DECL_DUMP_FUNCTOR(functor)					\
    int functor(FILE *o, const AST *ast, struct dump_cookie *cookie)

#define DECL_SPEC_FUNCTOR(functor, pivot_type)				\
    int functor(FILE *o, pivot_type pivot, struct dump_cookie *cookie)

DECL_DUMP_FUNCTOR(dump_ast_internal);

/* Functions to dump information in the AST tree that is not held in
   an AST node when we have interning.
*/
DECL_SPEC_FUNCTOR(dump_typeId, typeId_t);
DECL_SPEC_FUNCTOR(dump_typeId_prefix, typeId_t);
DECL_SPEC_FUNCTOR(dump_typeId_postfix_decl, typeId_t);
DECL_SPEC_FUNCTOR(dump_typeId_postfix_def, typeId_t);

DECL_SPEC_FUNCTOR(dump_symbolId, symbolId_t);

#endif
