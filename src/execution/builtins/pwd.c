#include "builtins.h"
#include <stdio.h>
#include <unistd.h>

void	ft_pwd(t_context *ctx)
{
	ft_putstr(1, ctx->cwd);
	ft_putstr(1, "\n");
}
