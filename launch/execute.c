/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:11:35 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/16 16:53:57 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				print_error(char *exec, char *exec2, char *err_to_print, int ret)
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

static int		check_redir(t_all *all, int *r_redir)
{
	t_token		*token;
	int			i;
	int			fd;

	i = 0;
	token = all->tok;
	fd = 0;
	while (token->redirect[i] != NULL)
	{
		if (!ft_strcmp(token->redirect[i], ">") || !ft_strcmp(token->redirect[i], ">>"))
		{
			if (!token->redirect[i + 1] || ft_strchr("><", token->redirect[i + 1][0]))
			{
				all->status = 258;
				dup2(all->temp_1, 1);
				dup2(all->temp_0, 0);
				close(all->fds[1]);
				close(all->fds[0]);
				return (print_error("", "", "syntax error near unexpected token", -1));
			}
			if (!ft_strcmp(token->redirect[i], ">"))
				fd = open(token->redirect[i + 1], O_WRONLY | O_TRUNC);
			else
				fd = open(token->redirect[i + 1], O_WRONLY | O_APPEND);
			if (fd < 0)
			{
				all->status = 1;
				dup2(all->temp_1, 1);
				dup2(all->temp_0, 0);
				close(all->fds[1]);
				close(all->fds[0]);
				return (print_error(token->redirect[i + 1], "", "No such file or directory", -1));
			}
			// close(all->fds[1]);
			all->fds[1] = fd;
			dup2(all->fds[1], 1);
			*r_redir = 1;
			i++;
		}
		else if (!ft_strcmp(token->redirect[i], "<"))
		{
			i++;
			if (!token->redirect[i] || ft_strchr("><", token->redirect[i][0]))
			{
				all->status = 258;
				dup2(all->temp_1, 1);
				dup2(all->temp_0, 0);
				close(all->fds[1]);
				close(all->fds[0]);
				return (print_error("", "", "syntax error near unexpected token", -1));
			}
			fd = open(token->redirect[i], O_RDONLY);
			if (fd < 0)
			{
				all->status = 1;
				dup2(all->temp_1, 1);
				dup2(all->temp_0, 0);
				close(all->fds[1]);
				close(all->fds[0]);
				return (print_error(token->redirect[i], "", "No such file or directory", -1));
			}
			// close(all->fds[0]);
			all->fds[0] = fd;
			dup2(all->fds[0], 0);
		}
		i++;
	}
	return (0);
}

void	ft_eof(void)
{
	int fd[2];
	
	pipe(fd);
	write(fd[1], "", 0);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
}

int				execute(t_all *all)
{
	int			ret;
	t_token		*token;
	int			r_redir;
	int			*tmp;
	int i = 0;
	int j = 0;
	int size = 0;
	
	token = all->tok;
	ret = 1;
	r_redir = 0;
	if (token->type_func == -1)
		return (ret);
	if (token->fd_red)
	{
		while (token->fd_red[size] != NULL)
			size++;
		size = size / 3;
		if (!(tmp = (int *)malloc(sizeof(int) * size)))
			return (ret);
		i = 0;
		while (token->fd_red[i] != NULL)
		{
			tmp[j] = dup(ft_atoi(token->fd_red[i]));
			dup2(ft_atoi(token->fd_red[i + 2]), ft_atoi(token->fd_red[i]));
			j++;
			i += 3;
		}
	}
	if (token->redirect)
		if (check_redir(all, &r_redir) == -1)
			return (ret);
	if (token->pipe && r_redir == 0)
		pipe(all->fds);
	if (token->type_func >= TYPE_CD && token->type_func <= TYPE_UNSET)
	{
		if (token->pipe)
			dup2(all->fds[1], 1);
		if (token->type_func == TYPE_CD)
			all->status = shell_cd(token, all->env, all);
		else if (token->type_func == TYPE_PWD)
			all->status = shell_pwd();
		else if (token->type_func == TYPE_ECHO)
			all->status = shell_echo(token);
		else if (token->type_func == TYPE_EXIT)
			ret = shell_exit(all);
		else if (token->type_func == TYPE_EXPORT)
			all->status = shell_export(token, all);
		else if (token->type_func == TYPE_ENV)
			all->status = shell_env(all->env);
		else if (token->type_func == TYPE_UNSET)
			all->status = shell_unset(token, all->env);
		if (ret && token->pipe == 1)
		{
			dup2(all->temp_1, 1);
			if (r_redir != 0)
				ft_eof();
			else
				dup2(all->fds[0], 0);
			close(all->fds[1]);
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
	if (ret && token->redirect && !token->pipe /*&& all->pre_pipe > 0*/)
	{
		dup2(all->temp_1, 1);
		dup2(all->temp_0, 0);
		close(all->fds[1]);
		close(all->fds[0]);
	}
	if (token->fd_red)
	{
		i = 0;
		j = 0;
		while (token->fd_red[i] != NULL)
		{
			dup2(tmp[j], ft_atoi(token->fd_red[i]));
			j++;
			i += 3;
		}
		free(tmp);
	}

	return (ret);
}
