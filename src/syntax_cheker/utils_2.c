#include "minishell.h"
#include "syntax_checker.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_list	*init_tokens(t_list *head, t_list **tokens, char **line)
{
	*line = (char *)malloc(sizeof(char) * tk(head)->len - 1);
	if (!*line)
		return (NULL);
	ft_strncpy(*line, tk(head)->value + 1, tk(head)->len - 2);
	*tokens = tokenizer(*line);
	if (!*tokens)
		free(*line);
	return (*tokens);
}

t_list	*_checksub_cmd(t_list *head, int *err)
{
	char	*line;
	t_list	*tokens;
	t_list	*head_;
	int		cmd;

	cmd = 0;
	head_ = init_tokens(head, &tokens, &line);
	if (!head_)
		return (NULL);
	while (tk(tokens)->type != TK_EOF)
	{
		tokens = ft_checkcmd(tokens, err, cmd);
		cmd++;
		if (*err)
		{
			ft_errorhandler(tokens, *err, 1);
			break ;
		}
	}
	free(line);
	ft_lstclear(&head_, NULL);
	return (head);
}
