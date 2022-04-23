#ifndef MINISHELL_H
# define MINISHELL_H

# include "list.h"
# include "utils.h"
# include <signal.h>

# define SH_READING 1
# define SH_EXECUTING 2 
# define SH_WAITING 4

typedef struct s_data
{
	int				*exit_code;
	char			*basename;
	sig_atomic_t	g_shell_state;
	int				x_cur_pos;
}	t_data;

extern t_data	g_data;

typedef struct s_context
{
	t_mut	*env;
	char	*siglist[NSIG];
	int		last_status_code;
	char	*cwd;
	char	*home;
}	t_context;

int		exec_shell(char *line, t_context *ctx);
char	*search_env(t_mut *arr, char *find, int len);
void	signals_handler(int sig, siginfo_t *siginfo, void *ptr);
int		duptty(void);
void	move_cursor(int init_x);
int		get_cursor_position(int *x, int *y);
void	ft_merror(char *pre, char *msg);
char	*ft_basename(char *s, char c);
void	free_mut(t_mut *mut);
void	clear(t_context *ctx, int exit_code);

#endif
