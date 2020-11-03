# include "../minishell.h"

int				quote_no(char *line, t_token *tok, t_pars *ps, char **env)
{
	char		*tmp_line;

	tmp_line = NULL;
	while (line[ps->pos] != '\0' && line[ps->pos] != ' ' &&
            line[ps->pos] != '\t' && line[ps->pos] != ';' && 
            line[ps->pos] != '\"' && line[ps->pos] != '\'')
	{
		if (line[ps->pos] == '\0')
			break ;

		if (line[ps->pos] == '$')
		{
			ps->pos++;

			ps->ps_env->env_line = 0;
			ps->ps_env->env_pos = 0;
			ps->ps_env->str_pos = ps->pos;
			ps->ps_env->str = NULL;
			
			check_env(line, ps->ps_env, env);

			ps->pos = ps->ps_env->str_pos;

			if (ps->ps_env->str != NULL)
				tmp_line = ft_str_to_str(tmp_line, ps->ps_env->str);
			continue ;
		}

		if (line[ps->pos] == '>' || line[ps->pos] == '<')
		{
			while (line[ps->pos] == '>' || line[ps->pos] == '<')
			{
				tok->redir = ft_letter_to_str(tok->redir, line[ps->pos], 0);
				ps->pos++;
			}
			while (line[ps->pos] == ' ' || line[ps->pos] == '\t' || line[ps->pos] == '\0')
				ps->pos++;
			while (line[ps->pos] != ' ' && line[ps->pos] != '\t' && line[ps->pos] != '\0')
			{
				tok->file = ft_letter_to_str(tok->file, line[ps->pos], 0);
				ps->pos++;
			}
			continue ;
		}

		if (line[ps->pos] == '\\' && line[ps->pos + 1] != '\\')
			ps->pos++;
		if (line[ps->pos] == '\\' && line[ps->pos + 1] == '#')
			ps->pos++;
		tmp_line = ft_letter_to_str(tmp_line, line[ps->pos], 0);
		ps->pos++;


		// if (line[ps->pos] == ' ')
		// 	break ;


	}

	if (tmp_line)
	{
		if (tok->arg)
		{
			if (ps->space == 1)
				tok->arg = ft_letter_to_str(tok->arg, ' ', 0);
			tok->arg = ft_str_to_str(tok->arg, tmp_line);
		}
		else
			tok->arg = tmp_line;
	}

	return (0);
}
