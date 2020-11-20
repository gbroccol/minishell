/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_new_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:32:07 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/20 14:51:06 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_line_to_smb(char *ar, char *str, int smb)
{
	int			i;

	i = 0;
	while (ar[i] == str[i] && ar[i] != '\0')
		i++;
	if (smb == 1)
	{
		if (ar[i] == '=')
			return (0);
	}
	else if (smb == 2)
	{
		if (ar[i] == '=' || ar[i] == '\0')
			return (0);
	}
	return (1);
}

static int	find_env(char *line, char **ar, int smb)
{
	int			l_line;

	l_line = 0;
	while (ar && ar[l_line] != NULL)
	{
		if (check_line_to_smb(ar[l_line], line, smb))
		{
			l_line++;
			continue ;
		}
		else
			return (l_line);
	}
	return (-1);
}

static	int	export_new_env(t_all *all, char *env, int *status)
{
	int i;

	i = 0;
	if ((i = replace_env(all->env, env)) < 0)
		return (1);
	if ((i != 0) || (env[0] == '='))
	{
		if (check_new_env(all, env) == 0)
		{
			if (!(new_str(all, env)))
				return (1);
		}
		else
			*status = 1;
	}
	return (0);
}

int			check_vars_and_export(t_token *token, t_all *all, int *status)
{
	int		i;
	int		line;

	i = 1;
	while (token->args[i] != NULL)
	{
		if (!ft_strchr(token->args[i], '=') && \
		find_env(token->args[i], all->env, 2))
		{
			if ((line = find_env(token->args[i], all->local, 1)) >= 0)
			{
				if (!(new_str(all, all->local[line])))
					return (1);
				all->local = ft_del_str_from_ar(all->local, line);
				i++;
				continue ;
			}
		}
		if (export_new_env(all, token->args[i], status) != 0)
			return (1);
		update_home(all, token->args[i]);
		i++;
	}
	return (0);
}
