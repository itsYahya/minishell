#include "utils.h"

int	has_chars(char c, char *chrs)
{
	int	i;

	i = 0;
	while (chrs[i])
	{
		if (chrs[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	is_space(char c)
{
	return (has_chars(c, " \r\n\t"));
}

int	is_special(char *s)
{
	return (has_chars(*s, "><|*$()") || ft_strncmp(s, "&&", 2) == 0);
}

int	is_alphanum(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}
