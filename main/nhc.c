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

/* Very simple main program to play with model transformation. */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <unistd.h>
#include <libgen.h>

#include <rENV.h>
#include <rAST.h>
#include <cpal_grammar.h>
#include <cpal_lex.h>
#include <dump.h>
#include <ft.h>

#define MAX_NOPTS 2

/* This function assumes the the input file is already open and does
   not close it, because it may be stdin
*/
static AST *parse_user_model(FILE *cpal_file)
{
    AST *user_model = NULL;

    /* Parsing code borrowed from TT's test program */
    yyscan_t scanner;
    parser_Env env;

    struct parser_context v_pctx;
    struct env_program v_program;

    env.pctx = &v_pctx;
    env.program = &v_program;
    env.ienv = 0;

    /* Make sure these fields are properly initialized */
    env.program->root = NULL;
    env.pctx->include_stack_ptr = -1;

    if(yylex_init(&scanner))
	fprintf(stderr, "yylex_init failed\n");

    else
    {
	yyset_in(cpal_file, scanner);
	if(yyparse(scanner, &env))
	    fprintf(stderr, "yyparse failed\n");
	else
	{
	    /* Wow, we parsed the user model :)
	       Now extract the root of the AST.
	    */
	    user_model = env.program->root;
	}

	if(yylex_destroy(scanner))
	    fprintf(stderr, "yylex_destroy failed\n");
    }

    return user_model;
}

/* This function emits 'output' on the file indicated by 'name', or
   stdout if 'name' is "-".  It also beautifies the output with cpal2x
   if so requested.
*/
void emit_output(char *name, int beautify, AST *output)
{
    FILE *cpal_dump_dst;
    struct dump_opts dump_opts = { .max_depth = 100 };

    if(!beautify)
    {
	/* Use the given file name if it is not "-".  Otherwise, use
	   stdout.
	*/
	if(strcmp(name, "-"))
	    cpal_dump_dst = fopen(name, "w");
	else
	    cpal_dump_dst = stdout;

	fprintf(stderr, "Dump_AST(output): %d\n",
		Dump_AST(cpal_dump_dst, output, &dump_opts));

	if(cpal_dump_dst != stdout)  fclose(cpal_dump_dst);
    }

    else
    {
	/* Beautify: dump into a temporary file, then run cpal2x on
	   it, giving it the final file name.  Assumes that cpal2x is
	   reachable by system().
	*/
	char tmpfile[] = "nhc_tmp_XXXXXX";
	int tmpfd = mkstemp(tmpfile);

	if(tmpfd < 0)
	    fprintf(stderr, "Can't create temporary file\n");

	else
	{
	    /* Use fdopen to get a FILE *, more convenient to use than
	       the file descriptor we got from mkstemp.
	    */
	    FILE *tmpfs = fdopen(tmpfd, "w");
	    char sysbuf[PATH_MAX];

	    fprintf(stderr, "Dump_AST(output): %d\n",
		    Dump_AST(tmpfs, output, &dump_opts));

	    fclose(tmpfs);  /* This also closes tmpfd */

	    /* Run cpal2x.  Build the command line in sysbuf. */
	    snprintf(sysbuf, sizeof(sysbuf),
		     "cpal2x -Tcpal %s %s",
		     tmpfile,
		     strcmp(name, "-") ? name : "");

	    fprintf(stderr, "Running %s\n", sysbuf);
	    if(system(sysbuf) != 0)
		fprintf(stderr, "Sorry, cpal2x is not our friend today.\n");

	    unlink(tmpfile);
	}
    }
}

