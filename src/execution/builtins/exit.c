#include "builtins.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

int	ft_checkerror(long long number, int *sing, char ch)
{
	if (ch != 0)
		return (1);
	if (number < 0)
	{
		if (number != LLONG_MIN)
			return (1);
		else if (number == LLONG_MIN && *sing == 1)
			return (1);
		*sing = 1;
	}
	return (0);
}

long long	ft_atoll(char *str, int *error)
{
	long long		number;
	int				index;
	int				sing;

	*error = 0;
	number = 0;
	index = 0;
	sing = 1;
	if (str[index] == '-')
	{
		sing = -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		number = number * 10 + (str[index] - '0');
		index++;
		if (number < 0)
			break ;
	}
	*error = ft_checkerror(number, &sing, str[index]);
	return (number * sing);
}

void	ft_exiterror(char *word)
{
	ft_putstr(2, g_data.basename);
	ft_putstr(2, ": exit: ");
	ft_putstr(2, word);
	ft_putstr(2, ": numeric argument required\n");
	exit(255);
}

void	ft_exit(char **words)
{
	long long	code;
	int			error;

	if (*words == 0)
	{
		ft_putstr(2, "exit\n");
		exit(0);
	}
	else
	{
		code = ft_atoll(*words, &error);
		ft_putstr(2, "exit\n");
		if (error == 1)
			ft_exiterror(*words);
		words++;
		if (*words != 0)
		{
			ft_merror("exit: ", "too many arguments\n");
			return ;
		}
		exit(code % 256);
	}
}
