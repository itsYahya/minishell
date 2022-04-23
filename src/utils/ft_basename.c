#include "utils.h"

char	*ft_basename(char *s, char c)
{
	int	len;

	len = ft_strlen(s);
	if (c == 0)
		return ((char *) s + len);
	while (len--)
	{
		if (s[len] == c)
			return ((char *) s + len);
	}
	return (0);
}
