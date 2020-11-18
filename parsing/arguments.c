/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:28:23 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/17 18:47:04 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int			arguments_finish(t_all *all, char *line, t_pars *ps)
{
	if (line[ps->pos] == ';')
	{
		ps->pos++;
		while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
			ps->pos++;
		if (line[ps->pos] == '\0')
			return (1);  // stop parsing
	}
	if (line[ps->pos] == '|')
	{
		if (line[ps->pos + 1] == '|')
			return (1);  // stop parsing
		all->tok->pipe = 1;
		ps->pos++;
		while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
			ps->pos++;
		if (line[ps->pos] == '\0')
			return (1);  // stop parsing never happened
	}
	return (0);  // continue parsing
}

static int			create_line(t_all *all, char *line, t_pars *ps)
{
	if (line[ps->pos] == '\'')
		quote_one(line, ps);
	else if (line[ps->pos] == '\"')
		quote_two(all, line, ps);
	else if (line[ps->pos] == '#')
		return (1);
	else if (line[ps->pos] == '|' && line[ps->pos + 1] == '|')
		return (1);
	else if ((line[all->ps->pos] == '>' || line[all->ps->pos] == '<') &&
			redirect(all, line, &all->tok->redirect, ps))
		return (1);
	else
		quote_no(all, line, ps);
	return (0);
}

int					arguments(t_all *all, char *line, t_pars *ps)
{
	all->tok->fd_red = NULL;
	while (is_smb_in_str(line[ps->pos], ";|", 1) == 0)
	{
		while (is_smb_in_str(line[ps->pos], " \t", 0))
			ps->pos++;
		if (create_line(all, line, ps))
		{
			command(all->tok);
			return (1); // stop parsing
		}
		if (all->ps->tmp && is_smb_in_str(line[ps->pos], " \t;|<>", 1))
		{
			all->tok->args = ft_str_to_array(all->tok->args, all->ps->tmp);
			all->ps->tmp = NULL;
		}
		while (is_smb_in_str(line[ps->pos], " \t", 0))
			ps->pos++;
	}
	command(all->tok);
	if (line[ps->pos] == ';' || line[ps->pos] == '|')
		return (arguments_finish(all, line, ps));  // 1 - stop parsing 0 - continue parsing
	if (line[ps->pos] == '\0')
		return (1);
	return (0); // never happened
}
