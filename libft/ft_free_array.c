/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:37:04 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/13 17:19:08 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_array(char **to_free)
{
	char	**tmp;

	tmp = to_free;
	while (*tmp != NULL)
	{
		free(*tmp);
		tmp++;
	}
	free(to_free);
	to_free = NULL;
}
