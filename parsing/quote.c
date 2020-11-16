/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:34:23 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/16 15:52:48 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		dollar(t_all *all, char *line, t_pars *ps)
{
	if (line[all->ps->pos] == '$' && line[all->ps->pos + 1] == '?')
	{
		ps->tmp2 = ft_str_to_str(ps->tmp2, all->ps->status);
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
				ps->tmp2 = ft_str_to_str(ps->tmp2, all->ps->env_str);
			all->ps->env_str = NULL;
			return (1);
		}
	}
	return (0);
}

static int		tilda(t_all *all, t_pars *ps)
{
	char		*tmp;

	ps->pos++;
	if (ps->tmp2)
	{
		tmp = ps->tmp2;
		ps->tmp2 = ft_strjoin(ps->tmp2, all->home);
		free(tmp);
	}
	else
		ps->tmp2 = ft_strdup(all->home);
	return (1);
}

int				quote_no(t_all *all, char *line, t_pars *ps)
{
	int			nmb;

	nmb = 1;
	ps->tmp2 = NULL;
	while (is_smb_in_str(line[ps->pos], " \t;\"\'|><", 1) == 0)
	{
		if (nmb == 1 && ft_isdigit(line[ps->pos]) == 0)
			nmb = 0;
		if (line[ps->pos] == '$' && dollar(all, line, ps) == 1)
			continue;
		if (line[ps->pos] == '~' &&
				is_smb_in_str(line[ps->pos + 1], " ;|/:", 1) &&
				tilda(all, ps))
			continue ;
		if (line[ps->pos] == '\\')
			ps->pos++;
		ps->tmp2 = ft_letter_to_str(ps->tmp2, line[ps->pos++], 0);
	}
	if (ps->tmp2 && ps->tmp)
		ps->tmp = ft_str_to_str(ps->tmp, ps->tmp2);
	else if (ps->tmp2)
	{
		if (nmb && ps->pos > 0 && ft_isdigit(line[ps->pos - 1]) && is_smb_in_str(line[ps->pos], "><", 0))
		{
			all->tok->fd_red = ft_str_to_array(all->tok->fd_red, ps->tmp2);
			ps->tmp2 = NULL;
			redirect(all, line, &all->tok->fd_red, ps);
		}
		else
			ps->tmp = ps->tmp2;
	}
	ps->tmp2 = NULL;
	return (0);
}

int				quote_one(char *line, t_pars *ps)
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
	if (tmp_line && ps->tmp)
		ps->tmp = ft_str_to_str(ps->tmp, tmp_line);
	else if (tmp_line)
		ps->tmp = tmp_line;
	if (line[ps->pos] == '\'')
		ps->pos++;
	return (0);
}

int				quote_two(t_all *all, char *line, t_pars *ps)
{
	ps->tmp2 = NULL;
	ps->tmp2 = ft_strdup("");
	ps->pos++;
	while (line[ps->pos] != '\0' && line[ps->pos] != '\"')
	{
		if (line[ps->pos] == '$' && dollar(all, line, ps) == 1)
			continue;
		if (line[ps->pos] == '\\' &&
				is_smb_in_str(line[ps->pos + 1], "$\"\\`", 0))
			ps->pos++;
		ps->tmp2 = ft_letter_to_str(ps->tmp2, line[ps->pos], 0);
		ps->pos++;
	}
	if (ps->tmp2)
	{
		if (ps->tmp)
			ps->tmp = ft_str_to_str(ps->tmp, ps->tmp2);
		else
			ps->tmp = ps->tmp2;
	}
	if (line[ps->pos] == '\"')
		ps->pos++;
	ps->tmp2 = NULL;
	return (0);
}
