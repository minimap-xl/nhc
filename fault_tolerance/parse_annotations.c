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

/* This function parses @dependability annotations and calls the
   corresponding fault tolerance functions.
*/

/* Enable debugging printouts if needed */
#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rENV.h>
#include <rAST.h>
#include <cpal_grammar.h>
#include <cpal_lex.h>
#include <ft.h>

#ifdef DEBUG
#include <dump.h>
#endif

/* When this symbol is defined, an artificial entry is added to the
   ft_table below, to test parse_annotations().  Define when needed.
*/
#define TEST_FT_F

/* This is the data type of the main ft functions.
*/
typedef void (* ft_f)(
    int seq,         /* Call sequence number */
    AST *user_model, /* AST to operate upon */
    AST *arguments,  /* Args from the annotation, linked by ->next */
    AST *skeleton,   /* Parsed skeleton */
    AST *output      /* Output buffer */
    );

/* This is the data type of pre- and post-processing functions.
*/
typedef void (* pp_f)(
    int seq,         /* Call sequence number */
    AST *user_model, /* AST to operate upon */
    AST *skeleton,   /* Parsed skeleton */
    AST *output      /* Output buffer */
    );

#ifdef TEST_FT_F

/* Test ft function.  It appends the 'user_model' and 'skeleton' to
   the 'output' after making all symbols unique by using the suffix it
   founds in the first 'argument'.
*/
static void test_ft_f(
    int seq, AST *user_model, AST *arguments, AST *skeleton, AST *output)
{
    fprintf(stderr, "\e[1;31mHelloooo, this is test_ft_f seq=%d\e[0m\n", seq);

#ifdef DEBUG
    struct dump_opts dump_opts = { .max_depth = 100 };
    AST *arg;

    fprintf(stderr, "  \e[1;31mUser_model:\e[0m\n");
    Dump_AST(stderr, user_model, &dump_opts);
    fprintf(stderr, "\n  \e[1;31mSkeleton:\e[0m\n");
    Dump_AST(stderr, skeleton, &dump_opts);

    arg = arguments;
    while(arg)
    {
	fprintf(stderr, "\n  \e[1;31mArgument:\e[0m\n");
	Dump_AST(stderr, arg, &dump_opts);
	arg = arg->next;
    }

    fprintf(stderr, "\n");
#endif

    assert(arguments && arguments->code == AST_CODE_SYMBOL);
    AST *dup_user = MT_Dup(user_model);
    AST *dup_skeleton = MT_Dup(skeleton);

    MT_Make_Unique(dup_user, arguments->ast_node_specific.symbol.text);
    MT_Make_Unique(dup_skeleton, arguments->ast_node_specific.symbol.text);

    AST_concatLists(NULL, output, dup_user, 0);
    AST_concatLists(NULL, output, dup_skeleton, 0);

#ifdef DEBUG
    fprintf(stderr, "\n  \e[1;31mOutput:\e[0m\n");
    Dump_AST(stderr, output, &dump_opts);
#endif

}

/* Test ft pre- and post-processor.  These functions do nothing except
   printing a message.
*/
static void test_pre_f(
    int seq, AST *user_model, AST *skeleton, AST *output)
{
    fprintf(stderr, "\e[1;31mHelloooo, this is test_pre_f seq=%d\e[0m\n", seq);
}

static void test_post_f(
    int seq, AST *user_model, AST *skeleton, AST *output)
{
    fprintf(stderr, "\e[1;31mGoodbyee, this is test_post_f seq=%d\e[0m\n", seq);
}
#endif

/* I TBD: Add one row to this table for each ft function. */
static const struct ft_desc
{
    char *name;     /* Symbolic name of the ft function */
    char *skeleton; /* Its skeleton */
    ft_f func;      /* Ft function to be called */
    pp_f pre;       /* Pre-processing function */
    pp_f post;      /* Post-processing function */
}
    ft_table[] =
    {
	{"nvp", "NVP_skeleton.cpal",
	 NVP_driver, NVP_pre_processor, NVP_post_processor},
#ifdef TEST_FT_F
	/* Extra row, just for testing */
	{"test", "test_skeleton.cpal", test_ft_f, test_pre_f, test_post_f}
#endif
    };

