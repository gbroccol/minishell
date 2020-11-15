/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 16:59:01 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/15 15:14:25 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exit_all_tok(t_token *tok)
{
	if (tok->cmd)
		free(tok->cmd);
	tok->cmd = NULL;
	if (tok->args)
		ft_free_array(tok->args);
	tok->args = NULL;
	if (tok->redirect)
		ft_free_array(tok->redirect);
	tok->redirect = NULL;
	
}

void		exit_all_ps(t_pars *ps)
{
	if (ps->status)
		free(ps->status);
	ps->status = NULL;
	if (ps->env_str)
		free(ps->env_str);
	ps->env_str = NULL;
	if (ps->tmp)
		free(ps->tmp);
	ps->tmp = NULL;
	if (ps->tmp2)
		free(ps->tmp2);
	ps->tmp2 = NULL;
}

void exit_all(t_all *all)
{
	if (all->gnl_line)
		free(all->gnl_line);
	all->gnl_line = NULL;
	if (all->gnl_tmp)
		free(all->gnl_tmp);
	all->gnl_tmp = NULL;
	if (all->env)
		ft_free_array(all->env);
	all->env = NULL;
	close(all->fds[0]);
	close(all->fds[1]);
	if (all->home)
		free(all->home);
	all->home = NULL;
	exit_all_tok(all->tok);
	free(all->tok);
	all->tok = NULL;
	exit_all_ps(all->ps);
	free(all->ps);
	all->ps = NULL;
}