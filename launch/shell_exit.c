/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:29:48 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/15 16:52:24 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_first_arg(t_all *all)
{
	int	i;

	i = 0;
	while (all->tok->args[1][i] != '\0')
	{
		if (!ft_isdigit(all->tok->args[1][i]))
		{
			print_error(all->tok->cmd, all->tok->args[1], \
			"numeric argument required", 0);
			all->status = 255;
			exit_all(all);
			return (0);
		}
		i++;
	}
	return (1);
}

int			shell_exit(t_all *all)
{
	if (all->pre_pipe)
		return (1);
	write(2, "exit\n", 5);
	if (all->tok->args[1])
	{
		if (check_first_arg(all) == 0)
			return (0);
		if (all->tok->args[2])
		{
			all->status = 1;
			return (print_error(all->tok->cmd, "", "too many arguments", 1));
		}
		all->status = ft_atoi(all->tok->args[1]);
	}
	exit_all(all);
	return (0);
}
