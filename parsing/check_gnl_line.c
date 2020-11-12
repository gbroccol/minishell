/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_gnl_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:29:50 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/11 19:29:51 by gbroccol         ###   ########.fr       */
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
			return (1);
		return (0);
	}
	return (0);
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

static void		check_err(t_all *all, char *str)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == ';' || str[i] == '|')
		{
			all->syntax = 1;
			return ;
		}
		i = check_err_middle(str, i);
		if (str[i] == ';')
			i++;
		else if (str[i] == '|')
		{
			i++;
			if (str[i] == '|')
				i++;
		}
	}
}

int				check_gnl_line(t_all *all, char *str)
{
	check_err(all, str);
	if (check_str_pipe(str) == 0)
		return (0);
	return (1);
}
