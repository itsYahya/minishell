#include <stdlib.h>
#include "list.h"
#include "minishell.h"
#include "constant.h"
#include "parse.h"
#include "token.h"

/*
 * count_size:
 * counts the argument if joined and returns pointer to next argument 
 *
 * @param tokens: pointer to first token in the argument
 * @param count: pointer to where to store argument length
 * @param is_asterisk:
 * pointer to where to store bool (does asterisk exist in argument)
 *
 * */
t_list	*count_size(t_list *tokens, int *arg_len)
{
	t_list	*prev;

	prev = NULL;
	*arg_len = 0;
	while (tokens && is_word(tokens))
	{
		*arg_len += tk_len(tokens->content);
		prev = tokens;
		tokens = tokens->next;
	}
	prev->next = NULL;
	return (tokens);
}

char	*join_tokens(t_list *tokens, int arg_len)
{
	int		i;
	char	*str;
	t_list	*head;

	head = tokens;
	str = malloc(sizeof(char) * (arg_len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (tk(tokens)->type == TK_ASTERISK)
			str[i++] = '*';
		else if (tk(tokens)->type == TK_EXPRESSION)
			i += tk_cpy(str + i, tk(tokens));
		else
			break ;
		head->next = tokens->next;
		if (head != tokens)
			ft_lstdelone(tokens, free_token);
		tokens = head->next;
	}
	str[arg_len] = 0;
	return (str);
}

int	expand_oth(t_context *ctx, t_list **head, t_list *cur)
{
	if (tk(cur)->type == TK_LITERAL)
		expand_literal(cur->content);
	else if (tk(cur)->type == TK_TEMPLATE_LITERAL)
		expand_template(ctx, cur->content);
	else if (tk(cur)->type == TK_EXPRESSION)
		expand_exp(cur->content);
	if (tk(cur)->value == NULL)
	{
		ft_lstclear(head, free_token);
		return (0);
	}
	ft_lstadd_back(head, cur);
	return (1);
}

t_list	*tk_ignore(t_list *cur, enum e_token_type types, int should_free)
{
	t_list	*next;

	while (cur && (tk(cur)->type & types))
	{
		next = cur->next;
		if (should_free)
			ft_lstdelone(cur, free_token);
		cur = next;
	}
	return (cur);
}
