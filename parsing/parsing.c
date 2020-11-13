/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:33:48 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/13 17:44:28 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		clear_token_again(t_token *tok)
{
	tok->type_func = -1;
	tok->cmd = NULL;
	tok->args = NULL;
	tok->redirect = NULL;
	tok->pipe = 0;
	tok->tmp = NULL;
	tok->tmp2 = NULL;
	tok->flag_n = 0;
}

int				parsing(t_all *all, t_pars *ps)
{
	clear_token_again(all->tok);
	while (is_smb_in_str(all->gnl_line[ps->pos], SHARE_SMB, 0))
		ps->pos++;
	if (all->gnl_line[ps->pos] != '\0')
	{
		all->wait_cmd = 0;
		all->tok->args = NULL;
		if (is_smb_in_str(all->gnl_line[ps->pos], "><", 0))
			redirect(all, all->gnl_line, all->tok); 
		if (arguments(all, all->gnl_line, ps))
			return (1); // 1 - stop parsing
	}
	else
		return(1);
	return (0); // 0 - continue parsing
}
