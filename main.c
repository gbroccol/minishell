/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:41:00 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/18 16:52:37 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	listener(int sig)
{
	if (sig == SIGINT)
	{
		write(0, "\b\b  \n", 5);
		write(1, "\x1b[1;32mminishell> \x1b[0m", 22);
	}
	else if (sig == SIGQUIT)
		write(0, "\b\b  \b\b", 6);
}

int	read_check_str(t_all *all, int status)
{
	all->gnl_tmp = NULL;
	write(1, "\x1b[1;32mminishell> \x1b[0m", 22);
	if (signal(SIGINT, listener) == SIG_ERR || signal(SIGQUIT, listener) == SIG_ERR)
		exit(all->status);
	while (status)
	{
		if (get_next_line(0, &(all->gnl_tmp)) == 2 && all->pre_pipe == 0)
		{
			exit_all(all);
			free(all);
			write(1, "exit\n", 5);
			exit(0);
		}
		if (all->gnl_line)
			all->gnl_line = ft_str_to_str(all->gnl_line, ft_strdup(" "));
		all->gnl_line = ft_str_to_str(all->gnl_line, all->gnl_tmp);
		all->gnl_tmp = NULL;
		if (check_gnl_line(all, all->gnl_line))
			status = 0;
		else
			write(1, "\x1b[1;32m> \x1b[0m", 13);
	}
	return (status);
}

int		loop(t_all *all)
{
	int		status;
	int		tmp_pos;

	status = 1;
	all->ret_pars = 0;
	while (all->ret_ex && all->ret_pars != -1)
	{
		status = read_check_str(all, status);
		all->ps->pos = 0;
		all->ret_pars = 0;
		all->ps->red_pos = 0;
		all->ps->er_redir = 0;
		while (all->ret_pars == 0 && !all->syntax)
		{
			all->ps->status = ft_itoa(all->status);
			all->ps->env_str_pos = 0;
			all->ps->env_str = NULL;
			if ((all->ps->red_pos == 0 && all->ps->pos == 0) || all->ps->red_pos < all->ps->pos)
			{
				tmp_pos = all->ps->pos;
				all->ps->red_pos = check_redir_files(all, all->gnl_line, all->ps);
				if (all->ps->red_pos == -1)
					all->ret_pars = 1;
				all->ps->pos = tmp_pos;
			}
			if (!all->ps->er_redir && all->ret_pars == 0)
				all->ret_pars = parsing(all, all->ps);
			if (!all->ps->er_redir && all->ret_pars != -1)
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
		if (all->ret_pars == -1)
		{
			write(1, "bash: malloc error\n", 19);
			all->status = 1;
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
	if ((all = clear_all(envp)) == NULL)
	{
		write(1, "bash: malloc error\n", 19);
		return (1);
	}
	exit_value = loop(all);
	free(all);
	all = NULL;
	exit(exit_value);
	return (exit_value);
}