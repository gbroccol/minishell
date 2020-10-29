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
	tok->pars.comment = 0;
	tok->next = NULL;
	return (tok);
}

void	ft_lstadd_back_tokens(t_tokens **lst, t_tokens *new)
{
	t_tokens *tmp;

	// if (!lst || !new)
	// 	return ;
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

int				parsing(char *line, t_tokens **toks, t_pars *ps)
{
	t_tokens	*tok_next;

	ps->place = 0;
	while (1)
	{
		tok_next = clear_tokens();
		command(line, tok_next, *toks, ps);
		parsing_arg(line, tok_next, ps);
		ft_lstadd_back_tokens(toks, tok_next);
		if (ps->place == -1)  // не нашла закрыв ковычку
			return (1);
		if (line[ps->place] != '\0')
			ps->place++;
		clear_parsing(ps, 0);
		// if (toks->pars.comment == 1)
		// 	break ;
		if (line[ps->place] == '\0')
			break ;
	}
	return (0);
}
