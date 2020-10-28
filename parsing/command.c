# include "../minishell.h"

void		choose_com(char *new_line, int position, t_tokens *tok_next)
{
	if ((ft_strncmp_nc(new_line, "cd", position)) == 0)
		tok_next->type_func = TYPE_CD;
	else if ((ft_strncmp_nc(new_line, "pwd", position)) == 0)
		tok_next->type_func = TYPE_PWD;
	else if ((ft_strncmp_nc(new_line, "echo", position)) == 0)
		tok_next->type_func = TYPE_ECHO;
	else if ((ft_strncmp_nc(new_line, "exit", position)) == 0)
		tok_next->type_func = TYPE_EXIT;
	else if ((ft_strncmp_nc(new_line, "export", position)) == 0)
		tok_next->type_func = TYPE_EXPORT;
	else if ((ft_strncmp_nc(new_line, "env", position)) == 0)
		tok_next->type_func = TYPE_ENV;
	else if ((ft_strncmp_nc(new_line, "unset", position)) == 0)
		tok_next->type_func = TYPE_UNSET;
	else if ((ft_strncmp_nc(new_line, "", position)) == 0)
		tok_next->type_func = TYPE_NO;
	else
		tok_next->type_func = TYPE_ERROR;
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

int			command(char *line, int position, t_tokens *tok_next,
							t_tokens *toks, t_pars *pars_inf)
{
	int		counter;
	char	*new_line; // убрать буффер для больших несущ=ч комманд его не хватит
	int		index;

	if (pars_inf->quote_start != 0)
	{
		the_same_command(toks, tok_next);
		return (position);
	}
	while (check_divide(line[position], " ;\t\r\a", 1))
		position++;
	counter = position;
	while (check_divide(line[position], " ;\t\r\a", 1) == 0)
	{
		if (line[position] != '\0')
			position++;
		else
			break ;
	}
	if (!(new_line = (char *)malloc(sizeof(char) * (position - counter))))
		return (1); // error
	index = 0;
	while (counter + index < position)
	{
		new_line[index] = line[counter + index];
		index++;
	}
	new_line[position] = '\0';
	choose_com(new_line, position, tok_next);
	return (position);
}