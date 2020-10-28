# include "../minishell.h"

t_tokens		*clear_tokens()
{
	t_tokens	*tok;

	if (!(tok = (t_tokens *)malloc(sizeof(t_tokens))))
			return (NULL);  // обработать ошибку
	tok->type_func = -1;
	tok->arg = NULL;
	tok->file = NULL;
	tok->quote = 0;
	tok->flag_n = 0;
	tok->flag_l = 0;
	tok->flag_a = 0;
	tok->redir_right = 0;
	tok->redir_2right = 0;
	tok->redir_left = 0;
	tok->next = NULL;

	tok->pars.comment = 0;
	return (tok);
}

void	ft_lstadd_back_tokens(t_tokens **lst, t_tokens *new)
{
	t_tokens *tmp;

	if (!lst || !new)
		return ;
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

int				parsing(char *line, t_tokens *toks, t_pars *pars_inf)
{
	int			position;
	t_tokens	*tok_next;

	position = 0;
	while (1)
	{
		tok_next = clear_tokens();
		position = command(line, position, tok_next, toks, pars_inf);
		position = parsing_echo(line, position, tok_next, pars_inf);
		ft_lstadd_back_tokens(&toks, tok_next);
		if (position == -1)  // не нашла закрыв ковычку
			return (1);
		if (line[position] != '\0')
			position++;
		if (toks->pars.comment == 1)
			break ;
		if (line[position] == '\0')
			break ;
	}
	return (0);
}
