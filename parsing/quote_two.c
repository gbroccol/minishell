/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:42:17 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/11 19:42:19 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int				quote_two(char *line, t_token *tok, t_pars *ps, char **env)
{
	char		*tmp_line;

	tmp_line = NULL;
	while (line[ps->pos] != '\0' && line[ps->pos] != '\"')
	{
		if (line[ps->pos] == '$' && line[ps->pos + 1] == '?')
		{
			tmp_line = ft_str_to_str(tmp_line, ps->status);
			ps->pos++;
			ps->pos++;
			continue ;
		}
		if (line[ps->pos] == '$' && line[ps->pos + 1] != '=')
		{
			if (is_env(line, ps, env) == 0)
			{
				if (ps->ps_env->str != NULL)
					tmp_line = ft_str_to_str(tmp_line, ps->ps_env->str);
				continue ;
			}
		}

		if (line[ps->pos] == '\\' && line[ps->pos + 1] == '$')
			ps->pos++;
        else if (line[ps->pos] == '\\' && line[ps->pos + 1] == '\"')
			ps->pos++;
		else if (line[ps->pos] == '\\' && line[ps->pos + 1] == '\\')
			ps->pos++;
        else if (line[ps->pos] == '\\' && line[ps->pos + 1] == '`')
			ps->pos++;
		
		tmp_line = ft_letter_to_str(tmp_line, line[ps->pos], 0);
		ps->pos++;
	}
	if (tmp_line)
	{
		if (tok->tmp)
			tok->tmp = ft_str_to_str(tok->tmp, tmp_line);
		else
			tok->tmp = tmp_line;
	}
	if (line[ps->pos] == '\"')
		ps->pos++;
	return (0);
}
