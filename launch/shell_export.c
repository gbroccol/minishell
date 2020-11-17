/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:30:52 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/17 15:28:11 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		check_line_to_smb(char *ar, char *str, int smb)
{
	int			i;

	i = 0;
	while (ar[i] == str[i] && ar[i] != '\0')
		i++;
	if (smb == 1)
	{
		if (ar[i] == '=')
			return (0);
	}
	else if (smb == 2)
	{
		if (ar[i] == '=' || ar[i] == '\0')
			return (0);
	}
	return (1);
}

static int		find_env(char *line, char **ar, int smb)
{
	int			l_line;

	l_line = 0;
	while (ar && ar[l_line] != NULL)
	{
		if (check_line_to_smb(ar[l_line], line, smb)) // no
		{
			l_line++;
			continue ;
		}
		else
			return (l_line);
	}
	return (-1);
}

int				replace_env(char **array, char *str)
{
	int	i;
	int	size;
	char *arr;

	i = 0;
	size = 0;
	if (!array)
		return (1);
	while (str[size] != '=' && str[size] != '\0')
		size++;
	while (array[i] != NULL)
	{
		arr = array[i];
		if (ft_strchr(str, '=') && !ft_strncmp(str, array[i], size + 1))
		{
			free(array[i]);
			array[i] = NULL;
			if (!(array[i] = ft_strdup(str)))
				return (-1);
			i = 0;
			break ;
		}
		else if (!ft_strchr(str, '=') && !ft_strncmp(str, array[i], size))
			return (0);
		i++;
	}
	return (i);
}

static void		print_env(char **env)
{
	int			i;
	int			size;
	char		**sort_env;

	i = 0;
	sort_env = NULL;
	sort_env = ft_sort_array(env);
	while (sort_env[i] != NULL)
	{
		size = 0;
		while (sort_env[i][size] != '=' && sort_env[i][size] != '\0')
			size++;
		size++;
		if (size > 1)
		{
			write(1, "declare -x ", 11);
			write(1, sort_env[i], size);
			if ((ft_strlen(sort_env[i]) - size) > 0)
			{
				write(1, "\"", 1);
				write(1, sort_env[i] + size, ft_strlen(sort_env[i]) - size);
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		i++;
	}
	if (sort_env)
		ft_free_array(sort_env);
}

int				shell_export(t_token *token, t_all *all)
{
	int		i;
	int		j;
	int		status;
	int		line;

	i = 0;
	j = 1;
	status = 0;
	if (!token->args[j])
		print_env(all->env);
	else
	{
		while (token->args[j] != NULL)
		{
			if (!strchr(token->args[j], '=') && find_env(token->args[j], all->env, 2))
			{
				if ((line = find_env(token->args[j], all->local, 1)) >= 0)
				{
					if (!(new_env(all, all->local[line])))
						return (1);
					all->local = ft_del_str_from_ar(all->local, line);
					j++;
					continue ;
				}
			}
			if ((i = replace_env(all->env, token->args[j])) < 0)
				return (1);
			if ((i != 0) || (token->args[j][0] == '='))
			{
				if (check_new_env(all, token->args[j]) == 0)
				{
					if (!(new_env(all, token->args[j])))
						return (1);
				}
				else
					status = 1;
			}
			update_home(all, token->args[j]);
			j++;
		}
	}
	return (status);
}
