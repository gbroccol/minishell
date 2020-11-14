/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:41:00 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/13 19:46:53 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		loop(t_all *all)
{
	int		status;

	status = 1;
	
	while (all->ret_ex)
	{
		all->gnl_tmp = NULL;
		write(1, "\x1b[1;32mminishell> \x1b[0m", 22);
		// write(1, "\b\b", 2); - для затирания символов
		if (signal(SIGINT, SIG_IGN) == SIG_ERR || signal(SIGQUIT, SIG_IGN) == SIG_ERR) // прописать ошибки
			exit(all->status);
		while (status)
		{
			get_next_line(0, &(all->gnl_tmp));
			if (all->gnl_line)
				all->gnl_line = ft_str_to_str(all->gnl_line, ft_strdup(" "));
			all->gnl_line = ft_str_to_str(all->gnl_line, all->gnl_tmp);
			all->gnl_tmp = NULL;
			if (check_gnl_line(all, all->gnl_line) == 0 || all->syntax)
				status = 0;
			else
				write(1, "\x1b[1;32m> \x1b[0m", 13);
		}
		all->ps->pos = 0;
		all->ret_pars = 0;
		while (!all->ret_pars && !all->syntax)
		{
			all->ps->status = ft_itoa(all->status);
			all->ps->env_str_pos = 0;
			all->ps->env_str = NULL;
			all->ret_pars = parsing(all, all->ps); // 1 - stop parsing 0 - continue parsing
			if (!all->tok->er_redir)
				all->ret_ex = execute(all);
			if (all->tok)
				exit_all_tok(all->tok);
			if (all->ps)
				exit_all_ps(all->ps);
		}
		status = 1;
		if (all->syntax)
		{
			write(1, "bash: syntax error near unexpected token\n", 41);
			all->syntax = 0;
		}
		if (all->gnl_line)
			free(all->gnl_line);
		all->gnl_line = NULL;
	}
	return (all->status);
}

int		main(int argc, char **argv, char **envp)
{
	t_all	*all;
	int		exit_value;

	if (argc == 1)
		argv[1] = "minishell"; // костыль для argc / argv
	all = clear_all(envp);
	exit_value = loop(all);
	free(all);
	all = NULL;
	exit(exit_value);
	return (EXIT_SUCCESS);
}