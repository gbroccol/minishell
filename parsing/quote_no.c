# include "../minishell.h"

int				quote_no(char *line, t_token *tok, t_pars *ps, char **env, int redir_ignor)
{
	char		*tmp_line;

	tmp_line = NULL;
	while (line[ps->pos] != '\0' && line[ps->pos] != ' ' &&
            line[ps->pos] != '\t' && line[ps->pos] != ';' && 
            line[ps->pos] != '\"' && line[ps->pos] != '\'' && line[ps->pos] != '|')
	{
		if (line[ps->pos] == '\0')
			break ;

		if (line[ps->pos] == '$')
		{
			is_env(line, ps, env);
			if (ps->ps_env->str != NULL)
				tmp_line = ft_str_to_str(tmp_line, ps->ps_env->str);
			continue ;
		}

		if (line[ps->pos] == '$' && line[ps->pos + 1] == '?')
		{
			tmp_line = ft_str_to_str(tmp_line, ps->status);
			ps->pos++;
			ps->pos++;
			continue ;
		}

		if (line[ps->pos] == '~')
			if (line[ps->pos + 1] == ' ' || line[ps->pos + 1] == ';' || line[ps->pos + 1] == '|'
					|| line[ps->pos + 1] == '/' || line[ps->pos + 1] == ':' || line[ps->pos + 1] == '\0')
			{
				ps->pos++;
				ps->ps_env->env_line = 0;
				ps->ps_env->env_pos = 0;
				ps->ps_env->str_pos = 0;
				ps->ps_env->str = NULL;
				check_env("HOME", ps->ps_env, env);
				if (ps->ps_env->str != NULL)
					tmp_line = ft_str_to_str(tmp_line, ps->ps_env->str);
				continue ;
			}
		if (redir_ignor == 0)
		{
			if (line[ps->pos] == '>' || line[ps->pos] == '<')
			{
				check_redirect(line, ps, tok, env);
				continue ;
			}
		}
		else
			if (line[ps->pos] == '>' || line[ps->pos] == '<')
				break ;
		if (line[ps->pos] == '\\' && line[ps->pos + 1] != '\\')
			ps->pos++;
		if (line[ps->pos] == '\\' && line[ps->pos + 1] == '#')
			ps->pos++;
		tmp_line = ft_letter_to_str(tmp_line, line[ps->pos], 0);
		ps->pos++;
	}

	if (tmp_line)
	{
		if (tok->tmp)
			tok->tmp = ft_str_to_str(tok->tmp, tmp_line);
		else
			tok->tmp = tmp_line;
	}
	return (0);
}
