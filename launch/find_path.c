/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:35:26 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/13 18:25:53 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*search_env(char **env, char *to_find)
{
	int		i;
	int		size;
	char	*value;

	i = 0;
	size = ft_strlen(to_find);
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], to_find, size))
		{
			if (!(value = ft_strdup(env[i] + size)))
				return (NULL);
			i = 0;
			break ;
		}
		i++;
	}
	if (i != 0)
	{
		write(2, to_find, size - 1);
		write(2, " not set\n", 9);
		return (ft_strdup(""));
	}
	return (value);
}

int			check_pwd(char **env, char **executable)
{
	char			*pwd;
	DIR				*dir;
	struct dirent	*subdir;
	int				err_no;

	pwd = search_env(env, "PWD=");
	dir = opendir(pwd);
	errno = 0;
	if (!dir)
		return (1);
	while ((subdir = readdir(dir)) != NULL)
	{
		if (!ft_strcmp(subdir->d_name, *executable))
		{
			closedir(dir);
			free(pwd);
			return (0);
		}
	}
	err_no = errno;
	closedir(dir);
	free(pwd);
	if (err_no != 0)
		return (print_error(*executable, strerror(err_no), 0));
	return (1);
}

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
		print_error(executable, strerror(err_no), 0);
		return (NULL);
	}
	return (prefix);
}

char		*find_prefix(char **dirs, char *executable, t_all *all)
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
	if (prefix == NULL)
	{
		print_error(all->tok->cmd, "command not found", 0);
		all->status = 127;
	}
	return (prefix);
}

int			find_path(char **env, char **executable, t_all *all)
{
	char	*path;
	char	**dirs;
	char	**tmp;
	char	*str;
	char	*prefix;

	str = NULL;
	if (!(path = search_env(env, "PATH=")))
		return (0);
	if (ft_strlen(path) == 0)
		return (1);
	tmp = ft_split(path, '=');
	dirs = ft_split(tmp[0], ':');
	if (!(prefix = find_prefix(dirs, executable[0], all)))
	{
		ft_free_array(tmp);
		free(path);
		free(prefix);
		ft_free_array(dirs);
		return (1);
	}
	ft_free_array(tmp);
	free(path);
	str = executable[0];
	path = ft_strjoin(prefix, executable[0]);
	free(str);
	executable[0] = path;
	free(prefix);
	ft_free_array(dirs);
	return (2);
}
