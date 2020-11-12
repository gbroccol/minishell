/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:30:52 by pvivian           #+#    #+#             */
/*   Updated: 2020/11/12 13:39:34 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**new_str(t_all *all, char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	if (!(tmp = save_env(all->env, 1)))
		return (NULL);
	ft_free_array(all->env);
	all->env = tmp;
	while (all->env[i] != NULL)
		i++;
	if (!(all->env[i] = ft_strdup(str)))
		return (NULL);
	return (all->env);
}

char		**new_env(t_all *all, char *str)
{
	int		i;

	i = 0;
	while (all->env[i] != NULL)
	{
		if (ft_strlen(all->env[i]) == 0)
		{
			if (!(all->env[i] = ft_strdup(str)))
				return (NULL);
			i = 0;
			break ;
		}
		i++;
	}
	if (i != 0)
		return (new_str(all, str));
	return (all->env);
}

static int	check_env_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (if_smb_in_str(str[i], WRONG_ENV_SMB))
			return (1);
		i++;
	}
	return (0);
}

int			check_new_env(t_all *all, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=' || ft_isdigit(str[i]) || check_env_key(str))
	{
		write(1, "bash: export: `", 15);
		write(1, str, ft_strlen(str));
		write(1, "': not a valid identifier\n", 26);
		all->status = 1;
		return (1);
	}
	return (0);
}

void		update_home(t_all *all, char *str)
{
	if (!ft_strncmp(str, "HOME=", 5))
	{
		free(all->home);
		all->home = ft_strdup(str);
	}
}
