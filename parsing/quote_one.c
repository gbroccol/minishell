# include "../minishell.h"

int				quote_one(char *line, t_token *tok, t_pars *ps)
{
	char		*tmp_line;

	tmp_line = NULL;
	while (line[ps->pos] != '\0' && line[ps->pos] != '\'')
	{
		tmp_line = ft_letter_to_str(tmp_line, line[ps->pos], 0);
		ps->pos++;
	}
	// if (tok->arg)
	// {
	// 	if (ps->space == 1)
	// 		tok->arg = ft_letter_to_str(tok->arg, ' ', 0);
	// 	tok->arg = ft_str_to_str(tok->arg, tmp_line);
	// }
	// else
	// 	tok->arg = tmp_line;

	if (tok->tmp)
	{
		tok->tmp = ft_str_to_str(tok->tmp, tmp_line);
	}
	else
	{
		tok->tmp = tmp_line;
	}

	if (line[ps->pos] == '\'')
	{
		ps->quote_finish = 1;
		ps->pos++;
	}
	return (0);
}
