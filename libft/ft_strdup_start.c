/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:07:41 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/12 17:07:43 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_start(const char *s, int start)
{
	char	*res;
	int		index;
	int		len;

	len = ft_strlen((char *)s);
	if ((res = malloc(len + 1 - start)) == NULL)
		return (NULL);
	index = 0;
	while (s[start] != '\0')
	{
		res[index] = s[start];
		index++;
		start++;
	}
	res[index] = '\0';
	return (res);
}
