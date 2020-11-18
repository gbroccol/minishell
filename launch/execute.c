/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:11:35 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/18 10:39:26 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			print_error(char *exec, char *exec2, char *err_to_print, int ret)
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

static int	redir_err(t_all *all, char *exec, char *error, int status)
{
	all->status = status;
	dup2(all->temp_1, 1);
	dup2(all->temp_0, 0);
	if (all->fds[1] >= 3)
		close(all->fds[1]);
	if (all->fds[0] >= 3)
		close(all->fds[0]);
	return (print_error(exec, "", error, -1));
}

static int	check_redir(t_all *all, int *r_redir)
{
	t_token		*token;
	int			i;
	int			fd;

	i = 0;
	token = all->tok;
	fd = 0;
	while (token->redirect[i] != NULL)
	{
		if (!ft_strcmp(token->redirect[i], ">") || \
		!ft_strcmp(token->redirect[i], ">>"))
		{
			if (!token->redirect[i + 1] || \
			ft_strchr("><", token->redirect[i + 1][0]))
				return (redir_err(all, "", ERR_SYN, 258));
			if (!ft_strcmp(token->redirect[i], ">"))
				fd = open(token->redirect[i + 1], O_WRONLY | O_TRUNC);
			else
				fd = open(token->redirect[i + 1], O_WRONLY | O_APPEND);
			if (fd < 0)
				return (redir_err(all, token->redirect[i + 1], ERR_NO_F_D, 1));
			all->fds[1] = fd;
			dup2(all->fds[1], 1);
			*r_redir = 1;
			close(fd);
			i++;
		}
		else if (!ft_strcmp(token->redirect[i], "<"))
		{
			i++;
			if (!token->redirect[i] || ft_strchr("><", token->redirect[i][0]))
				return (redir_err(all, "", ERR_SYN, 258));
			fd = open(token->redirect[i], O_RDONLY);
			if (fd < 0)
				return (redir_err(all, token->redirect[i], ERR_NO_F_D, 1));
			if (all->pre_pipe == 0)
			{
				all->fds[0] = fd;
				dup2(all->fds[0], 0);
			}
			close(fd);
		}
		i++;
	}
	return (0);
}

void		ft_eof(void)
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

static void	launch_builtins(t_all *all, t_token *token, int *ret)
{
	if (token->type_func == TYPE_CD)
		all->status = shell_cd(token, all->env, all);
	else if (token->type_func == TYPE_PWD)
		all->status = shell_pwd(all);
	else if (token->type_func == TYPE_ECHO)
		all->status = shell_echo(token);
	else if (token->type_func == TYPE_EXIT)
		*ret = shell_exit(all);
	else if (token->type_func == TYPE_EXPORT)
		all->status = shell_export(token, all);
	else if (token->type_func == TYPE_ENV)
		all->status = shell_env(all->env);
	else if (token->type_func == TYPE_UNSET)
		all->status = shell_unset(token, all->env);
}

int			execute(t_all *all)
{
	int			ret;
	t_token		*token;
	int			r_redir;
	int			*tmp;

	token = all->tok;
	ret = 1;
	r_redir = 0;
	tmp = NULL;
	if (token->type_func == -1)
		return (ret);
	if (token->fd_red)
		if (fd_redir(token, &tmp) != 0)
			return (1);
	if (token->redirect)
	{
		if (check_redir(all, &r_redir) == -1)
		{
			if (token->pipe)
			{
				ft_eof();
				all->pre_pipe = 1;
			}
			return (1);
		}
	}
	if (token->pipe && r_redir == 0)
		pipe(all->fds);
	if (token->type_func >= TYPE_CD && token->type_func <= TYPE_UNSET)
	{
		if (token->pipe)
			dup2(all->fds[1], 1);
		launch_builtins(all, token, &ret);
		if (ret && token->pipe == 1)
		{
			dup2(all->temp_1, 1);
			if (r_redir != 0)
				ft_eof();
			else
				dup2(all->fds[0], 0);
			if (all->fds[1] >= 3)
				close(all->fds[1]);
			if (all->fds[0] >= 3)
				close(all->fds[0]);
			all->pre_pipe = 1;
		}
		if (ret && !token->pipe)
		{
			dup2(all->temp_0, 0);
			all->pre_pipe = 0;
		}
	}
	else if (token->type_func == TYPE_BIN)
		launch(all, r_redir);
	if (ret && token->redirect && !token->pipe)
	{
		dup2(all->temp_1, 1);
		dup2(all->temp_0, 0);
		if (all->fds[1] >= 3)
			close(all->fds[1]);
		if (all->fds[0] >= 3)
			close(all->fds[0]);
	}
	if (all->tok && token->fd_red)
		clear_fd_redir(token, &tmp);
	return (ret);
}
