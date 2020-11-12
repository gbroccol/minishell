/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:29:48 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/12 11:29:51 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		shell_exit(t_all *all)
{
	int	i;

	i = 0;
	if (all->pre_pipe)
		return (1);
	if (all->tok->args[1])
	{
		// if (all->tok->args[2] && all->tok->args[2][])
		// {
		// 	write(2, "minishell: exit: too many arguments\n", 36); // прописать разные коды выхода при разных аргументах
		// 	return (1);
		// }
		while (all->tok->args[1][i] != '\0')
		{
			if (!ft_isdigit(all->tok->args[1][i]))
			{
				all->status = 255;
				return (0);
			}
			i++;
		}
		all->status = ft_atoi(all->tok->args[1]);
	}
	return (0);
}
