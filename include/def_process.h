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

#ifndef DEF_PROCESS_H
#define DEF_PROCESS_H

#include "rENV.h"
#include "rAST_stub.h"


enum transition_type {
	ON_OP,
	AFTER_OP
};

AST *defProc_declareStateMachine(
    parser_Env *, symbolId_t, AST *, AST *, AST *, AST *, AST *, AST *);

AST *defProc_declareStateMachinePrototype(parser_Env *, symbolId_t, AST *);

void defProc_declareLocalInstance(parser_Env *, AST *);

void defProc_clearLocalInstances(parser_Env *);

AST *defProc_addStaticVariable(parser_Env *, AST *);

AST *defProc_addVariable(parser_Env *, AST *);

AST *defProc_makeInstance(parser_Env *, AST *, AST *);

AST *defProc_makeTransition(
    parser_Env *, enum transition_type, symbolId_t, AST *, AST*, AST *);

void defProc_define_global_process_implicit(parser_Env *, AST *);

AST *defProc_defineGlobalInstance(parser_Env *, AST *, AST *, AST *, AST *, AST *);

AST *process_makeState(parser_Env *, AST *, AST *, AST *);

uint32_t Process_State_getTypeID(uint32_t);

#endif /* DEF_PROCESS_H */
