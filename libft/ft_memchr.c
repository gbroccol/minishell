/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 16:32:16 by gbroccol          #+#    #+#             */
/*   Updated: 2020/05/08 22:47:07 by anastasiya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_tmp;
	unsigned char	c_tmp;

	s_tmp = (unsigned char*)s;
	c_tmp = (unsigned char)c;
	while (n > 0)
	{
		if (*s_tmp == c_tmp)
			return ((void *)s_tmp);
		s_tmp++;
		n--;
	}
	return (NULL);
}
