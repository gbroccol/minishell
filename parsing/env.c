/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:29:08 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/17 18:49:45 by gbroccol         ###   ########.fr       */
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

static void		check_env(char *line, t_pars *ps, t_all *all)
{
	if (find_env(line, ps, all->env) == 0)
	{
		if (ps->env_pos != 0)
		{
			ps->env_pos++;
			ps->env_str = ft_strdup_start(all->env[ps->env_line], ps->env_pos);
		}
	}
	else if (find_env(line, ps, all->local) == 0)
	{
		if (ps->env_pos != 0)
		{
			ps->env_pos++;
			ps->env_str = ft_strdup_start(all->local[ps->env_line],
									ps->env_pos);
		}
	}
	while (is_smb_in_str(line[ps->env_str_pos], "/\\ \t|?.,\'\"=:;$", 1) == 0)
		ps->env_str_pos++;
}

int				env(char *line, t_pars *ps, t_all *all)
{
	if (is_smb_in_str(line[ps->pos + 1], "/\\ \t|?.,\'\"=:;$", 1) == 0)
	{
		ps->pos++;
		if (ft_isdigit(line[ps->pos]))
		{
			ps->pos++;
			return (1);
		}
		ps->env_str_pos = ps->pos;
		ps->env_str = NULL;
		check_env(line, ps, all);
		ps->pos = ps->env_str_pos;
		return (0);
	}
	return (1);
}
