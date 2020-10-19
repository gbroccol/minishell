/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 16:32:54 by gbroccol          #+#    #+#             */
/*   Updated: 2020/05/18 23:09:18 by anastasiya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			index;
	unsigned char	*dest2;
	unsigned char	*src2;

	if ((!dest && !src) || !n || dest == src)
		return (dest);
	index = 1;
	dest2 = (unsigned char *)dest;
	src2 = (unsigned char *)src;
	if (src2 < dest2)
		while (n >= index)
		{
			dest2[n - index] = src2[n - index];
			index++;
		}
	else
		while (n > 0)
		{
			*dest2 = *src2;
			dest2++;
			src2++;
			n--;
		}
	return (dest);
}
