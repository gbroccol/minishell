/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 23:59:45 by gbroccol          #+#    #+#             */
/*   Updated: 2020/05/19 21:23:06 by anastasiya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*s2_tmp;
	int		s1_size;
	int		s2_size;

	if (!s1 || !s2)
		return (NULL);
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	if ((res = malloc(s1_size + s2_size + 1)) == NULL)
		return (NULL);
	ft_strlcpy(res, s1, (size_t)(s1_size + 1));
	s2_tmp = (char *)s2;
	while (*s2_tmp != '\0')
	{
		res[s1_size] = *s2_tmp;
		s2_tmp++;
		s1_size++;
	}
	res[s1_size] = '\0';
	return (res);
}
