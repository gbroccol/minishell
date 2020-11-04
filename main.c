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

void			free_tok(t_token *tok)
{
	// if (tok->cmd)
	// 	free(tok->cmd);
	// if (tok->flags)
	// 	free(tok->flags);
	// if (tok->arg != NULL)
	// 	free(tok->arg);
	// if (tok->redir)
	// 	free(tok->redir);
	// if (tok->file)
	// 	free(tok->file);
	// if (tok->type_func == TYPE_BIN)
	// 	ft_free_array(tok->bin_tok);
	if (tok->args != NULL)
		ft_free_array(tok->args);
	tok->args = NULL;
	free(tok);
}

void			lsh_loop(t_all *all)
{
	int i;

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
			all->ps->status = ft_itoa(all->status);

			all->ps->ps_env->env_line = 0;
			all->ps->ps_env->env_pos = 0;
			all->ps->ps_env->str_pos = 0;
			all->ps->ps_env->str = NULL;


			all->ret_pars = parsing(all, all->ps);


			i = 0;
			while (all->tok->args != NULL && all->tok->args[i])
			{
				printf("%s\n", all->tok->args[i]);
				i++;
			}
			


			// all->ret_ex = execute(all);
			free_tok(all->tok);  // вопрос по очистке КАТЯ (обсудить)
			all->tok = NULL;
			// free(all->ps->status);
		}
		free(all->gnl_line);
		all->gnl_line = NULL;
	}
	exit(all->status);
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
		argv[1] = "minishell";
	if (!(all->env = save_env(envp, 0)))
		return (EXIT_FAILURE);
	lsh_loop(all);
	ft_free_array(all->env);
	free(all->ps);
  	free(all);
	return (EXIT_SUCCESS);
}



// подсветка синтаксиса при выводе ls (нужно ?)
