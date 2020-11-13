/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:30:52 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/12 20:25:58 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			replace_env(t_all *all, char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[size] != '=' && str[size] != '\0')
		size++;
	while (all->env[i] != NULL)
	{
		if (!ft_strncmp(str, all->env[i], size) &&
		ft_strchr(str, '='))
		{
			free(all->env[i]);
			if (!(all->env[i] = ft_strdup(str)))
				return (-1);
			i = 0;
			break ;
		}
		i++;
	}
	return (i);
}

// static int		print_env(char **env, int i, int j, int ascii_nmb)
// {
// 	// int			size;

// 	while (ascii_nmb >= 32 && ascii_nmb <= 126)
// 	{
// 		while (env[i] != NULL)
// 		{
// 			if (env[i][j] == ascii_nmb && print_env(env, i, j + 1, ascii_nmb))
// 			{
// 				if (env[i][0] != '\0')
// 				{
// 					write(1, env[i], ft_strlen(env[i]));
// 					// size = 0;
// 					// while (env[i][size] != '=' && env[i][size] != '\0')
// 					// 	size++;
// 					// size++;
// 					// if (size > 1)
// 					// {
// 					// 	write(1, "declare -x ", 11);
// 					// 	write(1, env[i], size);
// 					// 	if ((ft_strlen(env[i]) - size) > 0)
// 					// 	{
// 					// 		write(1, "\"", 1);
// 					// 		write(1, env[i] + size, ft_strlen(env[i]) - size);
// 					// 		write(1, "\"", 1);
// 					// 	}
// 						write(1, "\n", 1);
// 					// }
// 				}
				
// 			}
// 			i++;
// 		}
// 		i = 0;
// 		ascii_nmb++;
// 	}
// 	return (0);
// }


static void		print_env(char **env)
{
	int			i;
	int			j;
	int			size;
	int			ascii_nmb;

	ascii_nmb = 32;
	j = 0;
	while (ascii_nmb >= 32 && ascii_nmb <= 126)
	{
		i = 0;
		while (env[i] != NULL)
		{
			if (env[i][j] == ascii_nmb)
			{
				size = 0;
				while (env[i][size] != '=' && env[i][size] != '\0')
					size++;
				size++;
				if (size > 1)
				{
					write(1, "declare -x ", 11);
					write(1, env[i], size);
					if ((ft_strlen(env[i]) - size) > 0)
					{
						write(1, "\"", 1);
						write(1, env[i] + size, ft_strlen(env[i]) - size);
						write(1, "\"", 1);
					}
					write(1, "\n", 1);
				}
			}
			i++;
		}
		ascii_nmb++;
	}
}

// static void		print_env_pre(char **env)
// {
// 	int			i;
// 	// int			size;

// 		i = 0;
// 		while (env[i] != NULL)
// 		{
// 			write(1, env[i], ft_strlen(env[i]));
// 			write(1, "\n", 1);
// 			i++;
// 		}
// }

int			shell_export(t_token *token, t_all *all)
{
	int		i;
	int		j;
	int		status;

	i = 0;
	j = 1;
	status = 0;
	// print_env_pre(all->env);
	if (!token->args[j])
		print_env(all->env);
	else
	{
		while (token->args[j] != NULL)
		{
			if ((i = replace_env(all, token->args[j])) < 0)
				return (1);
			if ((i != 0) || (token->args[j][0] = '='))
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
