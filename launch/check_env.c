/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:32:40 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/18 20:10:20 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_find_error(char *exec, char *env, int size)
{
	write(2, "bash: ", 6);
	write(2, exec, ft_strlen(exec));
	write(2, ": ", 2);
	write(2, env, size - 1);
	write(2, " not set\n", 9);
}

char		*search_env(char **env, char *to_find, t_all *all)
{
	int		i;
	int		size;
	char	*value;

	i = 0;
	size = ft_strlen(to_find);
	value = NULL;
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
		if (ft_strncmp(to_find, "PATH", 4) && ft_strncmp(to_find, "PWD", 3))
			print_find_error(all->tok->cmd, to_find, size);
		return (ft_strdup(""));
	}
	return (value);
}
