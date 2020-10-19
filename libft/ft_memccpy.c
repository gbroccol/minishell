/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 16:32:02 by gbroccol          #+#    #+#             */
/*   Updated: 2020/05/18 22:48:26 by anastasiya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*dest2;
	unsigned char	*src2;

	dest2 = (unsigned char *)dest;
	src2 = (unsigned char *)src;
	while (n > 0)
	{
		*dest2 = *src2;
		if (*src2 == (unsigned char)c)
			break ;
		dest2++;
		src2++;
		n--;
	}
	if (*dest2 != (unsigned char)c)
		return (NULL);
	dest2++;
	return (dest2);
}
