#include "builtins.h"
#include <stdio.h>

int	ft_newline(char *word, int len)
{
	int	i;

	i = 0;
	if (word[i++] != '-' || len == 1)
		return (0);
	while (word[i])
	{
		if (word[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **words, t_context *ctx)
{
	int	nl;

	nl = 1;
	while (*words && ft_newline(*words, ft_strlen(*words)))
	{
		nl = 0;
		words++;
	}
	while (*words)
	{
		ft_putstr(1, *words);
		words++;
		if (*words)
			ft_putstr(1, " ");
	}
	if (nl)
		ft_putstr(1, "\n");
	ctx->last_status_code = 0;
}
