#include "utils.h"
#include <stdlib.h>

void	free_mut(t_mut *mut)
{
	int	i;

	if (mut->size <= 0)
		return ;
	i = 0;
	while (mut->content[i])
	{
		free(mut->content[i]);
		i++;
	}
	free(mut->content);
}

void	*ft_realloc(void *mem, int size, int append)
{
	char	*from;
	char	*to;
	int		i;

	from = (char *)mem;
	to = malloc(sizeof(char *) * (size + append));
	if (to == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		to[i] = from[i];
		i++;
	}
	free(mem);
	return (to);
}

int	mut_add(t_mut *arr, void *new_value)
{
	if (arr->len >= arr->size)
	{
		arr->content = ft_realloc(arr->content, arr->size, arr->defsize);
		if (arr->content == NULL)
			return (0);
		arr->size += arr->defsize;
	}
	arr->content[arr->len] = new_value;
	if (new_value != NULL)
	{
		arr->len++;
		mut_add(arr, NULL);
	}
	return (1);
}

void	init_mut(t_mut *arr, int defsize)
{
	arr->content = NULL;
	arr->len = 0;
	arr->size = 0;
	arr->defsize = defsize;
}

int	search_mut(t_mut *arr, char *name)
{
	int	i;

	i = 0;
	while (arr->content[i])
	{
		if (ft_strncmp(arr->content[i], name, ft_strlen(name)) == 0
			&& (((char *)arr->content[i])[ft_strlen(name)] == '='
			|| ((char *)arr->content[i])[ft_strlen(name)] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}
