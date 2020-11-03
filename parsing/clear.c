
#include "../minishell.h"

void			clear_parsing_env(t_env *ps_env)
{
	// ps_env->tmp = 0;


	ps_env->env_line = 0;
	// ps_env->env_start = 0;

	// ps_env->env_len = 0;

	// ps_env->sp_smb = 0;

	// ps_env->str_len = 0; // old str without env
	// ps_env->pre_env = 0;
	// ps_env->after_env = 0;

	// ps_env->full_len = 0;
	// return (ps_env);
}

void			clear_parsing(t_pars *ps, int clear_pos)
{
	if (clear_pos)
	{
		ps->pos = 0;
		if(!(ps->ps_env = (t_env *)(malloc(sizeof(t_env)))))
			return ; // error
	}
		
	ps->tmp_pos = 0;

	ps->quote_start = 0;
	ps->quote_finish = 0;

	ps->space = 0;

	// ps->env_line = 0;
	// ps->env_start = 0;
	// ps->env_len = 0;
	clear_parsing_env(ps->ps_env);
}

t_all			*clear_all()
{
	t_all		*all;

	if (!(all = malloc(sizeof(t_all))))
		return (NULL);							// errror
	all->ret_ex = 1;
	all->ret_pars = 0;
	all->gnl_line = NULL;
	all->env = NULL;
	all->toks = NULL;
	all->status = 0;
	if(!(all->ps = (t_pars *)(malloc(sizeof(t_pars)))))
		return (NULL);
	clear_parsing(all->ps, 1);
	return (all);
}
