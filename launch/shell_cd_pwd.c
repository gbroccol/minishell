/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cd_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:11:35 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/17 15:23:02 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	define_path(t_token *tokens, char **env, int *home)
{
	if (!tokens->args[1])
	{
		*home = 1;
		ft_free_array(tokens->args);
		if (!(tokens->args = (char **)malloc(sizeof(char *) * 3)))
			return (1);
		tokens->args[0] = ft_strdup("cd");
		if (!(tokens->args[1] = search_env(env, "HOME=")))
			return (1);
		tokens->args[2] = NULL;
	}
	else if (!ft_strncmp(tokens->args[1], "-", 1))
	{
		free(tokens->args[1]);
		tokens->args[1] = NULL;
		if (!(tokens->args[1] = search_env(env, "OLDPWD=")))
			return (1);
		write(1, tokens->args[1], ft_strlen(tokens->args[1]));
		if (ft_strlen(tokens->args[1]) != 0)
			write(1, "\n", 1);
	}
	return (0);
}

int			shell_cd(t_token *tokens, char **env, t_all *all)
{
	t_token tmp;
	char	dir[MAXPATHLEN];
	int		home;

	home = 0;
	if (define_path(tokens, env, &home) == 1)
		return (1);
	if (ft_strlen(tokens->args[1]) == 0)
		return (0);
	if (!(tmp.args = (char **)malloc(sizeof(char *) * 3)))
		return (1);
	tmp.args[0] = ft_strdup("export");
	tmp.args[2] = NULL;
	tmp.args[1] = ft_strjoin("OLDPWD=", search_env(env, "PWD="));
	if (chdir(tokens->args[1]) != 0)
	{
		print_error(all->tok->cmd, tokens->args[1], strerror(errno), 0);
		return (1);
	}
	shell_export(&tmp, all);
	free(tmp.args[1]);
	tmp.args[1] = NULL;
	if (home == 0)
		tmp.args[1] = ft_strjoin("PWD=", getcwd(dir, MAXPATHLEN));
	else
	{
		tmp.args[1] = ft_strjoin("PWD=", tokens->args[1]);
	}
	shell_export(&tmp, all);
	ft_free_array(tmp.args);
	return (0);
}

char	*ft_tolower_str(char *str)
{
	int i;
	
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int			shell_pwd(t_all *all)
{
	char	dir[MAXPATHLEN];
	char	*home;
	char	*path;
	char	*pwd;

	if (!(home = ft_tolower_str(ft_strdup(all->home))))
		return (1);
	if (getcwd(dir, MAXPATHLEN) == NULL)
		return (1);
	if (!(path = ft_tolower_str(ft_strdup(dir))))
		return (1);
	if (!(pwd = search_env(all->env, "PWD=")))
		return (1);
	if (!ft_strcmp(home, path))
		write(1, all->home, ft_strlen(all->home));
	else	
		write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (0);
}
