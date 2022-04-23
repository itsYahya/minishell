#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "utils.h"

char	*ft_join(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	char	*str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1_len + s2_len + 3));
	ft_strncpy(str, s1, s1_len);
	ft_strncpy(str + s1_len, ": ", 2);
	ft_strncpy(str + s1_len + 2, s2, s2_len);
	return (str);
}

int	ft_perror(char *msg)
{
	char	*str;

	str = ft_join(g_data.basename, msg);
	if (str == NULL)
		str = msg;
	perror(str);
	free(str);
	return (1);
}
