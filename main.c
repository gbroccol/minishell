/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:41:00 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/16 18:24:58 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BUFFER_SIZE 32

static int		mem_free(char **remember)
{
	free(*remember);
	return (-1);
}

static char		*ft_find_n(char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == '\n')
			return (str);
		str++;
	}
	return (NULL);
}

static int		get_line(char **line, char **remember)
{
	int			n_yes;
	char		*tmp;
	int			remember_len;
	int			line_len;


	tmp = NULL;
	remember_len = ft_strlen_n(*remember, '\0');
	if ((n_yes = ft_find_n(*remember) ? 1 : 0))
		line_len = ft_strlen_n(*remember, '\n');
	else
		line_len = remember_len;

	if (!(*line = ft_substr(*remember, 0, line_len)))
		return (mem_free(remember));
	if (n_yes && (remember_len - line_len - 1) > 0)
	{
		if (!(tmp = ft_substr(*remember, line_len + 1, remember_len - line_len - 1)))
			return (mem_free(remember));
	}
	else
		tmp = NULL;
	free(*remember);
	*remember = NULL;
	*remember = tmp;
	return (n_yes);
}

static char		*write_surplus(char **s_fd, char *buf)
{
	char		*result;

	result = NULL;
	if (!*s_fd)
		return (ft_strdup(buf));
	result = ft_strjoin(*s_fd, buf);
	free(*s_fd);
	return (result);
}

void			rewrite_eof(char **str)
{
	int			i;

	i = ft_strlen(*str);
	*str[i] = '\0';
	*str[i - 1] = '\0';
}

int				get_next_line_dif(int fd, char **line)
{
	static char	*s_fd[2000];
	char		buf[BUFFER_SIZE + 1];
	int			line_len;

	line_len = 0;
	if (fd < 0 || fd > 1999 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	*line = NULL;
	if (!ft_find_n(s_fd[fd]))
	{
		while ((line_len = read(fd, buf, BUFFER_SIZE)) >= 0)
		{
			buf[line_len] = '\0';
			write(0, "  \b\b", 4);
			s_fd[fd] = write_surplus(&s_fd[fd], buf);
			if (buf[0] == '\0' && s_fd[fd][0] == '\0' && line_len == 0)
				return (2);
			if (ft_find_n(buf) || !s_fd[fd])
				break ;
		}
	}
	return ((line_len < 0 || !s_fd[fd]) ? (-1) : (get_line(line, &s_fd[fd])));
}

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

void		print_array(char **ar)
{
	int		i;

	i = 0;
	while (ar && ar[i] != NULL)
	{
		write(1, "array-> ", 8);
		write(1, ar[i], ft_strlen(ar[i]));
		write(1, "\n", 1);
		i++;
	}
}

void	creat_files(t_pars *ps)
{
	int	i;
	int	fd;

	i = 0;
	
	// print_array(ps->red_files);
	// write(1, "__________\n", 11);
	// check if stop creating
	
	while (ps->red_files && ps->red_files[i])
	{
		// write(1, ps->red_files[i], ft_strlen(ps->red_files[i]));
		i++;
		if (ps->red_files[i])
		{
			// write(1, ps->red_files[i], ft_strlen(ps->red_files[i]));
			fd = open(ps->red_files[i], O_CREAT, 0666);
			close(fd);
			i++;
		}
	}
}

void	write_redir_files(t_all *all, char *str, t_pars *ps)
{
	while (is_smb_in_str(str[ps->pos], ";\'\"", 1) == 0)
	{
		// if (is_smb_in_str(str[ps->pos], "<>", 0))
		if (is_smb_in_str(str[ps->pos], ">", 0))
		{
			if (ps->pos > 0 && str[ps->pos - 1] == '\\')
				ps->pos = ps->pos + 2;
			else
				redirect(all, str, &ps->red_files, ps);
		}
		else
			ps->pos++;
	}
	while (is_smb_in_str(str[ps->pos], " \t\a", 1) == 0)
		ps->pos++;
}

int	check_redir_files(t_all *all, char *str, t_pars *ps)
{
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
	

	// print_array(ps->red_files);
	// write(1, "__________\n", 11);
	
	
	creat_files(ps);
	
	// if (ps->red_files)
	// 	ft_free_array(ps->red_files);
	// ps->red_files = NULL;
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
		if (signal(SIGINT, listener) == SIG_ERR || signal(SIGQUIT, listener) == SIG_ERR)
			exit(all->status);
		while (status)
		{
			if (get_next_line_dif(0, &(all->gnl_tmp)) == 2)
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
			{
				all->ret_pars = parsing(all, all->ps); // 1 - stop parsing 0 - continue parsing
			}
	
			print_array(all->tok->redirect);
			write(1, "__________\n", 11);
			
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