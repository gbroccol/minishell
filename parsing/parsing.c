# include "../minishell.h"

t_tokens		*clear_tokens()
{
	t_tokens	*tok;

	if (!(tok = (t_tokens *)malloc(sizeof(t_tokens))))
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
	// tok->pars.comment = 0;
	tok->next = NULL;
	return (tok);
}

void	ft_lstadd_back_tokens(t_tokens **lst, t_tokens *new)
{
	t_tokens *tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int				parsing(t_all *all, t_tokens **toks, t_pars *ps)
{
	t_tokens	*tok_next;
	int			ret_arg;

	ps->pos = 0;
	ret_arg = 0;
	while (1)
	{
		tok_next = clear_tokens();
		command(all->gnl_line, tok_next, *toks, ps);
		ret_arg = arguments(all->gnl_line, tok_next, ps, all->env);
		if (tok_next->type_func == 8)
			create_bin_tok(tok_next);
		ft_lstadd_back_tokens(toks, tok_next);
		// if (ps->pos == -1)
		// 	return (1); // ???
		clear_parsing(ps, 0);
		if (all->gnl_line[ps->pos] == '\0')
			break ;
		if (ret_arg == 0)
			break ;
	}
	return (0);
}
