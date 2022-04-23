#ifndef SIG_H
# define SIG_H

# include "minishell.h"

typedef struct sigaction	t_sigaction;

void	ft_init_sigaction(t_context *ctx);
void	init_sig_list(t_context *ctx);
void	mask_sig(t_sigaction *sa);
void	catch_sig(t_sigaction *sa);

#endif
