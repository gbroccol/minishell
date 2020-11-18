/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 15:24:43 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/18 20:12:09 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define BUFFER_SIZE 32

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
	int			rmb_len;
	int			line_len;

	tmp = NULL;
	rmb_len = ft_strlen_n(*remember, '\0');
	if ((n_yes = ft_find_n(*remember) ? 1 : 0))
		line_len = ft_strlen_n(*remember, '\n');
	else
		line_len = rmb_len;
	if (!(*line = ft_substr(*remember, 0, line_len)))
		return (mem_free(remember));
	if (n_yes && (rmb_len - line_len - 1) > 0)
	{
		if (!(tmp = ft_substr(*remember, line_len + 1, rmb_len - line_len - 1)))
			return (mem_free(remember));
	}
	else
		tmp = NULL;
	free(*remember);
	*remember = NULL;
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
	{
		while ((line_len = read(fd, buf, BUFFER_SIZE)) >= 0)
		{
			buf[line_len] = '\0';
			write(0, "  \b\b", 4);
			s_fd[fd] = write_surplus(&s_fd[fd], buf);
			if (buf[0] == '\0' && s_fd[fd][0] == '\0' && line_len == 0)
				return (2);
			if (ft_find_n(buf) || !s_fd[fd])
				break ;
		}
	}
	return ((line_len < 0 || !s_fd[fd]) ? (-1) : (get_line(line, &s_fd[fd])));
}
