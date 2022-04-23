#include "export.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_degit(char ch)
{
	return ((ch >= 'A' && ch <= 'Z')
		|| (ch >= 'a' && ch <= 'z'));
}

int	ft_valide_name(char *name, int *plus, int *equal)
{
	int	i;

	i = 0;
	*plus = 0;
	if (name[0] == '=')
		return (0);
	while ((ft_degit(name[i]) || name[i] == '_' || (name[i] == '+')) && name[i])
	{
		if (name[i] == '+')
		{
			*plus = 1;
			i++;
			break ;
		}
		i++;
	}
	*equal = name[i] == '=';
	return (*equal || (!name[i] && !(*plus)));
}

int	ft_parsword(char *word, char **name, char **value)
{
	int	i;

	i = 0;
	while (word[i] != '=' && word[i] != '+' && word[i])
		i++;
	*name = ft_strndup(word, i);
	i += 1 + (word[i] == '+');
	*value = ft_strndup(word + i, ft_strlen(word + i));
	if (*value == 0 || *name == 0)
	{
		free(value);
		free(name);
		return (1);
	}
	return (0);
}

void	ex_free(char *value, char *env)
{
	free(value);
	if (env)
		free(env);
}

void	ex_printenv(t_mut *genv)
{
	int		i;
	int		j;
	char	*env;

	i = 0;
	while (genv->content[i])
	{
		j = 0;
		env = genv->content[i];
		while (env[j] != '=' && env[j])
			j++;
		ft_putstr(1, "declare -x ");
		write(1, env, j + (env[j] == '='));
		if (env[j++] == '=')
		{
			ft_putstr(1, "\"");
			ft_putstr(1, env + j);
			ft_putstr(1, "\"");
		}
		ft_putstr(1, "\n");
		i++;
	}
}
