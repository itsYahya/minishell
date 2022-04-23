#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_putstr(int fd, char *s)
{
	return (write(fd, s, ft_strlen(s)));
}

void	ft_strncpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
}
