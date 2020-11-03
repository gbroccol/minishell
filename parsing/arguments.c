# include "../minishell.h"

int			arguments(char *line, t_tokens *tok, t_pars *ps, char **env)
{
	check_flags(line, ps, tok);
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

		if (line[ps->pos] == ' ' || line[ps->pos] == '\t')
		{
			ps->space = 1;
			while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
				ps->pos++;
		}
		else
			ps->space = 0;

	}
	if (line[ps->pos] == ';')
	{
		ps->pos++;
		return (1);
	}
	if (line[ps->pos] == '|')
	{
		ps->pos++;
		tok->pipe = 1;
		return (1);
	}
	return (0);
}
