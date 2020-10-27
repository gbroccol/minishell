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

void		error(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
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
	else if ((ft_strncmp_nc(buf, "", counter)) == 0)
		tok->type_func = 0;
	else
		error(MSG_CMD_NOT_FOUND);
}

int				check_divide(char smb, char *line)
{
	int			i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == smb)
			return (1);
		i++;
	}
	return (0);
}

int			first_com(char *line, t_tokens *tok)
{
	int		counter;
	char	buf[10];
	int		index;

	counter = 0;
	index = 0;
	while (index < 10)
	{
		buf[index] = '\0';
		index++;
	}
	index = 0;
	while (check_divide(line[counter], " ;\t\r\a\0"))
		counter++;
	while (check_divide(line[counter], " ;\t\r\a\0") != 1 && counter < 10)
	{
		buf[index] = line[counter];
		index++;
		counter++;
	}
	buf[9] = '\0';
	choose_com(buf, counter, tok);
	return (counter);
}

char	*ft_str_to_str(char *s1, char *s2)
{
	char	*res;
	char	*s2_tmp;
	int		s1_size;
	int		s2_size;

	if (!s1 || !s2)
		return (NULL);
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	if ((res = malloc(s1_size + s2_size + 2)) == NULL)
		return (NULL);
	ft_strlcpy(res, s1, (size_t)(s1_size + 1));
	s2_tmp = (char *)s2;
	res[s1_size] = ' ';
	s1_size++;
	while (*s2_tmp != '\0')
	{
		res[s1_size] = *s2_tmp;
		s2_tmp++;
		s1_size++;
	}
	res[s1_size] = '\0';
	free(s1);
	free(s2);
	return (res);
}

int				parse_arg(char *line, int pos, t_tokens *tok)
{
	int			tmp_pos;
	char		*tmp_line;
	int			index;

	tmp_line = NULL;
	while (line[pos] == ' ' || line[pos] == '\t')
		pos++;
	while (line[pos] != '\0' && line[pos] != ';')
	{
		if (line[pos] == '-' && line[pos + 1] == 'n')
		{
			tok->flag = 1;
			pos = pos + 2;
			while (line[pos] == ' ' || line[pos] == '\t')
				pos++;
		}
		if (line[pos] == '\'' || line[pos] == '\"')
		{
			tok->quote = line[pos]; 									//	check
			pos++;
		}
		tmp_pos = pos;
		if (tok->quote != 0)
		{
			while (line[pos] != tok->quote && line[pos] != '\0')
			{
				pos++;
			}
		}
		else
		{
			while (check_divide(line[pos], " \t;") == 0 && line[pos] != '\0')
			{
				pos++;
			}
		}
		if (!(tmp_line = (char *)malloc(sizeof(char) * (pos - tmp_pos + 1))))
			return (1);												// error
		index = 0;
		// if (tok->quote != 0)
		// 	tmp_pos++;
		while (index < pos - tmp_pos)
		{
			tmp_line[index] = line[tmp_pos + index];
			index++;
		}
		tmp_line[index] = '\0';
		if (tok->arg)
			tok->arg = ft_str_to_str(tok->arg, tmp_line);
		else
			tok->arg = tmp_line;
		if (tok->quote != 0)
		{
			if (line[pos] == tok->quote)
				pos++;
			else
				return (-1);
		}
		while (check_divide(line[pos], " \t") == 1)
			pos++;
	}
	return (pos);
}

int				parsing(char *line, t_tokens *tok, int ret_parsing)
{
	int			position;
	// t_tokens	*tok_next;
	
	if (ret_parsing == 0)
		clear_tokens(tok);
	position = first_com(line, tok);
	position = parse_arg(line, position, tok);
	if (position == -1)
		return (1);
	while (line[position] != '\0')
	{
		// if (tok_next = (t_tokens *)malloc(sizeof(t_tokens)))
		// 	return (1);
		// clear_tokens(tok_next);
		// position = first_com(line, tok);
		// position = parse_arg(line, position, tok);
		// tok->next = tok_next;
		position++;
	}
	return (0);
}


