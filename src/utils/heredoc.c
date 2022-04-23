#include "utils.h"
#include "token.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "parse.h"
#include "constant.h"

#define FT_TMPFILE "/tmp/minishell-aaaaaa"

/*
 * abcdefghijklmnopkrstuvwxyz0123456789
 *
 * */
void	get_next_comb(char *s)
{
	int	len;
	int	i;

	len = ft_strlen(s);
	i = 1;
	while (i < 7 && s[len - i] == '9')
		s[len - i++] = 'a';
	if ((s[len - i] >= 'a' && s[len - i] < 'z')
		|| (s[len - i] >= '0' && s[len - i] < '9'))
		s[len - i]++;
	else if (s[len - i] == 'z')
		s[len - i] = '0';
}

char	*get_tmp(void)
{
	char	*file;

	file = ft_strndup(FT_TMPFILE, -1);
	if (file == NULL)
		return (NULL);
	while (1)
	{
		if (access(file, F_OK | W_OK | R_OK) == 0)
		{
			get_next_comb(file);
			continue ;
		}
		break ;
	}
	return (file);
}

int	expandable(t_list *tks)
{
	while (is_word(tks))
	{
		if (tk(tks)->type == TK_LITERAL
			|| tk(tks)->type == TK_TEMPLATE_LITERAL)
			return (0);
		tks = tks->next;
	}
	return (1);
}

int	tk_set(t_token *tk, enum e_token_type type, char *value, int len)
{
	tk->len = len;
	tk->value = value;
	tk->type = type;
	return (1);
}
