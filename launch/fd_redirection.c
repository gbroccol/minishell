/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 20:30:07 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/19 16:41:17 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			fd_redir(t_token *token, int **tmp)
{
	int i;
	int j;
	int size;
	int	fd;

	i = 0;
	j = 0;
	size = 0;
	while (token->fd_red[size] != NULL)
		size++;
	size = size / 3;
	if (!(*tmp = (int *)malloc(sizeof(int) * size)))
		return (1);
	i = 0;
	while (token->fd_red[i] != NULL)
	{
		*tmp[j] = dup(ft_atoi(token->fd_red[i]));
		fd = open(token->fd_red[i + 2], O_WRONLY | O_TRUNC);
		dup2(fd, ft_atoi(token->fd_red[i]));
		close(fd);
		j++;
		i += 3;
	}
	return (0);
}

void		clear_fd_redir(t_token *token, int **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (*tmp)
	{
		while (token->fd_red[i] != NULL)
		{
			close(ft_atoi(token->fd_red[i]));
			dup2(*tmp[j], ft_atoi(token->fd_red[i]));
			j++;
			i += 3;
		}
		free(*tmp);
		*tmp = NULL;
	}
}
