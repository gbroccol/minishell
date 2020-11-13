/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:46:11 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/13 17:29:07 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_str_to_str(char *s1, char *s2)
{
	char		*res;
	char		*s2_tmp;
	int			s1_size;
	int			s2_size;

	if (!s1)
		s1_size = 0;
	else
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
	if (s1)
		free(s1);
	s1 = NULL;
	if (s2)
		free(s2);
	s2 = NULL;
	return (res);
}
