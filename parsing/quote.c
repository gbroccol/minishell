/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:34:23 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/18 15:47:54 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				dollar(t_all *all, char *line, t_pars *ps)
{
	int			ret;

	if (line[all->ps->pos] == '$' && line[all->ps->pos + 1] == '?')
	{
		if ((ps->tmp2 = ft_str_to_str(ps->tmp2, all->ps->status)) == NULL)
			return (-1);
		all->ps->status = NULL;
		all->ps->pos++;
		all->ps->pos++;
		return (1);
	}
	else if (line[all->ps->pos] == '$' &&
		is_smb_in_str(line[ps->pos + 1], "/\\ \t|?.,=:;$", 1) == 0)
	{
		ret = env(line, all->ps, all);
		if (ret == 0)
		{
			if (all->ps->env_str != NULL)
			{
				if ((ps->tmp2 = ft_str_to_str(ps->tmp2, all->ps->env_str)) == NULL)
					return (-1);
			}
			all->ps->env_str = NULL;
			return (1);
		}
		else if (ret == -1)
			return (-1);
	}
	return (0);
}

int				quote_one(char *line, t_pars *ps)
{
	char		*tmp_line;

	tmp_line = NULL;
	if ((tmp_line = ft_strdup("")) == NULL)
		return (-1);
	ps->pos++;
	while (line[ps->pos] != '\0' && line[ps->pos] != '\'')
	{
		if ((tmp_line = ft_letter_to_str(tmp_line, line[ps->pos], 0)) == NULL)
			return (-1);
		ps->pos++;
	}
	if (tmp_line && ps->tmp)
	{
		if ((ps->tmp = ft_str_to_str(ps->tmp, tmp_line)) == NULL)
			return (-1);
	}
	else if (tmp_line)
		ps->tmp = tmp_line;
	if (line[ps->pos] == '\'')
		ps->pos++;
	return (0);
}

int				quote_two(t_all *all, char *line, t_pars *ps)
{
	int			dollar_ret;

	ps->tmp2 = NULL;
	if ((ps->tmp2 = ft_strdup("")) == NULL)
		return (-1);
	ps->pos++;
	while (line[ps->pos] != '\0' && line[ps->pos] != '\"')
	{
		if (line[ps->pos] == '$')
		{
			dollar_ret = dollar(all, line, ps);
			if (dollar_ret == 1)
				continue;
			if (dollar_ret == -1)
				return (-1);
		}			
		if (line[ps->pos] == '\\' && is_smb_in_str(line[ps->pos + 1], "$\"\\`", 0))
			ps->pos++;
		if ((ps->tmp2 = ft_letter_to_str(ps->tmp2, line[ps->pos], 0)) == NULL)
			return (-1);
		ps->pos++;
	}
	if (ps->tmp2)
	{
		if (ps->tmp)
		{
			if ((ps->tmp = ft_str_to_str(ps->tmp, ps->tmp2)) == NULL)
				return (-1);
		}	
		else
			ps->tmp = ps->tmp2;
	}
	if (line[ps->pos] == '\"')
		ps->pos++;
	ps->tmp2 = NULL;
	return (0);
}
