# include "../minishell.h"

void		choose_com(t_token *tok)
{
	if (tok->args[0] == NULL)
		tok->type_func = TYPE_NO;
	else if ((ft_strncmp(tok->args[0], "cd", 3)) == 0)
		tok->type_func = TYPE_CD;
	else if ((ft_strncmp(tok->args[0], "pwd", 4)) == 0)
		tok->type_func = TYPE_PWD;
	else if ((ft_strncmp(tok->args[0], "echo", 5)) == 0)
		tok->type_func = TYPE_ECHO;
	else if ((ft_strncmp(tok->args[0], "exit", 5)) == 0)
		tok->type_func = TYPE_EXIT;
	else if ((ft_strncmp(tok->args[0], "export", 7)) == 0)
		tok->type_func = TYPE_EXPORT;
	else if ((ft_strncmp(tok->args[0], "env", 4)) == 0)
		tok->type_func = TYPE_ENV;
	else if ((ft_strncmp(tok->args[0], "unset", 6)) == 0)
		tok->type_func = TYPE_UNSET;
	else if ((ft_strncmp(tok->args[0], "", 1)) == 0)
		tok->type_func = TYPE_NO;
	else
		tok->type_func = TYPE_BIN;
}

void			command(char *line, t_token *tok, t_pars *ps, char **env)
{
	if (!(tok->args = (char **)malloc(sizeof(char *) * 2)))
		return ; // error
	tok->args[0] = NULL;
	tok->args[1] = NULL;

	while (line[ps->pos] != '\0' &&
			line[ps->pos] != ';' &&
			line[ps->pos] != '|' &&
			line[ps->pos] != ' ')
	{
		if (line[ps->pos] == '\'')
		{
			ps->pos++;
			cmd_quote_one(line, tok, ps);
		}	
		else if (line[ps->pos] == '\"')
		{
			ps->pos++;
			cmd_quote_two(line, tok, ps, env);
		}
		else
			cmd_quote_no(line, tok, ps, env);

		if (line[ps->pos] == ' ' || line[ps->pos] == '\t')
			break ;
	}
	choose_com(tok);
}