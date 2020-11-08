#include "libft.h"

char			**ft_del_str_from_ar(char **array, int nmb)
{
	int			index;
    int         write;
	char		**new_array;

	index = 0;
	while (array != NULL && array[index] != NULL)
		index++;
	if (!(new_array = (char **)malloc(sizeof(char *) * index)))
			return (NULL); // error
	index = 0;
    write = 0;
	while (array != NULL && array[index] != NULL)
	{
        if (index == nmb)
        {
            index++;
            continue ;
        }
		new_array[write] = array[index];
		index++;
        write++;
	}
	new_array[write] = NULL;
	if (array != NULL)
		free(array);
	return (new_array);
}