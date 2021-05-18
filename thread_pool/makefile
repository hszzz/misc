.PHONY : all clean rebuild

CC := gcc
RM := rm -fr
MKDIR := mkdir

CFLAGS := -lpthread

DIR_DEPS := deps
DIR_OBJS := objs
DIR_EXES := .

DIRS := $(DIR_DEPS) $(DIR_OBJS) # $(DIR_EXES)

EXE := target
EXE := $(addprefix $(DIR_EXES)/,$(EXE))

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
OBJS := $(addprefix $(DIR_OBJS)/,$(OBJS))
DEPS := $(SRCS:.c=.dep)
DEPS := $(addprefix $(DIR_DEPS)/,$(DEPS))

all : $(DIR_OBJS) $(DIR_EXES) $(EXE)

ifeq ("$(MAKECMDGOALS)", "all")
-include $(DEPS)
endif

ifeq ("$(MAKECMDGOALS)", "")
-include $(DEPS)
endif

$(EXE) : $(OBJS)
	$(CC) -o $@ $^ ${CFLAGS}

$(DIR_OBJS)/%.o : %.c
	$(CC) -o $@ -c $(filter %.c,$^)

ifeq ("$(wildcard $(DIR_DEPS))", "")
$(DIR_DEPS)/%.dep : $(DIR_DEPS) %.c
else
$(DIR_DEPS)/%.dep : %.c
endif
	@set -e;\
	$(CC) -MM -E $(filter %.c,$^) | sed 's,\(.*\)\.o[ :]*,objs/\1.o $@ : ,g' > $@

$(DIRS) :
	$(MKDIR) $@

clean :
	$(RM) $(DIRS)

rebuild :
	$(MAKE) clean
	$(MAKE) all
