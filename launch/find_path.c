/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:35:26 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/20 16:30:44 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_subdir(DIR *dir, char *executable, char *dirs)
{
	struct dirent	*subdir;
	char			*prefix;
	int				err_no;

	prefix = NULL;
	while ((subdir = readdir(dir)) != NULL)
	{
		if (!ft_strcmp(subdir->d_name, executable))
		{
			prefix = ft_strjoin(dirs, "/");
			break ;
		}
	}
	err_no = errno;
	closedir(dir);
	if (err_no != 0)
	{
		print_error(executable, "", strerror(err_no), 0);
		return (NULL);
	}
	return (prefix);
}

static char	*find_prefix(char **dirs, char *executable)
{
	char			*prefix;
	DIR				*dir;
	int				i;

	prefix = NULL;
	i = 0;
	while (dirs[i] != NULL)
	{
		dir = opendir(dirs[i]);
		errno = 0;
		if (dir)
			prefix = check_subdir(dir, executable, dirs[i]);
		if (prefix != NULL)
			break ;
		i++;
	}
	ft_free_array(dirs);
	return (prefix);
}

static int	ft_free(char *str, int res)
{
	if (str)
		free(str);
	return (res);
}

int			find_path(char **env, char **executable, t_all *all)
{
	char	*path;
	char	**dirs;
	char	**tmp;
	char	*str;
	char	*prefix;

	str = NULL;
	path = NULL;
	if (!(path = search_env(env, "PATH=", all)))
		return (0);
	if (ft_strlen(path) == 0)
		return (ft_free(path, 1));
	tmp = ft_split(path, '=');
	dirs = ft_split(tmp[0], ':');
	ft_free_array(tmp);
	free(path);
	if (!(prefix = find_prefix(dirs, executable[0])))
		return (2);
	str = executable[0];
	if (!(path = ft_strjoin(prefix, executable[0])))
		return (ft_free(prefix, 0));
	free(str);
	executable[0] = path;
	return (ft_free(prefix, 3));
}
