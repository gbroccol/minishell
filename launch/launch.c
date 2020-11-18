/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:37:39 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/17 20:19:09 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				check_local(t_all *all)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (all->tok->args[++i] != NULL)
	{
		if (all->tok->args[i][j] == '=' || ft_isdigit(all->tok->args[i][j]) || \
		check_env_key(all->tok->args[i]) || !strchr(all->tok->args[i], '='))
			return (1);
	}
	i = -1;
	while (all->tok->args[++i] != NULL)
	{
		if ((j = replace_env(all->local, all->tok->args[i])) < 0)
			return (-1);
		if (j != 0)
			if (!(all->local = ft_str_to_array(all->local, \
			ft_strdup(all->tok->args[i]))))
				return (-1);
		if ((j = replace_env(all->env, all->tok->args[i])) < 0)
			return (-1);
		update_home(all, all->tok->args[i]);
	}
	return (0);
}

static	void	fork_error(t_all *all)
{
	print_error(all->tok->cmd, "", strerror(errno), 0);
	if (all->fds[0] >= 3)
		close(all->fds[0]);
	if (all->fds[1] >= 3)
		close(all->fds[1]);
}

static	int		print_cmd_err(t_all *all, char *error, int ret)
{
	print_error(all->tok->cmd, "", error, ret);
	all->status = 127;
	return (ret);
}

static	int		find_command(t_all *all, t_token *tok)
{
	int ret;

	if (tok->args[0][0] != '/' && ft_strncmp(tok->args[0], "./", 2) && \
	ft_strncmp(tok->args[0], "../", 3))
	{
		if ((ret = check_pwd(all->env, tok->args, all)) != 0)
		{
			if (!(ret = find_path(all->env, tok->args, all)))
				return (0);
			else if (ret == 1)
				return (print_cmd_err(all, "No such file or directory", 1));
			else if (ret == 2)
			{
				all->status = 0;
				if (tok->pipe)
					ft_eof();
				else if (!tok->pipe)
					dup2(all->temp_0, 0);
				if (check_local(all) > 0)
					print_cmd_err(all, "command not found", 1);
				return (1);
			}
		}
	}
	return (2);
}

int				launch(t_all *all, int r_redir)
{
	pid_t		pid;
	int			ret;
	t_token		*tok;

	tok = all->tok;
	if ((ret = find_command(all, tok)) == 0 || ret == 1)
		return (ret);
	pid = fork();
	if (pid == 0)
		daughter(all, tok);
	else if (pid < 0)
		fork_error(all);
	else
		parent(all, tok, pid, r_redir);
	return (1);
}
