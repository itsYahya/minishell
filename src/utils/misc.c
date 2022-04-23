#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "minishell.h"
#include "utils.h"

void	ft_merror(char *pre, char *msg)
{
	ft_putstr(2, g_data.basename);
	ft_putstr(2, ": ");
	ft_putstr(2, pre);
	ft_putstr(2, msg);
}

void	ft_free_env(t_mut *genv, int i)
{
	while (i-- > 0)
		free(genv->content[i]);
}

int	clone_env(t_mut *c_env, char *env[])
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		tmp = ft_strndup(env[i], ft_strlen(env[i]));
		if (tmp == 0 || !mut_add(c_env, tmp))
		{
			ft_free_env(c_env, i);
			ft_merror("", " failed to allocate with malloc");
			return (0);
		}
		i++;
	}
	return (1);
}

char	*search_env(t_mut *genv, char *find, int len)
{
	char	**env;
	int		i;

	env = (char **)genv->content;
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], find, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}
