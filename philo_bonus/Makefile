# Configuration of paths
SRCDIR := src
OBJDIR := obj
INCDIR := include
LIBFTDIR := libft

# Name of the final executable
NAME = philo_bonus

# Decide whether the commands will be shwon or not
VERBOSE = TRUE

# Create the list of directories
DIRS = $(shell find $(SRCDIR) -type d | sed 's/$(SRCDIR)\///g' | sed -n '1!p')
SRCDIRS	= $(foreach dir, $(DIRS), $(addprefix $(SRCDIR)/, $(dir)))
OBJDIRS = $(foreach dir, $(DIRS), $(addprefix $(OBJDIR)/, $(dir)))

# Create a list of *.c sources in DIRS
SRCS = $(wildcard src/*.c)
SRCS += $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

# Unit Test
SRCS_TEST =  $(wildcard test/*.c)
SRCS_TEST += $(SRCS)
SRCS_TEST := $(filter-out src/main.c, $(SRCS_TEST))

# Define objects for all sources
OBJS_TEST = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS_TEST))

# Define objects for all sources
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Name the compiler & flags
CC = clang
# CC = clang

CFLAGS = -iquote$(INCDIR)
CFLAGS += -Wall -Wextra -Werror

LIBS = -L./libft -lft

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(HIDE)$(CC) $(CFLAGS) -c  $< -o $@

all			: buildrepo $(NAME)

$(NAME)		: $(OBJS)
	$(HIDE)$(MAKE) -C $(LIBFTDIR)
	$(HIDE)$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@printf $(GREEN)"[$@] program created\n"$(RESET)

clean		:
	$(HIDE)rm -rf $(OBJDIR)
	$(HIDE)$(MAKE) clean -C $(LIBFTDIR)
	@printf $(YELLOW)"[$(NAME)] objects removed\n"$(RESET)

fclean		: clean
	$(HIDE)rm -f $(NAME)
	$(HIDE)$(MAKE) fclean -C $(LIBFTDIR)

re			: fclean all

LEAK = valgrind 

test	: all
	./$(NAME) 5 800 200 200

val		: all
	$(LEAK) ./$(NAME) 5 800 200 200

docker:
	docker build . -t 42/valgrind
	docker run --rm -it --name valgrind -v /Users/tonted/42/philosophers:/valgrind 42/valgrind

utest	: buildrepo $(OBJS_TEST)
	@echo "Hello utest"
	$(HIDE)$(MAKE) -C $(LIBFTDIR)
	$(HIDE)$(CC) $(CFLAGS) $(OBJS_TEST) $(LIBS) -o utest
	@printf $(MAGENTA)"[$@] unit test created\n"$(RESET)
	./utest

buildrepo	:
	$(HIDE)$(call make-repo)

print	:
	@echo $(DIRS)
	@echo $(SRCS)

.PHONY		: clean fclean all re $(OBJDIR) buildrepo print
	
# Create
define make-repo
	$(HIDE)mkdir -p $(OBJDIR)
	$(HIDE)for dir in $(DIRS); \
   	do \
	mkdir -p $(OBJDIR)/$$dir; \
   	done
endef

# Color
BLACK := "\e[0;30m"
RED := "\e[0;31m"
GREEN := "\e[0;32m"
YELLOW := "\e[0;33m"
BLUE := "\e[0;34m"
MAGENTA := "\e[0;35m"
CYAN := "\e[0;36m"
RESET :="\e[0m"

# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),TRUE)
    HIDE =
else
    HIDE = @
endif