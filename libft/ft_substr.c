/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 20:46:33 by gbroccol          #+#    #+#             */
/*   Updated: 2020/05/20 00:38:55 by anastasiya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		len_s;

	if (!s)
		return (ft_strdup(""));
	len_s = ft_strlen(s);
	if (len_s < start)
		return (ft_strdup(""));
	if (len_s - start < len)
	{
		if ((str = malloc(len_s - start + 1)) == NULL)
			return (NULL);
		ft_strlcpy(str, &s[start], (len_s - start + 1));
	}
	else
	{
		if ((str = malloc(len + 1)) == NULL)
			return (NULL);
		ft_strlcpy(str, &s[start], (len + 1));
	}
	return (str);
}
