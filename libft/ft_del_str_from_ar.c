/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_str_from_ar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:38:31 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/13 17:27:00 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_del_str_from_ar(char **array, int nmb)
{
	int			index;
	int			write;
	char		**new_array;

	index = 0;
	while (array != NULL && array[index] != NULL)
		index++;
	if (!(new_array = (char **)malloc(sizeof(char *) * index)))
		return (NULL);
	index = 0;
	write = 0;
	while (array != NULL && array[index] != NULL)
	{
		if (index == nmb)
		{
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
