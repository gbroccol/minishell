/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_no.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:30:34 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/18 14:24:23 by gbroccol         ###   ########.fr       */
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
		if ((ps->tmp2 = ft_strjoin(ps->tmp2, all->home)) == NULL)
			return (-1);
		free(tmp);
	}
	else
	{
		if ((ps->tmp2 = ft_strdup(all->home)) == NULL)
			return (-1);
	}
	return (1);
}

static int		quote_no_middle(t_all *all, char *line, t_pars *ps)
{
	int			nmb;
	int			ret;

	nmb = 1;
	while (is_smb_in_str(line[ps->pos], " \t;\"\'|><", 1) == 0)
	{
		if (nmb == 1 && ft_isdigit(line[ps->pos]) == 0)
			nmb = 0;
		if (line[ps->pos] == '$')
		{
			ret = dollar(all, line, ps);
			if (ret == 1)
				continue;
			if (ret == -1)
				return (-1);
		}
		if (line[ps->pos] == '~' &&	is_smb_in_str(line[ps->pos + 1], " ;|/:", 1))
		{
			ret = tilda(all, ps);
			if (ret == 1)
				continue;
			if (ret == -1)
				return (-1);
		}
		if (line[ps->pos] == '\\')
			ps->pos++;
		if ((ps->tmp2 = ft_letter_to_str(ps->tmp2, line[ps->pos++], 0)) == NULL)
			return (-1);
	}
	return (nmb);
}

int				quote_no(t_all *all, char *line, t_pars *ps, int red_ignor)
{
	int			nmb;

	nmb = 1;
	ps->tmp2 = NULL;
	if ((nmb = quote_no_middle(all, line, ps)) == -1)
		return (-1);
	if (ps->tmp2 && ps->tmp)
	{
		if ((ps->tmp = ft_str_to_str(ps->tmp, ps->tmp2)) == NULL)
			return (-1);
	}	
	else if (ps->tmp2)
	{
		if (red_ignor == 0 && nmb && ps->pos > 0 && ft_isdigit(line[ps->pos - 1]) &&
				is_smb_in_str(line[ps->pos], "><", 0))
		{
			all->tok->fd_red = ft_str_to_array(all->tok->fd_red, ps->tmp2);
			if (all->tok->fd_red == NULL)
				return (-1);
			ps->tmp2 = NULL;
			if ((redirect(all, line, &all->tok->fd_red, ps)) == -1)
				return (-1);
		}
		else
			ps->tmp = ps->tmp2;
	}
	ps->tmp2 = NULL;
	return (0);
}
