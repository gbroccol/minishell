/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 17:32:50 by gbroccol          #+#    #+#             */
/*   Updated: 2020/05/15 17:07:25 by anastasiya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;

	if (s[0] == '\0' && c != 0)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
		i++;
	while (s[i] != (const char)c)
	{
		i--;
		if (i == 0 && s[i] != (const char)c)
			return (NULL);
	}
	if (s[i] == (const char)c)
		return ((char *)&s[i]);
	return (NULL);
}
