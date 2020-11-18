/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:27:50 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/18 19:16:39 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_tolower_str(char *str)
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

static int	ft_free_three_str(char *s1, char *s2, char *s3, int *ret)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	*ret = 0;
	write(2, "bash: malloc error\n", 19);
	return (1);
}

int			shell_pwd(t_all *all, int *ret)
{
	char	dir[MAXPATHLEN];
	char	*home;
	char	*path;
	char	*pwd;

	home = NULL;
	path = NULL;
	pwd = NULL;
	if (!(home = ft_tolower_str(ft_strdup(all->home))))
		return (ft_free_three_str(home, path, pwd, ret));
	if (getcwd(dir, MAXPATHLEN) == NULL)
		return (ft_free_three_str(home, path, pwd, ret));
	if (!(path = ft_tolower_str(ft_strdup(dir))))
		return (ft_free_three_str(home, path, pwd, ret));
	if (!(pwd = search_env(all->env, "PWD=", all)))
		return (ft_free_three_str(home, path, pwd, ret));
	if (!ft_strcmp(home, path))
		write(1, all->home, ft_strlen(all->home));
	else
		write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(home);
	free(path);
	free(pwd);
	return (0);
}
