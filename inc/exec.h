#ifndef EXEC_H
# define EXEC_H

# include "astree.h"
# include "minishell.h"

void	execute(t_context *ctx, t_node *tree);
void	execute_cmd(t_context *ctx, t_node *cmd);
void	execute_pipe(t_context *ctx, t_node *tree);
void	execute_redirection(t_context *ctx, t_node *red);
char	*get_cmd_path(t_context *ctx, char *cmd);
int		ft_wait_last(t_context *ctx, int pid);
void	dup_cmd(t_simple_cmd *cmd);
int		read_files(t_node *red);
int		ft_pipe(t_pipe *p);
t_pipe	empty_pipe(void);
t_node	*parse_list(t_list *tks);
int		execute_list(t_context *ctx, t_node *tree, int is_exec);
void	free_redirect(void *ptr);
int		exec_builtsin(t_context *ctx, t_simple_cmd *cmd, char *word);
int		close_cmd_fds(t_simple_cmd *cmd);
int		is_dir(char *filename, char *orginal);

#endif
