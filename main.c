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

void lsh_loop(char **env)
{
	char *line;
	int status;
 //   int gnl_ret;
	int ret_parsing;
	t_tokens	tok;

	line = NULL;
	status = 1;
 //   gnl_ret = 1;
	ret_parsing = 0;
	while (status)
	{
        write(1, "> ", 2);
//	    gnl_ret = get_next_line(0, &line);
		get_next_line(0, &line);
		// if (gnl_ret != -1)
		// {
			ret_parsing = parsing(line, &tok, ret_parsing); // функция для разбиения строки на аргументы
			if (ret_parsing == 0)
				status = execute(&tok, env); // исполняются аргументы
			free(line); // освобождается память, выделенная под строку и аргументы
		// }
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
	char	**env;

	if (argc == 1)
		argv[1] = "minishell";
	if (!(env = save_env(envp)))
		return (EXIT_FAILURE);
	// Загрузка файлов конфигурации при их наличии.
	// Запуск цикла команд.
	lsh_loop(env); // циклически интерпретирует команды

	// Выключение / очистка памяти.
	ft_free_array(env);
	return (EXIT_SUCCESS);
}

// https://github.com/ska42/minishell/blob/master/includes/utils.h
