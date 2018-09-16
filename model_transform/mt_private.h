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

/* This is the private header of the model transformation (MT)
   functions.
*/

#ifndef MT_PRIVATE
#define MT_PRIVATE

/* Abort the recursion initiated, for instance, by MT_Transform(),
   jump to the top-level, and return alt_value.
*/
void MT_To_Top_Level(struct mt_cookie *cookie, AST *alt_value);

/* Descend recursively on all children of node, in an unspecified
   order, applying trans_f to them and updating them in place
   according to its return value.
*/
void MT_Recurse(AST *node, mt_trans_f trans_f, struct mt_cookie *cookie);

/* This function returns true iff 'node' matches the pattern stored in
   the 'search_pattern' of 'cookie'.
*/
int MT_Node_Matches_Pattern(AST *node, struct mt_cookie *cookie);

#endif
