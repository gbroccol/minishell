/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:29:03 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/13 17:24:23 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		shell_env(char **env)
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

int		shell_unset(t_token *token, char **env)
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
				if (ft_strcmp(env[i], token->args[j]) == '=' ||
				!ft_strcmp(env[i], token->args[j]))
				{
					free(env[i]);
					env[i] = NULL;
					env[i] = ft_strdup("");
					break ;
				}
				i++;
			}
			j++;
		}
	}
	return (0);
}