#define N_FT_DESC (sizeof(ft_table)/sizeof(struct ft_desc))

/* Cache for parsed skeleton (and, if needed, for other things as
   well).  It also stores how many times each ft function has been
   invoked, in this way we can decide whether we should run the
   corresponding post-processing function.  The cache has one row for
   each row of the ft table above.
*/
static struct ft_cache
{
    AST *p_skeleton;  /* Parsed skeleton */
    int n_calls; /* Number of calls to this ft function */
}
    ft_cache_table[N_FT_DESC];


/* This is the cookie given to parse_annotation() every time it is
   called.  Currently it holds the current call sequence number and
   output AST.
*/
struct parse_annotations_cookie
{
    int seq;
    AST *output;
};


/* Parse a skeleton given its name and return the corresponding AST.

   This function looks for the skeleton in a list of colon-separated
   paths retrieved from the environment variable CPAL_SKELETON_PATH.
   If the environment variable is undefined, "." is used as default.

   The function returns NULL when unsuccessful.
*/
AST *parse_skeleton(char *name)
{
    AST *skeleton = NULL;

    yyscan_t scanner;
    parser_Env env;

    struct parser_context v_pctx;
    struct env_program v_program;

    char *sk_paths, *sk_path;
    char sk_name[PATH_MAX];

    FILE *cpal_file = NULL;

    env.pctx = &v_pctx;
    env.program = &v_program;
    env.ienv = 0;

    /* Make sure these fields are properly initialized */
    env.program->root = NULL;
    env.pctx->include_stack_ptr = -1;

    /* Get the list of paths to try from the environment variable
       CPAL_SKELETON_PATH.  If undefined, use "." as default.
       Duplicate the list because strtok modifies is.
    */
    sk_paths = getenv("CPAL_SKELETON_PATH");
    if(sk_paths == NULL)  sk_paths = ".";
    sk_paths = strdup(sk_paths);

    /* Parse sk_paths as a colon-separated list of paths */
    for(sk_path = strtok(sk_paths, ":");
	sk_path;
	sk_path = strtok(NULL, ":"))
    {
	/* Yes, a hardwired '/' is POSIX */
	snprintf(sk_name, PATH_MAX, "%s/%s", sk_path, name);
	fprintf(stderr, "Trying to open skeleton %s\n", sk_name);

	if((cpal_file = fopen(sk_name, "r")) != NULL)
	    break;
    }

    free(sk_paths);

    if(cpal_file == NULL)
	fprintf(stderr, "Can't find %s\n", name);

    else
    {
	if(yylex_init(&scanner))
	    fprintf(stderr, "yylex_init failed\n");

	else
	{
	    yyset_in(cpal_file, scanner);
	    if(yyparse(scanner, &env))
		fprintf(stderr, "yyparse failed\n");
	    else
	    {
		skeleton = env.program->root;
	    }

	    if(yylex_destroy(scanner))
		fprintf(stderr, "yylex_destroy failed\n");
	}

	fclose(cpal_file);
    }

    if(!skeleton)
	fprintf(stderr, "Warning: something wrong with skeleton %s\n",
		name);

    return skeleton;
}


/* Initialize ft_cache_table.  In the initial state, a cache row has
   a NULL p_skeleton (because the skeleton has not been parsed yet)
   and a zero n_calls (because the row has never been used).  We can
   use N_FT_DESC because ft_table and ft_cache_table have the same
   number of rows.
*/
static void init_ft_cache(void)
{
    int i;

    for(i=0; i<N_FT_DESC; i++)
    {
	ft_cache_table[i].p_skeleton = NULL;
	ft_cache_table[i].n_calls = 0;
    }
}

