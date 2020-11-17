/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:30:55 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/17 18:48:52 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char			**save_env(char **envp, int size)
{
	char		**env;
	int			i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	size += i;
	if (!(env = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	bzero_array(env, size);
	i = 0;
	while (i < size && envp[i])
	{
		if (!(env[i] = ft_strdup(envp[i])))
		{
			ft_free_array(env);
			return (NULL);
		}
		i++;
	}
	return (env);
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

t_all			*clear_all(char **envp)
{
	t_all		*all;

	if (!(all = malloc(sizeof(t_all))))
		return (NULL);
	all->syntax = 0;
	all->ret_ex = 1;
	all->ret_pars = 1;
	all->gnl_line = NULL;
	all->gnl_tmp = NULL;
	all->env = NULL;
	if (!(all->env = save_env(envp, 0)))
		return (NULL);
	all->local = NULL;
	all->status = 0;
	all->fds[1] = -1;
	all->fds[0] = -1;
	all->temp_0 = dup(0);
	all->temp_1 = dup(1);
	all->pre_pipe = 0;
	all->home = NULL;
	all->home = search_env(all->env, "HOME=");
	all->tok = clear_all_tok();
	all->ps = clear_all_ps();
	return (all);
}
