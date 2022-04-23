#ifndef PARSE_H
# define PARSE_H

# include "astree.h"
# include "list.h"
# include "minishell.h"

t_node	*parse(t_list *list, t_context *ctx);
void	print_tree(t_node *tree);
t_list	*join(t_context *ctx, t_list *tks);
t_list	*join_next(t_list *tks);
void	del_spaces(t_list **head);
int		is_redirection(enum e_token_type type);
char	*expand_str(t_context *ctx, char *str, int len);
t_list	*match(t_list *tks);
int		read_heredoc(t_context *ctx, t_list *tks);
int		join_heredoc(t_list *tks);
t_node	*parse_pipe(t_context *ctx, t_node *root, t_list *tokens);
int		has_tk(t_list *tks, enum e_token_type type);
int		expand_var(t_context *ctx, t_list **head, t_list *cur);
int		expand_literal(t_token *tk);
int		expand_template(t_context *ctx, t_token *tk);
int		expand_exp(t_token *tk);
int		is_word(t_list *item);
char	*join_tokens(t_list *tokens, int arg_len);
t_list	*count_size(t_list *tokens, int *arg_len);
t_list	*str_to_tokens(char *str);
char	*get_var_value(t_context *ctx, char *var, int len);
int		exp_len(t_context *ctx, char *str, int size);
int		expand_oth(t_context *ctx, t_list **head, t_list *cur);
t_node	*new_node(enum e_node_type type);
t_list	*free_red(t_list *tks);
t_node	*new_red_node(t_node *body);
t_list	*new_red(char *file);
int		expand(t_context *ctx, t_list **head);
char	*ft_dup_norm(t_list *tks);

#endif
