# include "../minishell.h"

int			arguments(t_all *all, char *line, t_token *tok, t_pars *ps, char **env)
{
	while (line[ps->pos] != '\0' && line[ps->pos] != ';' && line[ps->pos] != '|')
	// while (line[ps->pos] != '\0')
	{
		while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
			ps->pos++;
		if (line[ps->pos] == '\'')
		{
			ps->pos++;
			quote_one(line, tok, ps);
		}	
		else if (line[ps->pos] == '\"')
		{
			ps->pos++;
			quote_two(line, tok, ps, env);
		}
		else if (line[ps->pos] == '#')
			return (0);
		else
			quote_no(line, tok, ps, env, 0);

		if (line[ps->pos] == ' ' ||	line[ps->pos] == '\t' ||
				line[ps->pos] == '\0' || line[ps->pos] == ';' ||
				line[ps->pos] == '|')
		{
			if (tok->tmp)
			{
				tok->args = ft_str_to_array(tok->args, tok->tmp);
				tok->tmp = NULL;
			}
		}
	
	}
	if (line[ps->pos] == ';')
	{
		ps->pos++;
		while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
				ps->pos++;
		if (line[ps->pos] == '\0')
			return (0);
		else
			return (1);
	}
	if (line[ps->pos] == '|') // ждать окончания команды будем?
	{
		all->wait_cmd = 1;
		tok->pipe = 1;
		ps->pos++;
		while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
				ps->pos++;
		if (line[ps->pos] == '\0')
			return (0);
		else
			return (1);
	}
	return (0);
}

