// #include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "minishell.h"
#include "safe.h"
#include "utils.h"

int	file_exist(char *filename)
{
	struct stat	st;

	if (filename == NULL || access(filename, F_OK) != 0)
		return (0);
	stat(filename, &st);
	if (S_ISDIR(st.st_mode))
		return (0);
	return (1);
}

char	*ft_joindir(char *s1, char *s2, int s1_len)
{
	int		s2_len;
	char	*str;

	if (s1 == NULL)
		return (NULL);
	s2_len = 0;
	if (s2)
		s2_len = ft_strlen(s2);
	str = malloc(s1_len + s2_len + 2);
	if (str == NULL)
		return (NULL);
	ft_strncpy(str, s1, s1_len);
	ft_strncpy(str + s1_len, "/", 1);
	ft_strncpy(str + s1_len + 1, s2, s2_len);
	return (str);
}

/**
 *
 * if PATH is not set then
 * check if it exist in the current directory
 * else
 * check every path in PATH env variable
 *
 * */
char	*check_envpath(char *cmd, t_mut *env)
{
	char	*filename;
	char	*paths;
	int		i;
	int		len;

	i = 0;
	filename = NULL;
	paths = search_env(env, "PATH", 4);
	if (paths == NULL)
		return (ft_strndup(cmd, -1));
	while (*cmd != '\0' && paths[i])
	{
		len = til_set(paths + i, ":", ft_strlen(paths + i));
		if (len != 0)
		{
			filename = ft_joindir(paths + i, cmd, len);
			if (file_exist(filename))
				break ;
			free(filename);
			filename = NULL;
		}
		i += len + 1;
	}
	return (filename);
}

char	*get_cmd_path(t_context *ctx, char *cmd)
{
	char	*filename;

	if (has_chars('/', cmd))
		return (ft_strndup(cmd, -1));
	else
	{
		filename = check_envpath(cmd, ctx->env);
		if (filename == NULL)
		{
			ft_merror(cmd, ": command not found\n");
			ctx->last_status_code = 127;
		}
	}
	return (filename);
}
