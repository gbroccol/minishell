# include "../minishell.h"

t_token		*clear_tokens()
{
	t_token	*tok;

	if (!(tok = (t_token *)malloc(sizeof(t_token))))
			return (NULL);  // обработать ошибку
	tok->type_func = -1;
	tok->cmd = NULL;
	tok->arg = NULL;
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
	// t_token		*new_tok;

	all->tok = clear_tokens();
	command(all->gnl_line, all->tok, ps);
	arguments(all->gnl_line, all->tok, ps, all->env);
	if (all->tok->type_func == 8)
		create_bin_tok(all->tok);

	// all->tok = all->tok;

	if (all->gnl_line[ps->pos] != '\0')
		return (1);
	return (0);
}
