/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:30:55 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/18 18:03:51 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_all	*error_malloc(t_all *all)
{
	if (all->ps)
		free(all->ps);
	if (all->tok)
		free(all->tok);
	if (all->home)
		free(all->home);
	if (all->env)
		ft_free_array(all->env);
	if (all)
		free(all);
	return (NULL);
}

static t_pars	*clear_all_ps(void)
{
	t_pars		*ps;

	if (!(ps = (t_pars *)(malloc(sizeof(t_pars)))))
		return (NULL);
	ps->pos = 0;
	ps->status = NULL;
	ps->env_line = 0;
	ps->env_pos = 0;
	ps->env_str_pos = 0;
	ps->env_str = NULL;
	ps->tmp = NULL;
	ps->tmp2 = NULL;
	ps->er_redir = 0;
	ps->red_files = NULL;
	return (ps);
}

static t_token	*clear_all_tok(void)
{
	t_token		*tok;

	if (!(tok = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	tok->type_func = -1;
	tok->cmd = NULL;
	tok->args = NULL;
	tok->redirect = NULL;
	tok->fd_red = NULL;
	tok->pipe = 0;
	tok->flag_n = 0;
	return (tok);
}

void			clear_all_in(t_all *all)
{
	all->syntax = 0;
	all->ret_ex = 1;
	all->ret_pars = 1;
	all->gnl_line = NULL;
	all->gnl_tmp = NULL;
	all->local = NULL;
	all->status = 0;
	all->fds[1] = -1;
	all->fds[0] = -1;
	all->temp_0 = dup(0);
	all->temp_1 = dup(1);
	all->pre_pipe = 0;
}

t_all			*clear_all(char **envp)
{
	t_all		*all;

	all = NULL;
	if (!(all = malloc(sizeof(t_all))))
		return (NULL);
	all->env = NULL;
	all->home = NULL;
	all->tok = NULL;
	all->ps = NULL;
	clear_all_in(all);
	if (!(all->env = save_env(envp, 0)))
		return (error_malloc(all));
	if (!(all->home = search_env(all->env, "HOME=", all)))
		return (error_malloc(all));
	if (!(all->tok = clear_all_tok()))
		return (error_malloc(all));
	if (!(all->ps = clear_all_ps()))
		return (error_malloc(all));
	return (all);
}
