/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cd_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:11:35 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/15 16:54:04 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	define_path(t_token *tokens, char **env)
{
	if (!tokens->args[1])
	{
		ft_free_array(tokens->args);
		if (!(tokens->args = (char **)malloc(sizeof(char *) * 3)))
			return (1);
		tokens->args[0] = ft_strdup("cd");
		if (!(tokens->args[1] = search_env(env, "HOME=")))
			return (1);
		tokens->args[2] = NULL;
	}
	else if (!ft_strcmp(tokens->args[1], "-"))
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

	if (define_path(tokens, env) == 1)
		return (1);
	if (ft_strlen(tokens->args[1]) == 0)
		return (0);
	if (!(tmp.args = (char **)malloc(sizeof(char *) * 3)))
		return (1);
	tmp.args[0] = ft_strdup("export");
	tmp.args[2] = NULL;
	tmp.args[1] = ft_strjoin("OLDPWD=", getcwd(dir, MAXPATHLEN));
	if (chdir(tokens->args[1]) != 0)
		print_error(all->tok->cmd, tokens->args[1], strerror(errno), 0);
	shell_export(&tmp, all);
	free(tmp.args[1]);
	tmp.args[1] = NULL;
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
