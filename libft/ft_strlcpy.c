/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 17:31:55 by gbroccol          #+#    #+#             */
/*   Updated: 2020/05/15 17:27:39 by anastasiya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t len;

	i = 0;
	if (!dst || !src)
		return (0);
	if (size == 0)
		return ((size_t)(ft_strlen(src)));
	len = size - 1;
	while (len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
		len--;
	}
	dst[i] = '\0';
	return ((size_t)(ft_strlen(src)));
}
