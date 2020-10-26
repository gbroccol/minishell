
# include "../minishell.h"

void clear_tokens(t_tokens *tok)
{
	tok->type_func = -1;
	tok->arg = NULL;
	tok->file = NULL;
	tok->quote = 0;
	tok->flag = 0;
	tok->redir_right = 0;
	tok->redir_2right = 0;
	tok->redir_left = 0;
	tok->next = NULL;
}

void		choose_com(char *buf, int counter, t_tokens *tok)
{
	if ((ft_strncmp_nc(buf, "cd", counter)) == 0)
		tok->type_func = TYPE_CD;
	else if ((ft_strncmp_nc(buf, "pwd", counter)) == 0)
		tok->type_func = TYPE_PWD;
	else if ((ft_strncmp_nc(buf, "echo", counter)) == 0)
		tok->type_func = TYPE_ECHO;
	else if ((ft_strncmp_nc(buf, "exit", counter)) == 0)
		tok->type_func = TYPE_EXIT;
	else if ((ft_strncmp_nc(buf, "export", counter)) == 0)
		tok->type_func = TYPE_EXPORT;
	else if ((ft_strncmp_nc(buf, "env", counter)) == 0)
		tok->type_func = TYPE_ENV;
	else if ((ft_strncmp_nc(buf, "unset", counter)) == 0)
		tok->type_func = TYPE_UNSET;
}

int			first_com(char *line, t_tokens *tok)
{
	int		counter;
	char	buf[10];

	counter = 0;
	while (line[counter] != ' ' && line[counter] != ';' && line[counter] != '\t' && 
			line[counter] != '\r' && line[counter] != '\a'  && counter < 10)
	{
		buf[counter] = line[counter];
		counter++;
	}
	choose_com(buf, counter, tok);
	return (counter);
}


int				parse_arg(char *line, int pos, t_tokens *tok)
{
	int			tmp_pos;
	char		*tmp_line;
	int			index;

	tmp_line = NULL;
	while (line[pos] == ' ' || line[pos] == '\t')
		pos++;
	while (line[pos] != '\0')
	{
		if (line[pos] == '\'' || line[pos] == '\"')
			tok->quote = line[pos]; 									//	check
		tmp_pos = pos;
		pos++;
		while (line[pos] != tok->quote && line[pos] != '\0')
			pos++;
		if (!(tmp_line = (char *)malloc(sizeof(char) * (pos - tmp_pos))))
			return (1);												// error
		index = 0;
		if (tok->quote != 0)
			tmp_pos++;
		while (index < pos - tmp_pos)
		{
			tmp_line[index] = line[tmp_pos + index];
			index++;
		}
		tmp_line[index] = '\0';
		// if (tok->arg)
		// {
		// 	free(tok->arg);
		// }
		tok->arg = tmp_line;
		if (tok->quote != 0)
		{
			if (line[pos] == tok->quote)
				pos++;
			else
				return (-1);
		}
		while (line[pos] == ' ' || line[pos] == '\t')
			pos++;
	}
	return (0);
}

int				parsing(char *line, t_tokens *tok, int ret_parsing)
{
	int			position;
	
	if (ret_parsing == 0)
		clear_tokens(tok);
	position = first_com(line, tok);
	position = parse_arg(line, position, tok);
	if (position == -1)
		return (1);
	return (0);
}
