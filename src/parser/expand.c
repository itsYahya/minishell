#include "list.h"
#include "minishell.h"
#include "token.h"
#include "utils.h"
#include "constant.h"
#include "parse.h"
#include <stdlib.h>

int	expand_literal(t_token *tk)
{
	tk->value = ft_strndup(tk->value + 1, tk->len - 2);
	tk->len = -1;
	tk->type = TK_EXPRESSION;
	return (tk->value != NULL);
}

int	expand_exp(t_token *tk)
{
	if (tk->len == -1)
		return (1);
	tk->value = ft_strndup(tk->value, tk->len);
	tk->len = -1;
	return (tk->value != NULL);
}

char	*expand_str(t_context *ctx, char *str, int size)
{
	int		len;
	int		i;
	char	*res;
	char	*tmp;

	res = malloc(sizeof(char) * (exp_len(ctx, str, size) + 1));
	if (res == NULL)
		return (NULL);
	*res = '\0';
	i = 0;
	while (i < size)
	{
		len = til_set(str + i, "$", size - i);
		ft_append(res, str + i, len);
		i += len;
		if (str[i] != '$')
			continue ;
		len = scan_var(str + i);
		tmp = get_var_value(ctx, str + i + 1, len - 1);
		if (tmp != NULL)
			ft_append(res, tmp, ft_strlen(tmp));
		free(tmp);
		i += len;
	}
	return (res);
}

int	expand_template(t_context *ctx, t_token *tk)
{
	char	*str;

	str = expand_str(ctx, tk->value + 1, tk->len - 2);
	tk->value = str;
	tk->type = TK_EXPRESSION;
	tk->len = -1;
	return (str != NULL);
}

int	expand_var(t_context *ctx, t_list **head, t_list *cur)
{
	char	*str;
	t_list	*tmp;

	str = get_var_value(ctx, tk(cur)->value + 1, tk(cur)->len - 1);
	ft_lstdelone(cur, free_token);
	if (str == NULL)
		return (1);
	tmp = str_to_tokens(str);
	free(str);
	if (tmp == NULL)
	{
		ft_lstclear(head, free_token);
		return (0);
	}
	ft_lstadd_back(head, tmp);
	return (1);
}