/* Clear the ft_cache_table.  TBD: Be careful if we decide to destroy
   the skeletons here, because some ft functions may place references
   to them in their output, rather than copying.
*/
static void clear_ft_cache(void)
{
    /* Empty implementation for now.  This is a memory leak, but the
       calling process is going to terminate (and free all memory)
       anyway and it is safer until we define precise memory
       management rules.
    */
}

/* Update ft_cache_table[i], fetching the skeleton if necessary.
   Return the skeleton.  This function is also responsible of updating
   .n_call.  We may return a NULL skeleton in two cases:

   1) the ft function has no skeleton associated to it, that is,
      the .skeleton in ft_table is NULL.  This is somewhat borderline,
      but can still be useful.

   2) the ft function has a skeleton associated to it, but we were
      unable to parse it.  This is an error.

   In the second case we emit a warning, then it's up to the ft
   function to decide whether or not it makes sense to keep going
   without a skeleton.
*/
static AST *update_ft_cache(int i)
{
    AST *skeleton;

    if(ft_cache_table[i].p_skeleton)
    {
	/* This is the simple case: The skeleton exists and has
	   already been parsed and cached successfully.  Reuse it.
	*/
	skeleton = ft_cache_table[i].p_skeleton;

#ifdef DEBUG
	fprintf(stderr, "Reusing cached skeleton %s\n",
		ft_table[i].skeleton);
#endif
    }

    else
    {
	/* The skeleton has not been parsed yet. */
	if(ft_table[i].skeleton)
	{
	    /* The is a skeleton name in ft_table.  Parse it, cache
	       and use the resulting AST.
	    */
	    ft_cache_table[i].p_skeleton =
		skeleton =
		parse_skeleton(ft_table[i].skeleton);

#ifdef DEBUG
	    fprintf(stderr, "Parsing skeleton %s for the first time -> %p\n",
		    ft_table[i].skeleton, skeleton);
#endif
	}

	else
	{
	    /* There is no skeleton name in ft_table.  Pass a NULL
	       pointer to the ft function.
	    */
	    skeleton = NULL;
	}
    }

    ft_cache_table[i].n_calls++;
    return skeleton;
}

/* Function to look up 'ft_name_text' in ft_table and call the
   appropriate ft function, giving it 'user_model', 'arguments', and
   'output'.  This function must also retrieve the skeleton, either
   from the cache or by parsing it.  In addition, before calling a
   certain ft function for the first time, it invokes its
   pre-processing function.

   With pre-processing and call sequence numbers in place, we have
   several different possible places to put service operations and the
   system should be quite flexible.  We can do things:

   1) Before calling the very first ft function, regardless of what it
      is: in all pre-processing functions, check if the call sequence
      number is 1.

   2) Before calling a specific ft function for the first time: in the
      pre-processing function associated to that ft function.

   3) After a specific ft function has been called for the last time:
      in the post-processing function associated to that ft function.

   4 and 5) Before and after executing each ft function: add code at
     the very beginning / end of that ft function.
*/
static int ft_table_lookup(
    char *ft_name_text, int *pseq,
    AST *user_model, AST *arguments, AST *output)
{
    int i;

    for(i=0; i<N_FT_DESC && strcmp(ft_name_text, ft_table[i].name); i++);

    if(i<N_FT_DESC)
    {
	AST *skeleton = update_ft_cache(i);

	/* Call pre-processing function if this is the
	   first invocation of this ft function, based on the value of
	   .n_calls in the cache.  We check for 1 because
	   update_ft_cache() incremented it already.
	*/
	if(ft_cache_table[i].n_calls == 1)
	{
#ifdef DEBUG
	    fprintf(stderr,
		    "Calling pre-processor because %s is about"
		    " to be used for the first time.\n",
		    ft_table[i].name);
#endif

	    if(ft_table[i].pre)
		ft_table[i].pre((*pseq)++, user_model, skeleton, output);
	}

	ft_table[i].func((*pseq)++, user_model, arguments, skeleton, output);
    }

    else
	fprintf(stderr, "Warning: @dependability:%s unrecognized\n",
		ft_name_text);

    /* Returns a success indication anyway because even if we had
       trouble with this annotation.  We want MT_Apply() to keep going
       with the others.
    */
    return 0;
}

