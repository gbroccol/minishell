/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:52:43 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/18 18:03:19 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		creat_files(t_pars *ps)
{
	int			i;
	int			fd;

	i = 0;
	while (ps->red_files && ps->red_files[i])
		if (ft_strcmp(ps->red_files[i], "<") == 0)
		{
			if ((fd = open(ps->red_files[i], O_RDONLY, 0666) < 0))
				break ;
			close(fd);
			i++;
			if (ps->red_files[i] != NULL)
				i++;
			continue ;
		}
		else
		{
			i++;
			if (ps->red_files[i])
			{
				fd = open(ps->red_files[i], O_CREAT, 0666);
				close(fd);
				i++;
			}
		}
}

static int		write_redir_files(t_all *all, char *str, t_pars *ps)
{
	while (is_smb_in_str(str[ps->pos], ";\'\"", 1) == 0)
	{
		if (is_smb_in_str(str[ps->pos], "<>", 0))
		{
			if (ps->pos > 0 && str[ps->pos - 1] == '\\')
				ps->pos = ps->pos + 2;
			else
			{
				if ((redirect(all, str, &ps->red_files, ps)) == -1)
					return (-1);
			}
		}
		else
			ps->pos++;
	}
	while (is_smb_in_str(str[ps->pos], " \t\a", 1) == 0)
		ps->pos++;
	return (0);
}

static void		skip_space(char *str, t_pars *ps, char smb)
{
	if (str[ps->pos] == smb)
	{
		ps->pos++;
		while (str[ps->pos] != smb && str[ps->pos] != '\0')
			ps->pos++;
		if (str[ps->pos] == smb)
			ps->pos++;
	}
}

int				check_redir_files(t_all *all, char *str, t_pars *ps)
{
	ps->red_files = NULL;
	while (str[ps->pos] != '\0' && str[ps->pos] != ';')
	{
		if (str[ps->pos] == '\"')
			skip_space(str, ps, '\"');
		else if (str[ps->pos] == '\'')
			skip_space(str, ps, '\'');
		else
		{
			if ((write_redir_files(all, str, ps)) == -1)
				return (-1);
		}
	}
	if (str[ps->pos] == ';')
		ps->pos++;
	creat_files(ps);
	if (ps->red_files)
		ft_free_array(ps->red_files);
	ps->red_files = NULL;
	return (all->ps->pos);
}
