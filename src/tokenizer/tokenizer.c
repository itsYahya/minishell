#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "token.h"
#include "utils.h"
#include "constant.h"

/*
 * Check if what after $ sign is valid to be considier it as a variable
 * Parameter can be number or name or special character
 * See:
 * https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
 * 
 * */
int	check_two_chars_tokens(t_token *tk, char *line)
{
	if (strncmp(line, "&&", 2) == 0)
		tk->type = TK_AND;
	else if (strncmp(line, "||", 2) == 0)
		tk->type = TK_OR;
	else if (strncmp(line, "<<", 2) == 0)
		tk->type = TK_HEREDOC;
	else if (strncmp(line, ">>", 2) == 0)
		tk->type = TK_APPEND;
	else
		return (0);
	tk->len = 2;
	return (1);
}

int	check_one_chars_tokens(t_token *tk, char *line)
{
	if (*line == '*')
		tk->type = TK_ASTERISK;
	else if (*line == '>')
		tk->type = TK_REDIRICT_OUT;
	else if (*line == '<')
		tk->type = TK_REDIRICT_IN;
	else if (*line == '|')
		tk->type = TK_PIPE;
	else if (*line == ')')
		tk->type = TK_PARNETHESIS;
	else
		return (0);
	tk->len = 1;
	return (1);
}

int	scan_subcmd(char *line)
{
	int	i;
	int	prt;

	prt = 1;
	i = 1;
	while (line[i] != 0)
	{
		if (line[i] == '(')
			prt++;
		if (line[i] == ')')
			prt--;
		if (prt == 0)
			break ;
		i++;
	}
	if (prt)
		return (1);
	return (i + 1);
}

char	*_tokenizer(char *line, t_token *token)
{
	token->value = line;
	if (check_whitespace(line, token))
		;
	else if (check_two_chars_tokens(token, line))
		;
	else if (check_one_chars_tokens(token, line))
		;
	else if (*line == '$' && is_var(line + 1))
		tk_set(token, TK_VAR, token->value, scan_var(line));
	else if (*line == CHAR_SINGLE_QOUTE)
		tk_set(token, TK_LITERAL, token->value, scan_literal(line));
	else if (*line == CHAR_DOUBLE_QOUTE)
		tk_set(token, TK_TEMPLATE_LITERAL, token->value, scan_literal(line));
	else if (*line == '(')
		tk_set(token, TK_SUB_CMD, token->value, scan_subcmd(line));
	else
		tk_set(token, TK_EXPRESSION, token->value, scan_word(line));
	return (line + token->len);
}

t_list	*tokenizer(char *line)
{
	t_list				*head;
	t_list				*cur;
	enum e_token_type	type;

	head = NULL;
	while (69)
	{
		cur = new_token(TK_EOF, NULL);
		if (cur == NULL)
		{
			ft_lstclear(&head, free_token);
			return (NULL);
		}
		ft_lstadd_back(&head, cur);
		if (*line == '\0' || *line == '\n')
			break ;
		line = _tokenizer(line, cur->content);
		type = ((t_token *)cur->content)->type;
		if (!(type & (TK_WORDABLE)))
			while (is_space(*line))
				line++;
	}
	return (head);
}
