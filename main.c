/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:41:00 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/29 11:37:16 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			lsh_loop(t_all *all)
{
	while (all->ret_ex)
	{
        write(1, "> ", 2);
	    get_next_line(0, &(all->gnl_line));
		if (all->ret_pars == 0)
		{
			all->toks = NULL;
			clear_parsing(all->ps, 1);
		}
		all->ret_pars = parsing(all, &all->toks, all->ps);
		if (all->ret_pars == 0)
		{
			all->ret_ex = execute(all->toks, all->env);
			// free_toks(toks);
		}
		free(all->gnl_line);
	}
	exit(EXIT_SUCCESS);
}

void	ft_free_array(char **to_free)
{
	char **tmp;

	tmp = to_free;
	while (*tmp != NULL)
	{
		free(*tmp);
		tmp++;
	}
	free(to_free);
}

void	bzero_array(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		array[i] = NULL;
		i++;
	}
	array[i] = NULL;
	i = 0;
}

char	**save_env(char **envp)
{
	char 	**env;
	int 	i;
	int		size;

	size = 0;
	while (envp[size] != NULL)
		size++;
	if (!(env = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	bzero_array(env, size);
	i = 0;
	while (i < size)
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

int main(int argc, char **argv, char **envp)
{
	// char    **env;
  t_all		*all;

	all = clear_all();
	if (argc == 1)
		argv[1] = "minishell";
	if (!(all->env = save_env(envp)))
		return (EXIT_FAILURE);
	lsh_loop(all);


	ft_free_array(all->env);
	free(all->ps);
  	free(all);
	return (EXIT_SUCCESS);
}
