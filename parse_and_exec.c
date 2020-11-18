/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:15:19 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/18 18:31:22 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parse(t_all *all)
{
	all->ps->pos = 0;
	all->ret_pars = 0;
	all->ps->red_pos = 0;
	all->ps->er_redir = 0;
}

void	parse_and_exec(t_all *all)
{
	int		tmp_pos;

	while (all->ret_pars == 0 && !all->syntax)
	{
		all->ps->status = ft_itoa(all->status);
		all->ps->env_str_pos = 0;
		all->ps->env_str = NULL;
		if ((all->ps->red_pos == 0 && all->ps->pos == 0) || \
		all->ps->red_pos < all->ps->pos)
		{
			tmp_pos = all->ps->pos;
			all->ps->red_pos = check_redir_files(all, all->gnl_line, all->ps);
			if (all->ps->red_pos == -1)
				all->ret_pars = 1;
			all->ps->pos = tmp_pos;
		}
		if (!all->ps->er_redir && all->ret_pars == 0)
			all->ret_pars = parsing(all, all->ps);
		if (!all->ps->er_redir && all->ret_pars != -1)
			all->ret_ex = execute(all);
		if (all->tok)
			exit_all_tok(all->tok);
		if (all->ps)
			exit_all_ps(all->ps);
	}
}
