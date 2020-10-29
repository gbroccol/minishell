/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:11:35 by pvivian           #+#    #+#             */
/*   Updated: 2020/10/29 14:57:06 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/param.h> // MAXPATHLEN
#include <errno.h> // errno
#include <string.h> //strerror

int lsh_cd(t_tokens *tokens, char **env)
{
	int	i;

	i = 0;
	if (!tokens->arg)
	{
		while (env[i] != NULL)
		{
			if (!ft_strncmp(env[i], "HOME=", 5))
				if (!(tokens->arg = ft_strdup(env[i] + 5)))
					return (0);
			i++;
		}
	}
	printf("%s\n", tokens->arg);
    if (chdir(tokens->arg) != 0)
	{
//		strerror(errno) //macos
		write(1, strerror(errno), ft_strlen(strerror(errno))); //wsl
		write(1, "\n", 1); //wsl
	}
	free(tokens->arg);
	return (1);
}


int lsh_pwd(void)
{
	char dir[MAXPATHLEN];

	getcwd(dir, MAXPATHLEN);
	write(1, dir, ft_strlen(dir));
	write(1, "\n", 1);
	return (1);
}

int lsh_echo(t_tokens *tokens)
{
	int fd;

	fd = 1;
	if (tokens->redir != NULL)
	{
		if ((ft_strncmp(tokens->redir, ">>", 3)) == 0)
			fd = open(tokens->file, O_RDWR | O_CREAT | O_APPEND, 0666);
		if ((ft_strncmp(tokens->redir, ">", 2)) == 0)
			fd = open(tokens->file, O_RDWR | O_CREAT, 0666);
		// обработать ошибку, если редирект есть но файл не подали
	}		
	if (fd < 0)
	{
		strerror(errno);
		return (1);
	}
	if (tokens->arg)
	{
		write(fd, tokens->arg, ft_strlen(tokens->arg));
		free(tokens->arg);
	}
	if (tokens->flag_n == 0)
		write(fd, "\n", 1);
	if (tokens->file)
		free(tokens->file);
	if (fd != 1)
		close(fd);
	return(1);
}

int lsh_exit()
{
  return (0);
}

int	lsh_export(t_tokens *token, char **env)
{
	int size;
	int	i;

	size = 0;
	i = 0;
	if (!token->arg)
	{
		while (env[i] != NULL)
		{
			size = 0;
			while (env[i][size] != '=' && env[i][size] != '\0')
				size++;
			size++;
			if (size > 1)
			{
				write(1, "declare -x ", 11);
				write(1, env[i], size);
				write(1, "\"", 1);
				write(1, env[i] + size, ft_strlen(env[i]) - size);
				write(1, "\"", 1);
				write(1, "\n", 1);
			}
			i++;
		}
	}
	else
	{
		while (token->arg[size] != '=')
			size++;
		size++;
		while (env[i] != NULL)
		{
			if (!ft_strncmp(token->arg, env[i], size))
			{
				free(env[i]);
				if (!(env[i] = ft_strdup(token->arg)))
					return (0);
				break ;
			}
			i++;
		}
		free(token->arg);
	}
	return (1);
}

int	lsh_env(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		write(1, env[i], ft_strlen(env[i]));
		if (ft_strlen(env[i]) > 0)
			write(1, "\n", 1);
		i++;
	}
	return (1);
}

int	lsh_unset(t_tokens *token, char **env)
{
	int	i;

	i = 0;
	if (token->arg)
	{
		while (env[i] != NULL)
		{
			if (ft_strcmp(env[i], token->arg) == 61)
			{
				free(env[i]);
				env[i] = "";
				break ;
			}
			i++;
		}
		free(token->arg);
	}
	return (1);
}

int execute(t_tokens *tokens, char **env)
{
	int ret;

	ret = 1;
	if (tokens->type_func == -1) 
    	return (ret);
	while (tokens)
	{
		if (tokens->type_func == TYPE_CD)
			ret = lsh_cd(tokens, env);
		else if (tokens->type_func == TYPE_PWD)
			ret = lsh_pwd();
		else if (tokens->type_func == TYPE_ECHO)
			ret = lsh_echo(tokens);
		else if (tokens->type_func == TYPE_EXIT)
			ret = lsh_exit();
		else if (tokens->type_func == TYPE_EXPORT)
			ret = lsh_export(tokens, env);
		else if (tokens->type_func == TYPE_ENV)
			ret = lsh_env(env);
		else if (tokens->type_func == TYPE_UNSET)
			ret = lsh_unset(tokens, env);
		tokens = tokens->next;
	}
	return (ret);
//  return lsh_launch(args);
}
