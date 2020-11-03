# include "../minishell.h"

int				quote_two(char *line, t_tokens *tok, t_pars *ps, char **env)
{
	char		*tmp_line;

	tmp_line = NULL;
	while (line[ps->pos] != '\0' && line[ps->pos] != '\"')
	{
		if (line[ps->pos] == '$')
		{
			if (line[ps->pos + 1] != '\"' && line[ps->pos + 1] != '/' &&
					line[ps->pos + 1] != '\'' &&
					line[ps->pos + 1] != ' ' &&
					line[ps->pos + 1] != '\t' &&
					line[ps->pos + 1] != '|')
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
		}
		if (line[ps->pos] == '\\' && line[ps->pos + 1] == '$')
		{
			ps->pos++;
			// continue ;
		}
        if (line[ps->pos] == '\\' && line[ps->pos + 1] == '\"')
		{
			ps->pos++;
			// continue ;
		}
		tmp_line = ft_letter_to_str(tmp_line, line[ps->pos], 0);
		ps->pos++;
	}
	if (tok->arg)
	{
		if (ps->space == 1)
			tok->arg = ft_letter_to_str(tok->arg, ' ', 0);
		tok->arg = ft_str_to_str(tok->arg, tmp_line);
	}
	else
		tok->arg = tmp_line;
	if (line[ps->pos] == '\"')
	{
		ps->quote_finish = 1;
		ps->pos++;
	}
	return (0);
}
