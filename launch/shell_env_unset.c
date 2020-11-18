/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:29:03 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/18 19:17:15 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			shell_env(char **env)
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
	return (0);
}

static int	malloc_err(int *ret)
{
	write(2, "bash: malloc error\n", 19);
	*ret = 0;
	return (1);
}

int			shell_unset(t_token *token, t_all *all, int *ret)
{
	int	i;
	int j;

	i = 0;
	j = 1;
	if (token->args[j])
	{
		while (token->args[j] != NULL)
		{
			while (all->env[i] != NULL)
			{
				if (ft_strcmp(all->env[i], token->args[j]) == '=' ||
				!ft_strcmp(all->env[i], token->args[j]))
				{
					if (!(all->env = ft_del_str_from_ar(all->env, i)))
						return (malloc_err(ret));
					break ;
				}
				i++;
			}
			j++;
		}
	}
	return (0);
}
