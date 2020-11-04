# include "../minishell.h"

int			arguments(char *line, t_token *tok, t_pars *ps, char **env)
{
	int		index;
	char	**tmp_args;

	check_flags(line, ps, tok);
	// tok->args = NULL;
	while (line[ps->pos] != '\0' && line[ps->pos] != ';' && line[ps->pos] != '|')
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
			quote_no(line, tok, ps, env);

		if (line[ps->pos] == ' ' || line[ps->pos] == '\t' || line[ps->pos] == '\0')
		{
			// ps->space = 1;

			index = 0;

			while (tok->args != NULL && tok->args[index] != NULL)
				index++;
			if (!(tmp_args = (char **)malloc(sizeof(char *) * (index + 2))))
				return (-1);

			index = 0;
			while (tok->args != NULL && tok->args[index] != NULL)
			{
				tmp_args[index] = tok->args[index];
				index++;
			}
			tmp_args[index] = tok->tmp;
			index++;
			tmp_args[index] = NULL;
				
			if (tok->args != NULL)
				free(tok->args);
			tok->args = tmp_args;

			while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
				ps->pos++;
			tok->tmp = NULL;
		}
		// else
		// 	ps->space = 0;

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

