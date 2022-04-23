CC = cc
CFLAGS = $(CPPFLAGS) -Wall -Werror -Wextra -g

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	LDFLAGS += -lreadline -ltermcap
else
	LDFLAGS = -lreadline -ltinfo
endif

INC = -I./inc

HEADERS = inc/astree.h inc/list.h inc/minishell.h inc/parse.h inc/token.h inc/utils.h

BDIR = build
FILES = main exec terminal terminal_utils destructors \
		signals/handler signals/utils \
		tokenizer/utils tokenizer/utils_2 tokenizer/tokenizer tokenizer/scanners \
		parser/parser parser/print_tree parser/expand parser/utils parser/utils_2 parser/join parser/match parser/heredoc \
		execution/exec_tree execution/pipe execution/path execution/wait execution/utils execution/utils_2\
		utils/misc utils/mutable utils/str utils/str_utils utils/str_utils_2 utils/ft_itoa utils/ft_perror utils/constant utils/ft_basename utils/heredoc \
		utils/join utils/expand \
		list/ft_lstnew list/ft_lstadd_back list/ft_lstlast list/ft_lstadd_front list/ft_lstdelone list/ft_lstclear list/ft_lstsize \
		execution/builtins/cd execution/builtins/cd_utils execution/builtins/echo execution/builtins/pwd execution/builtins/env \
		execution/builtins/export execution/builtins/export_utils execution/builtins/unset execution/builtins/exit \
		execution/builtins/cd execution/lists execution/builtins/exec execution/builtins/cd_utils \
		syntax_cheker/syntax_checker syntax_cheker/utils syntax_cheker/utils_2

OBJ = $(addprefix $(BDIR)/, $(FILES:=.o))
EXEC = minishell

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(BDIR)/%.o: src/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf build

fclean: clean
	rm -rf minishell

re: fclean all

include test.mk

.PHONY : all clean fclean
