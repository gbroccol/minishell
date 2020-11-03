/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:11:35 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/03 20:56:55 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/param.h> // MAXPATHLEN
#include <errno.h> // errno
#include <string.h> //strerror

//Добавить передачу кодов выхода из встроенных команд в all->status

int lsh_cd(t_token *tokens, char **env)
{
	//Добавить замену PWD и OLDPWD
	if (!tokens->arg)
	{
		if(!(tokens->arg = search_env(env, "HOME=")))
			return (0);
	}
	else if (!ft_strcmp(tokens->arg, "-"))
	{
		if(!(tokens->arg = search_env(env, "OLDPWD=")))
			return (0);
		write (1, tokens->arg, ft_strlen(tokens->arg));
		write(1, "\n", 1);
	}
	if (ft_strlen(tokens->arg) == 0)
		return (1);
    if (chdir(tokens->arg) != 0)
	{
		write(2, ">: ", 3);
//		strerror(errno) //macos
		write(2, strerror(errno), ft_strlen(strerror(errno))); //wsl
		write(2, "\n", 1); //wsl
	}
	if (ft_strlen(tokens->arg) != 0)
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

int lsh_echo(t_token *tokens)
{
	int fd;

	fd = 1;
	if (tokens->redir != NULL && !tokens->file)
	{
		if (tokens->arg)
			free(tokens->arg);
		write(2, ">: syntax error near unexpected token `newline'\n", 48);
		return (1);
	}
	if (tokens->redir != NULL)
	{
		if ((ft_strncmp(tokens->redir, ">>", 3)) == 0)
			fd = open(tokens->file, O_RDWR | O_CREAT | O_APPEND, 0666);
		if ((ft_strncmp(tokens->redir, ">", 2)) == 0)
			fd = open(tokens->file, O_RDWR | O_CREAT, 0666);
	}		
	if (fd < 0)
	{
		write(2, ">: ", 3);
//		strerror(errno) //macos
		write(2, strerror(errno), ft_strlen(strerror(errno))); //wsl
		write(2, "\n", 1); //wsl
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

char	**new_env(t_all *all, char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	while (all->env[i] != NULL)
	{
		if (ft_strlen(all->env[i]) == 0)
		{
			if (!(all->env[i] = ft_strdup(str)))
				return (NULL);
			i = 0;
			break ;
		}
		i++;
	}
	if (i != 0)
	{
		if (!(tmp = save_env(all->env, 1)))
			return (NULL);
		ft_free_array(all->env);
		all->env = tmp;
		i = 0;
		while (all->env[i] != NULL)
			i++;
		if (!(all->env[i] = ft_strdup(str)))
			return (NULL);
	}
	return (all->env);
}

int	lsh_export(t_token *token, t_all *all)
{
	int 		size;
	int			i;

	size = 0;
	i = 0;
	if (!token->arg)
	{
		while (all->env[i] != NULL)
		{
			size = 0;
			while (all->env[i][size] != '=' && all->env[i][size] != '\0')
				size++;
			size++;
			if (size > 1)
			{
				write(1, "declare -x ", 11);
				write(1, all->env[i], size);
				write(1, "\"", 1);
				write(1, all->env[i] + size, ft_strlen(all->env[i]) - size);
				write(1, "\"\n", 2);
			}
			i++;
		}
	}
	else
	{
		while (token->arg[size] != '=')
			size++;
		size++;
		while (all->env[i] != NULL)
		{
			if (!ft_strncmp(token->arg, all->env[i], size))
			{
				free(all->env[i]);
				if (!(all->env[i] = ft_strdup(token->arg)))
					return (0);
				i = 0;
				break ;
			}
			i++;
		}
		if (i != 0)
		{
			if (!(new_env(all, token->arg)))
			{
				free(token->arg);
				return (0);
			}
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

int	lsh_unset(t_token *token, char **env)
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

int execute(t_all *all)
{
	int			ret;
	t_token		*tokens;

	ret = 1;
	tokens = all->tok;
	if (tokens->type_func == -1) 
    	return (ret);
	// printf("%s\n", tokens->bin_tok[0]);
	// while (tokens)
	// {
		if (tokens->type_func == TYPE_CD)
			ret = lsh_cd(tokens, all->env);
		else if (tokens->type_func == TYPE_PWD)
			ret = lsh_pwd();
		else if (tokens->type_func == TYPE_ECHO)
			ret = lsh_echo(tokens);
		else if (tokens->type_func == TYPE_EXIT)
			ret = lsh_exit();
		else if (tokens->type_func == TYPE_EXPORT)
			ret = lsh_export(tokens, all);
		else if (tokens->type_func == TYPE_ENV)
			ret = lsh_env(all->env);
		else if (tokens->type_func == TYPE_UNSET)
			ret = lsh_unset(tokens, all->env);
		else if (tokens->type_func == TYPE_BIN)
			ret = launch(all);
		// tokens = tokens->next;
	// }
	return (ret);
}
