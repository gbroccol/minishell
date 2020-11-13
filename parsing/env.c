/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:29:08 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/11 19:29:10 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		find_env(char *line, t_env *ps_env, char **env)
{
	int			pos;

	ps_env->line = 0;
	while (env[ps_env->line] != NULL)
	{
		ps_env->pos = 0;
		while (env[ps_env->line][ps_env->pos] != '\0')
		{
			pos = ps_env->str_pos + ps_env->pos;
			if (env[ps_env->line][ps_env->pos] == '=' &&
					is_smb_in_str(line[pos], " \t/$\"\'\\;=", 1))
				return (0);
			else if (env[ps_env->line][ps_env->pos] == '=')
				break ;
			if (line[pos] == '\0')
				break ;
			if (env[ps_env->line][ps_env->pos] != line[pos])
				break ;
			ps_env->pos++;
		}
		ps_env->line++;
	}
	ps_env->pos = 0;
	return (-1);
}

static void		check_env(char *line, t_env *ps_env, char **env)
{
	find_env(line, ps_env, env);
	while (is_smb_in_str(line[ps_env->str_pos], "/\\ \t|?.,\'\"=:;$", 1) == 0)
		ps_env->str_pos++;
	if (ps_env->pos != 0)
	{
		ps_env->pos++;
		ps_env->str = ft_strdup_start(env[ps_env->line], ps_env->pos);
	}
}

int				env(char *line, t_pars *ps, char **env)
{
	if (is_smb_in_str(line[ps->pos + 1], "/\\ \t|?.,\'\"=:;$", 1) == 0)
	{
		ps->pos++;
		if (ft_isdigit(line[ps->pos]))
		{
			ps->pos++;
			return (1);
		}
		ps->ps_env->str_pos = ps->pos;
		ps->ps_env->str = NULL;
		check_env(line, ps->ps_env, env);
		ps->pos = ps->ps_env->str_pos;
		return (0);
	}
	return (1);
}
