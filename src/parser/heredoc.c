#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "minishell.h"
#include "astree.h"
#include "parse.h"
#include "constant.h"
#include "token.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

int	put_heredoc(t_context *ctx, int fd, char *delimiter, int is_expandable)
{
	char	*line;
	char	*str;

	while (69)
	{
		line = readline(PROMPT_2);
		if (line == NULL
			|| ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
			break ;
		if (is_expandable)
		{
			str = expand_str(ctx, line, ft_strlen(line));
			free(line);
			if (str == NULL)
				return (free(delimiter), close(fd), 0);
			line = str;
		}
		ft_putstr(fd, line);
		ft_putstr(fd, "\n");
		free(line);
	}
	free(line);
	free(delimiter);
	close(fd);
	return (1);
}

int	heredoc_len(t_list *tks)
{
	t_list	*cur;
	int		len;

	len = 0;
	cur = tks;
	while (cur && is_word(cur))
	{
		if (tk(cur)->type == TK_LITERAL || tk(cur)->type == TK_TEMPLATE_LITERAL)
		{
			tk(cur)->len -= 2;
			tk(cur)->value += 1;
		}
		len += tk_len(cur->content);
		cur = cur->next;
	}
	return (len);
}

int	join_heredoc(t_list *tks)
{
	char	*str;
	t_list	*next;
	t_list	*cur;
	int		len;

	cur = tks->next;
	len = heredoc_len(cur);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (free(str), 0);
	while (cur && is_word(cur))
	{
		next = cur->next;
		tk_cpy(str, cur->content);
		str += tk_len(cur->content);
		if (cur != tks->next)
			ft_lstdelone(cur, free_token);
		cur = next;
	}
	tks->next->next = cur;
	return (tk_set(tks->next->content, TK_EXPRESSION, str - len, -1));
}

t_list	*_read_heredoc(t_context *ctx, t_list *tks)
{
	char	*tmp_file;
	char	*delimiter;
	int		fd;
	int		is_expandable;

	tmp_file = get_tmp();
	if (tmp_file == NULL)
		return (NULL);
	fd = open(tmp_file, O_RDWR | O_CREAT);
	if (fd == -1)
	{
		ft_merror("", "failed to read heredoc");
		free(tmp_file);
		return (NULL);
	}
	is_expandable = expandable(tks->next);
	if (!join_heredoc(tks))
		return (NULL);
	delimiter = tk(tks->next)->value;
	tk(tks->next)->value = tmp_file;
	if (put_heredoc(ctx, fd, delimiter, is_expandable))
		return (tks->next->next);
	free(tmp_file);
	return (NULL);
}

int	read_heredoc(t_context *ctx, t_list *tks)
{
	while (tk(tks)->type != TK_EOF)
	{
		if (tk(tks)->type != TK_HEREDOC)
		{
			tks = tks->next;
			continue ;
		}
		tks = _read_heredoc(ctx, tks);
		if (tks == NULL)
		{
			ft_lstdelone(tks, free_token);
			return (0);
		}
	}
	return (1);
}