/* Function to parse one annotation and call the ft
   function specified by it.
*/
static int parse_annotation(AST *root, AST *node, int depth, void *hl_cookie)
{
    struct parse_annotations_cookie *c =
	(struct parse_annotations_cookie *)hl_cookie;

    AST *ft_name_node;
    char *ft_name_text;
    AST *arguments;

    /* Make sure we are really looking at an annotation.  Moreover,
       annotations shall only be at the top level, but double-check to
       be sure and ignore them if they are misplaced.
    */
    assert(node->code == AST_CODE_ANNOTATION);
    if(depth > 1)  return 0;

    /* Locate the second symbol in the .hierarchical_symbol.  This is
       the name of the ft function.  The first is always
       "dependability" and we are sure it exists, otherwise we would
       not have been called, so we can say ->next->next without being
       afraid of running into a NULL pointer.
    */
    ft_name_node =
	node->ast_node_specific.annotation.hierarchical_symbol->next->next;

    if(ft_name_node)
    {
	assert(ft_name_node->code == AST_CODE_SYMBOL);
	ft_name_text = ft_name_node->ast_node_specific.symbol.text;

	/* The list of additional arguments to the ft function starts
	   at the third element of .hierarchical_symbol and may be
	   NULL.
	*/
	arguments = ft_name_node->next;
    }
    else
    {
	/* If we have only @dependability {}, the name of the ft
	   function and its argument list are both NULL.  It's
	   unlikely we find a NULL name in the ft_table, but let's try
	   anyway to be general.
	*/
	ft_name_text = NULL;
	arguments = NULL;
    }

#ifdef DEBUG
    fprintf(stderr, "Parsing annotation @dependability:%s\n", ft_name_text);
#endif

    return ft_table_lookup(ft_name_text, &(c->seq), root, arguments, c->output);
}

/* Scan the ft_cache_table, determine which ft functions have been
   invoked at least once (based on .n_calls) and call the
   corresponding post_processing function (.pp in ft_table).
*/
void post_processing(int *pseq, AST *tree, AST *output)
{
    int i;

    for(i=0; i<N_FT_DESC; i++)
	if(ft_cache_table[i].n_calls > 0)
	{
#ifdef DEBUG
	    fprintf(stderr,
		    "Calling post-processor "
		    "because %s has been used %d time(s).\n",
		    ft_table[i].name, ft_cache_table[i].n_calls);
#endif

	    if(ft_table[i].post)
		ft_table[i].post(
		    *(pseq++), tree, ft_cache_table[i].p_skeleton, output);
	}
}

AST *parse_annotations(AST *tree)
{
    /* Create the empty list used to accumulate the output,
       save it in the hl_cookie.  Set initial call sequence number to
       zero, too.
    */
    AST *output = AST_makeList0(NULL, 0);
    struct parse_annotations_cookie hl_cookie =
	{ .seq =0, .output = output };

    init_ft_cache();

    /* Parse all annotations one by one, calling parse_annotation() on
       each of them, with the help of MT_Apply().  Each invocation of
       parse_annotation() accumulates output into 'output'.
    */
    (void)MT_Apply(tree, AST_CODE_ANNOTATION, "dependability",
		   parse_annotation, &hl_cookie);

    /* Call post-processing functions corresponding to ft functions
       that have been invoked at least once.
    */
    post_processing(&(hl_cookie.seq), tree, output);

    clear_ft_cache();

    /* Return the accumulated output. */
    return output;
}
