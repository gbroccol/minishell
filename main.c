/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:41:00 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/19 17:41:02 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void lsh_loop(void)
{
	char *line; // привет Катя!
	int status;
    int gnl_ret;
	int ret_parsing;
	t_tokens	tok;

	line = NULL;
	status = 1;
    gnl_ret = 1;
	ret_parsing = 0;
	while (status)
	{
        write(1, "> ", 2);
	    gnl_ret = get_next_line(0, &line);
		// if (gnl_ret != -1)
		// {
			ret_parsing = parsing(line, &tok, ret_parsing); // функция для разбиения строки на аргументы
			if (ret_parsing == 0)
				status = execute(&tok); // исполняются аргументы
			free(line); // освобождается память, выделенная под строку и аргументы
		// }
	}
	exit(EXIT_SUCCESS);
}

int main()
{
	// Загрузка файлов конфигурации при их наличии.
	// Запуск цикла команд.
	lsh_loop(); // циклически интерпретирует команды
	// Выключение / очистка памяти.
	return EXIT_SUCCESS;
}

// https://github.com/ska42/minishell/blob/master/includes/utils.h