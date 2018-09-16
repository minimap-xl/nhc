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

#ifndef DEF_EXPRESSION_H
#define DEF_EXPRESSION_H

#include "rENV.h"
#include "rAST_stub.h"

enum operator_type {
	OR_OP,
	AND_OP,
	BITWISE_OR_OP,
	BITWISE_XOR_OP,
	BITWISE_AND_OP,
	BITWISE_NOT_OP,
	BITWISE_LEFT_SHIFT_OP,
	BITWISE_RIGHT_SHIFT_OP,
	CEQ_OP,
	CNE_OP,
	NOT_OP,
	PLUS_OP,
	MINUS_OP,
	NEG_OP,
	MUL_OP,
	DIV_OP,
	MOD_OP,
	LT_OP,
	GT_OP,
	CGE_OP,
	CLE_OP
};

AST *defExpr_makeAssignment(parser_Env *, AST *, AST *);

AST *defExpr_makeLogicalOp(parser_Env *, enum operator_type, AST *, AST *);

AST *defExpr_makeArithmeticOp(parser_Env *, enum operator_type, AST *, AST *);

AST *defExpr_makeMultipleEqualityExpression(parser_Env *, enum operator_type, AST *, AST *);

AST *defExpr_makeMultipleRelationalExpression(parser_Env *, uint32_t, AST *, AST *);

AST *defExpr_makeFieldCall(parser_Env *, AST *, AST *);

AST *defExpr_makeSymbol(parser_Env *, char *, int);

AST *defExpr_makeTimeLiteral(parser_Env *, char *, int);

AST *defExpr_makeFrequencyLiteral(parser_Env *, char *, int);

AST *defExpr_makeFloatLiteralNode(parser_Env *, char *, int);

AST *defExpr_makeStr(parser_Env *, char *, int);

AST *defExpr_makeLabelStr(parser_Env *, char *, int);

#endif /* DEF_EXPRESSION_H */
