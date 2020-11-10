/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:11:35 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/08 18:01:00 by pvivian          ###   ########.fr       */
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


static void	echo_n(t_token *token)
{
	int		i;
	int		j;

	i = 1;
	while (token->args[i] != NULL)
	{
		j = 0;
		if (token->args[i][j] == '-')
		{
			j++;
			while (token->args[i][j] == 'n')
				j++;
			if (token->args[i][j] == '\0')
			{
				token->flag_n = 1;
				token->args = ft_del_str_from_ar(token->args, i);
				i--;
			}
			else
				return ;
		}
		else
			return ;
		i++;
	}
}

int		lsh_echo(t_token *tokens, t_all *all)
{
	int i;

	echo_n(tokens);
	if (tokens->redir != NULL && !tokens->file)
	{
//		if (tokens->arg)
//			free(tokens->arg);
		write(2, ">: syntax error near unexpected token `newline'\n", 48);
		return (1);
	}
	i = 1;
	if (tokens->args[i])
	{
		while (tokens->args[i] != NULL)
		{
			write(1, tokens->args[i], ft_strlen(tokens->args[i]));
			if (tokens->args[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
		// free(tokens->arg);
	}
	if (tokens->flag_n == 0)
		write(1, "\n", 1);
//	if (tokens->file)
//		free(tokens->file);
	all->status = 0;
	return (1);
}

int		lsh_exit(t_all *all)
{
	int	i;

	i = 0;
	if (all->pre_pipe)
		return (1);
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

int		check_new_env(t_all *all, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=' || ft_isdigit(str[i]))
	{
		write(1, "bash: export: `", 15);
		write(1, str, ft_strlen(str));
		write(1, "': not a valid identifier\n", 26);
		all->status = 1;
		return (1);
	}
	return (0);
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
				if (check_new_env(all, token->args[j]) == 0)
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

int		print_error(void)
{
	write(2, ">: ", 3);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	return (1);
}

int		check_redir(t_all *all, int *r_redir)
{
	t_token		*token;
	int			i;
	int 		fd;
	
	i = 0;
	token = all->tok;
	fd = 0;
	while (token->redirect[i] != NULL)
	{
		if (!ft_strcmp(token->redirect[i], ">") || !ft_strcmp(token->redirect[i], ">>"))
		{
			if (!ft_strcmp(token->redirect[i], ">"))
				fd = open(token->redirect[i + 1], O_RDWR | O_CREAT, 0666);
			else
				fd = open(token->redirect[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
			if (fd < 0)
				return (print_error());
			all->fds[1] = fd;
			dup2(all->fds[1], 1);
			*r_redir = 1;
			i++;
		}
		else if (!ft_strcmp(token->redirect[i], "<"))
		{
			i++;
			fd = open(token->redirect[i], O_RDWR);
			if (fd < 0)
				return (print_error());
			all->fds[0] = fd;
			dup2(all->fds[0], 0);
		}
		i++;
	}
	return (0);
}

int		execute(t_all *all)
{
	int			ret;
	t_token		*token;
	int			r_redir;

	ret = 1;
	r_redir = 0;
	token = all->tok;
	if (token->type_func == -1)
		return (ret);
	if (token->redirect)
		check_redir(all, &r_redir);
	if (token->pipe && r_redir == 0)
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
			all->pre_pipe = 1;
		}
		if (!token->pipe)
		{
			dup2(all->temp_0, 0);
			all->pre_pipe = 0;
		}
	}
	else if (token->type_func == TYPE_BIN)
		ret = launch(all);
	if (token->redirect)
	{
		dup2(all->temp_1, 1);
		dup2(all->temp_0, 0);
		close(all->fds[1]);
		close(all->fds[0]);
	}
	return (ret);
}
