#include "token.h"
#include "utils.h"
#include "constant.h"

unsigned int	scan_word(char *s)
{
	int	i;

	i = 1;
	while (s[i]
		&& s[i] != CHAR_SINGLE_QOUTE
		&& s[i] != CHAR_DOUBLE_QOUTE
		&& !is_special(s + i)
		&& !is_space(s[i]))
		i++;
	return (i);
}

unsigned int	scan_var(char *s)
{
	int	i;

	i = 1;
	if (has_chars(s[1], SH_SPECAIL_PARMS))
		return (2);
	if (s[1] >= '0' && s[1] <= '9')
		return (2);
	while (is_alphanum(s[i]))
		i++;
	return (i);
}

unsigned int	scan_literal(char *s)
{
	char			c;
	unsigned int	i;

	c = *s;
	i = 1;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == '\0')
		return (1);
	return (i + 1);
}
