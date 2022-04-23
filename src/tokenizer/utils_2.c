#include "token.h"
#include "constant.h"
#include "utils.h"

int	check_whitespace(char *line, t_token *token)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	token->type = TK_WHITESPACE;
	token->len = i;
	return (i);
}

int	is_var(char *line)
{
	return (has_chars(*line, SH_SPECAIL_PARMS)
		|| is_alphanum(*line));
}
