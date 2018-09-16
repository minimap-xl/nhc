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

#ifndef DEF_TYPE_H
#define DEF_TYPE_H

#include "rENV.h"
#include "rAST_stub.h"


#ifdef SYMBOL_INTERNING
typedef enum typeId_t typeId_t;

enum typeId_t {
	NO_ID
};

#else
/* I TBD: For the time being, we don't have symbol interning, so we
   have to use symbolId_t also as typeId_t to be able to parse
   anything.  In a later version, we should definitely go back to the
   enum above.
*/
typedef symbolId_t typeId_t;

#define NO_ID NO_SYMBOL_ID
#endif

enum compound_struct {
	TypeEnum,
	TypeStruct
};

enum buffer_type {
	ARRAY_BUFFER,
	QUEUE_BUFFER,
	STACK_BUFFER,
	CHANNEL_BUFFER
};

AST *defType_declare(
    parser_Env *, symbolId_t, enum compound_struct, uint32_t, AST *, int);

AST *defType_makeField(parser_Env *, typeId_t, AST *);

typeId_t defType_getBuffer(parser_Env *, uint32_t, typeId_t, AST *);

typeId_t defType_lookup(parser_Env *,  symbolId_t);

char *Symbol_getName(env_program *, symbolId_t);

void defType_add_enum(parser_Env *, uint32_t, AST *); 

#endif /* DEF_TYPE_H */
