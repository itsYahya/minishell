#include <stdlib.h>
#include "constant.h"
#include "minishell.h"
#include "token.h"

t_list	*str_to_tokens(char *str)
{
	t_list	*head;
	t_list	*cur;
	int		len;

	head = NULL;
	while (*str)
	{
		cur = new_token(TK_WHITESPACE, NULL);
		if (cur == NULL)
			break ;
		if (is_space(*str))
			while (is_space(*str))
				str++;
		else
		{
			len = til_set(str, SET_WHITESPACE, ft_strlen(str));
			((t_token *)cur->content)->value = ft_strndup(str, len);
			tk(cur)->type = TK_EXPRESSION;
			str += len;
		}
		ft_lstadd_back(&head, cur);
	}
	if (*str != '\0')
		ft_lstclear(&head, free_token);
	return (head);
}

char	*get_var_value(t_context *ctx, char *var, int len)
{
	char	*str;

	if (*var == '?')
	{
		str = ft_itoa(ctx->last_status_code);
		if (str != NULL)
			return (str);
	}
	str = search_env(ctx->env, var, len);
	return (ft_strndup(str, -1));
}

int	exp_len(t_context *ctx, char *str, int size)
{
	int		i;
	int		len;
	int		tmp_len;
	char	*tmp;

	i = 0;
	len = 0;
	tmp_len = 0;
	while (i < size)
	{
		tmp_len = til_set(str + i, "$", size - i);
		i += tmp_len;
		len += tmp_len;
		if (str[i] != '$')
			continue ;
		tmp_len = scan_var(str + i);
		tmp = get_var_value(ctx, str + i + 1, tmp_len - 1);
		if (tmp != NULL)
			len += ft_strlen(tmp);
		free(tmp);
		i += tmp_len;
	}
	return (len);
}
