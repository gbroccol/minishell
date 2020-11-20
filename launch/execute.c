/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:11:35 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/20 11:50:56 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	launch_builtins(t_all *all, t_token *token, int *ret)
{
	if (token->type_func == TYPE_CD)
		all->status = shell_cd(token, all->env, all, ret);
	else if (token->type_func == TYPE_PWD)
		all->status = shell_pwd(all, ret);
	else if (token->type_func == TYPE_ECHO)
		all->status = shell_echo(token);
	else if (token->type_func == TYPE_EXIT)
		*ret = shell_exit(all);
	else if (token->type_func == TYPE_EXPORT)
		all->status = shell_export(token, all, ret);
	else if (token->type_func == TYPE_ENV)
		all->status = shell_env(all->env);
	else if (token->type_func == TYPE_UNSET)
		all->status = shell_unset(token, all, ret);
}

static void	execute_command(t_all *all, t_token *token, int *ret, int r_redir)
{
	if (token->pipe && r_redir == 0)
		pipe(all->fds);
	if (token->type_func >= TYPE_CD && token->type_func <= TYPE_UNSET)
	{
		if (token->pipe)
			dup2(all->fds[1], 1);
		launch_builtins(all, token, ret);
		if (*ret && token->pipe == 1)
		{
			dup2(all->temp_1, 1);
			if (r_redir != 0)
				ft_eof();
			else
				dup2(all->fds[0], 0);
			close_fd(all);
			all->pre_pipe = 1;
		}
		if (*ret && !token->pipe)
		{
			dup2(all->temp_0, 0);
			all->pre_pipe = 0;
		}
	}
	else if (token->type_func == TYPE_BIN)
		launch(all, r_redir);
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
	if (token->type_func == -1 && !token->redirect)
		return (ret);
	if (check_all_redirs(token, &tmp, all, &r_redir) != 0)
		return (ret);
	execute_command(all, token, &ret, r_redir);
	if (ret && token->redirect && !token->pipe)
	{
		dup2(all->temp_1, 1);
		dup2(all->temp_0, 0);
		close_fd(all);
	}
	if (all->tok && token->fd_red)
		clear_fd_redir(token, &tmp);
	return (ret);
}
