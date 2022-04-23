#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "token.h"
#include "utils.h"
#include "constant.h"

int	get_next_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	is_match(char *str, t_list *tks);

int	match_asterisk(char *str, t_list *tks)
{
	int	n;

	tks = tk_ignore(tks, TK_ASTERISK, 0);
	if (tks == NULL || tk(tks)->type != TK_EXPRESSION)
		return (1);
	while (*str)
	{
		n = get_next_char(str, tk(tks)->value[0]);
		if (n == -1)
			return (0);
		if (is_match(str + n, tks))
			return (1);
		str += n + 1;
	}
	return (0);
}

int	is_match(char *str, t_list *tks)
{
	int	n;

	while (tks)
	{
		if (tk(tks)->type == TK_ASTERISK)
			return (match_asterisk(str, tks));
		else if (tk(tks)->type == TK_EXPRESSION)
		{
			n = tk_cmp(tks->content, str);
			if (n == -1)
				return (0);
			str += n;
			tks = tks->next;
		}
		else
			break ;
	}
	return (*str == 0);
}

t_list	*match(t_list *tks)
{
	DIR				*dp;
	struct dirent	*entry;
	t_list			*head;
	t_list			*cur;

	dp = opendir(".");
	if (dp == NULL)
		return (NULL);
	head = NULL;
	while (1)
	{
		entry = readdir(dp);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] != '.' && is_match(entry->d_name, tks))
		{
			cur = new_token(TK_EXPRESSION, ft_strndup(entry->d_name, -1));
			if (cur == NULL)
				break ;
			ft_lstadd_back(&head, cur);
		}
	}
	if (cur == NULL)
		ft_lstclear(&head, free_token);
	return (closedir(dp), head);
}
