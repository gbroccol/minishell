/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 15:24:43 by gbroccol          #+#    #+#             */
/*   Updated: 2020/06/22 20:15:05 by anastasiya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int		mem_free(char **remember)
{
	free(*remember);
	return (-1);
}

static char		*ft_find_n(char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == '\n')
			return (str);
		str++;
	}
	return (NULL);
}

static int		get_line(char **line, char **remember)
{
	int			n_yes;
	char		*tmp;
	int			remember_len;
	int			line_len;

	tmp = NULL;
	remember_len = ft_strlen_n(*remember, '\0');
	if ((n_yes = ft_find_n(*remember) ? 1 : 0))
		line_len = ft_strlen_n(*remember, '\n');
	else
		line_len = remember_len;
	if (!(*line = ft_substr(*remember, 0, line_len)))
		return (mem_free(remember));
	if (n_yes)
	{
		if (!(tmp = ft_substr(*remember, line_len + 1,
				remember_len - line_len - 1)))
			return (mem_free(remember));
	}
	free(*remember);
	*remember = tmp;
	return (n_yes);
}

static char		*write_surplus(char **s_fd, char *buf)
{
	char		*result;

	result = NULL;
	if (!*s_fd)
		return (ft_strdup(buf));
	result = ft_strjoin(*s_fd, buf);
	free(*s_fd);
	return (result);
}

int				get_next_line(int fd, char **line)
{
	static char	*s_fd[2000];
	char		buf[BUFFER_SIZE + 1];
	int			line_len;

	line_len = 0;
	if (fd < 0 || fd > 1999 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	*line = NULL;
	if (!ft_find_n(s_fd[fd]))
		while ((line_len = read(fd, buf, BUFFER_SIZE)) >= 0)
		{
			buf[line_len] = '\0';
			s_fd[fd] = write_surplus(&s_fd[fd], buf);
			if (ft_find_n(buf) || !line_len || !s_fd[fd])
				break ;
		}
	return ((line_len < 0 || !s_fd[fd]) ? (-1) : (get_line(line, &s_fd[fd])));
}
