# Simple Makefile to build the NHC tool.
#
# Set up the parser source tree and build tree

PARSER_INC = include
PARSER_ROOT = parser
PARSER_LIB = $(PARSER_ROOT)/libparser.a
PARSER_SRC = $(sort $(PARSER_ROOT)/cpal_lex.c				\
	$(PARSER_ROOT)/cpal_grammar.c $(wildcard $(PARSER_ROOT)/*.c))
PARSER_OBJ = $(PARSER_SRC:.c=.o)
PARSER_DEP = $(PARSER_SRC:.c=.d)

# Set up the fault tolerance source tree and build tree

FT_ROOT = fault_tolerance
FT_LIB = $(FT_ROOT)/libft.a
FT_SRC = $(wildcard $(FT_ROOT)/*.c)
FT_OBJ = $(FT_SRC:.c=.o)
FT_DEP = $(FT_SRC:.c=.d)

# Set up the model transformation source tree and build tree

MT_ROOT = model_transform
MT_LIB = $(MT_ROOT)/libmt.a
MT_SRC = $(wildcard $(MT_ROOT)/*.c)
MT_OBJ = $(MT_SRC:.c=.o)
MT_DEP = $(MT_SRC:.c=.d)

# Set up the dumper source tree and build tree

DUMP_ROOT = dumper
DUMP_LIB = $(DUMP_ROOT)/libdumper.a
DUMP_SRC = $(wildcard $(DUMP_ROOT)/*.c)
DUMP_OBJ = $(DUMP_SRC:.c=.o)
DUMP_DEP = $(DUMP_SRC:.c=.d)

# Set up the utility source tree and build tree

UTILITY_ROOT = utility
UTILITY_LIB = $(UTILITY_ROOT)/libutility.a
UTILITY_SRC = $(wildcard $(UTILITY_ROOT)/*.c)
UTILITY_OBJ = $(UTILITY_SRC:.c=.o)
UTILITY_DEP = $(UTILITY_SRC:.c=.d)


# Definitions to build main programs in the main subdirectory.

MAIN_ROOT = main
MAIN_C_SRC = $(wildcard $(MAIN_ROOT)/*.c)
MAIN_SRC = $(MAIN_C_SRC)
MAIN_OBJ = $(sort $(addsuffix .o, $(basename $(MAIN_SRC))))
MAIN_BIN = $(MAIN_OBJ:.o=)
MAIN_DEP = $(MAIN_C_SRC:.c=.d)

# Definitions for the MT samples
MT_S_ROOT = mt_samples
MT_S_SRC =  $(wildcard $(MT_S_ROOT)/*.cpal)
MT_S_OBJ = $(wildcard $(MT_S_ROOT)/beauty*) $(wildcard	\
$(MT_S_ROOT)/mt*)

# General flags for the C compiler and the linker.  The libraries -ly
# and -ll are the yacc and lex libraries and contain utility functions
# for the generated scanner and parser, respectively. 

CC = gcc
IFLAGS = -I$(FT_ROOT) -I$(MT_ROOT) -I$(DUMP_ROOT) -I$(PARSER_INC) -I$(PARSER_ROOT)
CFLAGS = -std=c99 -Wall -D_POSIX_C_SOURCE=200809L $(IFLAGS) -g
LDLIBS = $(FT_LIB) $(MT_LIB) $(DUMP_LIB) $(PARSER_LIB) $(UTILITY_LIB) -ly -ll

all: $(FT_LIB) $(MT_LIB) $(DUMP_LIB) $(UTILITY_LIB) $(PARSER_LIB) $(MAIN_BIN) 

clean:
	$(RM) $(FT_DEP) $(FT_OBJ) $(FT_LIB)
	$(RM) $(MT_DEP) $(MT_OBJ) $(MT_LIB)
	$(RM) $(DUMP_DEP) $(DUMP_OBJ) $(DUMP_LIB)
	$(RM) $(UTILITY_DEP) $(UTILITY_OBJ) $(UTILITY_LIB)
	$(RM) $(PARSER_DEP) $(PARSER_OBJ) $(PARSER_LIB)
	$(RM) $(MAIN_DEP) $(MAIN_OBJ) $(MAIN_BIN)
	$(RM) $(MT_S_OBJ)

# ---
# Build rules for the various libraries
# ---

# Rules to build the fault tolerance library by first building
# the object files and then archiving them

$(FT_LIB): $(FT_OBJ)
	$(AR) -r -s $@ $?

# Rules to build the model transformation library by first building
# the object files and then archiving them

$(MT_LIB): $(MT_OBJ)
	$(AR) -r -s $@ $?

# Rules to build the dump library by first building the object
# files and then archiving them

$(DUMP_LIB): $(DUMP_OBJ)
	$(AR) -r -s $@ $?

# Rules to build the utility library by first building the object
# files and then archiving them

$(UTILITY_LIB): $(UTILITY_OBJ)
	$(AR) -r -s $@ $?

# ---
# Build rules for the parser
# ---

$(PARSER_LIB): $(PARSER_OBJ)
	$(AR) -r -s $@ $?


$(PARSER_ROOT)/%.o: $(PARSER_ROOT)/%.c $(PARSER_ROOT)/%.h $(UTILITY_LIB)
	$(CC) -c $(CFLAGS) -o $@ $<

# Parser dependancy
$(PARSER_ROOT)/%.d: $(PARSER_ROOT)/%.c $(PARSER_ROOT)/%.h
	@echo "Generating $@"
	@set +e; $(CC) -MM $(CFLAGS) $< \
	| sed "s,.*\.o,$(patsubst %.d,%.o,$@) $@," \
	> $@; \
	[ -s $@ ] || rm -f $@

-include $(PARSER_DEP)

# TBD: This will prevent make from removing these intermediate files
.PRECIOUS: $(PARSER_ROOT)/cpal_lex.c $(PARSER_ROOT)/cpal_lex.h		\
	$(PARSER_ROOT)/cpal_grammar.c $(PARSER_ROOT)/cpal_grammar.h	



# ---
# Build rule for main programs.
# ---

$(MAIN_ROOT)/%: $(MAIN_ROOT)/%.c $(FT_LIB) $(MT_LIB) $(DUMP_LIB)	\
	$(UTILITY_LIB) $(PARSER_LIB)
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.d: %.c $(PARSER_ROOT)/cpal_lex.h $(PARSER_ROOT)/cpal_grammar.h
	@echo "Generating $@"
	@set +e; $(CC) -MM $(CFLAGS) $< \
	| sed "s,.*\.o,$(patsubst %.d,%.o,$@) $@," \
	> $@; \
	[ -s $@ ] || rm -f $@

-include $(FT_DEP)
-include $(MT_DEP)
-include $(DUMP_DEP)
-include $(UTILITY_DEP)
-include $(PARSER_DEP)
-include $(MAIN_DEP)


DIST_TMPDIR=.
DIST_ROOT=NHC_Model_Transformation_Release
DIST_LIST=Makefile include parser/*.[ch] dumper fault_tolerance			\
model_transform utility main mt_samples/test.cpal mt_pressure_test.sh	\
README.txt LICENSE

dist:
	rm -rf $(DIST_TMPDIR)/$(DIST_ROOT) $(DIST_ROOT).tar.bz2
	mkdir -p $(DIST_TMPDIR)/$(DIST_ROOT)
	git archive --format=tar -v HEAD \
		| tar -x -C $(DIST_TMPDIR)/$(DIST_ROOT)
	make -C $(DIST_TMPDIR)/$(DIST_ROOT) \
		parser/cpal_lex.c parser/cpal_grammar.h >/dev/null # 2>&1
	tar -C $(DIST_TMPDIR) -c -j -f $(DIST_ROOT).tar.bz2 --exclude '*.d' \
	  $(patsubst %,$(DIST_ROOT)/%,$(DIST_LIST))
	rm -rf $(DIST_TMPDIR)/$(DIST_ROOT)
