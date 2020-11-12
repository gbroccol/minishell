/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:30:55 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/11 19:31:06 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pars		*clear_all_ps(void)
{
	t_pars	*ps;

	if (!(ps = (t_pars *)(malloc(sizeof(t_pars)))))
		return (NULL);
	ps->pos = 0;
	return (ps);
}

t_env		*clear_all_ps_env(void)
{
	t_env	*env;

	if (!(env = (t_env *)(malloc(sizeof(t_env)))))
		return (NULL);
	env->line = 0;
	env->pos = 0;
	env->str_pos = 0;
	env->str = NULL;
	return (env);
}

t_all		*clear_all(void)
{
	t_all	*all;

	if (!(all = malloc(sizeof(t_all))))
		return (NULL);
	all->syntax = 0;
	all->ret_ex = 1;
	all->ret_pars = 1;
	all->gnl_line = NULL;
	all->env = NULL;
	all->status = 0;
	all->temp_0 = dup(0);
	all->temp_1 = dup(1);
	all->fds[1] = -1;
	all->fds[0] = -1;
	all->tok = NULL;
	all->ps = clear_all_ps();
	all->ps->ps_env = clear_all_ps_env();
	return (all);
}
