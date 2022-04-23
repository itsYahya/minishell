#include "astree.h"
#include "builtins.h"
#include "minishell.h"
#include "utils.h"
#include "exec.h"
#include <unistd.h>

int	fun_to_call(char *word)
{
	if (ft_strncmp(word, "echo", ft_strlen("echo")) == 0)
		return (1);
	else if (ft_strncmp(word, "pwd", ft_strlen("pwd")) == 0)
		return (2);
	else if (ft_strncmp(word, "env", ft_strlen("env")) == 0)
		return (3);
	else if (ft_strncmp(word, "export", ft_strlen("export")) == 0)
		return (4);
	else if (ft_strncmp(word, "unset", ft_strlen("unset")) == 0)
		return (5);
	else if (ft_strncmp(word, "cd", ft_strlen("cd")) == 0)
		return (6);
	else if (ft_strncmp(word, "exit", ft_strlen("exit")) == 0)
		return (7);
	else
		return (0);
}

int	save_io(int fds[])
{
	fds[0] = dup(STDIN_FILENO);
	fds[1] = dup(STDOUT_FILENO);
	return (1);
}

int	restore_io(int fds[])
{
	dup2(fds[0], STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	return (1);
}

void	_exec_bi(t_context *ctx, int num, char **words)
{
	if (num == 1)
		ft_echo(words, ctx);
	else if (num == 2)
		ft_pwd(ctx);
	else if (num == 3)
		ft_env(ctx->env, ctx);
	else if (num == 4)
		ft_export(ctx->env, words, ctx);
	else if (num == 5)
		ft_unset(words, ctx->env);
	else if (num == 6)
		ft_cd(ctx->env, ctx, words);
	else if (num == 7)
		ft_exit(words);
}

int	exec_builtsin(t_context *ctx, t_simple_cmd *cmd, char *word)
{
	char	**words;
	int		num;
	int		fds[2];

	num = fun_to_call(word);
	if (num == 0)
		return (0);
	save_io(fds);
	dup_cmd(cmd);
	words = (char **)cmd->words.content + 1;
	ctx->last_status_code = 0;
	_exec_bi(ctx, num, words);
	restore_io(fds);
	return (1);
}
