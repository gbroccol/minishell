/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cd_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:11:35 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/13 14:22:04 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	define_path(t_token *tokens, char **env)
{
	if (!tokens->args[1])
	{
		if (!(tokens->args[1] = search_env(env, "HOME=")))
			return (1);
	}
	else if (!ft_strcmp(tokens->args[1], "-"))
	{
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

	if (!(tmp.args = (char **)malloc(sizeof(char *) * 3)))
		return (1);
	if (define_path(tokens, env) == 1)
		return (1);
	if (ft_strlen(tokens->args[1]) == 0)
		return (0);
	tmp.args[0] = ft_strdup("export");
	tmp.args[2] = NULL;
	tmp.args[1] = ft_strjoin("OLDPWD=", getcwd(dir, MAXPATHLEN));
	if (chdir(tokens->args[1]) != 0)
	{
		write(2, "bash: ", 6);
		write(2, all->tok->cmd, ft_strlen(all->tok->cmd));
		write(2, ": ", 2);
		write(2, tokens->args[1], ft_strlen(tokens->args[1]));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	shell_export(&tmp, all);
	free(tmp.args[1]);
	tmp.args[1] = ft_strjoin("PWD=", getcwd(dir, MAXPATHLEN));
	shell_export(&tmp, all);
	ft_free_array(tmp.args);
	return (0);
}

int			shell_pwd(void)
{
	char dir[MAXPATHLEN];

	getcwd(dir, MAXPATHLEN);
	write(1, dir, ft_strlen(dir));
	write(1, "\n", 1);
	return (0);
}
