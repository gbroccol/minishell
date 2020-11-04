# include "../minishell.h"

t_token		*clear_tokens()
{
	t_token	*tok;

	if (!(tok = (t_token *)malloc(sizeof(t_token))))
			return (NULL);  // обработать ошибку
	tok->type_func = -1;
	tok->cmd = NULL;
	tok->arg = NULL;
	tok->args = NULL;
	tok->flags = NULL;
	tok->pipe = 0;
	tok->redir = NULL;
	tok->file = NULL;
	tok->flag_n = 0;
	tok->bin_tok = NULL;
	return (tok);
}

int				parsing(t_all *all, t_pars *ps)
{
	int			pars_ret;
	// t_token		*new_tok;
	pars_ret = 1;
	all->tok = clear_tokens();
	while (check_divide(all->gnl_line[ps->pos], " \t\r\a", 1))
		ps->pos++;
	if (all->gnl_line[ps->pos] != '\0')
	{
		command(all->gnl_line, all->tok, ps, all->env);
		pars_ret = arguments(all->gnl_line, all->tok, ps, all->env);
		
		
		if (all->tok->type_func == 8) // rm
			create_bin_tok(all->tok); // rm

		// all->tok = all->tok;

		if (pars_ret == 0) // для комментария
			return (0);

		if (all->gnl_line[ps->pos] != '\0')
			return (1);
	}
	return (0);
}
