/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 00:01:08 by gbroccol          #+#    #+#             */
/*   Updated: 2020/05/19 14:52:26 by anastasiya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_int(int n)
{
	int	i;
	int	negativ;

	i = 0;
	negativ = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		negativ = 1;
		n = n * (-1);
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (negativ ? (i + 1) : i);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		count;
	int		negativ;

	negativ = 0;
	if (n < 0)
		negativ = 1;
	count = ft_count_int(n);
	if ((res = malloc((count + 1) * sizeof(char))) == NULL)
		return (NULL);
	res[count] = '\0';
	if (n == -2147483648)
		res[--count] = '8';
	if (n == -2147483648)
		n = -214748364;
	if (negativ == 1)
		n = n * (-1);
	while (count)
	{
		res[--count] = ((char)(n % 10 + '0'));
		n = n / 10;
	}
	if (negativ == 1)
		res[0] = '-';
	return (res);
}
