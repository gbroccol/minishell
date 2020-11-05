/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:37:39 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/05 18:43:34 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_env(char **env, char *to_find)
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
		return (""); // difficult to free
	}
	return (value);
}

int		check_dir(char **env, char **executable)
{
	char			*pwd;
	DIR				*dir;
	struct dirent	*subdir;

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
	if (errno != 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		return (0);
	}
	closedir(dir);
	free(pwd);
	return (1);
}

char	*find_prefix(char **dirs, char *executable)
{
	char			*prefix;
	DIR				*dir;
	struct dirent	*subdir;
	int				i;

	prefix = NULL;
	i = 0;
	while (dirs[i] != NULL)
	{
		dir = opendir(dirs[i]);
		errno = 0;
		if (dir)
		{
			while ((subdir = readdir(dir)) != NULL)
			{
				if (!ft_strcmp(subdir->d_name, executable))
				{
					prefix = ft_strjoin(dirs[i], "/");
					break ;
				}
			}
			if (errno != 0)
			{
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				closedir(dir);
				return (NULL);
			}
			closedir(dir);
		}
		if (prefix != NULL)
			break ;
		i++;
	}
	if (prefix == NULL)
	{
		write(2, executable, ft_strlen(executable));
		write(2, ": command not found\n", 20);
		return (NULL);
	}
	return (prefix);
}

int		find_path(char **env, char **executable)
{
	char	*path;
	char	**dirs;
	char	**tmp;
	char	*prefix;

	if (!(path = search_env(env, "PATH=")))
		return (0);
	if (ft_strlen(path) == 0)
		return (1);
	tmp = ft_split(path, '=');
	dirs = ft_split(tmp[0], ':');
	if (!(prefix = find_prefix(dirs, executable[0])))
		return (1);
	ft_free_array(tmp);
	free(path);
	// *tmp = executable[0];
	path = ft_strjoin(prefix, executable[0]);
	executable[0] = path;
	// free(*tmp);
	free(prefix);
	ft_free_array(dirs);
	return (2);
}

int		launch(t_all *all)
{
	pid_t		pid;
	int			status;
	int			ret;
	t_token		*tok;

	tok = all->tok;
	if (tok->args[0][0] != '/' && tok->args[0][0] != '.')
	{
		if ((ret = check_dir(all->env, tok->args)) != 0)
		{
			if (!(ret = find_path(all->env, tok->args)))
				return (0);
			else if (ret == 1)
				return (1);
		}
	}
	pid = fork();
	if (pid == 0)
	{
		if (tok->pipe)
		{
			dup2(all->fds[1], 1);
			close(all->fds[0]);
		}
		if (execve(tok->args[0], tok->args, all->env) == -1)
		{
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, "\n", 1);
			exit(EXIT_FAILURE);
		}
		close(all->fds[1]);
	}
	else if (pid < 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		close(all->fds[0]);
		close(all->fds[1]);
	}
	else
	{
		if (tok->pipe)
			dup2(all->fds[0], 0);
		if (all->fds[1] != 1)
			close(all->fds[1]);
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
		if (WEXITSTATUS(status) != 1)
			all->status = WEXITSTATUS(status);
		else
			all->status = 127;
		close(all->fds[0]);
		if (!tok->pipe)
			dup2(all->temp_0, 0);
	}
	return (1);
}
