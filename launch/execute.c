/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:11:35 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/05 19:22:22 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		lsh_cd(t_token *tokens, char **env)
{
	if (!tokens->args[1])
	{
		if (!(tokens->args[1] = search_env(env, "HOME=")))
			return (0);
	}
	else if (!ft_strcmp(tokens->args[1], "-"))
	{
		if (!(tokens->args[1] = search_env(env, "OLDPWD=")))
			return (0);
		write(1, tokens->args[1], ft_strlen(tokens->args[1]));
		if (ft_strlen(tokens->args[1]) != 0)
			write(1, "\n", 1);
	}
	if (ft_strlen(tokens->args[1]) == 0)
		return (1);
	if (chdir(tokens->args[1]) != 0)
	{
		write(2, ">: ", 3);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
//	if (ft_strlen(tokens->args[1]) != 0)
//		free(tokens->args[1]);
	return (1);
}

int		lsh_pwd(void)
{
	char dir[MAXPATHLEN];

	getcwd(dir, MAXPATHLEN);
	write(1, dir, ft_strlen(dir));
	write(1, "\n", 1);
	return (1);
}

int		lsh_echo(t_token *tokens, t_all *all)
{
	int fd;
	int i;

	fd = 1;
	if (tokens->redir != NULL && !tokens->file)
	{
//		if (tokens->arg)
//			free(tokens->arg);
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
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		return (1);
	}
	i = 1;
	if (tokens->args[i])
	{
		while (tokens->args[i] != NULL)
		{
			write(fd, tokens->args[i], ft_strlen(tokens->args[i]));
			if (tokens->args[i + 1] != NULL)
				write(fd, " ", 1);
			i++;
		}
		// free(tokens->arg);
	}
	if (tokens->flag_n == 0)
		write(fd, "\n", 1);
//	if (tokens->file)
//		free(tokens->file);
	if (fd != 1)
		close(fd);
	all->status = 0;
	return (1);
}

int		lsh_exit(t_all *all)
{
	int	i;

	i = 0;
	if (all->tok->args[1])
	{
		while (all->tok->args[1][i] != '\0')
		{
			if (!ft_isdigit(all->tok->args[1][i]))
			{
				all->status = 255;
				return (0);
			}
			i++;
		}
		all->status = ft_atoi(all->tok->args[1]);
	}
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

int		lsh_export(t_token *token, t_all *all)
{
	int	size;
	int	i;
	int	j;

	size = 0;
	i = 0;
	j = 1;
	if (!token->args[j])
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
		while (token->args[j] != NULL)
		{
			while (token->args[j][size] != '=' && token->args[j][size] != '\0')
				size++;
			size++;
			while (all->env[i] != NULL)
			{
				if (!ft_strncmp(token->args[j], all->env[i], size))
				{
					free(all->env[i]);
					if (!(all->env[i] = ft_strdup(token->args[j])))
						return (0);
					i = 0;
					break ;
				}
				i++;
			}
			if (i != 0)
			{
				if (!(new_env(all, token->args[j])))
				{
//					free(token->args[j]);
					return (0);
				}
			}
//			free(token->args[j]);
			j++;
		}
	}
	return (1);
}

int		lsh_env(char **env)
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

int		lsh_unset(t_token *token, char **env)
{
	int	i;
	int j;

	i = 0;
	j = 1;
	if (token->args[j])
	{
		while (token->args[j] != NULL)
		{
			while (env[i] != NULL)
			{
				if (ft_strcmp(env[i], token->args[j]) == '=')
				{
					free(env[i]);
					env[i] = ft_strdup("");
					break ;
				}
				i++;
			}
//		free(token->arg);
			j++;
		}
	}
	return (1);
}

int		execute(t_all *all)
{
	int			ret;
	t_token		*token;

	ret = 1;
	token = all->tok;
	if (token->type_func == -1)
		return (ret);
	if (token->pipe)
		pipe(all->fds);
	if (token->type_func >= TYPE_CD && token->type_func <= TYPE_UNSET)
	{
		if (token->pipe)
			dup2(all->fds[1], 1);
		if (token->type_func == TYPE_CD)
			ret = lsh_cd(token, all->env);
		else if (token->type_func == TYPE_PWD)
			ret = lsh_pwd();
		else if (token->type_func == TYPE_ECHO)
			ret = lsh_echo(token, all);
		else if (token->type_func == TYPE_EXIT)
			ret = lsh_exit(all);
		else if (token->type_func == TYPE_EXPORT)
			ret = lsh_export(token, all);
		else if (token->type_func == TYPE_ENV)
			ret = lsh_env(all->env);
		else if (token->type_func == TYPE_UNSET)
			ret = lsh_unset(token, all->env);
		if (token->pipe)
		{
			dup2(all->temp_1, 1);
			dup2(all->fds[0], 0);
			close(all->fds[1]);
			close(all->fds[0]);
		}
		if (!token->pipe)
			dup2(all->temp_0, 0);
	}
	else if (token->type_func == TYPE_BIN)
		ret = launch(all);
	return (ret);
}
