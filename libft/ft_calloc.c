/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 23:57:27 by gbroccol          #+#    #+#             */
/*   Updated: 2020/05/19 14:11:45 by anastasiya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	char	*result;
	size_t	i;

	i = 0;
	if (num == 0 || size == 0)
	{
		if ((result = (char *)malloc(1)) == NULL)
			return (NULL);
		result[i] = '\0';
		return ((void *)result);
	}
	if ((result = (char *)malloc(num * size)) == NULL)
		return (NULL);
	while (i < (size * num))
	{
		result[i] = '\0';
		i++;
	}
	result[i] = '\0';
	return ((void *)result);
}
