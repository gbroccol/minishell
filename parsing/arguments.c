/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:28:23 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/11 19:28:25 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			arguments_finish(t_all *all, char *line, t_pars *ps)
{
	if (line[ps->pos] == ';')
	{
		ps->pos++;
		while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
			ps->pos++;
		if (line[ps->pos] == '\0')
			return (0);
	}
	if (line[ps->pos] == '|')
	{
		if (line[ps->pos + 1] == '|')
			return (0);
		all->wait_cmd = 1;
		all->tok->pipe = 1;
		ps->pos++;
		while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
			ps->pos++;
		if (line[ps->pos] == '\0')
			return (0);
	}
	return (1);
}

static int	create_line(t_all *all, char *line, t_pars *ps)
{
	if (line[ps->pos] == '\'')
		quote_one(line, all->tok, ps);
	else if (line[ps->pos] == '\"')
		quote_two(all, line, all->tok, ps);
	else if (line[ps->pos] == '#')
		return (0);
	else if (line[ps->pos] == '|' && line[ps->pos + 1] == '|')
		return (0);
	else
		quote_no(all, line, all->tok, 0);
	return (1);
}

int			arguments(t_all *all, char *line, t_pars *ps)
{
	while (is_smb_in_str(line[ps->pos], ";|", 1) == 0)
	{
		while (is_smb_in_str(line[ps->pos], " \t", 0))
			ps->pos++;
		if (create_line(all, line, ps) == 0)
			return (0);
		if (is_smb_in_str(line[ps->pos], " \t;|", 1))
		{
			if (all->tok->tmp)
			{
				all->tok->args = ft_str_to_array(all->tok->args, all->tok->tmp);
				all->tok->tmp = NULL;
			}
		}
		while (is_smb_in_str(line[ps->pos], " \t", 0))
			ps->pos++;
	}
	if (line[ps->pos] == ';' || line[ps->pos] == '|')
		return (arguments_finish(all, line, ps));
	return (0);
}
