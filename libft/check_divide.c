/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_divide.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:37:59 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/11 21:37:59 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				check_divide(char smb, char *line, int null_smb)
{
	int			i;

	i = 0;
	if (null_smb == 0)
		while (line[i] != '\0')
		{
			if (line[i] == smb)
				return (1);
			i++;
		}
	if (null_smb == 1)
		while (line[i] != '\0')
		{
			if (line[i] == smb || line[i] == '\0')
				return (1);
			i++;
		}
	return (0);
}
