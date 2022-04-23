#ifndef SYNTAX_CHECKER_H
# define SYNTAX_CHECKER_H

# include "constant.h"

int		ft_syntax_checker(t_list *tokens);
void	ft_errorhandler(t_list *head, int err, int pr);
int		ft_isrediriction(t_list *head);
t_list	*ft_checkpao(t_list *head, int *err);
t_list	*ft_return(t_list *head, int *err, int error);
t_list	*ft_checkcmd(t_list *head, int *err, int cmd);
t_list	*init_tokens(t_list *head, t_list **tokens, char **line);
t_list	*_checksub_cmd(t_list *head, int *err);

#endif
