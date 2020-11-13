/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:34:23 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/13 19:49:47 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		dollar(t_all *all, char *line, t_token *tok)
{
	if (line[all->ps->pos] == '$' && line[all->ps->pos + 1] == '?')
	{
		tok->tmp2 = ft_str_to_str(tok->tmp2, all->ps->status);
		all->ps->status = NULL;
		all->ps->pos++;
		all->ps->pos++;
		return (1);
	}
	if (line[all->ps->pos] == '$' && line[all->ps->pos + 1] != '=')
	{
		if (env(line, all->ps, all->env) == 0)
		{
			if (all->ps->env_str != NULL)
				tok->tmp2 = ft_str_to_str(tok->tmp2, all->ps->env_str);
			all->ps->env_str = NULL;
			return (1);
		}
	}
	return (0);
}

static int		tilda(t_all *all, t_token *tok, t_pars *ps)
{
	char		*tmp;

	ps->pos++;
	if (tok->tmp2)
	{
		tmp = tok->tmp2;
		tok->tmp2 = ft_strjoin(tok->tmp2, all->home);
		free(tmp);
	}
	else
		tok->tmp2 = ft_strdup(all->home);
	return (1);
}

int				quote_no(t_all *all, char *line, t_token *tok)
{
	tok->tmp2 = NULL;
	while (is_smb_in_str(line[all->ps->pos], " \t;\"\'|><", 1) == 0)
	{
		if (line[all->ps->pos] == '$' && dollar(all, line, tok) == 1)
			continue;
		if (line[all->ps->pos] == '~' &&
				is_smb_in_str(line[all->ps->pos + 1], " ;|/:", 1) &&
				tilda(all, tok, all->ps))
			continue ;
		if (line[all->ps->pos] == '\\')
			all->ps->pos++;
		tok->tmp2 = ft_letter_to_str(tok->tmp2, line[all->ps->pos++], 0);
	}
	if (tok->tmp2 && tok->tmp)
		tok->tmp = ft_str_to_str(tok->tmp, tok->tmp2);
	else if (tok->tmp2)
		tok->tmp = tok->tmp2;
	tok->tmp2 = NULL;
	return (0);
}

int				quote_one(char *line, t_token *tok, t_pars *ps)
{
	char		*tmp_line;

	tmp_line = NULL;
	tmp_line = ft_strdup("");
	ps->pos++;
	while (line[ps->pos] != '\0' && line[ps->pos] != '\'')
	{
		tmp_line = ft_letter_to_str(tmp_line, line[ps->pos], 0);
		ps->pos++;
	}
	if (tmp_line && tok->tmp)
		tok->tmp = ft_str_to_str(tok->tmp, tmp_line);
	else if (tmp_line)
		tok->tmp = tmp_line;
	if (line[ps->pos] == '\'')
		ps->pos++;
	return (0);
}

int				quote_two(t_all *all, char *line, t_token *tok, t_pars *ps)
{
	tok->tmp2 = NULL;
	tok->tmp2 = ft_strdup("");
	ps->pos++;
	while (line[ps->pos] != '\0' && line[ps->pos] != '\"')
	{
		if (line[ps->pos] == '$' && dollar(all, line, tok) == 1)
			continue;
		if (line[ps->pos] == '\\' &&
				is_smb_in_str(line[ps->pos + 1], "$\"\\`", 0))
			ps->pos++;
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
	tok->tmp2 = NULL;
	return (0);
}
