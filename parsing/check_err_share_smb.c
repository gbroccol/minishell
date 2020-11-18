/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err_share_smb.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:52:32 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/17 18:58:04 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		error_smb(t_all *all)
{
	all->syntax = 1;
	return (1);
}

static int		check_err_middle(char *str, int i)
{
	while (str[i] != ';' && str[i] != '|' && str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
			if (str[i] == '\'')
				i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"' && str[i] != '\0')
				i++;
			if (str[i] == '\"')
				i++;
		}
		else
			i++;
	}
	return (i);
}

static int		check_err_finish(char *str, int i)
{
	if (str[i] == ';')
		i++;
	else if (str[i] == '|')
	{
		i++;
		if (str[i] == '|')
			i++;
	}
	return (i);
}

int				check_err_share_smb(t_all *all, char *str, t_pars *ps)
{
	ps->pos = 0;
	while (str[ps->pos] != '\0')
	{
		while (str[ps->pos] == ' ' || str[ps->pos] == '\t')
			ps->pos++;
		if (str[ps->pos] == ';' || str[ps->pos] == '|')
			return (error_smb(all));
		if (str[ps->pos] == '>' || str[ps->pos] == '<')
		{
			while (str[ps->pos] == '>' || str[ps->pos] == '<')
				ps->pos++;
			while (str[ps->pos] == ' ' || str[ps->pos] == '\t')
				ps->pos++;
			if (is_smb_in_str(str[ps->pos], "|;", 1))
				return (error_smb(all));
		}
		ps->pos = check_err_middle(str, ps->pos);
		ps->pos = check_err_finish(str, ps->pos);
	}
	return (0);
}
