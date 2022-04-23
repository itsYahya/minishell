#include "builtins.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_error(char *path, char *error)
{
	ft_putstr(2, g_data.basename);
	ft_putstr(2, ": cd: ");
	ft_putstr(2, path);
	ft_putstr(2, error);
	ft_putstr(2, "\n");
}

void	update_pwd(t_mut *genv, t_context *ctx)
{
	char	*value;
	char	*cwd;
	int		ex;
	int		num;

	num = 0;
	value = ft_newcwd(ctx, genv, &ex);
	if (value == 0)
	{
		ctx->last_status_code = 2;
		return ;
	}
	cwd = ctx->cwd;
	ctx->cwd = ft_strndup(value + ft_strlen("PWD="),
			ft_strlen(value) - ft_strlen("PWD="));
	if (ctx->cwd == NULL)
	{
		ctx->last_status_code = 2;
		return ;
	}
	free(cwd);
	if (ex)
		num = ft_updatepwd_ex(value, genv);
	free(value);
	ctx->last_status_code = num;
}
