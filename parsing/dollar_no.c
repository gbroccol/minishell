/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_no.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:26:31 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/18 18:59:43 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		dollar_no_middle(t_all *all, char *line, t_pars *ps)
{
	int			ret;

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
	return (0);
}

int				dollar_no(t_all *all, char *line, t_pars *ps)
{
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
		return (dollar_no_middle(all, line, ps));
	}
	return (0);
}
