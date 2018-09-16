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

/* This module implements the MT_Transform and MT_To_Top_Level functions.

   See mt.h and mt_private.h for a short description of what they do.
*/

#include <mt.h>
#include "mt_private.h"

AST *MT_Transform(AST *tree, mt_trans_f trans_f, struct mt_cookie *cookie)
{
    AST *r;

    /* Save the top-level context into the cookie */
    if(setjmp(cookie->to_top_level) == 0)
    {
	/* Apply trans_f to the tree */
	r = trans_f(tree, cookie);
    }

    else
    {
	/* MT_To_Top_Level() was called.  Use the alternate return
	   value it stored in the cookie.
	*/
	r = cookie->alt_value;
    }

    return r;
}

void MT_To_Top_Level(struct mt_cookie *cookie, AST *alt_value)
{
    /* Store the alternate return value into the cookie */
    cookie->alt_value = alt_value;

    /* And let longjmp() play its magic for us :)

       longjmp() also propagates an integer, which is unused for now,
       so let's use 1, as a value it's as good as any other.
    */
    longjmp(cookie->to_top_level, 1);
}
