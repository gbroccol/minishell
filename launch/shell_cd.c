/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:11:35 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/18 19:16:06 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	define_path(t_token *tok, char **env, int *home, t_all *all)
{
	if (!tok->args[1])
	{
		*home = 1;
		ft_free_array(tok->args);
		if (!(tok->args = (char **)malloc(sizeof(char *) * 3)))
			return (1);
		tok->args[0] = ft_strdup("cd");
		if (!(tok->args[1] = search_env(env, "HOME=", all)))
			return (1);
		tok->args[2] = NULL;
	}
	else if (!ft_strncmp(tok->args[1], "-", 1))
	{
		free(tok->args[1]);
		tok->args[1] = NULL;
		if (!(tok->args[1] = search_env(env, "OLDPWD=", all)))
			return (1);
		write(1, tok->args[1], ft_strlen(tok->args[1]));
		if (ft_strlen(tok->args[1]) != 0)
			write(1, "\n", 1);
	}
	return (0);
}

static int	ft_free(char *pwd, char **tmp, int *ret)
{
	if (pwd)
		free(pwd);
	if (tmp)
		ft_free_array(tmp);
	write(2, "bash: malloc error\n", 19);
	*ret = 0;
	return (1);
}

static int	change_dir(t_token *tmp, t_all *all, int *ret, int home)
{
	char	dir[MAXPATHLEN];
	t_token *tok;

	tok = all->tok;
	if (chdir(tok->args[1]) != 0)
	{
		ft_free_array(tmp->args);
		return (print_error(all->tok->cmd, tok->args[1], strerror(errno), 1));
	}
	shell_export(tmp, all, ret);
	free(tmp->args[1]);
	tmp->args[1] = NULL;
	if (home == 0)
	{
		if (!(tmp->args[1] = ft_strjoin("PWD=", getcwd(dir, MAXPATHLEN))))
			return (ft_free(NULL, tmp->args, ret));
	}
	else
	{
		if (!(tmp->args[1] = ft_strjoin("PWD=", tok->args[1])))
			return (ft_free(NULL, tmp->args, ret));
	}
	shell_export(tmp, all, ret);
	ft_free_array(tmp->args);
	return (0);
}

int			shell_cd(t_token *tok, char **env, t_all *all, int *ret)
{
	t_token tmp;
	int		home;
	char	*pwd;

	home = 0;
	if (define_path(tok, env, &home, all) == 1)
		return (1);
	if (ft_strlen(tok->args[1]) == 0)
		return (0);
	if (!(pwd = search_env(env, "PWD=", all)))
		return (1);
	if (!(tmp.args = (char **)malloc(sizeof(char *) * 3)))
		return (ft_free(pwd, tmp.args, ret));
	bzero_array(tmp.args, 3);
	if (!(tmp.args[0] = ft_strdup("export")))
		return (ft_free(pwd, tmp.args, ret));
	if (!(tmp.args[1] = ft_strjoin("OLDPWD=", pwd)))
		return (ft_free(pwd, tmp.args, ret));
	free(pwd);
	return (change_dir(&tmp, all, ret, home));
}
