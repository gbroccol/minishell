/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:28:23 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/18 18:02:44 by gbroccol         ###   ########.fr       */
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
			return (1);
	}
	if (line[ps->pos] == '|')
	{
		if (line[ps->pos + 1] == '|')
			return (1);
		all->tok->pipe = 1;
		ps->pos++;
		while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
			ps->pos++;
		if (line[ps->pos] == '\0')
			return (1);
	}
	return (0);
}

static int			create_line(t_all *all, char *line, t_pars *ps)
{
	if (line[ps->pos] == '\'' && quote_one(line, ps) == -1)
		return (-1);
	else if (line[ps->pos] == '\"' && quote_two(all, line, ps) == -1)
		return (-1);
	else if (line[ps->pos] == '#')
		return (1);
	else if (line[ps->pos] == '|' && line[ps->pos + 1] == '|')
		return (1);
	else if ((line[all->ps->pos] == '>' || line[all->ps->pos] == '<'))
	{
		if (redirect(all, line, &all->tok->redirect, ps) == -1)
			return (-1);
	}
	else
	{
		if ((quote_no(all, line, ps, 0)) == -1)
			return (-1);
	}
	return (0);
}

static int			arguments_middle(t_all *all, char *line, t_pars *ps)
{
	int				ret;

	ret = 0;
	while (is_smb_in_str(line[ps->pos], " \t", 0))
		ps->pos++;
	if ((ret = create_line(all, line, ps) == 1))
		return (command(all->tok) == -1 ? -1 : 1);
	if (ret == -1)
		return (-1);
	if (all->ps->tmp && is_smb_in_str(line[ps->pos], " \t;|<>", 1))
	{
		if ((all->tok->args = ft_str_to_array(all->tok->args, ps->tmp)) == NULL)
			return (-1);
		all->ps->tmp = NULL;
	}
	while (is_smb_in_str(line[ps->pos], " \t", 0))
		ps->pos++;
	return (0);
}

int					arguments(t_all *all, char *line, t_pars *ps)
{
	int				ret;

	all->tok->fd_red = NULL;
	while (is_smb_in_str(line[ps->pos], ";|", 1) == 0)
	{
		if ((ret = arguments_middle(all, line, ps)) != 0)
			return (ret);
	}
	if (command(all->tok) == -1)
		return (-1);
	if (line[ps->pos] == ';' || line[ps->pos] == '|')
		return (arguments_finish(all, line, ps));
	if (line[ps->pos] == '\0')
		return (1);
	return (0);
}
