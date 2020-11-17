/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_gnl_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:29:50 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/17 17:44:44 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		check_str_pipe(char *str)
{
	int			i;

	i = 0;
	if (str && str[i] != '\0')
	{
		while (str[i] != '\0')
			i++;
		while (i > 0 && (str[i] == '\0' ||
			str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
			i--;
		if (str[i] == '|')
			return (0);
		return (1);
	}
	return (1);
}

int				check_gnl_line(t_all *all, char *str)
{
	if (check_err_share_smb(all, str, all->ps))
		return (1);
	if (check_err_red_smb(all, str, all->ps))
		return (1);
	if (check_str_pipe(str))
		return (1);
	return (0);
}
