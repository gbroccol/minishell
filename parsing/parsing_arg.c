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

static char		*clear_shielding(char *line, t_pars *ps)
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
	if (tmp == 0 || ps->quote_start != '\"')
		return (line);
	// if (tmp == 0 || tok->quote != '\"')
	// 	return (line);
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

static char		*replace_env_variable(char *line, t_pars *ps)
{
	char		*new_line;
	int			index;

	// if ((ft_strncmp(line, "PWD", ps->place)) == 0)
	if (line[ps->place] == 'P')
		if (line[ps->place + 1] == 'W')
			if (line[ps->place + 2] == 'D')
				if (line[ps->place + 3] == '\0' || line[ps->place + 3] == ' ')
				{
					ps->env_var = VAR_PWD;
					ps->ev_len = 4;
				}
	if (!(new_line = (char *)malloc(sizeof(char) * (ft_strlen(line) - ps->ev_len + 5 + 1))))
		return (NULL); // errror
	index = 0;
	ps->place--;
	while (index < ps->place)
	{
		new_line[index] = line[index];
		index++;
	}
	while (index < (ps->place + 5))
	{
		new_line[index] = '1';
		index++;
	}
	while (line[ps->place + ps->ev_len] != '\0')
	{
		new_line[index] = line[ps->place + ps->ev_len];
		index++;
		ps->place++;
	}
	new_line[index] = '\0';
	free(line);
	return (new_line);
}

static char		*find_env_variable(char *line, t_pars *ps)
{
	int			index;

	index = 0;
	while (1)
	{
		while (line[index] != '\0' && line[index] != '$')
			index++;
		if (line[index] == '\0')
			return (line);
		if ((line[index] == '$' && index > 0 && line[index - 1] == '\\') ||
				(ft_isalpha(line[index + 1]) == 0))
			{
				index++;
				continue ;
			}
		index++;
		ps->place = index;
		line = replace_env_variable(line, ps);
		index = 0;
	}
	return (line);
}

int				check_flags(char *line, int pos, t_tokens *tok)
{
	int			index;

	index = pos;
	if (tok->type_func == 3)
	{
		while (line[pos] == '-')
		{
			if (line[pos] == '-' && line[pos + 1] == 'n')
			{
				tok->flag_n = 1;
				pos = pos + 2;
				while (line[pos] == 'n')
					pos++;
				if (line[pos] != ' ' && line[pos] != '\t')
					return (index);
				while (line[pos] == ' ' || line[pos] == '\t')
					pos++;
			}
		}
	}
	else
	{
		while (line[pos] == '-')
		{
			pos++;
			while (ft_isalpha(line[pos]))
			{
				tok->flags = ft_letter_to_str(tok->flags, line[pos], 1);
				pos++;
			}
			while (line[pos] == ' ' || line[pos] == '\t')
				pos++;
		}
	}
	return (pos);
}






























void			parsing_arg(char *line, t_tokens *tok, t_pars *ps)
{
	int			tmp_pos;
	char		*tmp_line;
	int			index;

	tmp_line = NULL;
	while (line[ps->place] == ' ' || line[ps->place] == '\t')
		ps->place++;
	while (1)
	{
		ps->place = check_flags(line, ps->place, tok);
		if (ps->quote_start == 0)			  // ковычки
			if (line[ps->place] == '\'' || line[ps->place] == '\"') // 
			{
				// tok->quote = line[ps->place]; 									//	check
				ps->quote_start = line[ps->place];
				ps->place++;
			}
		tmp_pos = ps->place;
		if (ps->quote_start != 0)  			  // считаю кол-во символов в строчке если есть ковычки
		{
			while (line[ps->place] != ps->quote_start && line[ps->place] != '\0')
				ps->place++;
			if (line[ps->place] == ps->quote_start)
				ps->quote_finish = 1;
		}
		else   										  // считаю кол-во символов в строчке если нет ковычек
		{
			while (1)
			{
				if (line[ps->place] == ' ')
					break;
				if (line[ps->place] == '>')
					break;
				if (line[ps->place] == '<')
					break;	
				if (line[ps->place] == '\'')
					break;
				if (line[ps->place] == '\"')
					break;
				if (line[ps->place] == '\t')
					break;
				if (line[ps->place] == ';')
					break;
				if (line[ps->place] == '\0')
					break;
				if (line[ps->place] == '#' && line[ps->place - 1] != '\\' && ps->quote_start == 0)
				{
					tok->pars.comment = 1;
					break;
				}
				ps->place++;
			}
		}
		if (!(tmp_line = (char *)malloc(sizeof(char) * (ps->place - tmp_pos + 1))))
		{
			ps->place = 1;
			return ;										// error
		}
		index = 0;
		while (index < ps->place - tmp_pos)
		{
			tmp_line[index] = line[tmp_pos + index];
			index++;
		}
		tmp_line[index] = '\0';


		if (ps->quote_start == 0 || ps->quote_start == '\"')
			tmp_line = find_env_variable(tmp_line, ps);

		tmp_line = clear_shielding(tmp_line, ps);

		if (tok->arg)
			tok->arg = ft_str_to_str(tok->arg, tmp_line);
		else
			tok->arg = tmp_line;

		if (ps->quote_start != 0)
		{
			if (line[ps->place] == ps->quote_start)
				ps->place++;
			else
			{
				ps->place = -1;
				return ;
			}
		}
		while (check_divide(line[ps->place], " \t", 0) == 1)
			ps->place++;
		if (tok->pars.comment != 0)
			break;
		if (line[ps->place] == '>' || line[ps->place] == '<')
			ps->place = check_redirect(line, ps->place, tok);
		if (line[ps->place] == ';')
			break ;
		if (line[ps->place] == '|')
		{
			tok->pipe = 1;
			break ;
		}
		if (line[ps->place] == '\0')
			break ;
	}
	return ;
}