/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_letter_to_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:47:42 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/13 17:27:38 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	rm_double_check(char *s1, char smb)
{
	int		index;

	index = 0;
	while (s1[index] != '\0')
	{
		if (s1[index] == smb)
			return (1);
		index++;
	}
	return (0);
}

char		*ft_letter_to_str(char *s1, char smb, int rm_double)
{
	char	*res;
	int		index;

	index = 0;
	if (s1 != NULL)
	{
		if (rm_double && rm_double_check(s1, smb))
			return (s1);
		index = ft_strlen(s1);
		if (!(res = malloc(index + 2)))
			return (NULL);
		ft_strlcpy(res, s1, (size_t)(index + 1));
		res[index] = smb;
		res[index + 1] = '\0';
		if (s1)
			free(s1);
		return (res);
	}
	if (!(res = malloc(sizeof(char) * 2)))
		return (NULL);
	res[0] = smb;
	res[1] = '\0';
	return (res);
}
