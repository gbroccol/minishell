/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_smb_in_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:37:59 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/18 16:13:43 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_smb_in_str(char smb, char *line, int null_smb)
{
	int			i;

	i = 0;
	if (null_smb == 0)
	{
		while (line[i] != '\0')
		{
			if (line[i] == smb)
				return (1);
			i++;
		}
	}
	if (null_smb == 1)
	{
		if (smb == '\0')
			return (1);
		while (line[i] != '\0')
		{
			if (line[i] == smb)
				return (1);
			i++;
		}
	}
	return (0);
}
