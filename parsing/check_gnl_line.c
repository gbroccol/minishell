/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_gnl_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:29:50 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/16 16:10:37 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		check_str_pipe(char *str)
{
	int			i;

	i = 0;
	if (str && str[i] != '\0')
	{
		while (str[i] != '\0')
			i++;
		while (i > 0 && (str[i] == '\0' ||
			str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
			i--;
		if (str[i] == '|')
			return (0);
		return (1);
	}
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
	if (str[ps->pos] == '|' || str[ps->pos] == ';' || str[ps->pos] == '\0' || ft_isprint(str[ps->pos]) == 0)
		return (1);
	return (0);
}

static int		check_err_share_smb(t_all *all, char *str, t_pars *ps)
{
	ps->pos = 0;
	while (str[ps->pos] != '\0')
	{
		while (str[ps->pos] == ' ' || str[ps->pos] == '\t')
			ps->pos++;
		if (str[ps->pos] == ';' || str[ps->pos] == '|')
		{
			all->syntax = 1;
			return (1);
		}
		ps->pos = check_err_middle(str, ps->pos);
		if (str[ps->pos] == ';')
			ps->pos++;
		else if (str[ps->pos] == '|')
		{
			ps->pos++;
			if (str[ps->pos] == '|')
				ps->pos++;
		}
	}
	return (0);
}

int				check_err_red_smb(t_all *all, char *str, t_pars *ps)
{
	ps->pos = 0;
	while (str[ps->pos] != '\0')
	{
		while (str[ps->pos] != '\'' && str[ps->pos] != '\"'
				&& str[ps->pos] != '>' && str[ps->pos] != '<' && str[ps->pos] != '\0')
			ps->pos++;
		if (str[ps->pos] == '\'')
		{
			while (str[ps->pos] != '\'' && str[ps->pos] != '\0')
				ps->pos++;
			if (str[ps->pos] == '\'')
				ps->pos++;
		}
		if (str[ps->pos] == '\"')
		{
			while (str[ps->pos] != '\"' && str[ps->pos] != '\0')
				ps->pos++;
			if (str[ps->pos] == '\"')
				ps->pos++;
		}
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

int				check_gnl_line(t_all *all, char *str)
{
	if (check_err_share_smb(all, str, all->ps))
		return (1);
	if (check_err_red_smb(all, str, all->ps))
		return (1);
	if (check_str_pipe(str))
		return (1);
	return (0);
}
