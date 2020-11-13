/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:29:48 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/13 19:23:09 by pvivian          ###   ########.fr       */
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
		while (all->tok->args[1][i] != '\0')
		{
			if (!ft_isdigit(all->tok->args[1][i]))
			{
				write(2, "exit\n", 5);
				write(2, "bash: ", 6);
				write(2, all->tok->cmd, ft_strlen(all->tok->cmd));
				write(2, ": ", 2);
				write(2, all->tok->args[1], ft_strlen(all->tok->args[1]));
				write(2, ": numeric argument required\n", 28);
				all->status = 255;
				exit_all(all);
				return (0);
			}
			i++;
		}
		if (all->tok->args[2])
		{
			all->status = 1;
			write(2, "exit\n", 5);
			return (print_error(all->tok->cmd, "too many arguments", 1));
		}
		all->status = ft_atoi(all->tok->args[1]);
	}
	write(2, "exit\n", 5);
	exit_all(all);
	return (0);
}
