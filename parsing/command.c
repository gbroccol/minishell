# include "../minishell.h"

void		choose_com(t_token *tok, char *cmd)
{
	if (cmd == NULL)
		tok->type_func = TYPE_NO;
	else if ((ft_strncmp(cmd, "cd", 3)) == 0)
		tok->type_func = TYPE_CD;
	else if ((ft_strncmp(cmd, "pwd", 4)) == 0)
		tok->type_func = TYPE_PWD;
	else if ((ft_strncmp(cmd, "echo", 5)) == 0)
		tok->type_func = TYPE_ECHO;
	else if ((ft_strncmp(cmd, "exit", 5)) == 0)
		tok->type_func = TYPE_EXIT;
	else if ((ft_strncmp(cmd, "export", 7)) == 0)
		tok->type_func = TYPE_EXPORT;
	else if ((ft_strncmp(cmd, "env", 4)) == 0)
		tok->type_func = TYPE_ENV;
	else if ((ft_strncmp(cmd, "unset", 6)) == 0)
		tok->type_func = TYPE_UNSET;
	// else if ((ft_strncmp(cmd, "", 1)) == 0)
	// 	tok->type_func = TYPE_NO;
	else
		tok->type_func = TYPE_BIN;
}

void			command(char *line, t_token *tok, t_pars *ps, char **env)
{
	int			index;

	tok->tmp = NULL;
	while(line[ps->pos] == ' ' || line[ps->pos] == '\t')
		ps->pos++;
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
	tok->cmd = ft_strdup(tok->tmp);
	index = 0;
	while (tok->tmp != NULL && tok->tmp[index] != '\0')
	{
		tok->tmp[index] = ft_tolower(tok->tmp[index]);
		index++;
	}
	choose_com(tok, tok->tmp);
	if (tok->tmp)
		tok->args = ft_str_to_array(tok->args, tok->tmp);
	tok->tmp = NULL;
}