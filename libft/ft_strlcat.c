/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 17:32:08 by gbroccol          #+#    #+#             */
/*   Updated: 2020/05/19 22:16:13 by anastasiya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t len_dst;
	size_t len_src;
	size_t i;
	size_t j;

	len_dst = (size_t)ft_strlen(dst);
	len_src = (size_t)(ft_strlen(src));
	i = 0;
	j = 0;
	if (size <= len_dst)
		return (len_src + size);
	if (size > len_dst)
	{
		while (dst[i] != '\0')
			i++;
		while ((size - len_dst - 1 - j) && src[j] != '\0')
			dst[i++] = src[j++];
		dst[i] = '\0';
	}
	return (len_dst + len_src);
}
