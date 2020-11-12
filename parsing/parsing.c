/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:33:48 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/11 19:33:50 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*clear_tokens(void)
{
	t_token		*tok;

	if (!(tok = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	tok->type_func = -1;
	tok->cmd = NULL;
	tok->args = NULL;
	tok->redirect = NULL;
	tok->pipe = 0;
	tok->tmp = NULL;
	tok->tmp2 = NULL;
	tok->flag_n = 0;
	
	// tok->arg = NULL;
	
	// tok->flags = NULL;
	
	// tok->redir = NULL;
	// tok->file = NULL;
	
	// tok->bin_tok = NULL;
	


	
	return (tok);
}

int				parsing(t_all *all, t_pars *ps)
{
	int			pars_ret;

	pars_ret = 1;
	all->tok = clear_tokens();
	while (is_smb_in_str(all->gnl_line[ps->pos], SHARE_SMB, 0))
		ps->pos++;
	if (all->gnl_line[ps->pos] != '\0')
	{
		all->wait_cmd = 0;
		all->tok->args = NULL;
		if (is_smb_in_str(all->gnl_line[ps->pos], "><", 0))
			redirect(all, all->gnl_line, all->tok);
		pars_ret = arguments(all, all->gnl_line, ps);
		command(all->tok);
		if (pars_ret == 0)
			return (0);
		if (all->gnl_line[ps->pos] != '\0')
			return (1);
	}
	return (0);
}
