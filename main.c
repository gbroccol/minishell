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
	char *line;
	char **args;
	int status;
    int gnl_ret;
    int fd;

	line = NULL;
	status = 1;
    gnl_ret = 1;
    fd = open("bash1.sh", O_RDONLY);
	while (status)
	{
        write(1, "> ", 2);
	    gnl_ret = get_next_line(1, &line);
		args = lsh_split_line(line); // функция для разбиения строки на аргументы
		status = lsh_execute(args); // исполняются аргументы
		free(line); // освобождается память, выделенная под строку и аргументы
		free(args);
	}
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