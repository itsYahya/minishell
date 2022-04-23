#include "list.h"
#include "constant.h"
#include "token.h"
#include "utils.h"
#include <stdlib.h>

void	free_token(void *ptr)
{
	t_token	*tk;

	tk = ptr;
	if (tk->len == -1)
		free(tk->value);
	free(tk);
}

t_list	*new_token(enum e_token_type type, char *value)
{
	t_list	*node;
	t_token	*tk_;

	tk_ = malloc(sizeof(t_token));
	node = ft_lstnew(tk_);
	if (node == NULL)
		return (NULL);
	tk(node)->type = type;
	tk(node)->value = value;
	tk(node)->len = -1;
	return (node);
}

int	tk_len(t_token *tk)
{
	int	len;

	if (tk->len == -1)
		len = ft_strlen(tk->value);
	else
		len = tk->len;
	return (len);
}

int	tk_cpy(char *dst, t_token *tk)
{
	int	i;

	if (tk->len != -1)
	{
		ft_strncpy(dst, tk->value, tk->len);
		return (tk->len);
	}
	i = 0;
	while (tk->value[i])
	{
		dst[i] = tk->value[i];
		i++;
	}
	dst[i] = 0;
	return (i);
}

int	tk_cmp(t_token *tk, char *str)
{
	int	len;
	int	i;

	i = 0;
	len = tk->len;
	if (len == -1)
		len = ft_strlen(tk->value);
	while (i < len)
	{
		if (str[i] != tk->value[i])
			return (-1);
		i++;
	}
	return (i);
}
