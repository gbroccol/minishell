/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:12:22 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/18 16:12:33 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_sort_array2(char **array, int array_len)
{
	int			i;
	char		*tmp;

	i = 0;
	while (i < array_len - 1)
	{
		if (ft_strcmp(array[i], array[i + 1]) > 0)
		{
			tmp = array[i];
			array[i] = array[i + 1];
			array[i + 1] = tmp;
			i = 0;
			continue ;
		}
		i++;
	}
	return (array);
}

char		**ft_sort_array(char **env)
{
	int			ascii_smb;
	int			i;
	int			j;
	int			array_len;
	char		**new_ar;

	array_len = ft_array_len(env);
	ascii_smb = 32;
	if (!(new_ar = (char **)malloc(sizeof(char *) * (array_len + 1))))
		return (NULL);
	new_ar[array_len] = NULL;
	j = 0;
	while ((ascii_smb >= 32 && ascii_smb <= 126) && j < array_len)
	{
		i = 0;
		while (j < array_len && env[i] != NULL)
		{
			if (env[i][0] == ascii_smb)
				new_ar[j++] = ft_strdup(env[i]);
			i++;
		}
		ascii_smb++;
	}
	return (ft_sort_array2(new_ar, array_len));
}
