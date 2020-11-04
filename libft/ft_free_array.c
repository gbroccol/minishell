#include "libft.h"

void	ft_free_array(char **to_free)
{
	char **tmp;


	tmp = to_free;
	while (*tmp != NULL)
	{
		free(*tmp);
		tmp++;
	}
	free(to_free);
}