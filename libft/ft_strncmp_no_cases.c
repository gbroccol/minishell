/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_no_cases.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 17:33:24 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/27 14:26:41 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cmpcases(char a, char b)
{
	if (a >= 'a' && a <= 'z')
	{
		a -= 32;
		if (a == b)
			return (0);
	}
	else if (a >= 'A' && a <= 'Z')
	{
		a += 32;
		if (a == b)
			return (0);
	}
	return (1);
}

int	ft_strncmp_nc(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n > 0 && *s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			if (ft_cmpcases(*s1, *s2) == 1)
				return ((int)((unsigned char)*s1 - (unsigned char)*s2));
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((int)((unsigned char)*s1 - (unsigned char)*s2));
}
