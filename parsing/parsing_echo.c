# include "../minishell.h"

static char		*ft_str_to_str(char *s1, char *s2)
{
	char		*res;
	char		*s2_tmp;
	int			s1_size;
	int			s2_size;

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

static char		*clear_shielding(char *line, t_tokens *tok)
{
	char		*new_line;
	int			index;
	int			tmp;

	index = 0;
	tmp = 0;
	while (line[index] != '\0')
	{
		if (line[index] == '\\' && line[index + 1] == '$')
			tmp++;
		index++;
	}
	if (tmp == 0 || tok->quote != '\"')
		return (line);
	if (!(new_line = (char *)malloc(sizeof(char) * (ft_strlen(line) - tmp + 1))))
		return (NULL);
	index = 0;
	tmp = 0;
	while (line[++index] != '\0')
	{
		if (line[index] == '\\' && line[index + 1] == '$')
			continue ;
		new_line[tmp++] = line[index];
	}
	free(line);
	return (new_line);
}

// static char		*clear_comment(char *line, t_tokens *tok)
// {
// 	char		*new_line;
// 	int			index;
// 	int			tmp;

// 	index = 0;
// 	if (tok->quote == 0)
// 	{
// 		while (line[index] != '\0')
// 		{
// 			if (line[index] == '#' && line[index - 1] != '\\')
// 				break ;
// 			index++;
// 		}
// 		if (line[index] == '#')
// 		{
// 			if (!(new_line = (char *)malloc(sizeof(char) * (index + 1))))
// 				return (NULL);
// 			tmp = 0;
// 			while (tmp < index)
// 			{
// 				new_line[tmp] = line[tmp];
// 				tmp++;
// 			}
// 			new_line[tmp] = '\0';
// 			free(line);
// 			return (new_line);
// 		}	
// 	}
// 	return (line);
// }

int				parsing_echo(char *line, int pos, t_tokens *tok, t_pars *pars_inf)
{
	int			tmp_pos;
	char		*tmp_line;
	int			index;

	tmp_line = NULL;
	while (line[pos] == ' ' || line[pos] == '\t')
		pos++;
	while (1)
	{
		while (1)
		{
			if (line[pos] == '-' && line[pos + 1] == 'n')
			{
				tok->flag_n = 1;
				pos = pos + 2;
				while (line[pos] == ' ' || line[pos] == '\t')
					pos++;
			}
			else
				break ;
		}
		if (pars_inf->quote_start == 0)
			if (line[pos] == '\'' || line[pos] == '\"') // 
			{
				tok->quote = line[pos]; 									//	check
				pars_inf->quote_start = line[pos];
				pos++;
			}
		tmp_pos = pos;
		if (pars_inf->quote_start != 0)
		{
			while (line[pos] != pars_inf->quote_start && line[pos] != '\0')
				pos++;
			if (line[pos] == pars_inf->quote_start)
				pars_inf->quote_finish = 1;
		}
		else
		{
			while (1)
			{
				// write(1, &line[pos], 1);
				// write(1, (&line[pos]), 1);
				// write(1, "\n", 1);
				if (line[pos] == ' ')
					break;
				if (line[pos] == '\'')
					break;
				if (line[pos] == '\"')
					break;
				if (line[pos] == '\t')
					break;
				if (line[pos] == ';')
					break;
				if (line[pos] == '\0')
					break;
				if (line[pos] == '#' && line[pos - 1] != '\\' && tok->quote == 0)
				{
					tok->pars.comment = 1;
					break;
				}
				pos++;
			}
		}
			// while ((check_divide(line[pos], " \t;", 1) == 0))
			// 	pos++;
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
		tmp_line = clear_shielding(tmp_line, tok);
		if (tok->arg)
			tok->arg = ft_str_to_str(tok->arg, tmp_line);
		else
			tok->arg = tmp_line;
		if (pars_inf->quote_start != 0)
		{
			if (line[pos] == pars_inf->quote_start)
				pos++;
			else
				return (-1);
		}
		while (check_divide(line[pos], " \t", 0) == 1)
			pos++;
		if (line[pos] == '\0')
			break ;
		if (line[pos] == ';')
			break ;
		if (tok->pars.comment != 0)
			break;
	}
	return (pos);
}