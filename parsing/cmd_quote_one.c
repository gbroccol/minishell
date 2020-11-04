# include "../minishell.h"

int				cmd_quote_one(char *line, t_token *tok, t_pars *ps)
{
	char		*tmp_line;

	tmp_line = NULL;
	while (line[ps->pos] != '\0' && line[ps->pos] != '\'')
	{
		tmp_line = ft_letter_to_str(tmp_line, line[ps->pos], 0);
		ps->pos++;
	}
	// if (tok->cmd)
	// 	tok->cmd = ft_str_to_str(tok->cmd, tmp_line);
	// else
	// 	tok->cmd = tmp_line;

	if (tok->args[0])
		tok->args[0] = ft_str_to_str(tok->args[0], tmp_line);
	else
		tok->args[0] = tmp_line;

	if (line[ps->pos] == '\'')
		ps->pos++;
	return (0);
}
