/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 20:14:40 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/20 15:31:36 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			child(t_all *all, t_token *tok)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (tok->pipe)
	{
		dup2(all->fds[1], 1);
		if (all->fds[0] >= 3)
			close(all->fds[0]);
	}
	if (execve(tok->args[0], tok->args, all->env) == -1)
	{
		print_error(all->tok->cmd, "", strerror(errno), 0);
		exit(errno);
	}
	if (all->fds[1] >= 3)
		close(all->fds[1]);
}

static	void	parent_wait(t_all *all, pid_t pid)
{
	int	status;

	waitpid(pid, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		waitpid(pid, &status, WUNTRACED);
	all->status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			all->status = 130;
			write(1, "\n", 1);
		}
		else if (WTERMSIG(status) == 3)
		{
			all->status = 131;
			write(1, "Quit: 3\n", 8);
		}
	}
}

void			parent(t_all *all, t_token *tok, pid_t pid, int r_redir)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (tok->pipe)
	{
		if (r_redir > 0)
		{
			ft_eof();
			dup2(all->temp_1, 1);
		}
		else
			dup2(all->fds[0], 0);
		all->pre_pipe = 1;
	}
	if (all->fds[1] >= 3)
		close(all->fds[1]);
	parent_wait(all, pid);
	if (all->fds[0] >= 3)
		close(all->fds[0]);
	if (!tok->pipe)
	{
		dup2(all->temp_0, 0);
		dup2(all->temp_1, 1);
		all->pre_pipe = 0;
	}
}
