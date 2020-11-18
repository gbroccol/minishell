/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err_red_smb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:44:51 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/17 18:47:41 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				check_err_redir(char *str, t_pars *ps)
{
	if (str[ps->pos] == '<' && str[ps->pos + 1] == '<')
		return (1);
	else if (str[ps->pos] == '>' && str[ps->pos + 1] == '<')
		return (1);
	else if (str[ps->pos] == '<' && str[ps->pos + 1] == '>')
		return (1);
	else if ((str[ps->pos + 1] == '>' || str[ps->pos + 1] == '<') &&
				(str[ps->pos + 2] == '>' || str[ps->pos + 2] == '<'))
		return (1);
	ps->pos++;
	if (str[ps->pos] == '>')
		ps->pos++;
	while (str[ps->pos] == ' ' || str[ps->pos] == '\t')
		ps->pos++;
	if (str[ps->pos] == '|' || str[ps->pos] == ';' || str[ps->pos] == '\0' ||
			ft_isprint(str[ps->pos]) == 0)
		return (1);
	return (0);
}

void			skip_space(char *str, t_pars *ps, char smb)
{
	if (str[ps->pos] == smb)
	{
		ps->pos++;
		while (str[ps->pos] != smb && str[ps->pos] != '\0')
			ps->pos++;
		if (str[ps->pos] == smb)
			ps->pos++;
	}
}

int				check_err_red_smb(t_all *all, char *str, t_pars *ps)
{
	ps->pos = 0;
	while (str[ps->pos] != '\0')
	{
		while (is_smb_in_str(str[ps->pos], "\'\"<>", 1) == 0)
			ps->pos++;
		if (str[ps->pos] == '\"')
			skip_space(str, ps, '\"');
		if (str[ps->pos] == '\'')
			skip_space(str, ps, '\'');
		if (str[ps->pos] == '>' || str[ps->pos] == '<')
		{
			if (ps->pos > 0 && str[ps->pos - 1] != '\\')
			{
				if (check_err_redir(str, all->ps))
				{
					all->syntax = 1;
					return (1);
				}
			}
			else
				ps->pos++;
		}
	}
	return (0);
}
