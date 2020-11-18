/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_str_from_ar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:38:31 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/18 16:22:50 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**new_arr(char **array)
{
	int		index;
	char	**new_array;

	index = 0;
	while (array != NULL && array[index] != NULL)
		index++;
	if (!(new_array = (char **)malloc(sizeof(char *) * index)))
		return (NULL);
	return (new_array);
}

char		**ft_del_str_from_ar(char **array, int nmb)
{
	int		index;
	int		write;
	char	**new_array;

	if (!(new_array = new_arr(array)))
		return (NULL);
	index = 0;
	write = 0;
	while (array != NULL && array[index] != NULL)
	{
		if (index == nmb)
		{
			free(array[nmb]);
			array[nmb] = NULL;
			index++;
			continue ;
		}
		new_array[write++] = array[index++];
	}
	new_array[write] = NULL;
	if (array != NULL)
		free(array);
	array = NULL;
	return (new_array);
}
