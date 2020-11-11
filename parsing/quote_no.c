/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_no.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:34:09 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/11 19:34:13 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		check_dollar(char *line, t_token *tok, t_pars *ps, char **env)
{
	if (line[ps->pos] == '$' && line[ps->pos + 1] == '?')
	{
		tok->tmp2 = ft_str_to_str(tok->tmp2, ps->status);
		ps->pos++;
		ps->pos++;
		return (1);
	}
	if (line[ps->pos] == '$' && line[ps->pos + 1] != '=')
	{
		if (is_env(line, ps, env) == 0)
		{
			if (ps->ps_env->str != NULL)
				tok->tmp2 = ft_str_to_str(tok->tmp2, ps->ps_env->str);
			return (1);
		}
	}
	return (0);
}

int				quote_no(char *line, t_token *tok, t_pars *ps, char **env, int redir_ignor)
{
	tok->tmp2 = NULL;
	while (is_smb_in_str(line[ps->pos], " \t;\"\'|", 1) == 0)
	{
		if (line[ps->pos] == '$' && check_dollar(line, tok, ps, env) == 1)
			continue;
		if (line[ps->pos] == '~' && is_smb_in_str(line[ps->pos + 1], " ;|/:", 1))
		{
			ps->pos++;
			ps->ps_env->env_line = 0;
			ps->ps_env->env_pos = 0;
			ps->ps_env->str_pos = 0;
			ps->ps_env->str = NULL;
			check_env("HOME", ps->ps_env, env);
			if (ps->ps_env->str != NULL)
				tok->tmp2 = ft_str_to_str(tok->tmp2, ps->ps_env->str);
			continue ;
		}
		if (redir_ignor == 0 && (line[ps->pos] == '>' || line[ps->pos] == '<'))
		{
			check_redirect(line, ps, tok, env);
			continue ;
		}
		else if (line[ps->pos] == '>' || line[ps->pos] == '<')
			break ;

		if (line[ps->pos] == '\\' && line[ps->pos + 1] != '\\') // ?
			ps->pos++;
		if (line[ps->pos] == '\\' && line[ps->pos + 1] == '#')
			ps->pos++;
		tok->tmp2 = ft_letter_to_str(tok->tmp2, line[ps->pos], 0);
		ps->pos++;
	}
	
	if (tok->tmp2 && tok->tmp)
		tok->tmp = ft_str_to_str(tok->tmp, tok->tmp2);
	else if (tok->tmp2)
		tok->tmp = tok->tmp2;
	return (0);
}
