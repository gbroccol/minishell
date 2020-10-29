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
		all->ret_pars = parsing(all->gnl_line, &all->toks, all->ps);
		if (all->ret_pars == 0)
		{
			all->ret_ex = execute(all->toks);
			// free_toks(toks);
		}
		free(all->gnl_line);
	}
	exit(EXIT_SUCCESS);
}

int				main()
{
	t_all		*all;

	all = clear_all();
	lsh_loop(all);
	free(all);
	free(all->ps);
	return EXIT_SUCCESS;
}
