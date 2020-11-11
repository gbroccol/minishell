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

// void			clear_parsing_env(t_env *ps_env)
// {
	// ps_env->tmp = 0;


	// ps_env->env_line = 0;
	// ps_env->env_start = 0;

	// ps_env->env_len = 0;

	// ps_env->sp_smb = 0;

	// ps_env->str_len = 0; // old str without env
	// ps_env->pre_env = 0;
	// ps_env->after_env = 0;

	// ps_env->full_len = 0;
	// return (ps_env);
// }

// void			clear_parsing(t_pars *ps, int clear_pos)
// {
// 	if (clear_pos)
// 	{
// 		ps->pos = 0;
// 		if(!(ps->ps_env = (t_env *)(malloc(sizeof(t_env)))))
// 			return ; // error
// 	}
		
// 	ps->tmp_pos = 0;

// 	ps->quote_start = 0;
// 	ps->quote_finish = 0;

// 	ps->space = 0;

	// ps->env_line = 0;
	// ps->env_start = 0;
	// ps->env_len = 0;
// 	clear_parsing_env(ps->ps_env);
// }

t_all			*clear_all()
{
	t_all		*all;

	if (!(all = malloc(sizeof(t_all))))
		return (NULL);							// errror
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
	

	if(!(all->ps = (t_pars *)(malloc(sizeof(t_pars)))))
		return (NULL);
	all->ps->pos = 0;
	all->ps->tmp_pos = 0;
	all->ps->index = 0;
	all->ps->quote_start = 0;
	all->ps->quote_finish = 0;
	all->ps->space = 0;



	if(!(all->ps->ps_env = (t_env *)(malloc(sizeof(t_env)))))
			return (NULL); // error
	all->ps->ps_env->env_line = 0;
	all->ps->ps_env->env_pos = 0;
	all->ps->ps_env->str_pos = 0;
	all->ps->ps_env->str = NULL;

	if(!(all->er = (t_error *)(malloc(sizeof(t_error)))))
			return (NULL); // error
	all->er->syntax = 0;
	// all->er->token = NULL;

	return (all);
}
