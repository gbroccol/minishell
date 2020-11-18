/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:34:23 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/18 17:27:12 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
