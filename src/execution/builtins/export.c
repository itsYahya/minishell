#include "minishell.h"
#include "builtins.h"
#include "export.h"
#include <stdio.h>
#include <stdlib.h>

int	ex_append(char *name, char *value, int pos, t_mut *genv)
{
	char	*curr_env;
	char	*new_env;

	curr_env = search_env(genv, name, ft_strlen(name));
	new_env = ft_strjoin(name, "=", 1);
	if (new_env == 0)
	{
		ex_free(value, name);
		return (1);
	}
	new_env = ft_strjoin(new_env, curr_env, ft_strlen(curr_env));
	if (new_env == 0)
	{
		ex_free(value, name);
		return (1);
	}
	new_env = ft_strjoin(new_env, value, ft_strlen(value));
	if (new_env == 0)
	{
		ex_free(value, name);
		return (1);
	}
	genv->content[pos] = new_env;
	return (0);
}

int	ex_overwrite(char *name, char *value, int pos, t_mut *genv)
{
	char	*new_env;

	new_env = ft_strjoin(name, "=", 1);
	if (new_env == 0)
	{
		ex_free(value, name);
		return (1);
	}
	new_env = ft_strjoin(new_env, value, ft_strlen(value));
	if (new_env == NULL)
	{
		ex_free(value, name);
		return (1);
	}
	genv->content[pos] = new_env;
	return (0);
}

int	ex_add(char *name, char *value, int equal, t_mut *genv)
{
	char	*new_env;

	if (equal)
	{
		new_env = ft_strjoin(name, "=", 1);
		if (new_env == 0)
		{
			ex_free(value, name);
			return (1);
		}
		new_env = ft_strjoin(new_env, value, ft_strlen(value));
		if (new_env == 0)
			ex_free(value, name);
	}
	else
	{
		new_env = ft_strndup(name, ft_strlen(name));
		if (new_env == 0)
			ex_free(name, value);
	}
	if (new_env == NULL)
		return (1);
	mut_add(genv, new_env);
	return (0);
}

int	exporting(char *word, int plus, int equal, t_mut *genv)
{
	char	*name;
	char	*value;
	int		env_pos;
	char	*env;
	int		num;

	if (ft_parsword(word, &name, &value))
		return (1);
	num = 0;
	env_pos = search_mut(genv, name);
	env = 0;
	if (env_pos >= 0 && equal)
	{
		env = genv->content[env_pos];
		if (plus)
			num = ex_append(name, value, env_pos, genv);
		else
			num = ex_overwrite(name, value, env_pos, genv);
	}
	else if (env_pos < 0)
		num = ex_add(name, value, equal, genv);
	ex_free(value, env);
	return (num);
}

void	ft_export(t_mut *genv, char **words, t_context *ctx)
{
	int		plus;
	int		equal;
	int		args;
	int		num;

	args = 1;
	num = 0;
	while (*words)
	{
		num = 1;
		args = 0;
		if (ft_valide_name(*words, &plus, &equal))
			num = exporting(*words, plus, equal, genv);
		else
		{
			ft_merror("export: `", *words);
			ft_putstr(2, "': not a valid identifier\n");
		}
		words++;
	}
	if (args)
		ex_printenv(genv);
	if (ctx)
		ctx->last_status_code = num;
}
