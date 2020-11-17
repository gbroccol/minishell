/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_no.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:30:34 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/17 18:33:53 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		tilda(t_all *all, t_pars *ps)
{
	char		*tmp;

	ps->pos++;
	if (ps->tmp2)
	{
		tmp = ps->tmp2;
		ps->tmp2 = ft_strjoin(ps->tmp2, all->home);
		free(tmp);
	}
	else
		ps->tmp2 = ft_strdup(all->home);
	return (1);
}

static int		quote_no_middle(t_all *all, char *line, t_pars *ps)
{
	int			nmb;

	nmb = 1;
	while (is_smb_in_str(line[ps->pos], " \t;\"\'|><", 1) == 0)
	{
		if (nmb == 1 && ft_isdigit(line[ps->pos]) == 0)
			nmb = 0;
		if (line[ps->pos] == '$' && dollar(all, line, ps) == 1)
			continue;
		if (line[ps->pos] == '~' &&
				is_smb_in_str(line[ps->pos + 1], " ;|/:", 1) &&
				tilda(all, ps))
			continue ;
		if (line[ps->pos] == '\\')
			ps->pos++;
		ps->tmp2 = ft_letter_to_str(ps->tmp2, line[ps->pos++], 0);
	}
	return (nmb);
}

int				quote_no(t_all *all, char *line, t_pars *ps)
{
	int			nmb;

	nmb = 1;
	ps->tmp2 = NULL;
	nmb = quote_no_middle(all, line, ps);
	if (ps->tmp2 && ps->tmp)
		ps->tmp = ft_str_to_str(ps->tmp, ps->tmp2);
	else if (ps->tmp2)
	{
		if (nmb && ps->pos > 0 && ft_isdigit(line[ps->pos - 1]) &&
				is_smb_in_str(line[ps->pos], "><", 0))
		{
			all->tok->fd_red = ft_str_to_array(all->tok->fd_red, ps->tmp2);
			ps->tmp2 = NULL;
			redirect(all, line, &all->tok->fd_red, ps);
		}
		else
			ps->tmp = ps->tmp2;
	}
	ps->tmp2 = NULL;
	return (0);
}
