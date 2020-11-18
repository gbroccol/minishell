/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:47:27 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/18 16:09:41 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	redir_err(t_all *all, char *exec, char *error, int status)
{
	all->status = status;
	dup2(all->temp_1, 1);
	dup2(all->temp_0, 0);
	close_fd(all);
	return (print_error(exec, "", error, -1));
}

static int	check_r_redir(t_all *all, t_token *token, int *r_red, int i)
{
	int	fd;

	fd = 0;
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
	*r_red = 1;
	close(fd);
	return (0);
}

static int	check_l_redir(t_all *all, t_token *token, int i)
{
	int	fd;

	fd = 0;
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
	return (0);
}

static int	check_redir(t_all *all, int *r_red)
{
	t_token		*token;
	int			i;

	i = 0;
	token = all->tok;
	while (token->redirect[i] != NULL)
	{
		if (!ft_strcmp(token->redirect[i], ">") || \
		!ft_strcmp(token->redirect[i], ">>"))
		{
			if (check_r_redir(all, token, r_red, i) != 0)
				return (-1);
			i++;
		}
		else if (!ft_strcmp(token->redirect[i], "<"))
		{
			i++;
			if (check_l_redir(all, token, i) != 0)
				return (-1);
		}
		i++;
	}
	return (0);
}

int			check_all_redirs(t_token *tok, int **tmp, t_all *all, int *r_red)
{
	if (tok->fd_red)
		if (fd_redir(tok, tmp) != 0)
			return (1);
	if (tok->redirect)
	{
		if (check_redir(all, r_red) == -1)
		{
			if (tok->pipe)
			{
				ft_eof();
				all->pre_pipe = 1;
			}
			return (1);
		}
	}
	return (0);
}
