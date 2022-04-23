#include "builtins.h"
#include <stdio.h>

int	ft_toprint(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_env(t_mut *env, t_context *ctx)
{
	int	i;

	i = 0;
	while (env->content[i])
	{
		if (ft_toprint(env->content[i]))
		{
			ft_putstr(1, env->content[i]);
			ft_putstr(1, "\n");
		}
		i++;
	}
	ctx->last_status_code = 0;
}
