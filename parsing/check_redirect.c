# include "../minishell.h"

void		check_redirect(char *line, t_pars *ps, t_token *tok, char **env)
{
	tok->tmp = NULL;
	// tok->redir = NULL;
	// tok->file = NULL;
	while (line[ps->pos] == '>' || line[ps->pos] == '<')
	{
		tok->tmp = ft_letter_to_str(tok->tmp, line[ps->pos], 0);
		ps->pos++;
	}
	tok->redirect = ft_str_to_array(tok->redirect, tok->tmp);
	while (line[ps->pos] == ' ' || line[ps->pos] == '\t' || line[ps->pos] == '\0')
		ps->pos++;



	tok->tmp = NULL;
	while (line[ps->pos] != '\0' && line[ps->pos] != ';' &&
			line[ps->pos] != '|' && line[ps->pos] != ' ' &&
			line[ps->pos] != '>' && line[ps->pos] != '<')
	{
		// while (line[ps->pos] == ' ' || line[ps->pos] == '\t')
		// 	ps->pos++;
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
		else
			quote_no(line, tok, ps, env, 1);

		// if (line[ps->pos] == ' ' ||	line[ps->pos] == '\t' ||
		// 		line[ps->pos] == '\0' || line[ps->pos] == ';' ||
		// 		line[ps->pos] == '|')
		// {
		// 	tok->args = ft_str_to_array(tok->args, tok->tmp);
		// 	tok->tmp = NULL;
		// }
	
	}


	// while (line[ps->pos] != ' ' && line[ps->pos] != '\t' && line[ps->pos] != '\0')
	// {
	// 	tok->file = ft_letter_to_str(tok->file, line[ps->pos], 0);
	// 	ps->pos++;
	// }

	// tok->file = tok->tmp;
	tok->redirect = ft_str_to_array(tok->redirect, tok->tmp);
	tok->tmp = NULL;

}


