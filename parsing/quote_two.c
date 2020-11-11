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

int				quote_two(char *line, t_token *tok, t_pars *ps, char **env)
{
	tok->tmp2 = NULL;
	while (line[ps->pos] != '\0' && line[ps->pos] != '\"')
	{
		if (line[ps->pos] == '$' && check_dollar(line, tok, ps, env) == 1)
			continue;
		if (line[ps->pos] == '\\')
			check_shielding(line, ps);
		tok->tmp2 = ft_letter_to_str(tok->tmp2, line[ps->pos], 0);
		ps->pos++;
	}
	if (tok->tmp2)
	{
		if (tok->tmp)
			tok->tmp = ft_str_to_str(tok->tmp, tok->tmp2);
		else
			tok->tmp = tok->tmp2;
	}
	if (line[ps->pos] == '\"')
		ps->pos++;
	return (0);
}
