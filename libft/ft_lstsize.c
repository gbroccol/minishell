/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 18:53:27 by gbroccol          #+#    #+#             */
/*   Updated: 2020/05/16 19:01:31 by anastasiya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*count;
	int		i;

	if (lst == NULL)
		return (0);
	count = lst;
	i = 1;
	while (count->next != NULL)
	{
		i++;
		count = count->next;
	}
	return (i);
}
