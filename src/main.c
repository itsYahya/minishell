#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "sig.h"
#include "utils.h"
#include "constant.h"
#include <errno.h>
#include <unistd.h>

t_data	g_data;

void	clear(t_context *ctx, int exit_code)
{
	free(ctx->home);
	free(ctx->cwd);
	rl_clear_history();
	move_cursor(g_data.x_cur_pos);
	printf("exit\n");
	free_mut(ctx->env);
	exit(exit_code);
}

void	show_prompt(t_context *ctx)
{
	char	*line;
	int		code;

	while (1)
	{
		g_data.g_shell_state = SH_READING;
		line = readline(PROMPT);
		g_data.g_shell_state = SH_EXECUTING;
		if (line == NULL)
			clear(ctx, EXIT_SUCCESS);
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		code = exec_shell(line, ctx);
		free(line);
		if (code >= 0)
			clear(ctx, code);
		rl_on_new_line();
	}
}

int	ft_get_c(FILE *in)
{
	int	y;
	int	c;

	c = rl_getc(in);
	if (c == 4)
		get_cursor_position(&g_data.x_cur_pos, &y);
	return (c);
}

int	setup(t_context *ctx, char **env)
{
	char	*tmp;

	if (!isatty(STDOUT_FILENO))
		duptty();
	init_mut(ctx->env, 100);
	ctx->last_status_code = 0;
	if (!clone_env(ctx->env, env))
		return (12);
	ctx->cwd = getcwd(NULL, 0);
	tmp = search_env(ctx->env, "HOME", ft_strlen("HOME"));
	ctx->home = ft_strndup(tmp, -1);
	rl_getc_function = &ft_get_c;
	ft_init_sigaction(ctx);
	g_data.exit_code = &ctx->last_status_code;
	return (-1);
}

int	main(int ac, char *av[], char *env[])
{
	t_context	ctx;
	t_mut		genv;
	int			exit_code;

	if (ac > 0)
		g_data.basename = ft_basename(av[0], '/') + 1;
	ctx.env = &genv;
	exit_code = setup(&ctx, env);
	if (exit_code == -1)
		show_prompt(&ctx);
	free(ctx.env->content);
	return (exit_code);
}
