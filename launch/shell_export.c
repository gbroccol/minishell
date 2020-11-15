/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:30:52 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/15 17:05:13 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				replace_env(t_all *all, char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[size] != '=' && str[size] != '\0')
		size++;
	while (all->env[i] != NULL)
	{
		if (!ft_strncmp(str, all->env[i], size) &&
		ft_strchr(str, '='))
		{
			free(all->env[i]);
			all->env[i] = NULL;
			if (!(all->env[i] = ft_strdup(str)))
				return (-1);
			i = 0;
			break ;
		}
		i++;
	}
	return (i);
}

static void		print_env(char **env)
{
	int			i;
	int			size;
	char		**sort_env;

	i = 0;
	sort_env = NULL;
	sort_env = ft_sort_array(env);
	while (sort_env[i] != NULL)
	{
		size = 0;
		while (sort_env[i][size] != '=' && sort_env[i][size] != '\0')
			size++;
		size++;
		if (size > 1)
		{
			write(1, "declare -x ", 11);
			write(1, sort_env[i], size);
			if ((ft_strlen(sort_env[i]) - size) > 0)
			{
				write(1, "\"", 1);
				write(1, sort_env[i] + size, ft_strlen(sort_env[i]) - size);
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		i++;
	}
	if (sort_env)
		ft_free_array(sort_env);
}

int				shell_export(t_token *token, t_all *all)
{
	int		i;
	int		j;
	int		status;

	i = 0;
	j = 1;
	status = 0;
	if (!token->args[j])
		print_env(all->env);
	else
	{
		while (token->args[j] != NULL)
		{
			if ((i = replace_env(all, token->args[j])) < 0)
				return (1);
			if ((i != 0) || (token->args[j][0] == '='))
			{
				if (check_new_env(all, token->args[j]) == 0)
				{
					if (!(new_env(all, token->args[j])))
						return (1);
				}
				else
					status = 1;
			}
			update_home(all, token->args[j]);
			j++;
		}
	}
	return (status);
}
