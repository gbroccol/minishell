/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 17:33:03 by gbroccol          #+#    #+#             */
/*   Updated: 2020/05/19 23:47:34 by anastasiya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	big_len;

	if (*little == '\0')
		return ((char *)big);
	little_len = (size_t)(ft_strlen(little));
	big_len = (size_t)(ft_strlen(big));
	if (big_len < little_len || len < little_len)
		return (NULL);
	while (len >= little_len && *big != '\0')
	{
		if (*big == *little && (!ft_memcmp(big, little, little_len)))
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
