#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"
# include "minishell.h"

void	ft_echo(char **words, t_context *ctx);
void	ft_pwd(t_context *ctx);
void	ft_env(t_mut *env, t_context *ctx);
void	ft_export(t_mut *genv, char **words, t_context *ctx);
void	ft_unset(char **words, t_mut *genv);
void	ft_cd(t_mut *genv, t_context *ctx, char **words);
void	ft_exit(char **words);
void	ft_error(char *path, char *error);
void	update_pwd(t_mut *genv, t_context *ctx);
int		ft_updatepwd_ex(char *value, t_mut *genv);
char	*ft_newcwd(t_context *ctx, t_mut *genv, int *exp);

#endif
