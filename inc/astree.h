#ifndef ASTREE_H
# define ASTREE_H

# include "list.h"
# include "utils.h"

enum e_node_type
{
	NODE_AND,
	NODE_OR,
	NODE_COMPLEX_CMD,
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECTION_STATMENT,
	NODE_SUB_CMD,
};

typedef enum e_type
{
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_HEREDOC,
	REDIRECT_APPEND
}	t_type;

typedef struct s_redirect
{
	t_type	type;
	char	*file;
	int		fd;
	int		is_expandable;
}	t_redirect;

typedef struct s_pipe
{
	int	readend;
	int	writend;
}	t_pipe;

typedef struct s_simple_cmd
{
	t_mut	words;
	char	*cmd;
	int		fdin;
	int		fdout;
	t_pipe	in;
	t_pipe	out;
}	t_simple_cmd;

typedef struct s_re_stat
{
	struct s_node	*body;
	t_list			*redirections;
	t_pipe			pipe_in;
	t_pipe			pipe_out;
}	t_re_stat;

typedef struct s_leaf
{
	struct s_node	*left;
	struct s_node	*right;
	t_pipe			pipe_in;
	t_pipe			pipe_out;
}	t_leaf;

typedef struct s_complex_cmd
{
	t_list	*tokens;
}	t_complex_cmd;

typedef struct s_logic
{
	struct s_node	*right;
	struct s_node	*left;
}	t_logic;

typedef union u_content
{
	t_simple_cmd	ast_command;
	t_re_stat		redirected_statement;
	t_leaf			leaf;
	t_logic			list;
	t_complex_cmd	complex_cmd;
}	t_content;

typedef struct s_node
{
	enum e_node_type	type;
	t_content			content;
}	t_node;

void	free_tree(t_node *node);
void	clear_tree(t_node *node, void (*del)(t_node *));

#endif
