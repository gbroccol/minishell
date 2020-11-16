/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:37:39 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/16 15:32:59 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int		check_local(t_all *all)
{
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	while (all->tok->args[i] != NULL)
	{
		if (all->tok->args[i][j] == '=' || ft_isdigit(all->tok->args[i][j] ) || check_env_key(all->tok->args[i]) || !strchr(all->tok->args[i], '='))
			return (1);
		i++;
	}
	i = 0;
	while (all->tok->args[i] != NULL)
	{
		if ((j = replace_env(all->local, all->tok->args[i])) < 0)
			return (-1);
		if (j != 0)
			if(!(all->local = ft_str_to_array(all->local, ft_strdup(all->tok->args[i]))))
				return (-1);
		if ((j = replace_env(all->env, all->tok->args[i])) < 0)
			return (-1);
		update_home(all, all->tok->args[i]);
		i++;
	}
	return (0);
}

int		launch(t_all *all, int r_redir)
{
	pid_t		pid;
	int			status;
	int			ret;
	t_token		*tok;

	tok = all->tok;
	if (tok->args[0][0] != '/' && ft_strncmp(tok->args[0], "./", 2) && \
	ft_strncmp(tok->args[0], "../", 3))
	{
		if ((ret = check_pwd(all->env, tok->args)) != 0)
		{
			if (!(ret = find_path(all->env, tok->args)))
				return (0);
			else if (ret == 1)
			{
				if (tok->pipe)
					ft_eof();
				else if (!tok->pipe)
					dup2(all->temp_0, 0);
				if (check_local(all) > 0)
				{
					print_error(all->tok->cmd, "", "command not found", 0);
					all->status = 127;
				}
				return (1);
			}
		}
	}
	pid = fork();
	if (pid == 0)
	{
		if (signal(SIGINT, SIG_DFL) == SIG_ERR || \
		signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			exit(EXIT_FAILURE);
		if (tok->pipe)
		{
			dup2(all->fds[1], 1);
			close(all->fds[0]);
		}
		if (execve(tok->args[0], tok->args, all->env) == -1)
		{
			print_error(all->tok->cmd, "", strerror(errno), 0);
			exit(EXIT_FAILURE);
		}
		close(all->fds[1]);
	}
	else if (pid < 0)
	{
		print_error(all->tok->cmd, "", strerror(errno), 0);
		close(all->fds[0]);
		close(all->fds[1]);
	}
	else
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR || \
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (0);
		if (tok->pipe)
		{
			if (r_redir > 0)
				ft_eof();
			else
				dup2(all->fds[0], 0);
		}
		close(all->fds[1]);
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
		close(all->fds[0]);
		if (!tok->pipe)
		{
			dup2(all->temp_0, 0);
			dup2(all->temp_1, 1);
			all->pre_pipe = 0;
		}
	}
	return (1);
}
