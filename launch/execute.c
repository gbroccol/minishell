/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:11:35 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/12 19:40:48 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				print_error(char *to_print, int ret)
{
	write(2, "bash: ", 6);
	write(2, to_print, ft_strlen(to_print));
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
			if (!ft_strcmp(token->redirect[i], ">"))
				fd = open(token->redirect[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
			else
				fd = open(token->redirect[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (fd < 0)
				return (print_error(strerror(errno), 1));
			all->fds[1] = fd;
			dup2(all->fds[1], 1);
			*r_redir = 1;
			i++;
		}
		else if (!ft_strcmp(token->redirect[i], "<"))
		{
			i++;
			fd = open(token->redirect[i], O_RDONLY);
			if (fd < 0)
				return (print_error(strerror(errno), 1));
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

	ret = 1;
	r_redir = 0;
	token = all->tok;
	if (token->type_func == -1)
		return (ret);
	if (token->redirect)
		check_redir(all, &r_redir);
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
		if (token->pipe)
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
		if (!token->pipe)
		{
			dup2(all->temp_0, 0);
			all->pre_pipe = 0;
		}
	}
	else if (token->type_func == TYPE_BIN)
		launch(all, r_redir);
	if (token->redirect && !token->pipe)
	{
		dup2(all->temp_1, 1);
		dup2(all->temp_0, 0);
		close(all->fds[1]);
		close(all->fds[0]);
	}
	return (ret);
}
