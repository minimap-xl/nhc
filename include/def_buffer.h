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

#ifndef DEF_BUFFER_H
#define DEF_BUFFER_H

#include <stdbool.h>

#include "rENV.h"
#include "rAST_stub.h"
#include "def_type.h"  /* For typeId_t */


AST *defBuff_makeDefinition(parser_Env *, typeId_t, AST *, AST *, AST *, bool);

AST *defBuff_makeArrayCall(parser_Env *, AST *, AST *);

#endif /* DEF_BUFFER_H */
