#include "list.h"
#include <stdlib.h>
#include "utils.h"
#include "constant.h"

static int	nbr_size(int nbr)
{
	int	i;

	i = 1;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nbr)
{
	int		i;
	int		is_neg;
	char	*result;

	is_neg = nbr < 0;
	i = (nbr <= 0) + nbr_size(nbr);
	result = malloc(sizeof(char) * i);
	if (result == 0)
		return (0);
	result[0] = '-';
	result[--i] = 0;
	if (!is_neg)
		nbr *= -1;
	while (--i >= is_neg)
	{
		result[i] = (nbr % 10 * -1) + '0';
		nbr /= 10;
	}
	return (result);
}

char	*ft_dup_norm(t_list *tks)
{
	return (ft_strndup(tk(tks)->value + 1,
			tk(tks)->len - 2));
}
