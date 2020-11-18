/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:27:18 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/18 18:19:58 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		quote_two_finish(char *line, t_pars *ps)
{
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

static int		quote_two_middle(t_all *all, char *line, t_pars *ps)
{
	int			dollar_ret;

	if (line[ps->pos] == '$')
	{
		if ((dollar_ret = dollar_two(all, line, ps)) == 1)
			return (2);
		if (dollar_ret == -1)
			return (-1);
	}
	if (line[ps->pos] == '\\' && is_smb_in_str(line[ps->pos + 1], "$\"\\`", 0))
		ps->pos++;
	if ((ps->tmp2 = ft_letter_to_str(ps->tmp2, line[ps->pos], 0)) == NULL)
		return (-1);
	ps->pos++;
	return (0);
}

int				quote_two(t_all *all, char *line, t_pars *ps)
{
	int			ret;

	ps->tmp2 = NULL;
	if ((ps->tmp2 = ft_strdup("")) == NULL)
		return (-1);
	ps->pos++;
	while (line[ps->pos] != '\0' && line[ps->pos] != '\"')
	{
		if ((ret = quote_two_middle(all, line, ps)) == -1)
			return (-1);
		if (ret == 2)
			continue ;
	}
	if ((quote_two_finish(line, ps)) == -1)
		return (-1);
	return (0);
}
