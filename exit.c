/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 16:59:01 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/13 17:40:54 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exit_all_tok(t_token *tok)
{
	if (tok->cmd)
		free(tok->cmd);
	if (tok->args)
		ft_free_array(tok->args);
	if (tok->redirect)
		ft_free_array(tok->redirect);
	if (tok->tmp)
		free(tok->tmp);
	if (tok->tmp2)
		free(tok->tmp2);
}

void		exit_all_ps(t_pars *ps)
{
	if (ps->status)
		free(ps->status);
	if (ps->ps_env->str)
		free(ps->ps_env->str);
}

void		exit_all(t_all *all)
{
	if (all->gnl_line)
		free(all->gnl_line);
	all->gnl_line = NULL;
	if (all->gnl_tmp)
		free(all->gnl_tmp);
	if (all->env)
		ft_free_array(all->env);
	close(all->fds[0]);
	close(all->fds[1]);
	if (all->home)
		free(all->home);
	exit_all_tok(all->tok);
	free(all->tok);
	exit_all_ps(all->ps);
	free(all->ps);
	free(all->ps->ps_env);
	free(all);
}