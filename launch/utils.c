/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:24:34 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/20 14:28:25 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		print_error(char *exec, char *exec2, char *err_to_print, int ret)
{
	int size;

	size = ft_strlen(exec);
	write(2, "bash: ", 6);
	write(2, exec, size);
	if (size > 0)
		write(2, ": ", 2);
	size = ft_strlen(exec2);
	write(2, exec2, size);
	if (size > 0)
		write(2, ": ", 2);
	write(2, err_to_print, ft_strlen(err_to_print));
	write(2, "\n", 1);
	return (ret);
}

void	ft_eof(void)
{
	int fd[2];

	pipe(fd);
	write(fd[1], "", 0);
	dup2(fd[0], 0);
	if (fd[1] >= 3)
		close(fd[1]);
	if (fd[0] >= 3)
		close(fd[0]);
}

void	close_fd(t_all *all)
{
	if (all->fds[1] >= 3)
		close(all->fds[1]);
	if (all->fds[0] >= 3)
		close(all->fds[0]);
}
