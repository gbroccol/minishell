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

# include "../minishell.h"

int				find_env(char *line, t_env *ps_env, char **env)
{
	ps_env->env_line = 0;
	while (env[ps_env->env_line] != NULL)
	{
		ps_env->env_pos = 0;
		while (env[ps_env->env_line][ps_env->env_pos] != '\0')
		{
			if (env[ps_env->env_line][ps_env->env_pos] == '=')
			{
				if (line[ps_env->str_pos + ps_env->env_pos] == ' ' ||
						line[ps_env->str_pos + ps_env->env_pos] == '\t' ||
						line[ps_env->str_pos + ps_env->env_pos] == '\0' ||
						line[ps_env->str_pos + ps_env->env_pos] == '/' ||
						line[ps_env->str_pos + ps_env->env_pos] == '$' ||
						line[ps_env->str_pos + ps_env->env_pos] == '\"' ||
						line[ps_env->str_pos + ps_env->env_pos] == '\'' ||
						line[ps_env->str_pos + ps_env->env_pos] == '\\' ||
						line[ps_env->str_pos + ps_env->env_pos] == ';' ||
						line[ps_env->str_pos + ps_env->env_pos] == '=') 
					return (0);
				// else if (line[ps_env->str_pos + ps_env->env_pos] == '\\')
				// 	return (0);
				else
					break ;
			}
			else if (env[ps_env->env_line][ps_env->env_pos] != '=')
			{
				if (line[ps_env->str_pos + ps_env->env_pos] == '\0')
					break ;
				if (env[ps_env->env_line][ps_env->env_pos] != line[ps_env->str_pos + ps_env->env_pos])
					break ;
			}
			ps_env->env_pos++;
		}
		ps_env->env_line++;
	}
	ps_env->env_pos = 0;
	return (-1);
}

void			check_env(char *line, t_env *ps_env, char **env)
{
	find_env(line, ps_env, env);
	while (line[ps_env->str_pos] != ' ' && line[ps_env->str_pos] != '\0' &&
			line[ps_env->str_pos] != '\\' && line[ps_env->str_pos] != '/' &&
			line[ps_env->str_pos] != '\'' && line[ps_env->str_pos] != '\"' &&
			line[ps_env->str_pos] != '$' && line[ps_env->str_pos] != ';' &&
			line[ps_env->str_pos] != '=')
		ps_env->str_pos++;

	// if (line[ps_env->str_pos] == '\\') // ???
	// 	ps_env->str_pos++;
	//  echo hello '\' ';' "   '\' \" " \" "$PWD\\\"\~\;"\; >> t1 \' \ \ \\     -> check it

	if (ps_env->env_pos != 0)
	{
		ps_env->env_pos++;
		while (env[ps_env->env_line][ps_env->env_pos] != '\0')
		{
			ps_env->str = ft_letter_to_str(ps_env->str, env[ps_env->env_line][ps_env->env_pos], 0);
			ps_env->env_pos++;
		}
	}
}
