#include "libft.h"

char			**ft_str_to_array(char **array, char *new_str)
{
	int			index;
	char		**new_array;

	index = 0;
	while (array != NULL && array[index] != NULL)
		index++;
	if (!(new_array = (char **)malloc(sizeof(char *) * (index + 2))))
			return (NULL); // error
	index = 0;
	while (array != NULL && array[index] != NULL)
	{
		new_array[index] = array[index];
		index++;
	}
	new_array[index] = new_str;
	index++;
	new_array[index] = NULL;
		
	if (array != NULL)
		free(array);
	return (new_array);
}