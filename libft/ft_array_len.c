
#include "libft.h"

int				ft_array_len(char **array)
{
	int			i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}