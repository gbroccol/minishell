/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:33:48 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/18 18:00:59 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		clear_token_again(t_token *tok)
{
	tok->type_func = -1;
	tok->cmd = NULL;
	tok->args = NULL;
	tok->redirect = NULL;
	tok->fd_red = NULL;
	tok->pipe = 0;
	tok->flag_n = 0;
}

int				parsing(t_all *all, t_pars *ps)
{
	int			arg_ret;

	clear_token_again(all->tok);
	ps->tmp = NULL;
	ps->tmp2 = NULL;
	all->tok->redirect = NULL;
	while (is_smb_in_str(all->gnl_line[ps->pos], SHARE_SMB, 0))
		ps->pos++;
	if (all->gnl_line[ps->pos] != '\0')
	{
		all->tok->args = NULL;
		if (is_smb_in_str(all->gnl_line[ps->pos], "><", 0))
			redirect(all, all->gnl_line, &all->tok->redirect, ps);
		arg_ret = arguments(all, all->gnl_line, ps);
		if (arg_ret == 1 || arg_ret == -1)
			return (arg_ret == 1 ? 1 : -1);
	}
	else
		return (1);
	return (0);
}
