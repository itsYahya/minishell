#include "token.h"
#include "utils.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char	*ft_strjoin(char *s1, char *s2, int s2_len)
{
	int		s1_len;
	char	*str;

	s1_len = 0;
	if (s1)
		s1_len = ft_strlen(s1);
	if (s2_len == -1)
		s2_len = ft_strlen(s2);
	str = malloc(s1_len + s2_len + 1);
	if (str == 0)
	{
		free(s1);
		return (0);
	}
	ft_strncpy(str, s1, s1_len);
	ft_strncpy(str + s1_len, s2, s2_len);
	free(s1);
	return (str);
}

char	*ft_strndup(char *src, int len)
{
	char	*ret;

	if (src == NULL)
		return (NULL);
	if (len == -1)
		len = ft_strlen(src);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strncpy(ret, src, len);
	return (ret);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	if (n == -1)
		n = ft_strlen(s2);
	if (n < 1)
		return (0);
	i = 0;
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

int	ft_append(char *dest, char *src, int len)
{
	int	i;

	while (*dest)
		dest++;
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}

int	til_set(char *str, char *set, int n)
{
	int	i;

	i = 0;
	while (i < n && str[i] && !has_chars(str[i], set))
		i++;
	return (i);
}
