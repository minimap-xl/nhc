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

#ifndef RENV_H
#define RENV_H


#include <stdint.h>  /* uint32_t */
#include <string.h>  /* char */
#include <stdbool.h> /* bool */
#include <limits.h> /* LINE_MAX, PATH_MAX */


#ifndef PARSER_CONTEXT_STRUCT
#define PARSER_CONTEXT_STRUCT

typedef enum filepath_return_type {LfpFound, LfpNotFound, LfpFileNameTooLong} filepath_return_type;

/* Values retrieved from the C99 standard. */
#define MAX_INCLUDE_DEPTH      15      /* referred to as nesting level in the standard. */
#define MAX_PATH               PATH_MAX    /* should be 4095 according to C99 */
#define MAX_LINE               LINE_MAX    /* 4095, referred to as a logical source line */

struct parser_context {
void *parser_LineNode;
int   definition_line_no;
char *parseFilename;
int   lineno;
int   include_stack_ptr;
char *include_stack_filenames[MAX_INCLUDE_DEPTH];
int   line_no_save[MAX_INCLUDE_DEPTH];
void *include_stack_nodes[MAX_INCLUDE_DEPTH];
void *include_stack_buffer[MAX_INCLUDE_DEPTH];
char  scanned_line[MAX_LINE+1];
char *parser_include_path;
char *already_included_files[MAX_INCLUDE_DEPTH];
int   include_ptr;
};

#endif /* PARSER_CONTEXT_STRUCT */


#ifndef ENV_PROGRAM_STRUCT
#define ENV_PROGRAM_STRUCT

typedef struct env_program env_program;

struct env_program {
void *root;
};

#endif /* ENV_PROGRAM_STRUCT */

#ifndef PARSER_ENV_STRUCT
#define PARSER_ENV_STRUCT

typedef struct parser_Env parser_Env; 

struct parser_Env {
struct parser_context *pctx;
struct env_program *program;
uint32_t ienv;

};

#endif /* PARSER_ENV_STRUCT */





#endif /* RENV_H */