// void clear_tokens(t_tokens *tok)
// {
// 	tok->type_func = -1;
// 	tok->arg = NULL;
// 	tok->file = NULL;
// 	tok->quote = 0;
// 	tok->flag = 0;
// 	tok->redir_right = 0;
// 	tok->redir_2right = 0;
// 	tok->redir_left = 0;
// 	tok->next = NULL;
// }

// void		choose_com(char *buf, int counter, t_tokens *tok)
// {
// 	if ((ft_strncmp_nc(buf, "cd", counter)) == 0)
// 		tok->type_func = TYPE_CD;
// 	else if ((ft_strncmp_nc(buf, "pwd", counter)) == 0)
// 		tok->type_func = TYPE_PWD;
// 	else if ((ft_strncmp_nc(buf, "echo", counter)) == 0)
// 		tok->type_func = TYPE_ECHO;
// 	else if ((ft_strncmp_nc(buf, "exit", counter)) == 0)
// 		tok->type_func = TYPE_EXIT;
// 	else if ((ft_strncmp_nc(buf, "export", counter)) == 0)
// 		tok->type_func = TYPE_EXPORT;
// 	else if ((ft_strncmp_nc(buf, "env", counter)) == 0)
// 		tok->type_func = TYPE_ENV;
// 	else if ((ft_strncmp_nc(buf, "unset", counter)) == 0)
// 		tok->type_func = TYPE_UNSET;
// }

// int			first_com(char *line, t_tokens *tok)
// {
// 	int		counter;
// 	char	buf[10];

// 	counter = 0;
// 	while (line[counter] != ' ' && line[counter] != ';' && line[counter] != '\t' && 
// 			line[counter] != '\r' && line[counter] != '\a'  && counter < 10)
// 	{
// 		buf[counter] = line[counter];
// 		counter++;
// 	}
// 	choose_com(buf, counter, tok);
// 	return (counter);
// }


// int				parse_arg(char *line, int pos, t_tokens *tok)
// {
// 	int			tmp_pos;
// 	char		*tmp_line;
// 	int			index;

// 	tmp_line = NULL;
// 	while (line[pos] == ' ' || line[pos] == '\t')
// 		pos++;
// 	while (line[pos] != '\0')
// 	{
// 		if (line[pos] == '\'' || line[pos] == '\"')
// 			tok->quote = line[pos]; 									//	check
// 		tmp_pos = pos;
// 		pos++;
// 		while (line[pos] != tok->quote && line[pos] != '\0')
// 			pos++;
// 		if (!(tmp_line = (char *)malloc(sizeof(char) * (pos - tmp_pos))))
// 			return (1);												// error
// 		index = 0;
// 		if (tok->quote != 0)
// 			tmp_pos++;
// 		while (index < pos - tmp_pos)
// 		{
// 			tmp_line[index] = line[tmp_pos + index];
// 			index++;
// 		}
// 		tmp_line[index] = '\0';
// 		// if (tok->arg)
// 		// {
// 		// 	free(tok->arg);
// 		// }
// 		tok->arg = tmp_line;
// 		if (tok->quote != 0)
// 		{
// 			if (line[pos] == tok->quote)
// 				pos++;
// 			else
// 				return (-1);
// 		}
// 		while (line[pos] == ' ' || line[pos] == '\t')
// 			pos++;
// 	}
// 	return (0);
// }

// int				parsing(char *line, t_tokens *tok, int ret_parsing)
// {
// 	int			position;
	
// 	if (ret_parsing == 0)
// 		clear_tokens(tok);
// 	position = first_com(line, tok);
// 	position = parse_arg(line, position, tok);
// 	if (position == -1)
// 		return (1);
// 	return (0);
// }
