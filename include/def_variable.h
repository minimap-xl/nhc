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

#ifndef DEF_VARIABLE_H
#define DEF_VARIABLE_H

#include "rENV.h"
#include "rAST_stub.h"
#include "def_type.h"  /* For typeId_t */

enum var_decl_op {
	VARIABLE_DECL_OP,
	CONSTANT_DECL_OP
};

void defVar_declareGlobal(parser_Env *, AST *);

void defVar_declareLocal(parser_Env *, AST *);

void defVar_declareStatic(parser_Env *, AST *);

void defVar_clearLocals(parser_Env *, AST *);

void defVar_clearProcessLocalImplicitVariables(parser_Env *, AST *);

AST *defVar_makeAndDeclareProcessInstanceData(parser_Env *);

AST *defVar_makeAndDeclareNamedBlockDefinition(parser_Env *, AST *);

AST *defVar_makeAndDeclareStateDefinition(parser_Env *, AST *);

AST *defVar_makeDefinition(
    parser_Env *, enum var_decl_op, typeId_t, AST *, AST *);

AST *defVar_makeInitializer(parser_Env *, AST *);

AST *defVar_makeAccess(parser_Env *, AST *);

#endif /* DEF_VARIABLE_H */
