#include "builtins.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_newcwd(t_context *ctx, t_mut *genv, int *exp)
{
	char	*value;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	value = 0;
	*exp = (search_mut(genv, "PWD") != -1);
	value = ft_strndup("PWD=", 4);
	if (value == NULL)
		return (free(cwd), NULL);
	if (cwd != NULL)
	{
		value = ft_strjoin(value, cwd, ft_strlen(cwd));
		if (value == NULL)
			return (free(cwd), NULL);
	}
	else
	{
		value = ft_strjoin(value, ctx->cwd, ft_strlen(ctx->cwd));
		if (value == NULL)
			return (NULL);
		value = ft_strjoin(value, "/..", ft_strlen("/.."));
		if (value == NULL)
			return (NULL);
	}
	return (free(cwd), value);
}

int	ft_updatepwd_ex(char *value, t_mut *genv)
{
	char	**args;

	args = (char **)malloc(sizeof(char *) * 2);
	if (args)
	{
		args[0] = value;
		args[1] = 0;
		ft_export(genv, args, 0);
		return (0);
	}
	free(args);
	return (2);
}

int	ft_cd_(char *path)
{
	void	*ptr;

	if (chdir(path) == -1)
	{
		ft_error(path, ": no such file or directory");
		return (0);
	}
	else
	{
		ptr = getcwd(NULL, 0);
		if (ptr == NULL)
		{
			ft_putstr(2, "cd: error retrieving current directory: ");
			ft_putstr(2, "getcwd: cannot access parent directories: ");
			ft_putstr(2, "No such file or directory");
		}
		free(ptr);
	}
	return (1);
}

void	ft_go_home(t_context *ctx)
{
	if (!ctx->cwd)
	{
		ft_merror("", ": home directory is undefined\n");
		return ;
	}
	chdir(ctx->home);
}

void	ft_cd(t_mut *genv, t_context *ctx, char **words)
{
	char	*path;

	if (*words)
	{
		path = *words;
		words++;
		if (*words)
		{
			ft_error(*words, "cd: string not in pwd: ");
			ctx->last_status_code = 2;
			return ;
		}
		else if (ft_strncmp(path, "~", 1) == 0)
			ft_go_home(ctx);
		else if (ft_cd_(path) == 0)
			return ;
	}
	else
		ft_go_home(ctx);
	update_pwd(genv, ctx);
}
