/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:50:41 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/20 14:50:59 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	str_cmp_len(char *s1, char *s2)
{
	int size1;
	int size2;

	size1 = 0;
	size2 = 0;
	while (s1[size1] != '=' && s1[size1] != '\0')
		size1++;
	while (s2[size2] != '=' && s2[size2] != '\0')
		size2++;
	if (size1 == size2)
		return (1);
	return (0);
}

int			replace_env(char **array, char *str)
{
	int	i;
	int	size;

	i = -1;
	if (!array)
		return (1);
	size = ft_strlen_env(str);
	while (array[++i] != NULL)
	{
		if (ft_strchr(str, '=') && (!ft_strncmp(str, array[i], size) || \
		!ft_strcmp(str, array[i]) || (str_cmp_len(str, array[i]) && \
		!ft_strncmp(str, array[i], size - 1))))
		{
			free(array[i]);
			array[i] = NULL;
			if (!(array[i] = ft_strdup(str)))
				return (-1);
			i = 0;
			break ;
		}
		else if (!ft_strchr(str, '=') && !ft_strncmp(str, array[i], size))
			return (0);
	}
	return (i);
}
