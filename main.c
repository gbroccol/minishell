/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:41:00 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/03 20:55:09 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			lsh_loop(t_all *all)
{
	while (all->ret_ex)
	{
        write(1, "\x1b[1;32mminishell> \x1b[0m", 22);
	    get_next_line(0, &(all->gnl_line));
		all->ps->pos = 0;
		all->ret_pars = 1;
		while (all->ret_pars)
		{
			all->ps->tmp_pos = 0;
			all->ps->index = 0;
			all->ps->quote_start = 0;
			all->ps->quote_finish = 0;
			all->ps->space = 0;

			all->ps->ps_env->env_line = 0;
			all->ps->ps_env->env_pos = 0;
			all->ps->ps_env->str_pos = 0;
			all->ps->ps_env->str = NULL;


			all->ret_pars = parsing(all, all->ps);
			all->ret_ex = execute(all);
			// free_toks(toks);
			free(all->tok);
			all->tok = NULL;
		}
		free(all->gnl_line);
	}
	exit(all->status);
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

char	**save_env(char **envp, int size)
{
	char 	**env;
	int 	i;

	while (envp[size] != NULL)
		size++;
	if (!(env = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	bzero_array(env, size);
	i = 0;
	while (i < size && envp[i])
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
 	t_all		*all;

	all = clear_all();
	if (argc == 1)
		argv[1] = "minishell"; // костыль
	if (!(all->env = save_env(envp, 0)))
		return (EXIT_FAILURE);
	lsh_loop(all);
	ft_free_array(all->env);
	free(all->ps);
  	free(all);
	return (EXIT_SUCCESS);
}
