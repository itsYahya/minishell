#include "builtins.h"
#include <stdlib.h>

void	uns_delete(int pos, t_mut *genv)
{
	char	*env;

	env = genv->content[pos];
	while (genv->content[pos])
	{
		genv->content[pos] = genv->content[pos + 1];
		pos++;
	}
	genv->len -= 1;
	free(env);
}

void	ft_unset(char **words, t_mut *genv)
{
	int	pos;

	while (*words)
	{
		pos = search_mut(genv, *words);
		if (pos > 0)
			uns_delete(pos, genv);
		words++;
	}
}
