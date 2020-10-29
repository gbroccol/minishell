
#include "../minishell.h"

void			clear_parsing(t_pars *ps, int clear_place)
{
	ps->ev_len = 0;
	ps->quote_finish = 0;
	ps->quote_start = 0;
	ps->env_var = 0;
	ps->ev_len = 0;
	if (clear_place)
		ps->place = 0;
}

t_all			*clear_all()
{
	t_all		*all;

	if (!(all = malloc(sizeof(t_all))))
		return (NULL);							// errror
	all->gnl_line = NULL;
	all->ret_pars = 0;
	all->ret_ex = 1;


	all->toks = NULL;


	if(!(all->ps = (t_pars *)(malloc(sizeof(t_pars)))))
		return (NULL);
	clear_parsing(all->ps, 1);



	return (all);
}
