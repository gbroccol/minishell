/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:29:08 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/18 13:55:10 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		find_env(char *line, t_pars *ps, char **env)
{
	int			pos;

	ps->env_line = 0;
	if (!env)
		return (1);
	while (env != NULL && env[ps->env_line] != NULL)
	{
		ps->env_pos = 0;
		while (env[ps->env_line][ps->env_pos] != '\0')
		{
			pos = ps->env_str_pos + ps->env_pos;
			if (env[ps->env_line][ps->env_pos] == '=' &&
					is_smb_in_str(line[pos], " \t/$\"\'\\;=", 1))
				return (0);
			else if (env[ps->env_line][ps->env_pos] == '=')
				break ;
			if (line[pos] == '\0' ||
					env[ps->env_line][ps->env_pos] != line[pos])
				break ;
			ps->env_pos++;
		}
		ps->env_line++;
	}
	ps->env_pos = 0;
	return (1);
}

static int		check_env(char *line, t_pars *ps, t_all *all)
{
	if (find_env(line, ps, all->env) == 0)
	{
		if (ps->env_pos != 0)
		{
			ps->env_pos++;
			ps->env_str = ft_strdup_start(all->env[ps->env_line], ps->env_pos);
			if (ps->env_str == NULL)
				return (-1);
		}
	}
	else if (find_env(line, ps, all->local) == 0)
	{
		if (ps->env_pos != 0)
		{
			ps->env_pos++;
			ps->env_str = ft_strdup_start(all->local[ps->env_line],
									ps->env_pos);
			if (ps->env_str == NULL)
				return (-1);
		}
	}
	while (is_smb_in_str(line[ps->env_str_pos], "/\\ \t|?.,\'\"=:;$", 1) == 0)
		ps->env_str_pos++;
	return (0);
}

int				env(char *line, t_pars *ps, t_all *all)
{
	if (is_smb_in_str(line[ps->pos + 1], "/\\ \t|?.,=:;$", 1) == 0)
	{
		ps->pos++;
		if (ft_isdigit(line[ps->pos]))
		{
			ps->pos++;
			return (1);
		}
		ps->env_str_pos = ps->pos;
		ps->env_str = NULL;
		if (check_env(line, ps, all) == -1)
			return (-1);
		ps->pos = ps->env_str_pos;
		return (0);
	}
	return (1);
}
