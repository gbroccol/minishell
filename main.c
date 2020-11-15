/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:41:00 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/15 17:12:06 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_array(char **ar)
{
	int		i;

	i = 0;
	while (ar && ar[i] != NULL)
	{
		write(1, ar[i], ft_strlen(ar[i]));
		write(1, "\n", 1);
		i++;
	}
}

void	write_redir_files(t_all *all, char *str, t_pars *ps)
{
	while (is_smb_in_str(str[ps->pos], ";\'\"", 1) == 0)
	{
		if (is_smb_in_str(str[ps->pos], ">", 0))
			redirect(all, str, &ps->red_files, ps);
		else
			ps->pos++;
	}
	// print_array(all->ps->red_files); // test
	// write(1, "__________\n", 11); // test
}

int	check_redir_files(t_all *all, char *str, t_pars *ps)
{
	if (ps->red_files)
		ft_free_array(ps->red_files);
	ps->red_files = NULL;
	while (str[ps->pos] != '\0' && str[ps->pos] != ';')
	{
		if (str[ps->pos] == '\'')
		{
			ps->pos++;
			while (str[ps->pos] != '\'' && str[ps->pos] != '\0')
				ps->pos++;
			if (str[ps->pos] == '\'')
				ps->pos++;
		}
		else if (str[ps->pos] == '\"')
		{
			ps->pos++;
			while (str[ps->pos] != '\"' && str[ps->pos] != '\0')
				ps->pos++;
			if (str[ps->pos] == '\"')
				ps->pos++;
		}
		else
			write_redir_files(all, str, ps);
	}
	if (str[ps->pos] == ';')
		ps->pos++;
	return (all->ps->pos);
}


int		loop(t_all *all)
{
	int		status;
	int		tmp_pos;

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
		all->ps->red_pos = 0;
		while (!all->ret_pars && !all->syntax)
		{
			all->ps->status = ft_itoa(all->status);
			all->ps->env_str_pos = 0;
			all->ps->env_str = NULL;
			
			if ((all->ps->red_pos == 0 && all->ps->pos == 0) || all->ps->red_pos < all->ps->pos)
			{
				tmp_pos = all->ps->pos;
				all->ps->red_pos = check_redir_files(all, all->gnl_line, all->ps);
				all->ps->pos = tmp_pos;


				// print_array(all->ps->red_files);
				// write(1, "__________\n", 11);
			}
			
			if (!all->ps->er_redir)
				all->ret_pars = parsing(all, all->ps); // 1 - stop parsing 0 - continue parsing
			
				// print_array(all->tok->redirect);
				// write(1, "__________\n", 11);
			
			if (!all->ps->er_redir)
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