/* This function handles the --ftconfig options whose arguments have
   been stored in 'f_opts[]'.  'f_nopts' is the number of options.
   'base_out' is the base file name to be used as output, 'beautify'
   has the usual meaning, 'user_model' is the base used model to be
   combined with each --ftconfig option.
*/
void handle_ftconfig(
    AST *user_model,
    char *base_out, char *f_opts[], int f_nopts, int beautify)
{
    int i;

    for(i=0; i<f_nopts; i++)
    {
	char f_opt[PATH_MAX];
	char f_out[PATH_MAX];
	char *base_f_opt;
	FILE *ann_file;
	AST *ann_tree;

	/* According to POSIX, some (silly) implementations of
	   basename may modify their argument, so we need a copy.
	*/
	strcpy(f_opt, f_opts[i]);
	base_f_opt = basename(f_opt);

	/* The output file name is the concatenation of 'base_out'
	   (that comes from the command line) and the base portion of
	   the argument of the current --ftconfig option (that is, the
	   argument stripped of all path components but the last).
	*/
	strcpy(f_out, base_out);
	strcat(f_out, "_");
	strcat(f_out, base_f_opt);

	if((ann_file = fopen(f_opts[i], "r")) == NULL)
	    fprintf(stderr, "Error: opening --ftconfig %s\n", f_opts[i]);
	else
	{
	    if((ann_tree = parse_user_model(ann_file)) == NULL)
		fprintf(stderr, "Error: parsing --ftconfig %s\n", f_opts[i]);

	    else
	    {
		/* Duplicate user model, concatenate ann_tree,
		   parse annotations.
		*/
		AST *dup_user_model = MT_Dup(user_model);
		AST *output;
		assert(dup_user_model);

		AST_concatLists(NULL, dup_user_model, ann_tree, 0);
		output = parse_annotations(dup_user_model);

		/* Emit the output */
		emit_output(f_out, beautify, output);

		/* Free only dup_user_model because ann_tree is now
		   linked to it.  TBD: free it for real.
		*/
		MT_Free(output);
		MT_Free(dup_user_model);
	    }

	    fclose(ann_file);
	}
    }
}

static struct option options[] = {
    { "beautify", no_argument,       NULL, 'b' },
    { "ftconfig", required_argument, NULL, 'f' },
    { NULL,                       0, NULL,   0 }
};

int main(int argc, char *argv[])
{
    int opt;
    int beautify = 0;

    FILE *cpal_file;

    AST *user_model;
    AST *output;

    char *f_opts[MAX_NOPTS];
    int f_nopts = 0;

    while((opt = getopt_long(argc, argv, "bf:", options, NULL)) != -1)
    {
	switch(opt)
	{
	case 'b':
	    beautify = 1;
	    break;

	case 'f':
	    /* We have to save the arguments of these options because
	       we don't know where the main argument (the user model)
	       is yet, so we can not act on them right here.
	       Fortunately, since they come from argv[], saving a
	       pointer is enough.
	    */
	    if(f_nopts >= MAX_NOPTS)
		fprintf(stderr, "Too many --ftconfig options, ignored.\n");
	    else
		f_opts[f_nopts++] = optarg;
	    break;

	default:
	    break;
	}
    }

    /* Skip options, adjust argument vector.
       The first non-option argument is now in argv[0].
    */
    argc -= optind;
    argv += optind;

    /* Use the file name given as first argument on the command line
       as input, if it is present and is not "-".  Otherwise, use
       stdin.
    */
    if(argc >= 1 && strcmp(argv[0], "-"))
	cpal_file = fopen(argv[0], "r");
    else
	cpal_file = stdin;

    user_model = parse_user_model(cpal_file);
    if(cpal_file != stdin) fclose(cpal_file);

    if(!user_model)
	fprintf(stderr, "Error: error parsing the user model\n");

    if(f_nopts > 0)
    {
	if(argc < 2 || !strcmp(argv[1], "-"))
	    fprintf(stderr,
		    "Error: output to stdout unsupported with --ftconfig.\n");

	else
	    handle_ftconfig(user_model, argv[1], f_opts, f_nopts, beautify);
    }

    else
    {
	output = parse_annotations(user_model);
	emit_output(argc >= 2 ? argv[1] : "-", beautify, output);
    }

    return EXIT_SUCCESS;
}
