/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:41:00 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/20 15:19:05 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	listener(int sig)
{
	if (sig == SIGINT)
	{
		write(0, "\b\b  \n", 5);
		write(1, "\x1b[1;32mminishell> \x1b[0m", 22);
	}
	else if (sig == SIGQUIT)
		write(0, "\b\b  \b\b", 6);
}

int			read_check_str(t_all *all, int status)
{
	all->gnl_tmp = NULL;
	write(1, "\x1b[1;32mminishell> \x1b[0m", 22);
	signal(SIGINT, listener);
	signal(SIGQUIT, listener);
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

int			loop(t_all *all)
{
	all->ret_pars = 0;
	while (all->ret_ex && all->ret_pars != -1)
	{
		read_check_str(all, 1);
		init_parse(all);
		parse_and_exec(all);
		if (all->syntax)
		{
			write(1, "bash: syntax error near unexpected token\n", 41);
			all->syntax = 0;
			all->status = 258;
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

int			main(int argc, char **argv, char **envp)
{
	t_all	*all;
	int		exit_value;

	all = NULL;
	if (argc > 0 && argv && (all = clear_all(envp)) == NULL)
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
