/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:30:52 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/20 13:24:02 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_strlen_env(char *str)
{
	int size;

	size = 0;
	while (str[size] != '=' && str[size] != '\0')
		size++;
	if (str[size] == '=')
		size++;
	return (size);
}

static void	print_env(char **env)
{
	int			i;
	int			size;
	char		**sort_env;

	i = -1;
	sort_env = NULL;
	sort_env = ft_sort_array(env);
	while (sort_env[++i] != NULL)
	{
		size = ft_strlen_env(sort_env[i]);
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
	if (sort_env)
		ft_free_array(sort_env);
}

int			shell_export(t_token *token, t_all *all, int *ret)
{
	int		status;

	status = 0;
	if (!token->args[1])
		print_env(all->env);
	else
	{
		if (check_vars_and_export(token, all, &status) != 0)
		{
			write(2, "bash: malloc error\n", 19);
			*ret = 0;
			return (1);
		}
	}
	return (status);
}
