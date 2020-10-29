# include "../minishell.h"

void		choose_com(char *new_line, int position, t_tokens *tok_next)
{
	if ((ft_strncmp(new_line, "cd", position)) == 0)
		tok_next->type_func = TYPE_CD;
	else if ((ft_strncmp(new_line, "pwd", position)) == 0)
		tok_next->type_func = TYPE_PWD;
	else if ((ft_strncmp(new_line, "echo", position)) == 0)
		tok_next->type_func = TYPE_ECHO;
	else if ((ft_strncmp(new_line, "exit", position)) == 0)
		tok_next->type_func = TYPE_EXIT;
	else if ((ft_strncmp(new_line, "export", position)) == 0)
		tok_next->type_func = TYPE_EXPORT;
	else if ((ft_strncmp(new_line, "env", position)) == 0)
		tok_next->type_func = TYPE_ENV;
	else if ((ft_strncmp(new_line, "unset", position)) == 0)
		tok_next->type_func = TYPE_UNSET;
	else if ((ft_strncmp(new_line, "", position)) == 0)
		tok_next->type_func = TYPE_NO;
	else
		tok_next->type_func = TYPE_BIN;
	tok_next->cmd = new_line;
}

void		the_same_command(t_tokens *toks, t_tokens *tok_next)
{
	while (toks->next)
	{
		toks = toks->next;
	}
	tok_next->type_func = toks->type_func;
}

void			command(char *line, t_tokens *tok_next,	t_tokens *toks, t_pars *ps)
{
	int		counter;
	char	*new_line; // убрать буффер для больших несущ=ч комманд его не хватит
	int		index;

	if (ps->quote_start != 0 && ps->quote_finish == 0)
	{
		the_same_command(toks, tok_next);
		return ;
	}
	while (check_divide(line[ps->place], " ;\t\r\a", 1))
		ps->place++;
	counter = ps->place;
	while (check_divide(line[ps->place], " ;\t\r\a", 1) == 0)
	{
		if (line[ps->place] != '\0')
			ps->place++;
		else
			break ;
	}
	if (!(new_line = (char *)malloc(sizeof(char) * (ps->place - counter + 1))))
	{
		ps->place = 1;
		return ; // error
	}
	index = 0;
	// ft_memchr(new_line, '\0', (position - counter + 1));
	while (index < (ps->place - counter + 1))
	{
		new_line[index] = '\0';
		index++;
	}
	index = 0;
	while (counter + index < ps->place)
	{
		new_line[index] = line[counter + index];
		index++;
	}
	new_line[ps->place] = '\0';
	choose_com(new_line, ps->place, tok_next);
	return ;
}