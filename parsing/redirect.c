/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:44:42 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/18 17:55:21 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_file(char *str, t_pars *ps)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	write(1, "bash: syntax error near unexpected token `", 42);
	write(1, str, ft_strlen(str));
	write(1, "'\n", 2);
	ps->er_redir = 1;
	return (-1);
}

static int	redirect_file(t_all *all, char *line, t_pars *ps)
{
	ps->tmp = NULL;
	while (is_smb_in_str(line[ps->pos], ";|<> \t", 1) == 0)
	{
		if (line[ps->pos] == '\'' && quote_one(line, ps) == -1)
			return (-1);
		else if (line[ps->pos] == '\"' && quote_two(all, line, ps) == -1)
			return (-1);
		else
		{
			if ((quote_no(all, line, ps, 1)) == -1)
				return (-1);
		}
	}
	if (is_smb_in_str(line[ps->pos], "<>", 0) && check_file(ps->tmp, ps))
		return (-1);
	return (0);
}

int			redirect(t_all *all, char *line, char ***red_ar, t_pars *ps)
{
	ps->tmp = NULL;
	ps->er_redir = 0;
	while (line[ps->pos] == '>' || line[ps->pos] == '<')
	{
		if ((ps->tmp = ft_letter_to_str(ps->tmp, line[ps->pos], 0)) == NULL)
			return (-1);
		ps->pos++;
	}
	if (((*red_ar) = ft_str_to_array(*red_ar, ps->tmp)) == NULL)
		return (-1);
	while (is_smb_in_str(line[ps->pos], SHARE_SMB, 0))
		ps->pos++;
	ps->tmp = NULL;
	if (redirect_file(all, line, ps) == -1)
		return (-1);
	(*red_ar) = ft_str_to_array(*red_ar, ps->tmp);
	ps->tmp = NULL;
	return (0);
}
