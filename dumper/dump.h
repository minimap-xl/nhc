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

/* This is the main header file of the AST dumper.  Besides containing
   all definitions needed by the dumper, it is also responsible of
   including any other header the public interface of the dumper may
   require.
*/

#ifndef DUMP_H
#define DUMP_H

#include <stdio.h>
#include <rAST.h>

/* AST dump options.  Currently unused, except to limit the maximum
   recursion depth.
*/
struct dump_opts {
    int max_depth;
};

int Dump_AST(FILE *o, const AST *ast, const struct dump_opts *opts);

#endif
