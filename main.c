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

void			lsh_loop(void)
{
	char		*line;
	int			status;
	int			ret_parsing;
	t_tokens	*tok;
	t_pars		*pars_inf;

	line = NULL;
	status = 1;
	ret_parsing = 0;
	// tok = NULL; // ???
	// pars_inf = NULL;
	while (status)
	{
        write(1, "> ", 2);
	    get_next_line(0, &line);
		if (ret_parsing == 0)
		{
			tok = (t_tokens *)(malloc(sizeof(t_tokens))); // обработать ошибки ЛИШНИЕ ТОКЕНЫ  // ???
			pars_inf = (t_pars *)(malloc(sizeof(t_pars)));
			pars_inf->quote_finish = 0;
			pars_inf->quote_start = 0;
		}
		ret_parsing = parsing(line, tok, pars_inf); // функция для разбиения строки на аргументы
		if (ret_parsing == 0)
			status = execute(tok); // исполняются аргументы
		free(line); // освобождается память, выделенная под строку и аргументы
	}
	exit(EXIT_SUCCESS);
}

int				main()
{
	// Загрузка файлов конфигурации при их наличии.
	// Запуск цикла команд.
	lsh_loop(); // циклически интерпретирует команды
	// Выключение / очистка памяти.
	return EXIT_SUCCESS;
}

// https://github.com/ska42/minishell/blob/master/includes/utils.h
