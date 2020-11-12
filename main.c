/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:41:00 by gbroccol          #+#    #+#             */
/*   Updated: 2020/11/12 11:08:37 by pvivian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tok(t_token *tok)
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



int		check_str_pipe(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] != '\0')
	{
		while (str[i] != '\0')
			i++;
		while (i > 0 && (str[i] == '\0' || str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
			i--;
		if (str[i] == '|')
			return (1);
		return (0);
	}
	return (0);
}

void	lsh_loop(t_all *all)
{
	// int i;
	int status;
    char    *space;

	status = 1;
	all->wait_cmd = 0;
	all->pre_pipe = 0;
  space = ft_strdup(" ");
	all->home = search_env(all->env, "HOME=");
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
            {
                all->gnl_line = ft_str_to_str(all->gnl_line, space);
                space = ft_strdup(" ");
                all->gnl_line = ft_str_to_str(all->gnl_line, all->gnl_tmp);
            }
            else
			    all->gnl_line = ft_str_to_str(all->gnl_line, all->gnl_tmp);
			all->gnl_tmp = NULL;

            if (check_gnl_line(all->er, all->gnl_line) == 0 || all->er->syntax)
				status = 0;
			else
				write(1, "\x1b[1;32m> \x1b[0m", 13);


			// if (check_str_pipe(all->gnl_line) == 0)
			// 	status = 0;
			// else
			// 	write(1, "\x1b[1;32m> \x1b[0m", 13);
		}
		all->ps->pos = 0;
		all->ret_pars = 1;
		while (all->ret_pars && all->er->syntax == 0)
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

			// printf("**************************************************\n");
			// i = 0;
			// while (all->tok->args != NULL && all->tok->args[i])
			// {
			// 	printf("%s\n", all->tok->args[i]);
			// 	i++;
			// }
			// i = 0;
			// while (all->tok->redirect != NULL && all->tok->redirect[i])
			// {
			// 	printf("redirect* %s\n", all->tok->redirect[i]);
			// 	i++;
			// }
			// printf("__________________________________________________\n");
			all->ret_ex = execute(all);
//			free_tok(all->tok);  // вопрос по очистке КАТЯ (обсудить)
			all->tok = NULL;
			// free(all->ps->status);
			
		}
        status = 1;
        if (all->er->syntax)
        {
            write(1, "bash: syntax error near unexpected token\n", 41);
            // write(1, all->er->token, ft_strlen(all->er->token));
            // write(1, "'\n", 2);
            all->er->syntax = 0;
            // if (all->er->token)
            // {
            //     free(all->er->token);
            //     all->er->token = NULL;
            // }
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
	char	**env;
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	size += i;
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

int		main(int argc, char **argv, char **envp)
{
	t_all	*all;

	all = clear_all();
	if (argc == 1)
		argv[1] = "minishell"; // костыль для argc / argv
	if (!(all->env = save_env(envp, 0)))
		return (EXIT_FAILURE);
	lsh_loop(all);
	ft_free_array(all->env);
	free(all->ps);
	free(all);
	return (EXIT_SUCCESS);
}