/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 23:57:47 by gbroccol          #+#    #+#             */
/*   Updated: 2020/05/19 21:01:09 by anastasiya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	int		i;
	int		len;

	len = ft_strlen((char *)s);
	if ((res = malloc(len + 1)) == NULL)
		return (NULL);
	i = 0;
	while (len)
	{
		res[i] = s[i];
		i++;
		len--;
	}
	res[i] = '\0';
	return (res);
}
