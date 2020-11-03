# include "../minishell.h"

void		choose_com(char *new_line, t_tokens *tok_next)
{
	if ((ft_strncmp(new_line, "cd", 3)) == 0)
		tok_next->type_func = TYPE_CD;
	else if ((ft_strncmp(new_line, "pwd", 4)) == 0)
		tok_next->type_func = TYPE_PWD;
	else if ((ft_strncmp(new_line, "echo", 5)) == 0)
		tok_next->type_func = TYPE_ECHO;
	else if ((ft_strncmp(new_line, "exit", 5)) == 0)
		tok_next->type_func = TYPE_EXIT;
	else if ((ft_strncmp(new_line, "export", 7)) == 0)
		tok_next->type_func = TYPE_EXPORT;
	else if ((ft_strncmp(new_line, "env", 4)) == 0)
		tok_next->type_func = TYPE_ENV;
	else if ((ft_strncmp(new_line, "unset", 6)) == 0)
		tok_next->type_func = TYPE_UNSET;
	else if ((ft_strncmp(new_line, "", 1)) == 0)
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
	char	*new_line;
	int		index;

	if (ps->quote_start != 0 && ps->quote_finish == 0)
		return (the_same_command(toks, tok_next));
	
	while (check_divide(line[ps->pos], " \t\r\a", 1))
		ps->pos++;
	counter = ps->pos;
	while (check_divide(line[ps->pos], " \t\r\a", 1) == 0)
	{
		if (line[ps->pos] != '\0')
			ps->pos++;
		else
			break ;
	}
	if (!(new_line = (char *)malloc(sizeof(char) * (ps->pos - counter + 1))))
	{
		ps->pos = 1;
		return ; // error
	}
	index = 0;
	// ft_memchr(new_line, '\0', (position - counter + 1));
	while (index < (ps->pos - counter + 1))
		new_line[++index] = '\0'; // ???
	index = 0;
	while (counter + index < ps->pos)
	{
		new_line[index] = line[counter + index];
		index++;
	}
	new_line[ps->pos] = '\0';
	choose_com(new_line, tok_next);
	return ;
}